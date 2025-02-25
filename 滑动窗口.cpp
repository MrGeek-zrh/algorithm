#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <algorithm>
#include <pthread.h>
#include <queue>
#include <string>
#include <utility>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

const int N = 1000100;

int n;
// 队列中保存的是下标
int a[N], q[N];
int hh = 0, tt = -1;

int main()
{
    int k;
    scanf("%d %d", &n, &k);

    // 求最小值
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        // 目前的队首在移动过程中被移出去了，需要将队首hh++
        if (hh <= tt && i - k + 1 > q[hh]) {
            hh++;
        }
        // 队尾入队的时候，如果新元素更小，就将现在的队尾元素删去，然后将当前元素入队
        while (hh <= tt && a[q[tt]] > a[i]) {
            tt--;
        }
        // 新元素不比当前队尾小了，可以加入队列了
        tt++;
        q[tt] = i;
        if (i + 1 >= k) {
            printf("%d ", a[q[hh]]);
        }
    }

    printf("\n");

    // 求最大值
    hh = 0, tt = -1;
    for (int i = 0; i < n; i++) {
        // 目前的队首在移动过程中被移出去了，需要将队首hh++
        if (hh <= tt && i - k + 1 > q[hh]) {
            hh++;
        }
        while (hh <= tt && a[q[tt]] < a[i]) {
            tt--;
        }
        tt++;
        q[tt] = i;
        if (i + 1 >= k) {
            printf("%d ", a[q[hh]]);
        }
    }

    return 0;
}