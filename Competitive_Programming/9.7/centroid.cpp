#include <iostream>
#include <vector>
using namespace std;
int main(){
    int n = 0;
    double tX, tY;
    int NumX = 0;
    int denom = 0;
    int NumY = 0;
    int a, b ,c;
    int tCase = 1;

    while(n > -1){
        cin >> n;

        if(n < 0){
            break;
        }

        for(int i = 0; i < n; i++){
            cin >> a >> b >> c;
            NumY += c*b;
            NumX += c*a;
            denom += c;
        }
        tX = 1.0*NumX/denom;
        tY = 1.0*NumY/denom;

        cout << "Case " << tCase++ << ": ";
        printf("%0.2lf %0.2lf\n", tX, tY);

        NumX = NumY = denom = 0;

    }

    return 0;
}