#include <stdio.h>
#include <limits.h>

#define MAX 100

typedef struct Node {
    int left;
    int right;
    int symbol;
} Node;

int weight[MAX];
int prefix[MAX];

long long dp[MAX][MAX];
int split[MAX][MAX];

/* Calculate sum of weights from l to r */
int rangeSum(int l, int r) {

    return prefix[r + 1] - prefix[l];
}

/*
   Build optimal alphabetic binary tree
*/
long long solve(int l, int r) {

    if (l == r)
        return 0;

    if (dp[l][r] != -1)
        return dp[l][r];

    long long best = LLONG_MAX;

    int bestK = -1;

    /*
       Try every possible division point.

       Left:
       l ... k

       Right:
       k+1 ... r
    */
    for (int k = l; k < r; k++) {

        long long leftCost =
            solve(l, k);

        long long rightCost =
            solve(k + 1, r);

        long long cost =
            leftCost +
            rightCost +
            rangeSum(l, r);

        if (cost < best) {

            best = cost;
            bestK = k;
        }
    }

    split[l][r] = bestK;

    dp[l][r] = best;

    return best;
}

/*
   Print tree structure
*/
void printTree(int l, int r, int depth) {

    if (l == r) {

        printf("Symbol %c : Depth = %d\n",
               'A' + l,
               depth);

        return;
    }

    int k = split[l][r];

    printTree(l, k, depth + 1);

    printTree(k + 1, r, depth + 1);
}

int main() {

    int n;

    printf("Enter number of symbols: ");
    scanf("%d", &n);

    printf("Enter weights in alphabetic order:\n");

    for (int i = 0; i < n; i++) {

        scanf("%d", &weight[i]);
    }

    /*
       Prefix sum
    */
    prefix[0] = 0;

    for (int i = 0; i < n; i++) {

        prefix[i + 1] =
            prefix[i] + weight[i];
    }

    /*
       Initialize DP table
    */
    for (int i = 0; i < MAX; i++) {

        for (int j = 0; j < MAX; j++) {

            dp[i][j] = -1;
            split[i][j] = -1;
        }
    }

    /*
       Find optimal alphabetic tree
    */
    long long optimalCost =
        solve(0, n - 1);

    printf("\nMinimum weighted path length = %lld\n",
           optimalCost);

    printf("\nAlphabetic Tree Code Lengths:\n");

    printTree(0, n - 1, 0);

    return 0;
}