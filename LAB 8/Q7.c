#include <stdio.h>

int main()
{
    int n;

    printf("Enter rod length: ");
    scanf("%d", &n);

    int price[n + 1];
    int dp[n + 1];
    int cut[n + 1];

    price[0] = 0;

    printf("Enter prices for lengths 1 to %d:\n", n);

    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &price[i]);
    }

    // No revenue for rod of length 0
    dp[0] = 0;

    // Calculate maximum revenue
    for (int i = 1; i <= n; i++)
    {
        dp[i] = 0;
        cut[i] = 0;

        for (int j = 1; j <= i; j++)
        {
            if (price[j] + dp[i - j] > dp[i])
            {
                dp[i] = price[j] + dp[i - j];

                // Store the first piece cut
                cut[i] = j;
            }
        }
    }

    printf("\nMaximum Revenue = %d\n", dp[n]);

    // Reconstruction
    printf("Pieces used: ");

    int length = n;

    while (length > 0)
    {
        printf("%d ", cut[length]);

        length = length - cut[length];
    }

    printf("\n");

    return 0;
}