#ifndef WORLDCUP_WORLDCUP2022_H
#define WORLDCUP_WORLDCUP2022_H

#include <memory>
#include "worldcup.h"
#include "player.h"
#include "field.h"
#include "gameboard.h"

class WorldCup2022 : WorldCup {
private:
    std::vector< std::shared_ptr<Die> > dices;
    std::vector< std::shared_ptr<Player> > players;
    std::unique_ptr<GameBoard> gameBoard;
    std::shared_ptr<ScoreBoard> scoreBoard;

public:
    WorldCup2022() :
        gameBoard(std::make_shared<GameBoard>())
    {}

    void addDie(std::shared_ptr<Die> die) override {
        this->dices.push_back(die);
    }

    void addPlayer(std::string const &name) override {
        this->players.push_back(std::make_shared<Player>(name))
    }

    void setScoreBoard(std::shared_ptr<ScoreBoard> sb) override {
        this->scoreBoard = sb;
    }

    void play(unsigned int rounds) override {
        bool end = false;
        unsigned int roundsCounter = 0;
        while (!end && roundsCounter < rounds) {
            
        }
    }
};

#endif //WORLDCUP_WORLDCUP2022_H
