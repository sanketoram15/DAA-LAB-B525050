#include <stdio.h>

#define MAX 1000

typedef struct {
    int heap[MAX];
    int size;
} MinHeap;

void insert(MinHeap *h, int value) {

    int i = h->size++;
    h->heap[i] = value;

    while (i > 0) {

        int parent = (i - 1) / 2;

        if (h->heap[parent] <= h->heap[i])
            break;

        int temp = h->heap[parent];
        h->heap[parent] = h->heap[i];
        h->heap[i] = temp;

        i = parent;
    }
}

int extractMin(MinHeap *h) {

    int min = h->heap[0];

    h->heap[0] = h->heap[--h->size];

    int i = 0;

    while (1) {

        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < h->size &&
            h->heap[left] < h->heap[smallest])
            smallest = left;

        if (right < h->size &&
            h->heap[right] < h->heap[smallest])
            smallest = right;

        if (smallest == i)
            break;

        int temp = h->heap[i];
        h->heap[i] = h->heap[smallest];
        h->heap[smallest] = temp;

        i = smallest;
    }

    return min;
}

int main() {

    int n;

    printf("Enter number of sticks: ");
    scanf("%d", &n);

    MinHeap h;
    h.size = 0;

    printf("Enter stick lengths:\n");

    for (int i = 0; i < n; i++) {

        int length;
        scanf("%d", &length);

        insert(&h, length);
    }

    int totalCost = 0;

    while (h.size > 1) {

        int first = extractMin(&h);
        int second = extractMin(&h);

        int cost = first + second;

        totalCost += cost;

        printf("Connect %d + %d = %d\n",
               first,
               second,
               cost);

        insert(&h, cost);
    }

    printf("\nMinimum total cost = %d\n",
           totalCost);

    return 0;
}