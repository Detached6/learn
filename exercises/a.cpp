#include <bits/stdc++.h>
using namespace std;

class A {
public:
    static int x;
    A() {
        x ++ ;
    }
};

int A::x = 0;

int main() {
    vector<bool> vec(100, true);
    cout << sizeof (vec) << endl;
    cout << sizeof (bool) << endl;
}