#include <stdio.h>
#include <string.h>

#define MAX_STRINGS 100
#define MAX_LEN 1000

/*
   Find maximum suffix-prefix overlap.

   Example:

   A = abcde
   B = cdef

   overlap = "cde"

   A + remaining part of B
   = abcdef
*/
int findOverlap(char *a, char *b) {

    int lenA = strlen(a);
    int lenB = strlen(b);

    int maxOverlap = 0;

    int maxPossible =
        lenA < lenB ? lenA : lenB;

    for (int k = 1; k <= maxPossible; k++) {

        int match = 1;

        for (int i = 0; i < k; i++) {

            if (a[lenA - k + i] != b[i]) {

                match = 0;
                break;
            }
        }

        if (match)
            maxOverlap = k;
    }

    return maxOverlap;
}

/*
   Merge two strings using their overlap
*/
void mergeStrings(char *a,
                  char *b,
                  char *result) {

    int lenA = strlen(a);
    int lenB = strlen(b);

    int overlap =
        findOverlap(a, b);

    strcpy(result, a);

    strcat(result,
           b + overlap);
}

/*
   Remove duplicate / contained strings
*/
void removeContained(char strings[][MAX_LEN],
                     int *n) {

    for (int i = 0; i < *n; i++) {

        for (int j = 0; j < *n; j++) {

            if (i == j)
                continue;

            if (strstr(strings[i],
                       strings[j]) != NULL) {

                /*
                   strings[j] is already contained
                   inside strings[i].
                */

                if (strlen(strings[i]) >=
                    strlen(strings[j])) {

                    for (int k = j;
                         k < *n - 1;
                         k++) {

                        strcpy(strings[k],
                               strings[k + 1]);
                    }

                    (*n)--;

                    j--;
                }
            }
        }
    }
}

int main() {

    int n;

    char strings[MAX_STRINGS][MAX_LEN];

    printf("Enter number of strings: ");
    scanf("%d", &n);

    printf("Enter strings:\n");

    for (int i = 0; i < n; i++) {

        scanf("%s", strings[i]);
    }

    /*
       Remove strings already contained
       in another string.
    */
    removeContained(strings, &n);

    /*
       Greedy merging.
    */
    while (n > 1) {

        int bestI = -1;
        int bestJ = -1;
        int bestOverlap = -1;

        /*
           Find pair with maximum overlap.
        */
        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                if (i == j)
                    continue;

                int overlap =
                    findOverlap(strings[i],
                                strings[j]);

                if (overlap > bestOverlap) {

                    bestOverlap = overlap;

                    bestI = i;
                    bestJ = j;
                }
            }
        }

        /*
           Merge best pair.
        */
        char merged[MAX_LEN];

        mergeStrings(strings[bestI],
                     strings[bestJ],
                     merged);

        printf("\nMerge:\n");

        printf("%s + %s\n",
               strings[bestI],
               strings[bestJ]);

        printf("Overlap = %d\n",
               bestOverlap);

        printf("Result = %s\n",
               merged);

        /*
           Replace first string with merged string.
        */
        strcpy(strings[bestI], merged);

        /*
           Remove second string.
        */
        for (int i = bestJ;
             i < n - 1;
             i++) {

            strcpy(strings[i],
                   strings[i + 1]);
        }

        n--;
    }

    printf("\n=================================\n");

    printf("Greedy Superstring:\n");

    printf("%s\n", strings[0]);

    printf("Length = %lu\n",
           strlen(strings[0]));

    printf("=================================\n");

    return 0;
