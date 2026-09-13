/*
 * Reve's Puzzle - 4 Peg Tower of Hanoi
 *
 * Problem:
 * There are n disks and 4 pegs.
 * Initially all disks are on Peg A.
 * The objective is to move all disks to Peg D.
 *
 * Rules:
 * 1. Only one disk can be moved at a time.
 * 2. A larger disk cannot be placed on a smaller disk.
 *
 * Algorithm:
 * Frame-Stewart Algorithm
 *
 * For n disks:
 * 1. Move k smallest disks using 4 pegs.
 * 2. Move remaining n-k disks using the classical
 *    3-peg Tower of Hanoi.
 * 3. Move k disks to destination using 4 pegs.
 *
 * Time Complexity:
 * O(2^n) for the recursive solution.
 */

#include <stdio.h>
#include <limits.h>

#define MAX 30

long long dp[MAX + 1];
int split[MAX + 1];

/*
 * Calculate 3-peg Tower of Hanoi moves.
 *
 * Number of moves for n disks:
 *
 * T(n) = 2^n - 1
 */
long long hanoi3(int n)
{
    if (n == 0)
        return 0;

    return 2 * hanoi3(n - 1) + 1;
}

/*
 * Calculate the minimum number of moves
 * using 4 pegs.
 *
 * Frame-Stewart recurrence:
 *
 * T(n) = min [ 2*T(k) + (2^(n-k) - 1) ]
 *
 * where 1 <= k < n
 */
void calculateDP(int n)
{
    int i, k;
    long long moves;

    dp[0] = 0;

    if (n >= 1)
        dp[1] = 1;

    for (i = 2; i <= n; i++)
    {
        dp[i] = LLONG_MAX;

        /*
         * Try every possible value of k.
         *
         * k = number of smallest disks
         * moved using 4 pegs.
         */
        for (k = 1; k < i; k++)
        {
            /*
             * Move k disks using 4 pegs
             * + move remaining disks using 3 pegs
             * + move k disks using 4 pegs
             */
            moves = 2 * dp[k] + hanoi3(i - k);

            if (moves < dp[i])
            {
                dp[i] = moves;
                split[i] = k;
            }
        }
    }
}

/*
 * Print the actual moves for 3 pegs.
 */
void move3(int n, char source, char destination, char auxiliary)
{
    if (n == 0)
        return;

    move3(n - 1, source, auxiliary, destination);

    printf("Move disk %d: %c -> %c\n",
           n, source, destination);

    move3(n - 1, auxiliary, destination, source);
}

/*
 * Print the moves for 4 pegs.
 *
 * This function follows the Frame-Stewart strategy.
 */
void move4(int n, char source, char destination,
           char auxiliary1, char auxiliary2)
{
    int k;

    if (n == 0)
        return;

    if (n == 1)
    {
        printf("Move disk 1: %c -> %c\n",
               source, destination);
        return;
    }

    /*
     * Best split point calculated by DP.
     */
    k = split[n];

    /*
     * Step 1:
     * Move k smallest disks from source
     * to auxiliary1 using 4 pegs.
     */
    move4(k, source, auxiliary1,
          destination, auxiliary2);

    /*
     * Step 2:
     * Move remaining n-k disks from source
     * to destination using 3 pegs.
     *
     * We use auxiliary2 as the spare peg.
     */
    move3(n - k, source, destination, auxiliary2);

    /*
     * Step 3:
     * Move the k disks from auxiliary1
     * to destination using 4 pegs.
     */
    move4(k, auxiliary1, destination,
          source, auxiliary2);
}

int main()
{
    int n;

    printf("REVE'S PUZZLE - 4 PEG TOWER OF HANOI\n");
    printf("--------------------------------------\n");

    printf("Enter number of disks: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX)
    {
        printf("Invalid number of disks!\n");
        return 1;
    }

    /*
     * Calculate minimum number of moves.
     */
    calculateDP(n);

    printf("\nMinimum number of moves = %lld\n",
           dp[n]);

    printf("Optimal split k = %d\n\n",
           split[n]);

    printf("Sequence of moves:\n");
    printf("------------------\n");

    /*
     * Pegs:
     * A = Source
     * B = Auxiliary 1
     * C = Auxiliary 2
     * D = Destination
     */
    move4(n, 'A', 'D', 'B', 'C');

    return 0;
}