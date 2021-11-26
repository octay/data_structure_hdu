#include <iostream>

using namespace std;
typedef char ElemType;

typedef enum {
    Link, Thread    // Link 0指针 Thread 1线索
} PointerTag;

typedef struct BiTreeNode {
    ElemType data;
    struct BiTreeNode *lChild, *rChild;
    PointerTag lTag, rTag;
} BiTreeNode, *BiTree;

int Print(ElemType e) {
    cout << e << " ";
    return 1;
}

void CreateBiTree(BiTree &T) {
    // try AB##C##  ABC#D##E##F##
    char c;
    cin >> c;
    if ('#' == c) // if # set null
        T = nullptr;
    else {
        T = new BiTreeNode;
        T->data = c;
        CreateBiTree(T->lChild);
        CreateBiTree(T->rChild);
    }
}

int InOrderTraverse_Thr(BiTree T, int (*visit)(ElemType e)) {
    BiTree p = T->lChild;
    while (p != T) {
        while (p->lTag == Link) p = p->lChild;
        if (!p) return 0;   // 书上的代码有这一句，虽然觉得是空话，但还是保留一下。
        else visit(p->data);
        while (p->rTag == Thread && p->rChild != T) {
            p = p->rChild;
            visit(p->data);
        }
        p = p->rChild;
    }
    return 1;
}

int InThreading(BiTree p, BiTree &pre) {
    // pre 在内外连线索当作类似全局变量的一个方法
    // 在调用 InOrderThreading() 中创建这个变量
    if (p) {
        InThreading(p->lChild, pre);
        if (!p->lChild) {
            p->lTag = Thread;
            p->lChild = pre;
        } else p->lTag = Link;
        if (!pre->rChild) {
            pre->rTag = Thread;
            pre->rChild = p;
        } else p->rTag = Link;
        pre = p;
        InThreading(p->rChild, pre);
    }
    return 1;
}

int InOrderThreading(BiTree &T_head, BiTree T) {
    BiTree pre;
    T_head = new BiTreeNode;    // head node
    // 不得不说现在 c++ 越来越靠近保姆语言了，不错。
    T_head->lTag = Link;
    T_head->rTag = Thread;
    T_head->rChild = T_head;
    if (!T) T_head->lChild = T_head;
    else {
        T_head->lChild = T;
        pre = T_head;
        InThreading(T, pre);
        pre->rChild = T_head;
        pre->rTag = Thread;
        T_head->rChild = pre;
    }
    return 1;
}

int main() {
    BiTree T, T_head;
    cout << "input tree with entering \'#\' for null place" << endl;
    CreateBiTree(T);
    InOrderThreading(T_head, T);

    InOrderTraverse_Thr(T_head, Print);
    cout << endl;
    return 0;
}
