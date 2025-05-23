#include <iostream>
#include <string>
using namespace std;

struct Pesanan {
    string nama;
    string jenisRoti;
    double totalHarga;
};

struct Queue {
    Pesanan info;
    Queue *next;
};

struct NodeRiwayat {
    Pesanan info;
    NodeRiwayat *next;
};

Queue *depan = NULL, *belakang = NULL;
NodeRiwayat *riwayat = NULL; // head untuk riwayat

bool queueKosong() {
    return depan == NULL;
}

void enqueue(Pesanan p) {
    Queue *nb = new Queue;
    nb->info = p;
    nb->next = NULL;

    if (queueKosong()) {
        depan = nb;
    } else {
        belakang->next = nb;
    }
    belakang = nb;
}

void tambahRiwayat(Pesanan p) {
    NodeRiwayat *baru = new NodeRiwayat;
    baru->info = p;
    baru->next = NULL;

    if (riwayat == NULL) {
        riwayat = baru;
    } else {
        NodeRiwayat *temp = riwayat;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = baru;
    }
}

void dequeue() {
    if (queueKosong()) {
        cout << "\nAntrean kosong!\n";
        return;
    }

    Queue *hapus = depan;
    Pesanan p = hapus->info;

    tambahRiwayat(p);

    depan = depan->next;
    delete hapus;

    if (depan == NULL) belakang = NULL;

    cout << "\nPesanan atas nama " << p.nama << " telah dilayani.\n";
}

void tampilAntrean() {
    if (queueKosong()) {
        cout << "\nAntrean kosong.\n";
        return;
    }

    cout << "\nDaftar pesanan dalam antrean:\n";
    Queue *bantu = depan;
    int i = 1;
    while (bantu != NULL) {
        Pesanan p = bantu->info;
        cout << i++ << ". " << p.nama << " - " << p.jenisRoti << " - Rp" << p.totalHarga << endl;
        bantu = bantu->next;
    }
}

void tampilRiwayat() {
    if (riwayat == NULL) {
        cout << "\nBelum ada pesanan yang dilayani.\n";
        return;
    }

    cout << "\nRiwayat pesanan yang telah dilayani:\n";
    NodeRiwayat *temp = riwayat;
    int i = 1;
    while (temp != NULL) {
        Pesanan p = temp->info;
        cout << i++ << ". " << p.nama << " - " << p.jenisRoti << " - Rp" << p.totalHarga << endl;
        temp = temp->next;
    }
}

void batalkanPesananTerakhir() {
    if (queueKosong()) {
        cout << "\nAntrean kosong. Tidak ada yang bisa dibatalkan.\n";
        return;
    }

    if (depan == belakang) {
        cout << "\nPesanan atas nama " << depan->info.nama << " telah dibatalkan.\n";
        delete depan;
        depan = belakang = NULL;
        return;
    }

    Queue *bantu = depan;
    while (bantu->next != belakang) {
        bantu = bantu->next;
    }

    cout << "\nPesanan atas nama " << belakang->info.nama << " telah dibatalkan.\n";
    delete belakang;
    belakang = bantu;
    belakang->next = NULL;
}

void inputPesanan() {
    Pesanan p;
    cin.ignore();
    cout << "Masukkan nama pembeli: ";
    getline(cin, p.nama);
    cout << "Masukkan jenis roti: ";
    getline(cin, p.jenisRoti);
    cout << "Masukkan total harga: ";
    cin >> p.totalHarga;
    enqueue(p);
    cout << "\nPesanan berhasil ditambahkan ke antrean.\n";
}

int main() {
    int pilihan;

    do {
        cout << "\n=====================================\n";
        cout << "Sistem Antrean Toko Roti Manis Lezat\n";
        cout << "=====================================\n";
        cout << "Menu:\n";
        cout << "1. Ambil Antrean\n";
        cout << "2. Layani Pembeli\n";
        cout << "3. Tampilkan Pesanan dalam Antrean\n";
        cout << "4. Batalkan Pesanan Terakhir\n";
        cout << "5. Tampilkan Riwayat Pesanan\n";
        cout << "0. Keluar\n";
        cout << "=====================================\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: inputPesanan(); 
                break;
            case 2: dequeue(); 
                break;
            case 3: tampilAntrean(); 
                break;
            case 4: batalkanPesananTerakhir(); 
                break;
            case 5: tampilRiwayat(); 
                break;
            case 0: 
                cout << "\nTerima kasih telah menggunakan sistem.\n";
                exit(0); 
                break;
            default: cout << "\nPilihan tidak valid.\n";
        }

    } while (pilihan != 0);

    return 0;
}
