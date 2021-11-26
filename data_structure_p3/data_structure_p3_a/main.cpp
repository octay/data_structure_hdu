#include<iostream>

using namespace std;
typedef char ElemType;

typedef struct node {
    struct node *pLeft;
    struct node *pRight;
    ElemType data;
} BiTreeNode, *BiTree;

void InitBiTree(BiTree &T) {
    T->pRight = nullptr;
    T->pLeft = nullptr;
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
        CreateBiTree(T->pLeft);
        CreateBiTree(T->pRight);
    }
}

void Print(ElemType e) {
    cout << e << " ";
}

//前序遍历
void PreTraverse(BiTree T) {
    if (T) {
        cout << T->data << " ";
        PreTraverse(T->pLeft);
        PreTraverse(T->pRight);
    }
}

void PreTraverse(BiTree T, void (*visit)(ElemType T)) {
    if (T) {
        visit(T->data);
        PreTraverse(T->pLeft);
        PreTraverse(T->pRight);
    }
}

void CountNode(BiTree T, int &node_num) {
    if (T) {
        if (!(T->pLeft || T->pRight)) node_num++;
        else {
            CountNode(T->pLeft, node_num);
            CountNode(T->pRight, node_num);
        }
    }
}

//中序遍历
void InTraverse(BiTree T) {
    if (T) {
        InTraverse(T->pLeft);
        cout << T->data << " ";
        InTraverse(T->pRight);
    }
}

void InTraverse(BiTree T, void (*visit)(ElemType T)) {
    if (T) {
        InTraverse(T->pLeft);
        visit(T->data);
        InTraverse(T->pRight);
    }
}

//后续遍历
void PostTraverse(BiTree T) {
    if (T) {
        PostTraverse(T->pLeft);
        PostTraverse(T->pRight);
        cout << T->data << " ";
    }
}

void PostTraverse(BiTree T, void (*visit)(ElemType T)) {
    if (T) {
        PostTraverse(T->pLeft);
        PostTraverse(T->pRight);
        visit(T->data);
    }
}

int CountDepth(BiTree T) {
    int l, r;
    if (!T) return 0;   // 空树
    else {
        l = CountDepth(T->pLeft);   // 左子树的深度
        r = CountDepth(T->pRight);  // 右子树的深度
        return l > r ? l + 1 : r + 1;   // 加上本层
    }
}

int main() {
    BiTree T;
    cout << "input tree with entering \'#\' for null place" << endl;
    CreateBiTree(T);

    PreTraverse(T);
    cout << endl;

    int node_num = 0;
    CountNode(T, node_num);
    cout << "node num : " << endl << node_num << endl;

    cout << "depth : " << endl << CountDepth(T) << endl;

    return 0;
}