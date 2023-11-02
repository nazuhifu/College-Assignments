#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define jmlBuku 3

// Mendefinisikan struktur untuk buku
struct Book {
    char judul[30];    // Judul buku
    char penulis[30];  // Nama penulis buku
    int afkhTersedia;  // Status ketersediaan buku (1 untuk tersedia, 0 untuk tidak tersedia)
};

// Fungsi untuk melakukan peminjaman buku
void pinjamBuku(struct Book* library, const char* judul);
// Fungsi untuk melakukan pengembalian buku
void balikinBuku(struct Book* library, const char* judul);

int main() {
    printf("==== SELAMAT DATANG DI PERPUSTAKAAN WADIDAW ====\n");
    printf("Berikut adalah daftar buku di perpustakaan kami:\n");
    printf("@. 10 Dosa Besar Soeharto\n");
    printf("@. Bumi Manusia\n");
    printf("@. Laskar Pelangi\n\n");

    // Alokasi memori dinamis untuk array buku
    struct Book* library = (struct Book*)malloc(jmlBuku * sizeof(struct Book));

    // Menginisialisasi informasi buku
    strcpy(library[0].judul, "10 Dosa Besar Soeharto");
    strcpy(library[0].penulis, "Drs. Wimanjaya K.");
    library[0].afkhTersedia = 1;

    strcpy(library[1].judul, "Bumi Manusia");
    strcpy(library[1].penulis, "Pramoedya Ananta Toer");
    library[1].afkhTersedia = 1;

    strcpy(library[2].judul, "Laskar Pelangi");
    strcpy(library[2].penulis, "Andrea Hirata");
    library[2].afkhTersedia = 1;

    int choice;
    char judulBuku[30];

    while (1) {
        printf("1. Peminjaman buku\n");
        printf("2. Pengembalian buku\n");
        printf("3. Keluar\n");
        printf("Pilihan (1-3): ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Masukkan judul buku yang ingin dipinjam: ");
            scanf(" %[^\n]", judulBuku);
            pinjamBuku(library, judulBuku);
        } else if (choice == 2) {
            printf("Masukkan judul buku yang ingin dikembalikan: ");
            scanf(" %[^\n]", judulBuku);
            balikinBuku(library, judulBuku);
        } else if (choice == 3) {
            printf("\nTerima kasih sudah berkunjung :D\n");
            break;
        } else {
            printf("Pilihan tidak valid. Silakan pilih menu 1 sampai 3.\n");
        }
    }

    // Membebaskan memori yang dialokasikan
    free(library);

    return 0;
}

// Fungsi untuk melakukan peminjaman buku
void pinjamBuku(struct Book* library, const char* judul) {
    for (int i = 0; i < jmlBuku; i++) {
        if (strcmp(library[i].judul, judul) == 0) {
            if (library[i].afkhTersedia) {
                printf("\n====>>>> Kamu meminjam '%s' karya %s\n\n", library[i].judul, library[i].penulis);
                library[i].afkhTersedia = 0;
                return;
            } else {
                printf("\n====>>>> Maaf, buku '%s' sudah dipinjam.\n\n", library[i].judul);
                return;
            }
        }
    }
    printf("\n====>>>> Buku '%s' tidak ditemukan.\n\n", judul);
}

// Fungsi untuk melakukan pengembalian buku
void balikinBuku(struct Book* library, const char* judul) {
    for (int i = 0; i < jmlBuku; i++) {
        if (strcmp(library[i].judul, judul) == 0) {
            if (!library[i].afkhTersedia) {
                printf("\n====>>>> Kamu mengembalikan '%s' karya %s\n\n", library[i].judul, library[i].penulis);
                library[i].afkhTersedia = 1;
                return;
            } else {
                printf("\n====>>>> Maaf, buku '%s' belum dipinjam.\n\n", library[i].judul);
                return;
            }
        }
    }
    printf("\n====>>>> Buku '%s' tidak ditemukan.\n\n", judul);
}
