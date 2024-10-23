#include <cstdio>
#include <iostream>

using namespace std;

const int N = 1000010;

int a[N] = { 0 };

int max_arr[N] = { 0 };
int min_arr[N] = { 0 };

int min_val, max_val;
int min_idx = 0, max_idx = 0;
int second_min_val, second_max_val;
int second_min_idx = 0, second_max_idx = 0;

void get_max_min(int l, int r)
{
    for (int i = l; i <= r; i++) {
        if (a[i] >= max_val) {
            max_val = a[i];
            max_idx = i;
        } else if (a[i] < max_val && a[i] >= second_max_val) {
            second_max_val = a[i];
            second_max_idx = i;
        } else if (a[i] <= min_val) {
            min_val = a[i];
            min_idx = i;
        } else if (a[i] > min_val && a[i] <= second_min_val) {
            second_min_val = a[i];
            second_min_idx = i;
        }
    }
}

bool in_range(int k, int l, int r)
{
    return k <= r && k >= l;
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    max_val = min_val = second_max_val = second_min_val = a[0];
    get_max_min(0, k - 1);
    max_arr[0] = max_val;
    min_arr[0] = min_val;
    for (int i = 1; i <= n - k; i++) {
        int j = i + k - 1;
        // 如果最值不在这个区间，看看是最大值不在了还是最小值不在了，然后更新对应的最值索引和最值的记录
        if (!in_range(min_idx, i, j)) {
            // 最小值不在了，现将最大值和新的数进行比较
            // 新来的更加大
            if (max_val <= a[j]) {
                // 更新最大值
                second_max_val = max_val;
                second_max_idx = max_idx;
                max_val = a[j];
                max_idx = j;
                // 更新最小值：最小值就是原来的第二小的值
                min_val = second_min_val;
                min_idx = second_min_idx;
                // second_min_val = ;
                // second_min_idx = ;
                //新来的没有最大值大，最大值就不，变，接下来比较最小值
                // 只需要和第二小的值进行比较就行了
            } else {
                min_val = a[j] <= second_min_val ? a[j] : second_min_val;
                min_idx = a[j] <= second_min_val ? j : second_min_idx;
            }
        } else if (!in_range(max_idx, i, j)) {
            // 最大值不在了
            // 说明最小值还在小区间里
            // 先比较最小值和新来的
            if (a[j] <= min_val) {
                second_min_val = min_val;
                second_min_idx = min_idx;
                min_val = a[j];
                min_idx = j;
                // 接下来处理最大值
                // 只需要将第二大的变成最大值就行了
                max_val = second_max_val;
                max_idx = second_max_idx;
            } else {
                // 新来的没有最小值小，最小值不变，直接处理最大值
                // 将新来的数和现在的第二大的值进行比较
                max_val = a[j] >= second_max_val ? a[j] : second_max_val;
                max_idx = a[j] >= second_max_val ? j : second_max_idx;
            }
        }
        // 如果最值都在这个区间，只需要将最大值和最小值和新进来的这个数进行比较就行了
        else {
            if (a[j] >= max_val) {
                max_val = a[j];
                max_idx = j;
            } else if (a[j] <= min_val) {
                min_val = a[j];
                min_idx = j;
            }
        }
        max_arr[i] = max_val;
        min_arr[i] = min_val;
    }

    for (int i = 0; i <= n - k; i++) {
        printf("%d ", min_arr[i]);
    }

    printf("\n");

    for (int i = 0; i <= n - k; i++) {
        printf("%d ", max_arr[i]);
    }
    return 0;
}