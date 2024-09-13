#include <iostream>
#include <vector>
using namespace std;
int main(){
    int n = 0;
    int k;
    vector<long long> v;
    long long sum = 0;

    cin >> n;
    v.push_back(0);
    for(int i = 1; i < 302; i++){
        v.push_back(i + v[i-1]);
    }

    for(int i = 0; i < n; i++){
        cin >> k;
        for(int j = 0; j <= k; j++){
            sum += (j) * v[j + 1];
        }
        cout << i+1 << " " << k << " " << sum << endl;
        sum = 0;
    }
    return 0;
}