#include <iostream>
using namespace std;
int main(){
    int a, b, d;
    cin >> a >> b >> d;

    if((a*b % 12 == 0)){
        cout << d*(a*b)/12;
    }
    else {
        cout << d*((a*b)/12 + 1);
    }

    return 0;
}