#ifndef WORLDCUP_WORLDCUP2022_H
#define WORLDCUP_WORLDCUP2022_H

#include <memory>
#include <vector>
#include "worldcup.h"
#include "player.h"
#include "field.h"
#include "gameboard.h"
#include "worldcupexceptions.h"

class WorldCup2022 : WorldCup {
private:
    const size_t minPlayersAmount = 2;
    const size_t maxPlayersAmount = 11;
    const size_t minDicesAmount = 2;
    const size_t maxDicesAmount = 2;

    std::vector< std::shared_ptr<Die> > dices;
    std::vector< std::shared_ptr<Player> > players;
    std::shared_ptr<GameBoard> gameBoard;
    std::shared_ptr<ScoreBoard> scoreBoard;

public:
    WorldCup2022() :
        gameBoard(std::make_shared<GameBoard>())
    {}

    void addDie(std::shared_ptr<Die> die) override {
        this->dices.push_back(die);
    }

    void addPlayer(std::string const &name) override {
        this->players.push_back(std::make_shared<Player>(name));
    }

    void setScoreBoard(std::shared_ptr<ScoreBoard> sb) override {
        this->scoreBoard = sb;
    }

    void playPreprocessing() {
        if (this->dices.size() < this->minDicesAmount) {
            throw TooFewDiceException();
        } else if (this->dices.size() > maxDicesAmount) {
            throw TooManyDiceException();
        }
        if (this->players.size() < this->minPlayersAmount) {
            throw TooFewPlayersException();
        } else if (this->players.size() > this->maxPlayersAmount) {
            throw TooManyPlayersException();
        }
    }

    void play(unsigned int rounds) override {
        playPreprocessing();
        bool end = false;
        unsigned int roundsCounter = 0;
        while (!end && roundsCounter < rounds) {
            for (auto &it : this->players) {

            }
        }
    }
};

#endif //WORLDCUP_WORLDCUP2022_H
