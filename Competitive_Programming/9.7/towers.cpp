#include <iostream>
#include <math.h>
using namespace std;

int main(){
    int n = 1;
    long long k = 1;
    long long test = 1;

    while(cin >> k >> n){
        if(n == 0 && k == 0) break;
        cout << "Case " << test++ << ": ";

        long long bit = 1;
        while(!(k & bit) && bit <= k){
            bit = bit << 1;
        }

        long long disk = ((long long)log2(bit) + 1);

        long long diff = k / (bit << 1);

        if(!(n % 2)){
            if((disk % 2)){
                switch(diff % 3){
                case 0:
                    cout << disk << " A B" << endl;
                    break;

                case 1:
                    cout << disk << " B C" << endl;
                    break;
                case 2:
                    cout << disk << " C A" << endl;
                    break;
                }
            }

            else {
                switch(diff % 3){
                case 0:
                    cout << disk << " A C" << endl;
                    break;

                case 1:
                    cout << disk << " C B" << endl;
                    break;
                case 2:
                    cout << disk << " B A" << endl;
                    break;
                }
            }
        }

        else {
            if(!(disk % 2)){
                switch(diff % 3){
                case 0:
                    cout << disk << " A B" << endl;
                    break;

                case 1:
                    cout << disk << " B C" << endl;
                    break;
                case 2:
                    cout << disk << " C A" << endl;
                    break;
                }
            }

            else {
                switch(diff % 3){
                case 0:
                    cout << disk << " A C" << endl;
                    break;

                case 1:
                    cout << disk << " C B" << endl;
                    break;
                case 2:
                    cout << disk << " B A" << endl;
                    break;
                }
            }
        }
    }
}