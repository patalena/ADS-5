// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
    T arr[size] = {};
    int top = -1;
 public:
    TStack() {}
    bool empty() const {
        return top == -1;
    }
    bool full() const {
        return top == size - 1;
    }
    void push(const T& item) {
        if (!full()) {
            arr[++top] = item;
        }
    }
    void pop() {
        if (!empty()) {
            top--;
        }
    }
    T get() const {
        if (!empty()) {
            return arr[top];
        }
        return T();
    }
    T popget() {
        if (!empty()) {
            T val = arr[top];
            top--;
            return val;
        }
        return T();
    }
    void clear() {
        top = -1;
    }
};
#endif  // INCLUDE_TSTACK_H_
