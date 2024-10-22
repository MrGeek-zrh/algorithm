// 数组模拟双链表
#include <cstdio>
#include <iostream>
#include <string>
#include <map>

using namespace std;

const int N = 100010;
int value[N] = { 0 };
int l_idx[N] = { -1 };
int r_idx[N] = { -1 };

int head_idx = -1;
int tail_idx = -1;
int k_th = 0;
map<string, int> op_map = { { "L", 1 }, { "R", 2 }, { "D", 3 }, { "IL", 4 }, { "IR", 5 } };
map<int, int> k_map = { { -1, -1 } };

// op_type=-1表示在左段插入
// op_type=-2表示在右端插入
// k=0表示忽略k
void insert(int op_type, int k, int x, int length)
{
    value[length] = x;
    // 当前链表为空
    if (head_idx == -1 || tail_idx == -1) {
        head_idx = length;
        tail_idx = length;
        l_idx[head_idx] = -1;
        r_idx[head_idx] = -1;
        ++k_th;
        k_map[k_th] = length;
        return;
    }
    if (op_type == -1) {
        // 在头部插入
        if (k == 0) {
            l_idx[head_idx] = length;
            l_idx[length] = -1;
            r_idx[length] = head_idx;
            head_idx = length;
        } else {
            int current_idx = k_map[k];
            int current_left_idx = l_idx[current_idx];
            l_idx[current_idx] = length;
            r_idx[length] = current_idx;
            // 在头部插入
            if (head_idx == tail_idx) {
                l_idx[length] = -1;
                head_idx = length;
                ++k_th;
                k_map[k_th] = length;
                return;
            }
            // 从中间插入
            l_idx[length] = current_left_idx;
            r_idx[current_left_idx] = length;
        }
    } else {
        // 从尾部插入
        if (k == 0) {
            r_idx[tail_idx] = length;
            l_idx[length] = tail_idx;
            r_idx[length] = -1;
            tail_idx = length;
        } else {
            int current_idx = k_map[k];
            int current_right_idx = r_idx[current_idx];
            r_idx[current_idx] = length;
            l_idx[length] = current_idx;
            // 从尾部插入
            if (head_idx == tail_idx) {
                r_idx[length] = -1;
                tail_idx = length;
                ++k_th;
                k_map[k_th] = length;
                return;
            }
            r_idx[length] = current_right_idx;
            l_idx[current_right_idx] = length;
        }
    }
    ++k_th;
    k_map[k_th] = length;
}

void remove(int k)
{
    int current_idx = k_map[k];
    int current_left_idx = l_idx[current_idx];
    int current_right_idx = r_idx[current_idx];

    // 只有一个元素
    if (head_idx == tail_idx) {
        head_idx = -1;
        tail_idx = -1;
        l_idx[current_idx] = -1;
        r_idx[current_idx] = -1;
        value[current_idx] = 0;
        return;
    }

    // 删除头元素
    if (current_idx == head_idx) {
        head_idx = current_right_idx;
        l_idx[current_right_idx] = -1;
        l_idx[current_idx] = -1;
        r_idx[current_idx] = -1;
        value[current_idx] = 0;
        return;
    }

    // 删除尾元素
    if (current_idx == tail_idx) {
        tail_idx = current_left_idx;
        r_idx[current_left_idx] = -1;
        l_idx[current_idx] = -1;
        r_idx[current_idx] = -1;
        value[current_idx] = 0;
        return;
    }

    r_idx[current_left_idx] = current_right_idx;
    l_idx[current_right_idx] = current_left_idx;

    l_idx[current_idx] = -1;
    r_idx[current_idx] = -1;
    value[current_idx] = 0;
}

int main()
{
    int m = 0;
    cin >> m;

    string op;
    int x;
    int k;
    int length = 0;
    for (int i = 0; i < m; i++) {
        cin >> op;
        switch (op_map[op]) {
            case 1:
                cin >> x;
                // k=-1表示在最左段插入
                // k=-2表示在最右端插入
                insert(-1, 0, x, length);
                length++;
                break;
            case 2:
                cin >> x;
                insert(-2, 0, x, length);
                length++;
                break;
            case 3:
                cin >> k;
                remove(k);
                break;
            case 4:
                cin >> k >> x;
                insert(-1, k, x, length);
                length++;
                break;
            case 5:
                cin >> k >> x;
                insert(-2, k, x, length);
                length++;
                break;
            default:
                break;
        }
    }

    int idx = head_idx;
    while (idx != -1) {
        printf("%d ", value[idx]);
        idx = r_idx[idx];
    }

    return 0;
}