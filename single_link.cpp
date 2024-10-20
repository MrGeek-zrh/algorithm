// 数组模拟单链表
//
#include <cstdio>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>
#include <map>

using namespace std;

const int N = 100010;
int value[N] = { 0 };
int nxt[N] = { -1 };

// 记录头结点的idx
int head_idx = -1;

// 记录第k个数和对应的idx
map<int, int> k_map;
int k_th = 1;

void insert(int k, int x, int length)
{
    if (k == 0) {
        value[length] = x;
        nxt[length] = head_idx;
        head_idx = length;
    } else {
        value[length] = x;
        int k_index = k_map[k];
        nxt[length] = nxt[k_index];
        nxt[k_index] = length;
    }
    k_map[k_th++] = length;
}

void remove(int k, int length)
{
    int current_idx;
    if (k == 0) {
        current_idx = head_idx;
        head_idx = nxt[head_idx];
        value[current_idx] = -1;
        nxt[current_idx] = -1;
    } else {
        current_idx = k_map[k];
        int current_idx_next = nxt[current_idx];
        nxt[current_idx] = nxt[current_idx_next];
        nxt[current_idx_next] = -1;
        value[current_idx_next] = -1;
    }
}

int main()
{
    int m;
    cin >> m;

    char op;
    int k, x;
    k = -1, x = 0;
    int length = 0;
    for (int i = 0; i < m; i++) {
        cin >> op;
        switch (op) {
            case 'H':
                cin >> x;
                insert(0, x, length);
                length++;
                break;
            case 'D':
                cin >> k;
                remove(k, length);
                break;
            case 'I':
                cin >> k >> x;
                insert(k, x, length);
                length++;
                break;
            default:
                break;
        }
    }

    int i = head_idx;
    for (; nxt[i] != -1; i = nxt[i]) {
        printf("%d ", value[i]);
    }
    printf("%d", value[i]);

    return 0;
}
