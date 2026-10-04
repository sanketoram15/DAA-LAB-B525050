#include <stdio.h>
#include <string.h>

int min(int a, int b, int c)
{
    if (a < b && a < c)
        return a;
    else if (b < c)
        return b;
    else
        return c;
}

int main()
{
    char A[100], B[100];

    printf("Enter first string: ");
    scanf("%s", A);

    printf("Enter second string: ");
    scanf("%s", B);

    int m = strlen(A);
    int n = strlen(B);

    int dp[m + 1][n + 1];

    // Initialization
    for (int i = 0; i <= m; i++)
        dp[i][0] = i;

    for (int j = 0; j <= n; j++)
        dp[0][j] = j;

    // Fill DP table
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (A[i - 1] == B[j - 1])
            {
                // Characters are same
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                int insertion = dp[i][j - 1] + 1;
                int deletion = dp[i - 1][j] + 1;
                int substitution = dp[i - 1][j - 1] + 1;

                dp[i][j] = min(insertion, deletion, substitution);
            }
        }
    }

    printf("\nMinimum Edit Distance = %d\n", dp[m][n]);

    // Traceback
    printf("\nTraceback:\n");

    int i = m;
    int j = n;

    while (i > 0 || j > 0)
    {
        // Characters are same
        if (i > 0 && j > 0 && A[i - 1] == B[j - 1])
        {
            printf("Match: %c\n", A[i - 1]);

            i--;
            j--;
        }

        // Substitution
        else if (i > 0 && j > 0 &&
                 dp[i][j] == dp[i - 1][j - 1] + 1)
        {
            printf("Substitute %c -> %c\n",
                   A[i - 1], B[j - 1]);

            i--;
            j--;
        }

        // Deletion
        else if (i > 0 &&
                 dp[i][j] == dp[i - 1][j] + 1)
        {
            printf("Delete: %c\n", A[i - 1]);

            i--;
        }

        // Insertion
        else
        {
            printf("Insert: %c\n", B[j - 1]);

            j--;
        }
    }

    return 0;
}