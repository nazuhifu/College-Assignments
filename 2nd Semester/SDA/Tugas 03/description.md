# Tugas Praktikum Set dan Map

Note:

- Kerjakan dengan bahasa C++
- Kumpulkan semua source code dengan format **NIM_Nama Lengkap_PSDA04.cpp** dalam assignment Google Classroom

## Soal: Program Sign-up dan Login

Andi ingin membuat program sederhana untuk sign-up dan login menggunakan C++. Program ini memanfaatkan struktur data set dan map untuk menyimpan informasi pengguna.

#### Bagian 1: Sign-up

Andi ingin membuat fungsi untuk memungkinkan pengguna untuk mendaftar dengan username dan password mereka. Namun, setiap username harus unik dalam sistemnya. Jika username yang diinginkan telah digunakan sebelumnya, sistem akan menolak pendaftaran tersebut.

Tugas Anda adalah menulis fungsi C++ untuk mendaftar pengguna baru. Fungsi ini harus menerima masukan berupa username dan password. Pastikan untuk memeriksa apakah username sudah digunakan sebelumnya. Jika belum, tambahkan username beserta passwordnya ke dalam sistem.

#### Bagian 2: Login

Setelah mendaftar, pengguna harus dapat masuk ke dalam sistem dengan username dan password yang benar. Andi ingin memastikan bahwa pengguna hanya dapat masuk jika mereka memasukkan password yang sesuai dengan username yang terdaftar.

Tugas Anda adalah menulis fungsi C++ untuk memverifikasi login pengguna. Fungsi ini harus menerima masukan berupa username dan password. Pastikan untuk memeriksa apakah username dan password yang dimasukkan cocok dengan yang terdaftar dalam sistem.

Gunakan struktur data set dan map untuk menyimpan informasi pengguna dengan efisien.

Contoh: 

```
Input:
signUp("user1", "password123")
signUp("user2", "hello456")
login("user1", "password123")
login("user1", "wrongpassword")
login("user3", "password789")

Output:
Pendaftaran berhasil.
Pendaftaran berhasil.
Login berhasil.
Login gagal. Password salah.
Login gagal. Username tidak ditemukan.
```

Andi berharap Anda dapat membuat program yang efisien dan dapat menangani operasi sign-up dan login dengan baik. Selamat mengerjakan!
