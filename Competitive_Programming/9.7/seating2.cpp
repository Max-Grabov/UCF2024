#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>
using namespace std;

int tri(int c){
    int sum = 0;
    while(c > 0){
        sum += c--;
    }

    return sum;
}

bool checkRm(char c, char t1, char t2){
    if(c == t1 || c == t2){
        return true;
     }
        return false;
}


bool checkMap(map<string, int> &mp, string &s, string &sort){
    if(mp[sort]){
        return false;
    }

    mp[sort] = 1;
    return true;
}
bool check(string &s, string &sort, map<string, int> &mp, int couples, int index){
    if(index == couples){
        if(!checkMap(mp, s, sort)){
            return false;
        }
    }

    int a, b;
    for(int i = 0; i < 2 * index - 1; i++){
        a = s[i] - 'a';
        b = s[i + 1] - 'a';
        if(b - a == 1){
            return false;
        }
    }

    return true;
}

void sol(map<string, int> &mp, vector<string> &doubles, string &curr, vector<int> &indexs, string sortedCurr, vector<bool> &usedDouble, vector<bool> &usedSingle, int index, int couples, int *ans, int k){
    if(!check(curr, sortedCurr, mp, couples, index)) return;

    if(index == couples){
        // cout << curr << endl;
        // cout << sortedCurr << endl;
        // cout << endl;
        *ans += 1;
        return;
    }

    for(int i = 0; i < k; i++){
        if(usedDouble[i]){
            continue;
        }
        cout << i << endl;
        char a = doubles[i][0];
        char b = doubles[i][1];
        if(usedSingle[a - 'a']){
            i = indexs[a - 'a' + 1] - 1;
            continue;
        }

        if(usedSingle[b - 'a']){
            continue;
        }

        curr.append(doubles[i]);
        if(!index){
            sortedCurr.append(doubles[i]);
        }

        int j = 0;
        for(; j <= index * 2 && index != 0; j+=2){
            // cout << i << endl;
            // cout << doubles[i][0] << " " << curr[j] << endl;
            if(j == 2 * index){
               // cout << "put at end" << endl;
                sortedCurr.append(doubles[i]);
                break;
            }
            if(doubles[i][0] > sortedCurr[j]){
               // cout << "kept going" << endl;
                continue;
            }
            else {
                sortedCurr.insert(j, doubles[i]);
               // cout << "stopped" << endl;
                break;
            }
        }
        cout << curr << endl;
        cout << sortedCurr << endl;
        cout << endl;
        usedDouble[i] = true;
        usedSingle[a - 'a'] = true;
        usedSingle[b - 'a'] = true;

        sol(mp, doubles, curr, indexs, sortedCurr, usedDouble, usedSingle, index + 1, couples, ans, k);

        curr.pop_back();
        curr.pop_back();

        sortedCurr.erase(j, 2);

        usedDouble[i] = false;
        usedSingle[a - 'a'] = false;
        usedSingle[b - 'a'] = false;
    }
}
int main(){
    int n, couples;
    vector<long> ans(10, 0);
    cin >> n;

    ans[0] = 0;
    ans[1] = 0;
    ans[2] = 1;
    ans[3] = 5;

    for(int t = 0; t < n; t++){
        cin >> couples;
        // if(ans[couples]){
        //     cout << ans[couples] << endl;
        //     continue;
        // }

        vector<string> comb;
        string tmp;
        for(int i = 0; i < 2 * couples; i++){
            for(int j = i + 2; j < 2 * couples; j++){
                if(i == j) continue;
                tmp.push_back('a' + i);
                tmp.push_back('a' + j);
                comb.push_back(tmp);
                tmp.clear();
            }
        }


        int k = tri(couples * 2 - 2);

        // for(int i = 0; i < k; i++){
        //     cout << comb[i] << endl;
        // }

        vector<bool> usedDouble(k, false);
        vector<bool> usedChar(couples * 2 - 2, false);
        vector<int> indexs;

        indexs.push_back(0);
        for(int i = 1; i < 2 * couples - 2; i++){
            indexs.push_back(indexs[i - 1] + 2 * couples - 2 - i + 1);
        }

        string s = "";
        string holder = "";
        map<string, int> mp;
        //string popop = "abdefg";

        int answer = 0;

        // popop.insert(2, "xu");
        // cout << popop << " ";
        // popop.erase(4, 2);
        // cout << popop << endl;
        sol(mp, comb, s, indexs, holder, usedDouble, usedChar, 0, couples, &answer, k);
        cout << answer << endl;
    }
}