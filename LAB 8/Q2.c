#include <stdio.h>

int countWays(int coins[], int n, int V)
{
    // dp[i] = number of ways to make amount i
    int dp[V + 1];

    // Initially, no ways to make any amount
    for (int i = 0; i <= V; i++)
        dp[i] = 0;

    // There is exactly 1 way to make amount 0:
    // choose no coins
    dp[0] = 1;

    // Consider each coin one by one
    for (int i = 0; i < n; i++)
    {
        for (int j = coins[i]; j <= V; j++)
        {
            dp[j] = dp[j] + dp[j - coins[i]];
        }
    }

    return dp[V];
}

int main()
{
    int n, V;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    int coins[n];

    printf("Enter coin denominations:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &coins[i]);
    }

    printf("Enter target amount: ");
    scanf("%d", &V);

    int ways = countWays(coins, n, V);

    printf("Total number of ways = %d\n", ways);

    return 0;
}