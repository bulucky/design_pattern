// #ifndef ITERATOR_HPP_
// #define ITERATOR_HPP_

// class node;
// class gLists;

// class AbstractIterator {
// public:
//     AbstractIterator(gLists* list) : list_(list) {}
//     ~AbstractIterator() = default;

//     node* current() {
//         return current_;
//     }

//     virtual node* first() = 0;
//     virtual bool is_done() = 0;
//     virtual node* next() = 0;

// protected:
//     gLists* list_ = nullptr;
//     node* current_ = nullptr;
// };

// class ForwardIterator : public AbstractIterator {
// public:
//     using AbstractIterator::AbstractIterator;

//     node* first() override {
//         return list_->get_head();
//     }

//     bool is_done() override {
//         return current_ == list_->get_tail()->next;
//     }

//     node* next() override {
//         return current_->next;
//     }
// };

// class ReverseIterator : public AbstractIterator {
// public:
//     using AbstractIterator::AbstractIterator;

//     node* first() override {
//         return list_->get_tail();
//     }

//     bool is_done() override {
//         return current_ == list_->get_head()->prev;
//     }

//     node* next() override {
//         return current_->next;
//     }
// };

// #endif