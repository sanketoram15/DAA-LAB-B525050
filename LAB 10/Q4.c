#include <stdio.h>

#define MAX 1000

int parent[MAX];
int active[MAX];
int size[MAX];

long long weight[MAX];

int graph[MAX][MAX];

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

long long maximumComponentWeight(int n)
{
    long long maximum = 0;
    int i, root;

    for (i = 0; i < n; i++)
    {
        if (active[i])
        {
            root = find(i);

            if (root == i && weight[root] > maximum)
                maximum = weight[root];
        }
    }

    return maximum;
}

int main()
{
    int n, m;
    int i, u, v;
    int order[MAX];
    long long answer[MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter number of edges: ");
    scanf("%d", &m);

    if (m < 0 || m > n * (n - 1) / 2)
    {
        printf("Invalid number of edges.\n");
        return 1;
    }

    // Initialize DSU and read vertex weights
    for (i = 0; i < n; i++)
    {
        parent[i] = i;
        size[i] = 1;
        active[i] = 0;

        printf("Enter weight of vertex %d: ", i);
        scanf("%lld", &weight[i]);
    }

    // Read undirected edges
    for (i = 0; i < m; i++)
    {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= n || v < 0 || v >= n || u == v)
        {
            printf("Invalid edge.\n");
            return 1;
        }

        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    // Read deletion order
    printf("Enter deletion order of vertices: ");

    for (i = 0; i < n; i++)
        scanf("%d", &order[i]);

    // Process deletions in reverse
    for (i = n - 1; i >= 0; i--)
    {
        u = order[i];

        if (u < 0 || u >= n || active[u])
        {
            printf("Invalid deletion order.\n");
            return 1;
        }

        active[u] = 1;
        parent[u] = u;
        size[u] = 1;

        // Join with active neighbors
        for (v = 0; v < n; v++)
        {
            if (graph[u][v] && active[v])
                unite(u, v);
        }

        answer[i] = maximumComponentWeight(n);
    }

    printf("\nMaximum component weight after each deletion:\n");

    for (i = 0; i < n; i++)
        printf("%lld ", answer[i]);

    printf("\n");

    return 0;
}