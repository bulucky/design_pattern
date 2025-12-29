#include <iostream>

class abstractForeigner {
public:
    virtual std::string apologize() = 0;
    virtual void get_result(std::string msg) = 0;
    virtual ~abstractForeigner() {};
};

class americanForeigner : public abstractForeigner {
public:
    std::string apologize() override {
        return "american: i am bad";
    }

    void get_result(std::string msg) override {
        std::cout << msg << "\n";
    }
};

class frenchForeigner : public abstractForeigner {
public:
    std::string apologize() override {
        return "french: i am rotten";
    }

    void get_result(std::string msg) override {
        std::cout << msg << "\n";
    }
};

class panda {
public:
    void receive_msg(std::string& msg) {
        std::cout << "recive msg: " << msg << "\n";
    };
    std::string reply_msg() {
        return "yes! you are not a good boy";
    }
};

class abstractChopper {
public:
    abstractChopper(abstractForeigner* foreigner) : foreigner_(foreigner) {};
    virtual void translate_panda() = 0;
    virtual void translate_human() = 0;
    virtual ~abstractChopper() {};

protected:
    panda panda_;
    abstractForeigner* foreigner_;
};

class americanChopper : public abstractChopper {
public:
    using abstractChopper::abstractChopper;
    void translate_panda() override {
        std::string human_msg = foreigner_->apologize();
        panda_.receive_msg(human_msg);
    }

    void translate_human() override {
        std::string panda_msg = panda_.reply_msg();
        foreigner_->get_result(panda_msg);
    }
};

class frenchChopper : public abstractChopper {
public:
    using abstractChopper::abstractChopper;
    void translate_panda() override {
        std::string human_msg = foreigner_->apologize();
        panda_.receive_msg(human_msg);
    }

    void translate_human() override {
        std::string panda_msg = panda_.reply_msg();
        foreigner_->get_result(panda_msg);
    }
};

int main(int argc, char const* argv[]) {
    abstractForeigner* foreigner = new americanForeigner;
    abstractChopper* chopper = new americanChopper(foreigner);
    chopper->translate_panda();
    chopper->translate_human();

    delete foreigner;
    delete chopper;

    std::cout << "------------------------------------" << "\n";
    foreigner = new frenchForeigner;
    chopper = new frenchChopper(foreigner);
    chopper->translate_panda();
    chopper->translate_human();

    return 0;
}