// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
#include <cctype>

int getprior(char op) {
    if (op == '(') return 0;
    if (op == ')') return 1;
    if (op == '+' || op == '-') return 2;
    if (op == '*' || op == '/') return 3;
    return -1;
}

bool operatorr(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string result;
    size_t len = inf.length();
    for (size_t i = 0; i < len; ++i) {
        char c = inf[i];
        if (c == ' ') {
            continue;
        }
        if (isdigit(c)) {
            while (i < len && isdigit(inf[i])) {
                result += inf[i];
                ++i;
            }
            result += ' ';
            --i;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.empty() && stack.get() != '(') {
                result += stack.get();
                result += ' ';
                stack.pop();
            }
            if (!stack.empty() && stack.get() == '(') {
                stack.pop();
            }
        } else if (operatorr(c)) {
            while (!stack.empty() && stack.get() != '(' &&
                getprior(stack.get()) >= getprior(c)) {
                result += stack.get();
                result += ' ';
                stack.pop();
            }
            stack.push(c);
        }
    }
    while (!stack.empty()) {
        result += stack.get();
        result += ' ';
        stack.pop();
    }
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    return result;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    size_t len = post.length();
    for (size_t i = 0; i < len; ++i) {
        char c = post[i];
        if (c == ' ') {
            continue;
        }
        if (isdigit(c)) {
            std::string num;
            while (i < len && isdigit(post[i])) {
                num += post[i];
                ++i;
            }
            stack.push(std::stoi(num));
            --i;
        } else if (operatorr(c)) {
            int B = stack.get();
            stack.pop();
            int A = stack.get();
            stack.pop();
            int res = 0;
            if (c == '+') res = A + B;
            else if (c == '-') res = A - B;
            else if (c == '*') res = A * B;
            else if (c == '/') res = A / B;
            stack.push(res);
        }
    }
    return stack.get();
}
