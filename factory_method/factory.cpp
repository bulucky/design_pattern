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

// 抽象工厂提供接口
class abstractFactory {
public:
    virtual abstractSimle* create_simle() = 0;
    virtual ~abstractFactory() {};
};

class sheepFactory : public abstractFactory {
public:
    abstractSimle* create_simle() override {
        return new sheepSimle;
    }
    ~sheepFactory() {
        std::cout << "sheep Factory destory" << "\n";
    }
};

class lionFactory : public abstractFactory {
public:
    abstractSimle* create_simle() override {
        return new lionSimle;
    }
    ~lionFactory() {
        std::cout << "lion Factory destory" << "\n";
    }
};

class batFactory : public abstractFactory {
public:
    abstractSimle* create_simle() override {
        return new batSimle;
    }
    ~batFactory() {
        std::cout << "bat Factory destory" << "\n";
    }
};


int main(int argc, char const* argv[]) {
    std::cout << "simple factory" << "\n";

    abstractFactory* factory = new sheepFactory;
    abstractSimle* simle = factory->create_simle();
    simle->transformer();
    simle->ability();

    delete simle;
    delete factory;

    return 0;
}