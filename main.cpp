#include <iostream>
#include <string>
#include <queue>
using namespace std;

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

// Menghubungkan Stack milik Orang 1 ke Linked List
void kirimSemuaPaket(NodeStack* &topStack, int &ukuranStack) {
    if (topStack == NULL) {
        cout << "  [!] Tidak ada paket di antrian.\n";
        return;
    }
    cout << "  [KIRIM] Memproses semua paket...\n";
    while (topStack != NULL) {
        NodeStack* temp = topStack;
        tambahRiwayat(temp->idPaket, temp->pengirim, temp->penerima, temp->tujuan);
        cout << "  >> Paket '" << temp->idPaket << "' dikirim ke " << temp->tujuan << "\n";
        topStack = topStack->next;
        delete temp;
        ukuranStack--;
    }
    cout << "  [OK] Semua paket berhasil dikirim dan dicatat ke riwayat.\n";
}

void menuLinkedList() {
    int pilihan = -1;
    while (pilihan != 0) {
        cout << "\n====== MENU RIWAYAT PENGIRIMAN (Linked List) ======\n";
        cout << "  1. Tampilkan riwayat semua paket\n";
        cout << "  0. Kembali ke menu utama\n";
        cout << "Pilihan: "; cin >> pilihan; cin.ignore();

        if (pilihan == 1) {
            tampilRiwayat();
        }
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

    // Rekonstruksi jalur dari tujuan balik ke asal
    int jalur[MAX_KOTA];
    int panjang = 0;
    int kini = tujuan;
    while (kini != -1) {
        jalur[panjang++] = kini;
        kini = parent[kini];
    }

    // Tampilkan dari asal ke tujuan (balik array)
    cout << "  Rute terpendek (" << panjang - 1 << " langkah):\n  ";
    for (int i = panjang - 1; i >= 0; i--) {
        cout << namaKota[jalur[i]];
        if (i > 0) cout << " -> ";
    }
    cout << "\n";
}

#include <iostream>
using namespace std;

// ============================================================
//  CODE ORANG 5: MAIN & SYSTEM INTEGRATION
// ============================================================
int main() {
    // 1. Inisialisasi peta awal kurir (Punya Orang 3)
    inisialisasiGraph();

    // 2. Load Dummy Data awal ke dalam Riwayat (Punya Orang 2)
    // Berfungsi agar saat demo program didepan dosen tidak kosong melompong.
    tambahRiwayat("PKT001", "Andi",  "Budi",  "Jakarta");
    tambahRiwayat("PKT002", "Citra", "Dani",  "Bogor");
    tambahRiwayat("PKT003", "Eka",   "Fandi", "Bekasi");

    int pilihan;
    do {
        cout << "\n========================================\n";
        cout << "   SISTEM MANAJEMEN KURIR - RPL UPI\n";
        cout << "========================================\n";
        cout << "  1. Input & Kelola Paket  (Stack)\n";
        cout << "  2. Riwayat Pengiriman    (Linked List)\n";
        cout << "  3. Cari Rute Pengiriman  (Graph + BFS)\n";
        cout << "  4. Kirim Semua Paket Di Antrian\n"; // Menu tambahan integrasi
        cout << "  0. Keluar\n";
        cout << "Pilihan: "; cin >> pilihan; cin.ignore();

        if      (pilihan == 1) menuStack();        // Punya Orang 1
        else if (pilihan == 2) menuLinkedList();   // Punya Orang 2
        else if (pilihan == 3) menuGraph();        // Punya Orang 4
        else if (pilihan == 4) kirimSemuaPaket(topStack, ukuranStack); // Integrasi Orang 1 & 2
        else if (pilihan != 0) cout << "  [!] Pilihan tidak valid.\n";

    } while (pilihan != 0);

    cout << "\n  Terima kasih telah menggunakan Sistem Kurir!\n";
    return 0;
}

