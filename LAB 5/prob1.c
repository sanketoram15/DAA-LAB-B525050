#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
long long comparisons = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int rand_idx = low + rand() % (high - low + 1);
    swap(&arr[rand_idx], &arr[high]);

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

// In-place QuickSelect: after this call, arr[k] holds the k-th smallest
// element, with arr[0..k-1] <= arr[k] <= arr[k+1..n-1]
int quickSelect(int arr[], int low, int high, int k) {
    if (low == high)
        return arr[low];

    int pivotIndex = partition(arr, low, high);

    if (pivotIndex == k)
        return arr[pivotIndex];
    else if (k < pivotIndex)
        return quickSelect(arr, low, pivotIndex - 1, k);
    else
        return quickSelect(arr, pivotIndex + 1, high, k);
}

// Finds the median IN PLACE (reorders arr). No malloc used.
double findMedian(int arr[], int n) {
    if (n % 2 == 1) {
        return quickSelect(arr, 0, n - 1, n / 2);
    } else {
        int left = quickSelect(arr, 0, n - 1, n / 2 - 1);

        // Right-of-median element = minimum of the untouched right part
        // (guaranteed by the partition invariant above)
        int right = arr[n / 2];
        for (int i = n / 2 + 1; i < n; i++) {
            comparisons++;
            if (arr[i] < right)
                right = arr[i];
        }
        return (left + right) / 2.0;
    }
}
int main() {
    int arr[] = {7, 2, 9, 4, 1, 8, 3, 6};  // even-length example
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    double median = findMedian(arr, n);

    printf("Median = %.2f\n", median);
    printf("Total comparisons = %lld (n=%d, n log2 n = %.1f)\n",
           comparisons, n, n * log2(n));
    return 0;
}