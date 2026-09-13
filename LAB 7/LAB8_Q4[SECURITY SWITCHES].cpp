/*
 * Q4 - Security Switches
 *
 * There are n switches initially ON.
 *
 * Rules:
 * 1. The rightmost switch can be turned ON/OFF at any time.
 * 2. Any other switch can be toggled only when:
 *       - The switch immediately to its right is ON.
 *       - All switches further to its right are OFF.
 * 3. Only one switch can be toggled at a time.
 *
 * Goal:
 * Turn all switches OFF using minimum number of moves.
 *
 * Algorithm:
 * Recursive solution.
 *
 * Time Complexity: O(2^n)
 * Space Complexity: O(n)
 */

#include <stdio.h>

#define MAX 20

int switches[MAX];
long long moves = 0;

/*
 * Display current state of switches
 */
void display(int n)
{
    int i;

    printf("Switches: ");

    for (i = 0; i < n; i++)
    {
        printf("%d ", switches[i]);
    }

    printf("\n");
}

/*
 * Toggle a switch
 */
void toggle(int position, int n)
{
    switches[position] = 1 - switches[position];
    moves++;

    printf("Move %lld: Toggle switch %d\n",
           moves, position + 1);

    display(n);
}

/*
 * Recursive algorithm
 *
 * To turn n switches OFF:
 *
 * 1. Turn OFF the first n-1 switches.
 * 2. Toggle switch n.
 * 3. Turn OFF the first n-1 switches again.
 *
 * However, because of the special rule, the
 * recursive order is implemented from right to left.
 */
void solve(int n)
{
    if (n == 0)
        return;

    if (n == 1)
    {
        toggle(0, n);
        return;
    }

    /*
     * First solve for the switches to the right.
     */
    solve(n - 1);

    /*
     * Toggle the current switch.
     */
    toggle(n - 1, n);

    /*
     * Solve the remaining switches again.
     */
    solve(n - 1);
}

int main()
{
    int n;
    int i;

    printf("SECURITY SWITCHES\n");
    printf("-----------------\n");

    printf("Enter number of switches: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of switches!\n");
        return 1;
    }

    /*
     * Initially all switches are ON.
     */
    for (i = 0; i < n; i++)
    {
        switches[i] = 1;
    }

    printf("\nInitial state:\n");
    display(n);

    /*
     * Solve the problem.
     */
    solve(n);

    printf("\nFinal state:\n");
    display(n);

    printf("\nMinimum number of moves = %lld\n", moves);

    return 0;
}