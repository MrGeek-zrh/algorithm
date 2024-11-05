// dfs实现数字全排列
#include <cstdio>
#include <cstring>
#include <stack>

using namespace std;

enum { BAN_VISITED = -1, UN_VISITED, VISITED, CLOSED };
const int N = 8;
int visited[N][N] = { { UN_VISITED } };

stack<int> st;

int current_idx = 1;
int child_idx = 2;

int current_length = 0;
int a[N] = { 0 };

int n;

// unvisited就是标志位是UNVISITED，其他的都不是未被访问
bool has_unvisited(int root, int *next)
{
    *next = BAN_VISITED;
    for (int i = 1; i <= n; i++) {
        if (visited[root][i] == UN_VISITED) {
            *next = i;
            return true;
        }
    }
    return false;
}

// 除了CLOSED，其他都拷贝
void copy_visited_flag(int current, int next)
{
    for (int i = 1; i <= n; i++) {
        if (visited[current][i] != CLOSED) {
            visited[next][i] = visited[current][i];
        }
    }
}

// 除了CLOSED，其他都清空
void clear_visited(int current)
{
    for (int i = 1; i <= n; i++) {
        if (visited[current][i] != BAN_VISITED) {
            visited[current][i] = UN_VISITED;
        }
    }
}

void print()
{
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void dfs(int root)
{
    int next = BAN_VISITED;
    while (has_unvisited(root, &next)) {
        a[current_length++] = next;
        visited[root][next] = VISITED;
        // 拷贝被标记为VISITED的位置
        copy_visited_flag(root, next);
        dfs(next);
        visited[root][next] = CLOSED;
    }
    if (!has_unvisited(root, &next)) {
        if (current_length == n) {
            print();
        }
        current_length--;
        clear_visited(root);
        return;
    }
}

int main(int argc, char *argv[])
{
    scanf("%d", &n);

    // 图的对角线全部设为-1，因为一个点不可能访问自己
    for (int root = 1; root <= n; root++) {
        memset(visited, UN_VISITED, sizeof(int) * N * N);
        current_length = 0;
        for (int i = 1; i <= n; i++) {
            visited[i][i] = BAN_VISITED;
            visited[i][root] = BAN_VISITED;
        }

        a[current_length++] = root;
        dfs(root);
    }
    return 0;
}
