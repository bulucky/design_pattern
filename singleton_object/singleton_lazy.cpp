#include <mutex>
#include <iostream>

class taskQueue {
public:
    taskQueue(const taskQueue& t) = delete;
    taskQueue& operator=(const taskQueue& t) = delete;

    static taskQueue* get_instance() {
        if (t_Q == nullptr) {
            m_mutex.lock();
            if (t_Q == nullptr) {
                t_Q = new taskQueue;
            }
            m_mutex.unlock();
        }

        return t_Q;
    }

    void print() {
        std::cout << "singleton lazy" << "\n";
    }

private:
    taskQueue() = default;

    static taskQueue* t_Q;
    static std::mutex m_mutex;
};

taskQueue* taskQueue::t_Q = nullptr;
std::mutex taskQueue::m_mutex;

int main(int argc, char const* argv[]) {
    taskQueue* m_t_Q = taskQueue::get_instance();
    m_t_Q->print();

    return 0;
}