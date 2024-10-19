// 最长连续不重复子序列
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 100005;

int a[N] = { 0 };
// tmp 数组保存每个下标出现的次数
int tmp[N] = { 0 };

int res = 1;
int idx_begin = 0, idx_end = 0;

bool have_repeat(int j, int i)
{
    std::memset((int *)tmp, 0, N);
    // 感觉可能是memset有点问题
    for (int k = j; k <= i; k++) {
        tmp[a[k]] += 1;
        // 如果下标出现了两次，说明这个区间有重复
        // 如果当前区间有重复，j要++
        if (tmp[a[k]] > 1) {
            // 有重复元素，继续看更小区间,也就是j++
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);

    for (int i = 0, j = 0; i < n; i++) {
        scanf("%d", &a[i]);

        for (; j <= i; j++) {
            if (!have_repeat(j, i)) {
                res = std::max(res, i - j + 1);
                // printf("idx_begin：%d\t\tidx_end: %d\t\tlength: %d\n", j, i, i - j + 1);
                break;
            }
        }
    }
    printf("%d", res);
}
