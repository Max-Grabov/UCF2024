#include <iostream>
using namespace std;

int main(){
    int a1, a2, a3;
    int b1, b2, b3;

    cin >> a1 >> a2 >> a3 >> b1 >> b2 >> b3;

    if(a1 + 2*a2 + 3*a3 == b1 + 2*b2 + 3*b3){
        cout << 0;
        return 0;
    }
    else if(a1 + 2*a2 + 3*a3 > b1 + 2*b2 + 3*b3){
        cout << 1;
        return 0;
    }
    cout << 2;
    return 0;
}