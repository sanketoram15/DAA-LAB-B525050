#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct Node {
    char symbol;
    int frequency;
    int isLeaf;

    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    Node *data[MAX];
    int size;
} MinHeap;

/* Create a new node */
Node* createNode(char symbol, int frequency, int isLeaf) {
    Node *newNode = (Node*)malloc(sizeof(Node));

    newNode->symbol = symbol;
    newNode->frequency = frequency;
    newNode->isLeaf = isLeaf;

    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

/* Swap two nodes */
void swap(Node **a, Node **b) {
    Node *temp = *a;
    *a = *b;
    *b = temp;
}

/* Insert into min heap */
void insertHeap(MinHeap *heap, Node *node) {
    int i = heap->size++;

    heap->data[i] = node;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap->data[parent]->frequency <=
            heap->data[i]->frequency)
            break;

        swap(&heap->data[parent], &heap->data[i]);

        i = parent;
    }
}

/* Remove minimum */
Node* extractMin(MinHeap *heap) {
    Node *minNode = heap->data[0];

    heap->data[0] = heap->data[--heap->size];

    int i = 0;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap->size &&
            heap->data[left]->frequency <
            heap->data[smallest]->frequency)
            smallest = left;

        if (right < heap->size &&
            heap->data[right]->frequency <
            heap->data[smallest]->frequency)
            smallest = right;

        if (smallest == i)
            break;

        swap(&heap->data[i], &heap->data[smallest]);

        i = smallest;
    }

    return minNode;
}

/* Store Huffman code lengths */
void findLengths(Node *root, int depth, int lengths[]) {

    if (root == NULL)
        return;

    if (root->isLeaf) {
        lengths[(unsigned char)root->symbol] = depth;
        return;
    }

    findLengths(root->left, depth + 1, lengths);
    findLengths(root->right, depth + 1, lengths);
}

/* Structure for canonical codes */
typedef struct {
    char symbol;
    int length;
    char code[100];
} Canonical;

int compareCanonical(const void *a, const void *b) {

    Canonical *x = (Canonical*)a;
    Canonical *y = (Canonical*)b;

    if (x->length != y->length)
        return x->length - y->length;

    return x->symbol - y->symbol;
}

/* Convert number to binary string */
void makeBinary(unsigned long long number,
                int length,
                char code[]) {

    for (int i = length - 1; i >= 0; i--) {
        code[length - 1 - i] =
            ((number >> i) & 1) ? '1' : '0';
    }

    code[length] = '\0';
}

int main() {

    int n;

    printf("Enter number of symbols: ");
    scanf("%d", &n);

    MinHeap heap;
    heap.size = 0;

    for (int i = 0; i < n; i++) {

        char symbol;
        int frequency;

        printf("Enter symbol and frequency: ");
        scanf(" %c %d", &symbol, &frequency);

        Node *node =
            createNode(symbol, frequency, 1);

        insertHeap(&heap, node);
    }

    /* Build Huffman tree */
    while (heap.size > 1) {

        Node *left = extractMin(&heap);
        Node *right = extractMin(&heap);

        Node *parent =
            createNode('\0',
                       left->frequency + right->frequency,
                       0);

        parent->left = left;
        parent->right = right;

        insertHeap(&heap, parent);
    }

    Node *root = extractMin(&heap);

    int lengths[256] = {0};

    findLengths(root, 0, lengths);

    Canonical codes[MAX];

    for (int i = 0; i < n; i++) {
        /*
           We need to traverse symbols from input again.
           For simplicity, collect them from the tree.
        */
    }

    /* Collect leaf symbols from tree */
    int count = 0;

    void collect(Node *node) {
        if (node == NULL)
            return;

        if (node->isLeaf) {
            codes[count].symbol = node->symbol;
            codes[count].length =
                lengths[(unsigned char)node->symbol];
            count++;
            return;
        }

        collect(node->left);
        collect(node->right);
    }

    collect(root);

    /* Sort by length, then symbol */
    qsort(codes,
          count,
          sizeof(Canonical),
          compareCanonical);

    unsigned long long currentCode = 0;
    int previousLength = codes[0].length;

    for (int i = 0; i < count; i++) {

        if (i == 0) {
            currentCode = 0;
        }
        else {
            currentCode++;

            currentCode =
                currentCode <<
                (codes[i].length - previousLength);
        }

        makeBinary(currentCode,
                   codes[i].length,
                   codes[i].code);

        previousLength = codes[i].length;
    }

    printf("\nCanonical Huffman Codes:\n");
    printf("------------------------\n");

    for (int i = 0; i < count; i++) {

        printf("%c : length = %d, code = %s\n",
               codes[i].symbol,
               codes[i].length,
               codes[i].code);
    }

    return 0;
}