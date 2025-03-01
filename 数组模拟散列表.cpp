#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <pthread.h>
#include <queue>
#include <string>
#include <utility>
#include <vector>
#include <stack>
#include <unordered_map>
#include <cstring>

using namespace std;

const int N = 100003;
const int M = 1000100;

int n, m;

// 数组模拟散列表，拉链法解决冲突

// 一般用邻接表实现n条链表的时候，都是搭配链表的头插法，这样写起来代码最少，也最简单
int a[N], e[N], ne[N], idx;

void insert(int x)
{
    int x_idx = (x % N + N) % N;
    e[idx] = x;
    ne[idx] = a[x_idx];
    a[x_idx] = idx;
    idx++;
}

bool query(int x)
{
    int x_idx = (x % N + N) % N;
    int head = a[x_idx];
    bool find = false;
    while (head != -1) {
        if (e[head] == x) {
            find = true;
            break;
        }
        head = ne[head];
    }
    return find;
}

int main()
{
    cin >> n;

    memset(a, -1, sizeof(a));

    string op;
    int x;
    while (n--) {
        cin >> op;
        cin >> x;
        if (op == "I") {
            insert(x);
        } else if (op == "Q") {
            cout << (query(x) ? "Yes" : "No") << endl;
        }
    }

    return 0;
}