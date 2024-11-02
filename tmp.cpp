// 字符串hash-暴力解
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int N = 100010;
char a[N] = { '\0' };

bool compare(int l1, int r1, int l2, int r2)
{
    int offset = 0;
    int length1 = r1 - l1 + 1;
    int length2 = r2 - l2 + 1;
    if (length1 != length2) {
        return false;
    }
    while (offset < length1 && offset < length2) {
        if (a[l1 + offset] != a[l2 + offset]) {
            return false;
        }
        offset++;
    }
    return true;
}

int main()
{
    int n, m;
    scanf("%d %d\n", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%c", &a[i]);
    }

    int l1, r1, l2, r2;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &l1, &r1, &l2, &r2);
        printf("%s\n", compare(l1, r1, l2, r2) ? "Yes" : "No");
    }
    return 0;
}