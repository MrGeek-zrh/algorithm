#include <algorithm>
#include <iostream>

using namespace std;

const int N = 1000 + 10;
int a[N];
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
        for (int j = v; j >= ve[i]; j--) {
            a[j] = max(a[j], a[j - ve[i]] + we[i]);
        }
    }
    cout << a[v];
    return 0;
}