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

const int N = 1e6 + 10;
const int M = 1000100;

pair<int, int> a[N];
int n, m;

int main()
{
    int s, t;
    cin >> s >> t;
    cin >> n;
    int l, r;
    for (int i = 0; i < n; i++) {
        cin >> l >> r;
        a[i] = { l, r };
    }
    sort(a, a + n);

    int right = -1e9 - 10;
    for (int i = 0; i < n; i++) {
        int j = i;
        while (j < n && a[j].first <= s) {
            right = max(right, a[j].second);
            j++;
        }
        if (j == n) {
            cout << -1;
            return 0;
        }
        if (right < s) {
            cout << -1;
            return 0;
        }
    }

    return 0;
}