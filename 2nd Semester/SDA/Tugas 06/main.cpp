#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip> // untuk memanipulasi output

// Struktur data untuk menyimpan informasi lagu
struct Lagu
{
    std::string judul;
    std::string artis;
    int durasi;
};

// Fungsi untuk menukar dua lagu
void swap(Lagu &a, Lagu &b)
{
    std::swap(a.judul, b.judul);
    std::swap(a.artis, b.artis);
    std::swap(a.durasi, b.durasi);
}

// Bubble Sort berdasarkan judul
void bubbleSortByJudul(std::vector<Lagu> &koleksi)
{
    int n = koleksi.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (koleksi[j].judul > koleksi[j + 1].judul)
            {
                swap(koleksi[j], koleksi[j + 1]);
            }
        }
    }
}

// Selection Sort berdasarkan artis
void selectionSortByArtis(std::vector<Lagu> &koleksi)
{
    int n = koleksi.size();
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (koleksi[j].artis < koleksi[minIndex].artis)
            {
                minIndex = j;
            }
        }
        swap(koleksi[i], koleksi[minIndex]);
    }
}

// Insertion Sort berdasarkan durasi
void insertionSortByDurasi(std::vector<Lagu> &koleksi)
{
    int n = koleksi.size();
    for (int i = 1; i < n; i++)
    {
        Lagu key = koleksi[i];
        int j = i - 1;
        while (j >= 0 && koleksi[j].durasi > key.durasi)
        {
            koleksi[j + 1] = koleksi[j];
            j--;
        }
        koleksi[j + 1] = key;
    }
}

// Fungsi untuk mencetak daftar lagu dalam bentuk tabel
void cetakTabel(const std::vector<Lagu> &koleksi)
{
    const int judul_width = 30;
    const int artis_width = 30;
    const int durasi_width = 10;

    std::cout << std::setw(judul_width) << std::left << "Judul"
              << std::setw(artis_width) << std::left << "Artis"
              << std::setw(durasi_width) << std::right << "Durasi (detik)" << std::endl;

    std::cout << std::setfill('-') << std::setw(judul_width + artis_width + durasi_width + 2) << "-" << std::setfill(' ') << std::endl;

    for (const auto &lagu : koleksi)
    {
        std::cout << std::setw(judul_width) << std::left << lagu.judul
                  << std::setw(artis_width) << std::left << lagu.artis
                  << std::setw(durasi_width) << std::right << lagu.durasi << std::endl;
    }
}

int main()
{
    std::vector<Lagu> koleksi = {
        {"Indonesia Raya", "Wage Rudolf Supratman", 111},
        {"Never Gonna Give You Up", "Rick Astley", 213},
        {"Everything Is Awesome!!!", "Tegan and Sara", 164},
        {"I Want It That Way", "Backstreet Boys", 220},
        {"Balonku", "Abdullah Totong Mahmud", 180}};

    std::cout << "Koleksi lagu sebelum diurutkan:\n";
    cetakTabel(koleksi);

    std::cout << "\n\nUrutkan lagu berdasarkan:\n";
    std::cout << "1. Judul\n";
    std::cout << "2. Artis\n";
    std::cout << "3. Durasi\n";

    int choice;
    do
    {
        std::cout << "Input pilihan (1-3): ";
        std::cin >> choice;
    } while (choice < 1 || choice > 3);

    switch (choice)
    {
    case 1:
        bubbleSortByJudul(koleksi);
        std::cout << "\nKoleksi lagu setelah diurutkan berdasarkan judul:\n";
        cetakTabel(koleksi);
        break;
    case 2:
        selectionSortByArtis(koleksi);
        std::cout << "\nKoleksi lagu setelah diurutkan berdasarkan artis:\n";
        cetakTabel(koleksi);
        break;
    case 3:
        insertionSortByDurasi(koleksi);
        std::cout << "\nKoleksi lagu setelah diurutkan berdasarkan durasi:\n";
        cetakTabel(koleksi);
        break;

    default:
        break;
    }

    std::cout << std::endl;

    return 0;
}
