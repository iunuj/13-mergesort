#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int comparisonCount = 0;
int moveCount = 0;

void merge(int array[], int left, int mid, int right, int step, int rounds, int isFirst) {
    int i = left, j = mid + 1, k = 0;
    int size = right - left + 1;

    int* temp = (int*)malloc(size * sizeof(int));
    if (temp == NULL) {
        printf("Memory allocation failed! Exiting...\n");
        exit(1);
    }

    while (i <= mid && j <= right) {
        comparisonCount++;
        if (array[i] <= array[j]) {
            temp[k++] = array[i++];
        }
        else {
            temp[k++] = array[j++];
        }
        moveCount++;
    }

    while (i <= mid) {
        temp[k++] = array[i++];
        moveCount++;
    }

    while (j <= right) {
        temp[k++] = array[j++];
        moveCount++;
    }

    for (i = left, k = 0; i <= right; i++, k++) {
        array[i] = temp[k];
        moveCount++;
    }

    free(temp);

    if (rounds % 10 == 0 && isFirst == 0) {
        for (int i = 0; i < 10; i++) {
            printf("%3d ", array[i]);
        }
        printf("| ");
        for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) {
            printf("%3d ", array[i]);
        }
        printf("\n\n");
    }
}

void iterativeMergeSort(int array[], int rounds, int isFirst) {
    int step = 0;
    for (int size = 1; size < SIZE; size *= 2) {
        for (int left = 0; left < SIZE - 1; left += 2 * size) {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < SIZE - 1) ? left + 2 * size - 1 : SIZE - 1;

            if (mid >= SIZE) mid = SIZE - 1;
            if (right >= SIZE) right = SIZE - 1;

            merge(array, left, mid, right, ++step, rounds, isFirst);
        }
    }
}

void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%3d ", array[i]);
    }
    printf("\n");
}

int main() {
    int array[SIZE];
    int totalComparisons = 0;
    int totalMoves = 0;

    srand(time(NULL));

    for (int round = 0; round < 20; round++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (round == 0) {
            printf("Merge Sort Run\n");
            printArray(array, SIZE);
        }

        iterativeMergeSort(array, round, round == 0 ? 0 : 1);

        if (round == 0) {
            printf("\nResult\n");
            printArray(array, SIZE);
        }

        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}
