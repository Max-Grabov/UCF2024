#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
using namespace std;
int main(){
    int c = 0;
    vector<long long> f, ans;
    f.push_back(1);

    for(int i = 2; i < 100; i++){
        for(int j = 0; j < i; j++){
            ans.push_back(pow(2, i - 1));
        }
    }
    for(int i = 1; i < 1001; i++){
        f.push_back(f[i - 1] + ans[i - 1]);
    }

    // for(int i = 0; i < 1001; i++){
    //     cout << ans[i] << endl;
    // }

    int k = 0;
    string s;
    char ch, ch2;

    // for(int i = 1; i < 1000; i++){
    //     cout << f[i - 1] << endl;
    // }

    while(1){
        getline(cin, s);

        int num = 0;

        if(s.empty()){
            break;
        }

        else {
            for(int i = 0; i < s.size(); i++){
                num += (s[i] - '0')*pow(10, s.size() - i - 1);
            }
        }


        cout << "Case " << ++k << ": " << f[num - 1] << endl;
    }
    return 0;
}