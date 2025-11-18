#include <stdio.h>
#include <string.h>  // Untuk strcmp() dan strcpy()
#include <stdlib.h>  // Untuk system("cls") dan exit()
#include <windows.h> // Untuk Sleep()



struct Akun {
    char username[50];
    char password[50];
};
#define MAX_AKUN 10
struct Akun daftarAkun[MAX_AKUN];
int jumlahAkunSekarang = 0;

struct Jasa {
    char kodeJasa[10];
    char namaJasa[50];
    int hargaJasa;
};
#define MAX_JASA 20
struct Jasa daftarJasa[MAX_JASA];
int jumlahJasaSekarang = 0;

struct Sparepart {
    char kodeSparepart[10];
    char namaSparepart[50];
    int stok; // Ini yang labelnya kita ganti jadi "Jumlah"
    int hargaSparepart;
};
#define MAX_SPAREPART 50
struct Sparepart daftarSparepart[MAX_SPAREPART];
int jumlahSparepartSekarang = 0;

struct ItemStruk {
    char kode[10];
    char nama[50];
    int harga;
    int qty; // Kuantitas
};

struct MobilServis {
    char namaPelanggan[50];
    char platNomor[15];
    char jenisMobil[30];

    // Ini adalah "keranjang belanja" nya
    struct ItemStruk item[20]; // Setiap mobil bisa beli maks 20 jenis item
    int jumlahItemDibeli;      // Penghitung isi keranjang
};
#define MAX_MOBIL_SERVIS 10
struct MobilServis daftarMobil[MAX_MOBIL_SERVIS];
int jumlahMobilSekarang = 0;


void loadingAnimation() {
    printf("Harap tunggu, sistem sedang dimuat...\n");
    for (int i = 0; i <= 100; i++) {
        printf("\r[");
        int barWidth = 20;
        int pos = (i * barWidth) / 100;
        for (int j = 0; j < barWidth; j++) {
            if (j < pos) printf("=");
            else if (j == pos) printf(">");
            else printf(" ");
        }
        printf("] %d%% ", i);
        fflush(stdout);
        Sleep(30);
    }
    printf("\nSistem berhasil dimuat!\n\n");
    Sleep(1000);
    system("cls");
}

void pauseScreen() {
    printf("\n\nTekan Enter untuk kembali ke menu...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

void bersihkanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void registerSystem() {
    system("cls");
    printf("=== BUAT AKUN BARU ===\n");
    if (jumlahAkunSekarang >= MAX_AKUN) {
        printf("Maaf, kapasitas akun sudah penuh.\n");
        Sleep(2000);
        system("cls");
        return;
    }
    char usernameBaru[50];
    printf("Masukkan username baru: ");
    scanf("%s", usernameBaru);
    int duplikat = 0;
    for (int i = 0; i < jumlahAkunSekarang; i++) {
        if (strcmp(daftarAkun[i].username, usernameBaru) == 0) {
            duplikat = 1;
            break;
        }
    }
    if (duplikat == 1) {
        printf("\nMaaf, username '%s' sudah terpakai.\n", usernameBaru);
        Sleep(2000);
        system("cls");
        return;
    }
    char passwordBaru[50];
    printf("Masukkan password baru: ");
    scanf("%s", passwordBaru);
    strcpy(daftarAkun[jumlahAkunSekarang].username, usernameBaru);
    strcpy(daftarAkun[jumlahAkunSekarang].password, passwordBaru);
    jumlahAkunSekarang++;
    printf("\nAkun baru berhasil dibuat!\n");
    Sleep(2000);
    system("cls");
}

int loginSystem() {
    char username[50];
    char password[50];
    int attempts = 3;
    while (attempts > 0) {
        system("cls");
        printf("=== SISTEM INFORMASI BENGKEL ===\n");
        printf("----------------------------------\n");
        printf("Silakan login untuk melanjutkan.\n");
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        int loginBerhasil = 0;
        char namaYangLogin[50];
        for (int i = 0; i < jumlahAkunSekarang; i++) {
            if (strcmp(username, daftarAkun[i].username) == 0 &&
                strcmp(password, daftarAkun[i].password) == 0)
            {
                loginBerhasil = 1;
                strcpy(namaYangLogin, daftarAkun[i].username);
                break;
            }
        }
        if (loginBerhasil == 1) {
            printf("\nLogin berhasil!");
            printf("\nSelamat datang, %s!\n", namaYangLogin);
            Sleep(2000);
            system("cls");
            return 1;
        } else {
            attempts--;
            printf("\nMaaf, username atau password salah.\n");
            if (attempts > 0) {
                printf("Sisa percobaan: %d\n\n", attempts);
                Sleep(1500);
            } else {
                printf("Anda telah 3x gagal login. Program akan keluar.\n");
                Sleep(2000);
                return 0;
            }
        }
    }
    return 0;
}


void tambahJasa() {
    system("cls");
    printf("--- Tambah Jasa Baru ---\n");
    if (jumlahJasaSekarang >= MAX_JASA) {
        printf("Kapasitas data Jasa sudah penuh!\n");
        pauseScreen();
        return;
    }
    printf("Kode Jasa (cth: J01): ");
    scanf("%s", daftarJasa[jumlahJasaSekarang].kodeJasa);
    bersihkanBuffer();
    printf("Nama Jasa: ");
    fgets(daftarJasa[jumlahJasaSekarang].namaJasa, 50, stdin);
    daftarJasa[jumlahJasaSekarang].namaJasa[strcspn(daftarJasa[jumlahJasaSekarang].namaJasa, "\n")] = 0;
    printf("Harga Jasa (Rp): ");
    scanf("%d", &daftarJasa[jumlahJasaSekarang].hargaJasa);
    jumlahJasaSekarang++;
    printf("\nJasa baru berhasil ditambahkan!\n");
    pauseScreen();
}

void lihatJasa() {
    system("cls");
    printf("--- Daftar Jasa Servis ---\n");
    if (jumlahJasaSekarang == 0) {
        printf("Belum ada data jasa yang tersimpan.\n");
    } else {
        printf("---------------------------------------------------\n");
        printf("Kode | Nama Jasa                  | Harga\n");
        printf("---------------------------------------------------\n");
        for (int i = 0; i < jumlahJasaSekarang; i++) {
            printf("%-4s | %-26s | Rp %d\n",
                daftarJasa[i].kodeJasa,
                daftarJasa[i].namaJasa,
                daftarJasa[i].hargaJasa);
        }
        printf("---------------------------------------------------\n");
    }
}

void editJasa() {
    system("cls");
    lihatJasa();
    if (jumlahJasaSekarang == 0) {
        pauseScreen();
        return;
    }
    char kodeEdit[10];
    printf("\nMasukkan Kode Jasa yang ingin diedit: ");
    scanf("%s", kodeEdit);
    int index = -1;
    for (int i = 0; i < jumlahJasaSekarang; i++) {
        if (strcmp(daftarJasa[i].kodeJasa, kodeEdit) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Jasa dengan kode '%s' tidak ditemukan.\n", kodeEdit);
    } else {
        printf("--- Mengedit Jasa [%s] ---\n", daftarJasa[index].namaJasa);
        bersihkanBuffer();
        printf("Nama Jasa Baru: ");
        fgets(daftarJasa[index].namaJasa, 50, stdin);
        daftarJasa[index].namaJasa[strcspn(daftarJasa[index].namaJasa, "\n")] = 0;
        printf("Harga Jasa Baru (Rp): ");
        scanf("%d", &daftarJasa[index].hargaJasa);
        printf("\nData jasa berhasil diperbarui!\n");
    }
    pauseScreen();
}

void hapusJasa() {
    system("cls");
    lihatJasa();
    if (jumlahJasaSekarang == 0) {
        pauseScreen();
        return;
    }
    char kodeHapus[10];
    printf("\nMasukkan Kode Jasa yang ingin dihapus: ");
    scanf("%s", kodeHapus);
    int index = -1;
    for (int i = 0; i < jumlahJasaSekarang; i++) {
        if (strcmp(daftarJasa[i].kodeJasa, kodeHapus) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Jasa dengan kode '%s' tidak ditemukan.\n", kodeHapus);
    } else {
        printf("--- Menghapus Jasa [%s] ---\n", daftarJasa[index].namaJasa);
        for (int i = index; i < jumlahJasaSekarang - 1; i++) {
            daftarJasa[i] = daftarJasa[i + 1];
        }
        jumlahJasaSekarang--;
        printf("\nData jasa berhasil dihapus!\n");
    }
    pauseScreen();
}

void tambahSparepart() {
    system("cls");
    printf("--- Tambah Sparepart Baru ---\n");
    if (jumlahSparepartSekarang >= MAX_SPAREPART) {
        printf("Kapasitas data Sparepart sudah penuh!\n");
        pauseScreen();
        return;
    }
    printf("Kode Sparepart (cth: S01): ");
    scanf("%s", daftarSparepart[jumlahSparepartSekarang].kodeSparepart);
    bersihkanBuffer();
    printf("Nama Sparepart: ");
    fgets(daftarSparepart[jumlahSparepartSekarang].namaSparepart, 50, stdin);
    daftarSparepart[jumlahSparepartSekarang].namaSparepart[strcspn(daftarSparepart[jumlahSparepartSekarang].namaSparepart, "\n")] = 0;
    printf("Jumlah Awal: "); // Label sudah diganti
    scanf("%d", &daftarSparepart[jumlahSparepartSekarang].stok);
    printf("Harga Sparepart (Rp) (Ketik angkanya saja, cth: 50000): ");
    scanf("%d", &daftarSparepart[jumlahSparepartSekarang].hargaSparepart);
    jumlahSparepartSekarang++;
    printf("\nSparepart baru berhasil ditambahkan!\n");
    pauseScreen();
}

void lihatSparepart() {
    system("cls");
    printf("--- Daftar Sparepart ---\n");
    if (jumlahSparepartSekarang == 0) {
        printf("Belum ada data sparepart yang tersimpan.\n");
    } else {
        printf("------------------------------------------------------------------\n");
        printf("Kode | Nama Sparepart             | Jumlah | Harga\n"); // Label sudah diganti
        printf("------------------------------------------------------------------\n");
        for (int i = 0; i < jumlahSparepartSekarang; i++) {
            printf("%-4s | %-26s | %-6d | Rp %d\n", // Format spasi disesuaikan
                daftarSparepart[i].kodeSparepart,
                daftarSparepart[i].namaSparepart,
                daftarSparepart[i].stok,
                daftarSparepart[i].hargaSparepart);
        }
        printf("------------------------------------------------------------------\n");
    }
}

void editSparepart() {
    system("cls");
    lihatSparepart();
    if (jumlahSparepartSekarang == 0) {
        pauseScreen();
        return;
    }
    char kodeEdit[10];
    printf("\nMasukkan Kode Sparepart yang ingin diedit: ");
    scanf("%s", kodeEdit);
    int index = -1;
    for (int i = 0; i < jumlahSparepartSekarang; i++) {
        if (strcmp(daftarSparepart[i].kodeSparepart, kodeEdit) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Sparepart dengan kode '%s' tidak ditemukan.\n", kodeEdit);
    } else {
        printf("--- Mengedit Sparepart [%s] ---\n", daftarSparepart[index].namaSparepart);
        bersihkanBuffer();
        printf("Nama Sparepart Baru: ");
        fgets(daftarSparepart[index].namaSparepart, 50, stdin);
        daftarSparepart[index].namaSparepart[strcspn(daftarSparepart[index].namaSparepart, "\n")] = 0;
        printf("Jumlah Baru: "); // Label sudah diganti
        scanf("%d", &daftarSparepart[index].stok);
        printf("Harga Sparepart Baru (Rp): ");
        scanf("%d", &daftarSparepart[index].hargaSparepart);
        printf("\nData sparepart berhasil diperbarui!\n");
    }
    pauseScreen();
}

void hapusSparepart() {
    system("cls");
    lihatSparepart();
    if (jumlahSparepartSekarang == 0) {
        pauseScreen();
        return;
    }
    char kodeHapus[10];
    printf("\nMasukkan Kode Sparepart yang ingin dihapus: ");
    scanf("%s", kodeHapus);
    int index = -1;
    for (int i = 0; i < jumlahSparepartSekarang; i++) {
        if (strcmp(daftarSparepart[i].kodeSparepart, kodeHapus) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Sparepart dengan kode '%s' tidak ditemukan.\n", kodeHapus);
    } else {
        printf("--- Menghapus Sparepart [%s] ---\n", daftarSparepart[index].namaSparepart);
        for (int i = index; i < jumlahSparepartSekarang - 1; i++) {
            daftarSparepart[i] = daftarSparepart[i + 1];
        }
        jumlahSparepartSekarang--;
        printf("\nData sparepart berhasil dihapus!\n");
    }
    pauseScreen();
}

void menuManajemenData() {
    int pilihan = 0;
    do {
        system("cls");
        printf("=== MENU MANAJEMEN JASA & SPARE PART ===\n");
        printf("----------------------------------------\n");
        printf("--- JASA ---\n");
        printf("1. Tambah Jasa Baru\n");
        printf("2. Lihat Daftar Jasa\n");
        printf("3. Edit Jasa\n");
        printf("4. Hapus Jasa\n");
        printf("----\n");
        printf("--- SPARE PART ---\n");
        printf("5. Tambah Spare Part Baru\n");
        printf("6. Lihat Daftar Spare Part\n");
        printf("7. Edit Spare Part\n");
        printf("8. Hapus Spare Part\n");
        printf("\n9. Kembali ke Menu Utama\n");
        printf("----------------------------------------\n");
        printf("Pilihan Anda [1-8, 9]: ");

        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1: tambahJasa(); break;
            case 2: lihatJasa(); pauseScreen(); break;
            case 3: editJasa(); break;
            case 4: hapusJasa(); break;
            case 5: tambahSparepart(); break;
            case 6: lihatSparepart(); pauseScreen(); break;
            case 7: editSparepart(); break;
            case 8: hapusSparepart(); break;
            case 9: break;
            default: printf("Pilihan tidak valid!\n"); Sleep(1000);
        }
    } while (pilihan != 9);
}

// --- FUNGSI MENU 2: INPUT MOBIL ---

void inputMobilBaru() {
    system("cls");
    printf("=== INPUT MOBIL SERVIS BARU ===\n");
    if (jumlahMobilSekarang >= MAX_MOBIL_SERVIS) {
        printf("Antrian servis penuh! Tidak bisa menambah mobil baru.\n");
        pauseScreen();
        return;
    }
    char inputNama[50], inputPlat[15], inputJenis[30];
    bersihkanBuffer();
    printf("Input Nama Pelanggan: ");
    fgets(inputNama, 50, stdin);
    inputNama[strcspn(inputNama, "\n")] = 0;
    printf("Input Plat Nomor (cth: H 4444 AA): ");
    fgets(inputPlat, 15, stdin);
    inputPlat[strcspn(inputPlat, "\n")] = 0;
    printf("Input Jenis Mobil (cth: Avanza Veloz): ");
    fgets(inputJenis, 30, stdin);
    inputJenis[strcspn(inputJenis, "\n")] = 0;
    strcpy(daftarMobil[jumlahMobilSekarang].namaPelanggan, inputNama);
    strcpy(daftarMobil[jumlahMobilSekarang].platNomor, inputPlat);
    strcpy(daftarMobil[jumlahMobilSekarang].jenisMobil, inputJenis);

    // PENTING: Inisialisasi keranjang belanja mobil baru
    daftarMobil[jumlahMobilSekarang].jumlahItemDibeli = 0;

    jumlahMobilSekarang++;
    printf("\nData mobil baru berhasil disimpan!\n");
    printf("Antrian saat ini: %d / %d\n", jumlahMobilSekarang, MAX_MOBIL_SERVIS);
    pauseScreen();
}

void lihatAntrianMobil() {
    system("cls");
    printf("=== DAFTAR MOBIL DALAM ANTRIAN ===\n");
    printf("------------------------------------\n");
    if (jumlahMobilSekarang == 0) {
        printf("Belum ada mobil dalam antrian servis.\n");
    } else {
        printf("No. | Nama Pelanggan   | Plat Nomor      | Jenis Mobil\n");
        printf("-------------------------------------------------------------------\n");
        for (int i = 0; i < jumlahMobilSekarang; i++) {
            printf("%-3d | %-16s | %-15s | %s\n",
                i + 1,
                daftarMobil[i].namaPelanggan,
                daftarMobil[i].platNomor,
                daftarMobil[i].jenisMobil);
        }
    }
    pauseScreen();
}

void menuServiceMobil() {
    int pilihan = 0;
    do {
        system("cls");
        printf("=== MENU INPUT SERVICE MOBIL ===\n");
        printf("--------------------------------\n");
        printf("1. Input Mobil Servis Baru\n");
        printf("2. Lihat Antrian Mobil Servis\n");
        printf("\n9. Kembali ke Menu Utama\n");
        printf("--------------------------------\n");
        printf("Pilihan Anda [1, 2, 9]: ");
        scanf("%d", &pilihan);
        switch(pilihan) {
            case 1: inputMobilBaru(); break;
            case 2: lihatAntrianMobil(); break;
            case 9: break;
            default: printf("Pilihan tidak valid. Coba lagi.\n"); Sleep(1000);
        }
    } while (pilihan != 9);
}

// --- FUNGSI MENU 3: TAMBAH LAYANAN (TRANSAKSI) ---

// Helper: Menampilkan antrian mobil (versi simpel)
void tampilAntrianSimple() {
    printf("--- Daftar Mobil Antrian ---\n");
    if (jumlahMobilSekarang == 0) {
        printf("Antrian kosong.\n");
        return;
    }
    printf("No. | Nama Pelanggan   | Plat Nomor\n");
    printf("--------------------------------------\n");
    for (int i = 0; i < jumlahMobilSekarang; i++) {
        printf("%-3d | %-16s | %s\n",
            i + 1,
            daftarMobil[i].namaPelanggan,
            daftarMobil[i].platNomor);
    }
    printf("--------------------------------------\n");
}

// Helper: Menampilkan daftar jasa
void tampilDaftarJasa() {
    printf("--- Daftar Jasa Tersedia ---\n");
    if (jumlahJasaSekarang == 0) {
        printf("Katalog Jasa masih kosong.\n");
    } else {
        printf("Kode | Nama Jasa                  | Harga\n");
        printf("---------------------------------------------------\n");
        for (int i = 0; i < jumlahJasaSekarang; i++) {
            printf("%-4s | %-26s | Rp %d\n",
                daftarJasa[i].kodeJasa,
                daftarJasa[i].namaJasa,
                daftarJasa[i].hargaJasa);
        }
    }
}

// Helper: Menampilkan daftar sparepart
void tampilDaftarSparepart() {
    printf("--- Daftar Sparepart Tersedia ---\n");
    if (jumlahSparepartSekarang == 0) {
        printf("Katalog Sparepart masih kosong.\n");
    } else {
        printf("------------------------------------------------------------------\n");
        printf("Kode | Nama Sparepart             | Jumlah | Harga\n"); // Label diganti
        printf("------------------------------------------------------------------\n");
        for (int i = 0; i < jumlahSparepartSekarang; i++) {
            printf("%-4s | %-26s | %-6d | Rp %d\n", // Format spasi disesuaikan
                daftarSparepart[i].kodeSparepart,
                daftarSparepart[i].namaSparepart,
                daftarSparepart[i].stok,
                daftarSparepart[i].hargaSparepart);
        }
    }
}

void menuTambahLayanan() {
    int pilihanMobil = 0;
    int indexMobil = -1;

    system("cls");
    printf("=== MENU PENAMBAHAN JASA & SPARE PART ===\n");

    if (jumlahMobilSekarang == 0) {
        printf("Belum ada mobil di antrian servis.\n");
        printf("Silakan input mobil terlebih dahulu (Menu 2).\n");
        pauseScreen();
        return;
    }

    if (jumlahJasaSekarang == 0 && jumlahSparepartSekarang == 0) {
        printf("Katalog Jasa dan Sparepart masih kosong.\n");
        printf("Silakan isi katalog terlebih dahulu (Menu 1).\n");
        pauseScreen();
        return;
    }

    // --- Langkah 1: Pilih Mobil ---
    tampilAntrianSimple();
    printf("\nPilih mobil (No.) yang ingin ditambah layanannya: ");
    scanf("%d", &pilihanMobil);

    if (pilihanMobil < 1 || pilihanMobil > jumlahMobilSekarang) {
        printf("Pilihan tidak valid.\n");
        pauseScreen();
        return;
    }
    indexMobil = pilihanMobil - 1;

    // --- Langkah 2: Loop Penambahan Item ---
    int pilihanLayanan = 0;
    do {
        system("cls");
        printf("Menambahkan Layanan untuk: %s (%s)\n",
            daftarMobil[indexMobil].namaPelanggan,
            daftarMobil[indexMobil].platNomor);

        printf("--- Item Saat Ini (%d item) ---\n", daftarMobil[indexMobil].jumlahItemDibeli);
        if(daftarMobil[indexMobil].jumlahItemDibeli > 0) {
            for(int i=0; i<daftarMobil[indexMobil].jumlahItemDibeli; i++) {
                printf("%d. %s (Qty: %d)\n", i+1, daftarMobil[indexMobil].item[i].nama, daftarMobil[indexMobil].item[i].qty);
            }
        } else {
            printf("Keranjang masih kosong.\n");
        }
        printf("----------------------------\n");

        printf("1. Tambah Jasa\n");
        printf("2. Tambah Sparepart\n");
        printf("9. Selesai & Kembali ke Menu Utama\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihanLayanan);

        if (pilihanLayanan == 1) {
            // --- Tambah Jasa ---
            tampilDaftarJasa();
            char kodeJasa[10];
            printf("Masukkan Kode Jasa (cth: J01): ");
            scanf("%s", kodeJasa);
            int indexJasa = -1;
            for (int i = 0; i < jumlahJasaSekarang; i++) {
                if (strcmp(daftarJasa[i].kodeJasa, kodeJasa) == 0) {
                    indexJasa = i;
                    break;
                }
            }
            if (indexJasa == -1) {
                printf("Kode Jasa tidak ditemukan!\n");
            } else {
                int slot = daftarMobil[indexMobil].jumlahItemDibeli;
                strcpy(daftarMobil[indexMobil].item[slot].kode, daftarJasa[indexJasa].kodeJasa);
                strcpy(daftarMobil[indexMobil].item[slot].nama, daftarJasa[indexJasa].namaJasa);
                daftarMobil[indexMobil].item[slot].harga = daftarJasa[indexJasa].hargaJasa;
                daftarMobil[indexMobil].item[slot].qty = 1;
                daftarMobil[indexMobil].jumlahItemDibeli++;
                printf("\nJasa '%s' berhasil ditambahkan ke mobil!\n", daftarJasa[indexJasa].namaJasa);
            }
            Sleep(1500);

        } else if (pilihanLayanan == 2) {
            // --- Tambah Sparepart ---
            tampilDaftarSparepart();
            char kodePart[10];
            printf("Masukkan Kode Sparepart (cth: S01): ");
            scanf("%s", kodePart);
            int indexPart = -1;
            for (int i = 0; i < jumlahSparepartSekarang; i++) {
                if (strcmp(daftarSparepart[i].kodeSparepart, kodePart) == 0) {
                    indexPart = i;
                    break;
                }
            }
            if (indexPart == -1) {
                printf("Kode Sparepart tidak ditemukan!\n");
            } else {
                int qtyBeli = 0;
                printf("Jumlah saat ini: %d. Masukkan jumlah beli: ", daftarSparepart[indexPart].stok); // Label diganti
                scanf("%d", &qtyBeli);

                if (qtyBeli <= 0) {
                    printf("Jumlah beli tidak valid.\n");
                } else if (qtyBeli > daftarSparepart[indexPart].stok) {
                    printf("JUMLAH TIDAK CUKUP! (Sisa: %d)\n", daftarSparepart[indexPart].stok); // Label diganti
                } else {
                    int slot = daftarMobil[indexMobil].jumlahItemDibeli;
                    strcpy(daftarMobil[indexMobil].item[slot].kode, daftarSparepart[indexPart].kodeSparepart);
                    strcpy(daftarMobil[indexMobil].item[slot].nama, daftarSparepart[indexPart].namaSparepart);
                    daftarMobil[indexMobil].item[slot].harga = daftarSparepart[indexPart].hargaSparepart;
                    daftarMobil[indexMobil].item[slot].qty = qtyBeli;
                    daftarMobil[indexMobil].jumlahItemDibeli++;
                    daftarSparepart[indexPart].stok -= qtyBeli;
                    printf("\nSparepart '%s' (Qty: %d) berhasil ditambahkan!\n", daftarSparepart[indexPart].namaSparepart, qtyBeli);
                    printf("Jumlah '%s' tersisa: %d\n", daftarSparepart[indexPart].namaSparepart, daftarSparepart[indexPart].stok); // Label diganti
                }
            }
            Sleep(2000);
        }
    } while (pilihanLayanan != 9);
    printf("Kembali ke Menu Utama...\n");
    Sleep(1000);
}


// --- FUNGSI MENU 4: STRUK & PEMBAYARAN ---

/**
 * @brief Fungsi inti untuk memproses struk dan pembayaran.
 */
void prosesPembayaran() {
    system("cls");
    printf("=== PROSES STRUK & PEMBAYARAN ===\n");

    if (jumlahMobilSekarang == 0) {
        printf("Belum ada mobil di antrian servis.\n");
        pauseScreen();
        return;
    }

    // --- Langkah 1: Pilih Mobil ---
    tampilAntrianSimple(); // Memakai ulang fungsi dari Poin 3
    printf("\nPilih mobil (No.) yang akan melakukan pembayaran: ");
    int pilihanMobil;
    scanf("%d", &pilihanMobil);

    if (pilihanMobil < 1 || pilihanMobil > jumlahMobilSekarang) {
        printf("Pilihan tidak valid.\n");
        pauseScreen();
        return;
    }
    int indexMobil = pilihanMobil - 1;

    if (daftarMobil[indexMobil].jumlahItemDibeli == 0) {
        printf("Mobil %s belum memiliki tagihan.\n", daftarMobil[indexMobil].namaPelanggan);
        printf("Silakan tambahkan layanan di Menu 3 terlebih dahulu.\n");
        pauseScreen();
        return;
    }

    // --- Langkah 2: Cetak Struk & Hitung Total ---
    system("cls");
    printf("==================================================\n");
    printf("                 STRUK PEMBAYARAN                 \n");
    printf("                 BENGKEL MOBIL ANDA               \n");
    printf("==================================================\n");

    printf("Nama Pelanggan: %s\n", daftarMobil[indexMobil].namaPelanggan);
    printf("Plat Nomor    : %s\n", daftarMobil[indexMobil].platNomor);
    printf("Jenis Mobil   : %s\n", daftarMobil[indexMobil].jenisMobil);
    printf("--------------------------------------------------\n");
    printf("Rincian Biaya:\n");
    printf("Nama Item                  | Qty | Harga      | Subtotal\n");
    printf("--------------------------------------------------\n");

    long long totalTagihan = 0;

    for (int i = 0; i < daftarMobil[indexMobil].jumlahItemDibeli; i++) {
        long long subtotal = (long long)daftarMobil[indexMobil].item[i].harga * daftarMobil[indexMobil].item[i].qty;

        printf("%-26s | %-3d | Rp %-8d | Rp %lld\n",
            daftarMobil[indexMobil].item[i].nama,
            daftarMobil[indexMobil].item[i].qty,
            daftarMobil[indexMobil].item[i].harga,
            subtotal);

        totalTagihan += subtotal;
    }
    printf("==================================================\n");
    printf("TOTAL TAGIHAN                           : Rp %lld\n", totalTagihan);
    printf("==================================================\n");

    // --- Langkah 3: Proses Pembayaran ---
    int pilihanBayar;
    int bayarSukses = 0;

    printf("\nPilih Metode Pembayaran:\n");
    printf("1. Cash\n");
    printf("2. QRIS\n");
    printf("3. Debit\n");
    printf("Pilihan Anda [1-3]: ");
    scanf("%d", &pilihanBayar);

    switch(pilihanBayar) {
        case 1: // Cash
            {
                long long uangCash = 0;
                printf("Masukkan Jumlah Uang Tunai (Cash): Rp ");
                scanf("%lld", &uangCash);

                if (uangCash < totalTagihan) {
                    printf("\nUang tunai tidak cukup! (Kurang Rp %lld)\n", totalTagihan - uangCash);
                    printf("Pembayaran Gagal.\n");
                } else {
                    long long kembalian = uangCash - totalTagihan;
                    printf("\nUang Diterima : Rp %lld\n", uangCash);
                    printf("Kembalian     : Rp %lld\n", kembalian);
                    bayarSukses = 1;
                }
                break;
            }
        case 2: // QRIS
            printf("\nSilakan scan QRIS sejumlah Rp %lld...\n", totalTagihan);
            printf("Pembayaran dengan QRIS Berhasil!\n");
            bayarSukses = 1;
            break;
        case 3: // Debit
            printf("\nSilakan masukkan kartu Debit...\n");
            printf("Pembayaran dengan Debit (Rp %lld) Berhasil!\n", totalTagihan);
            bayarSukses = 1;
            break;
        default:
            printf("\nMetode pembayaran tidak valid. Pembayaran Gagal.\n");
            break;
    }

    // --- Langkah 4: Selesaikan Transaksi (Jika Bayar Sukses) ---
    if (bayarSukses == 1) {
        printf("\n--- PEMBAYARAN LUNAS ---\n");
        printf("Terima kasih, %s! Mobil %s selesai diservis.\n",
            daftarMobil[indexMobil].namaPelanggan,
            daftarMobil[indexMobil].platNomor);

        // Hapus mobil dari antrian
        for (int i = indexMobil; i < jumlahMobilSekarang - 1; i++) {
            daftarMobil[i] = daftarMobil[i + 1];
        }
        jumlahMobilSekarang--;

        printf("Mobil telah dikeluarkan dari antrian.\n");
    }

    pauseScreen();
}

void menuStruk() {
    int pilihan = 0;
    do {
        system("cls");
        printf("=== MENU STRUK & PEMBAYARAN ===\n");
        printf("---------------------------------\n");
        printf("1. Cetak Struk & Proses Pembayaran\n");
        printf("\n9. Kembali ke Menu Utama\n");
        printf("---------------------------------\n");
        printf("Pilihan Anda [1, 9]: ");

        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1:
                prosesPembayaran();
                break;
            case 9:
                break;
            default:
                printf("Pilihan tidak valid.\n");
                Sleep(1000);
        }
    } while (pilihan != 9);
}

// --- FUNGSI MENU 5 & 6 (Pola Dinamis) ---

void menuRumahPola() {
    system("cls");
    printf("=== MENU RUMAH POLA DINAMIS ===\n");
    printf("-------------------------------\n");
    int tinggiAtap;
    printf("Masukkan tinggi atap (misal 5): ");
    scanf("%d", &tinggiAtap);
    if (tinggiAtap < 3) {
        printf("Tinggi minimal adalah 3 agar berbentuk.\n");
        tinggiAtap = 3;
        Sleep(1000);
    }
    printf("\n");
    for (int i = 1; i <= tinggiAtap; i++) {
        for (int j = 0; j < (tinggiAtap - i); j++) printf(" ");
        for (int k = 0; k < (2 * i - 1); k++) printf("*");
        printf("\n");
    }
    int lebarDasar = 2 * tinggiAtap - 1;
    int tinggiDasar = tinggiAtap;
    for (int i = 0; i < tinggiDasar; i++) {
        for (int j = 0; j < lebarDasar; j++) printf("*");
        printf("\n");
    }
    pauseScreen();
}

void menuBendera() {
    system("cls");
    printf("=== MENU BENDERA DINAMIS (Indonesia) ===\n");
    printf("------------------------------------------\n");
    int tinggi, lebar;
    printf("Masukkan tinggi bendera (total, min 4): ");
    scanf("%d", &tinggi);
    printf("Masukkan lebar bendera (min 5): ");
    scanf("%d", &lebar);
    if (tinggi < 4) tinggi = 4;
    if (lebar < 5) lebar = 5;
    int tinggiMerah = tinggi / 2;
    int tinggiPutih = tinggi - tinggiMerah;
    printf("\n");
    printf(" TIANG | BENDERA\n");
    printf("   | \n");
    for (int i = 0; i < tinggiMerah; i++) {
        printf("   | ");
        for (int j = 0; j < lebar; j++) printf("*");
        printf("\n");
    }
    for (int i = 0; i < tinggiPutih; i++) {
        printf("   | ");
        for (int j = 0; j < lebar; j++) printf(" ");
        printf("\n");
    }
    printf("   | \n");
    printf(" __|__ \n");
    pauseScreen();
}


// --- Fungsi Menu Utama (Navigator) ---

void mainMenu() {
    int pilihan = 0;
    do {
        system("cls");
        printf("=== MENU UTAMA SISTEM BENGKEL ===\n");
        printf("-----------------------------------\n");
        printf("1. Manajemen Jasa & Spare Part\n");
        printf("2. Input Service Mobil\n");
        printf("3. Penambahan Jasa & Spare Part (ke Mobil)\n");
        printf("4. Struk & Pembayaran\n");
        printf("5. Rumah Pola\n");
        printf("6. Bendera\n");
        printf("\n99. Logout dan Keluar\n");
        printf("-----------------------------------\n");
        printf("Pilihan Anda [1-6, 99]: ");
        scanf("%d", &pilihan);
        switch (pilihan) {
            case 1: menuManajemenData(); break;
            case 2: menuServiceMobil(); break;
            case 3: menuTambahLayanan(); break;
            case 4: menuStruk(); break; // <-- Sudah diupdate
            case 5: menuRumahPola(); break;
            case 6: menuBendera(); break;
            case 99:
                printf("\nAnda memilih keluar...\n");
                printf("Terima kasih telah menggunakan sistem ini. Sampai jumpa!\n");
                Sleep(1500);
                break;
            default:
                printf("\nPilihan tidak valid. Silakan coba lagi.\n");
                Sleep(1000);
                break;
        }
    } while (pilihan != 99);
}


// --- Fungsi Main (Titik Awal Program) ---

int main() {
    int isLoggedIn = 0;
    int pilihanMenuAwal;

    loadingAnimation();

    while (isLoggedIn == 0) {
        system("cls");
        printf("=== SELAMAT DATANG ===\n");
        printf("1. Login\n");
        printf("2. Buat Akun Baru (Registrasi)\n");
        printf("3. Keluar dari Program\n");
        printf("-----------------------\n");
        printf("Pilihan Anda [1-3]: ");

        scanf("%d", &pilihanMenuAwal);
        switch (pilihanMenuAwal) {
            case 1:
                if (jumlahAkunSekarang == 0) {
                    printf("\nBelum ada akun terdaftar. Buat akun baru dulu.\n");
                    Sleep(2000);
                } else {
                    isLoggedIn = loginSystem();
                }
                break;
            case 2:
                registerSystem();
                break;
            case 3:
                printf("\nTerima kasih telah menggunakan sistem ini.\n");
                return 0;
            default:
                printf("\nPilihan tidak valid. Silakan coba lagi.\n");
                Sleep(1500);
                break;
        }
    }

    if(isLoggedIn) {
        mainMenu();
    }

    return 0;
}
