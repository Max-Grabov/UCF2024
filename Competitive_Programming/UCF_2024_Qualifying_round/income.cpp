#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    long int n;
    double k;
    double sum = 0;

    cin >> n;
    vector<double> vals;
    for(int i = 0; i < n; i++){
        cin >> k;
        vals.push_back(k);
        sum += k;
    }

    double lim = sum/(1.0*n);
    double e = 0;

    sort(vals.begin(), vals.end(), greater<double>());

    for(int i = 0; i < n; i++){
        if(vals[i] <= lim){
            printf("%lf", 100*(e/sum - 1.0*(i)/n));
            return 0;
        }
        e += vals[i];
    }
}
