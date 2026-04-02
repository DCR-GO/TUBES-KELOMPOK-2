/*
 * ============================================================
 *  SISTEM ADMINISTRASI PENERIMAAN MAHASISWA BARU
 *  Universitas Pendidikan Indonesia (UPI) - Tahun 2026
 * ============================================================
 *  Mata Kuliah : Struktur Data dan Algoritma
 *  Konsep      : Struct, Pointer, Array, Linked List
 * ============================================================
 */

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// ============================================================
// STRUCT: Mendefinisikan data satu mahasiswa (satu node)
// ============================================================
struct Mahasiswa {
    string nim;
    string nama;
    string jalur;    // SNBP / SNBT / Mandiri
    string prodi;
    Mahasiswa* next; // Pointer ke node berikutnya (Linked List)
};

// ============================================================
// KELAS: LinkedList untuk mengelola data mahasiswa
// ============================================================
class LinkedList {
private:
    Mahasiswa* head;
    int jumlah;

public:
    // Constructor: inisialisasi head = NULL
    LinkedList() {
        head   = nullptr;
        jumlah = 0;
    }

    // Destructor: bebaskan semua memori
    ~LinkedList() {
        hapusSemua();
    }

    // ----------------------------------------------------------
    // HELPER: Cetak garis pemisah
    // ----------------------------------------------------------
    void cetakGaris(char c = '-', int len = 65) {
        cout << string(len, c) << endl;
    }

    // ----------------------------------------------------------
    // HELPER: Cetak header tabel
    // ----------------------------------------------------------
    void cetakHeader() {
        cetakGaris('=');
        cout << left
             << setw(12) << "NIM"
             << setw(22) << "Nama"
             << setw(10) << "Jalur"
             << setw(16) << "Prodi"
             << endl;
        cetakGaris();
    }

    // ----------------------------------------------------------
    // HELPER: Cetak satu baris data mahasiswa
    // ----------------------------------------------------------
    void cetakBaris(Mahasiswa* m) {
        cout << left
             << setw(12) << m->nim
             << setw(22) << m->nama
             << setw(10) << m->jalur
             << setw(16) << m->prodi
             << endl;
    }

    // ----------------------------------------------------------
    // INSERT: Tambah node baru di akhir linked list
    // ----------------------------------------------------------
    void insert(string nim, string nama, string jalur,
                string prodi) {

        // Buat node baru di heap (menggunakan pointer)
        Mahasiswa* newNode = new Mahasiswa();
        newNode->nim   = nim;
        newNode->nama  = nama;
        newNode->jalur = jalur;
        newNode->prodi = prodi;
        newNode->next  = nullptr;

        // Kasus 1: list masih kosong
        if (head == nullptr) {
            head = newNode;
        }
        // Kasus 2: list sudah ada isinya -> traverse ke tail
        else {
            Mahasiswa* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode; // sambung ke node terakhir
        }

        jumlah++;
        cout << "\n  [OK] Data mahasiswa \"" << nama
             << "\" berhasil ditambahkan.\n";
    }

    // ----------------------------------------------------------
    // DISPLAY: Tampilkan semua data (traversal dari head ke tail)
    // ----------------------------------------------------------
    void display() {
        if (head == nullptr) {
            cout << "\n  [INFO] Belum ada data mahasiswa.\n";
            return;
        }

        cout << "\n  DAFTAR MAHASISWA BARU UPI 2026"
             << " (Total: " << jumlah << " mahasiswa)\n";
        cetakHeader();

        Mahasiswa* temp = head;
        int no = 1;
        while (temp != nullptr) {
            cout << no++ << ". ";
            cetakBaris(temp);
            temp = temp->next; // geser pointer ke node berikutnya
        }
        cetakGaris('=');
    }

    // ----------------------------------------------------------
    // SEARCH: Cari mahasiswa berdasarkan NIM
    // ----------------------------------------------------------
    Mahasiswa* search(string nim) {
        Mahasiswa* temp = head;

        while (temp != nullptr) {
            if (temp->nim == nim) {
                return temp; // ditemukan, kembalikan pointer-nya
            }
            temp = temp->next;
        }
        return nullptr; // tidak ditemukan
    }

    void cariDanTampilkan(string nim) {
        Mahasiswa* hasil = search(nim);

        if (hasil == nullptr) {
            cout << "\n  [!] Mahasiswa dengan NIM \"" << nim
                 << "\" tidak ditemukan.\n";
        } else {
            cout << "\n  [OK] Data ditemukan:\n";
            cetakHeader();
            cetakBaris(hasil);
            cetakGaris('=');
        }
    }

    // ----------------------------------------------------------
    // DELETE: Hapus node berdasarkan NIM
    // ----------------------------------------------------------
    void hapus(string nim) {
        if (head == nullptr) {
            cout << "\n  [INFO] List kosong, tidak ada yang dihapus.\n";
            return;
        }

        // Kasus 1: node yang dihapus adalah head
        if (head->nim == nim) {
            Mahasiswa* temp = head;
            head = head->next; // geser head ke node berikutnya
            string namaHapus = temp->nama;
            delete temp;       // bebaskan memori
            jumlah--;
            cout << "\n  [OK] Data \"" << namaHapus
                 << "\" berhasil dihapus.\n";
            return;
        }

        // Kasus 2: node di tengah atau akhir
        // -> perlu pointer ke node SEBELUMNYA
        Mahasiswa* prev = head;
        Mahasiswa* curr = head->next;

        while (curr != nullptr) {
            if (curr->nim == nim) {
                prev->next = curr->next; // bypass node yang dihapus
                string namaHapus = curr->nama;
                delete curr;             // bebaskan memori
                jumlah--;
                cout << "\n  [OK] Data \"" << namaHapus
                     << "\" berhasil dihapus bro.\n";
                return;
            }
            prev = curr;
            curr = curr->next;
        }

        cout << "\n  [!] NIM \"" << nim << "\" tidak ditemukan.\n";
    }

    // ----------------------------------------------------------
    // HAPUS SEMUA: Bebaskan seluruh memori (destructor)
    // ----------------------------------------------------------
    void hapusSemua() {
        Mahasiswa* temp = head;
        while (temp != nullptr) {
            Mahasiswa* next = temp->next;
            delete temp;
            temp = next;
        }
        head   = nullptr;
        jumlah = 0;
    }

    // Getter jumlah
    int getJumlah() { return jumlah; }
};

// ============================================================
// HELPER: Input mahasiswa baru secara interaktif
// ============================================================
void inputMahasiswaBaru(LinkedList& db) {
    string nim, nama, prodi;
    int    pilihanJalur;
    string jalur;

    // Array nama jalur (penggunaan Array dari materi kuliah)
    string daftarJalur[3] = {"SNBP", "SNBT", "Mandiri"};

    cout << "\n  --- INPUT DATA MAHASISWA BARU ---\n";
    cout << "  NIM        : "; cin >> nim;
    cin.ignore();
    cout << "  Nama Lengkap: "; getline(cin, nama);
    cout << "  Prodi      : "; getline(cin, prodi);
    cout << "  Jalur Masuk:\n";
    for (int i = 0; i < 3; i++) {
        cout << "    " << (i+1) << ". " << daftarJalur[i] << "\n";
    }
    cout << "  Pilih (1-3): "; cin >> pilihanJalur;
    if (pilihanJalur < 1 || pilihanJalur > 3) pilihanJalur = 1;
    jalur = daftarJalur[pilihanJalur - 1];

    db.insert(nim, nama, jalur, prodi);
}

// ============================================================
// FUNGSI UTAMA
// ============================================================
int main() {
    LinkedList db; // inisialisasi linked list
    int pilihan;

    // Data awal: beberapa mahasiswa yang sudah diterima
    db.insert("2600001", "Andi Saputra",    "SNBP",    "Ilmu Komputer");
    db.insert("2600002", "Budi Santoso",    "SNBT",    "Teknik Elektro");
    db.insert("2600003", "Citra Dewi",      "Mandiri", "Pendidikan Bahasa");
    db.insert("2600004", "Dwicky Pratama",  "SNBT",    "Rek. Perangkat Lunak");
    db.insert("2600005", "Eva Rahmawati",   "SNBP",    "Matematika");

    // Loop menu utama
    do {
        cout << "\n";
        cout << "  ╔═══════════════════════════════════════════╗\n";
        cout << "  ║   SISTEM ADMINISTRASI PMB UPI 2026        ║\n";
        cout << "  ║   Struct + Linked List (C++)              ║\n";
        cout << "  ╠═══════════════════════════════════════════╣\n";
        cout << "  ║  1. Tampilkan Semua Data  (Display)       ║\n";
        cout << "  ║  2. Tambah Mahasiswa      (Insert)        ║\n";
        cout << "  ║  3. Cari Mahasiswa        (Search)        ║\n";
        cout << "  ║  4. Hapus Mahasiswa       (Delete)        ║\n";
        cout << "  ║  0. Keluar                                ║\n";
        cout << "  ╚═══════════════════════════════════════════╝\n";
        cout << "  Pilihan: ";
        cin  >> pilihan;

        switch (pilihan) {
            case 1: {
                db.display();
                break;
            }
            case 2: {
                inputMahasiswaBaru(db);
                break;
            }
            case 3: {
                string nimCari;
                cout << "\n  Masukkan NIM yang dicari: ";
                cin  >> nimCari;
                db.cariDanTampilkan(nimCari);
                break;
            }
            case 4: {
                string nimHapus;
                cout << "\n  Masukkan NIM yang akan dihapus: ";
                cin  >> nimHapus;
                db.hapus(nimHapus);
                break;
            }
            case 0: {
                cout << "\n  Terima kasih. Memori dibebaskan. Program selesai.\n\n";
                break;
            }
            default: {
                cout << "\n  [!] Pilihan tidak valid.\n";
            }
        }

    } while (pilihan != 0);

    // Destructor LinkedList otomatis dipanggil di sini
    // -> menghapus seluruh node dan membebaskan memori
    return 0;
}