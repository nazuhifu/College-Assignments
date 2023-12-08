#include <stdio.h>
#include <stdlib.h>

// Define symbolic constant
#define MAX_SIZE 100

typedef struct {
    char nama[MAX_SIZE];
    int umur;
} Person;

// Cek operating system
void checkOS() {
    #ifdef _WIN32
        printf("OS: Windows\n");
    #elif __unix__
        printf("OS: Unix\n");
    #elif __APPLE__
        printf("OS: Apple\n");
    #else
        printf("OS: Unknown\n");
    #endif
}

// Fungsi untuk concatenate dan stringify
#define stringify(x) #x
#define concat(a, b) a##b

int main() {
    Person person;
    printf("Input nama: ");
    fgets(person.nama, MAX_SIZE, stdin);
    printf("Input umur: ");
    scanf("%d", &person.umur);

    // Cek operating system
    checkOS();

    int value1 = 10;
    int value2 = 20;
    int result = concat(value, 1) + concat(value, 2);
    printf("Nilai dari result: %d\n", result);
    printf("Stringify dari result: %s\n", stringify(result));

    return 0;
}
