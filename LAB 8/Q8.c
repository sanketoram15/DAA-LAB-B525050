#include <stdio.h>

#define MAX 20
#define INF 999999.0

int main()
{
    int n;

    double p[MAX], q[MAX];

    double e[MAX][MAX];
    double w[MAX][MAX];

    int root[MAX][MAX];

    printf("Enter number of keys: ");
    scanf("%d", &n);

    printf("\nEnter successful search probabilities p[1] to p[%d]:\n", n);

    for (int i = 1; i <= n; i++)
    {
        scanf("%lf", &p[i]);
    }

    printf("\nEnter unsuccessful search probabilities q[0] to q[%d]:\n", n);

    for (int i = 0; i <= n; i++)
    {
        scanf("%lf", &q[i]);
    }

    // Initialization
    for (int i = 1; i <= n + 1; i++)
    {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    // Calculate weight and expected cost
    for (int length = 1; length <= n; length++)
    {
        for (int i = 1; i <= n - length + 1; i++)
        {
            int j = i + length - 1;

            e[i][j] = INF;

            w[i][j] = w[i][j - 1] + p[j] + q[j];

            // Try every key as root
            for (int r = i; r <= j; r++)
            {
                double cost = e[i][r - 1]
                            + e[r + 1][j]
                            + w[i][j];

                if (cost < e[i][j])
                {
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\nMinimum Expected Search Cost = %.3lf\n", e[1][n]);

    printf("Root of Optimal BST = Key %d\n", root[1][n]);

    printf("\nRoot information for subtrees:\n");

    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            printf("Keys %d to %d -> Root = Key %d\n",
                   i, j, root[i][j]);
        }
    }

    return 0;
}