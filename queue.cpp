// 数组模拟队列
#include <cstdio>
#include <iostream>
#include <map>
#include <string>

using namespace std;

const int N = 100010;

int a[N] = { 0 };

map<string, int> op_map = { { "push", 1 }, { "pop", 2 }, { "empty", 3 }, { "query", 4 } };

int tail_idx = 0;
int top_idx = 0;

void push(int x)
{
    a[tail_idx] = x;
    tail_idx++;
}

void pop()
{
    a[top_idx] = 0;
    top_idx++;
}

bool empty()
{
    return top_idx >= tail_idx;
}

int query()
{
    return a[top_idx];
}

int main()
{
    int m = 0;
    cin >> m;
    string op;
    int x;
    for (int i = 0; i < m; i++) {
        cin >> op;
        switch (op_map[op]) {
            case 1:
                cin >> x;
                push(x);
                break;
            case 2:
                pop();
                break;

            case 3:
                if (empty()) {
                    printf("YES\n");
                } else {
                    printf("NO\n");
                }
                break;
            case 4:
                cout << query() << endl;
                break;
            default:
                break;
        }
    }
    return 0;
}