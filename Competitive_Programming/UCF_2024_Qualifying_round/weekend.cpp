#include <iostream>
#include <vector>
using namespace std;

int determineAdd(int j, int cAmount, int nAmount, int eAmount, long long int c, long long int n, long long int e){
    if(j < cAmount){
        return c;
    }
    if(j >= cAmount && j < cAmount + nAmount){
        return n;
    }
    return e;
}
int main(){
    long long int low, high;
    long long int c, n, e;

    int cAmount, nAmount, eAmount;

    cin >> low >> high;
    cin >> c >> n >> e;
    cin >> cAmount >> nAmount >> eAmount;

    int total = cAmount + nAmount + eAmount;

    vector<vector<long long int>> dp(total, vector<long long int>(total, 0));

    long int count = 0;
    for(int i = 0; i < total; i++){
        for(int j = 0; j < total; j++){
            if(!j){
                dp[i][j] = determineAdd(i, cAmount, nAmount, eAmount, c, n, e);
                continue;
            }
            if(i == j){
                dp[i][j] = dp[i][j-1] + c;

            }
            else {
                dp[i][j] = dp[i][j-1] + determineAdd(j, cAmount, nAmount, eAmount, c, n, e);
            }
            if(dp[i][j] >= low && dp[i][j] <= high){
                count++;
            }
        }


    }

    // for(int i = 0; i < total; i++){
    //     for(int j = 0; j < total; j++){
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    //cout << count << endl;
    printf("%lf", (1.0*count)/(total*total - total));
}