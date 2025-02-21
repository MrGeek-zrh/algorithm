#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <pthread.h>
#include <string>

using namespace std;

const int N = 100100;

int n;
int a[N];

int main()
{
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // 易错：要排序
    sort(a, a + n);

    int res = 0;
    for (int i = 0; i < n; i++) {
        res += abs(a[i] - a[n / 2]);
    }

    cout << res;
    return 0;
}