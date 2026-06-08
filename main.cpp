#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <sstream>
using namespace std;

const string FILE_CSV = "riwayat.csv";

int inputAngka() {
    int nilai;
    string baris;
    getline(cin, baris);
    if (baris.empty()) return -99;
 
    bool valid = true;
    int i = 0;
    if (baris[0] == '-') i = 1;
    if (i >= (int)baris.size()) valid = false;
 
    while (i < (int)baris.size()) {
        if (baris[i] < '0' || baris[i] > '9') {
            valid = false;
            break;
        }
        i++;
    }
 
    if (!valid) return -99;
 
    stringstream ss(baris);
    ss >> nilai;
    return nilai;
}

const int MAX_KOTA = 8;
string namaKota[MAX_KOTA] = {
    "Bandung", "Jakarta", "Bogor", "Bekasi",
    "Depok",   "Cimahi",  "Sukabumi", "Karawang"
};

struct NodeRiwayat {
    string idPaket;
    string pengirim;
    string penerima;
    string tujuan;
    NodeRiwayat* next;
};

NodeRiwayat* headRiwayat = NULL;

void tambahRiwayat(string id, string pengirim, string penerima, string tujuan) {
    NodeRiwayat* baru = new NodeRiwayat();
    baru->idPaket   = id;
    baru->pengirim  = pengirim;
    baru->penerima  = penerima;
    baru->tujuan    = tujuan;
    baru->next      = NULL;

    if (headRiwayat == NULL) {
        headRiwayat = baru;
    } else {
        NodeRiwayat* temp = headRiwayat;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = baru;
    }
}

void tampilRiwayat() {
    if (headRiwayat == NULL) {
        cout << "  [!] Belum ada riwayat pengiriman.\n";
        return;
    }
    NodeRiwayat* temp = headRiwayat;
    int no = 1;
    while (temp != NULL) {
        cout << "  " << no++ << ". ID: " << temp->idPaket
             << " | Pengirim: " << temp->pengirim
             << " | Penerima: " << temp->penerima
             << " | Tujuan: "   << temp->tujuan << "\n";
        temp = temp->next;
    }
}

void simpanSatuKeCSV(string id, string pengirim, string penerima, string tujuan) {
    ofstream file(FILE_CSV, ios::app);
    if (file.is_open()) {
        file << id << "," << pengirim << "," << penerima << "," << tujuan << "\n";
        file.close();
    } else {
        cout << "  [!] Gagal menyimpan ke file CSV.\n";
    }
}

void muatDariCSV() {
    ifstream file(FILE_CSV);
    if (!file.is_open()) {
        return;
    }

    string baris;
    int jumlah = 0;
    while (getline(file, baris)) {
        if (baris.empty()) continue;

        stringstream ss(baris);
        string id, pengirim, penerima, tujuan;

        getline(ss, id,       ',');
        getline(ss, pengirim, ',');
        getline(ss, penerima, ',');
        getline(ss, tujuan,   ',');

        tambahRiwayat(id, pengirim, penerima, tujuan);
        jumlah++;
    }
    file.close();

    if (jumlah > 0) {
        cout << "  [CSV] " << jumlah << " riwayat dimuat dari " << FILE_CSV << "\n";
    }
}

struct NodeStack {
    string idPaket;
    string pengirim;
    string penerima;
    string tujuan;
    NodeStack* next;
};

NodeStack* topStack = NULL;
int ukuranStack = 0;

void pushPaket(string id, string pengirim, string penerima, string tujuan) {
    NodeStack* baru = new NodeStack();
    baru->idPaket   = id;
    baru->pengirim  = pengirim;
    baru->penerima  = penerima;
    baru->tujuan    = tujuan;
    baru->next      = topStack;
    topStack        = baru;
    ukuranStack++;
    cout << "  [OK] Paket '" << id << "' berhasil diinput.\n";
}

void undoPaket() {
    if (topStack == NULL) {
        cout << "  [!] Stack kosong, tidak ada paket yang bisa dibatalkan.\n";
        return;
    }
    NodeStack* hapus = topStack;
    cout << "  [UNDO] Paket '" << hapus->idPaket << "' dibatalkan.\n";
    topStack = topStack->next;
    delete hapus;
    ukuranStack--;
}

void kirimSemuaPaket() {
    if (topStack == NULL) {
        cout << "  [!] Tidak ada paket di antrian.\n";
        return;
    }
    cout << "  [KIRIM] Memproses semua paket...\n";
    while (topStack != NULL) {
        NodeStack* temp = topStack;
        tambahRiwayat(temp->idPaket, temp->pengirim, temp->penerima, temp->tujuan);
        simpanSatuKeCSV(temp->idPaket, temp->pengirim, temp->penerima, temp->tujuan);
        cout << "  >> Paket '" << temp->idPaket << "' dikirim ke " << temp->tujuan << "\n";
        topStack = topStack->next;
        delete temp;
        ukuranStack--;
    }
    cout << "  [OK] Semua paket berhasil dikirim dan dicatat ke riwayat.\n";
}

void tampilStack() {
    if (topStack == NULL) {
        cout << "  [!] Tidak ada paket dalam antrian input.\n";
        return;
    }
    NodeStack* temp = topStack;
    int no = 1;
    cout << "  (Teratas = input terakhir)\n";
    while (temp != NULL) {
        cout << "  " << no++ << ". ID: " << temp->idPaket
             << " | " << temp->pengirim << " -> " << temp->penerima
             << " (" << temp->tujuan << ")\n";
        temp = temp->next;
    }
}

bool adjMatrix[MAX_KOTA][MAX_KOTA] = {false};

void inisialisasiGraph() {
    int koneksi[][2] = {
        {0,5}, {0,3}, {0,6},
        {1,3}, {1,4}, {1,2}, {1,7},
        {2,4}, {2,6},
        {3,7}, {3,4},
        {4,5},
        {5,6}
    };

    int total = sizeof(koneksi) / sizeof(koneksi[0]);
    for (int i = 0; i < total; i++) {
        int a = koneksi[i][0];
        int b = koneksi[i][1];
        adjMatrix[a][b] = true;
        adjMatrix[b][a] = true;
    }
}

int cariIndexKota(string nama) {
    for (int i = 0; i < MAX_KOTA; i++) {
        if (namaKota[i] == nama) return i;
    }
    return -1;
}

void tampilDaftarKota() {
    cout << "  Daftar kota yang tersedia:\n";
    for (int i = 0; i < MAX_KOTA; i++) {
        cout << "  [" << i << "] " << namaKota[i] << "\n";
    }
}

void bfsRuteTerpendek(int asal, int tujuan) {
    if (asal == tujuan) {
        cout << "  [!] Kota asal dan tujuan sama.\n";
        return;
    }

    bool dikunjungi[MAX_KOTA] = {false};
    int  parent[MAX_KOTA];
    for (int i = 0; i < MAX_KOTA; i++) parent[i] = -1;

    queue<int> q;
    q.push(asal);
    dikunjungi[asal] = true;

    bool ketemu = false;

    while (!q.empty()) {
        int kini = q.front();
        q.pop();

        if (kini == tujuan) {
            ketemu = true;
            break;
        }

        for (int j = 0; j < MAX_KOTA; j++) {
            if (adjMatrix[kini][j] && !dikunjungi[j]) {
                dikunjungi[j] = true;
                parent[j]     = kini;
                q.push(j);
            }
        }
    }

    if (!ketemu) {
        cout << "  [!] Tidak ada rute dari "
             << namaKota[asal] << " ke " << namaKota[tujuan] << ".\n";
        return;
    }

    int jalur[MAX_KOTA];
    int panjang = 0;
    int kini = tujuan;
    while (kini != -1) {
        jalur[panjang++] = kini;
        kini = parent[kini];
    }

    cout << "  Rute terpendek (" << panjang - 1 << " langkah):\n  ";
    for (int i = panjang - 1; i >= 0; i--) {
        cout << namaKota[jalur[i]];
        if (i > 0) cout << " -> ";
    }
    cout << "\n";
}

void tampilGraphKoneksi() {
    cout << "  Koneksi antar kota:\n";
    for (int i = 0; i < MAX_KOTA; i++) {
        cout << "  " << namaKota[i] << " terhubung ke: ";
        bool ada = false;
        for (int j = 0; j < MAX_KOTA; j++) {
            if (adjMatrix[i][j]) {
                if (ada) cout << ", ";
                cout << namaKota[j];
                ada = true;
            }
        }
        if (!ada) cout << "(tidak ada koneksi)";
        cout << "\n";
    }
}

void menuLinkedList() {
    int pilihan = -1;
    while (pilihan != 0) {
        cout << "\n====== MENU RIWAYAT PENGIRIMAN (Linked List) ======\n";
        cout << "  1. Tampilkan riwayat semua paket\n";
        cout << "  0. Kembali ke menu utama\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        pilihan = inputAngka();

        if (pilihan == 1) {
            cout << "\n-- Riwayat Paket Terkirim --\n";
            tampilRiwayat();
        }
        else if (pilihan != 0) {
            cout << "  [!] Pilihan tidak valid. Masukkan 0 atau 1.\n";
        }
    }
}

void menuStack() {
    int pilihan = -1;
    while (pilihan != 0) {
        cout << "\n====== MENU INPUT PAKET (Stack) ======\n";
        cout << "  1. Input paket baru\n";
        cout << "  2. Tampilkan antrian paket\n";
        cout << "  3. Undo (batalkan paket terakhir)\n";
        cout << "  4. Kirim semua paket\n";
        cout << "  0. Kembali ke menu utama\n";
        cout << "Pilihan: ";
        pilihan = inputAngka();

        if (pilihan == 1) {
            string id, pengirim, penerima, tujuan;
                        while (id.empty()) {
                cout << "  ID Paket   : ";
                getline(cin, id);
                if (id.empty()) cout << "  [!] ID Paket tidak boleh kosong.\n";
            }
            while (pengirim.empty()) {
                cout << "  Pengirim   : ";
                getline(cin, pengirim);
                if (pengirim.empty()) cout << "  [!] Nama pengirim tidak boleh kosong.\n";
            }
            while (penerima.empty()) {
                cout << "  Penerima   : ";
                getline(cin, penerima);
                if (penerima.empty()) cout << "  [!] Nama penerima tidak boleh kosong.\n";
            }
 
            bool kotaValid = false;
            while (!kotaValid) {
                cout << "  Kota Tujuan (";
                for (int i = 0; i < MAX_KOTA; i++) {
                    cout << namaKota[i];
                    if (i < MAX_KOTA - 1) cout << "/";
                }
                cout << "): ";
                getline(cin, tujuan);
 
                for (int i = 0; i < MAX_KOTA; i++) {
                    if (tujuan == namaKota[i]) {
                        kotaValid = true;
                        break;
                    }
                }
                if (!kotaValid) cout << "  [!] Kota tidak ditemukan. Masukkan nama kota yang sesuai daftar.\n";
            }
            pushPaket(id, pengirim, penerima, tujuan);
        } else if (pilihan == 2) {
        cout << "\n-- Antrian Paket (Stack) --\n";
        tampilStack();
        } else if (pilihan == 3) {
        undoPaket();
        } else if (pilihan == 4) {
         kirimSemuaPaket();
        } else if (pilihan != 0) {
        cout << "  [!] Pilihan tidak valid. Masukkan angka 0-4.\n";
        }
    }

}

void menuGraph() {
    int pilihan = -1;
    while (pilihan != 0) {
        cout << "\n====== MENU RUTE PENGIRIMAN (Graph + BFS) ======\n";
        cout << "  1. Cari rute terpendek antar kota\n";
        cout << "  2. Tampilkan semua koneksi kota\n";
        cout << "  0. Kembali ke menu utama\n";
        cout << "Pilihan: ";
        pilihan = inputAngka();

        if (pilihan == 1) {
            tampilDaftarKota();
            int asal = -1;
            while (asal < 0 || asal >= MAX_KOTA) {
                cout << "  Pilih nomor kota ASAL   : ";
                asal = inputAngka();
                if (asal < 0 || asal >= MAX_KOTA)
                    cout << "  [!] Nomor tidak valid. Masukkan angka 0-" << MAX_KOTA - 1 << ".\n";
            }
 
            int tujuan = -1;
            while (tujuan < 0 || tujuan >= MAX_KOTA) {
                cout << "  Pilih nomor kota TUJUAN : ";
                tujuan = inputAngka();
                if (tujuan < 0 || tujuan >= MAX_KOTA)
                    cout << "  [!] Nomor tidak valid. Masukkan angka 0-" << MAX_KOTA - 1 << ".\n";
            }

                        cout << "\n";
            bfsRuteTerpendek(asal, tujuan);
        } else if (pilihan == 2) {
            cout << "\n-- Peta Koneksi Kota --\n";
            tampilGraphKoneksi();
        } else if (pilihan != 0) {
            cout << "  [!] Pilihan tidak valid. Masukkan 0, 1, atau 2.\n";
        }

    }
}

int main() {
    inisialisasiGraph();
    muatDariCSV();

    int pilihan;
    do {
        cout << "\n========================================\n";
        cout << "   SISTEM MANAJEMEN KURIR - RPL UPI\n";
        cout << "========================================\n";
        cout << "  1. Input & Kelola Paket  (Stack)\n";
        cout << "  2. Riwayat Pengiriman    (Linked List)\n";
        cout << "  3. Cari Rute Pengiriman  (Graph + BFS)\n";
        cout << "  0. Keluar\n";
        cout << "Pilihan: ";
        pilihan = inputAngka();

        if      (pilihan == 1) menuStack();
        else if (pilihan == 2) menuLinkedList();
        else if (pilihan == 3) menuGraph();
        else if (pilihan != 0) cout << "  [!] Pilihan tidak valid.\n";

    } while (pilihan != 0);

    cout << "\n  Terima kasih telah menggunakan Sistem Coolrir!\n";
    return 0;
}