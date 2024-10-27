// 831. KMP字符串
#include <cstdio>
#include <iostream>
#include <stdexcept>

using namespace std;

const int N = 100010;
const int M = 1000010;
char p[N] = { 0 };
char s[M] = { 0 };

int ne[M] = { 0 };

int main()
{
    int n;
    scanf("%d\n", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%c", &p[i]);
    }

    int m;
    scanf("%d\n", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%c", &s[i]);
    }

    // 求最长公共子缀的长度
    // 是求被匹配串的
    // length是最长公共子前缀的长度
    // a b a b a c
    //     a b a b a
    for (int i = 2, length = 0; i <= n; i++) {
        while (length && p[i] != p[length + 1]) {
            length = ne[length];
        }
        if (p[i] == p[length + 1]) {
            length++;
        }
        ne[i] = length;
    }

    for (int i = 1, length = 0; i <= m; i++) {
        while (length && s[i] != p[length + 1]) {
            length = ne[length];
        }
        if (s[i] == p[length + 1]) {
            length++;
        }
        if (length >= n) {
            printf("%d ", i - length);
            length = ne[length];
        }
    }
    return 0;
}