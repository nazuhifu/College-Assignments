#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>

#define MAXSISI 10
#define MAXBOM 10

int SISI_PAPAN = 9;
int BOM = 10;

void banner (){
    printf("========        SELAMAT DATANG        ========\n");
    printf("======== DI PERMAINAN MINESWEEPER 9x9 ========\n");
    printf("========       SELAMAT BERMAIN        ========\n\n");

    return;
}

// fungsi untuk menentukan apakah posisi yang
// dipilih terdapat dalam papan
bool isValid (int baris, int kolom){
	return (baris >= 0) && (baris < SISI_PAPAN) &&
		(kolom >= 0) && (kolom < SISI_PAPAN);
}

// fungsi untuk menentukan apakah posisi yang
// dipilih adalah bom
bool isBom (int baris, int kolom, char realBoard[MAXSISI][MAXSISI]){
	if (realBoard[baris][kolom] == '*')
		return true;
	else
		return false;
}

// input posisi oleh player
void pilihPosisi (int *x, int *y){
	printf("Pilih posisi dipisahkan spasi (baris kolom) -> ");
	scanf("%d %d", x, y);
	return;
}

// mencetak keadaan papan ke layar player
void cetakPapan (char playerBoard[MAXSISI][MAXSISI]){

	printf ("  ");

	for (int i = 0; i < SISI_PAPAN; i++)
		printf ("%d ", i);

	printf ("\n");

	for (int i = 0; i < SISI_PAPAN; i++){
		printf ("%d ", i);

		for (int j = 0; j < SISI_PAPAN; j++)
			printf ("%c ", playerBoard[i][j]);

		printf ("\n");
	}
	return;
}

// hitung bom di 8 posisi sekeliling posisi yang dipilih
int hitungBom(int baris, int kolom, int bom[MAXBOM][2], char realBoard[MAXSISI][MAXSISI]){

	int jmlBom = 0;

	/*

			   N.W N N.E
			    \ | /
			W----POS----E
		            / | \
			  S.W S S.E

		Pos --> Posisi sekarang (baris, kolom)
		N --> North	  (baris-1, kolom)
		S --> South	  (baris+1, kolom)
		E --> East	  (baris, kolom+1)
		W --> West	  (baris, kolom-1)
		N.E--> North-East (baris-1, kolom+1)
		N.W--> North-West (baris-1, kolom-1)
		S.E--> South-East (baris+1, kolom+1)
		S.W--> South-West (baris+1, kolom-1)
	*/

	//----------- 1. North ------------

		if (isValid (baris-1, kolom) == true){
			if (isBom (baris-1, kolom, realBoard) == true)
			    jmlBom++;
		}

	//----------- 2. South ------------

		if (isValid (baris+1, kolom) == true){
			if (isBom (baris+1, kolom, realBoard) == true)
			    jmlBom++;
		}

	//----------- 3. East ------------

		if (isValid (baris, kolom+1) == true){
			if (isBom (baris, kolom+1, realBoard) == true)
			    jmlBom++;
		}

	//----------- 4. West ------------

		if (isValid (baris, kolom-1) == true){
			if (isBom (baris, kolom-1, realBoard) == true)
			    jmlBom++;
		}

	//----------- 5. North-East ------------

		if (isValid (baris-1, kolom+1) == true){
			if (isBom (baris-1, kolom+1, realBoard) == true)
			    jmlBom++;
		}

	//----------- 6. North-West ------------

		if (isValid (baris-1, kolom-1) == true){
			if (isBom (baris-1, kolom-1, realBoard) == true)
			    jmlBom++;
		}

	//----------- 7. South-East ------------

		if (isValid (baris+1, kolom+1) == true){
			if (isBom (baris+1, kolom+1, realBoard) == true)
			    jmlBom++;
		}

	//----------- 8. South-West ------------

		if (isValid (baris+1, kolom-1) == true){
			if (isBom (baris+1, kolom-1, realBoard) == true)
			    jmlBom++;
		}

	return jmlBom;
}

bool Minesweeper (char playerBoard[MAXSISI][MAXSISI], char realBoard[MAXSISI][MAXSISI], int bom[][2], int baris, int kolom, int *movesLeft){

	// base case ketika posisi sudah terisi bukan bom
    // kembalikan gameOver bernilai false
	if (playerBoard[baris][kolom] != '-')
		return false;

	// jika posisi yang dipilih adalah bom
	if (realBoard[baris][kolom] == '*'){
		playerBoard[baris][kolom]='*';

		for (int i = 0; i < BOM; i++)
			playerBoard[bom[i][0]][bom[i][1]]='*';

		cetakPapan (playerBoard);
		printf ("\nKAMU KALAH!\n\n");
		return true ;
	}

	else
	{
		// hitung banyak bom di sekitar posisi yang dipilih
		int count = hitungBom(baris, kolom, bom, realBoard);
		(*movesLeft)--;

		playerBoard[baris][kolom] = count + '0';

        // jika di sekitar posisi yang dipilih tidak ada bom
        // maka hitung bom di semua posisi sekitarnya
		if (!count){

	/*

			   N.W N N.E
			    \ | /
			W----POS----E
		            / | \
			  S.W S S.E

		Pos --> Posisi sekarang (baris, kolom)
		N --> North	  (baris-1, kolom)
		S --> South	  (baris+1, kolom)
		E --> East	  (baris, kolom+1)
		W --> West	  (baris, kolom-1)
		N.E--> North-East (baris-1, kolom+1)
		N.W--> North-West (baris-1, kolom-1)
		S.E--> South-East (baris+1, kolom+1)
		S.W--> South-West (baris+1, kolom-1)
	*/

			//----------- 1. North ------------

			if (isValid (baris-1, kolom) == true){
				if (isBom (baris-1, kolom, realBoard) == false)
				    Minesweeper(playerBoard, realBoard, bom, baris-1, kolom, movesLeft);
			}

			//----------- 2. South ------------

			if (isValid (baris+1, kolom) == true){
				if (isBom (baris+1, kolom, realBoard) == false)
					Minesweeper(playerBoard, realBoard, bom, baris+1, kolom, movesLeft);
			}

			//----------- 3. East ------------

			if (isValid (baris, kolom+1) == true){
				if (isBom (baris, kolom+1, realBoard) == false)
					Minesweeper(playerBoard, realBoard, bom, baris, kolom+1, movesLeft);
			}

			//----------- 4. West ------------

			if (isValid (baris, kolom-1) == true){
				if (isBom (baris, kolom-1, realBoard) == false)
					Minesweeper(playerBoard, realBoard, bom, baris, kolom-1, movesLeft);
			}

			//----------- 5. North-East ------------

			if (isValid (baris-1, kolom+1) == true){
				if (isBom (baris-1, kolom+1, realBoard) == false)
					Minesweeper(playerBoard, realBoard, bom, baris-1, kolom+1, movesLeft);
			}

			//----------- 6. North-West ------------

			if (isValid (baris-1, kolom-1) == true){
				if (isBom (baris-1, kolom-1, realBoard) == false)
					Minesweeper(playerBoard, realBoard, bom, baris-1, kolom-1, movesLeft);
			}

			//----------- 7. South-East ------------

			if (isValid (baris+1, kolom+1) == true){
				if (isBom (baris+1, kolom+1, realBoard) == false)
					Minesweeper(playerBoard, realBoard, bom, baris+1, kolom+1, movesLeft);
			}

			//----------- 8. South-West ------------

			if (isValid (baris+1, kolom-1) == true){
				if (isBom (baris+1, kolom-1, realBoard) == false)
					Minesweeper(playerBoard, realBoard, bom, baris+1, kolom-1, movesLeft);
			}
		}

		return false;
	}
}


void placeBom(int bom[MAXBOM][2], char realBoard[MAXSISI][MAXSISI]){

	bool adaBom[MAXSISI*MAXSISI];

    // set isi dari array adaBom dengan nilai false
	memset (adaBom, false, sizeof (adaBom));

	for (int i = 0; i < BOM; ){
		int random = rand() % (SISI_PAPAN*SISI_PAPAN);
		int x = random / SISI_PAPAN;
		int y = random % SISI_PAPAN;

		if (adaBom[random] == false){
			// indeks baris bom
			bom[i][0]= x;
			// indeks kolom bom
			bom[i][1] = y;

			// tempatkan bom pada posisi x,y
			realBoard[bom[i][0]][bom[i][1]] = '*';

            // sekarang sudah terisi bom
			adaBom[random] = true;
			i++;
		}
	}

	return;
}

void inisialisasi (char realBoard[][MAXSISI], char playerBoard[][MAXSISI]){
	// set seed untuk fungsi rand()
	srand(time (NULL));

	// mengisi semua array agar kosong
	for (int i = 0; i < SISI_PAPAN; i++){
		for (int j = 0; j < SISI_PAPAN; j++){
			playerBoard[i][j] = realBoard[i][j] = '-';
		}
	}

	return;
}

void replaceBom (int baris, int kolom, char realBoard[MAXSISI][MAXSISI]){
	for (int i = 0; i < SISI_PAPAN; i++){

		for (int j = 0; j < SISI_PAPAN; j++){

				if (realBoard[i][j] != '*'){
					realBoard[i][j] = '*';
					realBoard[baris][kolom] = '-';
					return;
				}
			}
	}
	return;
}

// Fungsi untuk memainkan minesweeper
void mainGame (){
	// Variabel boolean untuk menentukan
    // sudah atau belum berakhirnya game
	bool gameOver = false;

	// char realBoard untuk menyimpan posisi semua bom
    // dan posisi aman
    // playerBoard hanya bisa dilihat pemain
	char realBoard[MAXSISI][MAXSISI], playerBoard[MAXSISI][MAXSISI];

    // sisa move yang bisa dilakukan
	int movesLeft = SISI_PAPAN * SISI_PAPAN - BOM;
    int x, y;
	int bom[MAXBOM][2]; // menyimpan koordinat semua bom

    // mengisi array
	inisialisasi (realBoard, playerBoard);

	// mengisi posisi bom dengan acak
	placeBom (bom, realBoard);

    cetakPapan (realBoard);

	int movePertama = 0;

    // selama belum gameOver
	while (gameOver == false){
		cetakPapan (playerBoard);
		pilihPosisi (&x, &y);

		// pilihan pertama dijamin aman
		if (movePertama == 0){
			if (isBom (x, y, realBoard) == true)
				replaceBom (x, y, realBoard);
		}

		movePertama ++;

		gameOver = Minesweeper (playerBoard, realBoard, bom, x, y, &movesLeft);

		if ( (gameOver == false) && (movesLeft == 0) ){
			printf ("\nKAMU MENANG!\n\n");
			gameOver = true;
		}
	}
	return;
}

int main (){
    banner();

	mainGame ();

	return 0;
}
