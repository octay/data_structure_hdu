#include<stdio.h>
#include<stdlib.h>

struct node *create();  // 创建结点
struct node *init();    // 扩充了一下create() 增加了一个设置末尾next的功能
struct node *seek_tail(struct node *p); // 找链表最后一个结点

void append(struct node *p, int n, int code);   // 在最后插入

void insert(struct node *p, int n, int code, int pos);  // 插到n位置前, 插到n-1位置后, 实现思路是后者

struct node *locate(struct node *p, int n);     // 按num定位

struct node *get(struct node *p, int n);    // 按位置定位

struct node *get_next(struct node *p);  // 很无聊的一个函数

void joseph_c(struct node *p, int n);   // 实现约瑟夫环 in 实验册的主要func

int is_empty(struct node *p);   // 判空

int list_length(struct node *p);    // 记录链表的长度, 不算头结点

void print_list_num(struct node *p);    // 两种遍历就是说

void print_list_num_with_code(struct node *p);

void destroy_list(struct node *p);  // 销毁

struct node {
    int num;        // 这里的num是存储顺序的
    int code;       // 这里的code是存储密码的
    struct node *next;
};

struct node *create() {
    struct node *p;
    p = (struct node *) malloc(sizeof(struct node));
    if (p == NULL) {
        printf("create node error. \n");
        exit(-1);
    }
    return p;
}

struct node *init() {
    struct node *p_list = create();
    p_list->next = p_list;
    return p_list;
}

struct node *seek_tail(struct node *p) {
    struct node *p_mr = p;  // _mr mirror 镜像 之后会遇到很多次
    while (p_mr->next != p) p_mr = p_mr->next;
    return p_mr;        //  判断p_mr -> next是否指向头结点,返回末尾结点
}

void append(struct node *p, int n, int code) {
    struct node *pnew = create();
    struct node *p_mr = seek_tail(p);
    pnew->num = n;
    pnew->code = code;
    pnew->next = p; // 添加头结点为next
    p_mr->next = pnew;
}

void insert(struct node *p, int n, int code, int pos) {
    struct node *pnew = create();
    pnew->num = n;
    pnew->code = code;
    if (n == 1) {
        pnew->next = p->next;
        p->next = pnew;
    } else if (n >= 2) {
        struct node *p_conn = get(p, n - 1);
        pnew->next = p_conn->next; // 插到n位置前就是插到n-1位置后
        p_conn->next = pnew;
    }
}

struct node *locate(struct node *p, int n) {
    struct node *p_mr = p;
    while (p_mr->next != p && p_mr->next->num != n) p_mr = p_mr->next;
    // 如果p_mr -> next不为头结点,那么说明p_mr是所需查找的所在结点的前一个结点,因为理想地只有这两种可能
    if (p_mr->next != p) return p_mr->next;   // 返回所在结点
    else {
        printf("find element not \n");
        exit(-1);
    }
}

struct node *get(struct node *p, int n) {
    if (n <= 0) {
        printf("find element not \n");
        exit(-1);
    }
    struct node *p_mr = p;
    while (p_mr->next != p && n) {
        n--;
        p_mr = p_mr->next;
    }
    // 如果p_mr -> next不为头结点,那么说明p_mr是所需查找的所在结点的前一个结点,因为理想地只有这两种可能
    if (n == 0) return p_mr;   // 返回所在结点
    else {
        printf("find element not \n");
        exit(-1);
    }
}

struct node *get_next(struct node *p) {
    if (p->next) return p->next;
    else {
        printf("get_next func error\n");
        exit(-1);
    }
}

int is_empty(struct node *p) {
    if (p->next == p) return 1;
    else return 0;
}

int list_length(struct node *p) {
    struct node *p_mr = p;
    int count = 0;
    while (p_mr->next != p) {
        p_mr = p_mr->next;
        count++;
    }
    return count;
}

void destroy_list(struct node *p) {
    while (!is_empty(p)) free(p->next);
    free(p);
}

void joseph_c(struct node *p, int n) {
    int count = 0;
    struct node *p_mr = p;
    struct node *p_del;     //实现删除的结点
    while (!is_empty(p)) {
        count++;
        if (count == n) {
            count = 0;
            p_del = p_mr->next;
            if (p_del == p) {    // 跳过头结点 头结点的话自己向后移一位
                p_mr = p_mr->next;
                p_del = p_del->next;
            }
            printf("%d ", p_del->num);    // 打印出列的数字

            p_mr->next = p_del->next;             // 删除出列的结点
            n = p_del->code;
            free(p_del);
        } else {
            p_mr = p_mr->next;
            if (p_mr == p) p_mr = p_mr->next;  // 跳过头结点 头结点的话自己向后移一位
        } // 若删除之后, p_mr -> next 已经是新的数字
    }
    free(p);
    printf("\nowari \n");
}

void print_list_num(struct node *p) {
    for (struct node *p_mr = p; p_mr->next != p; p_mr = p_mr->next) {
        printf("%d ", p_mr->next->num);
    }
    printf("\n");
}

void print_list_num_with_code(struct node *p) {
    for (struct node *p_mr = p; p_mr->next != p; p_mr = p_mr->next) {
        printf("num : %d  code : %d \n", p_mr->next->num, p_mr->next->code);
    }
}

int main(void) {
    struct node *p_list = init();
    int i, num_people, o_code;
    int s_code;

    printf("input the num of people and initial code\n");
    scanf("%d%d", &num_people, &o_code);
    if (!(num_people > 0 && o_code > 0)) {   // m和n应该大于0.
        printf("overflow \n");
        exit(0);
    }

    printf("set a code for each person\n");
    for (i = 1; i <= num_people; i++) {    // 把序号和密码添加到链表中
        scanf("%d", &s_code);
        append(p_list, i, s_code);
    }

//    print_list_num_with_code(p_list);

    joseph_c(p_list, o_code);

    system("pause");
    return 0;
}