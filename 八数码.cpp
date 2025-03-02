#include <cctype>
#include <charconv>
#include <cmath>
#include <codecvt>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <pthread.h>
#include <queue>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <stack>
#include <unordered_map>
#include <cstring>

using namespace std;

const int N = 110;
const int M = 1000100;

int n, m;

// 按照上 下 左 右 的顺序的坐标偏移量
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

unordered_map<string, int> s_cnt;
queue<string> q;

int bfs(string s)
{
    string end = "12345678x";
    s_cnt[s] = 0;
    q.push(s);

    while (q.size()) {
        string t = q.front();
        string t_bak = t;
        q.pop();

        if (t_bak == end) {
            return s_cnt[t_bak];
        }

        int x_idx = t.find('x');
        int x_x = x_idx / 3;
        int x_y = x_idx % 3;

        for (int i = 0; i < 4; i++) {
            int x = x_x + dx[i];
            int y = x_y + dy[i];
            if (x >= 0 && x < 3 && y >= 0 && y < 3) {
                int ne_idx = x * 3 + y;
                swap(t_bak[ne_idx], t_bak[x_idx]);
                // 只有没被访问过的才能被放到队列中
                if (!s_cnt.count(t_bak)) {
                    s_cnt[t_bak] = s_cnt[t] + 1;
                    q.push(t_bak);
                }

                t_bak = t;
            }
        }
    }
    return -1;
}

int main()
{
    string s;
    char t;
    for (int i = 0; i < 9; i++) {
        cin >> t;
        s += t;
    }

    int res = bfs(s);
    cout << res;

    return 0;
}