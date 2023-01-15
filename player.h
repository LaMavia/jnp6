#ifndef PLAYER_H
#define PLAYER_H

#include "resetable.h"
#include <string>


/*
  Gracz zna tylko stan swojego konta oraz czy jest jeszcze w grze.
*/

class Player : public Resetable {
public:
  Player(std::string name) : name(name) { reset(); }
  ~Player() = default;
  void giveMoney(unsigned int m) { money += m; }
  unsigned int takeMoney(unsigned int m) {
    if (m >= money) {
      auto res = money;
      money = 0;
      bankrupted = true;

      return res;
    } else {
      money -= m;
      return m;
    }
  }

  unsigned int getMoney() const { return money; }
  const std::string &getName() const { return name; }
  bool isStillInGame() const { return !bankrupted; }

  void reset() {
    money = 1000;
    bankrupted = false;
  }

private:
  std::string name;
  unsigned int money;
  bool bankrupted;
};

#endif