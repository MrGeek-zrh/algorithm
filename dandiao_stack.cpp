// 单调栈
#include <cstdio>
#include <iostream>

using namespace std;

const int N = 100010;
int a[N] = { 0 };
int m[N] = { -1 };

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if (i == 0) {
            printf("-1 ");
            m[i] = -1;
            continue;
        } else {
            int j;
            for (j = i - 1; j >= 0;) {
                if (a[i] > a[j]) {
                    printf("%d ", a[j]);
                    m[i] = j;
                    break;
                } else {
                    j = m[j];
                    continue;
                }
            }
            if (j == -1) {
                printf("-1 ");
            }
        }
    }
    return 0;
}