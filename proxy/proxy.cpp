#include <iostream>

class communication {
public:
    virtual ~communication() = default;

    virtual void communicate() = 0;
};

class speaker : public communication {
public:
    ~speaker() override = default;

    void communicate() override {
        std::cout << "start talking en en" << "\n";
    }
};

class dendenMuShi : public communication {
public:
    dendenMuShi() {
        speaker_ = new speaker;
        is_start_ = true;
    }

    ~dendenMuShi() {
        if (speaker_) {
            delete speaker_;
        }
    }

    void communicate() override {
        if (is_start_) {
            std::cout << "The agent imitates the speech" << "\n";
            speaker_->communicate();
        }
    }

private:
    speaker* speaker_ = nullptr;
    bool is_start_ = false;
};

int main(int argc, char const* argv[]) {
    dendenMuShi* agent = new dendenMuShi;
    agent->communicate();

    delete agent;
    

    return 0;
}