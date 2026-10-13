#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

typedef struct {
    char ch;
    int frequency;
} Node;

/* Max heap */
typedef struct {
    Node heap[MAX];
    int size;
} MaxHeap;

void swap(Node *a, Node *b) {

    Node temp = *a;
    *a = *b;
    *b = temp;
}

void insert(MaxHeap *h, Node node) {

    int i = h->size++;

    h->heap[i] = node;

    while (i > 0) {

        int parent = (i - 1) / 2;

        if (h->heap[parent].frequency >=
            h->heap[i].frequency)
            break;

        swap(&h->heap[parent],
             &h->heap[i]);

        i = parent;
    }
}

Node extractMax(MaxHeap *h) {

    Node maxNode = h->heap[0];

    h->heap[0] = h->heap[--h->size];

    int i = 0;

    while (1) {

        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < h->size &&
            h->heap[left].frequency >
            h->heap[largest].frequency)
            largest = left;

        if (right < h->size &&
            h->heap[right].frequency >
            h->heap[largest].frequency)
            largest = right;

        if (largest == i)
            break;

        swap(&h->heap[i],
             &h->heap[largest]);

        i = largest;
    }

    return maxNode;
}

/* Queue node */
typedef struct {
    Node node;
    int availableTime;
} Cooldown;

int main() {

    char str[1000];
    int k;

    printf("Enter string: ");
    scanf("%s", str);

    printf("Enter K: ");
    scanf("%d", &k);

    int freq[256] = {0};

    int length = strlen(str);

    for (int i = 0; i < length; i++) {
        freq[(unsigned char)str[i]]++;
    }

    MaxHeap heap;
    heap.size = 0;

    /* Insert all characters into max heap */
    for (int i = 0; i < 256; i++) {

        if (freq[i] > 0) {

            Node node;

            node.ch = (char)i;
            node.frequency = freq[i];

            insert(&heap, node);
        }
    }

    Cooldown queue[MAX];

    int front = 0;
    int rear = 0;

    char result[1000];

    int resultIndex = 0;

    int time = 0;

    while (resultIndex < length) {

        /*
           Make characters available again
           when their cooldown is over.
        */
        if (front < rear &&
            queue[front].availableTime <= time) {

            insert(&heap, queue[front].node);

            front++;
        }

        /*
           No character is available.
        */
        if (heap.size == 0) {

            printf("\nReorganisation is not possible.\n");

            return 0;
        }

        Node current = extractMax(&heap);

        result[resultIndex++] = current.ch;

        current.frequency--;

        /*
           If character still exists,
           put it into cooldown queue.
        */
        if (current.frequency > 0) {

            queue[rear].node = current;

            queue[rear].availableTime =
                time + k;

            rear++;
        }

        time++;
    }

    result[resultIndex] = '\0';

    printf("\nReorganised string = %s\n",
           result);

    return 0;
}