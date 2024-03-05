/*
NIM: L0123084
Nama: Mohammad Nazhiif Al-Ghoniy
Kelas: C
*/

#include <iostream>
#include <list>
#include <string>

int main() {
    // Buat list untuk menyimpan daftar buah-buahan
    std::list<std::string> Buah;

    // Menambahkan buah-buahan ke dalam list Buah
    Buah.push_back("Rambutan");
    Buah.push_back("Jambu");
    Buah.push_back("Jeruk");
    Buah.push_back("Melon");
    Buah.push_back("Semangka");
    Buah.push_back("Durian");

    // Membuat dua list baru
    std::list<std::string> list1;
    std::list<std::string> list2;

    // Memindahkan elemen ke list1
    std::list<std::string>::iterator it = Buah.begin();
    for(int i = 0; i < 3; i++) {
        list1.push_back(*it);
        ++it;
    }

    for(int i = 0; i < 3; i++) {
        list2.push_back(*it);
        ++it;
    }

    // Menghapus Jambu dan Durian
    list1.remove("Jambu");
    list2.remove("Durian");

    // Mencetak isi list
    std::cout << "=== Seluruh isi list ===" << std::endl;

    for(const std::string &buah : Buah) {
        std::cout << buah << std::endl;
    }

    // Cetak list 1
    std::cout << "\n=== List 1 ===" << std::endl;
    for(const std::string &buah: list1) {
        std::cout << buah << std::endl;
    }

    // Cetak list 2
    std::cout << "\n=== List 2 ===" << std::endl;
    for(const std::string &buah: list2) {
        std::cout << buah << std::endl;
    }

    return 0;
}
