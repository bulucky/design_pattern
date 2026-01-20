#include <list>
#include <vector>
#include <string>
#include <iostream>

class AbstractMember;

class AbstractAction {
public:
    AbstractAction() = default;
    virtual ~AbstractAction() = default;

    virtual void male_doing(AbstractMember* male) = 0;
    virtual void female_doing(AbstractMember* female) = 0;
};

// declaration
class Angry : public AbstractAction {
public:
    void male_doing(AbstractMember* male) override;
    void female_doing(AbstractMember* female) override;

    void warning();
    void fight();
};

class Horor : public AbstractAction {
public:
    void male_doing(AbstractMember* male) override;
    void female_doing(AbstractMember* female) override;

    void thinking();
    void help();
};

class AbstractMember {
public:
    AbstractMember(std::string name) : name(std::move(name)) {}
    virtual ~AbstractMember() = default;

    inline std::string get_name() { return name; }

    virtual void accept(AbstractAction* action) = 0;

protected:
    std::string name;
};

class MaleMember : public AbstractMember {
public:
    using AbstractMember::AbstractMember;
    ~MaleMember() override = default;

    void accept(AbstractAction* action) override {
        action->male_doing(this);
    }
};

class FemaleMember : public AbstractMember {
public:
    using AbstractMember::AbstractMember;
    ~FemaleMember() override = default;

    void accept(AbstractAction* action) override {
        action->female_doing(this);
    }
};

// defination
void Angry::warning() {
    std::cout << "warning" << "\n";
}

void Angry::fight() {
    std::cout << "fight fight fight" << "\n";
}

void Angry::male_doing(AbstractMember* male) {
    fight();
}

void Angry::female_doing(AbstractMember* female) {
    warning();
}

void Horor::thinking() {
    std::cout << "thinking" << "\n";
}

void Horor::help() {
    std::cout << "help help help" << "\n";
}

void Horor::male_doing(AbstractMember* male) {
    thinking();
}

void Horor::female_doing(AbstractMember* female) {
    help();
}

class StrawHotTeam {
public:
    StrawHotTeam() {
        actions_.push_back(new Angry());
        actions_.push_back(new Horor());
    };

    ~StrawHotTeam() {
        for (const auto& member : members_) {
            delete member;
        }
        for (const auto& action : actions_) {
            delete action;
        }
    }

    void add_member(AbstractMember* member) {
        members_.push_back(member);
    }

    void delete_member(AbstractMember* member) {
        members_.remove(member);
    }

    void print_info() {
        srand(time(nullptr));
        for (const auto& member : members_) {
            std::cout << "i am " << member->get_name() << "\n";
            int rand_index = rand() % 2;
            member->accept(actions_[rand_index]);
        }
    }

private:
    std::vector<AbstractAction*> actions_;
    std::list<AbstractMember*> members_;
};

int main(int argc, char const* argv[]) {
    StrawHotTeam* strawhotteam = new StrawHotTeam();
    std::vector<std::string> males = {"luffy", "Sauron", "Sanji", "Franky"};
    std::vector<std::string> females = {"Nami", "Robin"};
    for (const auto& male : males) {
        strawhotteam->add_member(new MaleMember(male));
    }

    for (const auto& female : females) {
        strawhotteam->add_member(new FemaleMember(female));
    }

    strawhotteam->print_info();

    delete strawhotteam;

    return 0;
}