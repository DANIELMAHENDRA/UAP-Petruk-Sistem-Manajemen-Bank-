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

class Akun {
private:
    int nomorAkun;
    string nama;
    double saldo;
    string namaPengguna;
    string kataSandi;
    vector<Transaksi> riwayatTransaksi;
public:
    Akun() {
        nomorAkun = 0;
        nama = "";
        saldo = 0.0;
        namaPengguna = "";
        kataSandi = "";
    }
    Akun(int nomorAkun, string nama, double saldo, string namaPengguna, string kataSandi) {
        this->nomorAkun = nomorAkun;
        this->nama = nama;
        this->saldo = saldo;
        this->namaPengguna = namaPengguna;
        this->kataSandi = kataSandi;
    }
    void deposit(double jumlah) {
        saldo += jumlah;
        cout << "Berhasil menambahkan " << jumlah << " ke akun " << nomorAkun << endl;
        catatTransaksi("Setor", jumlah);
    }
