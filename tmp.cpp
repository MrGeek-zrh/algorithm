// 区间合并
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;
vector<PII> ranges;

bool repeated(int i, int j)
{
    return (ranges[i].second >= ranges[j].first);
}

int main()
{
    int n;
    cin >> n;

    int l, r;
    for (int i = 0; i < n; i++) {
        cin >> l >> r;
        ranges.push_back({ l, r });
    }
    // 先对l进行排序，小的放前面
    sort(ranges.begin(), ranges.end());

    int num = 0;
    for (int i = 0; i < n;) {
        int j;
        for (j = i + 1; j < n && repeated(i, j); j++) {
            if (ranges[j].second >= ranges[i].second) {
                ranges[i].second = ranges[j].second;
            }
        }
        i = j;
        num++;
    }

    cout << num;

    return 0;
}
