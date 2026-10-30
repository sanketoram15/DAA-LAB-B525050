#include <stdio.h>
#include <stdlib.h>

#define MAX 1005

int adj[MAX][MAX];
int dist[MAX];
int owner[MAX];
int queue[MAX * MAX];

int main() {
int V, E, K, R;
int hub[MAX];


printf("Enter number of vertices and edges: ");
scanf("%d %d", &V, &E);

for (int i = 1; i <= V; i++) {
    for (int j = 1; j <= V; j++) {
        adj[i][j] = 0;
    }
}

printf("Enter edges (u v):\n");

for (int i = 0; i < E; i++) {
    int u, v;
    scanf("%d %d", &u, &v);

    adj[u][v] = 1;
    adj[v][u] = 1;
}

printf("Enter number of hubs K and radius R: ");
scanf("%d %d", &K, &R);

printf("Enter hub vertices:\n");

for (int i = 1; i <= K; i++) {
    scanf("%d", &hub[i]);
}

for (int i = 1; i <= V; i++) {
    dist[i] = -1;
    owner[i] = -1;
}

int front = 0;
int rear = 0;

for (int i = 1; i <= K; i++) {
    int h = hub[i];

    if (dist[h] == -1) {
        dist[h] = 0;
        owner[h] = i;
        queue[rear++] = h;
    } else if (i < owner[h]) {
        owner[h] = i;
    }
}

while (front < rear) {
    int u = queue[front++];

    for (int v = 1; v <= V; v++) {
        if (adj[u][v] == 1) {
            int newDist = dist[u] + 1;

            if (newDist > R) {
                continue;
            }

            if (dist[v] == -1) {
                dist[v] = newDist;
                owner[v] = owner[u];
                queue[rear++] = v;
            } else if (newDist == dist[v] &&
                       owner[u] < owner[v]) {
                owner[v] = owner[u];
            }
        }
    }
}

printf("\nVertex\tOwner\tDistance\n");

for (int i = 1; i <= V; i++) {
    if (dist[i] == -1 || dist[i] > R) {
        printf("%d\t-1\t-1\n", i);
    } else {
        printf("%d\t%d\t%d\n", i, owner[i], dist[i]);
    }
}

return 0;


}
