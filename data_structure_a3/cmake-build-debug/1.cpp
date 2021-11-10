#include <iostream>

typedef char SElemType;

typedef struct {
    SElemType *base;
    SElemType *top;
    int stack_size;
} SqStack;

int isEmpty_r(SqStack &s);    // r 引用 p 指针

int isEmpty_p(SqStack *s);

int Pop_p(SqStack *s);

int Pop_p(SqStack *s, SElemType &e);     // append the poped elem

int Pop_r(SqStack &s);

int Pop_r(SqStack &s, SElemType &e);

int isEmpty_p(SqStack *s) {
    return s->base == s->top ? 1 : 0;
}

int isEmpty_r(SqStack &s) {
    return s.base == s.top ? 1 : 0;
}

int Pop_p(SqStack *s) {
    if (isEmpty_p(s)) {
        std::cout << "empty stack pop error" << std::endl;
        exit(-1);
    }
    return 1;
}

int Pop_p(SqStack *s, SElemType &e) {
    if (isEmpty_p(s)) {
        std::cout << "empty stack pop error" << std::endl;
        exit(-1);
    }
    e = *--s->top;
    return 1;
}

int Pop_r(SqStack &s) {
    if (isEmpty_r(s)) {
        std::cout << "empty stack pop error" << std::endl;
        exit(-1);
    }
    return 1;
}

int Pop_r(SqStack &s, SElemType &e) {
    if (isEmpty_r(s)) {
        std::cout << "empty stack pop error" << std::endl;
        exit(-1);
    }
    e = *--s.top;
    return 1;
}
