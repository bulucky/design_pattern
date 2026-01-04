#include <iostream>

class cokeSystem {
public:
    void immit_coke() {
        std::cout << "fill coke" << "\n";
    }
};

class energeSystem {
public:
    void energe_convert() {
        std::cout << "coke convert energe" << "\n";
    }
};

class aimLockSystem {
public:
    void aim_lock() {
        std::cout << "aim and lock" << "\n";
    }
};

class windCannon {
public:
    void wind_cannon_fire() {
        std::cout << "wind cannon fire" << "\n";
    }
};

class cannon {
public:
    void fire() {
        std::cout << "fire" << "\n";
    }
};

class lionCannonSystem {
public:
    lionCannonSystem() {
        coke_ = new cokeSystem;
        energe_ = new energeSystem;
        aim_lock_ = new aimLockSystem;
        wind_cannon_ = new windCannon;
        cannon_ = new cannon;
    }

    ~lionCannonSystem() {
        delete cannon_;
        delete wind_cannon_;
        delete aim_lock_;
        delete energe_;
        delete coke_;
    }

    void aim_and_lock() {
        coke_->immit_coke();
        energe_->energe_convert();
        aim_lock_->aim_lock();
    }

    void fire() {
        wind_cannon_->wind_cannon_fire();
        cannon_->fire();
    }

private:
    cokeSystem* coke_ = nullptr;
    energeSystem* energe_ = nullptr;
    aimLockSystem* aim_lock_ = nullptr;
    windCannon* wind_cannon_ = nullptr;
    cannon* cannon_ = nullptr;
};

int main(int argc, char const* argv[]) {
    lionCannonSystem* lion_cannon = new lionCannonSystem;
    lion_cannon->aim_and_lock();
    lion_cannon->fire();

    delete lion_cannon;

    return 0;
}