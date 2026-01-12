#include <list>
#include <string>
#include <iostream>

class Observer;

class News {
public:
    News() = default;
    virtual ~News() = default;

    void attach(Observer* observer) {
        observers_.push_back(observer);
    }

    void detach(Observer* observer) {
        observers_.remove(observer);
    }

    virtual void notify(std::string msg) = 0;

protected:
    std::list<Observer*> observers_;
};

class Observer {
public:
    Observer(News* pub, std::string name) : pub_(pub), name_(std::move(name)) {
        pub_->attach(this);
    }
    virtual ~Observer() = default;

    void unsubsribe(News* pub);

    virtual void update(std::string msg) = 0;

protected:
    News* pub_ = nullptr;
    std::string name_;
};

class Dargon : public Observer {
public:
    using Observer::Observer;
    ~Dargon() override = default;

    void update(std::string msg) override;
};

class Shanks : public Observer {
public:
    using Observer::Observer;
    ~Shanks() override = default;

    void update(std::string msg) override;
};

class Bartolomeo : public Observer {
public:
    using Observer::Observer;
    ~Bartolomeo() override = default;

    void update(std::string msg) override;
};

class Morgans : public News {
public:
    Morgans() = default;
    ~Morgans() override = default;

    void notify(std::string msg) override {
        for (const auto& observer : observers_) {
            observer->update(msg);
        }
    }
};

class Gossip : public News {
public:
    Gossip() = default;
    ~Gossip() override = default;

    void notify(std::string msg) override {
        for (const auto& observer : observers_) {
            observer->update(msg);
        }
    }
};

void Observer::unsubsribe(News* pub) {
    pub->detach(this);
}

void Dargon::update(std::string msg) {
    std::cout << "Dargon receive: " << msg << "\n";
}

void Shanks::update(std::string msg) {
    std::cout << "Shanks receive: " << msg << "\n";
}

void Bartolomeo::update(std::string msg) {
    std::cout << "Bartolomeo receive: " << msg << "\n";
}


int main(int argc, char const* argv[]) {

    News* morgans = new Morgans();
    News* gossip = new Gossip();

    Dargon* dargon = new Dargon(morgans, "dragon");
    Shanks* shanks = new Shanks(morgans, "shanks");
    Bartolomeo* bartolomeo = new Bartolomeo(gossip, "bartolomeo");

    morgans->notify("Luffy becomes the new Four Emperors");
    gossip->notify("The empress is going to marry Luffy");

    shanks->unsubsribe(morgans);

    morgans->notify("Luffy becomes the new Four Emperors");
    gossip->notify("The empress is going to marry Luffy");

    delete dargon;
    delete shanks;
    delete bartolomeo;
    delete morgans;
    delete gossip;
    return 0;
}
