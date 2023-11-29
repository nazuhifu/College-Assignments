#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Anime {
    char judul[20];
    char studio[20];
    int tahun;

    struct Anime *next;
};

// Fungsi untuk menambahkan anime di depan linked list
void tambahAnime (struct Anime **head_ref, const char *judul, const char *studio, int tahun) {

    // Alokasi memori untuk node baru
    struct Anime *new_node = (struct Anime*)malloc(sizeof(struct Anime));

    // Memasukkan data ke dalam node baru
    strcpy(new_node->judul, judul);
    strcpy(new_node->studio, studio);
    new_node->tahun = tahun;

    // Menjadikan node baru sebagai head
    new_node->next = *head_ref;
    *head_ref = new_node;
}

// Fungsi untuk menampilkan isi linked list
void printList(struct Anime *node) {
    while(node != NULL) {
        printf("%s | %s | %d\n-> ", node->judul, node->studio, node->tahun);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    // Inisialisasi linked list kosong
    struct Anime *head = NULL;

    // Menambahkan anime di depan linked list
    tambahAnime(&head, "Kimi no Na wa", "Comix Wave", 2016);
    tambahAnime(&head, "One Piece", "Toei Animation", 1998);
    tambahAnime(&head, "Naruto Shippuden", "Pierrot", 2007);

    // Menampilkan isi linked list
    printf("Linked list: \n");
    printList(head);

    return 0;
}
