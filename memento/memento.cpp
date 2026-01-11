#include <vector>
#include <utility>
#include <iostream>
#include <unordered_map>

class History {
public:
    History(std::string msg) : msg_(std::move(msg)) {}
    ~History() = default;

    std::string get_history() {
        return msg_;
    }

private:
    std::string msg_;
};

class Recorder {
public:
    Recorder() = default;
    ~Recorder() {
        for (const auto& history : historys_) {
            std::cout << "destory history " << history.second->get_history() << "\n";
            delete history.second;
        }
    };

    void set_history(int index, History* history) {
        historys_.insert({index, history});
    }

    History* get_history(int index) {
        if (historys_.find(index) != historys_.end()) {
            return historys_[index];
        }

        return nullptr;
    }

private:
    std::unordered_map<int, History*> historys_;
};

class JiaoPenJi {
public:
    JiaoPenJi() = default;
    ~JiaoPenJi() = default;

    void set_state(std::string msg) {
        msg_ = std::move(msg);
    }

    History* save_history() {
        return new History(msg_);
    }

    void get_history_from_recorder(History* history) {
        msg_ = history->get_history();
    }

    std::string get_state() {
        return msg_;
    }

private:
    std::string msg_;
};

int main(int argc, char const* argv[]) {
    std::vector<std::string> msgs = {"burn", "kill", "grab", "plunder"};

    Recorder* recorder = new Recorder();
    JiaoPenJi* jiaopenji = new JiaoPenJi();

    for (size_t i = 0; i < msgs.size(); ++i) {
        jiaopenji->set_state(msgs[i]);
        recorder->set_history(i, jiaopenji->save_history());
    }

    std::cout << "jiaopenji unrecognized history" << "\n";
    for (size_t i = 0; i < msgs.size(); ++i) {
        jiaopenji->get_history_from_recorder(recorder->get_history(i));
        std::cout << jiaopenji->get_state() << "\n";
    }

    delete jiaopenji;
    delete recorder;

    return 0;
}
