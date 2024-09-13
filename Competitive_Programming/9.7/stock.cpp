#include <vector>
#include <iostream>
#include <math.h>
#include <initializer_list>
using namespace std;

double retMax(vector<double> &in){
    double max = 0;
    for(int i = 0; i < in.size(); i++){
        if(in[i] > max){
            max = in[i];
        }
    }

    return max;
}
int main(){
    int cases, days;
    double cost, totalCash, tmp;

    double cost1, cost2, left1, left2;
    double new1, new2;
    long long int shares1, shares2;

    cin >> cases;

    for(int t = 0; t < cases; t++){
        cin >> days >> cost >> totalCash;
        vector<double> a, b;
        vector<double> best(days);

        best[0] = totalCash;

        for(int i = 0; i < days; i++){
            cin >> tmp;
            a.push_back(tmp);
        }

            for(int i = 0; i < days; i++){
            cin >> tmp;
            b.push_back(tmp);
        }

        for(int i = 1; i < days; i++){
            for(int j = 0; j < i; j++){
                shares1 = floor((best[j] - cost) / a[j]);
                shares2 = floor((best[j] - cost) / b[j]);

                left1 = best[j] - (shares1 * a[j] + cost);
                left2 = best[j] - (shares2 * b[j] + cost);

                new1 = shares1 * a[i] + left1 - cost;
                new2 = shares2 * b[i] + left2 - cost;

                vector<double> in;
                in.push_back(new1);
                in.push_back(new2);
                in.push_back(best[j]);
                in.push_back(best[i]);

                best[i] = retMax(in);
            }
        }

        printf("%0.2lf\n", best[days - 1]);

        a.clear();
        b.clear();
    }
}