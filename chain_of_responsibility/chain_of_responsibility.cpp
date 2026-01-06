#include <iostream>

enum class requestType : char { qingjia,
                                zhangxin,
                                chizi };

class abstractManager {
public:
    abstractManager() = default;
    virtual ~abstractManager() = default;

    void set_next(abstractManager* next) {}
    virtual void handle_request(requestType type) = 0;

protected:
    abstractManager* next_ = nullptr;
};

class directSupervisor : public abstractManager {
public:
    void set_next(abstractManager* next) {
        next_ = next;
    }

    void handle_request(requestType type) override {
        switch (type) {
            case requestType::qingjia:
                std::cout << "qingjia: slepp sleep" << "\n";
                break;
            case requestType::zhangxin:
                std::cout << "zhangxin: i can not handle >>>>>> ";
                next_->handle_request(type);
                break;
            case requestType::chizi:
                std::cout << "chizi: i can not handle >>>>>> ";
                next_->handle_request(type);
                break;
        }
    }
};

class CEO : public abstractManager {
public:
    void set_next(abstractManager* next) {
        next_ = next;
    }

    void handle_request(requestType type) override {
        switch (type) {
            case requestType::qingjia:
                std::cout << "qingjia: slepp sleep" << "\n";
                break;
            case requestType::zhangxin:
                std::cout << "zhangxin: up up" << "\n";
                break;
            case requestType::chizi:
                std::cout << "chizi: i also can not handle >>>>>> ";
                next_->handle_request(type);
                break;
        }
    }
};

class BOSS : public abstractManager {
public:
    void set_next(abstractManager* next) {
        next_ = next;
    }

    void handle_request(requestType type) override {
        switch (type) {
            case requestType::qingjia:
                std::cout << "qingjia: slepp sleep" << "\n";
                break;
            case requestType::zhangxin:
                std::cout << "zhangxin: up up" << "\n";
                break;
            case requestType::chizi:
                std::cout << "chizi: gun gun" << "\n";
                break;
        }
    }
};

class daCongMing {
public:
    daCongMing() = default;
    ~daCongMing() = default;

    void request(requestType type, abstractManager* manager) {
        manager->handle_request(type);
    }
};

int main(int argc, char const* argv[]) {

    directSupervisor* direct = new directSupervisor;
    CEO* ceo = new CEO;
    BOSS* boss = new BOSS;
    direct->set_next(ceo);
    ceo->set_next(boss);

    daCongMing* boy = new daCongMing;
    boy->request(requestType::qingjia, direct);
    boy->request(requestType::zhangxin, direct);
    boy->request(requestType::chizi, direct);

    boy->request(requestType::qingjia, ceo);
    boy->request(requestType::zhangxin, ceo);
    boy->request(requestType::chizi, ceo);

    boy->request(requestType::qingjia, boss);
    boy->request(requestType::zhangxin, boss);
    boy->request(requestType::chizi, boss);
    if(1) std::cout << "" << "\n";
    else std::cout << "h" << "\n";
    delete boy;
    delete boss;
    delete ceo;
    delete direct;

    return 0;
}
