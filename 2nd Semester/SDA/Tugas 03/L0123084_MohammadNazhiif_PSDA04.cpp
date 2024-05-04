#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

// Struktur data untuk menyimpan informasi user
struct User
{
    string username;
    string password;
};

// Set untuk menyimpan daftar username yang sudah terdaftar
set<string> Unames;

// Map untuk menyimpan informasi pengguna berdasarkan username
map<string, User> users;

// Fungsi untuk mendaftarkan pengguna baru
void signUp(string username, string password)
{
    // Periksa apakah username sudah terdaftar
    if (Unames.find(username) != Unames.end())
    {
        cout << "Maaf, Username sudah terdaftar!" << endl;
        return;
    }

    // Tambahkan username ke set
    Unames.insert(username);

    // Tambahkan informasi user ke map
    users[username] = {username, password};

    cout << "Pendaftaran berhasil." << endl;
}

// Fungsi untuk login user
void login(string username, string password)
{
    // Periksa apakah username terdaftar
    if (users.find(username) == users.end())
    {
        cout << "Login gagal. Username tidak ditemukan." << endl;
        return;
    }

    // Periksa apakah password cocok
    if (users[username].password == password)
    {
        cout << "Login berhasil." << endl;
    }
    else
    {
        cout << "Login gagal. Password salah." << endl;
    }
}

int main()
{
    signUp("user1", "password123");
    signUp("user2", "hello456");
    login("user1", "password123");
    login("user1", "wrongpassword");
    login("user3", "password789");

    signUp("user3", "info");
    login("user4", "info");

    return 0;
}
