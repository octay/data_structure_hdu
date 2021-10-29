#include<stdio.h>
#include<stdlib.h>

struct node {
    int num;
    struct node *next;
};

struct node *create();

void insert(struct node *p, int n);

void destroy(struct node *p);

void print(struct node *p);

void reverse(struct node *ori);

void reverse_ver2(struct node *ori);

int main() {
    struct node *l_head = create();
    l_head->next = NULL;
    int input_num;

    while (1) {
        scanf("%d", &input_num);
        if (!input_num) break;       // input_num为0时跳出循环
        insert(l_head, input_num);
    }

    printf("arranged series of number \n");
    print(l_head);

    reverse_ver2(l_head);
    printf("arranged and reversed series of number \n");
    print(l_head);

    destroy(l_head);

    return 0;
}

struct node *create() {
    struct node *p;
    p = (struct node *) malloc(sizeof(struct node));
    if (p == NULL) {
        printf("create node error. \n");
        exit(-1);
    }
    return p;
}

void insert(struct node *p, int n) {
    struct node *p_new = create();
    struct node *p_mr;
    p_mr = p;
    p_new->num = n;
    while (p_mr->next && n > p_mr->next->num) {
        p_mr = p_mr->next;
    }
    p_new->next = p_mr->next;
    p_mr->next = p_new;
}

void destroy(struct node *p) {
    while (p) {
        struct node *q = p->next;
        free(p);        // 逐个清空
        p = q;
    }
}

void print(struct node *p) {
    p = p->next;
    while (p) {
        printf("%d ", p->num);
        p = p->next;
    }
    printf("\n");
}

void reverse(struct node *ori) {
    struct node *ori_mr = ori;
    struct node *p, *q;
    p = ori_mr->next;
    ori_mr->next = NULL;
    while (p) {
        q = p;
        p = p->next;
        q->next = ori_mr->next;
        ori_mr->next = q;
    }
}

void reverse_ver2(struct node *ori) {
    struct node *ori_mr = ori;  // 在本程序中 ori_mr是在变化的，使用元ori来找到原先的链表头结点
    struct node *p, *q;
    struct node *r = ori_mr -> next;    // 第一个有数据的结点
    while (r -> next) {
        p = ori_mr;
        q = ori_mr;
        while(p -> next){
            q = p;
            p = p -> next;
        }
        q -> next = p -> next;  // NULL end of l
        p -> next = ori_mr -> next;
        ori_mr -> next = p;
        ori_mr = p;     // 下一个需要做插入处理的点就是在新处理的结点之后了就是说
    }
}
