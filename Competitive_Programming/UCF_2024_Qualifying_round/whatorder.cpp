#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

bool check(vector<string> &restrictions, string &curr, int numRestrictions){
    int size = curr.size();
    for(int i = 0; i < numRestrictions; i++){
        char a = restrictions[i][2];
        char b = restrictions[i][4];

        int aIndex = -1;
        int bIndex = -1;

        for(int j = 0; j < size; j++){
            if(curr[j] == a){
                aIndex = j;
            }
            if(curr[j] == b){
                bIndex = j;
            }
        }

        if(aIndex < 0 || bIndex < 0) continue;

        if(restrictions[i][0] == '1'){
            if(aIndex > bIndex) return false;
        }

        else if(restrictions[i][0] == '2'){
            if(aIndex < bIndex) return false;
        }

        else {
            if((int)abs(aIndex - bIndex) == 1) return false;
        }
    }

    return true;
}

void solve(vector<string> &restrictions, string curr, vector<bool> &used, int *ans, int len, int numRestrictions, int index){
    if(!check(restrictions, curr, numRestrictions)) return;

    if(index == len){
        *ans += 1;
        return;
    }

    for(int i = 0; i < len; i++){
        if(used[i]) continue;

        curr.push_back(i + 'A');
        used[i] = true;

        // cout << curr << endl;
        // cout << *ans << endl;

        solve(restrictions, curr, used, ans, len, numRestrictions, index + 1);

        used[i] = false;
        curr.pop_back();
    }
}

long factorial(int n){
    long ans = 1;
    while(n > 0){
        n;
        ans *= n;
        n--;
    }

    return ans;
}
int main(){
    int n, k;
    cin >> n >> k;

    string s, curr;
    vector<string> restrictions;
    vector<bool> used;
    for(int i = 0; i < k; i++){
        getline(cin >> ws, s);
        restrictions.push_back(s);
        used.push_back(false);
    }

    if(k == 1){
        if(restrictions[0][0] == '3'){
            cout << factorial(n) - 2*factorial(n - 1);
        }
        else {
            cout << factorial(n) / 2;
        }
        cout << endl;
        return 0;
    }

    int ans = 0;
    solve(restrictions, curr, used, &ans, n, k, 0);

    cout << ans << endl;
}