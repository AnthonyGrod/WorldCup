#ifndef PLAYER_H
#define PLAYER_H

#define STARTING_MONEY 1000
using zdzislaw_t = size_t;

class Player {
private:
    const std::string name;
    zdzislaw_t zdzislawy;
    bool bankrupt;
    size_t position;
    size_t wait_time;
public:
    explicit Player(const std::string &player_name)
            : name(std::move(player_name)),
              zdzislawy(STARTING_MONEY),
              bankrupt(false),
              position(1),
              wait_time(0) {
    }

    const std::string &get_name() const {
        return name;
    }

    zdzislaw_t get_money() const {
        return zdzislawy;
    }

    size_t get_position() const {
        return position;
    }

    size_t get_wait_time() const {
        return wait_time;
    }

    bool is_bankrupt() const {
        return bankrupt;
    }


    std::string get_info() const {
        if (bankrupt) {
            return "*** bankrut ***";
        }
        else if (wait_time > 0) {
            return "*** czekanie: " + std::to_string(wait_time) + "***";
        }
        else {
            return "w grze";
        }
    }

    void set_wait_time(size_t turns) {
        wait_time = turns;
    }

    void decrease_wait_time() {
        wait_time--;
    }

    void set_position(size_t new_position) {
        position = new_position;
    }

    void add_money(zdzislaw_t amount) {
        zdzislawy += amount;
    }

    void take_money(zdzislaw_t amount) {
        if (zdzislawy >= amount) {
            zdzislawy -= amount;
        }
        else {
            zdzislawy = 0;
            bankrupt = true;
        }
    }
};

#endif // PLAYER_H
