#include <iostream>

using namespace std;

bool is_zhishu(int x)
{
    if (x < 2) {
        return false;
    }
    for (int i = 2; i <= x / i; i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

int main()
{
    int n;
    cin >> n;
    int x;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        cout << (is_zhishu(x) ? "Yes" : "No") << endl;
    }
    return 0;
}