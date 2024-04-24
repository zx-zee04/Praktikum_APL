#include <iostream>
#include <string>
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

void Tambahkan_Karyawan(DaftarKaryawan* pDaftar) {
    if (pDaftar->jumlahKaryawan >= 15) {
        cout << "Maaf, sudah mencapai batas maksimal karyawan yang bisa ditambahkan." << endl;
        return;
    }
    
    Karyawan karyawan;
    karyawan.ID = pDaftar->jumlahKaryawan + 1;
    
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

    pDaftar->data[pDaftar->jumlahKaryawan++] = karyawan;
    cout << "\nKaryawan baru berhasil ditambahkan." << endl;
}

bool Tampilkan_Karyawan(const DaftarKaryawan* pDaftar) {
    char done;
    do {
        for (int i = 0; i < pDaftar->jumlahKaryawan; ++i) {
            const auto& karyawan = pDaftar->data[i];
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

void edit_Karyawan(Karyawan* pKaryawan) {
    cout << "Nama baru: ";
    cin.ignore();
    getline(cin, pKaryawan->nama);
    
    cout << "Jabatan baru: ";
    getline(cin, pKaryawan->jabatan);
    
    cout << "Divisi baru: ";
    getline(cin, pKaryawan->divisi);
    
    int gaji;
    while (true) {
        cout << "Gaji: ";
        cin >> gaji;
        if (gaji >= 0) {
            pKaryawan->gaji = gaji;
            cout << "Data Karyawan Telah Diperbarui.\n" << endl;
        }
        else {
            cout << "Gaji Harus Berupa Angka." << endl;
        }
        break;
    }
}

bool delete_Karyawan(DaftarKaryawan* pDaftar) {
    int id;
    cout << "ID karyawan: ";
    cin >> id;
    for (int i = 0; i < pDaftar->jumlahKaryawan; ++i) {
        if (pDaftar->data[i].ID == id) {
            for (int j = i; j < pDaftar->jumlahKaryawan - 1; ++j) {
                pDaftar->data[j] = pDaftar->data[j + 1];
            }
            pDaftar->jumlahKaryawan--;
            cout << "Data Karyawan Telah Dihapus.\n" << endl;
            return true; 
        }
    }
    cout << "ID karyawan Tidak Ditemukan!." << endl;
    return false;
}

void sort_Karyawan(DaftarKaryawan* pDaftar) {
    int n = pDaftar->jumlahKaryawan;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (pDaftar->data[j].nama > pDaftar->data[j + 1].nama) {
                Karyawan temp = pDaftar->data[j];
                pDaftar->data[j] = pDaftar->data[j + 1];
                pDaftar->data[j + 1] = temp;
            }
        }
    }
    cout << "\nDaftar Karyawan Telah Diurutkan Berdasarkan Nama secara Ascending.\n" << endl;
    Tampilkan_Karyawan(pDaftar);
}

void sort_Karyawan_Gaji(DaftarKaryawan* pDaftar) {
    int n = pDaftar->jumlahKaryawan;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (pDaftar->data[j].gaji < pDaftar->data[j + 1].gaji) {
                Karyawan temp = pDaftar->data[j];
                pDaftar->data[j] = pDaftar->data[j + 1];
                pDaftar->data[j + 1] = temp;
            }
        }
    }
    cout << "\nDaftar Karyawan Telah Diurutkan Berdasarkan Gaji secara Descending.\n" << endl;
    Tampilkan_Karyawan(pDaftar);
}

void sort_Karyawan_ID(DaftarKaryawan* pDaftar) {
    int n = pDaftar->jumlahKaryawan;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (pDaftar->data[j].ID > pDaftar->data[j + 1].ID) {
                Karyawan temp = pDaftar->data[j];
                pDaftar->data[j] = pDaftar->data[j + 1];
                pDaftar->data[j + 1] = temp;
            }
        }
    }
    cout << "\nDaftar Karyawan Telah Diurutkan Berdasarkan ID secara Ascending.\n" << endl;
    Tampilkan_Karyawan(pDaftar);
}

int binarySearch(const DaftarKaryawan* pDaftar, int targetID) {
    int low = 0;
    int high = pDaftar->jumlahKaryawan - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (pDaftar->data[mid].ID == targetID)
            return mid;
        else if (pDaftar->data[mid].ID < targetID)
            low = mid + 1;
        else
            high = mid - 1;
    } 
    return -1;
}

void searchingKaryawan_ID(const DaftarKaryawan* pDaftar) {
    int targetID;
    cout << "Masukkan ID karyawan yang ingin Anda cari: ";
    cin >> targetID;
    
    int index = binarySearch(pDaftar, targetID);
    if (index != -1) {
        const Karyawan& karyawan = pDaftar->data[index];
        cout << "Karyawan ditemukan:" << endl;
        cout << "ID: " << karyawan.ID << endl;
        cout << "Nama: " << karyawan.nama << endl;
        cout << "Jabatan: " << karyawan.jabatan << endl;
        cout << "Divisi: " << karyawan.divisi << endl;
        cout << "Gaji: " << karyawan.gaji << endl;
    } else {
        cout << "Karyawan dengan ID " << targetID << " tidak ditemukan." << endl;
    }
}

int searching_interpolation(const DaftarKaryawan* pDaftar, const string& targetNama) {
    int low = 0;
    int high = pDaftar->jumlahKaryawan - 1;

    while (low <= high && targetNama >= pDaftar->data[low].nama && targetNama <= pDaftar->data[high].nama) {
        int pos = low + ((double)(high - low) / (pDaftar->data[high].nama.compare(pDaftar->data[low].nama))) * (targetNama.compare(pDaftar->data[low].nama));

        if (pDaftar->data[pos].nama == targetNama)
            return pos;
        else if (pDaftar->data[pos].nama < targetNama)
            high = pos - 1;
        else
            low = pos + 1;
    }
    return -1;
}

void tampilkanKaryawanByName(const DaftarKaryawan* pDaftar) {
    string targetNama;
    cout << "Masukkan nama karyawan yang ingin Anda cari: ";
    cin.ignore(); 
    getline(cin, targetNama);

    int index = searching_interpolation(pDaftar, targetNama);
    if (index != -1) {
        const Karyawan& karyawan = pDaftar->data[index];
        cout << "Karyawan ditemukan:" << endl;
        cout << "ID: " << karyawan.ID << endl;
        cout << "Nama: " << karyawan.nama << endl;
        cout << "Jabatan: " << karyawan.jabatan << endl;
        cout << "Divisi: " << karyawan.divisi << endl;
        cout << "Gaji: " << karyawan.gaji << endl;
    } else {
        cout << "Karyawan dengan nama " << targetNama << " tidak ditemukan." << endl;
    }
}

void menu(DaftarKaryawan* pDaftar) {
    cout << "---------------------------------------------" << endl;
    cout << "\t** Menu Manajemen Karyawan **" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "1. Tampilkan Karyawan" << endl;
    cout << "2. Tambah Karyawan Baru" << endl;
    cout << "3. Edit Karyawan" << endl;
    cout << "4. Hapus Karyawan" << endl;
    cout << "5. Keluar" << endl;
    cout << "6. Urutkan Karyawan Berdasarkan Nama" << endl;
    cout << "7. Urutkan Karyawan Berdasarkan Gaji" << endl;
    cout << "8. Urutkan Karyawan Berdasarkan ID" << endl;
    cout << "9. Searching Karyawan dengan ID" << endl;
    cout << "10. Searching Karyawan dengan Nama" << endl;
    cout << "Pilih menu: ";
    int pilihan;
    cin >> pilihan;
    switch (pilihan) {
        case 1:
            Tampilkan_Karyawan(pDaftar);
            break;
        case 2:
            Tambahkan_Karyawan(pDaftar);
            break;
        case 3: {
            int id;
            cout << "ID karyawan yang akan diedit: ";
            cin >> id;
            for (int i = 0; i < pDaftar->jumlahKaryawan; ++i) {
                if (pDaftar->data[i].ID == id) {
                    edit_Karyawan(&(pDaftar->data[i]));
                    cout << endl;
                    menu(pDaftar);
                    return;
                }
            }
            cout << "ID karyawan tidak ditemukan." << endl;
            break;
        }
        case 4:
            delete_Karyawan(pDaftar);
            break;
        case 5:
            cout << "Terima Kasih, Semoga Harimu Menyenangkan :)\n" << endl;
            return;
        case 6:
            sort_Karyawan(pDaftar);
            break;
        case 7:
            sort_Karyawan_Gaji(pDaftar);
            break;
        case 8:
            sort_Karyawan_ID(pDaftar);
            break;
        case 9:
            searchingKaryawan_ID(pDaftar);
            break;
        case 10:
            tampilkanKaryawanByName(pDaftar);
        default:
            cout << "Menu Tidak Ada." << endl;
    }
    menu(pDaftar);
}

int main(){
    DaftarKaryawan daftarKaryawan;
    string nama, nim;
    int chance = 3;

    while (chance > 0) {
        cout << "Masukkan Nama : ";
        cin >> nama;
        cout << "Masukkan NIM : ";
        cin >> nim;

        if (nama == "Ramadhan" && nim == "2309106053") {
            cout << "Login berhasil!\n";
            menu(&daftarKaryawan);
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
