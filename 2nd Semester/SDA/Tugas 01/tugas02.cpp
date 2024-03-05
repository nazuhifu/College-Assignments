/*
NIM: L0123084
Nama: Mohammad Nazhiif Al-Ghoniy
Kelas: C
*/

#include <iostream>
#include <stack>
#include <string>

// Deklarasi stack global
std::stack <std::string> backStack;
std::stack <std::string> forwardStack;

// Fungsi untuk mengunjungi sebuah website
void visit(std::string url) {

    // Tambah history ke backStack
    backStack.push(url);
    std::cout << "Mengunjungi " << url << std::endl;
    
    // Kosongkan stack forward karena mengunjungi
    // halaman baru
    while (!forwardStack.empty()) {
        forwardStack.pop();
    }
}

// Fungsi untuk kembali ke halaman sebelumnya
void back() {
    // Jika backStack tidak kosong
    if (!backStack.empty()) {
        // Simpan url sekarang ke current
        // lalu pop url sekarang dari backStack
        // dan push url ke forwardStack
        std::string current = backStack.top();
        backStack.pop();
        forwardStack.push(current);

        if (!backStack.empty()) {
            std::cout << "Mengunjungi " << backStack.top() << std::endl;
        } else {
            std::cout << "Tidak ada halaman sebelumnya" << std::endl;
        } 
    } else {
        std::cout << "Tidak ada halaman sebelumnya" << std::endl;
    }
}

// Fungsi untuk maju ke halaman setelahnya
void forward() {
    // Jika halaman selanjutnya ada
    if (!forwardStack.empty()) {
        std::string current = forwardStack.top();
        forwardStack.pop();
        backStack.push(current);

        std::cout << "Mengunjungi " << current << std::endl;
        
    } else {
        std::cout << "Tidak ada halaman setelahnya" << std::endl;
    }
}

int main() {
    visit("google.com");
    visit("instagram.com");
    visit("github.com");
    back();
    back();
    forward();
    forward();
    visit("stackoverflow.com");
    forward();

    return 0;
}
