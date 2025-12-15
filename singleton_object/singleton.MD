# 单例模式
创建型设计模式,一个类仅能创建一个实例，且对该实例具有全局访问

饿汉模式: 立即实例

懒汉模式：需要时实例，但在多线程场景下会引出线程安全问题

区分: 实例对象的时刻

构造函数: 默认构造函数、拷贝构造函数、拷贝构造函数运算符重载、移动构造函数、移动构造函数运算符重载
## 饿汉模式

## 懒汉模式
解决多线程访问时的线程安全问题

- **双重判断加锁定**
  
  仅在首次获取时存在多次加锁解锁操作，提高效率，但是如果内存重排，会出现偶发性bug
  
  > 内存重排：
  >
  >正常顺序：分配空内存->将创建对象移至空内存->将指针指向内存
  >
  > 重排顺序：分配空内存->指针指向内存->将创建对象移至空内存
  
  ```
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
  ```
- **使用原子变量避免内存重排**
  
  将实例对象指针原子元
  ```
  static std::atomic<taskQueue*> t_Q;

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
  ```
- **局部静态变量**
  
  c++11标准：并发进程需等待静态局部变量完成初始化，故不存在线程访问安全问题
  ```
  static taskQueue* get_instance() {
      static taskQueue t_Q;

      return &t_Q;
  }
  ```