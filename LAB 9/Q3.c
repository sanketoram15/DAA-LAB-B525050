#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int distance;
    int fuel;
} Station;

/* Max Heap */
typedef struct {
    int data[1000];
    int size;
} MaxHeap;

void insert(MaxHeap *heap, int value) {

    int i = heap->size++;
    heap->data[i] = value;

    while (i > 0) {

        int parent = (i - 1) / 2;

        if (heap->data[parent] >= heap->data[i])
            break;

        int temp = heap->data[parent];
        heap->data[parent] = heap->data[i];
        heap->data[i] = temp;

        i = parent;
    }
}

int extractMax(MaxHeap *heap) {

    int maxValue = heap->data[0];

    heap->data[0] = heap->data[--heap->size];

    int i = 0;

    while (1) {

        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < heap->size &&
            heap->data[left] > heap->data[largest])
            largest = left;

        if (right < heap->size &&
            heap->data[right] > heap->data[largest])
            largest = right;

        if (largest == i)
            break;

        int temp = heap->data[i];
        heap->data[i] = heap->data[largest];
        heap->data[largest] = temp;

        i = largest;
    }

    return maxValue;
}

/* Sort stations according to distance */
int compareStations(const void *a, const void *b) {

    Station *x = (Station*)a;
    Station *y = (Station*)b;

    return x->distance - y->distance;
}

int main() {

    int n;
    int D;
    int initialFuel;

    printf("Enter target distance: ");
    scanf("%d", &D);

    printf("Enter initial fuel: ");
    scanf("%d", &initialFuel);

    printf("Enter number of stations: ");
    scanf("%d", &n);

    Station station[n];

    for (int i = 0; i < n; i++) {

        printf("Enter distance and fuel of station %d: ",
               i + 1);

        scanf("%d %d",
              &station[i].distance,
              &station[i].fuel);
    }

    qsort(station,
          n,
          sizeof(Station),
          compareStations);

    MaxHeap heap;
    heap.size = 0;

    int currentFuel = initialFuel;
    int previousDistance = 0;
    int refuels = 0;

    for (int i = 0; i <= n; i++) {

        int currentDistance;

        if (i == n)
            currentDistance = D;
        else
            currentDistance = station[i].distance;

        int distanceNeeded =
            currentDistance - previousDistance;

        /*
           If we cannot reach this point,
           refuel using the largest fuel from
           previously passed stations.
        */
        while (currentFuel < distanceNeeded) {

            if (heap.size == 0) {
                printf("\nTarget cannot be reached.\n");
                return 0;
            }

            int maxFuel = extractMax(&heap);

            currentFuel += maxFuel;
            refuels++;

            printf("Refueled %d units\n", maxFuel);
        }

        currentFuel -= distanceNeeded;

        previousDistance = currentDistance;

        if (i < n)
            insert(&heap, station[i].fuel);
    }

    printf("\nMinimum number of refuels = %d\n",
           refuels);

    return 0;
}