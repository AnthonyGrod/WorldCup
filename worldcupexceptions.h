#ifndef WORLDCUP_WORLDCUPEXCEPTIONS_H
#define WORLDCUP_WORLDCUPEXCEPTIONS_H

class TooManyDiceException : std::exception {
public:
    const char* what() const noexcept override { return "Too Many Dices!"; }
};

class TooFewDiceException : std::exception {
public:
    const char* what() const noexcept override { return "Too Few Dices!"; }
};

class TooManyPlayersException : std::exception {
public:
    const char* what() const noexcept override { return "Too Many Players!"; }
};

class TooFewPlayersException : std::exception {
public:
    const char* what() const noexcept override { return "Too Few Players!"; }
};

#endif //WORLDCUP_WORLDCUPEXCEPTIONS_H
