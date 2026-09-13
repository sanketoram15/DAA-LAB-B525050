/*
 * Q5 - Hitting a Moving Target
 *
 * There are n hiding spots arranged in a straight line.
 * The target moves to an adjacent spot between every two shots.
 *
 * The program generates a shooting sequence and verifies
 * whether the target can always be hit.
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 */

#include <stdio.h>

#define MAX 100

int possible[MAX + 1];
int nextPossible[MAX + 1];

/*
 * Generate the shooting sequence.
 */
void generateShots(int n, int shots[], int *count)
{
    int i;

    *count = 0;

    if (n == 2)
    {
        shots[(*count)++] = 1;
        shots[(*count)++] = 1;
    }
    else if (n % 2 == 0)
    {
        /*
         * Even n:
         * 2,3,...,n-1,n-1,...,3,2
         */
        for (i = 2; i <= n - 1; i++)
            shots[(*count)++] = i;

        for (i = n - 1; i >= 2; i--)
            shots[(*count)++] = i;
    }
    else
    {
        /*
         * Odd n:
         * 2,3,...,n-1,2,3,...,n-1
         */
        for (i = 2; i <= n - 1; i++)
            shots[(*count)++] = i;

        for (i = 2; i <= n - 1; i++)
            shots[(*count)++] = i;
    }
}

/*
 * Move all possible target positions to their
 * adjacent positions.
 */
void moveTarget(int n)
{
    int i;

    for (i = 1; i <= n; i++)
        nextPossible[i] = 0;

    for (i = 1; i <= n; i++)
    {
        if (possible[i])
        {
            if (i - 1 >= 1)
                nextPossible[i - 1] = 1;

            if (i + 1 <= n)
                nextPossible[i + 1] = 1;
        }
    }

    for (i = 1; i <= n; i++)
        possible[i] = nextPossible[i];
}

int main()
{
    int n;
    int shots[2 * MAX];
    int shotCount;
    int i, j;
    int remaining;

    printf("HITTING A MOVING TARGET\n");
    printf("-----------------------\n");

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);

    if (n <= 1 || n > MAX)
    {
        printf("Invalid input!\n");
        return 1;
    }

    /*
     * Initially target can be anywhere.
     */
    for (i = 1; i <= n; i++)
        possible[i] = 1;

    /*
     * Generate shooting sequence.
     */
    generateShots(n, shots, &shotCount);

    printf("\nShooting sequence:\n");

    for (i = 0; i < shotCount; i++)
    {
        printf("%d ", shots[i]);
    }

    printf("\n\nSimulation:\n");

    for (i = 0; i < shotCount; i++)
    {
        /*
         * Shoot at shots[i].
         */
        possible[shots[i]] = 0;

        printf("Shot %d at spot %d\n",
               i + 1, shots[i]);

        /*
         * If this is not the final shot,
         * target moves to an adjacent position.
         */
        if (i != shotCount - 1)
            moveTarget(n);

        /*
         * Count remaining possible positions.
         */
        remaining = 0;

        for (j = 1; j <= n; j++)
        {
            if (possible[j])
                remaining++;
        }

        printf("Possible positions remaining: %d\n",
               remaining);

        if (remaining == 0)
        {
            printf("\nTarget is guaranteed to be hit.\n");
            break;
        }
    }

    if (remaining == 0)
        printf("Algorithm successfully guarantees a hit.\n");
    else
        printf("Target may still survive.\n");

    return 0;
}