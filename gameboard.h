#ifndef WORLDCUP_BOARD_H
#define WORLDCUP_BOARD_H

#include "field.h"

class GameBoard {
private:
    std::vector<std::unique_ptr<Field>> fields;
public:
    GameBoard() {
        fields.push_back(std::make_unique<Beginning_Field>("Początek sezonu"));
        fields.push_back(std::make_unique<Match_Field>("Mecz z San Marino", 160, 1));
        fields.push_back(std::make_unique<Free_Day>("Dzień wolny od treningu"));
        fields.push_back(std::make_unique<Match_Field>("Mecz z Lichtensteinem", 220, 1));
        fields.push_back(std::make_unique<Yellow_Card>("Żółta kartka", 3));
        fields.push_back(std::make_unique<Match_Field>("Mecz z Meksykiem", 300, 2.5));
        fields.push_back(std::make_unique<Match_Field>("Mecz z Arabią Saudyjską", 280, 2.5));
        fields.push_back(std::make_unique<Bookmaker_Field>("Bukmacher", 100));
        fields.push_back(std::make_unique<Match_Field>("Mecz z Argentyną", 250, 2.5));
        fields.push_back(std::make_unique<Goal_Field>("Gol", 120));
        fields.push_back(std::make_unique<Match_Field>("Mecz z Francją", 400, 3));
        fields.push_back(std::make_unique<Penalty_Field>("Rzut karny", 180));
    };

    const std::vector<std::unique_ptr<Field>>& get_fields() const {
        return this.fields;
    }
};

#endif //WORLDCUP_BOARD_H
