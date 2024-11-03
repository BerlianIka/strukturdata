#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char nama[50];
    char jenisKelamin; // 'L' untuk laki-laki, 'P' untuk perempuan
    struct node *next;
};
typedef struct node node;

void tambahMahasiswa(node **head, char nama[], char jenisKelamin);
void pisahLingkaran(node **lingkaranBesar, node **lingkaranLaki, node **lingkaranPerempuan);
void hapusMahasiswa(node **head, char nama[]);
void tampilkanLingkaran(node *head);
int hitungMahasiswi(node *head);

//========================================================//

int cindySudahDitambahkan = 0; // untuk melacak apakah Cindy sudah ada di lingkaran

int main() {
    node *lingkaranBesar = NULL;
    node *lingkaranLaki = NULL;
    node *lingkaranPerempuan = NULL;
    char pilih;
    char nama[50];
    char jenisKelamin;
    int tambahCindy;
    int jumlahMahasiswa = 0;

    // meminta input dari user apakah Cindy ingin dimasukkan terlebih dahulu
    printf("apakah kamu ingin menambahkan Cindy ke lingkaran terlebih dahulu? (1 = Ya, 0 = Tidak): ");
    scanf("%d", &tambahCindy);

    if (tambahCindy == 1) {
        int jumlahMahasiswi = hitungMahasiswi(lingkaranPerempuan);
        if (jumlahMahasiswi < 2) {
            printf("tidak ada cukup mahasiswi untuk menambahkan Cindy ke dalam lingkaran perempuan Cindy akan keluar.\n");
        } else {
            printf("menambahkan Cindy ke lingkaran besar...\n");
            tambahMahasiswa(&lingkaranBesar, "Cindy", 'P');
            cindySudahDitambahkan = 1;
            jumlahMahasiswa++;
        }
    }

    do {
        printf("\nPilih Menu:\n");
        printf("1. Tambah Mahasiswa/i ke Lingkaran Besar\n");
        printf("2. Keluarkan Mahasiswa/i dari Lingkaran Besar\n");
        printf("3. Tampilkan Lingkaran Besar\n");
        printf("4. Pisah Lingkaran Menjadi Lingkaran Mahasiswa dan Lingakaran Mahasiswi\n");
        printf("5. Tampilkan Lingkaran Kecil (Lingkaran Mahasiswa atau Lingkaran Mahasiswi)\n");
        printf("MASUKKAN PILIHAN (tekan q untuk keluar) : ");
        fflush(stdin);
        scanf(" %c", &pilih); // Perhatikan spasi sebelum %c

        switch(pilih) {
            case '1':
                if (jumlahMahasiswa >= 20) {
                    printf("Tidak dapat menambahkan mahasiswa/i karna keterbatasan area kemah maksimum 20 sudah tercapai.\n");
                    break;
                }
                printf("Masukkan nama: ");
                fflush(stdin);
                fgets(nama, sizeof(nama), stdin);
                nama[strcspn(nama, "\n")] = 0;  // Menghapus karakter newline dari input
                printf("Masukkan jenis kelamin (L/P): ");
                scanf(" %c", &jenisKelamin);

                // Tampilkan input pengguna
                printf("Anda memasukkan: Nama = %s, Jenis Kelamin = %c\n", nama, jenisKelamin);

                tambahMahasiswa(&lingkaranBesar, nama, jenisKelamin);
                jumlahMahasiswa++;
                break;
            case '2':
                printf("Masukkan nama mahasiswa/i yang ingin keluar: ");
                fflush(stdin);
                fgets(nama, sizeof(nama), stdin);
                nama[strcspn(nama, "\n")] = 0;
                hapusMahasiswa(&lingkaranBesar, nama);
                jumlahMahasiswa--; // Kurangi jumlah mahasiswa saat ada yang keluar
                break;
            case '3':
                printf("Lingkaran Besar:\n");
                tampilkanLingkaran(lingkaranBesar);
                break;
            case '4':
                printf("Memisahkan lingkaran menjadi lingkaran mahasiswa dan mahasiswi...\n");
                pisahLingkaran(&lingkaranBesar, &lingkaranLaki, &lingkaranPerempuan);
                break;
            case '5':
                printf("Tampilkan Lingkaran Mahasiswa atau Mahasiswi (L = Mahasiswa, P = Mahasiswi): ");
                scanf(" %c", &jenisKelamin);
                if (jenisKelamin == 'L') {
                    printf("Lingkaran Mahasiswa:\n");
                    tampilkanLingkaran(lingkaranLaki);
                } else if (jenisKelamin == 'P') {
                    printf("Lingkaran Mahasiswi:\n");
                    tampilkanLingkaran(lingkaranPerempuan);
                } else {
                    printf("Pilihan tidak valid.\n");
                }
                break;
        }
    } while (pilih != 'q');

    return 0;
}

//========================================================//

void tambahMahasiswa(node **head, char nama[], char jenisKelamin) {
    node *pNew, *pCur;

    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        strcpy(pNew->nama, nama);
        pNew->jenisKelamin = jenisKelamin;

        if (*head == NULL) {
            *head = pNew;
            pNew->next = *head;
        } else {
            pCur = *head;
            while (pCur->next != *head) {
                pCur = pCur->next;
            }
            pCur->next = pNew;
            pNew->next = *head;
        }
    } else {
        printf("Alokasi memori gagal\n");
    }
}

//==========================================================================//

void pisahLingkaran(node **lingkaranBesar, node **lingkaranLaki, node **lingkaranPerempuan) {
    node *pCur = *lingkaranBesar;
    int irsyadAda = 0, arsyadAda = 0; // Flags untuk cek keberadaan Irsyad dan Arsyad

    if (*lingkaranBesar == NULL) {
        printf("Lingkaran besar kosong. Tidak ada yang bisa dipisah.\n");
        return;
    }

    // Cek apakah Irsyad dan Arsyad ada dalam lingkaran
    do {
        if (strcmp(pCur->nama, "Irsyad") == 0) {
            irsyadAda = 1;
        }
        if (strcmp(pCur->nama, "Arsyad") == 0) {
            arsyadAda = 1;
        }
        pCur = pCur->next;
    } while (pCur != *lingkaranBesar);

    // Jika keduanya ada, keluarkan keduanya
    if (irsyadAda && arsyadAda) {
        printf("Irsyad dan Arsyad tidak dapat dipisahkan. Mengeluarkan mereka dari lingkaran.\n");
        hapusMahasiswa(lingkaranBesar, "Irsyad");
        hapusMahasiswa(lingkaranBesar, "Arsyad");
    }

    // Lanjutkan pemisahan untuk mahasiswa dan mahasiswi yang tersisa
    pCur = *lingkaranBesar; // Reset untuk pemisahan
    do {
        if (pCur->jenisKelamin == 'L') {
            tambahMahasiswa(lingkaranLaki, pCur->nama, pCur->jenisKelamin);
        } else if (pCur->jenisKelamin == 'P') {
            tambahMahasiswa(lingkaranPerempuan, pCur->nama, pCur->jenisKelamin);
        }
        pCur = pCur->next;
    } while (pCur != *lingkaranBesar);

    printf("Lingkaran berhasil dipisah menjadi lingkaran mahasiswa dan mahasiswi.\n");
}


//========================================================//

void hapusMahasiswa(node **head, char nama[]) {
    node *pCur = *head;
    node *pPrev = NULL;

    if (*head == NULL) {
        return;
    }

    do {
        if (strcmp(pCur->nama, nama) == 0) {
            if (pPrev == NULL) {
                node *temp = *head;
                if (temp->next == *head) {
                    free(temp);
                    *head = NULL;
                } else {
                    while (temp->next != *head) {
                        temp = temp->next;
                    }
                    temp->next = pCur->next;
                    *head = pCur->next; // Perbarui head jika yang dihapus adalah head
                    free(pCur);
                }
            } else {
                pPrev->next = pCur->next;
                free(pCur);
            }
            return;
        }
        pPrev = pCur;
        pCur = pCur->next;
    } while (pCur != *head);
}

//========================================================//

void tampilkanLingkaran(node *head) {
    node *pWalker = head;
    if (head != NULL) {
        do {
            printf("%s (%c) -> ", pWalker->nama, pWalker->jenisKelamin);
            pWalker = pWalker->next;
        } while (pWalker != head);
        printf("(Kembali ke %s)\n", head->nama);
    } else {
        printf("Lingkaran kosong.\n");
    }
}

//========================================================//

int hitungMahasiswi(node *head) {
    int count = 0;
    node *pWalker = head;
    if (head != NULL) {
        do {
            if (pWalker->jenisKelamin == 'P') {
                count++;
            }
            pWalker = pWalker->next;
        } while (pWalker != head);
    }
    return count;
}


//======================================//
//Berlian ika isabella//23081010056//
