/* Max Grabov
 * Dr. Steinberg
 * COP3503 Fall 2024
 * Programming Assignment 5
 */

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.*;

public class Railroad
{
    private int tracks;
    private String filePath;

    Railroad(int tracks, String filePath)
    {
        this.tracks = tracks;
        this.filePath = filePath;
    }

    public String buildRailroad()
    {
        String ans = "";
        try
        {
            //Init data
            BufferedReader reader = new BufferedReader(new FileReader(this.filePath));

            //Map is used to link index in set to names
            Map<String, Integer> map = new HashMap<>();

            String[][] lines = new String[2][this.tracks];

            Pair[] costs = new Pair[this.tracks];

            int locations = 0;

            for(int i = 0; i < this.tracks; i++)
            {
                String[] values = reader.readLine().split(" ");

                //Set up data
                lines[0][i] = values[0];
                lines[1][i] = values[1];

                costs[i] = new Pair(Integer.parseInt(values[2]), i);

                //Put Strings in map for convenience, also gets total locations
                if(map.containsKey(values[0]) != true)
                {
                    map.put(values[0], locations++);
                }

                if(map.containsKey(values[1]) != true)
                {
                    map.put(values[1], locations++);
                }
            }

            //Min sort
            Arrays.sort(costs, new SortCost());

            //Use total locations from hashset usage
            DisjointSetImproved set = new DisjointSetImproved(locations);

            int totalCost = 0;

            //Perform Kruskal's
            for(int i = 0; i < this.tracks; i++)
            {
                //If set is not a cycle
                if(set.find(map.get(lines[0][costs[i].val2])) != set.find(map.get(lines[1][costs[i].val2])))
                {
                    set.union(map.get(lines[0][costs[i].val2]), map.get(lines[1][costs[i].val2]));
                    totalCost += costs[i].val1;

                    //Print accordingly
                    if(lines[0][costs[i].val2].compareTo(lines[1][costs[i].val2]) < 0)
                    {
                        ans = ans.concat(lines[0][costs[i].val2] + "---" + lines[1][costs[i].val2] + "\t$" + costs[i].val1 + "\n");
                    }
                    else
                    {
                        ans = ans.concat(lines[1][costs[i].val2] + "---" + lines[0][costs[i].val2] + "\t$" + costs[i].val1 + "\n");
                    }
                }
            }

            //End
            ans = ans.concat("The cost of the railroad is $" + totalCost + ".");

            reader.close();
        }

        catch(Exception e)
        {
            System.out.println(e);
        }

        return ans;
    }
}

//Pair classed is used to link a cost with original track index
class Pair
{
    int val1;
    int val2;

    Pair(int a, int b)
    {
        this.val1 = a;
        this.val2 = b;
    }
}

class SortCost implements Comparator<Pair>
{
    //When sorted, allows me to lookup much faster using val2
    public int compare(Pair a, Pair b)
    {
        if(a.val1 < b.val1)
        {
            return -1;
        }
        else if(a.val1 > b.val1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

//Taken from the provided Disjoint set in the homework
class DisjointSetImproved
{
    int [] rank;
    int [] parent;
    int n;

    public DisjointSetImproved(int n)
    {
        rank = new int[n];
        parent = new int[n];
        this.n = n;
        makeSet();
    }

    // Creates n sets with single item in each
    public void makeSet()
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    //path compression
    public int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }

    //union by rank
    public void union(int x, int y)
    {
        int xRoot = find(x), yRoot = find(y);

        if (xRoot == yRoot)
            return;

        if (rank[xRoot] < rank[yRoot])
            parent[xRoot] = yRoot;

        else if (rank[yRoot] < rank[xRoot])
            parent[yRoot] = xRoot;
        else
        {
            parent[yRoot] = xRoot;
            rank[xRoot] = rank[xRoot] + 1;
        }
    }
}


