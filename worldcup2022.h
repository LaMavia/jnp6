#ifndef WORLDCUP2022_H
#define WORLDCUP2022_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "board.h"
#include "dice.h"
#include "player.h"
#include "weight.h"
#include "worldcup.h"
#include "exceptions.h"

#define MAX_DICE_NUM 2
#define MIN_DICE_NUM 2
#define MAX_PLAYERS_NUM 11
#define MIN_PLAYERS_NUM 2


void dbg(std::string s) { std::cerr << s << std::endl; }

/*
  Ta klasa ma dostęp do kostek, planszy, vectora graczy i tablicy wyników
  oraz koordynuje działania między nimi.
*/
class WorldCup2022 : public WorldCup {
public:
  WorldCup2022()
      : dice({}), players({}), scoreboard({}), board({}), roundNumber(0),
        isOver(false) {
    board.addField(std::make_shared<StartField>());
    board.addField(
        std::make_shared<GameField>(160, Weight::Friendly, "San Marino"));
    board.addField(std::make_shared<DayOffField>());
    board.addField(
        std::make_shared<GameField>(220, Weight::Friendly, "Lichtensteinem"));
    board.addField(std::make_shared<YellowCardField>(3));
    board.addField(
        std::make_shared<GameField>(300, Weight::Deciding, "Meksykiem"));
    board.addField(
        std::make_shared<GameField>(280, Weight::Deciding, "Arabią Saudyjską"));
    board.addField(std::make_shared<BookmakerField>(300, 100, 3));
    board.addField(
        std::make_shared<GameField>(250, Weight::Deciding, "Argentyną"));
    board.addField(std::make_shared<GoalField>(120));
    board.addField(std::make_shared<GameField>(400, Weight::Final, "Francją"));
    board.addField(std::make_shared<PenaltyKickField>(180));
  }

  void addDie(std::shared_ptr<Die> die) { 
    if (die != NULL){
      dice.addNextDie(die);
    } 
  };

  void addPlayer(const std::string &name) {
    players.push_back(std::make_shared<Player>(name));
  };

  void setScoreBoard(std::shared_ptr<ScoreBoard> scoreboard) {
    this->scoreboard = scoreboard;
  };

  void play(unsigned int rounds) {
    checkConditions();
    for (unsigned int i = 1; i <= rounds && !isOver; i++) {
      dbg("Start rundy: " + std::to_string(i));
      makeRound();
    }
  };

private:
  void checkConditions() {
    auto nPlayers = players.size();
    auto nDice = dice.diceNum();
    if (nDice > MAX_DICE_NUM){
      throw TooManyDiceException();
    }
    if (nDice < MIN_DICE_NUM){
      throw TooFewDiceException();
    }
    if (nPlayers > MAX_PLAYERS_NUM){
      throw TooManyPlayersException();
    }
    if (nPlayers < MIN_PLAYERS_NUM){
      throw TooFewPlayersException();
    }

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

  void makeMove(std::shared_ptr<Player> p, size_t &nStillInGame) {
    if (p->isStillInGame()) {
      if (board.canPlayerMove(*p)) {
        board.movePlayer(*p, dice.rollDice());
      }

      scoreboard->onTurn(p->getName(),
                         p->isStillInGame() ? board.getPlayerStatus(*p)
                                            : "*** bankrut ***",
                         board.getPlayerFieldName(*p), p->getMoney());
    }

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