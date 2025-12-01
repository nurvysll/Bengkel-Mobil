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

#define BIRU 1
#define ABU 8
#define KUNING 14
#define UNGU 13
#define DEFAULT 12

#define MAX 100
#define MAX_AKUN 100
#define MAX_QUEUE 50

struct sparePart {
    char nama[50];
    int stok;
    int harga;
} spareParts[MAX];

struct jasa {
    char jenis[50];
    int harga;
} jasaList[MAX];

int totalSparepart = 2;
int totalJasa = 2;

typedef struct {
    char namaItem[50];
    int jumlah;
    int harga;
} OrderItem;

typedef struct {
    char namaCustomer[50];
    char plat[20];
    char jenisMobil[50];
} DataMobil;

typedef struct {
    int id;
    int totalItem;
    OrderItem items[100];
    int totalHarga;
    int paid;
    DataMobil mobil;
} Order;

Order orders[MAX];
int totalOrders = 0;
int nextOrderID = 1;

int queueLimit = MAX_QUEUE;

void bersihkan_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void login(){
    char username[25], password[25];
    char karakter;

    while (1){
        system("cls");
        printf("\t\t\t\t==========================================\n");
        printf("\t\t\t\t||                 LOGIN                ||\n");
        printf("\t\t\t\t==========================================\n");
        printf("\t\t\t\t||                                      ||\n");
        printf("\t\t\t\t||  Username :                          ||\n");
        printf("\t\t\t\t||  Password :                          ||\n");
        printf("\t\t\t\t||                                      ||\n");
        printf("\t\t\t\t==========================================\n");

        printf("\033[5;1H");
        printf("\t\t\t\t||  Username : ");
        scanf("%s", username);

        printf("\033[6;1H");
        printf("\t\t\t\t||  Password : ");

        int i = 0;
        while (1) {
            karakter = getch();

            if (karakter == 13) {
                password[i] = '\0';
                break;
            } 
            else if (karakter == 8) {
                if (i > 0) {
                    i--;
                    printf("\b \b");
                }
            } 
            else {
                if (i < 24) {
                    password[i++] = karakter;
                    printf("*");
                }
            }
        }
        if (strcmp(username, "login") == 0 && strcmp(password, "login321") == 0) {
            printf("\n\n\n\t\t\t\tLogin berhasil!\n");
            printf("\t\t\t\tMengalihkan ke Menu Utama...");
            Sleep(1500);
            system("cls");
            break;
        } else {
            printf("\n\n\n\t\t\t\tUsername atau Password salah!\n");
            printf("\t\t\t\tTekan Enter untuk mencoba lagi...");
            getch();
        }
    }
}

void listDefault() {
    strcpy(spareParts[0].nama, "Oli Mesin");
    spareParts[0].stok = 15;
    spareParts[0].harga = 75000;

    strcpy(spareParts[1].nama, "Kampas Rem");
    spareParts[1].stok = 10;
    spareParts[1].harga = 120000;

    strcpy(jasaList[0].jenis, "Service Berkala");
    jasaList[0].harga = 150000;

    strcpy(jasaList[1].jenis, "Tune Up");
    jasaList[1].harga = 200000;
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

void tambahList() {
    int pilih;
    char ulang;

    while (1) {
        system("cls");
        printf("=================== TAMBAH LIST ===================\n");
        printf("Apa yang ingin ditambah?\n");
        printf("1. Sparepart\n");
        printf("2. Jasa\n");
        printf("3. Kembali ke Menu Utama\n");
        printf("===================================================\n");
        printf("Pilihan: ");
        if (scanf("%d", &pilih) != 1){
            while(getchar()!='\n');
            continue;
        }
        getchar();
        if (pilih == 1) {
            do {
                if (totalSparepart >= MAX) {
                    printf("Maksimum sparepart tercapai.\n");
                    getch();
                    break;
                }
                system("cls");
                printf(">>> Tambah Sparepart <<<\n");
                printf("Nama Sparepart: ");
                fgets(spareParts[totalSparepart].nama, 50, stdin);
                spareParts[totalSparepart].nama[strcspn(spareParts[totalSparepart].nama, "\n")] = 0;

                printf("Stok: ");
                scanf("%d", &spareParts[totalSparepart].stok);

                printf("Harga: ");
                scanf("%d", &spareParts[totalSparepart].harga);

                totalSparepart++;

                getchar();
                printf("Data berhasil diupdate!\n");
                printf("Tambah lagi? (Y/N): ");
                scanf("%c", &ulang);
                getchar();

            } while (ulang == 'Y' || ulang == 'y');
        }
        else if (pilih == 2) {
            do {
                if (totalJasa >= MAX) {
                    printf("Maksimum jasa tercapai.\n");
                    getch();
                    break;
                }
                system("cls");
                printf(">>> Tambah Jasa <<<");
                printf("\nNama Jasa: ");
                fgets(jasaList[totalJasa].jenis, 50, stdin);
                jasaList[totalJasa].jenis[strcspn(jasaList[totalJasa].jenis, "\n")] = 0;

                printf("Harga: ");
                scanf("%d", &jasaList[totalJasa].harga);

                totalJasa++;

                getchar();
                printf("Data berhasil diupdate!\n");
                printf("Tambah lagi? (Y/N): ");
                scanf("%c", &ulang);
                getchar();

            } while (ulang == 'Y' || ulang == 'y');
        }
        else if (pilih == 3) {
            return;
        }
        else {
            printf("Pilihan Tidak Valid!");
            Sleep(1000);
            continue;
        };
    }
}

void editList() {
    char ulang;

    while (1) {
        int pilih;
        system("cls");
        printf("==================== EDIT DATA ====================\n");
        printf("Pilih jenis data yang ingin diedit:\n");
        printf("1. Sparepart\n");
        printf("2. Jasa Pelayanan\n");
        printf("3. Kembali ke Menu Utama\n");
        printf("===================================================\n");
        printf("Pilihan : ");
        if (scanf("%d", &pilih) != 1){
            while(getchar()!='\n');
            continue;
        }
        getchar();
        if (pilih == 1) {
            do{
                int nomor;
                system("cls");
                printf(">>> EDIT SPAREPART <<<\n\n");

                if (totalSparepart == 0) {
                    printf("Belum ada data sparepart");
                    Sleep(1000);
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
                    printf("Nomor tidak valid!");
                    Sleep(1000);
                    continue;
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

                printf("\nSparepart berhasil diperbarui!");
                printf("\nIngin mengedit data lagi? (Y/N): ");
                scanf(" %c", &ulang);
                getchar();
            } while (ulang == 'Y' || ulang == 'y');
        }
        else if (pilih == 2) {
            do{
                int nomor;
                system("cls");
                printf(">>> EDIT JASA <<<\n\n");

                if (totalJasa == 0) {
                    printf("Belum ada data jasa!");
                    Sleep(1000);
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
                    printf("Nomor tidak valid!");
                    Sleep(1000);
                    continue;
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

                printf("\nJasa berhasil diperbarui!");
                printf("\nIngin mengedit data lagi? (Y/N): ");
                scanf(" %c", &ulang);
                getchar();
            } while (ulang == 'Y' || ulang == 'y');
        } 
        else if (pilih == 3) {
            return;
        }
        else {
            printf("Pilihan tidak valid!");
            Sleep(1000);
            continue;
        };
    } 
}
void hapusList() {
    char ulang;
    while (1) {
        int pilih;
        system("cls");
        printf("==================== HAPUS DATA ====================\n");
        printf("Pilih jenis data yang ingin dihapus:\n");
        printf("1. Sparepart\n");
        printf("2. Jasa Pelayanan\n");
        printf("3. Kembali ke Menu Utama\n");
        printf("====================================================\n");
        printf("Pilihan: ");
        if (scanf("%d", &pilih) != 1){
            while(getchar()!='\n');
            continue;
        }
        getchar();
        if (pilih == 1) {
            do{
                int nomor;
                char konfirmasi;

                system("cls");
                printf(">>> HAPUS SPAREPART <<<\n\n");

                if (totalSparepart == 0) {
                    printf("Belum ada data sparepart!");
                    Sleep(1000);
                    continue;
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
                    printf("Nomor tidak valid!");
                    Sleep(1000);
                    continue;
                }

                nomor--;

                printf("\nAnda yakin ingin menghapus data berikut?\n");
                printf("Nama  : %s\n", spareParts[nomor].nama);
                printf("Stok  : %d\n", spareParts[nomor].stok);
                printf("Harga : Rp %d\n", spareParts[nomor].harga);

                printf("\n(Y/N) : ");
                scanf(" %c", &konfirmasi);

                if (konfirmasi == 'Y' || konfirmasi == 'y'){
                    for (int i = nomor; i < totalSparepart - 1; i++){
                        spareParts[i] = spareParts[i + 1];
                    }
                    totalSparepart--;
                
                    printf("\nSparepart berhasil dihapus!");
                } else {
                    printf("\nPenghapusan dibatalkan\n");
                    printf("Tekan Enter untuk Kembali...");
                    getch();
                }
            }while (ulang == 'Y' || ulang == 'y');
        }  
        else if (pilih == 2) {
            do{
                int nomor;
                char konfirmasi;

                system("cls");
                printf(">>> HAPUS JASA <<<\n\n");

                if (totalJasa == 0) {
                    printf("Belum ada data jasa");
                    Sleep(1000);
                    continue;
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
                    printf("Nomor tidak valid!");
                    Sleep(1000);
                    continue;
                }

                nomor--;

                printf("\nAnda yakin ingin menghapus data berikut?\n");
                printf("Jenis  : %s\n", jasaList[nomor].jenis);
                printf("Harga  : Rp %d\n", jasaList[nomor].harga);

                printf("\n(Y/N) : ");
                scanf(" %c", &konfirmasi);

                if (konfirmasi == 'Y' || konfirmasi == 'y'){
                    for (int i = nomor; i < totalJasa - 1; i++){
                        jasaList[i] = jasaList[i + 1];
                    }
                    totalJasa--;
                    printf("\nJasa berhasil dihapus!\n");
                } else {
                    printf("\nPenghapusan dibatalkan\n");
                    printf("Tekan Enter untuk Kembali...");
                    getch();
                }
            }while (ulang == 'Y' || ulang == 'y');
        } 
        else if (pilih == 3) {
            return;
        }
        else {
            printf("\nPilihan tidak valid!");
            Sleep(1000);
            continue;
        };
    }
}

void pemesananJasa(int index) {
    system("cls");

    if (totalOrders >= MAX) {
        printf("Antrian penuh. Tidak bisa menambah pesanan.\n");
        getch();
        return;
    }

    Order *o = &orders[index];
    o->totalItem = 0;
    o->totalHarga = 0;
    o->paid = 0;

    int pilih, jumlah;

    while (1) {
        system("cls");
        printf(">>> PEMESANAN JASA PERBAIKAN (ID %d) <<<\n", o->id);
        printf("1. Pilih Sparepart\n");
        printf("2. Pilih Jasa\n");
        printf("3. Selesai\n");
        printf("Pilih: ");
        if (scanf("%d", &pilih) != 1) { while(getchar()!='\n'); continue; }

        if (pilih == 1) {
            system("cls");
            for (int i = 0; i < totalSparepart; i++) {
                printf("%d. %s (Rp %d) | Stok: %d\n", i+1, spareParts[i].nama, spareParts[i].harga, spareParts[i].stok);
            }

            printf("\nPilih sparepart: ");
            int sp;
            scanf("%d", &sp);
            if (sp < 1 || sp > totalSparepart) {
                printf("Data Sparepart tidak ditemukan!");
                Sleep(1500);   
                continue;;
            }
            printf("Jumlah: ");
            scanf("%d", &jumlah);
            if (jumlah <= 0) continue;
            if (jumlah > spareParts[sp-1].stok) {
                printf("Stok tidak cukup. Stok tersedia: %d", spareParts[sp-1].stok);
                printf("\nTekan Enter untuk coba lagi...");
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
            system("cls");
            for (int i = 0; i < totalJasa; i++) {
                printf("%d. %s (Rp %d)\n", i+1, jasaList[i].jenis, jasaList[i].harga);
            }

            printf("\nPilih jasa: ");
            int js;
            scanf("%d", &js);
            if (js < 1 || js > totalJasa) {
                printf("Data Jasa tidak ditemukan!");
                Sleep(1500);
                continue;
            }
            strcpy(o->items[o->totalItem].namaItem, jasaList[js-1].jenis);
            o->items[o->totalItem].jumlah = 1;
            o->items[o->totalItem].harga = jasaList[js-1].harga;

            o->totalHarga += o->items[o->totalItem].harga;
            o->totalItem++;
        }
        else if (pilih == 3) {
            break;
        }
        else {
            printf("Pilihan Tidak Valid!");
            Sleep(1500);
        };
    }

    if (o->totalItem == 0) {
        printf("Pesanan kosong. Pesanan dibatalkan!\n");
        totalOrders--;
        nextOrderID--;
    } else {
        printf("Pesanan dibuat! ID: %d | Total: Rp %d\n", o->id, o->totalHarga);
    }
    printf("Tekan Enter untuk kembali...");
    getch();
}

void inputMobilServis() {
    system("cls");
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
    printf(">>>>  INPUT DATA SERVICE MOBIL  <<<<\n\n");
    printf("Nama Pelanggan           : ");
    fgets(o->mobil.namaCustomer, sizeof(o->mobil.namaCustomer), stdin);
    o->mobil.namaCustomer[strcspn(o->mobil.namaCustomer, "\n")] = 0;

    printf("Plat Nomor (ex : A 123 B): ");
    fgets(o->mobil.plat, sizeof(o->mobil.plat), stdin);
    o->mobil.plat[strcspn(o->mobil.plat, "\n")] = 0;

    printf("Jenis Mobil (ex : Avanza): ");
    fgets(o->mobil.jenisMobil, sizeof(o->mobil.jenisMobil), stdin);
    o->mobil.jenisMobil[strcspn(o->mobil.jenisMobil, "\n")] = 0;

    int index = totalOrders;
    totalOrders++;

    currentQueue = 0;
    for (int i = 0; i < totalOrders; i++) if (orders[i].paid == 0) currentQueue++;

    printf("\nData mobil baru berhasil disimpan!\n");
    printf("Antrian saat ini: %d / %d\n", currentQueue, queueLimit);
    pemesananJasa(index);
}

void lihatAntrian() {
    system("cls");
    printf(">>> LIHAT ANTRIAN MOBIL SERVIS <<<\n\n");

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
    getch();
}
void menuInputService() {
    int pilih;
    do {
        system("cls");
        printf("============= MENU INPUT SERVICE MOBIL =============\n");
        printf("1. Input Mobil Servis Baru\n");
        printf("2. Lihat Antrian Mobil Servis\n");
        printf("3. Kembali ke Menu Utama\n");
        printf("====================================================\n");
        printf("Pilihan : ");
        if (scanf("%d", &pilih) != 1) { while(getchar()!='\n'); continue; }

        if (pilih == 1) inputMobilServis();
        else if (pilih == 2) lihatAntrian();
        else if (pilih == 3) break;
        else {
            printf("Pilihan tidak valid!");
            Sleep(1500);
            continue;
        }
    } while (1);
}

void tambahanPesanan() {
    if (totalOrders == 0) {
        printf("Belum ada pesanan!\n");
        printf("Silakan pesan terlebih dahulu!");
        Sleep(1500);
        return;
    }

    int id;
    system("cls");
    printf(">>> TAMBAH PESANAN <<<");
    printf("\nMasukkan ID Pesanan: ");
    scanf("%d", &id);

    int idx = -1;
    for (int i = 0; i < totalOrders; i++) {
        if (orders[i].id == id) { idx = i; break; }
    }

    if (idx == -1) {
        printf("ID tidak ditemukan!\n");
        printf("Mengalihkan ke Menu Utama...");
        Sleep(1500);
        return;
    }

    Order *o = &orders[idx];

    if (o->paid == 1) {
        printf("Pesanan sudah dibayar!\n");
        printf("Mengalihkan ke Menu Utama...");
        Sleep(1500);
        return;
    }

    int pilih, jumlah;
    char ulang;

    while (1) {
        system("cls");
        printf(">>> TAMBAH PESANAN (ID %d) <<<\n", id);
        printf("1. Tambah Sparepart\n");
        printf("2. Tambah Jasa\n");
        printf("3. Selesai\n");
        printf("Pilih: ");
        if (scanf("%d", &pilih) != 1) { while(getchar()!='\n'); continue; }

        if (pilih == 1) {
            system("cls");
            for (int i = 0; i < totalSparepart; i++)
                printf("%d. %s (Rp %d) | Stok: %d\n", i+1, spareParts[i].nama, spareParts[i].harga, spareParts[i].stok);

            int sp;
            printf("\nPilih sparepart : ");
            scanf("%d", &sp);

            if (sp < 1 || sp > totalSparepart) {
                printf("Data Sparepart tidak ditemukan!");
                Sleep(1500);
                continue;
            }
            printf("Jumlah          : ");
            scanf("%d", &jumlah);
            if (jumlah <= 0) continue;
            if (jumlah > spareParts[sp-1].stok) {
                printf("Stok tidak cukup. Stok tersedia: %d\n", spareParts[sp-1].stok);
                printf("Tekan Enter untuk memilih kembali...");
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
            system("cls");
            for (int i = 0; i < totalJasa; i++)
                printf("%d. %s (Rp %d)\n", i+1, jasaList[i].jenis, jasaList[i].harga);

            int js;
            printf("\nPilih jasa  : ");
            scanf("%d", &js);

            if (js < 1 || js > totalJasa) {
                printf("Data Jasa tidak ditemukan!");
                Sleep(1500);
                continue;
            }
            strcpy(o->items[o->totalItem].namaItem, jasaList[js-1].jenis);
            o->items[o->totalItem].jumlah = 1;
            o->items[o->totalItem].harga = jasaList[js-1].harga;

            o->totalHarga += o->items[o->totalItem].harga;
            o->totalItem++;
        } else if (pilih == 3) {
            break;
        }
        else {
            printf("Pilihan Tidak Valid!");
            Sleep(1000);
            continue;
        }
        printf("\nTotal terbaru: Rp %d\n", o->totalHarga);
        printf("Tekan Enter untuk kembali...");
        getch();
    }
}

void cetakStruk() {
    int id;
    system("cls");
    printf(">>> CETAK STRUK <<<\n");
    printf("Masukkan ID Pesanan: ");
    scanf("%d", &id);

    int idx = -1;
    for (int i = 0; i < totalOrders; i++) {
        if (orders[i].id == id) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("ID tidak ditemukan!\n");
        printf("Mengalihkan ke Menu Utama...");
        Sleep(1500);
        return;
    }

    Order *o = &orders[idx];

    system("cls");
    printf("========== STRUK PEMBAYARAN ==========\n");
    printf("ID Pesanan : %d\n", o->id);

    if (strlen(o->mobil.namaCustomer) > 0)
        printf("Nama       : %s\n", o->mobil.namaCustomer);

    if (strlen(o->mobil.plat) > 0)
        printf("Plat       : %s\n", o->mobil.plat);

    if (strlen(o->mobil.jenisMobil) > 0)
        printf("Mobil      : %s\n", o->mobil.jenisMobil);

    printf("--------------------------------------\n");

    for (int i = 0; i < o->totalItem; i++) {
        printf("%d. %s (x%d)  Rp %d\n",
               i+1,
               o->items[i].namaItem,
               o->items[i].jumlah,
               o->items[i].harga);
    }
    printf("--------------------------------------\n");
    printf("TOTAL HARGA : Rp %d\n", o->totalHarga);
    printf("STATUS      : %s\n", o->paid ? "SUDAH BAYAR" : "BELUM BAYAR");
    printf("======================================\n");

    printf("\nTekan Enter untuk kembali...");
    getch();
}

void pembayaran() {
    int id, idx;
    while (1) {
        system("cls");
        printf(">>> PEMBAYARAN <<<\n");
        printf("Masukkan ID Pesanan: ");
        scanf("%d", &id);

        idx = -1;
        for (int i = 0; i < totalOrders; i++) {
            if (orders[i].id == id) {
                idx = i;
                break;
            }
        }

        if (idx == -1) {
            printf("ID tidak ditemukan!\n");
            printf("Mengalihkan ke Menu Utama...");
            Sleep(1000);
            return;
        }

        if (orders[idx].paid == 1) {
            printf("Pesanan ini sudah dibayar!");
            Sleep(1000);
            return;
        }
        break;
    }
    Order *o = &orders[idx];
    int metode;

    while (1) {
        system("cls");
        printf("Total yang harus dibayar: Rp %d\n", o->totalHarga);
        printf("\n>>> Pilih Metode Pembayaran <<<\n");
        printf("1. CASH\n");
        printf("2. QRIS\n");
        printf("Pilihan: ");
        scanf("%d", &metode);

        if (metode == 1) {
            int bayar;

            do {
                printf("\nMasukkan nominal uang: Rp ");
                scanf("%d", &bayar);

                if (bayar < o->totalHarga) {
                    printf("Uang tidak cukup! Masukkan ulang.\n");
                }
            } while (bayar < o->totalHarga);

            int kembalian = bayar - o->totalHarga;

            printf("\nPembayaran berhasil!\n");
            printf("Kembalian: Rp %d\n", kembalian);
            o->paid = 1;

            printf("Tekan Enter untuk Kembali ke Menu Utama...");
            getch();
            return;
        }
        else if (metode == 2) {
            system("cls");
            printf(">>> QRIS <<<\n\n");
            printf("[      QR CODE DINAMIS      ]\n");
            printf("[===========================]\n");
            printf("[   NOMINAL: Rp %-12d]\n", o->totalHarga);
            printf("[===========================]\n");

            int bayarQR;

            while (1) {
                printf("\nMasukkan nominal pembayaran QRIS (PAS): Rp ");
                scanf("%d", &bayarQR);

                if (bayarQR < o->totalHarga) {
                    printf("Nominal kurang! QRIS harus PAS.\n");
                }
                else if (bayarQR > o->totalHarga) {
                    printf("Nominal berlebih! QRIS harus PAS.\n");
                }
                else {
                    printf("Proses pembayaran QRIS...");
                    Sleep(1500);
                    printf("\n\nPembayaran QRIS berhasil!\n");
                    o->paid = 1;
                    printf("Tekan Enter untuk Kembali ke Menu Utama...");
                    getch();
                    return;
                }
            }
        }
        else {
            printf("Pilihan tidak valid!");
            Sleep(1000);
            continue;
        }
    }
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
    setColor(DEFAULT);
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
    setColor(DEFAULT);
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
        setColor(DEFAULT);

        printf("Masukkan pilihan (U: Ulang, X: Keluar): ");
        if (scanf(" %c", &pilihan) != 1) {
            bersihkan_input_buffer();
            pilihan = ' ';
        }
        if (pilihan == 'U' || pilihan == 'u') {
            bersihkan_input_buffer();
            system("cls");
             do {
                printf("Masukkan Tinggi Per Bagian (Merah & Putih): ");
                if (scanf("%d", &tinggi) != 1 || tinggi <= 0) {
                    printf("Input Tinggi tidak valid atau nol. Coba lagi.\n");
                    bersihkan_input_buffer();
                }
            } while (tinggi <= 0);
            bersihkan_input_buffer();

        } else if (pilihan == 'X' || pilihan == 'x') {
            setColor(DEFAULT);
            return;
        } else {
            printf("\nPilihan tidak dikenali. Tekan ENTER untuk kembali ke menu.\n");
            bersihkan_input_buffer();
            getchar();
        }
    } while (1);
}
void delay_ms(int ms) {
    Sleep(ms);
}
void rumahPola() {
    int n;
    char bahan;

    system("cls");
    printf(">>> Rumah Pola <<<\n");

    printf("Masukkan Tinggi : ");
    scanf("%d", &n);
    printf("Masukkan Bahan  : ");
    scanf(" %c", &bahan);
    printf("\n");

    int lebar_jajar = (n * 3 + 2);
    int lebar_segitiga = (2 * n);
    int offset_x = 8;
    int speed = 3;
    int row_delay = 10;
    int posCerobong = offset_x + lebar_segitiga;

    for(int c = 0; c < n; c++){
        setColor(ABU);
        for(int s = 0; s < posCerobong; s++) printf(" ");
        for(int j = 0; j < n; j++){
            printf("%c", bahan);
            fflush(stdout);
            delay_ms(speed);
        }
        printf("\n");
    }

    for(int i = 1; i <= n; i++){
        for(int s = 0; s < offset_x + (n - i); s++) printf(" ");

        setColor(BIRU);
        for(int k = 0; k < (2 * i - 1); k++){
            printf("%c", bahan);
            fflush(stdout);
            delay_ms(speed);
        }
        setColor(ABU);
        for(int k = 0; k < lebar_jajar; k++){
            printf("%c", bahan);
            fflush(stdout);
            delay_ms(speed);
        }
        printf("\n");
        delay_ms(row_delay);
    }
    for(int i = 0; i < n; i++){
        for(int s = 0; s < offset_x; s++) printf(" ");

        setColor(KUNING);
        for(int k = 0; k < lebar_segitiga; k++){
            printf("%c", bahan);
            fflush(stdout);
            delay_ms(speed);
        }
        setColor(UNGU);
        for(int k = 0; k < lebar_jajar; k++){
            printf("%c", bahan);
            fflush(stdout);
            delay_ms(speed);
        }
        printf("\n");
        delay_ms(row_delay);
    }
    setColor(DEFAULT);
    printf("\nTekan Enter untuk kembali...");
    getch();
    return;
}
void Author(){
    system("cls");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t||                  AUTHOR                  ||\n");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t||Author :                                  ||\n");
    printf("\t\t\t\t||Gerrant Natanael Hosana Glori (672022104) ||\n");
    printf("\t\t\t\t||Paskarine Pritania Putri      (672025183) ||\n");
    printf("\t\t\t\t||Hengki Gumara Putra           (672025204) ||\n");
    printf("\t\t\t\t||Elisabet Shintya Dese         (672025205) ||\n");
    printf("\t\t\t\t||Julio Isai Todi Lerrick       (672025230) ||\n");
    printf("\t\t\t\t||Kelas : AST Dasar Dasar Pemrograman H     ||\n");
    printf("\t\t\t\t||Semester : 1                              ||\n");
    printf("\t\t\t\t||Angkatan : 2025                           ||\n");
    printf("\t\t\t\t==============================================\n");
    printf("\n\t\t\t\tTekan Enter untuk kembali ke Menu Utama...");
    getch();
}
void menuUtama() {
    int pil;
    do {
        system("cls");
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t||               SISTEM BENGKEL             ||\n");
        printf("\t\t\t\t||Selamat Datang! Perlu apa? Silakan dipilih||\n");
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t||1. Lihat List Sparepart & Jasa            ||\n");
        printf("\t\t\t\t||2. Tambah List                            ||\n");
        printf("\t\t\t\t||3. Edit List                              ||\n");
        printf("\t\t\t\t||4. Hapus List                             ||\n");
        printf("\t\t\t\t||5. Input Pesanan                          ||\n");
        printf("\t\t\t\t||6. Tambahan Pesanan                       ||\n");
        printf("\t\t\t\t||7. Cetak Struk                            ||\n");
        printf("\t\t\t\t||8. Pembayaran                             ||\n");
        printf("\t\t\t\t||9. Rumah Pola                             ||\n");
        printf("\t\t\t\t||10. Bendera                               ||\n");
        printf("\t\t\t\t================= LAINNYA ====================\n");
        printf("\t\t\t\t||88. Author                                ||\n");
        printf("\t\t\t\t||99. Exit                                  ||\n");
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\tPilih : ");
        if (scanf("%d", &pil) != 1){
            while(getchar()!='\n'); 
            continue;
        }
        switch (pil) {
            case 1:
                listMenu();
            break;
            case 2:
                tambahList();
            break;
            case 3:
                editList();
            break;
            case 4:
                hapusList();
            break;
            case 5:
                menuInputService();
            break;
            case 6:
                tambahanPesanan();
            break;
            case 7:
                cetakStruk();
            break;
            case 8:
                pembayaran();
            break;
            case 9:
                rumahPola();
            break;
            case 10:
                programBendera();
            break;
            case 88:
                Author();
            break;
            case 99: {
                char konfirmasi;
                printf("\n\t\t\t\tApakah kamu yakin ingin keluar? (Y/N) : ");
                scanf(" %c", &konfirmasi);

                if (konfirmasi == 'Y' || konfirmasi == 'y'){
                    printf("\n\t\t\t\tTerima kasih telah menggunakan program ini!");
                    Sleep(1200);
                    exit(0);
                } break;
            }
            default:
                printf("\t\t\t\tPilihan Tidak Valid!");
                Sleep(1000);
                continue;
        }
    } while (1);
}
int main() {
    setColor(DEFAULT);
    listDefault();
    login();
    menuUtama();
    return 0;
}