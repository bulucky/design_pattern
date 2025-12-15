#include <mutex>
#include <atomic>
#include <iostream>

class taskQueue {
public:
    taskQueue(const taskQueue& t) = delete;
    taskQueue& operator=(const taskQueue& t) = delete;

    static taskQueue* get_instance() {
        taskQueue* task = t_Q.load();
        if (task == nullptr) {
            m_mutex.lock();
            task = t_Q.load();
            if (task == nullptr) {
                task = new taskQueue;
                t_Q.store(task);
            }
            m_mutex.unlock();
        }

        return t_Q.load();
    }

    void print() {
        std::cout << "singleton lazy" << "\n";
    }

private:
    taskQueue() = default;

    static std::atomic<taskQueue*> t_Q;
    static std::mutex m_mutex;
};

std::atomic<taskQueue*> taskQueue::t_Q;
std::mutex taskQueue::m_mutex;

int main(int argc, char const* argv[]) {
    taskQueue* m_t_Q = taskQueue::get_instance();
    m_t_Q->print();

    return 0;
}