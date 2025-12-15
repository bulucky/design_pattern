#include <iostream>

class taskQueue {
public:
    taskQueue(const taskQueue& t) = delete;
    taskQueue& operator=(const taskQueue& t) = delete;

    static taskQueue* get_instance() {
        static taskQueue t_Q;

        return &t_Q;
    }

    void print() {
        std::cout << "singleton lazy" << "\n";
    }

private:
    taskQueue() = default;
};


int main(int argc, char const* argv[]) {
    taskQueue* m_t_Q = taskQueue::get_instance();
    m_t_Q->print();

    return 0;
}