#include <mutex>
#include <queue>
#include <thread>
#include <iostream>

using namespace std::chrono_literals;

class taskQueue {
public:
    taskQueue(const taskQueue& t) = delete;
    taskQueue& operator=(const taskQueue& t) = delete;

    static taskQueue* get_instance() {
        return t_Q_;
    }

    void print() {
        std::cout << "singleton" << "\n";
    }

    // 队列判空
    bool is_empty() {
        std::lock_guard<std::mutex> locker(t_mutex_);
        return tasks_.empty();
    }

    // 填加任务
    void add_task(int task) {
        std::lock_guard<std::mutex> locker(t_mutex_);
        tasks_.push(task);
    }

    // 删除任务
    bool delete_task() {
        std::lock_guard<std::mutex> locker(t_mutex_);
        if (tasks_.empty()) return false;
        tasks_.pop();

        return true;
    }

    // 获取任务
    int get_task() {
        std::lock_guard<std::mutex> locker(t_mutex_);
        if (tasks_.empty()) return -1;
        return tasks_.front();
    }

private:
    taskQueue() = default;
    static taskQueue* t_Q_;

    std::queue<int> tasks_;
    std::mutex t_mutex_;
};
taskQueue* taskQueue::t_Q_ = new taskQueue;

int main(int argc, char const* argv[]) {
    taskQueue* m_t_Q = taskQueue::get_instance();

    // 生产者
    std::thread t_producer([=]() {
        for (int i = 0; i < 10; ++i) {
            m_t_Q->add_task(i);
            std::cout << "add task: " << i << " " << "thread_ID: " << std::this_thread::get_id() << "\n";
            std::this_thread::sleep_for(500ms);
        }
    });

    // 消费者
    std::thread t_consumer([=]() {
        while (!m_t_Q->is_empty()) {
            int task = m_t_Q->get_task();
            m_t_Q->delete_task();
            std::cout << "get task: " << task << " " << "thread_ID: " << std::this_thread::get_id() << "\n";
            std::this_thread::sleep_for(1000ms);
        }
    });

    t_producer.join();
    t_consumer.join();

    return 0;
}