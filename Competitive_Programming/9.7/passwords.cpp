#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
void solve(long long rank, vector<string> &s, int size){
    if(size == 0){
        return;
        // cout << s[size - 1][rank % s[size-1].size() - 1];
    }
    long long tot = 1;
    for(int i = 0; i < size - 1; i++){
        tot *= s[i].size();
    }

    long long curr = 0;
    //cout << tot << endl;
    for(int i = 0; i < s[size - 1].size(); i++){
        //cout << curr << endl;
        if(curr + tot >= rank){
            cout << s[size-1][i];
            solve(rank - curr, s, size-1);
            break;
        }
        curr += tot;
    }


}
using namespace std;
int main(){
    int n;
    int k;
    long long rank;
    string s;
    cin >> n;

    for(int i = 0; i < n; i++){
        cin >> k;
        vector<string> strings(k, "");
        for(int j = k-1; j >= 0; j--){
            cin >> s;
            strings[j] = s;
        }
        cin >> rank;
        int size = strings.size();
        //cout << size;
        solve(rank, strings, size);
        cout << endl;
    }
    return 0;
}