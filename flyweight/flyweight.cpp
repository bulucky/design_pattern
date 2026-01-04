#include <vector>
#include <utility>
#include <iostream>
#include <unordered_map>

class flyweightBody {
public:
    flyweightBody(std::string sprite) : sprite_(std::move(sprite)) {}

    virtual ~flyweightBody() = default;

    virtual void move(int x, int y, int speed) = 0;

    virtual void draw(int x, int y) = 0;

protected:
    std::string sprite_;
    std::string color_;
};

class sharedBombBody : public flyweightBody {
public:
    using flyweightBody::flyweightBody;

    void move(int x, int y, int speed) override {
        std::cout << "current status:" << x << "," << y << "," << speed << "\n";
    }

    void draw(int x, int y) override {
        std::cout << "reset the bomb position:" << x << y << "\n";
    }
};

class uniqueBombBody : public flyweightBody {
public:
    using flyweightBody::flyweightBody;

    void move(int x, int y, int speed) override {
        std::cout << "current status:" << x << "," << y << "," << speed << "\n";
    }

    void draw(int x, int y) override {
        std::cout << "reset the bomb position:" << x << "," << y << "\n";
    }
};

class launchBomb {
public:
    launchBomb(flyweightBody* bomb) : bomb_(bomb) {}

    int get_x() { return x_; }

    int get_y() { return y_; }

    int get_speed() { return speed_; }

    void set_speed(int speed) { speed_ = speed; }

    void move(int x, int y) {
        x_ = x;
        y_ = y;

        bomb_->move(x_, y_, speed_);
        draw();
    }

    void draw() {
        bomb_->draw(x_, y_);
    }

private:
    int x_ = 0;
    int y_ = 0;
    int speed_ = 10;
    flyweightBody* bomb_ = nullptr;
};

class bombBodyFactory {
public:
    bombBodyFactory() = default;

    ~bombBodyFactory() {
        for (const auto& bomb : bombs_) {
            delete bomb.second;
        }
    }

    sharedBombBody* get_shared_bomb_body(const std::string& name) {
        sharedBombBody* body = nullptr;
        for (const auto& bomb : bombs_) {
            if (bomb.first == name) {
                std::cout << "existing entity, multiplexed" << "\n";
                body = bomb.second;
                break;
            }
        }
        if (body == nullptr) { body = new sharedBombBody(name); }
        std::cout << "not existing entity, created" << "\n";

        bombs_.insert({name, body});

        return body;
    }

private:
    std::unordered_map<std::string, sharedBombBody*> bombs_;
};

int main(int argc, char const* argv[]) {
    std::vector<std::string> bombs_vec = {"AAAI", "AAAI", "AAAII", "AAAII", "AAAIII", "AAAI"};

    bombBodyFactory* bomb_factory = new bombBodyFactory;
    for (const auto& bomb_name : bombs_vec) {
        sharedBombBody* bomb = bomb_factory->get_shared_bomb_body(bomb_name);
        launchBomb* l_bomb = new launchBomb(bomb);
        int x = rand() % 10;
        int y = rand() % 5;
        l_bomb->move(x, y);
        delete l_bomb;
    }
    delete bomb_factory;

    uniqueBombBody* easter_eggs = new uniqueBombBody("big easter eggs");
    launchBomb* l_bomb = new launchBomb(easter_eggs);
    l_bomb->set_speed(99);
    l_bomb->move(20, 30);

    delete l_bomb;
    delete easter_eggs;

    return 0;
}
