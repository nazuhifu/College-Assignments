#include <stdio.h>

#define ROWS 2
#define COLS 3

int input;

void printArray(int array[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}

int getMenuChoice() {
    int choice;
    printf("Program Array:\n");
    printf("1. Mengubah nilai array\n");
    printf("2. Mengoperasikan nilai array\n");
    printf("Input kebutuhan anda (1-2): ");
    scanf("%d", &choice);
    return choice;
}

void changeValue(int array1[ROWS][COLS], int array2[ROWS][COLS]) {
    printf("\nPilih array yang ingin diubah:\n");
    printf("1. Array 1\n");
    printf("2. Array 2\n");
    printf("Pilih array (1-2): ");
    scanf("%d", &input);

    if (input == 1) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                printf("Array ke-[%d][%d]: ", i, j);
                scanf("%d", &array1[i][j]);
            }
        }
        printf("Hasil array: ");
        printArray(array1);
    } else {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                printf("Array ke-[%d][%d]: ", i, j);
                scanf("%d", &array2[i][j]);
            }
        }
        printf("Hasil array: ");
        printArray(array2);
    }
}

void addArray(int array1[ROWS][COLS], int array2[ROWS][COLS], int result[ROWS][COLS]) {
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            result[i][j] = array1[i][j] + array2[i][j];
        }
    }

    printf("Hasil penjumlahan array:\n");
    printArray(result);
}

void subtractArray(int array1[ROWS][COLS], int array2[ROWS][COLS], int result[ROWS][COLS]) {
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            result[i][j] = array1[i][j] - array2[i][j];
        }
    }

    printf("Hasil pengurangan array:\n");
    printArray(result);
}

void multiplyArray(int array1[ROWS][COLS], int array2[ROWS][COLS], int result[ROWS][COLS]) {
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            result[i][j] = array1[i][j] * array2[i][j];
        }
    }

    printf("Hasil perkalian array:\n");
    printArray(result);
}

void divideArray(int array1[ROWS][COLS], int array2[ROWS][COLS], int result[ROWS][COLS]) {
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (array2[i][j] == 0) {
                printf("Tidak dapat membagi oleh nol.\n");
                return;
            }
            result[i][j] = array1[i][j] / array2[i][j];
        }
    }

    printf("Hasil pembagian array:\n");
    printArray(result);
}

int main() {
    int arr1[ROWS][COLS] = {{1, 2, 3}, {4, 5, 6}};
    int arr2[ROWS][COLS] = {{7, 8, 9}, {0, 1, 2}};
    int result[ROWS][COLS];

    printf("Array pertama:\n");
    printArray(arr1);
    printf("\n");

    printf("Array kedua:\n");
    printArray(arr2);
    printf("\n");

    do {
        input = getMenuChoice();
    } while (input < 1 || input > 2);

    if (input == 1) {
        changeValue(arr1, arr2);
    } else if (input == 2) {
        printf("Operasi array:\n");
        printf("1. Penjumlahan\n");
        printf("2. Pengurangan\n");
        printf("3. Perkalian\n");
        printf("4. Pembagian\n");
        printf("Input kebutuhan: ");
        scanf("%d", &input);
        switch (input) {
            case 1:
                addArray(arr1, arr2, result);
                break;
            case 2:
                subtractArray(arr1, arr2, result);
                break;
            case 3:
                multiplyArray(arr1, arr2, result);
                break;
            case 4:
                divideArray(arr1, arr2, result);
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    }

    return 0;
}
