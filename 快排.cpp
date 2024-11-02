#include <cstdio>
#include <iostream>

using namespace std;

const int N = 100010;
int a[N] = { 0 };
int b[N] = { 0 };

int length = 0;

void quick_sort(int l, int r)
{
    if (l >= r) {
        return;
    }

    int mid = (l + r) >> 1;
    quick_sort(l, mid);
    quick_sort(mid + 1, r);
    int index = 0;
    int len = r - l + 1;
    // 先将数据在新数组中排好序，然后再拷贝会原宿主
    int i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) {
            b[index] = a[i];
            index++;
            i++;
        }
        if (a[i] >= a[j]) {
            b[index] = a[j];
            index++;
            j++;
        }
    }

    while (i <= mid) {
        b[index] = a[i];
        index++;
        i++;
    }

    while (j <= r) {
        b[index] = a[j];
        index++;
        j++;
    }
    for (int i = 0; i < index; i++) {
        a[l + i] = b[i];
    }
}

void print()
{
    for (int i = 0; i < length; i++) {
        printf("%d ", a[i]);
    }
}

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        length++;
    }
    quick_sort(0, n - 1);
    print();
    return 0;
}
