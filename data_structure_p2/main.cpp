#include <iostream>
#include <malloc.h>

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10      // p46

typedef char SElemType;     // 因为需要做的题目 括号匹配和行编辑都是处理字符型的数据所以在这里直接typedef char了

typedef struct {
    SElemType *base;
    SElemType *top;
    int stack_size;
} SqStack;

// 以下全部顺序栈的基本操作
// 初始化 销毁 清空 判空 判满 取长 取顶 入栈 出栈 印数 印字 遍历
// r 引用 s 直取 p 指针 请观者自行区分
// 为什么用int 因为不想用 boolean 就是说
int InitStack_r(SqStack &s);

SqStack InitStack_s();

int DestroyStack_p(SqStack *s);

int ClearStack_r(SqStack &s);

int ClearStack_p(SqStack *s);

int isEmpty_r(SqStack &s);

int isEmpty_p(SqStack *s);

int isFull_r(SqStack &s);

int isFull_p(SqStack *s);

int StackLength_r(SqStack &s);

int StackLength_p(SqStack *s);

SElemType GetTop_p(SqStack *s);

SElemType GetTop_r(SqStack &s);

int Push_p(SqStack *s, SElemType e);    // 如果栈满在此扩充

int Push_r(SqStack &s, SElemType e);

int Pop_p(SqStack *s);

int Pop_p(SqStack *s, SElemType &e);     // append the poped elem

int Pop_r(SqStack &s);

int Pop_r(SqStack &s, SElemType &e);

void print_num_elem(SElemType e);

void print_char_elem(SElemType e);

int StackTraverse_p(SqStack *s, void (*visit)(SElemType e));

int StackTraverse_r(SqStack &s, void (*visit)(SElemType e));

// 括号匹配的主函数是这个
int BracketMatchingMain();

// 两种输出方式完成行编辑
int LineEditMain();         // 大段文本输出 换行符也会认真地读取

int LineEditMain_lbl();     // _lbl line by line 逐行输出

int InitStack_r(SqStack &s) {
    s.base = (SElemType *) malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!s.base) {
        std::cout << "malloc error" << std::endl;
        exit(-1);
    }
    s.top = s.base;
    s.stack_size = STACK_INIT_SIZE;
    return 1;   // perform successfully 1
}

SqStack InitStack_s() {
    SqStack s;
    s.base = (SElemType *) malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!s.base) {
        std::cout << "malloc error" << std::endl;
        exit(-1);
    }
    s.top = s.base;
    s.stack_size = STACK_INIT_SIZE;
    return s;
}

int DestroyStack_p(SqStack *s) {
    free(s->base);
    s->base = nullptr;
    s->top = nullptr;
    s->stack_size = 0;    // 如果不这样设置的话 再次入栈判满会重新分配空间
    return 1;
}

int ClearStack_r(SqStack &s) {
    if (!s.base) {
        std::cout << "no base clear error" << std::endl;
        exit(-1);
    } else s.top = s.base;
    return 1;
}

int ClearStack_p(SqStack *s) {
    if (!s->base) {
        std::cout << "no base clear error" << std::endl;
        exit(-1);
    } else s->top = s->base;
    return 1;
}

int isEmpty_r(SqStack &s) {
    return s.base == s.top ? 1 : 0;
}

int isEmpty_p(SqStack *s) {
    return s->base == s->top ? 1 : 0;
}

int isFull_r(SqStack &s) {
    return StackLength_r(s) == s.stack_size ? 1 : 0;
}

int isFull_p(SqStack *s) {
    return StackLength_p(s) == s->stack_size ? 1 : 0;
}

int StackLength_r(SqStack &s) {
    return s.top - s.base;
}

int StackLength_p(SqStack *s) {
    return s->top - s->base;
}

SElemType GetTop_p(SqStack *s) {
    if (isEmpty_p(s)) {
        std::cout << "empty stack get top error" << std::endl;
        exit(-1);
    } else return *((s->top) - 1);
}

SElemType GetTop_r(SqStack &s) {
    if (isEmpty_r(s)) {
        std::cout << "empty stack get top error" << std::endl;
        exit(-1);
    } else return *(s.top - 1);
}

int Push_p(SqStack *s, SElemType e) {
    if (isFull_p(s)) {
        s->base = (SElemType *) realloc(s->base, (s->stack_size + STACK_INCREMENT) * sizeof(SElemType));
        if (!s->base) {
            std::cout << "malloc error" << std::endl;
            exit(-1);
        }
        s->top = s->base + s->stack_size;
        s->stack_size += STACK_INCREMENT;
    }
    *s->top++ = e;
    return 1;
}

int Push_r(SqStack &s, SElemType e) {
    if (isFull_r(s)) {
        s.base = (SElemType *) realloc(s.base, (s.stack_size + STACK_INCREMENT) * sizeof(SElemType));
        if (!s.base) {
            std::cout << "malloc error" << std::endl;
            exit(-1);
        }
        s.top = s.base + s.stack_size;
        s.stack_size += STACK_INCREMENT;
    }
    *s.top++ = e;
    return 1;
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

void print_num_elem(SElemType e) {
    std::cout << e << ' ';
}

void print_char_elem(SElemType e) {
    std::cout << e;     // 打印字符型数据的话就不在末尾添加空格了就是说
}

int StackTraverse_p(SqStack *s, void (*visit)(SElemType e)) {
    SElemType *p = s->base;
    while (p != s->top) {
        visit(*p);
        p++;
    }
    std::cout << std::endl;
    return 1;
}

int StackTraverse_r(SqStack &s, void (*visit)(SElemType e)) {
    SElemType *p = s.base;
    while (p != s.top) {
        visit(*p);
        p++;
    }
    std::cout << std::endl;
    return 1;
}

int BracketMatchingMain() {
    SqStack char_stack;
    InitStack_r(char_stack);
    int a_char;
    int flag = 1;   // flag 1正确 0错误
    std::cout << "input a string which will be checked end up with '#' " << std::endl;
    std::cout << "half-width brackets characters will be checked " << std::endl;
    while ((a_char = std::cin.get()) != EOF && a_char != '#') {
        // 前半括号入栈 后半括号判空出栈并根据括号样式是否一致进行匹配
        if (a_char == '(' || a_char == '[' || a_char == '{') Push_r(char_stack, (SElemType) a_char);
        else if (a_char == ')' || a_char == ']' || a_char == '}') {
            switch (a_char) {
                case ')':
                    if (isEmpty_r(char_stack)) flag = 0;
                    else {
                        char stack_top_char = 0;
                        Pop_r(char_stack, stack_top_char);
                        if ((char) stack_top_char != '(') flag = 0;
                    }
                    break;
                case ']':
                    if (isEmpty_r(char_stack)) flag = 0;
                    else {
                        char stack_top_char = 0;
                        Pop_r(char_stack, stack_top_char);
                        if ((char) stack_top_char != '[') flag = 0;
                    }
                    break;
                case '}':
                    if (isEmpty_r(char_stack)) flag = 0;
                    else {
                        char stack_top_char = 0;
                        Pop_r(char_stack, stack_top_char);
                        if ((char) stack_top_char != '{') flag = 0;
                    }
                    break;
                default:
                    break;
            }
        }
    }

    if (!isEmpty_r(char_stack)) flag = 0;   // 非空说明栈中还有前半括号未完成匹配
    DestroyStack_p(&char_stack);
    return flag;
}

int LineEditMain() {
    SqStack char_stack;
    InitStack_r(char_stack);
    char c = 'a';       // 默认值的作用不用太在意
    std::cout << "input your text" << std::endl;
    char ch = getchar();   // 先行读取一个字符
    while (ch != '0') {     // CLion中调试EOF很麻烦所以用'0'来作为输入的结束标志
        switch (ch) {
            case '#' :
                Pop_r(char_stack, c);
                break;
            case '@' :
                c = 'a';
                while (c != '\n') Pop_r(char_stack, c);
                Push_r(char_stack, '\n');
                break;
            default:
                Push_r(char_stack, ch);
                break;
        }
        ch = getchar();
    }

    StackTraverse_r(char_stack, print_char_elem);
    std::cout << std::endl;

    DestroyStack_p(&char_stack);

    return 1;
}

int LineEditMain_lbl() {
    SqStack char_stack;
    InitStack_r(char_stack);
    char c = 'a';       // 默认值的作用不用太在意
    std::cout << "input your text" << std::endl;
    char ch = getchar();   // 先行读取一个字符

    while (ch != EOF) {   // input EOF 结束
        while (ch != EOF && ch != '\n') {
            switch (ch) {
                case '#' :
                    Pop_r(char_stack, c);
                    break;
                case '@' :
                    ClearStack_r(char_stack);
                    break;
                default:
                    Push_r(char_stack, ch);
                    break;
            }
            ch = getchar();   //从终端接收下一个字符
        }

        StackTraverse_r(char_stack, print_char_elem);
        ClearStack_r(char_stack);
        std::cout << std::endl;

        if (ch != EOF) ch = getchar();
    }

    DestroyStack_p(&char_stack);

    return 1;
}

int main() {
    std::cout << "1. brackets matching" << std::endl;
    if (BracketMatchingMain()) std::cout << "matched ok" << std::endl;
    else std::cout << "matched failed" << std::endl;
    system("pause");

    std::cout << "2. line editing" << std::endl;
    LineEditMain();
//    LineEditMain_lbl();
    system("pause");

    return 0;
}
