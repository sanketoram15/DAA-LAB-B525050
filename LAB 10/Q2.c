#include <stdio.h>

#define MAX 10000

int parent[MAX];
int size[MAX];
int land[MAX];

int rows, cols;
int islands = 0;

// Convert grid coordinates to a single index
int getIndex(int r, int c)
{
    return r * cols + c;
}

// Find the representative of a set
int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

// Merge two sets
int unite(int a, int b)
{
    int rootA = find(a);
    int rootB = find(b);

    if (rootA == rootB)
        return 0;

    // Union by size
    if (size[rootA] < size[rootB])
    {
        int temp = rootA;
        rootA = rootB;
        rootB = temp;
    }

    parent[rootB] = rootA;
    size[rootA] += size[rootB];

    return 1;
}

// Add a land cell
int addLand(int r, int c)
{
    int index = getIndex(r, c);
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    int i, nr, nc, neighbor;

    // Ignore duplicate operations
    if (land[index])
        return islands;

    land[index] = 1;
    parent[index] = index;
    size[index] = 1;

    islands++;

    // Check four neighboring cells
    for (i = 0; i < 4; i++)
    {
        nr = r + dr[i];
        nc = c + dc[i];

        if (nr >= 0 && nr < rows &&
            nc >= 0 && nc < cols)
        {
            neighbor = getIndex(nr, nc);

            if (land[neighbor])
            {
                if (unite(index, neighbor))
                    islands--;
            }
        }
    }

    return islands;
}

int main()
{
    int k, i, r, c;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    if (rows <= 0 || cols <= 0 ||
        (long long)rows * cols > MAX)
    {
        printf("Invalid grid size.\n");
        return 1;
    }

    printf("Enter number of operations: ");
    scanf("%d", &k);

    for (i = 0; i < k; i++)
    {
        printf("Enter land cell (row column): ");
        scanf("%d %d", &r, &c);

        if (r < 0 || r >= rows || c < 0 || c >= cols)
        {
            printf("Invalid cell. Island count: %d\n", islands);
            continue;
        }

        printf("Number of islands: %d\n", addLand(r, c));
    }

    return 0;
}