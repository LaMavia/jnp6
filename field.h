#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <unordered_map>

#include "player.h"

class Field {
public:
  virtual ~Field() = 0;
  virtual void onPass([[maybe_unused]] Player &p) {}
  virtual void onStay([[maybe_unused]] Player &p) {}
  virtual bool canMove([[maybe_unused]] const Player &p) const { return true; }
  virtual std::string giveStatus(const Player &p) = 0;
  virtual void onLeave([[maybe_unused]] Player &p) {}
  virtual std::string getName() = 0;
};

class Game : public Field {
public:
  Game(unsigned int penalty, double weight, std::string &&title)
      : penalty(penalty), weight(weight), accumulated(0), title(title) {}
  ~Game() = default;

  void onPass(Player &p) { accumulated += p.takeMoney(penalty); }
  std::string giveStatus([[maybe_unused]] Player &p) { return "w grze"; }
  std::string getName() { return "Mecz z " + title; }

  void onStay(Player &p) {
    p.giveMoney(static_cast<unsigned int>(weight * accumulated));
  }

protected:
  unsigned int penalty;
  double weight;
  unsigned int accumulated;
  std::string title;
};

class YellowCard : public Field {
public:
  YellowCard(unsigned int timeout) : timeout(timeout), players({}) {}
  ~YellowCard() = default;
  void onStay(Player &p) { players.insert({p.getName(), timeout}); }
  std::string giveStatus(Player &p) {
    return "*** czekanie: " + std::to_string(players.at(p.getName())--) +
           " ***";
  }
  std::string getName() { return "żółta kartka"; }
  void onLeave(Player &p) { players.erase(p.getName()); }
  bool canMove(Player &p) const {
    return !players.contains(p.getName()) || players.at(p.getName()) == 0;
  }

protected:
  unsigned int timeout;
  std::unordered_map<std::string, unsigned int> players;
};

// implementacje pól

#endif /* FIELD_H */