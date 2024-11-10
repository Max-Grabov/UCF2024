/* Max Grabov
   Dr. Steinberg
   COP3503 Fall 2024
   Programming Assignment 3
*/

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Arrays;

public class GreedyChildren
{
    //The required attributes for the class
    //I will be really upset if overflow occurs since the project statement says integer arrays
    int greedyFactor[];
    int sweetFactor[];
    int happyChildren;
    int angryChildren;


    //Make my variables and call read
    GreedyChildren(int candies, int children, String greedyIn, String sweetIn)
    {
        this.greedyFactor = new int[children];
        this.sweetFactor = new int[candies];
        read(greedyIn, sweetIn);
    }

    public void read(String in, String out)
    {
        //Try catch because readers are so awesome
        try
        {
            BufferedReader greedReader = new BufferedReader(new FileReader(in));
            BufferedReader sweetReader = new BufferedReader(new FileReader(out));

            //Since the constructor set the array size, we use .length to get the amount of kids and candies to scan
            int children = greedyFactor.length;
            int candies = sweetFactor.length;

            //Scan input
            for(int i = 0; i < children; i++)
            {
                greedyFactor[i] = Integer.parseInt(greedReader.readLine());
            }

            for(int i = 0; i < candies; i++)
            {
                sweetFactor[i] = Integer.parseInt(sweetReader.readLine());
            }

            greedReader.close();
            sweetReader.close();
        }

        catch(Exception e)
        {
            System.out.println("error");
        }

    }

    public void greedyCandy()
    {
        //Used to keep track of all the happy kids
        int currHappyChildren = 0;

        //I sort these arrays, because we are looking for g <= s.
        //This means we take the least value of s that satisfies this for g
        Arrays.sort(this.greedyFactor);
        Arrays.sort(this.sweetFactor);

        //One again get num children and candies
        int children = this.greedyFactor.length;
        int candies = this.sweetFactor.length;

        //Make some helpful pointers to traverse
        int greedyPointer = 0;
        int candyPointer = 0;

        //Run until no more kids or we run out of candy
        while(greedyPointer < children && candyPointer < candies)
        {
            //If the child we are currently at has a greedy factor <= sweet factor, give it to them
            if(this.greedyFactor[greedyPointer] <= this.sweetFactor[candyPointer])
            {
                //Now that they are happy, increment our happy children and child pointer
                currHappyChildren++;
                greedyPointer++;
            }

            //If the candy we have is too low, then just increment the candy pointer
            //This is because no child after the current child will ever take this candy due to my sort
            //This also runs when the if statement succeeds since it is not in else
            candyPointer++;
        }

        //Set our values, the angry children will obviously be the remaining amount of children
        this.happyChildren = currHappyChildren;
        this.angryChildren = children - currHappyChildren;
    }

    //Print my data
    public void display()
    {
        System.out.println("There are " + this.happyChildren + " happy children.");
        System.out.println("There are " + this.angryChildren + " angry children.");
    }
}