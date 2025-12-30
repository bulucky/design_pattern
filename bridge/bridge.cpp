#include <iostream>
#include <unordered_map>
#include <utility>

struct person {
    person(const std::string& name, const std::string& ability) : name(name), ability(ability) {};
    ~person() {};
    std::string name;
    std::string ability;
};

class abstractTeam {
public:
    abstractTeam(std::string name) : name_(std::move(name)) {};

    ~abstractTeam() {
        for (const auto& member : team_members_) {
            std::cout << "destory" << member.first << "\n";
            delete member.second;
        }
    };

    void add_member(person* member) {
        team_members_[member->name] = member;
    }

    std::string get_name() {
        return name_;
    }

    void print_team_info() {
        std::cout << name_ << "\n";
        for (const auto& member : team_members_) {
            std::cout << member.second->name << "\n";
            std::cout << member.second->ability << "\n";
        }
    }

    virtual void execute_task() = 0;


protected:
    std::string name_;
    std::unordered_map<std::string, person*> team_members_;
};

class strawHotTeam : public abstractTeam {
    using abstractTeam::abstractTeam;

    void execute_task() override {
        std::cout << "one piece" << "\n";
    }
};

class smokerTeam : public abstractTeam {
    using abstractTeam::abstractTeam;

    void execute_task() override {
        std::cout << "catch pirates" << "\n";
    }
};

class abstractShip {
public:
    abstractShip(abstractTeam* team) : team_(team) {};

    void print_ship_info() {
        team_->print_team_info();
        team_->execute_task();
    }

    virtual std::string get_name() = 0;
    virtual void feature() = 0;

protected:
    abstractTeam* team_;
};

class merryShip : public abstractShip {
    using abstractShip::abstractShip;

    std::string get_name() override {
        return "merry";
    }

    void feature() override {
        std::cout << "merry mei mei mei" << "\n";
    }
};

class navyShip : public abstractShip {
    using abstractShip::abstractShip;

    std::string get_name() override {
        return "navy";
    }

    void feature() override {
        std::cout << "smoker qiu qiu qiu" << "\n";
    }
};

int main(int argc, char const* argv[]) {

    abstractTeam* team = new strawHotTeam("strawHot");
    person* luffy = new person("luffy", "rubber gun");
    person* sauron = new person("sauron", "Three knife flow");

    team->add_member(luffy);
    team->add_member(sauron);

    abstractShip* merry = new merryShip(team);
    merry->print_ship_info();

    return 0;
}