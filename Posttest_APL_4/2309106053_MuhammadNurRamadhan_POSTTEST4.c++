#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>

using namespace std;

struct Karyawan {
    int ID;
    string nama;
    string jabatan;
    string divisi;
    int gaji;
};

struct DaftarKaryawan {
    Karyawan data[15];
    int jumlahKaryawan = 0;
};

DaftarKaryawan daftarKaryawan;

void Tambahkan_Karyawan() {
    if (daftarKaryawan.jumlahKaryawan >= 15) {
        cout << "Maaf, sudah mencapai batas maksimal karyawan yang bisa ditambahkan." << endl;
        return;
    }
    
    Karyawan karyawan;
    karyawan.ID = daftarKaryawan.jumlahKaryawan + 1;
    
    cout << "Nama: ";
    cin.ignore();
    getline(cin, karyawan.nama);
    
    cout << "Jabatan: ";
    getline(cin, karyawan.jabatan);
    
    cout << "Divisi: ";
    getline(cin, karyawan.divisi);
    
    bool inputValid = false;
    do {
        cout << "Gaji: ";
        if (cin >> karyawan.gaji) {
            if (karyawan.gaji >= 0) {
                inputValid = true;
            } else {
                cout << "Gaji harus berupa angka positif." << endl;
            }
        } else {
            cout << "Gaji harus berupa angka positif." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } 
    while (!inputValid);

    daftarKaryawan.data[daftarKaryawan.jumlahKaryawan++] = karyawan;
    cout << "\nKaryawan baru berhasil ditambahkan." << endl;
}


bool Tampilkan_Karyawan() {
    char done;
    do {
        for (int i = 0; i < daftarKaryawan.jumlahKaryawan; ++i) {
            const auto& karyawan = daftarKaryawan.data[i];
            cout << endl;
            cout << "ID: " << karyawan.ID << endl;
            cout << "Nama: " << karyawan.nama << endl;
            cout << "Jabatan: " << karyawan.jabatan << endl;
            cout << "Divisi: " << karyawan.divisi << endl;
            cout << "Gaji: " << karyawan.gaji << endl;
            cout << "------------------------------------------------\n" << endl;
        }
        cout << "Isi Jika Ingin Kembali Ke Menu ('y' untuk kembali ke menu): ";
        cin >> done;
        if (done != 'y') {
            cout << "Santai Liat-liat aja dulu" << endl;
        }
    } while (done != 'y');
    return true; 
}

void edit_Karyawan() {
    int id;
    cout << "ID karyawan: ";
    cin >> id;
    for (int i = 0; i < daftarKaryawan.jumlahKaryawan; ++i) {
        if (daftarKaryawan.data[i].ID == id) {
            cout << "Nama baru: ";
            cin.ignore();
            getline(cin, daftarKaryawan.data[i].nama);
            
            cout << "Jabatan baru: ";
            getline(cin, daftarKaryawan.data[i].jabatan);
            
            cout << "Divisi baru: ";
            getline(cin, daftarKaryawan.data[i].divisi);
            
            int gaji;
            while (true) {
                cout << "Gaji: ";
                cin >> gaji;
                if (gaji >= 0) {
                    daftarKaryawan.data[i].gaji = gaji;
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

bool delete_Karyawan() {
    int id;
    cout << "ID karyawan: ";
    cin >> id;
    for (int i = 0; i < daftarKaryawan.jumlahKaryawan; ++i) {
        if (daftarKaryawan.data[i].ID == id) {
            for (int j = i; j < daftarKaryawan.jumlahKaryawan - 1; ++j) {
                daftarKaryawan.data[j] = daftarKaryawan.data[j + 1];
            }
            daftarKaryawan.jumlahKaryawan--;
            cout << "Data Karyawan Telah Dihapus.\n" << endl;
            return true; 
        }
    }
    cout << "ID karyawan Tidak Ditemukan!." << endl;
    return false;
}

void menu() {
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
    menu();
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