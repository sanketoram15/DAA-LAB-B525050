#include <stdio.h>

#define MAX 1000

typedef struct {
    int heap[MAX];
    int size;
} MaxHeap;

/* Swap */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Insert into max heap */
void insert(MaxHeap *h, int value) {

    int i = h->size++;
    h->heap[i] = value;

    while (i > 0) {

        int parent = (i - 1) / 2;

        if (h->heap[parent] >= h->heap[i])
            break;

        swap(&h->heap[parent], &h->heap[i]);

        i = parent;
    }
}

/* Extract maximum */
int extractMax(MaxHeap *h) {

    int max = h->heap[0];

    h->heap[0] = h->heap[--h->size];

    int i = 0;

    while (1) {

        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < h->size &&
            h->heap[left] > h->heap[largest])
            largest = left;

        if (right < h->size &&
            h->heap[right] > h->heap[largest])
            largest = right;

        if (largest == i)
            break;

        swap(&h->heap[i], &h->heap[largest]);

        i = largest;
    }

    return max;
}

int main() {

    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    MaxHeap heap;
    heap.size = 0;

    int minimum = 1000000000;

    printf("Enter elements:\n");

    for (int i = 0; i < n; i++) {

        int x;
        scanf("%d", &x);

        /*
           If odd, multiply by 2
           so that it becomes even.
        */
        if (x % 2 != 0)
            x = x * 2;

        if (x < minimum)
            minimum = x;

        insert(&heap, x);
    }

    int answer = 1000000000;

    while (heap.size > 0) {

        int maximum = extractMax(&heap);

        int deviation = maximum - minimum;

        if (deviation < answer)
            answer = deviation;

        /*
           Maximum is odd.
           It cannot be divided further.
        */
        if (maximum % 2 != 0)
            break;

        maximum = maximum / 2;

        if (maximum < minimum)
            minimum = maximum;

        insert(&heap, maximum);
    }

    printf("\nMinimum deviation = %d\n", answer);

    return 0;
}