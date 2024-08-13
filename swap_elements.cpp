#include <iostream>
using namespace std;

int main() {
    int a,b;
    cout<<"enter 2 nos: ";
    cin>> a >> b;
    //swapping
    a=a^b;
    b=a^b;
    a=a^b;
    cout << "a = " << a << " b = " << b;
}