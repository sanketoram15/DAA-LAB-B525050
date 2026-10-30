#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 1005
#define INF INT_MAX

typedef struct {
int to;

int weight;
int next;
} Edge;

Edge edges[MAX * MAX];
int head[MAX];
int edgeCount = 0;

void addEdge(int u, int v, int w) {
edges[edgeCount].to = v;
edges[edgeCount].weight = w;
edges[edgeCount].next = head[u];
head[u] = edgeCount++;
}

typedef struct {
int vertex;
int parity;
} State;

State deque[MAX * MAX * 2];
int front = 0, rear = 0;

void pushFront(int vertex, int parity) {
front = (front - 1 + MAX * MAX * 2) % (MAX * MAX * 2);
deque[front].vertex = vertex;
deque[front].parity = parity;
}

void pushBack(int vertex, int parity) {
deque[rear].vertex = vertex;
deque[rear].parity = parity;
rear = (rear + 1) % (MAX * MAX * 2);
}

State popFront() {
State s = deque[front];
front = (front + 1) % (MAX * MAX * 2);
return s;
}

int isEmpty() {
return front == rear;
}

int dist[MAX][2];

int main() {
int V, E;
int P, C;


printf("Enter number of vertices and edges: ");
scanf("%d %d", &V, &E);

for (int i = 0; i < MAX; i++)
    head[i] = -1;

printf("Enter directed edges (u v weight):\n");

for (int i = 0; i < E; i++) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);

    if (w != 0 && w != 1) {
        printf("Invalid edge weight!\n");
        return 1;
    }

    addEdge(u, v, w);
}

printf("Enter source vertex P and cost C: ");
scanf("%d %d", &P, &C);

for (int i = 1; i <= V; i++) {
    dist[i][0] = INF;
    dist[i][1] = INF;
}

front = rear = 0;

// Initially, zero weight-1 edges have been used.
dist[P][0] = 0;
pushFront(P, 0);

while (!isEmpty()) {
    State current = popFront();

    int u = current.vertex;
    int parity = current.parity;

    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        int w = edges[i].weight;

        // Weight 1 changes parity; weight 0 does not.
        int newParity = parity ^ w;

        if (dist[u][parity] != INF &&
            dist[v][newParity] > dist[u][parity] + w) {

            dist[v][newParity] = dist[u][parity] + w;

            if (w == 0)
                pushFront(v, newParity);
            else
                pushBack(v, newParity);
        }
    }
}

printf("\nMinimum costs with an EVEN number of weight-1 edges:\n");

for (int i = 1; i <= V; i++) {
    if (dist[i][0] == INF) {
        printf("Vertex %d: Unreachable\n", i);
    } else {
        printf("Vertex %d: %d", i, dist[i][0]);

        if (dist[i][0] <= C)
            printf(" (Cost <= C)\n");
        else
            printf(" (Cost > C)\n");
    }
}

return 0;

}
