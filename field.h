#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <unordered_map>

#include "player.h"
#include "weight.h"

/*
  Pola w grze mają zaimplementowane metody, które korzystają z metod gracza
  modyfikujących jego stan konta.
*/
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

/*
    Pole reprezentujące mecz.
*/
class GameField : public Field {
public:
  GameField(unsigned int penalty, Weight weight, std::string &&title)
      : penalty(penalty), weight(doubleOfWeight(weight)), accumulated(0),
        title(title) {}
  ~GameField() = default;

  virtual void onPass(Player &p) override {
    accumulated += p.takeMoney(penalty);
  }

  std::string getName() const override { return "Mecz z " + title; }

  virtual void onStay(Player &p) override {
    p.giveMoney(static_cast<unsigned int>(weight * accumulated));
  }

private:
  unsigned int penalty;
  double weight;
  unsigned int accumulated;
  std::string title;
};

/*
    Pole reprezentujące żółtą kartkę.
*/
class YellowCardField : public Field {
public:
  YellowCardField(unsigned int timeout) : timeout(timeout), players({}) {}
  ~YellowCardField() = default;

  virtual void onStay(Player &p) override {
    players.insert({p.getName(), timeout});
  }

  virtual std::string giveStatus(Player &p) override {
    return "*** czekanie: " + std::to_string(players.at(p.getName())--) +
           " ***";
  }

  virtual std::string getName() const override { return "Żółta kartka"; }

  virtual void onLeave(Player &p) override { players.erase(p.getName()); }

  virtual bool canMove(const Player &p) const override {
    bool contains = players.contains(p.getName());
    bool done = players.at(p.getName()) == 0;
    return !contains || done;
  }

private:
  unsigned int timeout;
  std::unordered_map<std::string, unsigned int> players;
};

/*
    Pole reprezentujące pole startowe.
*/
class StartField : public Field {
public:
  StartField() = default;
  virtual std::string getName() const override { return "Początek sezonu"; }
  virtual void onPass(Player &p) override { p.giveMoney(50); }
  virtual void onStay(Player &p) override { p.giveMoney(50); }
};

class GoalField : public Field {
public:
  GoalField(unsigned long prize) : prize(prize) {}
  virtual std::string getName() const override { return "Gol"; }
  virtual void onStay(Player &p) override { p.giveMoney(prize); }

private:
  unsigned int prize;
};

/*
    Pole reprezentujące rzut karny.
*/
class PenaltyKickField : public Field {
public:
  PenaltyKickField(unsigned int penalty) : penalty(penalty) {}
  virtual std::string getName() const override { return "Rzut karny"; }
  virtual void onStay(Player &p) override { p.takeMoney(penalty); }

private:
  unsigned int penalty;
};

/*
    Pole reprezentujące bukmachera.
*/
class BookmakerField : public Field {
public:
  BookmakerField(unsigned int penalty, unsigned int bonus, size_t frequency)
      : penalty(penalty), bonus(bonus), frequency(frequency), visitCount(0) {}

  virtual std::string getName() const override { return "Bukmacher"; }

  virtual void onStay(Player &p) override {
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

/*
    Pole reprezentujące dzień wolny.
*/
class DayOffField : public Field {
public:
  virtual std::string getName() const override {
    return "Dzień wolny od treningu";
  }
};

#endif /* FIELD_H */