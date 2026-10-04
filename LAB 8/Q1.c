#include <stdio.h>
#include <limits.h>

int minCoins(int coins[], int m, int V)
{
    // dp[i] = minimum number of coins needed to make amount i
    int dp[V + 1];

    dp[0] = 0;

    // Initialize all values as infinity
    for (int i = 1; i <= V; i++)
        dp[i] = INT_MAX;

    // Calculate minimum coins for every amount
    for (int i = 1; i <= V; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX)
            {
                int result = dp[i - coins[j]] + 1;

                if (result < dp[i])
                    dp[i] = result;
            }
        }
    }

    // If amount cannot be formed
    if (dp[V] == INT_MAX)
        return -1;

    return dp[V];
}

int main()
{
    int m, V;

    printf("Enter number of coin denominations: ");
    scanf("%d", &m);

    int coins[m];

    printf("Enter coin denominations:\n");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &coins[i]);
    }

    printf("Enter target amount: ");
    scanf("%d", &V);

    int answer = minCoins(coins, m, V);

    if (answer == -1)
        printf("Amount cannot be made using given coins.\n");
    else
        printf("Minimum number of coins = %d\n", answer);

    return 0;
}