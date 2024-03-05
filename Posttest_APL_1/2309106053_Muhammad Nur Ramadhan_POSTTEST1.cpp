#include <iostream>
#include <string>

using namespace std;

// Mengkonversi kilometer/jam ke centimeter/detik
double km_per_jam_to_cm_per_detik(double km_per_jam) {
    return km_per_jam * 100000 / 3600;
}

// Mengkonversi kilometer/jam ke meter/detik
double km_per_jam_to_meter_per_detik(double km_per_jam) {
    return km_per_jam * 1000 / 3600;
}

// Mengkonversi kilometer/jam ke mil/jam
double km_per_jam_to_mil_per_jam(double km_per_jam) {
    return km_per_jam / 1.60934;
}

// Mengkonversi centimeter/detik ke kilometer/jam
double cm_per_detik_to_km_per_jam(double cm_per_detik) {
    return cm_per_detik * 3600 / 100000;
}

// Mengkonversi centimeter/detik ke meter/detik
double cm_per_detik_to_meter_per_detik(double cm_per_detik) {
    return cm_per_detik / 100;
}

// Mengkonversi centimeter/detik ke mil/jam
double cm_per_detik_to_mil_per_jam(double cm_per_detik) {
    return cm_per_detik * 0.0000223694 * 3600;
}

// Mengkonversi meter/detik ke kilometer/jam
double meter_per_detik_to_km_per_jam(double meter_per_detik) {
    return meter_per_detik * 3.6;
}

// Mengkonversi meter/detik ke centimeter/detik
double meter_per_detik_to_cm_per_detik(double meter_per_detik) {
    return meter_per_detik * 100;
}

// Mengkonversi meter/detik ke mil/jam
double meter_per_detik_to_mil_per_jam(double meter_per_detik) {
    return meter_per_detik * 2.23694;
}

// Mengkonversi mil/jam ke kilometer/jam
double mil_per_jam_to_km_per_jam(double mil_per_jam) {
    return mil_per_jam * 1.60934;
}

// Mengkonversi mil/jam ke centimeter/detik
double mil_per_jam_to_cm_per_detik(double mil_per_jam) {
    return mil_per_jam * 160934 / 3600;
}

// Mengkonversi mil/jam ke meter/detik
double mil_per_jam_to_meter_per_detik(double mil_per_jam) {
    return mil_per_jam * 0.44704;
}

int main() {
    string nama, nim;
    int chance = 3;

    // Loop untuk login
    while (chance > 0) {
        cout << "Masukkan Nama : ";
        cin >> nama;
        cout << "Masukkan NIM : ";
        cin >> nim;

        if (nama == "Ramadhan" && nim == "2309106053") {
            cout << "Login berhasil!\n";
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

    int pilih;
    double value;

    while (true) {
        cout << "\nMenu Utama:\n";
        cout << "1. Konversi Kilometer/jam\n";
        cout << "2. Konversi Centimeter/detik\n";
        cout << "3. Konversi Meter/detik\n";
        cout << "4. Konversi Mil/jam\n";
        cout << "Pilih menu (1-4) atau 0 untuk keluar: ";
        cin >> pilih;

        if (pilih == 0) {
            cout << "Program selesai.\n";
            break;
        }

        cout << "Masukkan nilai: ";
        cin >> value;

        switch (pilih) {
            case 1:
                cout << value << " kilometer/jam ke:\n";
                cout << "- Centimeter/detik: " << km_per_jam_to_cm_per_detik(value) << endl;
                cout << "- Meter/detik: " << km_per_jam_to_meter_per_detik(value) << endl;
                cout << "- Mil/jam: " << km_per_jam_to_mil_per_jam(value) << endl;
                break;
            case 2:
                cout << value << " centimeter/detik ke:\n";
                cout << "- Kilometer/jam: " << cm_per_detik_to_km_per_jam(value) << endl;
                cout << "- Meter/detik: " << cm_per_detik_to_meter_per_detik(value) << endl;
                cout << "- Mil/jam: " << cm_per_detik_to_mil_per_jam(value) << endl;
                break;
            case 3:
                cout << value << " meter/detik ke:\n";
                cout << "- Kilometer/jam: " << meter_per_detik_to_km_per_jam(value) << endl;
                cout << "- Centimeter/detik: " << meter_per_detik_to_cm_per_detik(value) << endl;
                cout << "- Mil/jam: " << meter_per_detik_to_mil_per_jam(value) << endl;
                break;
            case 4:
                cout << value << " mil/jam ke:\n";
                cout << "- Kilometer/jam: " << mil_per_jam_to_km_per_jam(value) << endl;
                cout << "- Centimeter/detik: " << mil_per_jam_to_cm_per_detik(value) << endl;
                cout << "- Meter/detik: " << mil_per_jam_to_meter_per_detik(value) << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan pilih 1-4 atau 0 untuk keluar.\n";
        }
    }

    return 0;
}
