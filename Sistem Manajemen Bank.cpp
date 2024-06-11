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

 void tarik(double jumlah) {
        if (jumlah > saldo) {
            cout << "Saldo tidak mencukupi. Permintaan penarikan ditolak." << endl;
        } else {
            saldo -= jumlah;
            cout << "Berhasil menarik " << jumlah << " dari akun " << nomorAkun << endl;
            catatTransaksi("Tarik", -jumlah);
        }
    }

    void cekSaldo() const {
        cout << "Saldo akun " << nomorAkun << ": " << saldo << endl;
    }

    void transfer(Akun& tujuan, double jumlah) {
        if (jumlah > saldo) {
            cout << "Saldo tidak mencukupi untuk transfer." << endl;
        } else {
            tarik(jumlah);
            tujuan.deposit(jumlah);
            cout << "Transfer berhasil." << endl;
            catatTransaksi("Transfer keluar", -jumlah);
            tujuan.catatTransaksi("Transfer masuk", jumlah);
        }
    }

    int getNomorAkun() const {
        return nomorAkun;
    }

    string getNama() const {
        return nama;
    }

    double getSaldo() const {
        return saldo;
    }

    void catatTransaksi(string jenisTransaksi, double jumlah) {
        Transaksi transaksi(jenisTransaksi, nomorAkun, jumlah);
        riwayatTransaksi.push_back(transaksi);
    }

    void tampilkanRiwayatTransaksi() const {
        cout << "\nRiwayat Transaksi untuk Akun " << nomorAkun << " (" << nama << "):\n";
        cout << setw(15) << "Waktu" << setw(20) << "Jenis Transaksi" << setw(15) << "Nomor Akun" << setw(15) << "Jumlah" << endl;
        for (const Transaksi& transaksi : riwayatTransaksi) {
            char waktu[100];
            strftime(waktu, sizeof(waktu), "%Y-%m-%d %H:%M:%S", localtime(&transaksi.waktuTransaksi));

            cout << setw(15) << waktu << setw(20) << transaksi.jenisTransaksi << setw(15) << transaksi.nomorAkun << setw(15) << transaksi.jumlah << endl;
        }
    }

    string getNamaPengguna() const {
        return namaPengguna;
    }

    // Getter untuk kata sandi
    string getKataSandi() const {
        return kataSandi;
    }
};

vector<Akun> daftarAkun;

void buatAkun() {
    int nomorAkun;
    string nama, namaPengguna, kataSandi;
    double saldo;

    cout << "Masukkan nomor akun: ";
    cin >> nomorAkun;

    for (const Akun& akun : daftarAkun) {
        if (akun.getNomorAkun() == nomorAkun) {
            cout << "Nomor akun sudah ada. Masukkan nomor akun lain." << endl;
            return;
        }
    }

    cout << "Masukkan nama: ";
    cin.ignore();
    getline(cin, nama);

    cout << "Masukkan nama pengguna: ";
    cin >> namaPengguna;

    cout << "Masukkan kata sandi: ";
    cin >> kataSandi;

    cout << "Masukkan saldo awal: ";
    cin >> saldo;

    Akun akun(nomorAkun, nama, saldo, namaPengguna, kataSandi);
    daftarAkun.push_back(akun);

    cout << "Akun berhasil dibuat!" << endl;
}
