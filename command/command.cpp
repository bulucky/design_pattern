#include <map>
#include <list>
#include <string>
#include <iostream>

class cookerZeef {
public:
    cookerZeef() = default;
    ~cookerZeef() = default;

    void make_GBJD() {
        std::cout << "make GBJD" << "\n";
    }

    void make_DSX() {
        std::cout << "make DSX" << "\n";
    }

    void make_YXRS() {
        std::cout << "make YXRS" << "\n";
    }

    void make_HSPG() {
        std::cout << "make HSPG" << "\n";
    }
};

class abstractCommand {
public:
    abstractCommand(cookerZeef* cooker) : cooker_(cooker) {}
    virtual ~abstractCommand() = default;

    virtual void execute() = 0;
    virtual std::string get_name() = 0;

protected:
    cookerZeef* cooker_ = nullptr;
};

class GBJD : public abstractCommand {
public:
    using abstractCommand::abstractCommand;

    void execute() override {
        cooker_->make_GBJD();
    }

    std::string get_name() override {
        return "GBJD";
    }
};

class DSX : public abstractCommand {
public:
    using abstractCommand::abstractCommand;

    void execute() override {
        cooker_->make_DSX();
    }

    std::string get_name() override {
        return "DSX";
    }
};

class YXRS : public abstractCommand {
public:
    using abstractCommand::abstractCommand;

    void execute() override {
        cooker_->make_YXRS();
    }

    std::string get_name() override {
        return "YXRS";
    }
};

class HSPG : public abstractCommand {
public:
    using abstractCommand::abstractCommand;

    void execute() override {
        cooker_->make_HSPG();
    }

    std::string get_name() override {
        return "HSPG";
    }
};

class waiterLuffy {
public:
    void set_command(int index, abstractCommand* command) {
        if (commands_.find(index) != commands_.end()) {
            if (command->get_name() == "YXRS") {
                std::cout << "sorry, not fish" << "\n";
                return;
            }
        }
        commands_[index].push_back(command);
    }

    void undo_command(int index, abstractCommand* command) {
        for (const auto& cmd : commands_[index]) {
            if (cmd->get_name() == command->get_name()) {
                commands_[index].remove(command);
                break;
            }
        }
    }

    void notify(int index) {
        std::cout << "start make dish" << "\n";
        for (const auto& cmd : commands_[index]) {
            cmd->execute();
        }
        std::cout << "end make dish" << "\n";
    }

    void checkout(int index) {
        std::cout << "start checkout" << "\n";
        for (const auto& cmd : commands_[index]) {
            std::cout << cmd->get_name() << "\n";
        }
    }

private:
    std::map<int, std::list<abstractCommand*>> commands_;
};

int main(int aegc, char const* argv[]) {

    cookerZeef* zeef = new cookerZeef;
    GBJD* gbjd = new GBJD(zeef);
    DSX* dsx = new DSX(zeef);
    YXRS* yxrs = new YXRS(zeef);
    HSPG* hspg = new HSPG(zeef);

    waiterLuffy* luffy = new waiterLuffy;

    luffy->set_command(1, gbjd);
    luffy->set_command(1, dsx);
    luffy->set_command(1, yxrs);
    luffy->set_command(1, hspg);

    luffy->undo_command(1, hspg);

    luffy->notify(1);

    luffy->checkout(1);

    delete luffy;
    delete gbjd;
    delete dsx;
    delete yxrs;
    delete hspg;
    delete zeef;

    return 0;
}
