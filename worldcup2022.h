#ifndef WORLDCUP2022_H
#define WORLDCUP2022_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "worldcup.h"
#include "player.h"
#include "dice.h"

void dbg(std::string s) { std::cerr << s << std::endl; }

class WorldCup2022 : public WorldCup {
private:
  Dice dice;
  std::vector<std::shared_ptr<Player>> players;
  std::shared_ptr<ScoreBoard> scoreboard;

public:
  WorldCup2022() : dice({}), players({}), scoreboard({}) {}

  void addDie(std::shared_ptr<Die> die) { dice.addNextDie(die); };

  void addPlayer(const std::string &name) { players.emplace_back(name); };

  void setScoreBoard(std::shared_ptr<ScoreBoard> scoreboard) {
    this->scoreboard = scoreboard;
  };

  void play(unsigned int rounds) {
    checkConditions();
    setPlayersOnStart();
    for (unsigned int i = 1; i <= rounds; i++) {
      dbg("Start rundy: " + std::to_string(i));
      makeRound();
    }
  };

private:
  void checkConditions() {}

  void setPlayersOnStart() {}

  void makeRound() { passInfoToScoreBoard(); }

  void passInfoToScoreBoard() {}

  void makeMove() {}
};

#endif /* WORLDCUP2022_H */