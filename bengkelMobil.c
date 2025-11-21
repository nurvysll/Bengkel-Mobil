#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define MAX 100

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
            sleep(2);
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
    menuUtama();
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
            sleep(2);
            system("cls");
            menuUtama();
            return;
        }

        else {
            printf("Pilihan tidak valid!\n");
            system("pause");
        }
    }
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
                getch();
                break;
            case 2: 
                tambahList();
                system("pause");
                getch();
                break;
            case 3: printf(">> Edit List\n"); system("pause"); break;
            case 4: printf(">> Hapus List\n"); system("pause"); break;
            case 5: printf(">> Pemesanan\n"); system("pause"); break;
            case 6: printf(">> Tambah Sparepart\n"); system("pause"); break;
            case 7: printf(">> Cetak Struk\n"); system("pause"); break;
            case 8: printf(">> Pembayaran\n"); system("pause"); break;
            case 9: printf(">> Rumah Pola\n"); system("pause"); break;
            case 10: printf(">> Bendera\n"); system("pause"); break;
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