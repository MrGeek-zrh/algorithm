#include <algorithm>
#include <iostream>

using namespace std;

const int N = 1000, M = 10010;

int f[M];
int v[N];
int w[N];

int main()
{
    int n, m;
    cin >> n >> m;
    int a, b, s;
    // 对物品打包以后，包裹的数量
    int cnt = 0;
    // 对物品按照1,2,4,8的数量进行打包
    for (int i = 1; i <= n; i++) {
        cin >> a >> b >> s;
        int k = 1;
        // 对物品i进行打包
        while (k <= s) {
            cnt++;
            v[cnt] = k * a;
            w[cnt] = k * b;
            // 打包成功，更新计数
            s -= k;
            k *= 2;
        }
        if (s > 0) {
            cnt++;
            v[cnt] = s * a;
            w[cnt] = s * b;
        }
    }

    n = cnt;
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= v[i]; j--) {
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }
    cout << f[m];

    return 0;
}