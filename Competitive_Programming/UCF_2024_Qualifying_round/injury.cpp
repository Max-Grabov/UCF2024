#include <iostream>
#include <vector>
using namespace std;

int main(){
    int w, n;
    int flag = 1;
    string q;
    vector<string> words;
    cin >> w;

    for(int i = 0; i < w; i++){
        cin >> q;
        words.push_back(q);
    }

    cin >> n;
    int m;
    string s;
    string s2;
    for(int i = 0; i < n; i++){
        cin >> s;
        int val = 0;
        for(int j = 0; j < w; j++){
            //cout << s << " " << words[j] << endl;
            if(s == words[j]){
                val = 1;
                break;
            }
            else if(s.find(words[j]) == 0){
                s2 = s.substr(words[j].length(), s.length() - words[j].length());
                for(int k = 0; k < w; k++){
                    if(s2 == words[k]){
                        val = 2;
                        break;
                    }
                }
            }

        }
        cout << val << endl;

    }
}