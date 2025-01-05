#include <algorithm>
#include <iostream>

using namespace std;

const int N = 1000 + 10;
int a[N][N];
int ve[N];
int we[N];

int main()
{
    int n, v;
    cin >> n >> v;
    for (int i = 1; i <= n; i++) {
        cin >> ve[i] >> we[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= v; j++) {
            a[i][j] = a[i - 1][j];
            if (j >= ve[i]) {
                a[i][j] = max(a[i][j], a[i - 1][j - ve[i]] + we[i]);
            }
        }
    }
    cout << a[n][v];
    return 0;
}