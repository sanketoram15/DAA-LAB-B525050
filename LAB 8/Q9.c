#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

/* Structure to store information about a Collatz trajectory */
typedef struct {
    uint64_t *values;
    size_t size;
    size_t capacity;
    uint64_t maximum;
    int overflow;
} Trajectory;


/* Initialize the dynamic array */
void initTrajectory(Trajectory *t)
{
    t->capacity = 10;
    t->size = 0;
    t->maximum = 0;
    t->overflow = 0;

    t->values = (uint64_t *)malloc(t->capacity * sizeof(uint64_t));

    if (t->values == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
}


/* Add a value to the dynamic array */
void addValue(Trajectory *t, uint64_t value)
{
    if (t->size == t->capacity) {

        t->capacity *= 2;

        uint64_t *temp =
            (uint64_t *)realloc(t->values,
                                t->capacity * sizeof(uint64_t));

        if (temp == NULL) {
            printf("Memory reallocation failed.\n");
            free(t->values);
            exit(1);
        }

        t->values = temp;
    }

    t->values[t->size] = value;
    t->size++;

    if (value > t->maximum)
        t->maximum = value;
}


/* Free dynamically allocated memory */
void freeTrajectory(Trajectory *t)
{
    free(t->values);
    t->values = NULL;
    t->size = 0;
    t->capacity = 0;
}


/* Generate Collatz trajectory */
void generateCollatz(Trajectory *t, uint64_t n)
{
    addValue(t, n);

    while (n != 1) {

        if (n % 2 == 0) {

            /* Even number */
            n = n / 2;
        }
        else {

            /*
             * Before calculating 3*n + 1,
             * check whether overflow will occur.
             */
            if (n > (UINT64_MAX - 1) / 3) {

                printf("\nOverflow detected while calculating 3n + 1.\n");
                t->overflow = 1;
                return;
            }

            n = 3 * n + 1;
        }

        addValue(t, n);
    }
}


/* Print trajectory */
void printTrajectory(const Trajectory *t)
{
    size_t i;

    for (i = 0; i < t->size; i++) {

        printf("%llu", (unsigned long long)t->values[i]);

        if (i != t->size - 1)
            printf(" -> ");
    }

    printf("\n");
}


/* Analyse one starting value */
void analyseNumber(uint64_t n)
{
    Trajectory t;

    initTrajectory(&t);

    generateCollatz(&t, n);

    printf("\nStarting value: %llu\n",
           (unsigned long long)n);

    printf("Trajectory:\n");
    printTrajectory(&t);

    if (t.overflow) {
        printf("Status: Overflow occurred.\n");
    }
    else {
        printf("Reached 1: YES\n");
        printf("Number of steps: %zu\n", t.size - 1);
        printf("Maximum value reached: %llu\n",
               (unsigned long long)t.maximum);
    }

    freeTrajectory(&t);
}


/* Analyse all numbers in [a,b] */
void analyseInterval(uint64_t a, uint64_t b)
{
    uint64_t n;

    printf("\n========================================\n");
    printf("Analysis of interval [%llu, %llu]\n",
           (unsigned long long)a,
           (unsigned long long)b);
    printf("========================================\n");

    for (n = a; n <= b; n++) {

        Trajectory t;

        initTrajectory(&t);

        generateCollatz(&t, n);

        printf("\nStarting value = %llu\n",
               (unsigned long long)n);

        if (t.overflow) {

            printf("Status: OVERFLOW\n");
        }
        else {

            printf("Steps = %zu\n", t.size - 1);

            printf("Maximum = %llu\n",
                   (unsigned long long)t.maximum);
        }

        freeTrajectory(&t);

        /* Prevent unsigned integer wraparound when b == UINT64_MAX */
        if (n == UINT64_MAX)
            break;
    }
}


/* Main function */
int main()
{
    uint64_t n;
    uint64_t a, b;

    printf("===== COLLATZ CONJECTURE ANALYSER =====\n");

    /* Single starting value */
    printf("\nEnter starting value n: ");
    scanf("%llu", (unsigned long long *)&n);

    if (n < 1) {
        printf("Starting value must be >= 1.\n");
        return 1;
    }

    analyseNumber(n);


    /* Interval */
    printf("\nEnter interval [a,b]:\n");

    printf("Enter a: ");
    scanf("%llu", (unsigned long long *)&a);

    printf("Enter b: ");
    scanf("%llu", (unsigned long long *)&b);

    if (a < 1 || b < a) {
        printf("Invalid interval.\n");
        return 1;
    }

    analyseInterval(a, b);

    return 0;
}