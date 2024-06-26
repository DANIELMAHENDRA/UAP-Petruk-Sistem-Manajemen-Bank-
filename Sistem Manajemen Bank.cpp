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

bool login() {
    string namaPengguna, kataSandi;

    cout << "Masukkan nama pengguna: ";
    cin >> namaPengguna;

    cout << "Masukkan kata sandi: ";
    cin >> kataSandi;

    for (const Akun& akun : daftarAkun) {
        if (akun.getNamaPengguna() == namaPengguna && akun.getKataSandi() == kataSandi) {
            cout << "Login berhasil." << endl;
            return true;
        }
    }

    cout << "Nama pengguna atau kata sandi salah. Login gagal." << endl;
    return false;
}

void setorUang() {
    int nomorAkun;
    double jumlah;

    cout << "Masukkan nomor akun: ";
    cin >> nomorAkun;

    cout << "Masukkan jumlah yang akan disetor: ";
    cin >> jumlah;

    for (Akun& akun : daftarAkun) {
        if (akun.getNomorAkun() == nomorAkun) {
            akun.deposit(jumlah);
            return;
        }
    }

    cout << "Akun tidak ditemukan." << endl;
}

void tarikUang() {
    int nomorAkun;
    double jumlah;

    cout << "Masukkan nomor akun: ";
    cin >> nomorAkun;

    cout << "Masukkan jumlah yang akan ditarik: ";
    cin >> jumlah;

    for (Akun& akun : daftarAkun) {
        if (akun.getNomorAkun() == nomorAkun) {
            akun.tarik(jumlah);
            return;
        }
    }

    cout << "Akun tidak ditemukan." << endl;
}

void cekSaldo() {
    int nomorAkun;

    cout << "Masukkan nomor akun: ";
    cin >> nomorAkun;

    for (const Akun& akun : daftarAkun) {
        if (akun.getNomorAkun() == nomorAkun) {
            akun.cekSaldo();
            return;
        }
    }

    cout << "Akun tidak ditemukan." << endl;
}
void transferUang() {
    int nomorAkunAsal, nomorAkunTujuan;
    double jumlah;

    cout << "Masukkan nomor akun pengirim: ";
    cin >> nomorAkunAsal;

    cout << "Masukkan nomor akun penerima: ";
    cin >> nomorAkunTujuan;

    cout << "Masukkan jumlah yang akan ditransfer: ";
    cin >> jumlah;

    Akun* akunAsal = nullptr;
    Akun* akunTujuan = nullptr;

    for (Akun& akun : daftarAkun) {
        if (akun.getNomorAkun() == nomorAkunAsal) {
            akunAsal = &akun;
        }
        if (akun.getNomorAkun() == nomorAkunTujuan) {
            akunTujuan = &akun;
        }
    }

    if (akunAsal == nullptr || akunTujuan == nullptr) {
        cout << "Salah satu atau kedua akun tidak ditemukan." << endl;
        return;
    }

    akunAsal->transfer(*akunTujuan, jumlah);
}
void tampilkanSemuaAkun() {
    if (daftarAkun.empty()) {
        cout << "Tidak ada akun ditemukan." << endl;
        return;
    }

    cout << "\nDaftar Akun:\n";
    cout << setw(15) << "Nomor Akun" << setw(20) << "Nama" << setw(15) << "Saldo" << endl;
    for (const Akun& akun : daftarAkun) {
        cout << setw(15) << akun.getNomorAkun() << setw(20) << akun.getNama() << setw(15) << akun.getSaldo() << endl;
    }
}

void tampilkanRiwayatTransaksi() {
    int nomorAkun;

    cout << "Masukkan nomor akun: ";
    cin >> nomorAkun;

    for (const Akun& akun : daftarAkun) {
        if (akun.getNomorAkun() == nomorAkun) {
            akun.tampilkanRiwayatTransaksi();
            return;
        }
    }

    cout << "Akun tidak ditemukan." << endl;
}

int main() {
    int pilihan;

    while (true) {
        cout << "\nMenu Utama\n";
        cout << "1. Buat Akun\n";
        cout << "2. Login\n";
        cout << "3. Keluar\n";
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                buatAkun();
                break;
            case 2:
                if (daftarAkun.empty()) {
                    cout << "Belum ada akun yang terdaftar. Silakan buat akun terlebih dahulu." << endl;
                } else {
                    if (login()) {
                        
                        while (true) {
                            cout << "\nSistem Manajemen Bank\n";
                            cout << "1. Setor Uang\n";
                            cout << "2. Tarik Uang\n";
                            cout << "3. Transfer Uang\n";
                            cout << "4. Cek Saldo\n";
                            cout << "5. Tampilkan Semua Akun\n";
                            cout << "6. Tampilkan Riwayat Transaksi\n";
                            cout << "7. Keluar\n";
                            cout << "Masukkan pilihan Anda: ";
                            cin >> pilihan;

switch (pilihan) {
            case 1:
                buatAkun();
                break;
            case 2:
                if (daftarAkun.empty()) {
                    cout << "Belum ada akun yang terdaftar. Silakan buat akun terlebih dahulu." << endl;
                } else {
                    if (login()) {
                        
                        while (true) {
                            cout << "\nSistem Manajemen Bank\n";
                            cout << "1. Setor Uang\n";
                            cout << "2. Tarik Uang\n";
                            cout << "3. Transfer Uang\n";
                            cout << "4. Cek Saldo\n";
                            cout << "5. Tampilkan Semua Akun\n";
                            cout << "6. Tampilkan Riwayat Transaksi\n";
                            cout << "7. Keluar\n";
                            cout << "Masukkan pilihan Anda: ";
                            cin >> pilihan;

                            switch (pilihan) {
                                case 1:
                                    setorUang();
                                    break;
                                case 2:
                                    tarikUang();
                                    break;
                                case 3:
                                    transferUang();
                                    break;
                                case 4:
                                    cekSaldo();
                                    break;
                                case 5:
                                    tampilkanSemuaAkun();
                                    break;
                                case 6:
                                    tampilkanRiwayatTransaksi();
                                    break;
                                case 7:
                                    cout << "Keluar dari sistem..." << endl;
                                    exit(0);
                                default:
                                    cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                            }
                        }
                    }
                }
                break;
            case 3:
                cout << "Keluar dari sistem..." << endl;
                exit(0);
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }

    return 0;
}
