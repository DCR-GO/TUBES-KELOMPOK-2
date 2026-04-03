#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

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
