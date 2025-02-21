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
        int w, s;
        cin >> w >> s;
        a[i] = { w + s, w };
    }
    sort(a, a + n);

    // 这里要定义的足够小
    int res = -1e9;
    // sum 存储重量之和
    for (int i = 0, sum = 0; i < n; i++) {
        int w = a[i].second;
        int s = a[i].first - w;
        res = max(res, sum - s);
        sum += w;
    }
    cout << res;
    return 0;
}