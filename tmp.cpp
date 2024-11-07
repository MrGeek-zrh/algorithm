#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

const int N = 10;

enum { UNVISITED, VISITED, CLOSED };

int visited[N][N] = { { UNVISITED } };

// 存储符合条件的数组
vector<pair<int, int>> pos;
// 已经收集到的元素个数，到达n的时候，说明一轮就收集满了
int current_length = 0;

int n;

double ra(int x1, int y1, int x2, int y2)
{
    return abs((y1 - y2) * 1.0 / (x1 - x2));
}

bool ratio_not_one_or_zero(int x, int y)
{
    for (int i = 0; i < pos.size(); i++) {
        double ratio = ra(pos[i].first, pos[i].second, x, y);
        if (ratio == 1.0 || ratio == 0.0) {
            return false;
        }
    }
    return true;
}

// 这里增加筛选条件，除了需要是UNVISITED，还需要满足和当前的点的斜率绝对值不是1
// 这里的next所在的行是root所在行的下一行
bool has_unvisited(int row, int *next)
{
    for (int i = 1; i <= n; i++) {
        if (visited[row][i] == UNVISITED && ratio_not_one_or_zero(row, i)) {
            *next = i;
            return true;
        }
    }
    return false;
}

void print()
{
    for (int i = 0; i < pos.size(); i++) {
        cout << pos[i].first << " " << pos[i].second << endl;
    }
    printf("\n");
}

void clear_visited(int root)
{
    for (int i = 1; i <= n; i++) {
        visited[root][i] = UNVISITED;
    }
}

void dfs(int row, int root)
{
    int next = UNVISITED;
    while (row < n && has_unvisited(row + 1, &next)) {
        current_length++;
        pos.push_back(make_pair(row + 1, next));

        visited[row + 1][next] = VISITED;
        dfs(row + 1, next);
        visited[row + 1][next] = CLOSED;
    }
    if (!has_unvisited(row + 1, &next) || row == n) {
        if (current_length == n) {
            print();
        }
        current_length--;
        pos.pop_back();
        clear_visited(root);
        return;
    }
}

int main(int argc, char *argv[])
{
    scanf("%d", &n);

    for (int root = 1; root <= n; root++) {
        memset(visited, UNVISITED, sizeof(int) * N * N);

        dfs(1, root);
    }

    return 0;
}
