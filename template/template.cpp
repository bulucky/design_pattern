#include <string>
#include <iostream>

class AbstractRobot {
public:
    AbstractRobot() = default;
    virtual ~AbstractRobot() = default;

    virtual void weapon() = 0;
    virtual void apparence() = 0;
    virtual void fight_ability() = 0;
    virtual std::string get_name() = 0;

    virtual bool self_healing() {
        return false;
    }

    virtual bool can_flying() {
        return false;
    }

    virtual bool is_auto() {
        return true;
    }

    virtual void get_property() {
        std::cout << "name: " << get_name() << "\n";
        weapon();
        apparence();
        fight_ability();
        if (self_healing()) {
            std::cout << "can self healing" << "\n";
        }
        if (can_flying()) {
            std::cout << "can flying" << "\n";
        }
        if (is_auto()) {
            std::cout << "can auto runing" << "\n";
        }
    }
};

class Pacifist : public AbstractRobot {
public:
    Pacifist() = default;
    ~Pacifist() override = default;

    void weapon() override {
        std::cout << "laser cannon" << "\n";
    }

    void apparence() override {
        std::cout << "same as big bear" << "\n";
    }

    void fight_ability() override {
        std::cout << "resistant to beating, launch laser cannons" << "\n";
    }

    std::string get_name() override {
        return "pacifist";
    }
};

class Seraph : public AbstractRobot {
public:
    Seraph() = default;
    ~Seraph() = default;

    void weapon() override {
        std::cout << "a weapon similar to Qiwuhai" << "\n";
    }

    void apparence() override {
        std::cout << "similar appearance to Qiwuhai when he was a child" << "\n";
    }

    void fight_ability() override {
        std::cout << "Use abilities and knives" << "\n";
    }

    std::string get_name() override {
        return "Seraph";
    }

    bool self_healing() override {
        return true;
    }

    bool can_flying() override {
        return true;
    }
};

int main(int argc, char const* argv[]) {
    AbstractRobot* robot = new Pacifist;
    robot->get_property();
    delete robot;

    std::cout << "----------------" << "\n";
    robot = new Seraph;
    robot->get_property();
    delete robot;

    return 0;
}
