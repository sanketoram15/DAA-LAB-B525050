#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define N 1000
int arr[N];
long long comparisons = 0;
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}
void heapify(int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n) {
        comparisons++;
        if (arr[left] > arr[largest])
            largest = left;
    }
    if (right < n) {
        comparisons++;
        if (arr[right] > arr[largest])
            largest = right;
    }
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(n, largest);
    }
}
void heapSort() {
    for (int i = N / 2 - 1; i >= 0; i--) {
        heapify(N, i);
    }

    for (int i = N - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(i, 0);
    }
}
int main() {
    srand(time(NULL));
    FILE *fp = fopen("input.txt", "w");
    for (int i = 0; i < N; i++) {
        fprintf(fp, "%d\n", rand() % 100000);
    }
    fclose(fp);
    fp = fopen("input.txt", "r");
    for (int i = 0; i < N; i++) {
        fscanf(fp, "%d", &arr[i]);
    }
    fclose(fp);
    heapSort();
    printf("HeapSort completed for n = %d\n", N);
    printf("Comparisons made = %lld\n", comparisons);
    printf("n log2 n = %.1f\n", N * log2(N));
    return 0;
}