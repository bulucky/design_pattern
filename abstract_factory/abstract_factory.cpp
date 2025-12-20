#include <iostream>

class shipBody {
public:
    virtual ~shipBody() {};
    virtual std::string get_body() = 0;
};

class woodShipBody : public shipBody {
public:
    ~woodShipBody() {}

    std::string get_body() override {
        return "wood shipbody";
    }
};

class ironShipBody : public shipBody {
public:
    ~ironShipBody() {}

    std::string get_body() override {
        return "iron shipbody";
    }
};

class metalShipBody : public shipBody {
public:
    ~metalShipBody() {}

    std::string get_body() override {
        return "metal shipbody";
    }
};

class weapon {
public:
    virtual std::string get_weapon() = 0;
    virtual ~weapon() {};
};

class gunWeapon : public weapon {
public:
    ~gunWeapon() {}

    std::string get_weapon() override {
        return "gun weapon";
    }
};

class cannonWeapon : public weapon {
public:
    ~cannonWeapon() {}

    std::string get_weapon() override {
        return "cannon weapon";
    }
};

class laserWeapon : public weapon {
public:
    ~laserWeapon() {}

    std::string get_weapon() override {
        return "laser weapon";
    }
};

class engine {
public:
    virtual ~engine() {}
    virtual std::string get_engine() = 0;
};

class manualEngine : public engine {
public:
    ~manualEngine() {}

    std::string get_engine() override {
        return "manual engine";
    }
};

class mechanicalEngine : public engine {
public:
    ~mechanicalEngine() {}

    std::string get_engine() override {
        return "mechanical engine";
    }
};

class unclearEngine : public engine {
public:
    ~unclearEngine() {}

    std::string get_engine() override {
        return "unclear engine";
    }
};

class abstractShip {
public:
    virtual ~abstractShip() {};
    virtual void get_info() = 0;
};

class basicShip : public abstractShip {
public:
    basicShip(shipBody* ship_body, weapon* weapon, engine* engine) : ship_body_(ship_body), weapon_(weapon), engine_(engine) {
        std::cout << "basic ship" << "\n";
    }

    ~basicShip() {
        std::cout << "destroy basic ship" << "\n";
        delete ship_body_;
        delete weapon_;
        delete engine_;
    };

    void get_info() override {
        std::cout << ship_body_->get_body() << "\n"
                  << weapon_->get_weapon() << "\n"
                  << engine_->get_engine() << "\n";
    }

private:
    shipBody* ship_body_;
    weapon* weapon_;
    engine* engine_;
};

class standardShip : public abstractShip {
public:
    standardShip(shipBody* ship_body, weapon* weapon, engine* engine) : ship_body_(ship_body), weapon_(weapon), engine_(engine) {
        std::cout << "standard ship" << "\n";
    }

    ~standardShip() {
        std::cout << "destroy standard ship" << "\n";
        delete ship_body_;
        delete weapon_;
        delete engine_;
    };

    void get_info() override {
        std::cout << ship_body_->get_body() << "\n"
                  << weapon_->get_weapon() << "\n"
                  << engine_->get_engine() << "\n";
    }

private:
    shipBody* ship_body_;
    weapon* weapon_;
    engine* engine_;
};

class ultimateShip : public abstractShip {
public:
    ultimateShip(shipBody* ship_body, weapon* weapon, engine* engine) : ship_body_(ship_body), weapon_(weapon), engine_(engine) {
        std::cout << "ultimate ship" << "\n";
    }

    ~ultimateShip() {
        std::cout << "destroy ultimate ship" << "\n";
        delete ship_body_;
        delete weapon_;
        delete engine_;
    };

    void get_info() override {
        std::cout << ship_body_->get_body() << "\n"
                  << weapon_->get_weapon() << "\n"
                  << engine_->get_engine() << "\n";
    }

private:
    shipBody* ship_body_;
    weapon* weapon_;
    engine* engine_;
};

class abstractFactory {
public:
    virtual abstractShip* create_ship() = 0;
    virtual ~abstractFactory() {}
};

class basicFactory : public abstractFactory {
public:
    abstractShip* create_ship() override {
        return new basicShip(new woodShipBody, new gunWeapon, new manualEngine);
    }
};

class standardFactory : public abstractFactory {
public:
    abstractShip* create_ship() override {
        return new standardShip(new ironShipBody, new cannonWeapon, new mechanicalEngine);
    }
};

class ultimateFactory : public abstractFactory {
public:
    abstractShip* create_ship() override {
        return new ultimateShip(new metalShipBody, new laserWeapon, new unclearEngine);
    }
};

int main(int argc, char const* argv[]) {

    abstractFactory* factory = new basicFactory;
    abstractShip* ship = factory->create_ship();
    ship->get_info();

    delete ship;
    delete factory;

    return 0;
}
