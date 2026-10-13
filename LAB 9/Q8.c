#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct {
    int start;
    int end;
} Meeting;

typedef struct {
    int heap[MAX];
    int size;
} MinHeap;

/* Swap */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Insert into min heap */
void insert(MinHeap *h, int value) {

    int i = h->size++;
    h->heap[i] = value;

    while (i > 0) {

        int parent = (i - 1) / 2;

        if (h->heap[parent] <= h->heap[i])
            break;

        swap(&h->heap[parent], &h->heap[i]);

        i = parent;
    }
}

/* Remove minimum */
int extractMin(MinHeap *h) {

    int minimum = h->heap[0];

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

        swap(&h->heap[i], &h->heap[smallest]);

        i = smallest;
    }

    return minimum;
}

/* Sort according to start time */
int compareMeetings(const void *a, const void *b) {

    Meeting *x = (Meeting *)a;
    Meeting *y = (Meeting *)b;

    return x->start - y->start;
}

int main() {

    int n;

    printf("Enter number of meetings: ");
    scanf("%d", &n);

    Meeting meetings[n];

    printf("Enter start and end time:\n");

    for (int i = 0; i < n; i++) {

        scanf("%d %d",
              &meetings[i].start,
              &meetings[i].end);
    }

    /* Sort by start time */
    qsort(meetings,
          n,
          sizeof(Meeting),
          compareMeetings);

    MinHeap heap;
    heap.size = 0;

    int maxRooms = 0;

    for (int i = 0; i < n; i++) {

        /*
           Remove all meetings that have
           already finished.
        */
        while (heap.size > 0 &&
               heap.heap[0] <= meetings[i].start) {

            extractMin(&heap);
        }

        /* Add current meeting's ending time */
        insert(&heap, meetings[i].end);

        if (heap.size > maxRooms)
            maxRooms = heap.size;
    }

    printf("\nMinimum number of rooms = %d\n",
           maxRooms);

    return 0;
}