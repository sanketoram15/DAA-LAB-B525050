/*
 * Invert the Coin Triangle
 *
 * Given a triangle of 10 coins:
 *
 *             O
 *           O   O
 *         O   O   O
 *       O   O   O   O
 *
 * Move only 3 coins to invert the triangle.
 *
 * Minimum moves = 3
 */

#include <stdio.h>

#define N 10

// Structure to represent the position of a coin
typedef struct {
    int x;
    int y;
} Coin;

// Function to display the coins
void display(Coin coins[], int n)
{
    int i;

    printf("\nCoin positions:\n");

    for (i = 0; i < n; i++)
    {
        printf("Coin %d -> (%d, %d)\n",
               i + 1, coins[i].x, coins[i].y);
    }
}

// Function to move a coin
void moveCoin(Coin *coin, int newX, int newY)
{
    coin->x = newX;
    coin->y = newY;
}

int main()
{
    /*
     * Initial triangle:
     *
     *              (0,3)
     *
     *        (-1,2)       (1,2)
     *
     *    (-2,1)   (0,1)   (2,1)
     *
     * (-3,0) (-1,0) (1,0) (3,0)
     */

    Coin coins[N] = {
        {0, 3},          // Top
        {-1, 2}, {1, 2},
        {-2, 1}, {0, 1}, {2, 1},
        {-3, 0}, {-1, 0}, {1, 0}, {3, 0}
    };

    int moves = 0;

    printf("INITIAL TRIANGLE\n");
    display(coins, N);

    /*
     * MOVE 1:
     * Move the top coin to the bottom.
     *
     *        O
     *        |
     *        |
     *        V
     *
     * New position = (0,-1)
     */
    moveCoin(&coins[0], 0, -1);
    moves++;

    /*
     * MOVE 2:
     * Move bottom-left corner to upper-left.
     *
     * (-3,0) -> (-3,2)
     */
    moveCoin(&coins[6], -3, 2);
    moves++;

    /*
     * MOVE 3:
     * Move bottom-right corner to upper-right.
     *
     * (3,0) -> (3,2)
     */
    moveCoin(&coins[9], 3, 2);
    moves++;

    printf("\nAFTER INVERSION\n");
    display(coins, N);

    printf("\nMinimum number of moves = %d\n", moves);

    return 0;
}