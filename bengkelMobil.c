#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define RESET     "\x1b[0m"
#define MERAH     "\x1b[41m"
#define PUTIH     "\x1b[47m"
#define KARAKTER_BENDERA ' '
#define JEDA_MS 40
#define LEBAR_MULTIPLIER 7

#define MAX 100
#define MAX_AKUN 100
#define MAX_QUEUE 50

void menuUtama (void);
void programBendera (void);

struct Akun {
    char username[50];
    char password[50];
};

struct Akun daftarAkun[MAX_AKUN];
int jumlahAkunSekarang = 0;

struct sparePart{
    char nama[50];
    int stok;
    int harga;
} spareParts[MAX];

struct jasa{
    char jenis[50];
    int harga;
}jasaList[MAX];

int totalSparepart= 2;
int totalJasa = 2;

typedef struct {
    char namaItem[50];
    int jumlah;
    int harga;
} OrderItem;

typedef struct {
    char namaCustomer[100];
    char plat[30];
    char jenisMobil[50];
} Mobil;

typedef struct {
    int id;
    int totalItem;
    OrderItem items[100];
    int totalHarga;
    int paid;
    Mobil mobil;
} Order;

Order orders[MAX];
int totalOrders = 0;
int nextOrderID = 1;

int queueLimit = MAX_QUEUE;

void bersihkan_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void loading() {
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

void buatAkun() {
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

void login(){
    char username[25], password[25];

    while (1){
        system("cls");
        printf("==========================================\n");
        printf("                   LOGIN                  \n");
        printf("==========================================\n\n");

        printf("Username : \n");
        printf("Password : \n\n");
        
        printf("==========================================\n");

        printf("\033[5;1H");
        printf("Username : ");
        scanf("%s", username);

        printf("\033[6;1H");
        printf("Password : ");
        scanf("%s", password);


        if (strcmp(username, "udin") == 0 && strcmp(password, "gokil") == 0) {
            printf("\n\n\nLogin berhasil!\n");
            printf("Mengalihkan ke Menu Utama...");
            Sleep(2000);
            system("cls");
            break;
        } else {
            printf("\nUsername atau Password salah!\n");
            printf("Tekan Enter untuk mencoba lagi...");
            getch();
        }
    }
}

void listMenu(){
    system("cls");
    printf("==================LIST SPAREPART DAN JASA BENGKEL==================\n\n");

    printf(">>> SPAREPART <<<\n");
    printf("-------------------------------------------------------------------\n");
    printf("| %-3s | %-30s | %-6s | %-15s |\n",
           "No", "Nama Sparepart", "Stok", "Harga");
    printf("-------------------------------------------------------------------\n");

    if (totalSparepart == 0) {
        printf("| %-63s |\n", "Belum ada data Sparepart");
    } else {
        for (int i = 0; i < totalSparepart; i++) {
            printf("| %-3d | %-30s | %-6d | Rp %-12d |\n",
                   i + 1,
                   spareParts[i].nama,
                   spareParts[i].stok,
                   spareParts[i].harga
                  );
        }
    }
    printf("-------------------------------------------------------------------\n\n");

    printf(">>> JASA <<<\n");
    printf("-------------------------------------------------------------------\n");
    printf("| %-3s | %-39s | %-15s |\n",
           "No", "Jenis Pelayanan", "Harga");
    printf("-------------------------------------------------------------------\n");

    if (totalJasa == 0) {
        printf("| %-63s |\n", "Belum ada data Pelayanan");
    } else {
        for (int i = 0; i < totalJasa; i++) {
            printf("| %-3d | %-39s | Rp %-12d |\n",
                   i + 1,
                   jasaList[i].jenis,
                   jasaList[i].harga
                  );
        }
    }
    printf("-------------------------------------------------------------------\n");
    printf("Tekan Enter untuk kembali ke Menu Utama...");
    getch();
}

void listDefault(){
    strcpy(spareParts[0].nama, "Oli Mesin");
    spareParts[0].stok = 15;
    spareParts[0].harga = 75000;

    strcpy(spareParts[1].nama, "Kampas Rem");
    spareParts[1].stok = 10;
    spareParts[1].harga = 110000;

    totalSparepart = 2;
    
    strcpy(jasaList[0].jenis, "Service Berkala");
    jasaList[0].harga = 150000;

    strcpy(jasaList[1].jenis, "Tune Up");
    jasaList[1].harga = 100000;

    totalJasa = 2;
}

void tambahList() {
    int pilih;
    char ulang;

    while (1) {
        system ("cls");
        printf("==============TAMBAH LIST SPAREPART DAN JASA BENGKEL==============\n\n");
        printf("Apa yang akan ditambahkan?\n");
        printf("1. Sparepart\n");
        printf("2. Layanan Jasa\n");
        printf("3. Kembali\n");
        printf("Pilih opsi : ");
        scanf("%d", &pilih);
        getchar();

        if (pilih == 1) {
            do {
                system("cls");
                printf("=== TAMBAH SPAREPART ===\n");
                printf("Nama Sparepart : ");
                fgets(spareParts[totalSparepart].nama, 50, stdin);
                spareParts[totalSparepart].nama[strcspn(spareParts[totalSparepart].nama, "\n")] = 0;

                printf("Stok        : ");
                scanf("%d", &spareParts[totalSparepart].stok);

                printf("Harga       : ");
                scanf("%d", &spareParts[totalSparepart].harga);

                totalSparepart++;

                getchar();
                printf("\nData sparepart berhasil ditambahkan!\n");
                
                printf("Ingin menambahkan lagi? (Y/N) : ");
                scanf("%c", &ulang);
                getchar();

                if (ulang == 'N' || ulang == 'n') {
                    return;
                }
            } while (ulang == 'Y' || ulang == 'y');
        }

        else if (pilih == 2) {
            do {
                system("cls");
                printf("=== TAMBAH JASA ===\n");
                printf("Jenis Pelayanan : ");
                fgets(jasaList[totalJasa].jenis, 50, stdin);
                jasaList[totalJasa].jenis[strcspn(jasaList[totalJasa].jenis, "\n")] = 0;
    
                printf("Harga       : ");
                scanf("%d", &jasaList[totalJasa].harga);

                totalJasa++;

                getchar();
                printf("\nData jasa berhasil ditambahkan!\n");
            
                printf("Ingin menambahkan lagi? (Y/N) : ");
                scanf("%c", &ulang);
                getchar();

                if (ulang == 'N' || ulang == 'n') {
                    return;
                }
            } while (ulang == 'Y' || ulang == 'y');
        }

        else if (pilih == 3) {
            printf("\nMengalihkan ke Menu Utama...");
            Sleep(2000);
            system("cls");
            return;
        }

        else {
            printf("Pilihan tidak valid!\n");
            system("pause");
        }
    }
}

void editList() {
    int pilih;
    system("cls");
    printf("==================== EDIT DATA ====================\n\n");
    printf("Pilih jenis data yang ingin diedit:\n");
    printf("1. Sparepart\n");
    printf("2. Jasa Pelayanan\n");
    printf("3. Kembali\n");
    printf("Pilihan: ");
    scanf("%d", &pilih);
    getchar();

    if (pilih == 1) {
        int nomor;
        system("cls");
        printf("=============== EDIT SPAREPART ===============\n\n");

        if (totalSparepart == 0) {
            printf("Belum ada data sparepart.\n");
            getch();
            return;
        }

        for (int i = 0; i < totalSparepart; i++) {
            printf("%d. %s | Stok: %d | Harga: Rp %d\n",
                i + 1,
                spareParts[i].nama,
                spareParts[i].stok,
                spareParts[i].harga
            );
        }

        printf("\nPilih nomor sparepart yang akan diedit: ");
        scanf("%d", &nomor);
        getchar();

        if (nomor < 1 || nomor > totalSparepart) {
            printf("Nomor tidak valid!\n");
            getch();
            return;
        }
        nomor--;

        char namaBaru[50];
        int stokBaru, hargaBaru;

        printf("\nNama baru (enter untuk tidak ubah): ");
        fgets(namaBaru, sizeof(namaBaru), stdin);
        namaBaru[strcspn(namaBaru, "\n")] = 0;
        if (strlen(namaBaru) > 0)
            strcpy(spareParts[nomor].nama, namaBaru);

        printf("Stok baru (0 = tidak ubah): ");
        scanf("%d", &stokBaru);
        if (stokBaru > 0)
            spareParts[nomor].stok = stokBaru;

        printf("Harga baru (0 = tidak ubah): ");
        scanf("%d", &hargaBaru);
        if (hargaBaru > 0)
            spareParts[nomor].harga = hargaBaru;

        printf("\nSparepart berhasil diperbarui!\n");
        getch();
    }
    else if (pilih == 2) {
        int nomor;
        system("cls");
        printf("=============== EDIT JASA ===============\n\n");

        if (totalJasa == 0) {
            printf("Belum ada data jasa.\n");
            getch();
            return;
        }

        for (int i = 0; i < totalJasa; i++) {
            printf("%d. %s | Harga: Rp %d\n",
                i + 1,
                jasaList[i].jenis,
                jasaList[i].harga
            );
        }

        printf("\nPilih nomor jasa yang akan diedit: ");
        scanf("%d", &nomor);
        getchar();

        if (nomor < 1 || nomor > totalJasa) {
            printf("Nomor tidak valid!\n");
            getch();
            return;
        }
        nomor--;

        char jenisBaru[50];
        int hargaBaru;

        printf("\nJenis jasa baru (enter untuk tidak ubah): ");
        fgets(jenisBaru, sizeof(jenisBaru), stdin);
        jenisBaru[strcspn(jenisBaru, "\n")] = 0;
        if (strlen(jenisBaru) > 0)
            strcpy(jasaList[nomor].jenis, jenisBaru);

        printf("Harga baru (0 = tidak ubah): ");
        scanf("%d", &hargaBaru);
        if (hargaBaru > 0)
            jasaList[nomor].harga = hargaBaru;

        printf("\nJasa berhasil diperbarui!\n");
        getch();
    }

    else if (pilih == 3) {
        return;
    }

    else {
        printf("Pilihan tidak valid!\n");
        getch();
    }
}

void hapusList() {
    int pilih;
    system("cls");
    printf("==================== HAPUS DATA ====================\n\n");
    printf("Pilih jenis data yang ingin dihapus:\n");
    printf("1. Sparepart\n");
    printf("2. Jasa Pelayanan\n");
    printf("3. Kembali\n");
    printf("Pilihan: ");
    scanf("%d", &pilih);

    if (pilih == 1) {
        int nomor;
        system("cls");
        printf("=============== HAPUS SPAREPART ===============\n\n");

        if (totalSparepart == 0) {
            printf("Belum ada data sparepart.\n");
            getch();
            return;
        }

        for (int i = 0; i < totalSparepart; i++) {
            printf("%d. %s | Stok: %d | Harga: Rp %d\n",
                   i + 1,
                   spareParts[i].nama,
                   spareParts[i].stok,
                   spareParts[i].harga);
        }

        printf("\nMasukkan nomor sparepart yang ingin dihapus: ");
        scanf("%d", &nomor);

        if (nomor < 1 || nomor > totalSparepart) {
            printf("Nomor tidak valid!\n");
            getch();
            return;
        }

        nomor--;

        for (int i = nomor; i < totalSparepart - 1; i++) {
            spareParts[i] = spareParts[i + 1];
        }

        totalSparepart--;

        printf("\nSparepart berhasil dihapus!\n");
        getch();
    }

    else if (pilih == 2) {
        int nomor;
        system("cls");
        printf("=============== HAPUS JASA ===============\n\n");

        if (totalJasa == 0) {
            printf("Belum ada data jasa.\n");
            getch();
            return;
        }

        for (int i = 0; i < totalJasa; i++) {
            printf("%d. %s | Harga: Rp %d\n",
                   i + 1,
                   jasaList[i].jenis,
                   jasaList[i].harga);
        }

        printf("\nMasukkan nomor jasa yang ingin dihapus: ");
        scanf("%d", &nomor);

        if (nomor < 1 || nomor > totalJasa) {
            printf("Nomor tidak valid!\n");
            getch();
            return;
        }

        nomor--;

        for (int i = nomor; i < totalJasa - 1; i++) {
            jasaList[i] = jasaList[i + 1];
        }

        totalJasa--;

        printf("\nJasa berhasil dihapus!\n");
        getch();
    }

    else if (pilih == 3) {
        return;
    }

    else {
        printf("\nPilihan tidak valid!\n");
        getch();
    }
}

void pemesananJasa() {
    system("cls");

    if (totalOrders >= MAX) {
        printf("Antrian penuh. Tidak bisa menambah pesanan.\n");
        getch();
        return;
    }

    Order *o = &orders[totalOrders];
    o->id = nextOrderID++;
    o->totalItem = 0;
    o->totalHarga = 0;
    o->paid = 0;

    getchar();

    printf("=== DATA PEMESANAN JASA PERBAIKAN ===\n");


    int pilih, jumlah;

    while (1) {
        system("cls");
        printf("=== PEMESANAN JASA PERBAIKAN (ID %d) ===\n", o->id);
        printf("1. Pilih Sparepart\n");
        printf("2. Pilih Jasa\n");
        printf("3. Selesai\n");
        printf("Pilih: ");
        if (scanf("%d", &pilih) != 1) { while(getchar()!='\n'); continue; }

        if (pilih == 1) {
            for (int i = 0; i < totalSparepart; i++) {
                printf("%d. %s (Rp %d) | Stok: %d\n", i+1, spareParts[i].nama, spareParts[i].harga, spareParts[i].stok);
            }

            printf("Pilih sparepart: ");
            int sp;
            scanf("%d", &sp);
            if (sp < 1 || sp > totalSparepart) continue;

            printf("Jumlah: ");
            scanf("%d", &jumlah);
            if (jumlah <= 0) continue;
            if (jumlah > spareParts[sp-1].stok) {
                printf("Stok tidak cukup. Stok tersedia: %d\n", spareParts[sp-1].stok);
                getch();
                continue;
            }

            spareParts[sp-1].stok -= jumlah;

            strcpy(o->items[o->totalItem].namaItem, spareParts[sp-1].nama);
            o->items[o->totalItem].jumlah = jumlah;
            o->items[o->totalItem].harga = spareParts[sp-1].harga * jumlah;

            o->totalHarga += o->items[o->totalItem].harga;
            o->totalItem++;
        }

        else if (pilih == 2) {
            for (int i = 0; i < totalJasa; i++) {
                printf("%d. %s (Rp %d)\n", i+1, jasaList[i].jenis, jasaList[i].harga);
            }

            printf("Pilih jasa: ");
            int js;
            scanf("%d", &js);
            if (js < 1 || js > totalJasa) continue;

            strcpy(o->items[o->totalItem].namaItem, jasaList[js-1].jenis);
            o->items[o->totalItem].jumlah = 1;
            o->items[o->totalItem].harga = jasaList[js-1].harga;

            o->totalHarga += o->items[o->totalItem].harga;
            o->totalItem++;
        }

        else break;
    }

    if (o->totalItem == 0) {
        printf("Pesanan kosong. Dibatalkan!\n");
        getch();
        return;
    }

    totalOrders++;
    printf("Pesanan dibuat! ID: %d | Total: Rp %d\n", o->id, o->totalHarga);
    getch();
}

void tambahanPesanan() {
    if (totalOrders == 0) {
        printf("Belum ada pesanan!\n");
        getch();
        return;
    }

    int id;
    printf("Masukkan ID Pesanan: ");
    scanf("%d", &id);

    int idx = -1;
    for (int i = 0; i < totalOrders; i++) {
        if (orders[i].id == id) { idx = i; break; }
    }

    if (idx == -1) {
        printf("ID tidak ditemukan!\n");
        getch();
        return;
    }

    Order *o = &orders[idx];

    if (o->paid == 1) {
        printf("Pesanan sudah dibayar!\n");
        getch();
        return;
    }

    int pilih, jumlah;

    while (1) {
        system("cls");
        printf("=== TAMBAH PESANAN (ID %d) ===\n", id);
        printf("1. Tambah Sparepart\n");
        printf("2. Tambah Jasa\n");
        printf("3. Selesai\n");
        printf("Pilih: ");
        if (scanf("%d", &pilih) != 1) { while(getchar()!='\n'); continue; }

        if (pilih == 1) {
            for (int i = 0; i < totalSparepart; i++)
                printf("%d. %s (Rp %d) | Stok: %d\n", i+1, spareParts[i].nama, spareParts[i].harga, spareParts[i].stok);

            int sp;
            printf("Pilih sparepart: ");
            scanf("%d", &sp);

            if (sp < 1 || sp > totalSparepart) continue;

            printf("Jumlah: ");
            scanf("%d", &jumlah);
            if (jumlah <= 0) continue;
            if (jumlah > spareParts[sp-1].stok) {
                printf("Stok tidak cukup. Stok tersedia: %d\n", spareParts[sp-1].stok);
                getch();
                continue;
            }

            spareParts[sp-1].stok -= jumlah;

            strcpy(o->items[o->totalItem].namaItem, spareParts[sp-1].nama);
            o->items[o->totalItem].jumlah = jumlah;
            o->items[o->totalItem].harga = spareParts[sp-1].harga * jumlah;

            o->totalHarga += o->items[o->totalItem].harga;
            o->totalItem++;
        }

        else if (pilih == 2) {
            for (int i = 0; i < totalJasa; i++)
                printf("%d. %s (Rp %d)\n", i+1, jasaList[i].jenis, jasaList[i].harga);

            int js;
            printf("Pilih jasa: ");
            scanf("%d", &js);

            if (js < 1 || js > totalJasa) continue;

            strcpy(o->items[o->totalItem].namaItem, jasaList[js-1].jenis);
            o->items[o->totalItem].jumlah = 1;
            o->items[o->totalItem].harga = jasaList[js-1].harga;

            o->totalHarga += o->items[o->totalItem].harga;
            o->totalItem++;
        }

        else break;
    }

    printf("Total terbaru: Rp %d\n", o->totalHarga);
    getch();
}

void inputMobilServis() {
    int currentQueue = 0;
    for (int i = 0; i < totalOrders; i++) {
        if (orders[i].paid == 0) currentQueue++;
    }

    if (currentQueue >= queueLimit) {
        printf("Antrian penuh (%d/%d). Tidak dapat menambah mobil.\n", currentQueue, queueLimit);
        getch();
        return;
    }

    if (totalOrders >= MAX) {
        printf("Batas penyimpanan pesanan tercapai.\n");
        getch();
        return;
    }

    Order *o = &orders[totalOrders];
    o->id = nextOrderID++;
    o->totalItem = 0;
    o->totalHarga = 0;
    o->paid = 0;

    o->mobil.namaCustomer[0] = '\0';
    o->mobil.plat[0] = '\0';
    o->mobil.jenisMobil[0] = '\0';

    getchar();

    system("cls");
    printf("=== INPUT MOBIL SERVIS BARU ===\n");
    printf("Nama Pelanggan: ");
    fgets(o->mobil.namaCustomer, sizeof(o->mobil.namaCustomer), stdin);
    o->mobil.namaCustomer[strcspn(o->mobil.namaCustomer, "\n")] = 0;

    printf("Plat Nomor: ");
    fgets(o->mobil.plat, sizeof(o->mobil.plat), stdin);
    o->mobil.plat[strcspn(o->mobil.plat, "\n")] = 0;

    printf("Jenis Mobil: ");
    fgets(o->mobil.jenisMobil, sizeof(o->mobil.jenisMobil), stdin);
    o->mobil.jenisMobil[strcspn(o->mobil.jenisMobil, "\n")] = 0;


    totalOrders++;

   
    currentQueue = 0;
    for (int i = 0; i < totalOrders; i++) if (orders[i].paid == 0) currentQueue++;

    printf("\nData mobil baru berhasil disimpan!\n");
    printf("Antrian saat ini: %d / %d\n", currentQueue, queueLimit);
    printf("Tekan Enter untuk kembali ke menu...");
    getchar();
}


void lihatAntrian() {
    system("cls");
    printf("=== LIHAT ANTRIAN MOBIL SERVIS ===\n\n");

    int currentQueue = 0;
    for (int i = 0; i < totalOrders; i++) {
        if (orders[i].paid == 0) {
            currentQueue++;
            printf("ID Pesanan : %d\n", orders[i].id);
            if (strlen(orders[i].mobil.namaCustomer) > 0)
                printf("Customer   : %s\n", orders[i].mobil.namaCustomer);
            if (strlen(orders[i].mobil.plat) > 0)
                printf("Plat       : %s\n", orders[i].mobil.plat);
            if (strlen(orders[i].mobil.jenisMobil) > 0)
                printf("Mobil      : %s\n", orders[i].mobil.jenisMobil);
            printf("----------------------------------\n");
        }
    }

    printf("\nAntrian saat ini: %d / %d\n", currentQueue, queueLimit);
    printf("Tekan Enter untuk kembali...");
    getchar();
    getch();
}
void menuInputService() {
    int pilih;
    do {
        system("cls");
        printf("=== MENU INPUT SERVICE MOBIL ===\n");
        printf("1. Input Mobil Servis Baru\n");
        printf("2. Lihat Antrian Mobil Servis\n");
        printf("9. Kembali ke Menu Utama\n");
        printf("Pilihan Anda [1, 2, 9]: ");
        if (scanf("%d", &pilih) != 1) { while(getchar()!='\n'); continue; }

        getchar(); 
        if (pilih == 1) inputMobilServis();
        else if (pilih == 2) lihatAntrian();
        else if (pilih == 9) break;
        else {
            printf("Pilihan tidak valid.\n");
            getch();
        }
    } while (1);
}

void cetak_baris_bendera_animasi(int lebar, char *warna) {
    printf("%s", warna);
    fflush(stdout);

    for (int j = 0; j < lebar; j++) {
        printf("%c", KARAKTER_BENDERA);
        fflush(stdout);
        Sleep(JEDA_MS);
    }
    printf("%s\n", RESET);
    fflush(stdout);
}

void cetak_bendera_loading(int tinggi_input) {

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    if (tinggi_input <= 0) tinggi_input = 1;

    int tinggi_merah = tinggi_input;
    int tinggi_putih = tinggi_input;

    int tinggi_total_sebenarnya = tinggi_merah + tinggi_putih;


    int lebar_bendera = tinggi_total_sebenarnya * LEBAR_MULTIPLIER / 2;

    printf("================== Bendera Jaya ==================\n");
    printf("Tinggi input: %d | Tinggi total: %d | Lebar: %d\n", tinggi_input, tinggi_total_sebenarnya, lebar_bendera);
    printf("--- Merah: %d baris, Putih: %d baris ---\n", tinggi_merah, tinggi_putih);
    printf("-------------------------------------------------------\n");


    for (int i = 0; i < tinggi_merah; i++) {
        cetak_baris_bendera_animasi(lebar_bendera, MERAH);
    }


    for (int i = 0; i < tinggi_putih; i++) {
        cetak_baris_bendera_animasi(lebar_bendera, PUTIH);
    }

    printf("\n=======================================================\n");
}

void programBendera() {
    system("cls");
    int tinggi = 0;
    char pilihan;

    printf(">>> PROGRAM BENDERA MERAH PUTIH <<<\n\n");

    do {
        printf("Masukkan Tinggi Bendera : ");
        if (scanf("%d", &tinggi) != 1) {
            printf("Input Tinggi tidak valid. Coba lagi.\n");
            bersihkan_input_buffer();
            tinggi = 0;
        }
    } while (tinggi <= 0);

    bersihkan_input_buffer();

    do {
        cetak_bendera_loading(tinggi);

        printf("Masukkan pilihan (U: Ulang, X: Keluar): ");
        if (scanf(" %c", &pilihan) != 1) {
            bersihkan_input_buffer();
            pilihan = ' ';
        }

        if (pilihan == 'U' || pilihan == 'u') {
            bersihkan_input_buffer();

             do {
                printf("Masukkan Tinggi Per Bagian (Merah & Putih): ");
                if (scanf("%d", &tinggi) != 1 || tinggi <= 0) {
                    printf("Input Tinggi tidak valid atau nol. Coba lagi.\n");
                    bersihkan_input_buffer();
                }
            } while (tinggi <= 0);
            bersihkan_input_buffer();

        } else if (pilihan == 'X' || pilihan == 'x') {
            return;
        } else {
            printf("\nPilihan tidak dikenali. Tekan ENTER untuk kembali ke menu.\n");
            bersihkan_input_buffer();
            getchar();
        }

    } while (1);
 
}

void menuUtama() {
    int pil;

    do {
        system("cls");

        printf("==============================================\n");
        printf("             SISTEM BENGKEL MOBIL             \n");
        printf("  Selamat Datang! Perlu apa? Silakan dipilih  \n");
        printf("==============================================\n");
        printf("1. Lihat List Sparepart dan Jasa\n");
        printf("2. Tambah List Sparepart dan Jasa\n");
        printf("3. Edit List Sparepart dan Jasa\n");
        printf("4. Hapus Sparepart dan Jasa\n");
        printf("5. Pemesanan Jasa Perbaikan\n");
        printf("6. Tambahan Pesanan\n");
        printf("7. Cetak Struk\n");
        printf("8. Pembayaran\n");
        printf("9. Rumah Pola\n");
        printf("10. Bendera\n");
        printf("11. Exit\n");
        printf("==============================================\n");
        printf("Pilih Menu : ");
        scanf("%d", &pil);

        switch(pil) {
            case 1: 
                listMenu();
                system("pause");
                break;
            case 2: 
                tambahList();
                system("pause");
                break;
            case 3:
                editList();
                system("pause");
                break;
            case 4:
                hapusList();
                system("pause");
                break;
            case 5:
                pemesananJasa();
                system("pause");
                break;
            case 6: 
                tambahanPesanan();
                system("pause");
                break;
            case 7: printf(">> Cetak Struk\n"); system("pause"); break;
            case 8: printf(">> Pembayaran\n"); system("pause"); break;
            case 9:
                system("pause");
                break;
            case 10:
            programBendera();
            system("pause");
            break;
            case 11: 
                printf("Terima kasih!\n");
                exit(0);
            default:
                printf("Pilihan tidak valid!\n");
                system("pause");
        }
    } while(1);
}

int main() {
    listDefault();
    login();       
    menuUtama();
    return 0;
}