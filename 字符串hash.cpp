#include <cstdio>
#include <cmath>

using namespace std;

const int N = 100010;
char a[N] = { '\0' };

const int P = 131;

unsigned long long ha[N] = { 0 };

// 求字符串的所有前缀的hash值，结果放在ha数组中
void get_prefix_hash(int n)
{
    for (int i = 1; i <= n; i++) {
        // TODO:
        // FIXME:
        // 通过debug，发现这里i不是++，而是i += 2，为啥？没搞懂
        ha[i] = ha[i - 1] * P + a[i];
    }
}

// a b c d
unsigned long long h(int l, int r)
{
    return ha[r] - (unsigned long long)(ha[l - 1] * (unsigned long long)pow(P, r - l + 1));
}

bool compare(int l1, int r1, int l2, int r2)
{
    return h(l1, r1) == h(l2, r2);
}

int main(int argc, char *argv[])
{
    int n, m;
    scanf("%d %d\n", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%c", &a[i]);
    }
    get_prefix_hash(n);
    int l1, r1, l2, r2;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &l1, &r1, &l2, &r2);
        printf("%s\n", compare(l1, r1, l2, r2) ? "Yes" : "No");
    }
    return 0;
}
