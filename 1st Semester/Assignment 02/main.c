/*
Nama  : Mohammad Nazhiif Al-Ghoniy
NIM   : L0123084
Kelas : C
*/

#include<stdio.h>
#define sizePapan 3
#define PLAYER_1 1
#define PLAYER_2 2

void cetakPapan(char papan[sizePapan][sizePapan]){
    for (int i = 0; i < sizePapan; i++){
        for (int j = 0; j < sizePapan; j++){
            printf(" %c ", papan[i][j]);
            if (j != sizePapan - 1)
                printf("|");
            
        }
        printf("\n");
        if (i != sizePapan - 1)
            printf("---+---+---\n");
    }
}

int cetakHasil(char papan[sizePapan][sizePapan], char simbol){
    // Cek apakah ada 3 simbol yang sama dalam satu baris
    for (int i = 0; i < sizePapan; i++){
        int menang = 1;
        for (int j = 0; j < sizePapan; j++){
            // Jika ada posisi dimana isi array papan tidak sama dengan simbol
            // maka pasti belum menang
            if (papan[i][j] != simbol){
                menang = 0;
                break;
            }
        }
        // Jika dalam satu baris tersebut simbolnya sama
        // kembalikan nilai 1
        if (menang) return 1;
    }

    // Cek apakah ada 3 simbol yang sama dalam satu kolom
    for (int j = 0; j < sizePapan; j++){
        int menang = 1;
        for (int i = 0; i < sizePapan; i++){
            if (papan[i][j] != simbol){
                menang = 0;
                break;
            }
        }
        if (menang) return 1;
    }

    // Cek apakah ada 3 simbol yang sama dalam satu diagonal
    // Cek diagonal dari kiri
    int menang = 1;
    for (int i = 0; i < sizePapan; i++){
        if (papan[i][i] != simbol){
            menang = 0;
            break;
        }
    }
    if (menang)
        return 1;

    // Cek diagonal dari kanan
    menang = 1;
    for (int i = 0; i < sizePapan; i++){
        if (papan[i][sizePapan - 1 - i] != simbol){
            menang = 0;
            break;
        }
    }
    if (menang)
        return 1;

    return 0;
}

int main()
{
    printf("Selamat datang di game awikwok!\n");
    printf("Permainan ini dimainkan oleh 2 pemain.\n\n");
    printf("Player 1 simbolnya 'X' dan Player 2 simbolnya 'O'.\n");
    printf("Player akan menang apabila:\n");
    printf("1. Ada simbol yang sama dalam satu baris\n");
    printf("2. Ada simbol yang sama dalam satu kolom\n");
    printf("3. Ada simbol yang sama dalam satu diagonal\n");
    int mainLagi;

    do{
        printf("\nBentuk papan beserta nomor posisinya:\n");
        printf(" 1 | 2 | 3 \n");
        printf("---+---+---\n");
        printf(" 4 | 5 | 6 \n");
        printf("---+---+---\n");
        printf(" 7 | 8 | 9 \n");
        // Deklarasi ukuran papan
        // Isi array papan dengan spasi
        char papan[sizePapan][sizePapan];
        for (int i = 0; i < sizePapan; i++){
            for (int j = 0; j < sizePapan; j++){
                papan[i][j] = ' ';
            }
        }

        int player = PLAYER_1; // Mulai dari player pertama
        int batasMain = 0;
        while(1){
            printf("Giliran Player %d:\n", player);

            // Proses input posisi
            int baris, kolom, posisi;
            do{
                printf("Pilih posisi (1-9): ");
                scanf("%d", &posisi);
                baris = (posisi - 1) / sizePapan;
                kolom = (posisi - 1) % sizePapan;
            } while (posisi < 1 || posisi > sizePapan * sizePapan || papan[baris][kolom] != ' ');

            // Memberikan nilai ke array papan
            // sesuai input player
            if(player == PLAYER_1)
                papan[baris][kolom] = 'X';
            else
                papan[baris][kolom] = 'O';

            batasMain++;
            // Papan dicetak setelah pemain menginputkan posisi
            cetakPapan(papan);

            char simbol;
            switch(player){
                case PLAYER_1:
                    simbol = 'X';
                    break;
                case PLAYER_2:
                    simbol = 'O';
                    break;
                
                default:
                    break;
            }

            // Jika true berarti menang
            if(cetakHasil(papan, simbol)){
                printf("\nSELAMAT!\nPLAYER %d MENANG!\n", player);
                break;
            }

            if (batasMain == sizePapan * sizePapan)
            {
                printf("\nWADUH!\nSERI CUY\n");
                break;
            }

            // Ganti player
            switch(player){
                case PLAYER_1:
                    player = PLAYER_2;
                    break;
                case PLAYER_2:
                    player = PLAYER_1;
                    break;

                default:
                    break;
            }
        }
        printf("\nMau main lagi? (1 = Ya, 0 = Tidak): ");
        scanf("%d", &mainLagi);
    } while (mainLagi == 1);
    
    return 0;
}
