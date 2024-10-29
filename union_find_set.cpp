// 并查集
#include <cstdio>
#include <iostream>

using namespace std;

const int N = 100010;
int p[N] = { 0 };

int query(int a)
{
    // 这里可以进行优化，除了通过a = p[a] ，递归的往上找集合的根节点以外，还可以同时对这棵树进行扁平化压缩，
    // 虽然下面的写法， 在每次进行压缩的时候，并不能立刻压缩成一个扁平的树，但是经过多次压缩以后，就能变成一个很扁平的树
    int x;
    while (p[a] != a) {
        x = a;
        a = p[a];
        p[x] = p[a];
    }
    return a;
}

void merge(int a, int b)
{
    int p_a = query(a);
    int p_b = query(b);
    if (p_a != p_b) {
        p[p_b] = p_a;
    }
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    char op;
    int a, b;
    for (int i = 0; i < m; i++) {
        scanf("\n%c %d %d", &op, &a, &b);
        // 如果当前节点是第一次插入，需要先修改他为根节点
        if (p[a] == 0) {
            p[a] = a;
        }
        if (p[b] == 0) {
            p[b] = b;
        }
        switch (op) {
            case 'M':
                merge(a, b);
                break;
            case 'Q':
                if (query(a) == query(b)) {
                    printf("Yes\n");
                } else {
                    printf("No\n");
                }
                break;
            default:
                break;
        }
    }

    return 0;
}
