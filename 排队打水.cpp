#include <iostream>
#include <algorithm>

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
    // 要用longlong，不然会溢出
    long long res = 0;
    sort(a, a + n);
    for (int i = 0; i < n; i++) {
        res += a[i] * (n - 1 - i);
    }
    cout << res;
    return 0;
}