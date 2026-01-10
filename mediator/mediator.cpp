#include <iostream>
#include <unordered_map>

class MediatorOrg;

class Country {
public:
    Country(MediatorOrg* mediator) : mediator_(mediator) {}
    virtual ~Country() = default;

    virtual void declear(std::string msg, std::string country = "") = 0;
    virtual void set_message(std::string msg) = 0;
    virtual std::string get_name() = 0;

protected:
    MediatorOrg* mediator_ = nullptr;
};

class MediatorOrg {
public:
    MediatorOrg() = default;
    virtual ~MediatorOrg() = default;

    void add_member(Country* country) {
        countries_[country->get_name()] = country;
    }

    virtual void declear(const std::string& msg, Country* country, const std::string& name) = 0;

protected:
    std::unordered_map<std::string, Country*> countries_;
};

class WorldGove : public MediatorOrg {
public:
    using MediatorOrg::MediatorOrg;
    ~WorldGove() override = default;

    void declear(const std::string& msg, Country* country, const std::string& name) override {
        if (countries_.find(name) != countries_.end()) {
            std::string str = "from " + country->get_name() + " to " + name + ": " += msg;
            countries_[name]->set_message(str);
        }
    }
};

class RevolutionaryArmy : public MediatorOrg {
public:
    using MediatorOrg::MediatorOrg;
    ~RevolutionaryArmy() override = default;

    void declear(const std::string& msg, Country* country, const std::string& name) override {
        for (const auto& country_ : countries_) {
            std::string str = "from " + country->get_name() + " to " + name + ": " += msg;
            country_.second->set_message(str);
        }
    }
};

class Alabasta : public Country {
public:
    using Country::Country;
    ~Alabasta() override = default;

    void declear(std::string msg, std::string country = "") override {
        mediator_->declear(msg, this, country);
    }

    void set_message(std::string msg) override {
        std::cout << "Alabasta receive " << "\n"
                  << msg << "\n";
    }

    std::string get_name() override {
        return "Alabasta";
    }
};

class Dressrosa : public Country {
public:
    using Country::Country;
    ~Dressrosa() override = default;

    void declear(std::string msg, std::string country = "") override {
        mediator_->declear(msg, this, country);
    }

    void set_message(std::string msg) override {
        std::cout << "Dressrosa receive " << "\n"
                  << msg << "\n";
    }

    std::string get_name() override {
        return "Dressrosa";
    }
};

class Kamabaka : public Country {
public:
    using Country::Country;
    ~Kamabaka() override = default;

    void declear(std::string msg, std::string country = "") override {
        mediator_->declear(msg, this, country);
    }

    void set_message(std::string msg) override {
        std::cout << "Kamabaka receive " << "\n"
                  << msg << "\n";
    }

    std::string get_name() override {
        return "Kamabaka";
    }
};

class Lulusia : public Country {
public:
    using Country::Country;
    ~Lulusia() override = default;

    void declear(std::string msg, std::string country = "") override {
        mediator_->declear(msg, this, country);
    }

    void set_message(std::string msg) override {
        std::cout << "Lulusia receive " << "\n"
                  << msg << "\n";
    }

    std::string get_name() override {
        return "Lulusia";
    }
};

int main(int argc, char const* argv[]) {
    MediatorOrg* world_gove = new WorldGove();
    MediatorOrg* revolutionary_army = new RevolutionaryArmy();

    Alabasta* alabasta = new Alabasta(world_gove);
    Dressrosa* dressrosa = new Dressrosa(world_gove);
    world_gove->add_member(alabasta);
    world_gove->add_member(dressrosa);

    Kamabaka* kamabaka = new Kamabaka(revolutionary_army);
    Lulusia* lulusia = new Lulusia(revolutionary_army);
    revolutionary_army->add_member(kamabaka);
    revolutionary_army->add_member(lulusia);

    alabasta->declear("dressrosa, you are bad", dressrosa->get_name());
    dressrosa->declear("alabasta, you can fight with me", alabasta->get_name());

    kamabaka->declear("i will help everyone");

    delete lulusia;
    delete kamabaka;
    delete dressrosa;
    delete alabasta;
    delete revolutionary_army;
    delete world_gove;

    return 0;
}