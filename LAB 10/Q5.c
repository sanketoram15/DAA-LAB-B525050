#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int parent[MAX];
int size[MAX];

int A[MAX];
int result[MAX];

int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

void unite(int a, int b)
{
    int rootA = find(a);
    int rootB = find(b);

    if (rootA == rootB)
        return;

    if (size[rootA] < size[rootB])
    {
        int temp = rootA;
        rootA = rootB;
        rootB = temp;
    }

    parent[rootB] = rootA;
    size[rootA] += size[rootB];
}

int compareInt(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y)
        return -1;

    if (x > y)
        return 1;

    return 0;
}

int main()
{
    int n, m;
    int i, u, v;
    int root;

    int positions[MAX];
    int values[MAX];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of elements.\n");
        return 1;
    }

    printf("Enter the permutation:\n");

    for (i = 0; i < n; i++)
        scanf("%d", &A[i]);

    // Initialize DSU
    for (i = 0; i < n; i++)
    {
        parent[i] = i;
        size[i] = 1;
    }

    printf("Enter number of allowed swaps: ");
    scanf("%d", &m);

    if (m < 0)
    {
        printf("Invalid number of swaps.\n");
        return 1;
    }

    for (i = 0; i < m; i++)
    {
        printf("Enter allowed swap positions (u v): ");
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= n || v < 0 || v >= n)
        {
            printf("Invalid swap positions.\n");
            return 1;
        }

        unite(u, v);
    }

    // Process every connected component
    for (i = 0; i < n; i++)
    {
        root = find(i);

        if (root != i)
            continue;

        int count = 0;

        // Collect positions and values in this component
        for (int j = 0; j < n; j++)
        {
            if (find(j) == root)
            {
                positions[count] = j;
                values[count] = A[j];
                count++;
            }
        }

        // Sort positions and values
        qsort(positions, count, sizeof(int), compareInt);
        qsort(values, count, sizeof(int), compareInt);

        // Assign sorted values to sorted positions
        for (int j = 0; j < count; j++)
            result[positions[j]] = values[j];
    }

    printf("\nLexicographically smallest permutation:\n");

    for (i = 0; i < n; i++)
        printf("%d ", result[i]);

    printf("\n");

    return 0;
}