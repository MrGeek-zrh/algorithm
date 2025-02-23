#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <algorithm>
#include <pthread.h>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const int N = 100100;

int n;
int e[N], pre[N], ne[N], idx;

void init()
{
    // 易错：这里是2，不是0
    idx = 2;
    ne[0] = 1;
    pre[1] = 0;
}

void insert(int i, int x)
{
    int i_pre = pre[i];
    int i_ne = ne[i];
    e[idx] = x;
    ne[idx] = i_ne;
    pre[idx] = i;
    pre[i_ne] = idx;
    ne[i] = idx;
    idx++;
}

void del(int i)
{
    int i_pre = pre[i];
    int i_ne = ne[i];
    ne[i_pre] = i_ne;
    pre[i_ne] = i_pre;
}

int main()
{
    cin >> n;
    init();
    string op;
    int k, x;
    while (n--) {
        cin >> op;
        if (op == "L") {
            cin >> x;
            insert(0, x);
        } else if (op == "R") {
            cin >> x;
            insert(pre[1], x);
        } else if (op == "D") {
            cin >> k;
            del(k - 1 + 2);
        } else if (op == "IL") {
            cin >> k >> x;
            insert(pre[k + 1], x);
        } else if (op == "IR") {
            cin >> k >> x;
            insert(k + 1, x);
        }
    }
    for (int i = ne[0]; i != 1; i = ne[i]) {
        cout << e[i] << " ";
    }

    return 0;
}