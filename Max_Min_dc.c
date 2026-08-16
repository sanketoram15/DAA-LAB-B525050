/**
 * Program: Max and Min using Divide & Conquer Approach
 * ---------------------------------------------------
 * Problem Statement:
 *   Find the maximum and minimum elements in an array of size n using 
 *   Divide & Conquer such that total comparisons <= 3n/2.
 *
 * Algorithm Recurrence:
 *   T(n) = 2T(n/2) + 2
 *   Base cases:
 *     T(1) = 0 comparisons
 *     T(2) = 1 comparison
 *   Total Comparisons = 3n/2 - 2 (for n power of 2)
 */

#include <stdio.h>

// Structure to return both min and max from recursive calls
typedef struct {
    int min;
    int max;
} MinMax;

/**
 * Function: getMinMax
 * -------------------
 * Recursively divides the array into sub-problems and combines 
 * min and max values.
 *
 * Parameters:
 *   arr[] - Array of integers
 *   low   - Starting index of current sub-array
 *   high  - Ending index of current sub-array
 *
 * Returns:
 *   MinMax struct containing the min and max of arr[low..high]
 */
MinMax getMinMax(int arr[], int low, int high) {
    MinMax result, left, right;
    int mid;

    // Base Case 1: Sub-array contains only 1 element
    // Comparisons: 0
    if (low == high) {
        result.min = arr[low];
        result.max = arr[low];
        return result;
    }

    // Base Case 2: Sub-array contains 2 elements
    // Comparisons: 1
    if (high == low + 1) {
        if (arr[low] > arr[high]) {
            result.max = arr[low];
            result.min = arr[high];
        } else {
            result.max = arr[high];
            result.min = arr[low];
        }
        return result;
    }

    // Divide Step: Find the midpoint
    mid = low + (high - low) / 2;

    // Conquer Step: Recursively solve left and right halves
    left = getMinMax(arr, low, mid);
    right = getMinMax(arr, mid + 1, high);

    // Combine Step: Compare results of both halves (2 comparisons)
    // Comparison 1: For finding overall maximum
    if (left.max > right.max) {
        result.max = left.max;
    } else {
        result.max = right.max;
    }

    // Comparison 2: For finding overall minimum
    if (left.min < right.min) {
        result.min = left.min;
    } else {
        result.min = right.min;
    }

    return result;
}

int main() {
    int arr[] = {1000, 11, 445, 1, 330, 3000, -5, 89};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Function Call
    MinMax result = getMinMax(arr, 0, n - 1);

    // Output Results
    printf("Array elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    printf("Minimum element : %d\n", result.min);
    printf("Maximum element : %d\n", result.max);
    
    // Display Comparison Bound Verification
    printf("Expected Max Comparisons (3n/2): %.0f\n", (3.0 * n) / 2.0);

    return 0;
}
