#include <iostream>
using namespace std;
int main()
{
    int num[20];
    int i = 0;
    while (cin >> num[i])
    {
        if (cin.get() == '\n')
            break;
        i++;
    }
}