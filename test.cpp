#include <iostream>
#include <list>

using namespace std;

int main()
{
    list<int> a = {1,2,3,4,5};
    list<int> b = {6,7,8,9};

    a.splice(a.end(), b);

    for (auto x : a) cout << x << endl;
    for (auto x : b) cout << x << endl;

    return 0;
}
