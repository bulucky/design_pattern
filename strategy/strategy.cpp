#include <iostream>

class AbstractStrategy {
public:
    AbstractStrategy() = default;
    virtual ~AbstractStrategy() = default;

    virtual void fight() = 0;
};

class YiDang : public AbstractStrategy {
    using AbstractStrategy::AbstractStrategy;
    ~YiDang() override = default;

    void fight() override {
        std::cout << "YiDang fight" << "\n";
    }
};

class ErDang : public AbstractStrategy {
    using AbstractStrategy::AbstractStrategy;
    ~ErDang() override = default;

    void fight() override {
        std::cout << "ErDang fight" << "\n";
    }
};

class SanDang : public AbstractStrategy {
    using AbstractStrategy::AbstractStrategy;
    ~SanDang() override = default;

    void fight() override {
        std::cout << "SanDang fight" << "\n";
    }
};

class SiDang : public AbstractStrategy {
    using AbstractStrategy::AbstractStrategy;
    ~SiDang() override = default;

    void fight() override {
        std::cout << "SiDang fight" << "\n";
    }
};

class WuDang : public AbstractStrategy {
    using AbstractStrategy::AbstractStrategy;
    ~WuDang() override = default;

    void fight() override {
        std::cout << "WuDang fight" << "\n";
    }
};

enum class Opponent : char { EASY,
                             NORMAL,
                             HARD,
                             PROFESSIONAL,
                             EXPERT };

class Luffy {
public:
    Luffy() = default;
    ~Luffy() {
        if (strategy_ != nullptr) {
            delete strategy_;
        }
    }

    void fight(Opponent opponent) {
        if (strategy_ != nullptr) {
            delete strategy_;
            strategy_ = nullptr;
        }
        switch (opponent) {
            case Opponent::EASY:
                strategy_ = new YiDang();
                break;
            case Opponent::NORMAL:
                strategy_ = new ErDang();
                break;
            case Opponent::HARD:
                strategy_ = new SanDang();
                break;
            case Opponent::PROFESSIONAL:
                strategy_ = new SiDang();
                break;
            case Opponent::EXPERT:
                strategy_ = new WuDang();
                break;
        }

        strategy_->fight();
    }

private:
    AbstractStrategy* strategy_ = nullptr;
};

int main(int argc, char const* argv[]) {
    Luffy* luffy = new Luffy();
    std::cout << "Soldier" << "\n";
    luffy->fight(Opponent::EASY);
    std::cout << "Captain" << "\n";
    luffy->fight(Opponent::NORMAL);
    std::cout << "Lu Qi" << "\n";
    luffy->fight(Opponent::HARD);
    std::cout << "Ming Ge" << "\n";
    luffy->fight(Opponent::PROFESSIONAL);
    std::cout << "Kaido" << "\n";
    luffy->fight(Opponent::EXPERT);

    delete luffy;

    return 0;
}