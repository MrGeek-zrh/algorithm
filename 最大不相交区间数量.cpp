#include <algorithm>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using namespace std;

const int N = 100010;
struct range {
    int x, y;
    bool operator<(const range &r)
    {
        return y < r.y;
    }
} range[N];

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> range[i].x >> range[i].y;
    }
    sort(range, range + n);
    int end = -1e9 - 10;
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (end < range[i].x) {
            res++;
            end = range[i].y;
        }
    }
    cout << res;
    return 0;
}