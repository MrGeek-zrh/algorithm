#include <iostream>
#include <queue>
#include <string>
#include <map>

using namespace std;

queue<string> a;
map<string, int> times_map;

int child_offset_x[4] = { -1, 1, 0, 0 };
int child_offset_y[4] = { 0, 0, -1, 1 };

int code_num(int x, int y)
{
    return 3 * x + y;
}

void decode_num(int num, int *x, int *y)
{
    *x = num / 3;
    *y = num % 3;
}

string swap_get_child_str(string s, int x_idx, int child_idx)
{
    char tmp = s[x_idx];
    s[x_idx] = s[child_idx];
    s[child_idx] = tmp;
    return s;
}

// str没在map中作为key出现过
bool unvisited(string str)
{
    return times_map.count(str) == 0;
}

// 获取到当前x所在位置的所有子串，如果这些子串不在队列中，将其放入到队列
// 还有满足条件的子串，返回true；没有，返回false
bool get_child_str_of_x(string s, int x_idx)
{
    int times = times_map[s];
    int x, y;
    decode_num(x_idx, &x, &y);
    for (int i = 0; i < 4; i++) {
        int child_x = x + child_offset_x[i];
        int child_y = y + child_offset_y[i];
        if (child_x >= 0 && child_x <= 2 && child_y >= 0 && child_y <= 2) {
            int child_idx = code_num(child_x, child_y);
            string child_str = swap_get_child_str(s, x_idx, child_idx);
            if (unvisited(child_str)) {
                a.push(child_str);
                times_map[child_str] = times + 1;
                if (child_str == "12345678x") {
                    cout << times_map[child_str];
                    return true;
                }
            }
        }
    }
    return false;
}

int get_x_idx(string s)
{
    int i = 0;
    while (s[i] != 'x') {
        i++;
    }
    return i;
}

int main(int argc, char *argv[])
{
    string str;
    char c;
    int current_x_idx;
    for (int i = 0; i < 9; i++) {
        cin >> c;
        str += c;
        if (c == 'x') {
            current_x_idx = i;
        }
    }
    a.push(str);
    times_map[str] = 0;

    while (!a.empty()) {
        string s = a.front();
        a.pop();
        current_x_idx = get_x_idx(s);
        // 拿到当前x所在位置的所有孩子子串
        if (get_child_str_of_x(s, current_x_idx)) {
            break;
        }
    }

    return 0;
}
