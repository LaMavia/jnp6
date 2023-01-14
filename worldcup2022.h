#ifndef WORLDCUP2022_H
#define WORLDCUP2022_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "board.h"
#include "dice.h"
#include "player.h"
#include "worldcup.h"

void dbg(std::string s) { std::cerr << s << std::endl; }

class WorldCup2022 : public WorldCup {
public:
  WorldCup2022()
      : dice({}), players({}), scoreboard({}), roundNumber(0), isOver(false) {}

  void addDie(std::shared_ptr<Die> die) { dice.addNextDie(die); };

  void addPlayer(const std::string &name) {
    players.push_back(std::make_shared<Player>(name));
  };

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
  void checkConditions() {
    auto nPlayers = players.size();

    if (nPlayers < 2 || nPlayers > 11) {
      throw std::runtime_error{"@todo WorldCup.checkConditions()"};
    }

    board.checkConditions();
  }

  void setPlayersOnStart() {
    for (auto &p : players) {
      p->reset();
    }

    board.reset();
  }

  void makeRound() {
    scoreboard->onRound(roundNumber++);
    size_t nStillInGame = 0;

    for (auto &p : players) {
      makeMove(p, nStillInGame);
    }

    if (nStillInGame == 1) {
      for (auto &p : players) {
        if (p->isStillInGame()) {
          scoreboard->onWin(p->getName());
        }
      }
      isOver = true;
    }
  }

  void makeMove(std::shared_ptr<Player> p, size_t nStillInGame) {
    if (!board.canPlayerMove(*p)) {
      return;
    }

    board.movePlayer(*p, dice.rollDice());
    scoreboard->onTurn(p->getName(), board.getPlayerStatus(*p),
                       board.getPlayerFieldName(*p), p->getMoney());

    if (p->isStillInGame()) {
      nStillInGame++;
    }
  }

private:
  Dice dice;
  std::vector<std::shared_ptr<Player>> players;
  std::shared_ptr<ScoreBoard> scoreboard;
  Board board;
  unsigned int roundNumber;
  bool isOver;
};

#endif /* WORLDCUP2022_H */