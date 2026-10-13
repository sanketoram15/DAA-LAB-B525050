#include <stdio.h>

int main() {

    int n;

    printf("Enter number of children: ");
    scanf("%d", &n);

    int rating[n];
    int candy[n];

    printf("Enter ratings:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &rating[i]);
        candy[i] = 1;
    }

    /*
       Left to Right

       If current rating is greater than
       previous rating, current child gets
       one more candy.
    */
    for (int i = 1; i < n; i++) {

        if (rating[i] > rating[i - 1]) {
            candy[i] = candy[i - 1] + 1;
        }
    }

    /*
       Right to Left

       If current rating is greater than
       next rating, current child should have
       more candies than next child.
    */
    for (int i = n - 2; i >= 0; i--) {

        if (rating[i] > rating[i + 1]) {

            if (candy[i] < candy[i + 1] + 1)
                candy[i] = candy[i + 1] + 1;
        }
    }

    int total = 0;

    printf("\nCandy distribution:\n");

    for (int i = 0; i < n; i++) {

        printf("Child %d -> Rating = %d, Candy = %d\n",
               i + 1,
               rating[i],
               candy[i]);

        total += candy[i];
    }

    printf("\nMinimum candies required = %d\n",
           total);

    return 0;
}