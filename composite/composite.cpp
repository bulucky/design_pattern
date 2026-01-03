#include <list>
#include <string>
#include <utility>
#include <iostream>

class abstractTeam {
public:
    abstractTeam(std::string name) : name_(std::move(name)) {}

    virtual ~abstractTeam() {}

    void set_parent(abstractTeam* parent) { parent_ = parent; }

    abstractTeam* get_parent() { return parent_; }

    std::string get_name() { return name_; }

    virtual bool has_child() { return false; }

    virtual void add_child(abstractTeam* child) {}

    virtual void remove_child(abstractTeam* child) {}

    virtual void fight() = 0;

    virtual void display() = 0;

protected:
    std::string name_ = "";
    abstractTeam* parent_ = nullptr;
};

class managerTeam : public abstractTeam {
public:
    using abstractTeam::abstractTeam;

    ~managerTeam() {
        std::cout << name_ << "bye bye" << "\n";
    }

    bool has_child() override {
        return true;
    }

    void add_child(abstractTeam* child) override {
        child->set_parent(this);
        childs_.push_back(child);
    }

    void remove_child(abstractTeam* child) override {
        childs_.remove(child);
    }

    void fight() override {
        std::cout << name_ << "fight black beard" << "\n";
    }

    void display() override {
        std::cout << "i am " << name_ << "    " << "parent is " << parent_->get_name() << "\n";
        for (const auto& child : childs_) {
            std::cout << "child is " << child->get_name() << "\n";
        }
    }

    std::list<abstractTeam*> childs_;
};

class leafTeam : public abstractTeam {
public:
    using abstractTeam::abstractTeam;

    ~leafTeam() {
        std::cout << name_ << "bye bye" << "\n";
    }

    void fight() override {
        std::cout << name_ << "fight black beard" << "\n";
    }

    void display() override {
        std::cout << "i am " << name_ << "parent is " << parent_->get_name() << "\n";
    }
};

void game_over(abstractTeam* root) {
    if (!root) {
        return;
    }

    if (root && root->has_child()) {
        managerTeam* team = dynamic_cast<managerTeam*>(root);
        for (const auto& child : team->childs_) {
            game_over(dynamic_cast<abstractTeam*>(child));
        }
    }

    delete root;
}

int main(int argc, char const* argv[]) {
    managerTeam* root = new managerTeam("straw hot");

    std::list<std::string> childs_name = {"AAA", "BBB", "CCC", "DDD", "EEE"};

    for (const auto& child_name : childs_name) {
        managerTeam* middle = new managerTeam(child_name);
        root->add_child(middle);
        for (int i = 0; i < 3; ++i) {
            std::string leaf_name = middle->get_name() + std::to_string(i + 1) + "小队";
            leafTeam* leaf = new leafTeam(leaf_name);
            middle->add_child(leaf);
            leaf->fight();
            leaf->display();
        }
        middle->fight();
        middle->display();
    }

    game_over(root);

    return 0;
}