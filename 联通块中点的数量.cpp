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

using namespace std;

const int N = 100010;
const int M = 1000100;

int n, m;

pair<int, int> p[N];

int query(int s)
{
    while (s != p[s].first) {
        int x = s;
        s = p[s].first;
        p[x].first = p[s].first;
    }
    return s;
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        p[i].first = i;
        p[i].second = 1;
    }
    string op;

    int a, b;
    while (m--) {
        cin >> op;
        if (op == "C") {
            cin >> a >> b;
            if (a == b) {
                continue;
            } else {
                int parent_a = query(a);
                int parent_b = query(b);
                // 易错：如果两个点是在同一个区间，不应该合并
                if (parent_a != parent_b) {
                    p[parent_b].second += p[parent_a].second;
                    p[parent_a].first = parent_b;
                } else {
                    continue;
                }
            }
        } else if (op == "Q1") {
            cin >> a >> b;
            if (a == b) {
                cout << "Yes" << endl;
                continue;
            } else {
                cout << (query(a) == query(b) ? "Yes" : "No") << endl;
            }
        } else if (op == "Q2") {
            cin >> a;
            int parent_a = query(a);
            cout << p[parent_a].second << endl;
        }
    }
    return 0;
}