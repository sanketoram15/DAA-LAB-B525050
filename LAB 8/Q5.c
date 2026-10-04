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

        // Initially, only A[i] is included
        dp[i] = A[i];
    }

    // Find maximum sum increasing subsequence
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (A[i] > A[j])
            {
                if (dp[j] + A[i] > dp[i])
                {
                    dp[i] = dp[j] + A[i];
                }
            }
        }
    }

    // Find maximum value in dp[]
    int maxSum = dp[0];

    for (int i = 1; i < n; i++)
    {
        if (dp[i] > maxSum)
            maxSum = dp[i];
    }

    printf("Maximum Sum Increasing Subsequence = %d\n", maxSum);

    return 0;
}