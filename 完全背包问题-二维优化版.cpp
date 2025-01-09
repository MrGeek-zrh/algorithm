#include <algorithm>
#include <iostream>
using namespace std;

const int N = 1010;

int f[N][N];
int v[N];
int w[N];

int main()
{
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> v[i] >> w[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (v[i] > j) {
                f[i][j] = f[i - 1][j];
            } else {
                f[i][j] = max(f[i - 1][j], f[i][j - v[i]] + w[i]);
            }
        }
    }
    cout << f[n][m];
    return 0;
}