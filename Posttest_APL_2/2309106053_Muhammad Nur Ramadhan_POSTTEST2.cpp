#include <iostream>
#include <vector>

using namespace std;

vector<vector<string>> Karyawan;

void Tambahkan_Karyawan() {
    char ulang = 'y';
    while (ulang == 'y') {
        int ID = Karyawan.size() + 1;
        string nama, jabatan, divisi;
        int gaji;
        cout << "Nama: ";
        cin.ignore();
        getline(cin, nama);
        cout << "Jabatan: ";
        getline(cin, jabatan);
        cout << "Divisi: ";
        getline(cin, divisi);
        while (true) {
            cout << "Gaji: ";
            cin >> gaji;
            if (gaji >= 0) {
                vector<string> data = {to_string(ID), nama, jabatan, divisi, to_string(gaji)};
                Karyawan.push_back(data);
                cout << "\nKaryawan baru berhasil ditambahkan." << endl;
                break;
            }
            else {
                cout << "Gaji Harus Berupa Angka Positif dan Dibulatkan." << endl;
            }
        }
        cout << "Ingin Menambahkan Data Karyawan Lagi (y/n)?\n(Pilih 'y' jika ingin, pilih 'n' jika tidak)\n";
        cin >> ulang;
        if (ulang != 'y') {
            break;
        }
    }
}

void Tampilkan_Karyawan() {
    while (true) {
        for (const auto& employee : Karyawan) {
            cout << endl;
            cout << "ID: " << employee[0] << endl;
            cout << "Nama: " << employee[1] << endl;
            cout << "Jabatan: " << employee[2] << endl;
            cout << "Divisi: " << employee[3] << endl;
            cout << "Gaji: " << employee[4] << endl;
            cout << "------------------------------------------------\n" << endl;
        }
        char done;
        cout << "Isi Jika Ingin Kembali Ke Menu ('y' untuk kembali ke menu): ";
        cin >> done;
        if (done == 'y') {
            break;
        } else {
            cout << "Santai Liat-liat aja dulu" << endl;
        }
    }
}

void edit_Karyawan() {
    for (const auto& employee : Karyawan) {
        cout << endl;
        cout << "ID: " << employee[0] << endl;
        cout << "Nama: " << employee[1] << endl;
        cout << "Jabatan: " << employee[2] << endl;
        cout << "Divisi: " << employee[3] << endl;
        cout << "Gaji: " << employee[4] << endl;
        cout << "------------------------------------------------\n" << endl;
        }
    int id;
    cout << "ID karyawan: ";
    cin >> id;
    for (auto& employee : Karyawan) {
        if (stoi(employee[0]) == id) {
            string nama, jabatan, divisi;
            int gaji;
            cout << "Nama baru: ";
            cin.ignore();
            getline(cin, nama);
            cout << "Jabatan baru: ";
            getline(cin, jabatan);
            cout << "Divisi baru: ";
            getline(cin, divisi);
            while (true) {
                cout << "Gaji: ";
                cin >> gaji;
                if (gaji >= 0) {
                    employee[1] = nama;
                    employee[2] = jabatan;
                    employee[3] = divisi;
                    employee[4] = to_string(gaji);
                    cout << "Data Karyawan Dengan ID " << id << " Telah Diperbarui.\n" << endl;
                    return;
                }
                else {
                    cout << "Gaji Harus Berupa Angka." << endl;
                }
            }
        }
    }
    cout << "ID karyawan tidak ditemukan." << endl;
}

void delete_Karyawan() {
    for (const auto& employee : Karyawan) {
        cout << endl;
        cout << "ID: " << employee[0] << endl;
        cout << "Nama: " << employee[1] << endl;
        cout << "Jabatan: " << employee[2] << endl;
        cout << "Divisi: " << employee[3] << endl;
        cout << "Gaji: " << employee[4] << endl;
        cout << "------------------------------------------------\n" << endl;
        }
    int id;
    cout << "ID karyawan: ";
    cin >> id;
    for (auto it = Karyawan.begin(); it != Karyawan.end(); ++it) {
        if (stoi((*it)[0]) == id) {
            Karyawan.erase(it);
            cout << "Data Karyawan Telah Dihapus.\n" << endl;
            return;
        }
    }
    cout << "ID karyawan Tidak Ditemukan!." << endl;
}

void menu() {
    while (true) {
        cout << "---------------------------------------------" << endl;
        cout << "\t** Menu Manajemen Karyawan **" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "1. Tampilkan Karyawan" << endl;
        cout << "2. Tambah Karyawan Baru" << endl;
        cout << "3. Edit Karyawan" << endl;
        cout << "4. Hapus Karyawan" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih menu: ";
        int pilihan;
        cin >> pilihan;
        switch (pilihan) {
            case 1:
                Tampilkan_Karyawan();
                break;
            case 2:
                Tambahkan_Karyawan();
                break;
            case 3:
                edit_Karyawan();
                break;
            case 4:
                delete_Karyawan();
                break;
            case 5:
                cout << "Terima Kasih, Semoga Harimu Menyenangkan :)\n" << endl;
                return;
            default:
                cout << "Menu Tidak Ada." << endl;
        }
    }
}

int main(){
    string nama, nim;
    int chance = 3;

    while (chance > 0) {
        cout << "Masukkan Nama : ";
        cin >> nama;
        cout << "Masukkan NIM : ";
        cin >> nim;

        if (nama == "Ramadhan" && nim == "2309106053") {
            cout << "Login berhasil!\n";
            menu();
            break;
        } 
        else {
            chance--;
            if (chance > 0)
                cout << "Nama atau NIM salah. Sisa percobaan: " << chance << endl;
            else {
                cout << "Anda telah salah memasukkan Nama atau NIM sebanyak 3 kali. Program terhenti.\n";
                return 0;
            }
        }
    }
    return 0;
}
