#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <limits>
#include <fstream>
#include <sstream>
#include <unordered_set>

using namespace std;

enum Kategori {
    BIASA,
    TWIN,
    DELUXE,
    LUXURY,
    VIP
};

string kategoriToString(Kategori kategori) {
    switch (kategori) {
        case BIASA: return "Biasa";
        case TWIN: return "Twin";
        case DELUXE: return "Deluxe";
        case LUXURY: return "Luxury";
        case VIP: return "VIP";
        default: return "Unknown";
    }
}

int hargaKategori(Kategori kategori) {
    switch (kategori) {
        case BIASA: return 500000;
        case TWIN: return 700000;
        case DELUXE: return 900000;
        case LUXURY: return 1200000;
        case VIP: return 1500000;
        default: return 0;
    }
}

class Kamar {
public:
    int nomor;
    bool tersedia;
    string namaPemesan;
    Kategori kategori;

    Kamar(int nomor, Kategori kategori) : nomor(nomor), tersedia(true), namaPemesan(""), kategori(kategori) {}
};

class Hotel {
public:
    vector<Kamar> kamar;

    Hotel() {
        int nomor = 1;
        for (int i = 0; i < 5; ++i) {
            kamar.push_back(Kamar(nomor++, VIP));
            kamar.push_back(Kamar(nomor++, LUXURY));
            kamar.push_back(Kamar(nomor++, DELUXE));
            kamar.push_back(Kamar(nomor++, TWIN));
            kamar.push_back(Kamar(nomor++, BIASA));
        }
    }

    void tampilkanKamar() {
        cout << "Daftar Kamar:\n";
        for (const auto& k : kamar) {
            cout << "Kamar " << k.nomor << " - " << kategoriToString(k.kategori) << " - Rp " << hargaKategori(k.kategori) << " - " << (k.tersedia ? "Tersedia" : "Tidak Tersedia") << endl;
        }
    }

    void tampilkanKamarTersedia() {
        cout << "Daftar Kamar Tersedia:\n";
        for (const auto& k : kamar) {
            if (k.tersedia) {
                cout << "Kamar " << k.nomor << " - " << kategoriToString(k.kategori) << " - Rp " << hargaKategori(k.kategori) << " - Tersedia\n";
            }
        }
    }

    void tampilkanKamarBerdasarkanKategori(Hotel& hotel, Kategori kategori, int hargaMin, int hargaMax) {
        cout << "Daftar Kamar " << kategoriToString(kategori) << " (Harga antara Rp " << hargaMin << " - Rp " << hargaMax << "):\n";
        for (const auto& k : hotel.kamar) {
            if (k.kategori == kategori && hargaKategori(k.kategori) >= hargaMin && hargaKategori(k.kategori) <= hargaMax) {
                cout << "Kamar " << k.nomor << " - Rp " << hargaKategori(k.kategori) << " - " << (k.tersedia ? "Tersedia" : "Telah Dipesan") << endl;
            }
        }
    }

    void pesanKamar(int nomorKamar, const string& namaPemesan) {
        if (nomorKamar < 1 || nomorKamar > kamar.size()) {
            cout << "Nomor kamar tidak valid.\n";
            return;
        }

        if (kamar[nomorKamar - 1].tersedia) {
            kamar[nomorKamar - 1].tersedia = false;
            kamar[nomorKamar - 1].namaPemesan = namaPemesan;
            cout << "Kamar " << nomorKamar << " berhasil dipesan oleh " << namaPemesan << ".\n";
        } else {
            cout << "Kamar " << nomorKamar << " sudah dipesan.\n";
        }
    }

    void batalPesanKamar(int nomorKamar) {
        if (nomorKamar < 1 || nomorKamar > kamar.size()) {
            cout << "Nomor kamar tidak valid.\n";
            return;
        }

        if (!kamar[nomorKamar - 1].tersedia) {
            kamar[nomorKamar - 1].tersedia = true;
            kamar[nomorKamar - 1].namaPemesan = "";
            cout << "Pesanan kamar " << nomorKamar << " telah dibatalkan.\n";
        } 
        // else {
        //     cout << "Kamar " << nomorKamar << " belum dipesan.\n";
        // }
    }
};

bool isNumeric(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

struct Pesanan {
    string username;
    string nama;
    string ktp;
    string no_hp;
    int no_kamar;
    string tanggal;
};

vector<Pesanan> daftar_pesanan;

class SistemPemesanan {
private:
    string adminUsername = "admin";
    string adminPassword = "admin123";
    unordered_map<string, pair<string, string>> pelanggan;
    string pelangganFile = "pelanggan.csv";
    string namaPelanggan;

public:
    bool isAdminLoggedIn = false;
    string loggedInPelanggan;

    void bacaPelangganDariCSV() {
        ifstream file("pelanggan.csv");
        if (!file.is_open()) {
            cout << "File tidak dapat dibuka.\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string username, password, nama;
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, nama);
            pelanggan[username] = make_pair(password, nama);
        }
        file.close();
    }

    void simpanPelangganKeCSV() {
        ofstream file("pelanggan.csv");
        if (!file.is_open()) {
            cout << "File tidak dapat dibuka.\n";
            return;
        }

        for (const auto& entry : pelanggan) {
            file << entry.first << "," << entry.second.first << "," << entry.second.second << "\n";
        }
        file.close();
    }

    void registrasiPelanggan(const string& username, const string& password, const string& nama) {
        if (pelanggan.find(username) != pelanggan.end()) {
            cout << "Username sudah terdaftar. Silakan pilih username lain.\n";
            return;
        }
        pelanggan[username] = make_pair(password, nama);
        simpanPelangganKeCSV();
        cout << "Registrasi berhasil. Silakan login untuk memesan kamar.\n";
    }

    bool loginAdmin(const string& username, const string& password) {
        if (username == adminUsername && password == adminPassword) {
            isAdminLoggedIn = true;
            return true;
        }
        cout << "Username atau password admin salah.\n";
        return false;
    }

    bool loginPelanggan(const string& username, const string& password) {
        if (pelanggan.find(username) != pelanggan.end() && pelanggan[username].first == password) {
            loggedInPelanggan = username;
            namaPelanggan = pelanggan[username].second;
            cout << "Login berhasil. Selamat datang, " << namaPelanggan << ".\n";
            return true;
        }
        cout << "Username atau password pelanggan salah.\n";
        return false;
    }

    void logout() {
        isAdminLoggedIn = false;
        loggedInPelanggan = "";
        cout << "Logout berhasil.\n";
    }

    bool isAdmin() {
        return isAdminLoggedIn;
    }

    bool isPelanggan() {
        return !isAdminLoggedIn && !loggedInPelanggan.empty();
    }

    string getLoggedInPelanggan() {
        return loggedInPelanggan;
    }

    string getNamaPelanggan() {
        return namaPelanggan;
    }
};

void simpanPesananKeCSV() {
    ofstream file("pesanan.csv");
    if (!file.is_open()) {
        cout << "File tidak dapat dibuka.\n";
        return;
    }

    for (const auto& pesanan : daftar_pesanan) {
        file << pesanan.username << "," << pesanan.nama << "," << pesanan.ktp << "," << pesanan.no_hp << "," << pesanan.no_kamar << "," << pesanan.tanggal << "\n";
    }
    file.close();
}

void bacaKamarDariCSV(Hotel& hotel) {
    ifstream file("kamar.csv");
    if (!file.is_open()) {
        // cout << "File tidak dapat dibuka.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int nomor, kategori;
        bool isTersedia;
        char comma;
        if (!(ss >> nomor >> comma >> kategori >> comma >> isTersedia)) {
            cout << "Format file salah.\n";
            return;
        }
        hotel.kamar.push_back(Kamar(nomor, static_cast<Kategori>(kategori)));
        hotel.kamar.back().tersedia = isTersedia;
    }
    file.close();
}

void bacaPesananDariCSV() {
    ifstream file("pesanan.csv");
    if (!file.is_open()) {
        cout << "File tidak dapat dibuka.\n";
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Pesanan pesanan;
        getline(ss, pesanan.username, ',');
        getline(ss, pesanan.nama, ',');
        getline(ss, pesanan.ktp, ',');
        getline(ss, pesanan.no_hp, ',');
        string no_kamar_str;
        getline(ss, no_kamar_str, ',');
        pesanan.no_kamar = stoi(no_kamar_str);
        getline(ss, pesanan.tanggal);
        daftar_pesanan.push_back(pesanan);
    }
    file.close();
}

void tambahPesanan(Hotel& hotel, SistemPemesanan& sistem) {
    hotel.tampilkanKamarTersedia();
    Pesanan pesanan;
    cout << "Silahkan isi Form Pemesanan Kamar\n";
    pesanan.username = sistem.getLoggedInPelanggan();
    pesanan.nama = sistem.getNamaPelanggan();
    cout << "Nama: " << pesanan.nama << endl;
    cout << "KTP: ";
    cin.ignore();
    getline(cin, pesanan.ktp);
    cout << "No HP: ";
    getline(cin, pesanan.no_hp);

    string inputNoKamar;
    do {
        cout << "Nomor Kamar: ";
        getline(cin, inputNoKamar);
        if (!isNumeric(inputNoKamar)) {
            cout << "Nomor Kamar harus berupa angka. Silakan coba lagi.\n";
        }
    } while (!isNumeric(inputNoKamar));
    pesanan.no_kamar = stoi(inputNoKamar);

    cout << "Tanggal (YYYY-MM-DD): ";
    getline(cin, pesanan.tanggal);

    hotel.pesanKamar(pesanan.no_kamar, pesanan.nama);
    daftar_pesanan.push_back(pesanan);
    simpanPesananKeCSV();
}

void tampilkanPesanan() {
    cout << "Daftar Pesanan Kamar:\n";
    for (const auto& pesanan : daftar_pesanan) {
        cout << "Nama: " << pesanan.nama << ", KTP: " << pesanan.ktp << ", No HP: " << pesanan.no_hp << ", No Kamar: " << pesanan.no_kamar << ", Tanggal: " << pesanan.tanggal << endl;
    }
}


void tampilkanPesananUser(const string& loggedInUsername) {
    cout << "Daftar Pesanan Kamar:\n";
    for (const auto& pesanan : daftar_pesanan) {
        if (pesanan.username == loggedInUsername) {
            cout << "Nama: " << pesanan.nama << ", KTP: " << pesanan.ktp << ", No HP: " << pesanan.no_hp << ", No Kamar: " << pesanan.no_kamar << ", Tanggal: " << pesanan.tanggal << endl;
        }
    }
}

void batalPesanKamar(Hotel& hotel, SistemPemesanan& sistem) {
    string inputNoKamar;
    do {
        cout << "Nomor Kamar yang ingin dibatalkan: ";
        cin >> inputNoKamar;
        if (!isNumeric(inputNoKamar)) {
            cout << "Nomor Kamar harus berupa angka. Silakan coba lagi.\n";
        }
    } while (!isNumeric(inputNoKamar));

    int nomorKamar = stoi(inputNoKamar);

    bool found = false;
    for (auto it = daftar_pesanan.begin(); it != daftar_pesanan.end(); ++it) {
        if (it->no_kamar == nomorKamar && it->username == sistem.getLoggedInPelanggan()) {
            found = true;
            daftar_pesanan.erase(it);
            hotel.batalPesanKamar(nomorKamar);
            simpanPesananKeCSV();
            cout << "Pesanan untuk kamar " << nomorKamar << " telah dibatalkan.\n";
            break;
        }
    }

    if (!found) {
        cout << "Pesanan tidak ditemukan atau Anda tidak memiliki hak untuk membatalkan pesanan ini.\n";
    }
}

void hapusPesanan(Hotel& hotel) {
    string inputNoKamar;
    do {
        cout << "Nomor Kamar yang ingin dihapus pesanan: ";
        cin >> inputNoKamar;
        if (!isNumeric(inputNoKamar)) {
            cout << "Nomor Kamar harus berupa angka. Silakan coba lagi.\n";
        }
    } while (!isNumeric(inputNoKamar));

    int nomorKamar = stoi(inputNoKamar);

    bool found = false;
    for (auto it = daftar_pesanan.begin(); it != daftar_pesanan.end(); ++it) {
        if (it->no_kamar == nomorKamar) {
            found = true;
            daftar_pesanan.erase(it);
            hotel.batalPesanKamar(nomorKamar);
            simpanPesananKeCSV();
            cout << "Pesanan untuk kamar " << nomorKamar << " telah dihapus.\n";
            break;
        }
    }

    if (!found) {
        cout << "Pesanan tidak ditemukan.\n";
    }
}

void menuAdmin(SistemPemesanan& sistem, Hotel& hotel) {
    int pilihan;
    do {
        cout << "\nMenu Admin\n";
        cout << "1. Tampilkan Kamar\n";
        cout << "2. Tampilkan Pesanan\n";
        cout << "3. Hapus Pesanan\n";
        cout << "4. Logout\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilihan) {
            case 1:
                hotel.tampilkanKamar();
                break;
            case 2:
                tampilkanPesanan();
                break;
            case 3:
                cout << "Daftar Pesanan Sebelum Penghapusan:\n";
                tampilkanPesanan();
                hapusPesanan(hotel);
                break;
            case 4:
                sistem.logout();
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (sistem.isAdmin());
}

void menuPelanggan(SistemPemesanan& sistem, Hotel& hotel) {
    int pilihan;
    do {
        cout << "\nMenu Pelanggan\n";
        cout << "1. Tampilkan Kamar\n";
        cout << "2. Tampilkan Kamar Berdasarkan Kategori\n";
        cout << "3. Cari Kamar Berdasarkan Harga\n";
        cout << "4. Pesan Kamar\n";
        cout << "5. Tampilkan Pesanan\n";
        cout << "6. Batalkan Pesanan\n";
        cout << "7. Logout\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilihan) {
            case 1:
                hotel.tampilkanKamar();
                break;
            case 2: {
                int kategori;
                cout << "Pilih kategori kamar:\n";
                cout << "1. Biasa\n";
                cout << "2. Twin\n";
                cout << "3. Deluxe\n";
                cout << "4. Luxury\n";
                cout << "5. VIP\n";
                cout << "Pilihan: ";
                cin >> kategori;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                hotel.tampilkanKamarBerdasarkanKategori(hotel, static_cast<Kategori>(kategori), 0, numeric_limits<int>::max());
                break;
            }
            case 3: {
                int hargaMin, hargaMax;
                cout << "Masukkan range harga (harga minimum dan maksimum):\n";
                cout << "Harga Minimum: ";
                cin >> hargaMin;
                cout << "Harga Maksimum: ";
                cin >> hargaMax;
                cout << "Daftar Kamar dengan Harga antara Rp " << hargaMin << " dan Rp " << hargaMax << ":\n";
                for (Kategori kategori = BIASA; kategori <= VIP; kategori = static_cast<Kategori>(kategori + 1)) {
                    hotel.tampilkanKamarBerdasarkanKategori(hotel, kategori, hargaMin, hargaMax);
                }
                break;
            }
            case 4:
                tambahPesanan(hotel, sistem);
                break;
            case 5:
                tampilkanPesananUser(sistem.getLoggedInPelanggan());
                break;
            case 6:
                batalPesanKamar(hotel, sistem);
                break;
            case 7:
                sistem.logout();
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (sistem.isPelanggan());
}

void menuUtama(SistemPemesanan& sistem, Hotel& hotel) {
    int pilihan;
    do {
        cout << "\nMenu Utama\n";
        cout << "1. Login Admin\n";
        cout << "2. Login Pelanggan\n";
        cout << "3. Registrasi Pelanggan\n";
        cout << "4. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string username, password, nama;
        switch (pilihan) {
            case 1:
                cout << "Username: ";
                getline(cin, username);
                cout << "Password: ";
                getline(cin, password);
                if (sistem.loginAdmin(username, password)) {
                    menuAdmin(sistem, hotel);
                }
                break;
            case 2:
                cout << "Username: ";
                getline(cin, username);
                cout << "Password: ";
                getline(cin, password);
                if (sistem.loginPelanggan(username, password)) {
                    menuPelanggan(sistem, hotel);
                }
                break;
            case 3:
                cout << "Nama: ";
                getline(cin, nama);
                cout << "Username: ";
                getline(cin, username);
                cout << "Password: ";
                getline(cin, password);
                sistem.registrasiPelanggan(username, password, nama);
                break;
            case 4:
                cout << "Terima kasih telah menggunakan sistem pemesanan kami.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 4);
}

int main() {
    SistemPemesanan sistem;
    sistem.bacaPelangganDariCSV();
    bacaPesananDariCSV();
    Hotel hotel;
    bacaKamarDariCSV(hotel);
    menuUtama(sistem, hotel);
    return 0;
}
