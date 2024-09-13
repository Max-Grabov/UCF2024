#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <valarray>

using namespace std;

//This is the original English frequency list in order
vector<pair<char, double>> freq = {{'e', 0.12702}, {'a', 0.09056}, {'t', 0.08167}, {'i', 0.07507}, {'o', 0.06966},
   {'n', 0.06749}, {'s', 0.06327}, {'h', 0.06094}, {'r', 0.05987}, {'d', 0.04253},
   {'l', 0.04025}, {'c', 0.02782}, {'u', 0.02758}, {'m', 0.02406}, {'w', 0.02360},
   {'f', 0.02228}, {'g', 0.02015}, {'y', 0.01974}, {'p', 0.01929}, {'b', 0.01492},
   {'v', 0.00978}, {'k', 0.00772}, {'j', 0.00153}, {'x', 0.00150}, {'q', 0.00095},
   {'z', 0.00074}};

//This is the Frequency list I modified to solve Question 1, I swapped letters in the list to develop patterns and words
//Eventually solving it by hand
vector<pair<char, double>> freqQuestion1 = {{'e', 0.12702}, {'o', 0.09056}, {'t', 0.08167}, {'n', 0.07507}, {'i', 0.06966},
   {'a', 0.06749}, {'r', 0.06327}, {'l', 0.06094}, {'s', 0.05987}, {'d', 0.04253},
   {'m', 0.04025}, {'f', 0.02782}, {'h', 0.02758}, {'c', 0.02406}, {'y', 0.02360},
   {'u', 0.02228}, {'g', 0.02015}, {'w', 0.01974}, {'p', 0.01929}, {'b', 0.01492},
   {'v', 0.00978}, {'k', 0.00772}, {'q', 0.00153}, {'x', 0.00150}, {'j', 0.00095},
   {'z', 0.00074}};

double alphabeticalFreq[26] = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702,
                               0.02228, 0.02015, 0.06094, 0.06966, 0.00153,
                               0.00772, 0.04025, 0.02406, 0.06749, 0.07507,
                               0.01929, 0.00095, 0.05987, 0.06327, 0.09056,
                               0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074};

void Question2(string &s, int bestGroup);

bool cmpMapVal(pair<char, double> &a, pair<char, double> &b){
    return a.second > b.second;
}

//This just prints the frequencies
void proportionOfLetters(string &s){
    map<char, double> frequencyOfString;

    //Start my frequency count
    double total = s.size();
    double sum = 0;

    for(auto const &i : s){
        frequencyOfString[i] += 1/total;
    }

    for(int i = 0; i < 26; i++){
        cout << (char)(i + 'a') << " : " << 100*frequencyOfString[i + 'a'] << "%" << endl;
    }
}

void Substitution(string &s){
    map<char, double> frequencyOfString;
    vector<pair<char, double>> A;

    double total = s.size();
    double sum = 0;

    for(const char &i : s){
        frequencyOfString[i] += 1/total;
    }

    //Put all the map values in a vector
    for(auto const &i : frequencyOfString) {
        A.push_back(i);
    }

    int sizeV = A.size();
    int sizeS = s.size();
    char c;

    sort(A.begin(), A.end(), cmpMapVal);

    //Shows the original
    cout << s << endl;
    for(int j = 0; j < sizeS; j++){

        //Match the character in the string to the one in the sorted vector
        for(int i = 0; i < sizeV; i++){

            //If the letter does not appear, no point in replacing anything
            if(A[i].second == 0) break;

            //If the characters match
            if(s[j] == A[i].first){

                //This used the modified frequency
                s[j] = freqQuestion1[i].first;
                break;
            }
        }
    }

    //Final string
    cout << s;
}

void resetVector(vector<vector<int>> &v, int r, int c){
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            v[i][j] = 0;
        }
    }
}

void showVector(vector<vector<double>> &v, int r, int c){
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}

void Kasiski(string &s, int lim){
    //IOC of English is 0.065

    //I start at 2 since if k is just 1, it is a simple shift cipher
    int k = 2;
    int total = 0;

    //Holder variables to determine most statistically likely group size
    double IOC = 0;
    double totalDeviation = 0;

    double bestDeviation = 999999999;
    int bestGroup = 0;

    int size = s.size();

    vector<vector<int>> groups(lim, vector<int>(26, 0));

    //For every possible group from 2 to lim
    for(k; k <= lim; k++){

        for(int i = 0; i < k; i++){
            for(int j = i; j < size; j += k){

                //Add to the amount of letters present in the group, and add to the total
                groups[i][s[j] - 'a']++;
                total++;
            }

            //Calculate the Index of Coincidence for the group
            for(int j = 0; j < 26; j++){
                IOC += (1.0*groups[i][j] * (groups[i][j] - 1))/((total)*(total - 1));
            }

            //Add the deviation from the standard english IOC to the totalDeviation
            totalDeviation += abs(IOC - 0.065);

            //cout << "Group " << i + 1 << " IOC is " << IOC << endl;

            //Reset Values
            IOC = 0;
            total = 0;
        }

        //This is flawed in some cases, but for these big test cases it should give us the most likely size of the keyword
        //If the average deviation is smaller than the best one found, set the new best to this average, and set the bestGroup to k
        if(totalDeviation/k < bestDeviation){
            bestDeviation = totalDeviation/k;
            bestGroup = k;
        }

        //Reset total deviation
        totalDeviation = 0;

        //cout << "-----------------------------------------------------------" << endl;

        //Reset the vector to have all 0's again for the new groups
        resetVector(groups, lim, 26);
    }
    cout << bestGroup << endl;

    //Now that we have our most likely group, time to get the shifts
    Question2(s, bestGroup);
}

//This once converts a 2D vector of letter amounts to their respective frequencies in their group
void calcFreq(string &s, vector<vector<double>> &groups, int bestGroup){
    int size = s.size();
    int total = 0;
    for(int i = 0; i < bestGroup; i++){
        for(int j = i; j < size; j += bestGroup){
            groups[i][s[j] - 'a']++;
            total++;
        }

        for(int j = 0; j < 26; j++){
            groups[i][j] /= total;
        }

        total = 0;
    }
}

//Used for debugging
void PrintVa(vector<double> &v){
    for(int i = 0; i < 26; i++){
        cout << v[i] << " ";
    }
    cout << endl;
}


char calcShift(vector<double> &row){

    //Once again we will look for the most likely shift in each group
    double bestVariance = 99999999999;
    double currVariance = 0;

    int bestShift = 99999;
    int total = 0;

    //For every possible shift a-z, go through the group and calculate the variance from the standard english letter frequencies
    for(int i = 0; i < 26; i++){
        for(int j = 0; j < 26; j++){
            if(row[j] == 0) continue;
            currVariance += abs(row[j] - alphabeticalFreq[j]);
            total++;
        }

        //If the averageVariance is smaller than the best one found, set the best to the average, and set the best shift to i
        if(currVariance/total < bestVariance){
            bestVariance = currVariance/total;
            bestShift = i;
        }

        //Reset values
        total = 0;
        currVariance = 0;

        //"Shift" my group by 1 character
        rotate(row.begin(), row.begin() + 1, row.end());

    }
    cout << (char)(bestShift + 'a') << endl;

    //Give the best shift
    return bestShift + 'a';
}

void Question2(string &s, int bestGroup){
    vector<vector<double>> groups(bestGroup, vector<double>(26, 0));
    vector<char> shifts;
    int size = s.size();

    //Turn the 2D vector into the frequencies in the groups
    calcFreq(s, groups, bestGroup);

    //Push back each best shift
    for(int i = 0; i < bestGroup; i++){
        shifts.push_back(calcShift(groups[i]));
    }

    //Undo the shift for the string
    for(int i = 0; i < size; i++){
        cout << (char)(((s[i] - 'a' - (shifts[i % bestGroup] - 'a') + 26)) % 26 + 'a');
    }

}

void checkVigenere(string &s, string &key){
    int size = s.size();
    int kSize = key.size();

    for(int i = 0; i < size; i++){
        cout << (char)(((s[i] - 'a' + key[i % kSize] - 'a') + 26) % 26 + 'a');
    }
}

void toLower(string &s){
    int size = s.size();
    for(int i = 0; i < size; i++){
        if(s[i] >= 'A' && s[i] <= 'Z'){
            s[i] = s[i] - 'A' + 'a';
        }
    }
}
int main(){
    string s, key;
    int option;

    cin >> s;
    cin >> option;

    toLower(s);

    if(option == 1){
        Substitution(s);
    }

    else if(option == 2){
        Kasiski(s, 15);
    }

    else if(option == 3){
        cin >> key;
        checkVigenere(s, key);
    }
    else {
        cout << "sad";
    }
}