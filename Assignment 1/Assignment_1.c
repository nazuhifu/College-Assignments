/*
Nama  : Mohammad Nazhiif Al-Ghoniy
NIM   : L0123084
Kelas : C
*/

#include <stdio.h>
#include <string.h>
char huruf[5]; // Untuk menyimpan hasil konversi huruf

// Deklarasi fungsi untuk mengkonversi nilai
// ke angka atau huruf
float konversi_angka(int nilai){
    if(nilai < 55) return 0.00;
    else if(nilai <= 59) return 1.00;
    else if(nilai <= 64) return 2.00;
    else if(nilai <= 69) return 2.70;
    else if(nilai <= 74) return 3.00;
    else if(nilai <= 79) return 3.30;
    else if(nilai <= 84) return 3.70;
    else return 4.00;
}

// Huruf akan dimasukkan ke dalam array of char huruf
void konversi_huruf(int nilai){
    if(nilai < 55) strcpy(huruf, "E");
    else if(nilai <= 59) strcpy(huruf, "D");
    else if(nilai <= 64) strcpy(huruf, "C");
    else if(nilai <= 69) strcpy(huruf, "C+");
    else if(nilai <= 74) strcpy(huruf, "B");
    else if(nilai <= 79) strcpy(huruf, "B+");
    else if(nilai <= 84) strcpy(huruf, "A-");
    else strcpy(huruf, "A");
}

int main(){
    printf("\n==== PROGRAM UNTUK KONVERSI NILAI MAHASISWA ====\n\n");

    // Input jumlah mahasiswa
    int jml_mhs;
    printf("Input jumlah mahasiswa: ");
    scanf("%d", &jml_mhs);

    int nilai[jml_mhs+1]; // Array nilai yang berisi nilai mahasiswa sebanyak jml_mhs
    int cnt = 1;          // cnt sebagai counter untuk while

    // Input nilai mahasiswa
    while(cnt <= jml_mhs){ // Jika nilai cnt belum sama dengan jml_mhs, terus input nilai mahasiswa
        printf("Nilai mahasiswa ke-%d: ", cnt);
        scanf("%d", &nilai[cnt]);
        cnt++;
    }

    // Cetak header tabel
    printf("\n\n| No |   Nilai  |  Angka  |  Huruf  |\n");
    printf("|----|----------|---------|---------|\n");

    // Cetak nilai konversi dalam tabel
    for(int i = 1; i <= jml_mhs; i++){
        float angka = konversi_angka(nilai[i]);  // Pemanggilan fungsi
        konversi_huruf(nilai[i]);      

        // Output
        printf("| %2d | %8d | %7.2f | %7s |\n", i, nilai[i], angka, huruf);
    }

    return 0;
}
