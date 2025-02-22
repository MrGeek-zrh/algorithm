#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <pthread.h>
#include <string>
#include <utility>

using namespace std;

const int N = 500100;

typedef pair<int, int> PII;

int n;
PII a[N];

int main()
{
    cin >> n;

    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        a[i] = { l, r };
    }

    sort(a, a + n);

    int right = a[0].first;
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (right >= a[i].first) {
            // 相交，更新right
            right = max(right, a[i].second);
        } else {
            // 不想交，直接更新right
            res++;
            right = a[i].second;
        }
    }
    // 注意，是res+1
    cout << res + 1;

    return 0;
}