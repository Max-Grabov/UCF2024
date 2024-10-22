import java.util.*;

public class HW3 {

    public static String encrypt(String key, StringBuilder plaintext, char grid[][], int[] chars){
        //First, we do padding for the double letters
        for(int i = 1; i < plaintext.length(); i++){
            if(plaintext.charAt(i - 1) == plaintext.charAt(i)){
                //If the double letter happens to be an x, pad with q instead
                if(plaintext.charAt(i) == 'x'){
                    plaintext.insert(i, 'q');
                }

                else {
                    plaintext.insert(i, 'x');
                }
            }
        }

        //If we have an odd plaintext after the padding, insert x unless the last character is an x, in this case insert q
        if(plaintext.length() % 2 == 1){
            if(plaintext.charAt(plaintext.length() - 1) == 'x'){
                plaintext.append('q');

            }
            else {
                plaintext.append('x');
            }
        }

        //Now that padding is done, we do encryption
        String ans = "";
        int size = plaintext.length();
        int tmp1, tmp2;

        for(int i = 0; i < size; i += 2){
            //Get the index of the 2 characters we are gonna encrypt from used
            tmp1 = chars[plaintext.charAt(i) - 'a'];

            //If it is an 'i', use j's value
            if(plaintext.charAt(i) == 'i'){
                tmp1 = chars['j' - 'a'];
            }

            tmp2 = chars[plaintext.charAt(i + 1) - 'a'];

            if(plaintext.charAt(i + 1) == 'i'){
                tmp2 = chars['j' - 'a'];
            }

            //This means they share the same row
            if(tmp2 / 5 == tmp1 / 5){
                //Append the same row, but one column to the right
                ans += grid[tmp1 / 5][(tmp1 + 1) % 5];
                ans += grid[tmp2 / 5][(tmp2 + 1) % 5];
            }

            //They share the same column
            else if(tmp2 % 5 == tmp1 % 5){
                //Append one row down, but same column
                ans += grid[((tmp1 / 5) + 1) % 5][tmp1 % 5];
                ans += grid[((tmp2 / 5) + 1) % 5][tmp2 % 5];
            }

            //Only other case is they make a box
            else {
                //Append same row, but swapped columns
                ans += grid[tmp1 / 5][tmp2 % 5];
                ans += grid[tmp2 / 5][tmp1 % 5];
            }
        }

        //get the encrypted text!
        return ans;
    }
    public static void main(String args[]){

        //Make all my variables
        Scanner scan = new Scanner(System.in);
        String key;
        StringBuilder plaintext;
        int n;

        n = Integer.parseInt(scan.nextLine());

        for(int i = 0; i < n; i++){
            key = scan.nextLine();
            plaintext = new StringBuilder(scan.nextLine());

            boolean used[] = new boolean[26];
            int chars[] = new int[26];
            char grid[][] = new char[5][5];

            int keySize = key.length();

            int currIndex = 0;
            //First, insert the keyword
            for(int j = 0; j < keySize; j++){

                //If we already used this letter in the box, don't use it again!
                if(used[key.charAt(j) - 'a']) continue;

                //Since we want to consider i/j one entity, and only use i, anytime we see an i, we make the grid at the spot j instead
                if(key.charAt(j) == 'i'){

                    //This gets the correct grid spot
                    grid[currIndex / 5][currIndex % 5] = 'j';

                    //Set both the 'i' and 'j' to used, and set them both to the same index
                    used[key.charAt(j) - 'a'] = true;
                    used['j' - 'a'] = true;
                    chars['j' - 'a'] = currIndex;
                    chars['i' - 'a'] = currIndex;

                    //go up an index
                    currIndex++;
                    continue;
                }

                //Same process as above, except no i/j exception
                grid[currIndex / 5][currIndex % 5] = key.charAt(j);

                used[key.charAt(j) - 'a'] = true;
                chars[key.charAt(j) - 'a'] = currIndex;
                currIndex++;
            }

            //This is the exact same as above, except we fill in the rest of alphabet
            for(int j = 0; j < 26; j++){

                //If used from keyword, skip
                if(used[j]) continue;

                //Do the same i/j things as when we were doing the keyword
                if('a' + j == 'i'){
                    grid[currIndex / 5][currIndex % 5] = 'j';

                    used[j] = true;
                    used['j' - 'a'] = true;
                    chars['j' - 'a'] = currIndex;

                    currIndex++;
                    continue;
                }

                //Same process as for the keyword
                grid[currIndex / 5][currIndex % 5] = (char)(j + 'a');

                //unnecessary, since there is no repeat of this letter guarranteed in the alphabet, but done for consistency
                used[j] = true;

                chars[j] = currIndex;

                currIndex++;
            }

            String ans = encrypt(key, plaintext, grid, chars);
            System.out.println(ans);

            grid = null;
            chars = null;
        }

        scan.close();
    }
}
