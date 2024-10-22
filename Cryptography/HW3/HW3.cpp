//Max Grabov
//CIS 3362
#include <vector>
#include <string>
#include <iostream>

using namespace std;

//Used for debugging
void printGrid(vector<vector<char>> &grid){
    for(int j = 0; j < 5; j++){
        for(int k = 0; k < 5; k++){
            cout << grid[j][k] << " ";
        }
        cout << endl;
    }
}

//Also used for debugging
void printString(string &s){
    int size = s.size();
    for(int i = 0; i < size; i++){
        cout << s[i] << " ";
    }
    cout << endl;
}

//Thanks c++ string insert
string charToString(char c){
    return string(1, c);
}

//Playfair Encryption
string encrypt(string &key, string &plaintext, vector<vector<char>> &grid, vector<pair<bool, int>> &chars){

    //First, we do padding for the double letters
    for(int i = 0; i < plaintext.size() - 1; i++){
        if(plaintext[i] == plaintext[i + 1]){
            //If the double letter happens to be an x, pad with q instead
            if(plaintext[i] == 'x'){
                plaintext.insert(i + 1, "q");
            }

            else {
                plaintext.insert(i + 1, "x");
            }
        }
    }

    //If we have an odd plaintext after the padding, insert x unless the last character is an x, in this case insert q
    if(plaintext.size() % 2){
        if(plaintext[plaintext.size() - 1] == 'x'){
            plaintext.append("q");
        }
        else {
            plaintext.append("x");
        }
    }

    //Now that padding is done, we do encryption
    string ans = "";
    int size = plaintext.size();
    int tmp1, tmp2;

    for(int i = 0; i < size; i += 2){
        //Get the index of the 2 characters we are gonna encrypt from used
        tmp1 = chars[plaintext[i] - 'a'].second;

        //If it is an 'i', use j's value
        if(plaintext[i] == 'i'){
            tmp1 = chars['j' - 'a'].second;
        }

        tmp2 = chars[plaintext[i + 1] - 'a'].second;

        if(plaintext[i + 1] == 'i'){
            tmp2 = chars['j' - 'a'].second;
        }

        //This means they share the same row
        if(tmp2 / 5 == tmp1 / 5){
            //Append the same row, but one column to the right
            ans.append(charToString(grid[tmp1 / 5][(tmp1 + 1) % 5]));
            ans.append(charToString(grid[tmp2 / 5][(tmp2 + 1) % 5]));
        }

        //They share the same column
        else if(tmp2 % 5 == tmp1 % 5){
            //Append one row down, but same column
            ans.append(charToString(grid[((tmp1 / 5) + 1) % 5][tmp1 % 5]));
            ans.append(charToString(grid[((tmp2 / 5) + 1) % 5][tmp2 % 5]));
        }

        //Only other case is they make a box
        else {
            //Append same row, but swapped columns
            ans.append(charToString(grid[tmp1 / 5][tmp2 % 5]));
            ans.append(charToString(grid[tmp2 / 5][tmp1 % 5]));
        }
    }

    //get the encrypted text!
    return ans;
}
int main(){
    int n;
    cin >> n;
    string key, plaintext;

    for(int i = 0; i < n; i++){

        //Make our grid and a used pair to keep track of which letters have been used (for the keyword)
        //I also store the index in the grid so i can do quick lookups when I encrypt
        vector<pair<bool, int>> used(26, pair<bool, int>(false, 0));
        vector<vector<char>> grid(5, vector<char>(5));

        cin >> key >> plaintext;

        int keySize = key.size();

        int currIndex = 0;

        //First, insert the keyword
        for(int j = 0; j < keySize; j++){

            //If we already used this letter in the box, don't use it again!
            if(used[key[j] - 'a'].first) continue;

            //Since we want to consider i/j one entity, and only use i, anytime we see an i, we make the grid at the spot j instead
            if(key[j] == 'i'){

                //This gets the correct grid spot
                grid[currIndex / 5][currIndex % 5] = 'j';

                //Set both the 'i' and 'j' to used, and set them both to the same index
                used[key[j] - 'a'].first = true;
                used['j' - 'a'].first = true;
                used['j' - 'a'].second = currIndex;
                used['i' - 'a'].second = currIndex;

                //go up an index
                currIndex++;
                continue;
            }

            //Same process as above, except no i/j exception
            grid[currIndex / 5][currIndex % 5] = key[j];

            used[key[j] - 'a'].first = true;
            used[key[j] - 'a'].second = currIndex;
            currIndex++;
        }

        //This is the exact same as above, except we fill in the rest of alphabet
        for(int j = 0; j < 26; j++){

            //If used from keyword, skip
            if(used[j].first) continue;

            //Do the same i/j things as when we were doing the keyword
            if('a' + j == 'i'){
                grid[currIndex / 5][currIndex % 5] = 'j';

                used[j].first = true;
                used['j' - 'a'].first = true;
                used['j' - 'a'].second = currIndex;

                currIndex++;
                continue;
            }

            //Same process as for the keyword
            grid[currIndex / 5][currIndex % 5] = j + 'a';

            //unnecessary, since there is no repeat of this letter guarranteed in the alphabet, but done for consistency
            used[j].first = true;

            used[j].second = currIndex;

            currIndex++;
        }

        //Get answer, print, and clear grid and used
        string ans = encrypt(key, plaintext, grid, used);
        cout << ans << endl;

        used.clear();
        grid.clear();
    }

}