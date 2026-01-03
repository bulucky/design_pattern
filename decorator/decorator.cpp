#include <utility>
#include <iostream>

class solider {
public:
    solider() = default;
    solider(std::string name) : name_(std::move(name)) {}

    virtual ~solider() = default;

    std::string get_name() { return name_; }

    virtual void fighting_style() = 0;

protected:
    std::string name_;
};

class teach : public solider {
public:
    using solider::solider;

    ~teach() override = default;

    void fighting_style() override {
        std::cout << "superb physical skills" << "\n";
    }
};

class devilFruit : public solider {
public:
    ~devilFruit() override = default;

    void enhancement(solider* solider) {
        solider_ = solider;
        name_ = solider_->get_name();
    };

protected:
    solider* solider_ = nullptr;
};

class darkFruit : public devilFruit {
public:
    void fighting_style() override {
        std::cout << "absorb skills" << "\n";
        warning();
    }

private:
    void warning() {
        std::cout << "Absorb damage by yourself" << "\n";
    }
};

class shockFruit : public devilFruit {
public:
    void fighting_style() override {
        std::cout << "shock skills" << "\n";
    }
};

class pieFruit : public devilFruit {
public:
    void fighting_style() override {
        std::cout << "pie armor, improve defense" << "\n";
        ability();
    }

private:
    void ability() {
        std::cout << "restore vitality" << "\n";
    }
};


int main(int argc, char const* argv[]) {
    solider* teach = new class teach("teach");
    darkFruit* dark = new darkFruit();
    shockFruit* shock = new shockFruit();
    pieFruit* pie = new pieFruit();

    teach->fighting_style();
    dark->enhancement(teach);
    dark->fighting_style();
    shock->enhancement(shock);
    shock->fighting_style();
    pie->enhancement(shock);
    pie->fighting_style();

    delete teach;
    delete pie;
    delete shock;
    delete dark;

    return 0;
}