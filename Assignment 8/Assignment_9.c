#include <stdarg.h>
#include <stdio.h>

double cariMinimum(int count, ...) {
    va_list args;
    double min, current;

    va_start(args, count);
    min = va_arg(args, double);

    for (int i = 1; i < count; i++) {
        current = va_arg(args, double);
        if (current < min) {
            min = current;
        }
    }

    va_end(args);
    return min;
}

double cariMaksimum(int count, ...) {
    va_list args;
    double max, current;

    va_start(args, count);
    max = va_arg(args, double);

    for (int i = 1; i < count; i++) {
        current = va_arg(args, double);
        if (current > max) {
            max = current;
        }
    }

    va_end(args);
    return max;
}

int main() {
    double min, max;

    min = cariMinimum(5, 11.0, 2.0, 34.0, 95.0, 54.0);
    max = cariMaksimum(5, 11.0, 2.0, 34.0, 95.0, 54.0);

    printf("Nilai terkecilnya adalah: %.2f\n", min);
    printf("Nilai terbesarnya adalah: %.2f\n", max);

    return 0;
}
