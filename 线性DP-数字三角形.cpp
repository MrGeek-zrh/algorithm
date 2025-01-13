#include <algorithm>
#include <iostream>
using namespace std;

const int N = 510;
const int INF = 1e9;

int n;

int a[N][N];
int f[N][N];

int main()
{
    cin >> n;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cin >> a[i][j];
        }
    }

    // 设置边界为最小值，这样就不需要额外判断是不是边界了
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i + 1; j++) {
            f[i][j] = -INF;
        }
    }

    f[1][1] = a[1][1];

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            // 左边看列，右边看行
            f[i][j] = max(f[i - 1][j - 1] + a[i][j], f[i - 1][j] + a[i][j]);
        }
    }

    int res = -INF;
    for (int i = 1; i <= n; i++) {
        res = max(res, f[n][i]);
    }

    cout << res;

    return 0;
}