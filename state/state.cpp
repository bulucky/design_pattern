#include <vector>
#include <iostream>

class Sanji;

class AbstractState {
public:
    virtual ~AbstractState() = default;

    virtual void working(Sanji* sanji) = 0;
};

class ForenNoonState : public AbstractState {
    void working(Sanji* sanji) override;
};

class NoonState : public AbstractState {
    void working(Sanji* sanji) override;
};

class AfterNoonState : public AbstractState {
    void working(Sanji* sanji) override;
};

class EveningState : public AbstractState {
    void working(Sanji* sanji) override;
};

class Sanji {
public:
    Sanji() {
        state_ = new ForenNoonState;
    }
    ~Sanji() {
        if (state_ != nullptr) {
            delete state_;
            state_ = nullptr;
        }
    };

    void working() {
        state_->working(this);
    }

    void set_clock(int time) {
        time_ = time;
    }

    int get_clock() {
        return time_;
    }

    void set_state(AbstractState* state) {
        if (state_ != nullptr) {
            delete state_;
            state_ = nullptr;
        }
        state_ = state;
    }

private:
    int time_ = 0;
    AbstractState* state_ = nullptr;
};

void ForenNoonState::working(Sanji* sanji) {
    int time = sanji->get_clock();
    if (time <= 8) {
        std::cout << "now time: " << time << " prepare breakfast" << "\n";
    } else if (time > 8 && time <= 12) {
        std::cout << "now time: " << time << " prepare lunch ingredients" << "\n";
    } else {
        sanji->set_state(new NoonState);
        sanji->working();
    }
};

void NoonState::working(Sanji* sanji) {
    int time = sanji->get_clock();
    if (time <= 13) {
        std::cout << "now time: " << time << " prepare lunch" << "\n";
    } else if (time > 13 && time <= 15) {
        std::cout << "now time: " << time << " prepare afternoon tea" << "\n";
    } else {
        sanji->set_state(new AfterNoonState);
        sanji->working();
    }
};

void AfterNoonState::working(Sanji* sanji) {
    int time = sanji->get_clock();
    if (time <= 18) {
        std::cout << "now time: " << time << " prepare dinner ingredients" << "\n";
    } else if (time > 18 && time <= 19) {
        std::cout << "now time: " << time << " prepare dinner" << "\n";
    } else {
        sanji->set_state(new EveningState);
        sanji->working();
    }
};

void EveningState::working(Sanji* sanji) {
    int time = sanji->get_clock();
    if (time <= 22) {
        std::cout << "now time: " << time << " prepare to sleep" << "\n";
    } else if (time > 22) {
        std::cout << "now time: " << time << " sleep" << "\n";
    }
};

int main(int argc, char const* argv[]) {
    Sanji* sanji = new Sanji;
    std::vector<int> times = {7, 10, 13, 14, 16, 19, 21, 23};

    for (const auto& time : times) {
        sanji->set_clock(time);
        sanji->working();
    }

    delete sanji;

    return 0;
}
