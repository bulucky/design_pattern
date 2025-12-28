#include <iostream>

class germaSoldier {
public:
    virtual germaSoldier* get_clone() = 0;
    virtual void print_info() = 0;
    virtual ~germaSoldier() {};
};

class germaSoldier66 : public germaSoldier {
    germaSoldier* get_clone() override {
        return new germaSoldier66(*this);
    }

    void print_info() override {
        std::cout << "i am germaSoldier66" << "\n";
    }
};

class germaSoldier67 : public germaSoldier {
    germaSoldier* get_clone() override {
        return new germaSoldier67(*this);
    }

    void print_info() override {
        std::cout << "i am germaSoldier67" << "\n";
    }
};

int main(int argc, char const* argv[]) {

    germaSoldier* proto_soldier = new germaSoldier66;
    germaSoldier* clone_soldier = proto_soldier->get_clone();
    clone_soldier->print_info();

    delete clone_soldier;
    delete proto_soldier;

    proto_soldier = new germaSoldier67;
    clone_soldier = proto_soldier->get_clone();
    clone_soldier->print_info();

    delete clone_soldier;
    delete proto_soldier;

    return 0;
}