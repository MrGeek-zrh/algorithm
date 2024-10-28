// trie数组
// 核心就是用二维数组存多节点数的子节点，本质上和单链表没什么区别
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

const int N = 100010;
char a[N] = { 0 };
// 当前这个节点的儿子节点数组
int son[N][26] = { 0 };
// 以当前这个点结尾的字符串有多少个
int cnt[N] = { 0 };
// current idx
int current_idx = 0;

void insert(char *str)
{
    int parent = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        int son_idx = str[i] - 'a';
        if (son[parent][son_idx] == 0) {
            current_idx++;
            a[current_idx] = str[i];
            son[parent][son_idx] = current_idx;
        }
        parent = son[parent][son_idx];
    }
    cnt[parent]++;
}

int query(char *str)
{
    int parent = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        int son_idx = str[i] - 'a';
        if (son[parent][son_idx] == 0) {
            return 0;
        } else {
            parent = son[parent][son_idx];
        }
    }
    return cnt[parent];
}

int main()
{
    int n;
    scanf("%d", &n);
    char op;
    char str[N];
    for (int i = 0; i < n; i++) {
        cin >> op >> str;
        switch (op) {
            case 'I':
                insert(str);
                break;
            case 'Q':
                printf("%d\n", query(str));
                break;
            default:
                break;
        }
    }
    return 0;
}