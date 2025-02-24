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
int a[N], hh, tt = -1;

int main()
{
    cin >> n;
    string str;
    int x;
    while (n--) {
        cin >> str;
        if (str == "push") {
            cin >> x;
            tt++;
            a[tt] = x;
        } else if (str == "pop") {
            hh++;
        } else if (str == "empty") {
            cout << (hh <= tt ? "NO" : "YES") << endl;
        } else {
            cout << a[hh] << endl;
        }
    }
    return 0;
}