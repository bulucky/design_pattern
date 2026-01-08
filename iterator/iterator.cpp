#include <vector>
#include <string>
#include <utility>
#include <iostream>

struct node {
    node(std::string name) : name(std::move(name)) {}

    node* prev = nullptr;
    node* next = nullptr;
    std::string name = std::string();
};

class gLists;

class AbstractIterator {
public:
    AbstractIterator(gLists* list) : list_(list) {}
    virtual ~AbstractIterator() = default;

    node* current() {
        return current_;
    }

    virtual node* first() = 0;
    virtual bool is_done() = 0;
    virtual node* next() = 0;

protected:
    gLists* list_ = nullptr;
    node* current_ = nullptr;
};

class ForwardIterator : public AbstractIterator {
public:
    using AbstractIterator::AbstractIterator;
    ~ForwardIterator() override = default;

    node* first() override;
    bool is_done() override;
    node* next() override;

    // node* first() override {
    //     current_ = list_->get_head();
    //     return current_;
    // }

    // bool is_done() override {
    //     return current_ == list_->get_tail()->next;
    // }

    // node* next() override {
    //     return current_->next;
    // }
};

class ReverseIterator : public AbstractIterator {
public:
    using AbstractIterator::AbstractIterator;
    ~ReverseIterator() override = default;

    node* first() override;
    bool is_done() override;
    node* next() override;
    // node* first() override {
    //     current_ = list_->get_tail();
    //     return current_;
    // }

    // bool is_done() override {
    //     return current_ == list_->get_head()->prev;
    // }

    // node* next() override {
    //     return current_->prev;
    // }
};

class gLists {
public:
    inline int get_count() {
        return count_;
    }

    inline node* get_head() {
        return head;
    }

    inline node* get_tail() {
        return tail;
    }

    node* insert(node* item, const std::string& name) {
        node* node = nullptr;
        if (head == nullptr) {
            push_haed(name);
        } else {
            node = new struct node(name);
            node->next = item;
            node->prev = item->prev;
            item->prev->next = node;
            item->prev = node;
            ++count_;
        }

        return node;
    }

    node* push_haed(const std::string& name) {
        node* node = new struct node(name);
        if (head == nullptr) {
            head = tail = node;
        } else {
            head->prev = node;
            node->next = head;
            head = node;
        }
        ++count_;

        return node;
    }

    node* push_tail(const std::string& name) {
        node* node = new struct node(name);
        if (tail == nullptr) {
            head = tail = node;
        } else {
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
        ++count_;

        return node;
    }

    AbstractIterator* get_iterator(bool is_reverse) {
        if (is_reverse) {
            iterator_ = new ReverseIterator(this);
        } else {
            iterator_ = new ForwardIterator(this);
        }

        return iterator_;
    }

private:
    int count_ = 0;
    node* head = nullptr;
    node* tail = nullptr;
    AbstractIterator* iterator_ = nullptr;
};

node* ForwardIterator::first() {
    current_ = list_->get_head();
    return current_;
}

bool ForwardIterator::is_done() {
    return current_ == list_->get_tail()->next;
}

node* ForwardIterator::next() {
    current_ = current_->next;
    return current_;
}

node* ReverseIterator::first() {
    current_ = list_->get_tail();
    return current_;
}

bool ReverseIterator::is_done() {
    return current_ == list_->get_head()->prev;
}

node* ReverseIterator::next() {
    current_ = current_->prev;
    return current_;
}

int main(int argc, char const* argv[]) {

    std::vector<std::string> Pirates = {"Jin", "kuiyin", "jieke", "fuzifu", "deleike", "maliya", "shimu", "runti", "peijiwan"};
    gLists ls;
    for (const auto& pirat : Pirates) {
        ls.push_tail(pirat);
    }

    AbstractIterator* it = ls.get_iterator(false);
    std::cout << "forward iterator" << "\n";
    for (auto begin = it->first(); !it->is_done(); begin = it->next()) {
        std::cout << begin->name << ", ";
    }
    std::cout << "\n"
              << "end forward iterator" << "\n";
    delete it;

    it = ls.get_iterator(true);
    std::cout << "reverse iterator" << "\n";
    for (auto begin = it->first(); !it->is_done(); begin = it->next()) {
        std::cout << begin->name << ", ";
    }
    std::cout << "\n"
              << "end reverse iterator " << "\n ";
    delete it;

    return 0;
}