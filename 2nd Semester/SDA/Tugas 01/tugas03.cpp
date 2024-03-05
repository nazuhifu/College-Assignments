/*
NIM: L0123084
Nama: Mohammad Nazhiif Al-Ghoniy
Kelas: C
*/

#include <iostream>
#include <queue>
#include <stack>
#include <string>

void commandPrompt(std::queue <std::string> &perintah) {
    std::stack <int> stack;
    while(!perintah.empty()) {
        // Jalankan perintah yang paling awal
        // lalu hapus dari queue perintah yang dijalankan
        std::string command = perintah.front();
        perintah.pop();

        if (command.substr(0, 4) == "PUSH") {
            // Ambil angka di string tersebut
            // lalu convert dari string ke integer
            int angka = std::stoi(command.substr(5));
            stack.push(angka);
        } else if (command.substr(0, 3) == "TOP") {
            if (!stack.empty()) {
                // Cetak angka yang teratas di stack
                std::cout << stack.top();
            }
        } else if (command.substr(0, 3) == "POP") {
            if(!stack.empty()) {
                stack.pop();
            }
        }
    }
}

int main() {
    std::queue <std::string> perintah;

    // Masukan perintah ke komputer
    perintah.push("PUSH 0");
    perintah.push("PUSH 0");
    perintah.push("TOP");
    perintah.push("PUSH 1");
    perintah.push("TOP");
    perintah.push("POP");
    perintah.push("POP");
    perintah.push("TOP");

    // Eksekusi perintah
    commandPrompt(perintah);

    return 0;
}
