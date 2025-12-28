#include <map>
#include <string>
#include <vector>
#include <iostream>

class sunnyShip {
public:
    void add_parts(const std::string& name) {
        parts_.push_back(name);
    }

    void show_parts() {
        for (const auto& part : parts_) {
            std::cout << part << "\n";
        }
    }

private:
    std::vector<std::string> parts_;
};

class merryShip {
public:
    void assemble(const std::string& name, const std::string& part) {
        parts_.insert({name, part});
    }

    void show_parts() {
        for (const auto& part : parts_) {
            std::cout << part.first << "" << part.second << "\n";
        }
    }

private:
    std::map<std::string, std::string> parts_;
};

class shipBuilder {
public:
    virtual void reset() = 0;
    virtual void build_body() = 0;
    virtual void build_weapon() = 0;
    virtual void build_engine() = 0;
    virtual void build_interior() = 0;
    virtual ~shipBuilder() {};

private:
};

class sunnyBuilder : public shipBuilder {
public:
    sunnyBuilder() {
        reset();
    }

    ~sunnyBuilder() {
        if (sunny_) delete sunny_;
    }

    void reset() override {
        sunny_ = new sunnyShip;
    }
    void build_body() override {
        sunny_->add_parts("wood body");
    }
    void build_weapon() override {
        sunny_->add_parts("gun weapon");
    }
    void build_engine() override {
        sunny_->add_parts("steam engine");
    }
    void build_interior() override {
        sunny_->add_parts("no interior");
    }

    sunnyShip* get_sunny() {
        sunnyShip* ship = sunny_;
        sunny_ = nullptr;
        return ship;
    }

private:
    sunnyShip* sunny_ = nullptr;
};

class merryBuilder : public shipBuilder {
public:
    merryBuilder() {
        reset();
    }

    ~merryBuilder() {
        if (merry_) delete merry_;
    }

    void reset() override {
        if (!merry_) merry_ = new merryShip;
    }
    void build_body() override {
        merry_->assemble("wood", "iron body");
    }
    void build_weapon() override {
        merry_->assemble("weapon", "cannon weapon");
    }
    void build_engine() override {
        merry_->assemble("engine", "nuclear engine");
    }
    void build_interior() override {
        merry_->assemble("interior", "ultimate interior");
    }

    merryShip* get_merry() {
        merryShip* ship = merry_;
        merry_ = nullptr;
        return ship;
    }

private:
    merryShip* merry_ = nullptr;
};

class director {
public:
    void set_builder(shipBuilder* builder) {
        builder_ = builder;
    }

    void builder_simple_ship() {
        builder_->reset();
        builder_->build_body();
        builder_->build_engine();
    }

    void builder_standard_ship() {
        builder_simple_ship();
        builder_->build_weapon();
    }

    void builder_ultimate_ship() {
        builder_standard_ship();
        builder_->build_interior();
    }

private:
    shipBuilder* builder_;
};


int main(int argc, char const* argv[]) {
    auto* sunny_builder = new sunnyBuilder;
    auto* director = new class director;
    director->set_builder(sunny_builder);
    director->builder_simple_ship();
    sunnyShip* ship = sunny_builder->get_sunny();
    ship->show_parts();
    delete ship;
    director->builder_standard_ship();
    ship = sunny_builder->get_sunny();
    ship->show_parts();

    return 0;
}
