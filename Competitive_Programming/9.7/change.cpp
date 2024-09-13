#include <iostream>
#include <vector>
using namespace std;
int main(){
    int n = 0;
    cin >> n;
    int x;
    for(int i = 0; i < n; i++){
        cin >> x;
        int qCount = 0;
        int dCount = 0;
        int nCount = 0;
        int pCount = 0;
        while(x >= 25){
            qCount++;
            x -= 25;
        }
        while(x >= 10){
            dCount++;
            x -= 10;
        }
        while(x >= 5){
            nCount++;
            x -= 5;
        }
        while(x >= 1){
            pCount++;
            x -= 1;
        }

        cout << i + 1 << " " << qCount << " QUARTER(S), " << dCount << " DIME(S), " << nCount << " NICKEL(S), " << pCount << " PENNY(S)" << endl;
    }
    return 0;
}