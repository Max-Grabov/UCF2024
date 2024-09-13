#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>

using namespace std;

string normalize(string &s){
    string ret = s;
    int size = s.size();
    int nSize = size % 2 ? size - 1 : size;

    for(int i = 0; i < nSize; i += 2){
        if(s[i] > s[i + 1]){
            swap(ret[i + 1], ret[i]);
        }
    }

    if(size % 2){
        ret.push_back(s[size - 1]);
    }

    return ret;
}

void coutString(string &s){
    for(int i = 0; i < s.size(); i++){
        cout << s[i] - 'a' << " ";
        if(i > 0 && (i%2)) cout << "|";
    }
    cout << endl;
}

// int counet = 0;
// void gen(map<string, int> &mp, string &s, vector<bool> &use, string &curr, int index, int len){
//     if(index == len){
//         string k = normalize(curr);
//         mp[curr] = 1;
//         mp[k] = 1;
//         return;
//     }

//     for(int i = 0; i < len; i += 2){
//         if(use[i / 2]){
//             continue;
//         }
//         curr.push_back(s[i]);
//         curr.push_back(s[i + 1]);
//         use[i / 2] = true;

//         gen(mp, s, use, curr, index + 2, len);

//         curr.pop_back();
//         curr.pop_back();
//         use[i / 2] = false;
//     }
// }

bool check(string &s, map<string, int> &mp, int len, int index){
    if(len == index){
        int k = mp[normalize(s)];
        int d = mp[s];

        if(k == 1 || d == 1){
            return false;
        }
    }

    int size = s.size();

    for(int i = 0; i < size - 1; i++){
        int a = s[i] - 'a';
        int b = s[i + 1] - 'a';

        //cout << a << " " << b << " " << c << endl;

        if((int)abs(b - a) == 1){
            if(len == index){
                vector<bool> use(len/2, false);
                string l = "";
                //gen(mp, s, use, l, 0, len);
            }

            return false;
        }


    }

    if(len == index){
        if(mp[normalize(s)] == 0){
            vector<bool> use(len/2, false);
            mp[normalize(s)] = 1;
            string l = "";
           // gen(mp, s, use, l, 0, len);
        }
    }

    return true;
}

void solve(vector<bool> &used, map<string, int> &mp, string &s, int index, int len, long *ans){
    if(!check(s, mp, len, index)){
        return;
    }
    if(index == len){
        mp[s] = 1;
        mp[normalize(s)] = 1;
        //coutString(s);
        *ans += 1;
        return;
    }

    for(int i = 0; i < len; i++){
        if(used[i]){
            continue;
        }
        s.push_back('a' + i);
        used[i] = true;

        solve(used, mp, s, index + 1, len, ans);

        s.pop_back();
        used[i] = false;
    }
    return;
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
    int n, couples;
    vector<long> ans(10, 0);
    cin >> n;

    ans[0] = 0;
    ans[1] = 0;
    ans[2] = 1;
    ans[3] = 5;

    //720 - 3 * 5! * 2 + 2 * 3! * 3 - 3 * 1
    //12 - 3! * 2 + 1
    for(int t = 0; t < n; t++){
        cin >> couples;
        int p = 2 * couples;
        vector<bool> used(p, false);
        map<string, int> mp;

        if(ans[couples]){
            cout << ans[couples] << endl;
            continue;
        }

        else {
            long answer = 0;
            string k = "";
            solve(used, mp, k, 0, p, &answer);

            cout << answer << endl;
            ans[couples] = answer;
        }
        // string k = "acebfhdg";
        // cout << k << " is " << check(k, mp, couples * 2, couples * 2) << endl;

        used.clear();
    }
}