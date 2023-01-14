#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <unordered_map>

#include "player.h"
#include "weight.h"

class Field {
public:
  Field() = default;
  virtual ~Field() = default;
  virtual void onPass([[maybe_unused]] Player &p) {}
  virtual void onStay([[maybe_unused]] Player &p) {}
  virtual bool canMove([[maybe_unused]] const Player &p) const { return true; }
  virtual std::string giveStatus([[maybe_unused]] Player &p) {
    return "w grze";
  }
  virtual void onLeave([[maybe_unused]] Player &p) {}
  virtual std::string getName() const = 0;
};

class GameField : public Field {
public:
  GameField(unsigned int penalty, Weight weight, std::string &&title)
      : penalty(penalty), weight(doubleOfWeight(weight)), accumulated(0),
        title(title) {}
  ~GameField() = default;

  void onPass(Player &p) override { accumulated += p.takeMoney(penalty); }
  std::string getName() const { return "Mecz z " + title; }

  void onStay(Player &p) override {
    p.giveMoney(static_cast<unsigned int>(weight * accumulated));
  }

protected:
  unsigned int penalty;
  double weight;
  unsigned int accumulated;
  std::string title;
};

class YellowCardField : public Field {
public:
  YellowCardField(unsigned int timeout) : timeout(timeout), players({}) {}
  ~YellowCardField() = default;
  void onStay(Player &p) override { players.insert({p.getName(), timeout}); }
  std::string giveStatus(Player &p) override {
    return "*** czekanie: " + std::to_string(players.at(p.getName())--) +
           " ***";
  }
  std::string getName() const { return "Żółta kartka"; }
  void onLeave(Player &p) override { players.erase(p.getName()); }
  bool canMove(const Player &p) const override {
    bool contains = players.contains(p.getName());
    bool done = players.at(p.getName()) == 0;
    return !contains || done;
  }

protected:
  unsigned int timeout;
  std::unordered_map<std::string, unsigned int> players;
};

class StartField : public Field {
public:
  StartField() = default;
  std::string getName() const { return "Początek sezonu"; }
  void onPass(Player &p) override { p.giveMoney(50); }
  void onStay(Player &p) override { p.giveMoney(50); }
};

class GoalField : public Field {
public:
  GoalField(unsigned long prize) : prize(prize) {}
  std::string getName() const { return "Gol"; }
  void onStay(Player &p) override { p.giveMoney(prize); }

private:
  unsigned int prize;
};

class PenaltyKickField : public Field {
public:
  PenaltyKickField(unsigned int penalty) : penalty(penalty) {}
  std::string getName() const { return "Rzut karny"; }
  void onStay(Player &p) override { p.takeMoney(penalty); }

private:
  unsigned int penalty;
};

class BookmakerField : public Field {
public:
  BookmakerField(unsigned int penalty, unsigned int bonus, size_t frequency)
      : penalty(penalty), bonus(bonus), frequency(frequency), visitCount(0) {}
  std::string getName() const { return "Bukmacher"; }
  void onStay(Player &p) override {
    visitCount = (visitCount + 1) % frequency;
    if (visitCount == 1) {
      p.giveMoney(bonus);
    } else {
      p.takeMoney(penalty);
    }
  }

private:
  unsigned int penalty;
  unsigned int bonus;
  size_t frequency;
  size_t visitCount;
};

class DayOffField : public Field {
public:
  std::string getName() const { return "Dzień wolny od treningu"; }
};

// implementacje pól

#endif /* FIELD_H */