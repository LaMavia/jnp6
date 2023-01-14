#ifndef DICE_H
#define DICE_H

#include <vector>
#include <memory>
#include "worldcup.h"

class Dice {
public:
  Dice() : dice({}) {}

  void addNextDie(std::shared_ptr<Die> d) { dice.push_back(d); }

  size_t diceNum() { return dice.size(); }

  size_t rollDice() {
    int x = 0;
    for (auto const &d : dice) {
      x += d->roll();
    }
    return x;
  }

  ~Dice() = default;

private:
  std::vector<std::shared_ptr<Die>> dice;
};

#endif /* DICE_H */