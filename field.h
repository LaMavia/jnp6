#ifndef FIELD_H
#define FIELD_H

#include <map>

#include "player.h"

class Field {
public:
  Field() = default;
  virtual ~Field() = 0;
  virtual void onPass(Player &p) {}
  virtual void onStay(Player &p) {}
  virtual bool canMove(const Player &p) const { return true; }
  virtual void giveStatus(Player &p) {}
  virtual void onLeave(Player &p) {}
};

class Game : public Field {
public:
  Game(unsigned int penalty, double weight, std::string &&title)
      : penalty(penalty), weight(weight), accumulated(0), title(title) {}
  ~Game() = default;

  void onPass(Player &p) { accumulated += p.takeMoney(penalty); }

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
  void giveStatus(Player &p) {
    p.setStatus("*** czekanie: " + std::to_string(players.at(p.getName())--) +
                " ***");
  }
  void onLeave(Player &p) { players.erase(p.getName()); }
  bool canMove(Player &p) const {
    return !players.contains(p.getName()) || players.at(p.getName()) == 0;
  }

protected:
  unsigned int timeout;
  std::map<const std::string &, unsigned int> players;
};

// implementacje pól

#endif /* FIELD_H */