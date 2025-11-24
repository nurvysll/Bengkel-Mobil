void editLayanan() {
    header("Edit Sparepart/Jasa");
    if (layananCount == 0) { printf("Belum ada layanan.\n"); return; }
    listLayanan();
    int id;
    printf("Masukkan ID: ");
    if (scanf("%d", &id) != 1) { clearInput(); printf("Input tidak valid.\n"); return; }
    clearInput();
    int idx = findLayananById(id);
    if (idx < 0) { printf("ID tidak ditemukan.\n"); return; }

    printf("Data lama: Tipe=%s | Nama=%s | Harga=Rp %d\n",
           (layananDB[idx].tipe==0?"Jasa":"Sparepart"),
           layananDB[idx].nama, layananDB[idx].harga);

    char namaBaru[64];
    int hargaBaru, tipeBaru;

    printf("Nama baru (kosongkan jika tidak diubah): ");
    fgets(namaBaru, sizeof(namaBaru), stdin);
    namaBaru[strcspn(namaBaru, "\n")] = 0;
    if (strlen(namaBaru) > 0) strcpy(layananDB[idx].nama, namaBaru);

    printf("Harga baru (0 jika tidak diubah): ");
    if (scanf("%d", &hargaBaru) != 1) { clearInput(); printf("Input tidak valid.\n"); return; }
    clearInput();
    if (hargaBaru > 0) layananDB[idx].harga = hargaBaru;

    printf("Tipe baru (0=Jasa, 1=Sparepart, -1=tidak diubah): ");
    if (scanf("%d", &tipeBaru) != 1) { clearInput(); printf("Input tidak valid.\n"); return; }
    clearInput();
    if (tipeBaru == 0 || tipeBaru == 1) layananDB[idx].tipe = tipeBaru;

    printf("Berhasil diperbarui.\n");
}

void hapusLayanan() {
    header("Hapus Sparepart/Jasa");
    if (layananCount == 0) { printf("Belum ada layanan.\n"); return; }
    listLayanan();
    int id;
    printf("Masukkan ID yang akan dihapus: ");
    if (scanf("%d", &id) != 1) { clearInput(); printf("Input tidak valid.\n"); return; }
    clearInput();
    int idx = findLayananById(id);
    if (idx < 0) { printf("ID tidak ditemukan.\n"); return; }

    for (int i = idx; i < layananCount-1; i++) layananDB[i] = layananDB[i+1];
    layananCount--;
    printf("Layanan ID %d dihapus.\n", id);
}

void listTransaksi() {
    header("Daftar Transaksi");
    if (trxCount == 0) { printf("Belum ada transaksi.\n"); return; }
    for (int i = 0; i < trxCount; i++) {
        printf("ID: %d | Pemilik: %s | Nopol: %s | Total: Rp %d | Lunas: %s\n",
               trxDB[i].id, trxDB[i].pemilik, trxDB[i].nopol,
               trxDB[i].total, (trxDB[i].lunas ? "Ya" : "Belum"));
    }
}


struct Item {
    char nama[50];
    int harga;
};

struct Transaksi {
    char nama[50];
    int qty;
    int subtotal;
};

int main() {
    struct Item sparepart[] = {
        {"Oli Mesin", 75000},
        {"Filter Udara", 50000},
        {"Kampas Rem", 120000},
        {"Busi", 30000},
        {"Aki Mobil", 850000}
    };
    int jumlahItem = sizeof(sparepart) / sizeof(sparepart[0]);

    struct Transaksi belanja[50]; // simpan daftar belanja
    int count = 0;
    int pilihan, qty, total = 0;
    char lanjut;

    printf("=== Program Kasir Bengkel Mobil ===\n");

    do {
        printf("\nDaftar Sparepart:\n");
        for (int i = 0; i < jumlahItem; i++) {
            printf("%d. %s - Rp%d\n", i+1, sparepart[i].nama, sparepart[i].harga);
        }

        printf("\nPilih item (1-%d): ", jumlahItem);
        scanf("%d", &pilihan);

        if (pilihan < 1 || pilihan > jumlahItem) {
            printf("Pilihan tidak valid!\n");
            continue;
        }

        printf("Masukkan jumlah: ");
        scanf("%d", &qty);

        strcpy(belanja[count].nama, sparepart[pilihan-1].nama);
        belanja[count].qty = qty;
        belanja[count].subtotal = sparepart[pilihan-1].harga * qty;
        total += belanja[count].subtotal;
        count++;

        printf("Tambah item lain? (y/n): ");
        scanf(" %c", &lanjut);

    } while (lanjut == 'y' || lanjut == 'Y');

    int bayar;
    printf("\nTotal belanja: Rp%d\n", total);
    printf("Masukkan uang bayar: Rp");
    scanf("%d", &bayar);

    if (bayar < total) {
        printf("Uang tidak cukup! Transaksi dibatalkan.\n");
        return 0;
    }

    int kembalian = bayar - total;

    printf("\n=== STRUK BELANJA ===\n");
    for (int i = 0; i < count; i++) {
        printf("%s x%d = Rp%d\n", belanja[i].nama, belanja[i].qty, belanja[i].subtotal);
    }
    printf("----------------------\n");
    printf("Total Belanja : Rp%d\n", total);
    printf("Uang Bayar    : Rp%d\n", bayar);
    printf("Kembalian     : Rp%d\n", kembalian);
    printf("======================\n");
    printf("Terima kasih telah berbelanja di Bengkel Mobil!\n");

    return 0;
}
