#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Struktur untuk menyimpan informasi lagu
struct Song {
    std::string title;
    std::string artist;
    int duration;
};

// Operator overloading untuk memudahkan pengurutan
bool operator<(const Song& a, const Song& b) {
    return a.title < b.title;
}

// Fungsi untuk menukar dua elemen dalam vector
void swap(std::vector<Song>& songs, int i, int j) {
    Song temp = songs[i];
    songs[i] = songs[j];
    songs[j] = temp;
}

// Fungsi untuk memartisi array dalam quick sort
int partition(std::vector<Song>& songs, int low, int high, bool (*cmp)(const Song&, const Song&)) {
    Song pivot = songs[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (cmp(songs[j], pivot)) {
            i++;
            swap(songs, i, j);
        }
    }

    swap(songs, i + 1, high);
    return i + 1;
}

// Fungsi quick sort
void quickSort(std::vector<Song>& songs, int low, int high, bool (*cmp)(const Song&, const Song&)) {
    if (low < high) {
        int pivotIndex = partition(songs, low, high, cmp);
        quickSort(songs, low, pivotIndex - 1, cmp);
        quickSort(songs, pivotIndex + 1, high, cmp);
    }
}

// Fungsi untuk membandingkan judul lagu
bool compareTitle(const Song& a, const Song& b) {
    return a.title < b.title;
}

// Fungsi untuk membandingkan artis lagu
bool compareArtist(const Song& a, const Song& b) {
    return a.artist < b.artist;
}

// Fungsi untuk membandingkan durasi lagu
bool compareDuration(const Song& a, const Song& b) {
    return a.duration < b.duration;
}

int main() {
    std::vector<Song> songs = {
        {"Indonesia Raya", "Wage Rudolf Supratman", 111},
        {"Never Gonna Give You Up", "Rick Astley", 213},
        {"Everything Is Awesome!!!", "Tegan and Sara", 164},
        {"I Want It That Way", "Backstreet Boys", 220},
        {"Balonku", "Abdullah Totong Mahmud", 180}
    };

    std::cout << "Daftar Lagu Sebelum Diurutkan:" << std::endl;
    for (const Song& song : songs) {
        std::cout << "Judul: " << song.title << ", Artis: " << song.artist << ", Durasi: " << song.duration << " detik" << std::endl;
    }

    // Urutkan berdasarkan judul
    quickSort(songs, 0, songs.size() - 1, compareTitle);
    std::cout << "\nDaftar Lagu Setelah Diurutkan Berdasarkan Judul:" << std::endl;
    for (const Song& song : songs) {
        std::cout << "Judul: " << song.title << ", Artis: " << song.artist << ", Durasi: " << song.duration << " detik" << std::endl;
    }

    // Urutkan berdasarkan artis
    quickSort(songs, 0, songs.size() - 1, compareArtist);
    std::cout << "\nDaftar Lagu Setelah Diurutkan Berdasarkan Artis:" << std::endl;
    for (const Song& song : songs) {
        std::cout << "Judul: " << song.title << ", Artis: " << song.artist << ", Durasi: " << song.duration << " detik" << std::endl;
    }

    // Urutkan berdasarkan durasi
    quickSort(songs, 0, songs.size() - 1, compareDuration);
    std::cout << "\nDaftar Lagu Setelah Diurutkan Berdasarkan Durasi:" << std::endl;
    for (const Song& song : songs) {
        std::cout << "Judul: " << song.title << ", Artis: " << song.artist << ", Durasi: " << song.duration << " detik" << std::endl;
    }

    return 0;
}
