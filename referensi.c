#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX_BOOKS 100
#define MAX_STRING 100
typedef struct {
    int id;
    char judul[MAX_STRING];
    char pengarang[MAX_STRING];
    char penerbit[MAX_STRING];
    int tahun;
    int tersedia;
} Buku;
Buku perpustakaan[MAX_BOOKS];
int jumlah_buku = 0;
void clearScreen() {
    system("cls");
}
int login() {
    char username[50], password[50];
    
    printf("=================================\n");
    printf("    SISTEM PERPUSTAKAAN LOGIN    \n");
    printf("=================================\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    if (strcmp(username, "admin") == 0 && strcmp(password, "123") == 0) {
        printf("\nLogin berhasil! Selamat datang, %s\n", username);
        printf("Tekan enter untuk melanjutkan...");
        getch();
        return 1;
    } else {
        printf("\nLogin gagal! Username atau password salah.\n");
        printf("Tekan enter untuk mencoba lagi...");
        getch();
        return 0;
    }
}
void tampilkanMenu() {
    printf("\n=================================\n");
    printf("    SISTEM MANAJEMEN PERPUSTAKAAN\n");
    printf("=================================\n");
    printf("1. Tambah Buku\n");
    printf("2. Hapus Buku\n");
    printf("3. Edit Buku\n");
    printf("4. Tampilkan Daftar Buku\n");
    printf("5. Urutkan Buku (berdasarkan Judul)\n");
    printf("6. Keluar\n");
    printf("=================================\n");
    printf("Pilihan Anda: ");
}
int generateID() {
    int id = 1;
    int found;
    
    while (1) {
        found = 0;
        for (int i = 0; i < jumlah_buku; i++) {
            if (perpustakaan[i].id == id) {
                found = 1;
                break;
            }
        }
        if (!found) return id;
        id++;
    }
}
void tambahBuku() {
    if (jumlah_buku >= MAX_BOOKS) {
        printf("\nPerpustakaan sudah penuh!\n");
        return;
    }
    
    printf("\n=== TAMBAH BUKU BARU ===\n");
    
    perpustakaan[jumlah_buku].id = generateID();
    printf("ID Buku: %d (otomatis)\n", perpustakaan[jumlah_buku].id);
    
    printf("Judul Buku: ");
    getchar(); // Membersihkan buffer
    fgets(perpustakaan[jumlah_buku].judul, MAX_STRING, stdin);
    perpustakaan[jumlah_buku].judul[strcspn(perpustakaan[jumlah_buku].judul, "\n")] = 0;
    
    printf("Pengarang: ");
    fgets(perpustakaan[jumlah_buku].pengarang, MAX_STRING, stdin);
    perpustakaan[jumlah_buku].pengarang[strcspn(perpustakaan[jumlah_buku].pengarang, "\n")] = 0;
    
    printf("Penerbit: ");
    fgets(perpustakaan[jumlah_buku].penerbit, MAX_STRING, stdin);
    perpustakaan[jumlah_buku].penerbit[strcspn(perpustakaan[jumlah_buku].penerbit, "\n")] = 0;
    
    printf("Tahun Terbit: ");
    scanf("%d", &perpustakaan[jumlah_buku].tahun);
    
    perpustakaan[jumlah_buku].tersedia = 1;
    
    jumlah_buku++;
    printf("\nBuku berhasil ditambahkan!\n");
}
void tampilkanBuku() {
    if (jumlah_buku == 0) {
        printf("\nTidak ada buku dalam perpustakaan.\n");
        return;
    }
    
    printf("\n=== DAFTAR BUKU PERPUSTAKAAN ===\n");
    printf("%-5s %-25s %-20s %-15s %-6s %-10s\n", "ID", "Judul", "Pengarang", "Penerbit", "Tahun", "Status");
    printf("================================================================================\n");
    
    for (int i = 0; i < jumlah_buku; i++) {
        printf("%-5d %-25s %-20s %-15s %-6d %-10s\n",
               perpustakaan[i].id,
               perpustakaan[i].judul,
               perpustakaan[i].pengarang,
               perpustakaan[i].penerbit,
               perpustakaan[i].tahun,
               perpustakaan[i].tersedia ? "Tersedia" : "Dipinjam");
    }
}
void hapusBuku() {
    if (jumlah_buku == 0) {
        printf("\nTidak ada buku untuk dihapus.\n");
        return;
    }
    
    int id, found = -1;
    printf("\n=== HAPUS BUKU ===\n");
    tampilkanBuku();
    printf("\nMasukkan ID buku yang akan dihapus: ");
    scanf("%d", &id);
    for (int i = 0; i < jumlah_buku; i++) {
        if (perpustakaan[i].id == id) {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        printf("Buku dengan ID %d tidak ditemukan!\n", id);
        return;
    }
    
    printf("\nBuku yang akan dihapus:\n");
    printf("Judul: %s\n", perpustakaan[found].judul);
    printf("Pengarang: %s\n", perpustakaan[found].pengarang);
    
    char konfirmasi;
    printf("\nApakah Anda yakin ingin menghapus buku ini? (y/n): ");
    scanf(" %c", &konfirmasi);
    
    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        for (int i = found; i < jumlah_buku - 1; i++) {
            perpustakaan[i] = perpustakaan[i + 1];
        }
        jumlah_buku--;
        printf("Buku berhasil dihapus!\n");
    } else {
        printf("Penghapusan dibatalkan.\n");
    }
}
void editBuku() {
    if (jumlah_buku == 0) {
        printf("\nTidak ada buku untuk diedit.\n");
        return;
    }
    
    int id, found = -1;
    printf("\n=== EDIT BUKU ===\n");
    tampilkanBuku();
    printf("\nMasukkan ID buku yang akan diedit: ");
    scanf("%d", &id);
    for (int i = 0; i < jumlah_buku; i++) {
        if (perpustakaan[i].id == id) {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        printf("Buku dengan ID %d tidak ditemukan!\n", id);
        return editBuku();
    }
    
    printf("\nData buku saat ini:\n");
    printf("1. Judul: %s\n", perpustakaan[found].judul);
    printf("2. Pengarang: %s\n", perpustakaan[found].pengarang);
    printf("3. Penerbit: %s\n", perpustakaan[found].penerbit);
    printf("4. Tahun: %d\n", perpustakaan[found].tahun);
    printf("5. Status: %s\n", perpustakaan[found].tersedia ? "Tersedia" : "Dipinjam");
    
    int pilihan;
    printf("\nPilih data yang ingin diedit (1-5): ");
    scanf("%d", &pilihan);
    
    switch (pilihan) {
        case 1:
            printf("Judul baru: ");
            getchar();
            fgets(perpustakaan[found].judul, MAX_STRING, stdin);
            perpustakaan[found].judul[strcspn(perpustakaan[found].judul, "\n")] = 0;
            break;
        case 2:
            printf("Pengarang baru: ");
            getchar();
            fgets(perpustakaan[found].pengarang, MAX_STRING, stdin);
            perpustakaan[found].pengarang[strcspn(perpustakaan[found].pengarang, "\n")] = 0;
            break;
        case 3:
            printf("Penerbit baru: ");
            getchar();
            fgets(perpustakaan[found].penerbit, MAX_STRING, stdin);
            perpustakaan[found].penerbit[strcspn(perpustakaan[found].penerbit, "\n")] = 0;
            break;
        case 4:
            printf("Tahun baru: ");
            scanf("%d", &perpustakaan[found].tahun);
            break;
        case 5:
            printf("Status baru (1=Tersedia, 0=Dipinjam): ");
            scanf("%d", &perpustakaan[found].tersedia);
            break;
        default:
            printf("Pilihan tidak valid!\n");
            return;
    }
    
    printf("Data buku berhasil diupdate!\n");
}
void urutkanBuku() {
    if (jumlah_buku <= 1) {
        printf("\nTidak cukup buku untuk diurutkan.\n");
        return;
    }
    
    printf("\n=== MENGURUTKAN BUKU BERDASARKAN JUDUL ===\n");
    for (int i = 0; i < jumlah_buku - 1; i++) {
        for (int j = 0; j < jumlah_buku - i - 1; j++) {
            if (strcmp(perpustakaan[j].judul, perpustakaan[j + 1].judul) > 0) {
                Buku temp = perpustakaan[j];
                perpustakaan[j] = perpustakaan[j + 1];
                perpustakaan[j + 1] = temp;
            }
        }
    }
    
    printf("Buku berhasil diurutkan berdasarkan judul (A-Z)!\n");
    tampilkanBuku();
}
void inisialisasiData() {
    strcpy(perpustakaan[0].judul, "Laskar Pelangi");
    strcpy(perpustakaan[0].pengarang, "Andrea Hirata");
    strcpy(perpustakaan[0].penerbit, "Bentang Pustaka");
    perpustakaan[0].id = 1;
    perpustakaan[0].tahun = 2005;
    perpustakaan[0].tersedia = 1;
    
    strcpy(perpustakaan[1].judul, "Bumi Manusia");
    strcpy(perpustakaan[1].pengarang, "Pramoedya Ananta Toer");
    strcpy(perpustakaan[1].penerbit, "Hasta Mitra");
    perpustakaan[1].id = 2;
    perpustakaan[1].tahun = 1980;
    perpustakaan[1].tersedia = 0;
    
    strcpy(perpustakaan[2].judul, "Ayat-Ayat Cinta");
    strcpy(perpustakaan[2].pengarang, "Habiburrahman El Shirazy");
    strcpy(perpustakaan[2].penerbit, "Republika");
    perpustakaan[2].id = 3;
    perpustakaan[2].tahun = 2004;
    perpustakaan[2].tersedia = 1;
    
    jumlah_buku = 3;
}

int main() {
    int pilihan;
    inisialisasiData();
    while (!login()) {
        clearScreen();
    }
    do {
        clearScreen();
        tampilkanMenu();
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1:
                clearScreen();
                tambahBuku();
                printf("\nTekan enter untuk kembali ke menu...");
                getch();
                break;
            case 2:
                clearScreen();
                hapusBuku();
                printf("\nTekan enter untuk kembali ke menu...");
                getch();
                break;
            case 3:
                clearScreen();
                editBuku();
                printf("\nTekan enter untuk kembali ke menu...");
                getch();
                break;
            case 4:
                clearScreen();
                tampilkanBuku();
                printf("\nTekan enter untuk kembali ke menu...");
                getch();
                break;
            case 5:
                clearScreen();
                urutkanBuku();
                printf("\nTekan enter untuk kembali ke menu...");
                getch();
                break;
            case 6:
                printf("\nTerima kasih telah menggunakan Sistem Perpustakaan!\n");
                break;
            default:
                printf("\nPilihan tidak valid! Silakan coba lagi.\n");
                printf("Tekan enter untuk melanjutkan...");
                getch();
        }
    } while (pilihan != 6);
    
    return 0;
}