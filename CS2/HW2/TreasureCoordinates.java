/* Max Grabov
 * Dr. Steinberg
 * COP3503 Fall 2024
 * Programming Assignment 2
 */

//I probably put too many comments, sorry about that.
import java.util.*;
class TreasureCoordinates
{
    public String buildToString(StringBuilder build, String s, int size)
    {
        //Here, we build our string output using the generated build string
        StringBuilder temp = new StringBuilder(s);

        //Append the first parenthesis
        StringBuilder ret = new StringBuilder("(");

        //Sort the values of the build string
        int index1 = build.charAt(0) - 'a';
        int index2 = build.charAt(1) - 'a';
        int index3 = build.charAt(2) - 'a';

        /*Put them into an arraylist to sort
         *The reason I sort, is because when I insert the decimals and commas, it shifts the string after the inserted value
         *I want to make sure I am inserting at the correct value, so I start with the character that comes first
         */
        ArrayList<Integer> indexs = new ArrayList<>();
        indexs.add(index1);
        indexs.add(index2);
        indexs.add(index3);

        Collections.sort(indexs);

        //The offset is one, since if we insert a "," at the value 0 into "123", it will be ",123", so that is bad :(
        int offset = 1;
        for(int i = 0; i < 3; i++)
        {
            /*If the value represents the "end" of the string, this means it doesn't appear as specified in the solve function,
             *So do not insert anything!
             */
            if(indexs.get(i) == size - 1)
            {
                continue;
            }

            //If the index is for the comma, we need to also append the space, and the offset increases by 2 (1 for comma and space)
            if(indexs.get(i) == index1)
            {
                temp.insert(indexs.get(i) + offset, ", ");
                offset += 2;
                continue;
            }

            //Only other option is the decimal, so we do that, then add one to the total offset for the next character
            temp.insert(indexs.get(i) + offset, ".");
            offset += 1;
        }

        //append this built up string to the return value, which contains just "(", then add the last parenthesis
        ret.append(temp);
        ret.append(")");

        //Return the toString()
        return ret.toString();
    }

    public boolean check(StringBuilder build, String s, int size)
    {

        //Don't cancel the build if we just started
        if(build.length() == 0)
        {
            return true;
        }

        //If the comma is a value of len - 1, which in my code represents "Not in the string", then it is impossible
        if(build.charAt(0) - 'a' == size - 1)
        {
            return false;
        }

        //Since comma is always first in the build string, we check for 2 and 3 length strings
        if(build.length() == 2)
        {
            //The comma and decimal cannot have the same integer index (They are next to eachother in the actual string)
            if((build.charAt(0) == build.charAt(1)))
            {
                return false;
            }

            //Now check for leading zeroes of the first integer (X-coordinate) ONLY, we will check the second after we place the next decimal
            char firstCharX = s.charAt(0);

            if(firstCharX == '0')
            {
                /*If we do have a leading zero, the index of the decimal MUST be the same as the zero
                 *In my representation, this means the decimal MUST be at a value of 0 (e.g. 0.11 vs 01.1)
                 *OR, we could have the comma there instead
                 */
                if(build.charAt(1) - 'a' != 0 && build.charAt(0) - 'a' != 0)
                {
                    return false;
                }
            }

            //Now we check for TRAILING zeroes on the first number (Thanks test case #3...)
            char lastCharX = s.charAt(build.charAt(0) - 'a');

            if(lastCharX == '0')
            {
                //If there is a 0 at the end of the first number, and we have a decimal in that first number, this breaks the trailing zero check
                if(build.charAt(1) < build.charAt(0))
                {
                    return false;
                }
            }

        }

        if(build.length() == 3)
        {
            /*This check ensures that the 2 decimals don't share a position
             *In addition, we force the 2nd decimal to always be after the comma
             *This helps to remove duplicate coordinates and makes certain checks easier
             */
            if(build.charAt(0) == build.charAt(1) || build.charAt(0) == build.charAt(2) || (build.charAt(1) == build.charAt(2) && build.charAt(1) - 'a' != size - 1))
            {
                return false;
            }

            if((build.charAt(0) > build.charAt(2)) || (build.charAt(1) > build.charAt(2)))
            {
                return false;
            }

            //Now check for 3 length builds if both decimals are on the second number
            if((build.charAt(1) > build.charAt(0)) && (build.charAt(2) > build.charAt(0)) && build.charAt(2) - 'a' != size - 1)
            {
                return false;
            }

            /*The next check is to see if there is leading zeroes on the second number, using a similar process as the first number
             *We also need to ensure that if we don't have a second decimal, then we use the value for the 1st decimal instead
             *We can do this with an or operator, since if the first decimal actually satisfies it,
             */
            char firstCharY = s.charAt(build.charAt(0) - 'a' + 1);

            if(firstCharY == '0')
            {
                /*Check if the decimal is to the right of the zero, otherwise it fails
                 *This also works if the value is size - 1, since that means there is no decimal
                 *This lines up perfectly if the comma is at the character before the end (e.g. 123, 0)
                 *The only way this works is if there is no decimal after 0, which is the same as size - 1 in my permutation
                 */
                if(build.charAt(2) != build.charAt(0) + 1 && build.charAt(1) != build.charAt(0) + 1)
                {
                    return false;
                }
            }

            //Now, the final check, looking for trailing zeroes in second number
            char lastCharY = s.charAt(size - 1);

            if(lastCharY == '0')
            {
                //If there is a decimal in the second number, it automatically means the 0 is a trailing zero, so it is invalid
                if(build.charAt(2) - 'a' != size - 1)
                {
                    return false;
                }

                /*The absolute last part, which is not included in the test cases, is that if the first decimal
                 *Is in the second number and there is a trailing zero, we need to invalidate that too
                 *This covers a test case such as (000111000)
                 *Also, we make sure that the 1st decimal is also not included, since that will make test cases such as (1010)
                 *Not produce a correct option of (10, 10)
                 */
                if(build.charAt(2) - 'a' == size - 1 && (build.charAt(1) > build.charAt(0) && build.charAt(1) - 'a' != size - 1))
                {
                    return false;
                }
            }
        }

        return true;
    }

    public void solve(String s, int size, StringBuilder build, ArrayList<String> ans, int index)
    {
        //If we fail the check, end the recursion for this branch and go back up
        if(!check(build, s, size))
        {
            return;
        }

        //If we reach the end, add it to the answer then end the recursion
        if(index == 3)
        {
            ans.add(buildToString(build, s, size));
            return;
        }

        /*For every integer up to the total size, we are going to build a 3 length string
         *The first index represents the comma
         * second and third represent the decimals

         *index 0 represent the gap between the 0th index digit and the 1st index digit of the original input
         *This continues until the end, where the size - 1 index represents that the decimal/comma is not in the end result
         */
        for(int i = 0; i < size; i++)
        {
            /*append the integer
             *Sadly, as I was about to submit this, I realized that the input could contain an insane amount of digits
             *This would break my algorithm if I append digits, as the new string would contain more than 3 characters
             *I remedy this by appending a character as there are way more of them compared to 0-9 digits
             *Hopefully the test cases won't be more than the characters from 'a' to char(255) :D
            */
            build.append((char)('a' + i));

            //Go up an index
            solve(s, size, build, ans, index + 1);

            //Remove the character at index
            build.deleteCharAt(index);
        }
    }

    public ArrayList<String> determineCoordinates(String s)
    {
        //Make a list for the answer, I do this only once since my actual recursive function is going to be called later
        ArrayList<String> list = new ArrayList<String>();

        //I am going to "build" up a combination of 2 decimals and a comma for the answer
        StringBuilder build = new StringBuilder("");

        //The input is the actual string inputted without the parenthesis
        String input = s.substring(1, s.length() - 1);
        int size = input.length();

        //Solve this test case :D
        solve(input, size, build, list, 0);
        return list;
    }
}