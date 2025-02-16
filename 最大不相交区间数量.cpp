#include <algorithm>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

const int N = 100010;
int a[N];

int tmp[N];

/**
利用两个指针（通常称作左指针 left 与右指针 right）维护一个「无重复数字」的子区间，对于新加入的数字：
将其计数加一；
如果发现某个数字的计数超过 1，则说明窗口内有重复数字，此时需要不断移动左指针并减少对应计数，直到窗口内不含重复数字。
在移动过程中，持续更新最长的窗口大小，最后输出最大值即可。整个过程只需要遍历一次数组，故时间复杂度为 O(n)。
 */
int main()
{
    int n;
    cin >> n;
    for (int i = 0, j = 0; i < n; i++) {
        cin >> a[i];
    }
    int left = 0, res = 0;
    for (int right = 0; right < n; right++) {
        tmp[a[right]]++;
        // 这里应该是while，而不是if
        while (tmp[a[right]] > 1) {
            tmp[a[left]]--;
            left++;
        }
        res = max(res, right - left + 1);
    }
    cout << res;
    return 0;
}
