#include <stdio.h>

int jumlah();
int kurang();
int kali();
int bagi();
int faktorial(int n);
int fibo(int n);
int angka, num1, num2;

int main() {
    int mode;
    char more;
    
    printf("\n===== SIMPLE CALCULATOR =====\n");
    do
    {
        do
        {
            printf("\nPilih kebutuhanmu: \n");
            printf("1. Penjumlahan\n");
            printf("2. Pengurangan\n");
            printf("3. Perkalian\n");
            printf("4. Pembagian\n");
            printf("5. Faktorial\n");
            printf("6. Fibonacci\n");

            printf("Pilihanmu (1-6): ");
            scanf("%d", &mode);

        } while (mode < 1 || mode > 6);

        switch (mode) {
            case 1:
                jumlah();
                break;
            case 2:
                kurang();
                break;
            case 3:
                kali();
                break;
            case 4:
                bagi();
                break;
            case 5:
                printf("Input angka untuk faktorial: ");
                scanf("%d", &angka);
                printf("\nHasil dari %d! = %d\n", angka, faktorial(angka));
                break;
            case 6:
                printf("Input untuk fibonacci ke-n: ");
                scanf("%d", &angka);
                printf("\nFibonacci ke-%d = %d\n", angka, fibo(angka));
                break;
            default:
                break;
        }

        printf("\nMau menghitung lagi? (y/n): ");
        scanf(" %c", &more);
        
    } while(more == 'y');


    return 0;
}

int jumlah()
{
    printf("Input angka pertama: ");
    scanf("%d", &num1);
    printf("Input angka kedua: ");
    scanf("%d", &num2);

    int result = num1 + num2;
    printf("\nHasil dari %d + %d = %d\n", num1, num2, result);
    return result;
}

int kurang()
{
    printf("Input angka pertama: ");
    scanf("%d", &num1);
    printf("Input angka kedua: ");
    scanf("%d", &num2);

    int result = num1 - num2;
    printf("\nHasil dari %d - %d = %d\n", num1, num2, result);
    return result;
}

int kali()
{
    printf("Input angka pertama: ");
    scanf("%d", &num1);
    printf("Input angka kedua: ");
    scanf("%d", &num2);

    int result = num1 * num2;
    printf("\nHasil dari %d * %d = %d\n", num1, num2, result);
    return result;
}

int bagi()
{
    printf("Input angka pertama: ");
    scanf("%d", &num1);
    printf("Input angka kedua: ");
    scanf("%d", &num2);

    if (num2 == 0) {
        printf("\nPembagian dengan nol tidak terdefinisi.\n");
        return 0;
    }

    double result = (double)num1 / num2;
    printf("\nHasil dari %d / %d = %.2lf\n", num1, num2, result);
    return result;
}

int faktorial(int n)
{
    if(n <= 1)
        return 1;
    else
    {
        return n * faktorial(n-1);
    }
}

int fibo(int n)
{
    if(n <= 1)
        return n;
    
    return fibo(n-1) + fibo(n-2);
}
