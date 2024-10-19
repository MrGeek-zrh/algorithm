// 统计数字的二进制表示中1的数量
#include <cstdio>
#include <iostream>

using namespace std;

const int N = 1e5 + 10;
int a[N] = { 0 };

int lowbit(int a)
{
    return a & -a;
}

int count(int a)
{
    int cnt = 0;

    while (a) {
        a -= lowbit(a);
        cnt++;
    }
    return cnt;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        int num_one = count(a[i]);
        printf("%d ",num_one);
    }
    return 0;
}