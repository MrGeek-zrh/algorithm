#include <iostream>
#include <algorithm>
#include <pthread.h>
#include <string>

using namespace std;

const int N = 100100;

int n;
int e[N], l[N], r[N], idx;

// 在i右边插入x
void insert(int i, int x)
{
    e[idx] = x;
    l[idx] = i;
    r[idx] = r[i];
    l[r[i]] = idx;
    r[i] = idx;
    idx++;
}

void del(int i)
{
    int pre = l[i];
    int next = r[i];
    r[pre] = next;
    l[next] = pre;
}

int main()
{
    // 0表示左边界，1表示右边界，这两个的e数组不存储任何值
    // r[0]存储的是双链表的头结点，l[1]存储的是双链表的尾节点
    // 头结点的后继指针指向尾节点
    // 尾节点的前驱指针指向头结点
    cin >> n;
    r[0] = 1, l[1] = 0;
    idx = 2;
    while (n--) {
        string op;
        cin >> op;
        int k, x;
        if (op == "L") {
            cin >> x;
            insert(0, x);
        } else if (op == "R") {
            cin >> x;
            insert(l[1], x);
        } else if (op == "D") {
            cin >> k;
            // 函数接收的都是索引，所以这里需要转换一下 索引 = k-1+2 = k+1
            del(k + 1);
        } else if (op == "IL") {
            cin >> k >> x;
            insert(l[k + 1], x);
        } else if (op == "IR") {
            cin >> k >> x;
            insert(k + 1, x);
        }
    }
    for (int t = r[0]; t != 1; t = r[t]) {
        cout << e[t] << " ";
    }
    return 0;
}