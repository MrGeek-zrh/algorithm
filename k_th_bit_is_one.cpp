#include <iostream>
using namespace std;

int main()
{
    int x;
    cin >> x;
    int k;
    cin >> k;

    int is_one = (x >> k) & 1;
    
    cout << is_one;

    return 0;
}