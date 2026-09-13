/*
 * Q7 - Matrix Chain Multiplication
 *
 * Dynamic Programming solution.
 *
 * Find:
 * 1. Minimum number of scalar multiplications.
 * 2. Optimal parenthesization.
 *
 * Time Complexity: O(n^3)
 * Space Complexity: O(n^2)
 */

#include <stdio.h>
#include <limits.h>

#define MAX 100

long long dp[MAX][MAX];
int split[MAX][MAX];

/*
 * Print the optimal parenthesization.
 */
void printParenthesis(int i, int j)
{
    if (i == j)
    {
        printf("A%d", i);
        return;
    }

    printf("(");

    printParenthesis(i, split[i][j]);

    printf(" x ");

    printParenthesis(split[i][j] + 1, j);

    printf(")");
}

/*
 * Matrix Chain Multiplication DP
 */
long long matrixChainMultiplication(int p[], int n)
{
    int i, j, k;
    int length;
    long long cost;

    /*
     * length = length of matrix chain
     */
    for (length = 2; length <= n; length++)
    {
        for (i = 1; i <= n - length + 1; i++)
        {
            j = i + length - 1;

            dp[i][j] = LLONG_MAX;

            /*
             * Try every possible split.
             */
            for (k = i; k < j; k++)
            {
                cost = dp[i][k]
                     + dp[k + 1][j]
                     + (long long)p[i - 1]
                     * p[k]
                     * p[j];

                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    return dp[1][n];
}

int main()
{
    int n;
    int p[MAX];
    int i;
    long long result;

    printf("MATRIX CHAIN MULTIPLICATION\n");
    printf("---------------------------\n");

    /*
     * n = number of matrices
     */
    printf("Enter number of matrices: ");
    scanf("%d", &n);

    if (n <= 0 || n >= MAX)
    {
        printf("Invalid input!\n");
        return 1;
    }

    /*
     * If matrices are:
     *
     * A1 = p0 x p1
     * A2 = p1 x p2
     * ...
     * An = p(n-1) x pn
     *
     * We need n+1 dimensions.
     */
    printf("\nEnter %d dimensions:\n", n + 1);

    for (i = 0; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }

    /*
     * Calculate minimum cost.
     */
    result = matrixChainMultiplication(p, n);

    printf("\nMinimum number of scalar multiplications = %lld\n",
           result);

    printf("\nOptimal parenthesization:\n");
    printParenthesis(1, n);

    printf("\n");

    return 0;
}