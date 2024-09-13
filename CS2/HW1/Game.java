/* Max Grabov
 * Dr. Steinberg
 * COP3503 Fall 2024
 * Programming Assignment 1
 */

import java.util.Random;
public class Game
{
    //Make the data we need for the class
    int arr[][] = new int[8][8];
    char moves[] = {'d', 'r', 'b'};
    Random seed;

    //Initialize the game object wit the seed
    Game(Random seed)
    {
        this.seed = seed;
    }

    //Used to get the current row position at the start of a round
    public int getRow()
    {
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(this.arr[i][j] == 1)
                {
                    return i;
                }
            }
        }

        return -1;
    }

    //Used to get the current column position at the start of a round
    public int getColumn()
    {
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(this.arr[i][j] == 1)
                {
                    return j;
                }
            }
        }

        return -1;
    }

    //Get the computer move, using the random seed from (0,3)
    public char selectPlayerTwoMove()
    {
        return this.moves[seed.nextInt(3)];
    }

    int play()
    {
        int r = getRow();
        int c = getColumn();

        /*If it is the first turn of the game, the functions above will fail since no piece is on the board
        make the piece start at (0,0)
        */
        if(r == -1 || c == -1)
        {
            r = c = 0;
        }

        //If the row and column is already at the winning square, since our turn is at the beginning of play
        //this means the computer moved to the winning square, so we lost :(
        if(c == 7 && r == 7)
        {
            return -1;
        }

        //Initialize a char for the player move
        char p1Move = ' ';

        /*If we are on a odd row, move to the right
        this is because we want to get to the edge on the "correct" row, so when the only moves available is down
        we have a 100% of winning

        Being on the correct side means, if we are at the edge (e.g. (0, 7)), the only move becomes to the right
        since the right is the only direction and there are 2 players, we have 100% chance of winning
        */
        if(r % 2 == 1)
        {
            p1Move = 'r';
        }

        /*If we are on a odd column, move down
        same reason as above
        */
        else if(c % 2 == 1)
        {
            p1Move = 'b';
        }

        //If we are on a even row/column, decide whether it is advantageous to go diagonal or not
        else if(r % 2 == 0)
        {
            //Once again, we want to end up on the "correct" row so we can force a win, so move accordingly
            if(c % 2 == 1)
            {
                p1Move = 'b';
            }
            else
            {
                p1Move = 'd';
            }
        }

        //Same reasoning as above
        else if(c % 2 == 0)
        {
            if(r % 2 == 1)
            {
                p1Move = 'r';
            }
            else
            {
                p1Move = 'd';
            }
        }

        //Ensure that if we are on the last row/column, we don't index out of bounds
        if(r == 7)
        {
            p1Move = 'r';
        }
        if(c == 7)
        {
            p1Move = 'b';
        }

        //Move the player according to their selected character move
        if(p1Move == 'd')
        {
            this.arr[r][c] = 0;
            this.arr[r + 1][c + 1] = 1;
        }

        else if(p1Move == 'r')
        {
            this.arr[r][c] = 0;
            this.arr[r][c + 1] = 1;
        }

        else
        {
            this.arr[r][c] = 0;
            this.arr[r + 1][c] = 1;
        }

        //If our move brings us to (7,7), we win the game :)
        if(this.arr[7][7] == 1)
        {
            return 1;
        }

        //Now we decide the computer's move (really it decides itself)
        char p2Move = ' ';

        //If we are at the edge, make sure the computer only moves in the only possible direction
        if(r == 7)
        {
            p2Move = this.moves[1];
        }
        else if(c == 7)
        {
            p2Move = this.moves[2];
        }

        //Otherwise, make it chose its move
        else
        {
            p2Move = selectPlayerTwoMove();
        }

        //Move the computer according to its selected move
        if(p2Move == 'd')
        {
            this.arr[r][c] = 0;
            this.arr[r + 1][c + 1] = 1;
        }

        else if(p2Move == 'r')
        {
            this.arr[r][c] = 0;
            this.arr[r][c + 1] = 1;
        }

        else
        {
            this.arr[r][c] = 0;
            this.arr[r + 1][c] = 1;
        }

        //Call Play again from the new square
        return play();
    }
}