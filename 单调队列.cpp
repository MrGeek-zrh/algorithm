// 单调队列：滑动窗口
#include <cstdio>
#include <iostream>
#include <string.h>
using namespace std;

const int N = 1000010;
int a[N] = { 0 };

int q[N] = { 0 };
int head = 0, tail = 0;

bool empty()
{
    return tail == head;
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < k; i++) {
        if (empty()) {
            q[tail] = i;
            tail++;
            continue;
        }
        while ((a[i] <= a[q[tail - 1]]) && !empty()) {
            tail--;
        }
        q[tail] = i;
        tail++;
    }
    printf("%d ", a[q[head]]);
    for (int j = k; j < n; j++) {
        if (q[head] < j - k + 1) {
            head++;
        }
        while ((a[j] <= a[q[tail - 1]]) && !empty()) {
            tail--;
        }
        q[tail] = j;
        tail++;
        printf("%d ", a[q[head]]);
    }

    memset(q, 0, N);
    for (int i = 0; i < k; i++) {
        if (empty()) {
            q[tail] = i;
            tail++;
            continue;
        }
        while ((a[i] >= a[q[tail - 1]]) && !empty()) {
            tail--;
        }
        q[tail] = i;
        tail++;
    }
    printf("\n");
    printf("%d ", a[q[head]]);
    for (int j = k; j < n; j++) {
        if (q[head] < j - k + 1) {
            head++;
        }
        while ((a[j] >= a[q[tail - 1]]) && !empty()) {
            tail--;
        }
        q[tail] = j;
        tail++;
        printf("%d ", a[q[head]]);
    }
    return 0;
}