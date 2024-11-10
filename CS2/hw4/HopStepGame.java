/* Max Grabov
 * Dr. Steinberg
 * COP3503 Fall 2024
 * Programming Assignment 4
 */

import java.lang.Math;

class HopStepGame
{
    public int minCost(int arr[], int numSquares)
    {
        //Don't go further if at last 2 squares
        if(numSquares <= 1)
        {
            return arr[numSquares];
        }

        //return the minimum sum of all paths
        //then add the square we are currently on
        return Math.min(minCost(arr, numSquares - 1),
                   minCost(arr, numSquares - 2))
                   + arr[numSquares];
    }

    public int minCostMemoization(int arr[], int numSquares, int res[])
    {
        //If we don't have saved
        if(res[numSquares] == 0)
        {
            //If at the last 2 squares, set res to the square
            if(numSquares <= 1)
            {
                res[numSquares] = arr[numSquares];
            }
            else
            {
                //Set res to that minimum sum value of all path at currSquare
                res[numSquares] = Math.min(minCostMemoization(arr, numSquares - 1, res),
                                      minCostMemoization(arr, numSquares - 2, res))
                                      + arr[numSquares];
            }
        }

        //Return res if we have it
        return res[numSquares];
    }

    public int minCostTabulation(int arr[])
    {
        //Create my table and initialize values
        int table[] = new int[arr.length];
        int len = arr.length;
        table[0] = arr[0];
        table[1] = arr[1];

        for(int i = 2; i < len; i++)
        {
            //table value is minimum of past 2 + current array value
            table[i] = Math.min(table[i - 1],
                           table[i - 2])
                           + arr[i];
        }

        //Return the minimum of last 2 squares
        return Math.min(table[len - 1], table[len - 2]);
    }
}