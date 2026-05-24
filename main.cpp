#include <iostream>
#include <string>
#include <queue>
using namespace std;

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