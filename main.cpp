#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// INI STRUCT (Rapi)
struct Mahasiswa {
    string nim;
    string nama;
    string jalur;    // SNBP / SNBT / Mandiri
    string prodi;
    Mahasiswa* next;
};

Mahasiswa* head       = nullptr;
string daftarJalur[3] = {"SNBP", "SNBT", "Mandiri"};

//  HELPER [Tolongin saya plis] (Rapi)
void cetakHeader() {
    cout << string(55, '=') << endl;
    cout << left
         << setw(12) << "NIM"
         << setw(22) << "Nama"
         << setw(10) << "Jalur"
         << "Prodi" << endl;
    cout << string(55, '-') << endl;
}

void cetakBaris(Mahasiswa* m) {
    cout << left
         << setw(12) << m->nim
         << setw(22) << m->nama
         << setw(10) << m->jalur
         << m->prodi
         << endl;
}

// ============================================================
//  INSERT
// ============================================================
void insert(string nim, string nama, string jalur, string prodi) {

    Mahasiswa* newNode = new Mahasiswa();
    newNode->nim   = nim;
    newNode->nama  = nama;
    newNode->jalur = jalur;
    newNode->prodi = prodi;
    newNode->next  = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        Mahasiswa* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    cout << "  [OK] Data \"" << nama << "\" berhasil ditambahkan.\n";
}

void inputMahasiswaBaru() {
    string nim, nama, prodi;
    int    pilihanJalur;

    cout << "\n  --- INPUT DATA MAHASISWA BARU ---\n";
    cout << "  NIM         : "; cin >> nim;
    cin.ignore();
    cout << "  Nama Lengkap: "; getline(cin, nama);
    cout << "  Prodi       : "; getline(cin, prodi);
    cout << "  Jalur Masuk :\n";
    for (int i = 0; i < 3; i++) {
        cout << "    " << (i + 1) << ". " << daftarJalur[i] << "\n";
    }
    cout << "  Pilih (1-3) : "; cin >> pilihanJalur;
    if (pilihanJalur < 1 || pilihanJalur > 3) pilihanJalur = 1;

    insert(nim, nama, daftarJalur[pilihanJalur - 1], prodi);
}

// ============================================================
//  DISPLAY
// ============================================================
void display() {
    if (head == nullptr) {
        cout << "\n  [INFO] Belum ada data mahasiswa.\n";
        return;
    }

    int total = 0;
    Mahasiswa* hitung = head;
    while (hitung != nullptr) {
        total++;
        hitung = hitung->next;
    }

    cout << "\n  DAFTAR MAHASISWA BARU UPI 2026"
         << " (Total: " << total << " mahasiswa)\n";
    cetakHeader();

    Mahasiswa* temp = head;
    int no = 1;
    while (temp != nullptr) {
        cout << no++ << ". ";
        cetakBaris(temp);
        temp = temp->next;
    }

    cout << string(55, '=') << endl;
}

// ============================================================
//  SEARCH
// ============================================================
Mahasiswa* search(string nim) {
    Mahasiswa* temp = head;
    while (temp != nullptr) {
        if (temp->nim == nim) return temp;
        temp = temp->next;
    }
    return nullptr;
}

void cariDanTampilkan(string nim) {
    Mahasiswa* hasil = search(nim);
    if (hasil == nullptr) {
        cout << "\n  [!] NIM \"" << nim << "\" tidak ditemukan.\n";
    } else {
        cout << "\n  [OK] Data ditemukan:\n";
        cetakHeader();
        cetakBaris(hasil);
        cout << string(55, '=') << endl;
    }
}


// ============================================================
//  MENU & MAIN
// ============================================================
void tampilMenu() {
    cout << "\n";
    cout << "  +-------------------------------------------+\n";
    cout << "  |   SISTEM ADMINISTRASI PMB UPI 2026        |\n";
    cout << "  |   Struct + Linked List (C++)              |\n";
    cout << "  +-------------------------------------------+\n";
    cout << "  |  1. Tampilkan Semua Data  (Display)       |\n";
    cout << "  |  2. Tambah Mahasiswa      (Insert)        |\n";
    cout << "  |  3. Cari Mahasiswa        (Search)        |\n";
    cout << "  |  4. Hapus Mahasiswa       (Delete)        |\n";
    cout << "  |  0. Keluar                                |\n";
    cout << "  +-------------------------------------------+\n";
    cout << "  Pilihan: ";
}

int main() {

    // Data awal mahasiswa yang sudah diterima
    insert("2600001", "Andi Saputra",   "SNBP",    "Ilmu Komputer");
    insert("2600002", "Budi Santoso",   "SNBT",    "Teknik Elektro");
    insert("2600003", "Citra Dewi",     "Mandiri", "Pendidikan Bahasa");
    insert("2600004", "Pratama Putra", "SNBT",    "Rek. Perangkat Lunak");
    insert("2600005", "Eva Rahmawati",  "SNBP",    "Matematika");

    int pilihan = -1;

    while (pilihan != 0) {
        tampilMenu();
        cin >> pilihan;

        if (pilihan == 1) {
            display();

        } else if (pilihan == 2) {
            inputMahasiswaBaru();

        } else if (pilihan == 3) {
            string nimCari;
            cout << "\n  Masukkan NIM yang dicari: ";
            cin  >> nimCari;
            cariDanTampilkan(nimCari);

        } else if (pilihan == 4) {
            string nimHapus;
            cout << "\n  Masukkan NIM yang dihapus: ";
            cin  >> nimHapus;
            hapus(nimHapus);

        } else if (pilihan == 0) {
            cout << "\n  Terima kasih. Sampai jumpa!\n\n";

        } else {
            cout << "\n  [!] Pilihan tidak valid. Coba lagi.\n";
        }
    }

    hapusSemua();
    return 0;
}
