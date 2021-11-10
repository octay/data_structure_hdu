//设有一个带头结点的单链表hc，设计一个算法:void split(LinkList *hc, LinkList *&ha, LinkList *&hb,ElemType x,ElemType y)，将hc拆分成两个带头结点的单链表ha和hb，其 中 ha 的所有结点值均大于等于 x 且小于等于 y，hb 为其他结点。

#include <iostream>
#include <cstdio>
#include <malloc.h>

using namespace std;

typedef int ElemType;   // 方便分离

typedef struct node {
    ElemType num;
    struct node *next;
} LinkList;

LinkList *Create();

LinkList *Init();

void InsertOrder(LinkList *p, int n);

void InsertFront(LinkList *p, int n);

void Append(LinkList *p, int n);

void Destroy(LinkList *p);

void Print(LinkList *p);

void Split(LinkList *hc, LinkList *&ha, LinkList *&hb, ElemType x, ElemType y); // >= x or <= y

LinkList *Create() {
    LinkList *p;
    p = (LinkList *) malloc(sizeof(LinkList));
    if (p == nullptr) {
        printf("Create node error. \n");
        exit(-1);
    }
    return p;
}

LinkList *Init() {
    LinkList *p = Create();
    p->next = nullptr;
    return p;
}

void InsertOrder(LinkList *p, int n) {
    LinkList *pnew = Create();
    LinkList *p_mr = p;   // mr是mirror镜像的意思
    pnew->num = n;
    while (p_mr->next && n > p_mr->next->num) {
        p_mr = p_mr->next;
    }
    pnew->next = p_mr->next;
    p_mr->next = pnew;
}

void InsertFront(LinkList *p, int n) {
    LinkList *pnew = Create();
    LinkList *p_mr = p;   // mr是mirror镜像的意思
    pnew->num = n;
    pnew->next = p_mr->next;
    p_mr->next = pnew;
}

void Append(LinkList *p, int n) {
    LinkList *pnew = Create();
    LinkList *p_mr = p;   // mr是mirror镜像的意思
    while (p_mr->next) p_mr = p_mr->next;
    pnew->num = n;
    pnew->next = p_mr->next;
    p_mr->next = pnew;
}

void Destroy(LinkList *p) {
    while (p) {
        struct node *q = p->next;
        free(p);                        // 逐个清空
        p = q;
    }
}

void Print(LinkList *p) {
    p = p->next;
    while (p) {
        cout << p->num << " ";
        p = p->next;
    }
    cout << endl;
}

void Split(LinkList *hc, LinkList *&ha, LinkList *&hb, ElemType x, ElemType y) {
    LinkList *hc_mr = hc;
    LinkList *ha_mr = ha;
    LinkList *hb_mr = hb;       // 定位最初的点
    LinkList *pos;
    while (hc_mr->next) {
        pos = hc_mr->next;
        hc_mr->next = hc_mr->next->next;
        if (pos->num >= x && pos->num <= y) {
            pos->next = ha_mr->next;
            ha_mr->next = pos;
            ha_mr = pos;
        } else {
            pos->next = hb_mr->next;
            hb_mr->next = pos;
            hb_mr = pos;
        }
    }
}

int main() {
    LinkList *ha = Init();
    LinkList *hb = Init();
    LinkList *hc = Init();

    int num = 0, ub = 0, lb = 0;
    string get_rest;

    cout << "please enter nums end with any non-digital char" << endl;
    while (cin >> num) {
        Append(hc, num);
    }
    cin.clear();
    getline(cin, get_rest);
    cout << "please enter lb and ub" << endl;
    cin >> lb >> ub;
    if (lb > ub) {
        int temp;
        temp = lb;
        lb = ub;
        ub = temp;
    }

    Split(hc, ha, hb, lb, ub);

    Print(ha);
    Print(hb);
    return 0;
}