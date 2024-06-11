#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
using namespace std;

struct Transaksi {
    string jenisTransaksi;
    int nomorAkun;
    double jumlah;
    time_t waktuTransaksi;

    Transaksi(string jenisTransaksi, int nomorAkun, double jumlah) {
        this->jenisTransaksi = jenisTransaksi;
        this->nomorAkun = nomorAkun;
        this->jumlah = jumlah;
        this->waktuTransaksi = time(nullptr);
    }
};
