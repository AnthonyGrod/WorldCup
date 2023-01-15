#ifndef WORLDCUP_WORLDCUP2022_H
#define WORLDCUP_WORLDCUP2022_H

#include <memory>
#include <vector>
#include "worldcup.h"
#include "player.h"
#include "field.h"
#include "gameboard.h"
#include "worldcupexceptions.h"

class WorldCup2022 : public WorldCup {
private:
    const size_t minPlayersAmount = 2;
    const size_t maxPlayersAmount = 11;
    const size_t minDicesAmount = 2;
    const size_t maxDicesAmount = 2;

    Dices dices;
    std::vector< std::shared_ptr<Player> > players;
    std::shared_ptr<GameBoard> gameBoard;
    std::shared_ptr<ScoreBoard> scoreBoard;

public:
    WorldCup2022() :
        gameBoard(std::make_shared<GameBoard>())
    {}

    ~WorldCup2022() override = default;

    void addDie(std::shared_ptr<Die> die) override {
        this->dices.add_die(die);
    }

    void addPlayer(std::string const &name) override {
        this->players.push_back(std::make_shared<Player>(name));
    }

    void setScoreBoard(std::shared_ptr<ScoreBoard> scoreboard) override {
        this->scoreBoard = scoreboard;
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

    bool isOnlyOneAlive() const {
        int aliveCounter = 0;
        for (auto &it : this->players) {
            if (!it->is_bankrupt()) {
                aliveCounter++;
            }
        }
        if (aliveCounter < 2) {
            return true;
        }
        return false;
    }

    int getWinnersIndex() const {
        zdzislaw_t maxCoins = 0;
        int winnerIndex = 0;
        int index = 0;
        for (auto &it : players) {
            if (it->get_money() > maxCoins) {
                winnerIndex = index;
            }
            index++;
        }
        return winnerIndex;
    }

    void play(unsigned int rounds) override {
        playPreprocessing();
        bool end = false;
        unsigned int roundsCounter = 0;
        const int fieldsTotal = this->gameBoard->get_fields().size();
        int diceResult;
        int currPosition;
        while (!end && roundsCounter < rounds) {
            scoreBoard->onRound(roundsCounter);
            for (auto &it : this->players) {
                if (it->get_wait_time() > 0) {
                    diceResult = this->dices.roll();
                    for (int i = 0; i < diceResult; i++) {
                        currPosition = (currPosition + 1) % (fieldsTotal + 1);
                        if (currPosition == 0) {
                            ++currPosition;
                        }
                        if (i == diceResult - 1) {
                            this->gameBoard->get_fields()[currPosition]->on_landing(it);
                        } else {
                            this->gameBoard->get_fields()[currPosition]->through_field(it);
                        }
                        if (it->is_bankrupt()) {
                            std::remove(this->players.begin(), this->players.end(), it);
                        }
                        if (this->players.size() == 1) {
                            end = true;
                        }
                    }
                } else {
                    it->decrease_wait_time();
                }
                scoreBoard->onTurn(it->get_name(),it->get_info(),
                        this->gameBoard->get_fields()[currPosition]->get_name(),it->get_money());
            }

            roundsCounter++;
        }
        int winnerIndex = getWinnersIndex();
        scoreBoard->onWin(players[winnerIndex]->get_name());
    }
};

#endif //WORLDCUP_WORLDCUP2022_H
