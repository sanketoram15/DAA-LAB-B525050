#include <stdio.h>
#include <math.h>

typedef struct {
    int id;
    double value;
    double weight;
    double lambda;
    double remaining;
} Item;

int main() {
    int n;
    double capacity;

    printf("Enter number of items: ");
    scanf("%d", &n);

    Item item[n];

    for (int i = 0; i < n; i++) {
        printf("\nItem %d\n", i + 1);

        item[i].id = i + 1;

        printf("Enter value: ");
        scanf("%lf", &item[i].value);

        printf("Enter weight: ");
        scanf("%lf", &item[i].weight);

        printf("Enter deterioration rate: ");
        scanf("%lf", &item[i].lambda);

        item[i].remaining = item[i].weight;
    }

    printf("\nEnter knapsack capacity: ");
    scanf("%lf", &capacity);

    double totalValue = 0;
    double time = 0;

    printf("\nSelected items:\n");

    while (capacity > 0) {
        int best = -1;
        double bestDensity = -1;

        /* Find item having maximum current value density */
        for (int i = 0; i < n; i++) {
            if (item[i].remaining > 0) {

                double effectiveValue =
                    item[i].value * exp(-item[i].lambda * time);

                double density =
                    effectiveValue / item[i].weight;

                if (density > bestDensity) {
                    bestDensity = density;
                    best = i;
                }
            }
        }

        if (best == -1)
            break;

        double take;

        if (item[best].remaining <= capacity)
            take = item[best].remaining;
        else
            take = capacity;

        double effectiveValue =
            item[best].value *
            exp(-item[best].lambda * time);

        double fraction = take / item[best].weight;

        double gainedValue = effectiveValue * fraction;

        totalValue += gainedValue;

        printf("Time %.0lf: Item %d -> %.2lf weight, value gained = %.2lf\n",
               time,
               item[best].id,
               take,
               gainedValue);

        item[best].remaining -= take;
        capacity -= take;

        /*
           Move to next time slot after completely consuming
           the selected item.
        */
        if (item[best].remaining <= 0.000001)
            time++;
    }

    printf("\nMaximum total value = %.2lf\n", totalValue);

    return 0;
}