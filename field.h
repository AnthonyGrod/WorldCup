#ifndef FIELD_H
#define FIELD_H

#include "player.h"

class Field {
private:
    std::string name;

public:
    explicit Field(const std::string &field_name)
            :name(std::move(field_name)) {
    }

    std::string const &get_name() const {
        return name;
    }

    virtual void on_landing([[maybe_unused]] std::shared_ptr<Player> player) = 0;

    virtual void through_field([[maybe_unused]] std::shared_ptr<Player> player) = 0;
};

class Beginning_Field : public Field {
private:
    zdzislaw_t bonus;

public:
    explicit Beginning_Field(const std::string &field_name)
            : Field(std::move(field_name)) {
        bonus = 50;
    }

    void on_landing(std::shared_ptr<Player> player) override {
        player->add_money(bonus);
    }

    void through_field(std::shared_ptr<Player> player) override {
        player->add_money(bonus);
    }
};

class Free_Day : public Field {
public:
    explicit Free_Day(const std::string &field_name)
            : Field(std::move(field_name)) {
    }

    void on_landing([[maybe_unused]] std::shared_ptr<Player> player) override {
        return;
    }

    void through_field([[maybe_unused]] std::shared_ptr<Player> player) override {
        return;
    }

};

class Penalty_Field : public Field {
private:
    const zdzislaw_t rate;

public:
    explicit Penalty_Field(const std::string &field_name, zdzislaw_t rate)
            : Field(std::move(field_name)),
              rate(rate) {
    }

    void on_landing(std::shared_ptr<Player> player) override {
        player->take_money(rate);
    }

    void through_field([[maybe_unused]] std::shared_ptr<Player> player) override {
        return;
    }
};

class Goal_Field : public Field {
private:
    zdzislaw_t bonus;

public:
    explicit Goal_Field(const std::string &field_name, zdzislaw_t bonus)
            : Field(std::move(field_name)),
              bonus(bonus) {
    }

    void on_landing(std::shared_ptr<Player> player) override {
        player->add_money(bonus);
    }

    void through_field([[maybe_unused]] std::shared_ptr<Player> player) override {
        return;
    }
};

class Yellow_Card : public Field {
private:
    size_t wait_time;

public:
    explicit Yellow_Card(const std::string &field_name, size_t wait_time)
            : Field(std::move(field_name)),
              wait_time(wait_time) {
    }

    void on_landing(std::shared_ptr<Player> player) override {
        player->set_wait_time(wait_time);
    }

    void through_field([[maybe_unused]] std::shared_ptr<Player> player) override {
        return;
    }
};

class Match_Field : public Field {
private:
    zdzislaw_t rate;
    double weight;
    zdzislaw_t cumulation;
public:
    explicit Match_Field(const std::string &field_name, zdzislaw_t rate, double weight)
            : Field(std::move(field_name)),
              rate(rate),
              weight(weight) {
        cumulation = 0;
    }

    void on_landing(std::shared_ptr<Player> player) override {
        player->add_money(cumulation * weight);
        cumulation = 0;
    }

    void through_field(std::shared_ptr<Player> player) override {
        cumulation += std::min(rate, player->get_money());
        player->take_money(rate);
    }

};

class Bookmaker_Field : public Field {
private:
    zdzislaw_t rate;
    size_t lucky_element;

public:
    explicit Bookmaker_Field(const std::string &field_name, zdzislaw_t rate)
            : Field(std::move(field_name)),
              rate(rate) {
        lucky_element = 0;
    }

    void on_landing(std::shared_ptr<Player> player) override {
        if (lucky_element == 0) {
            player->add_money(rate);
        }
        else {
            player->take_money(rate);
        }
        lucky_element++;
        lucky_element %= 3;
    }

    void through_field([[maybe_unused]] std::shared_ptr<Player> player) override {
        return;
    }
};

#endif // FIELD_H