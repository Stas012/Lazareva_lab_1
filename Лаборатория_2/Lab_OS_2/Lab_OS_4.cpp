#include <iostream>

using namespace std;

int main()
{
    int a = 0, b = 3, c = 3;

    for (int i = 0; i < 1000000000; i++) {
        a += 2*b + c - i;
    }

    cout << a << endl;
    return 0;
}
/*1653374720*/
