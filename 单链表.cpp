#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <pthread.h>
#include <string>
#include <utility>

using namespace std;

const int N = 500100;

int n;
int e[N], ne[N], idx;

void init()
{
    idx = 1;
    ne[0] = -1;
}

void insert(int k, int x)
{
    e[idx] = x;
    ne[idx] = ne[k];
    ne[k] = idx;
    idx++;
}

void del(int k)
{
    int next = ne[k];
    ne[k] = ne[next];
}

int main()
{
    cin >> n;
    init();
    string op;
    int k, x;
    while (n--) {
        cin >> op;
        if (op == "H") {
            cin >> x;
            insert(0, x);
        } else if (op == "D") {
            cin >> k;
            del(k);
        } else if (op == "I") {
            cin >> k >> x;
            insert(k, x);
        }
    }
    for (int i = ne[0]; i != -1; i = ne[i]) {
        cout << e[i] << " ";
    }

    return 0;
}