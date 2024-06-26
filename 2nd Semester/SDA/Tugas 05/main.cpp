#include <bits/stdc++.h>
using namespace std;

const int MAX_STUDENTS = 50;

// Graf pertemanan sebagai matriks adjacency
bool adj_matrix[MAX_STUDENTS][MAX_STUDENTS] = {false};
vector<string> student_names(MAX_STUDENTS);
int num_students = 0;

// Cek pertemanan mahasiswa berdasarkan nama
int getStudentId(const string &name)
{
    for (int i = 0; i < num_students; i++)
    {
        if (student_names[i] == name)
            return i;
    }
    return -1; // Mahasiswa tidak ditemukan
}

// 1. Menambahkan mahasiswa beserta teman-temannya
void addStudent(const string &name, const vector<string> &friends)
{
    int idx = getStudentId(name);
    if (idx == -1)
    {
        idx = num_students;
        student_names[num_students++] = name;
    }

    // cout << "\nidx= " << idx << endl;
    // cout << student_names[idx] << endl;

    for (const string &friend_name : friends)
    {
        int friend_idx = getStudentId(friend_name);
        if (friend_idx == -1)
        {
            friend_idx = num_students;
            student_names[num_students++] = friend_name;
            // cout << student_names[friend_idx] << endl;
        }
        // cout << "friend_idx=" << friend_idx << endl;
        if (friend_idx != -1)
        {
            adj_matrix[idx][friend_idx] = true;
            adj_matrix[friend_idx][idx] = true;
        }
    }
}

// 2. Menambahkan hubungan pertemanan antara dua mahasiswa yang sudah terdaftar.
void addFriendship(const string &student1, const string &student2)
{
    int idx1 = getStudentId(student1);
    int idx2 = getStudentId(student2);
    if (idx1 != -1 && idx2 != -1) // Jika kedua mahasiswa ada
    {
        adj_matrix[idx1][idx2] = true;
        adj_matrix[idx2][idx1] = true;
    }
}

// 3. Menghapus mahasiswa beserta seluruh hubungan pertemanannya.
void removeStudent(const string &name)
{
    int idx = getStudentId(name);
    if (idx != -1)
    {
        // Hapus pertemanan
        for (int i = 0; i < num_students; i++)
        {
            adj_matrix[idx][i] = false;
            adj_matrix[i][idx] = false;
        }

        // Hapus mahasiswa
        student_names[idx] = ""; // Kosongkan nama mahasiswa yang dihapus

        // Geser indeks mahasiswa setelah idx ke kiri
        for (int i = idx + 1; i < num_students; i++)
        {
            student_names[i - 1] = student_names[i];
            for (int j = 0; j < num_students; j++)
            {
                adj_matrix[i - 1][j] = adj_matrix[i][j];
                adj_matrix[j][i - 1] = adj_matrix[j][i];
            }
        }

        num_students--;
    }
}

// 4. Mencari teman bersama antara dua mahasiswa yang sudah terdaftar.
vector<string> findCommon(const string &student1, const string &student2)
{
    vector<string> common_friends;
    int idx1 = getStudentId(student1);
    int idx2 = getStudentId(student2);
    if (idx1 != -1 && idx2 != -1)
    {
        for (int i = 0; i < num_students; i++)
        {
            // Jika punya teman yang sama
            if (adj_matrix[idx1][i] && adj_matrix[idx2][i])
                common_friends.push_back(student_names[i]);
        }
    }
    return common_friends;
}

// 5. Menampilkan daftar teman dari seorang mahasiswa tertentu.
vector<string> getFriendList(const string &name)
{
    vector<string> friend_list;
    int idx = getStudentId(name);
    if (idx != -1)
    {
        for (int i = 0; i < num_students; i++)
        {
            if (adj_matrix[idx][i])
                friend_list.push_back(student_names[i]);
        }
    }
    return friend_list;
}

int main()
{
    // Menambahkan mahasiswa baru beserta daftar teman-temannya
    addStudent("Andi", {"Budi", "Citra", "Dani"});
    addStudent("Budi", {"Andi", "Citra"});
    addStudent("Citra", {"Andi", "Budi", "Eka"});
    addStudent("Dani", {"Andi"});
    addStudent("Eka", {"Citra"});

    // Menambahkan hubungan pertemanan antara dua mahasiswa yang sudah terdaftar
    addFriendship("Andi", "Eka");

    // Menghapus mahasiswa beserta seluruh hubungan pertemanannya
    removeStudent("Dani");

    // Mencari teman bersama antara dua mahasiswa yang sudah terdaftar
    vector<string> common_friends = findCommon("Andi", "Citra");
    cout << "Teman bersama antara Andi dan Citra: ";
    for (const string &friend_name : common_friends)
    {
        cout << friend_name << " ";
    }
    cout << endl;

    // Menampilkan daftar teman dari seorang mahasiswa tertentu
    vector<string> friend_list = getFriendList("Andi");
    cout << "Daftar teman Andi: ";
    for (const string &friend_name : friend_list)
    {
        cout << friend_name << " ";
    }
    cout << endl;

    /* for (int i = 0; i < num_students; i++)
    {
        for (int j = 0; j < num_students; j++)
        {
            cout << i << " " << student_names[i] << "- " << j << " " << student_names[j] << " " << adj_matrix[i][j] << endl;
        }
        cout << endl;
    } */
    
    // cout << "num_students= " << num_students;

    return 0;
}
