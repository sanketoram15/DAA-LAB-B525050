#include <stdio.h>

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int A[n];
    int dp[n];

    printf("Enter elements:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
        dp[i] = 1;
    }

    // Find LIS
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (A[i] > A[j])
            {
                if (dp[j] + 1 > dp[i])
                    dp[i] = dp[j] + 1;
            }
        }
    }

    // Find maximum value in dp[]
    int max = dp[0];

    for (int i = 1; i < n; i++)
    {
        if (dp[i] > max)
            max = dp[i];
    }

    printf("Length of LIS = %d\n", max);

    return 0;
}