#ifndef WORLDCUP2022_H
#define WORLDCUP2022_H

#include <memory>
#include <string>
#include <iostream>
#include <vector>

#include "worldcup.h"

using std::shared_ptr;
using std::vector;

class Die;

class ScoreBoard;

void dbg(std::string s){
    std::cerr<<s<<std::endl;
}

class Dice{
public:
    Dice(){
        dice = std::make_shared<vector<shared_ptr<Die>>>();
    }

    void addNextDie(shared_ptr<Die> d){
        dice->push_back(d);
    }

    size_t DiceNum(){
        return dice->size();
    }

    int rollDice(){
        int x = 0;
        for (shared_ptr<Die> d : *dice){
            x += d->roll();
        }
        return x;
    }

    ~Dice() = default;
private:
    shared_ptr<vector<shared_ptr<Die>>> dice;
};

class Player{

};

class Players{
public:
    Players(){
        players = std::make_shared<vector<shared_ptr<Player>>>();
    }

    void addNextPlayer(shared_ptr<Player> p){
        players->push_back(p);
    }

    size_t PlayersNum(){
        return players->size();
    }

    ~Players() = default;


private:
    shared_ptr<vector<shared_ptr<Player>>> players;
};

class WorldCup2022 : public WorldCup{
private:
    shared_ptr<Dice> dice;
public:

    WorldCup2022(){
        initPlayers();
        initDice();
        initScoreBoard();
        initBoard();
    }

    void addDie(std::shared_ptr<Die> die){

    };

    void addPlayer(std::string const &name){

    };

    void setScoreBoard(std::shared_ptr<ScoreBoard> scoreboard){

    };

    void play(unsigned int rounds){
        checkConditions();
        setPlayersOnStart();
        for (unsigned int i = 1; i <= rounds; i++){
            dbg("Start rundy: " + std::to_string(i));
            makeRound();
        }

        
    };

    



private:

    void initPlayers(){

    }

    void initDice(){
        shared_ptr<Dice> dice = std::make_shared<Dice>();
    }

    void initScoreBoard(){

    }

    void initBoard(){

    }

    void checkConditions(){

    }

    void setPlayersOnStart(){

    }

    void makeRound(){
        passInfoToScoreBoard();


    }

    void passInfoToScoreBoard(){

    }

    void makeMove(){

    }

};

#endif //WORLDCUP2022_H