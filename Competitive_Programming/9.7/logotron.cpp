#include <math.h>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int main(){
    int n;
    int bots, statements;
    string s;
    vector<string> st;
    cin >> n;

    for(int i = 0; i < n; i++){
        cin >> bots >> statements;
        vector<pair<int, int>> table(bots);
        for(int j = 0; j < statements; j++){
            getline(cin >> ws, s);
            st.push_back(s);
        }

        long long ans = pow(2, bots);

        for(int j = 0; j < statements; j++){
            if(statements)
        }
        st.clear();
    }
}