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
int partition(int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}
void quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
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
    quickSort(0, N - 1);
    printf("QuickSort completed for n = %d\n", N);
    printf("Comparisons made = %lld\n", comparisons);
    printf("Average(n log2 n) = %.1f\n", N * log2(N));
    printf("Worst(n^2) = %d\n", N * N);
    return 0;
}