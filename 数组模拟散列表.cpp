// 数组模拟散列表
// 使用拉链法解决hash冲突
#include <cstdio>
#include <iostream>

using namespace std;

const int N = 100003;

// 这里就放每个链表的头结点的索引
int map[N] = { -1 };

// 这里存放实际的数
int a[N] = { 0 };
int current_idx_a = 0;
// 这里存放链接关系
int ne[N] = { -1 };
// 这里存放每个链表的长度
int length[N] = { 0 };

int h(int x)
{
    // +N 在 %N是为了处理负数情况
    return ((x % N) + N) % N;
}

void insert_list(int idx, int x)
{
    a[current_idx_a] = x;

    length[idx]++;
    if (length[idx] == 1) {
        // 采用头插法实现链表，在链表为空的时候，需要将next指向-1。
        ne[current_idx_a] = -1;
    } else {
        ne[current_idx_a] = map[idx];
    }
    map[idx] = current_idx_a;

    current_idx_a++;
}

void insert(int x)
{
    int idx = h(x);
    insert_list(idx, x);
}

bool query_list(int idx, int x)
{
    int head_idx = map[idx];
    while (head_idx != -1) {
        if (a[head_idx] == x) {
            return true;
        }
        head_idx = ne[head_idx];
    }
    return false;
}

bool query(int x)
{
    int idx = h(x);
    return query_list(idx, x);
}

int main()
{
    int n;
    scanf("%d", &n);
    int x;
    char op;
    for (int i = 0; i < n; i++) {
        scanf("\n%c %d", &op, &x);
        switch (op) {
            case 'I':
                insert(x);
                break;
            case 'Q':
                printf("%s\n", query(x) ? "Yes" : "No");
                break;
            default:
                break;
        }
    }
    return 0;
}