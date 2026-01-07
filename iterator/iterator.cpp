#include <string>
#include <utility>

struct node {
    node(std::string name) : name(std::move(name)) {}

    node* prev = nullptr;
    node* next = nullptr;
    std::string name = std::string();
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

private:
    int count_ = 0;
    node* head = nullptr;
    node* tail = nullptr;
};

int main(int argc, char const* argv[]) {

    return 0;
}