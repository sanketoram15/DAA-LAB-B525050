#include <stdio.h>

#define MAX 100

int graph[MAX][MAX];
int color[MAX];
int n;

// Check whether the graph is bipartite using BFS
int isBipartite()
{
    int queue[MAX];
    int front, rear;
    int i, u, v;

    for (i = 0; i < n; i++)
        color[i] = -1;

    for (i = 0; i < n; i++)
    {
        if (color[i] == -1)
        {
            front = rear = 0;

            queue[rear++] = i;
            color[i] = 0;

            while (front < rear)
            {
                u = queue[front++];

                for (v = 0; v < n; v++)
                {
                    if (graph[u][v])
                    {
                        if (color[v] == -1)
                        {
                            color[v] = 1 - color[u];
                            queue[rear++] = v;
                        }
                        else if (color[v] == color[u])
                        {
                            return 0;
                        }
                    }
                }
            }
        }
    }

    return 1;
}

int main()
{
    int m, u, v, i;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &m);

    for (i = 0; i < m; i++)
    {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);

        // Convert to zero-based indexing
        if (u < 0 || u >= n || v < 0 || v >= n || u == v)
        {
            printf("Invalid edge. Skipped.\n");
            continue;
        }

        // Add edge temporarily
        graph[u][v] = 1;
        graph[v][u] = 1;

        if (isBipartite())
        {
            printf("Edge (%d, %d) ACCEPTED\n", u, v);
        }
        else
        {
            // Remove edge if it violates bipartiteness
            graph[u][v] = 0;
            graph[v][u] = 0;

            printf("Edge (%d, %d) REJECTED: Odd cycle detected\n",
                   u, v);
        }
    }

    return 0;
}