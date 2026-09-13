/*
 * Super Egg Testing Experiment
 *
 * Problem:
 * Given E eggs and F floors, determine the minimum number
 * of drops required in the worst case to find the highest
 * floor from which an egg can be dropped without breaking.
 *
 * Dynamic Programming Solution
 *
 * Time Complexity: O(E * F^2)
 * Space Complexity: O(E * F)
 */

#include <stdio.h>
#include <limits.h>

// Function to find minimum number of trials
int eggDrop(int E, int F)
{
    // dp[e][f] = minimum number of drops needed
    // with e eggs and f floors
    int dp[E + 1][F + 1];

    int e, f, x;
    int minDrops, worstCase;

    // Base case:
    // With 0 floors -> 0 drops
    // With 1 floor  -> 1 drop
    for (e = 1; e <= E; e++)
    {
        dp[e][0] = 0;

        if (F >= 1)
            dp[e][1] = 1;
    }

    // Base case:
    // With only 1 egg, we have to check every floor
    for (f = 1; f <= F; f++)
    {
        dp[1][f] = f;
    }

    // Fill the DP table
    for (e = 2; e <= E; e++)
    {
        for (f = 2; f <= F; f++)
        {
            minDrops = INT_MAX;

            // Try dropping the egg from every possible floor
            for (x = 1; x <= f; x++)
            {
                /*
                 * Two possibilities:
                 *
                 * 1. Egg breaks:
                 *    We have e-1 eggs and x-1 floors.
                 *
                 * 2. Egg does not break:
                 *    We still have e eggs and f-x floors.
                 *
                 * We take the WORST case using max().
                 */

                if (dp[e - 1][x - 1] > dp[e][f - x])
                    worstCase = dp[e - 1][x - 1] + 1;
                else
                    worstCase = dp[e][f - x] + 1;

                // Select the minimum among all possible floors
                if (worstCase < minDrops)
                    minDrops = worstCase;
            }

            dp[e][f] = minDrops;
        }
    }

    return dp[E][F];
}

int main()
{
    int E, F;
    int result;

    printf("SUPER EGG TESTING EXPERIMENT\n");
    printf("----------------------------\n");

    printf("Enter number of eggs: ");
    scanf("%d", &E);

    printf("Enter number of floors: ");
    scanf("%d", &F);

    if (E <= 0 || F < 0)
    {
        printf("Invalid input!\n");
        return 1;
    }

    result = eggDrop(E, F);

    printf("\nNumber of eggs   = %d\n", E);
    printf("Number of floors = %d\n", F);

    printf("Minimum number of drops required = %d\n", result);

    return 0;
}