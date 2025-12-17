#include <iostream>

class abstractSimle {
public:
    virtual ~abstractSimle() {};

    virtual void transformer() = 0;
    virtual void ability() = 0;
};

class sheepSimle : public abstractSimle {
public:
    void transformer() override {
        std::cout << "sheep......" << "\n";
    }

    void ability() override {
        std::cout << "mei mei mei......" << "\n";
    }
};

class lionSimle : public abstractSimle {
public:
    void transformer() override {
        std::cout << "lion......" << "\n";
    }

    void ability() override {
        std::cout << "wa wa wa......" << "\n";
    }
};

class batSimle : public abstractSimle {
public:
    void transformer() override {
        std::cout << "bat......" << "\n";
    }

    void ability() override {
        std::cout << "ji ji ji......" << "\n";
    }
};

enum class simleType : char { sheep,
                              lion,
                              bat };

class simpleFactory {
public:
    abstractSimle* create_simle(simleType type) {
        abstractSimle* new_simle = nullptr;
        switch (type) {
            case simleType::sheep:
                new_simle = new sheepSimle;
                break;
            case simleType::lion:
                new_simle = new lionSimle;
                break;
            case simleType::bat:
                new_simle = new batSimle;
                break;
            default:
                break;
        }

        return new_simle;
    }
};

int main(int argc, char const* argv[]) {
    std::cout << "simple factory" << "\n";

    simpleFactory simle_factory;
    abstractSimle* simle = simle_factory.create_simle(simleType::sheep);
    simle->transformer();
    simle->ability();

    delete simle;

    return 0;
}