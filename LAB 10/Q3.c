#include <stdio.h>

#define MAX 1000

int parent[MAX];
int size[MAX];
long long weight[MAX];

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
    weight[rootA] += weight[rootB];
}

long long maximumWeight(int n, int K)
{
    long long maximum = 0;
    int i, root;

    for (i = 0; i < n; i++)
    {
        root = find(i);

        if (root == i && size[root] <= K)
        {
            if (weight[root] > maximum)
                maximum = weight[root];
        }
    }

    return maximum;
}

int main()
{
    int n, m, K;
    int i, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter number of edges: ");
    scanf("%d", &m);

    printf("Enter size constraint K: ");
    scanf("%d", &K);

    if (m < 0 || K < 1)
    {
        printf("Invalid input.\n");
        return 1;
    }

    // Initialize vertices
    for (i = 0; i < n; i++)
    {
        parent[i] = i;
        size[i] = 1;

        printf("Enter weight of vertex %d: ", i);
        scanf("%lld", &weight[i]);
    }

    printf("Initial maximum weight: %lld\n",
           maximumWeight(n, K));

    for (i = 0; i < m; i++)
    {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= n || v < 0 || v >= n)
        {
            printf("Invalid edge.\n");
            i--;
            continue;
        }

        unite(u, v);

        printf("Maximum weight with size <= %d: %lld\n",
               K, maximumWeight(n, K));
    }

    return 0;
}