/*
 * Q6 - The Best Time to Be Alive
 *
 * Find the year in which the maximum number of
 * scientists were alive.
 *
 * If one person dies in the same year another
 * person is born, death is processed first.
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct
{
    int year;
    int type;       // -1 = death, +1 = birth
} Event;

/*
 * Comparator for sorting events.
 *
 * First sort by year.
 * If years are equal, death comes before birth.
 */
int compare(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    if (e1->year != e2->year)
        return e1->year - e2->year;

    return e1->type - e2->type;
}

int main()
{
    int n;
    int i;
    int birth, death;
    int eventCount = 0;

    int currentAlive = 0;
    int maxAlive = 0;
    int bestYear = 0;

    Event events[2 * MAX];

    printf("THE BEST TIME TO BE ALIVE\n");
    printf("-------------------------\n");

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid input!\n");
        return 1;
    }

    /*
     * Read birth and death years.
     */
    for (i = 0; i < n; i++)
    {
        printf("\nScientist %d\n", i + 1);

        printf("Birth year: ");
        scanf("%d", &birth);

        printf("Death year: ");
        scanf("%d", &death);

        /*
         * Birth event
         */
        events[eventCount].year = birth;
        events[eventCount].type = 1;
        eventCount++;

        /*
         * Death event
         */
        events[eventCount].year = death;
        events[eventCount].type = -1;
        eventCount++;
    }

    /*
     * Sort all events.
     *
     * Death is automatically placed before birth
     * when both occur in the same year.
     */
    qsort(events, eventCount,
          sizeof(Event), compare);

    /*
     * Process events.
     */
    for (i = 0; i < eventCount; i++)
    {
        currentAlive += events[i].type;

        /*
         * Update maximum.
         */
        if (currentAlive > maxAlive)
        {
            maxAlive = currentAlive;
            bestYear = events[i].year;
        }
    }

    printf("\n-------------------------\n");
    printf("Maximum number of scientists alive = %d\n",
           maxAlive);

    printf("Year with maximum scientists alive = %d\n",
           bestYear);

    return 0;
}