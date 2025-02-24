#include <cctype>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <algorithm>
#include <pthread.h>
#include <queue>
#include <string>
#include <utility>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

const int N = 100100;

int n;

stack<int> num;
stack<int> op;

unordered_map<char, int> h { { '+', 1 }, { '-', 1 }, { '*', 2 }, { '/', 2 } };

void eval()
{
    int b = num.top();
    num.pop();
    int a = num.top();
    num.pop();

    char p = op.top();
    op.pop();

    int res = 0;
    switch (p) {
        case '+':
            res = a + b;
            break;
        case '-':
            res = a - b;
            break;
        case '*':
            res = a * b;
            break;
        case '/':
            res = a / b;
            break;
    }
    num.push(res);
}

int main()
{
    string str;
    cin >> str;
    char c;
    for (int i = 0; i < str.size(); i++) {
        c = str[i];
        if (isdigit(c)) {
            // 继续遍历字符串，以形成一个完整的数字
            int x = 0, j = i;
            while (j < str.size() && isdigit(str[j])) {
                x = x * 10 + str[j] - '0';
                j++;
            }
            num.push(x);
            // 这里是避免后面i++多加一次
            i = j - 1;
        } else if (str[i] == '(') {
            // 左括号直接入栈
            op.push(str[i]);
        } else if (str[i] == ')') {
            // 右括号，开始从数字栈中弹栈进行计算
            while (op.top() != '(') {
                eval();
            }
            // 从右往左计算完毕，将剩下的左括号弹出栈
            // 左括号出栈
            op.pop();
        } else {
            while (op.size() > 0 && op.top() != '(' && h[op.top()] >= h[str[i]]) {
                eval();
            }
            op.push(str[i]);
        }
    }
    while (op.size() > 0) {
        eval();
    }
    cout << num.top();
    return 0;
}