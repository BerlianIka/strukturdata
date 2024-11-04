#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

// Struktur node double linked list
struct node {
    int data;
    struct node *next;
    struct node *prev;  // Pointer ke node sebelumnya
};
typedef struct node node;

void tambahAwal(node **head);
void tambahAkhir(node **head);
void tambahTengah(node **head);
void hapusAwal(node **head);
void hapusTengah(node **head);
void hapusAkhir(node **head);
void cariData(node *head);
void hitungJumlah(node *head);
void jumlahData(node *head);
void tranverse(node *head);
void tranverseReverse(node *head);  // Cetak dari akhir ke awal

int main()
{
    node *head;
    char pilih;

    head = NULL;
    do {
        system("cls");
        printf("Masukkan pilihan\n");
        printf("0. Keluar\n");
        printf("1. Tambah data di awal\n");
        printf("2. Tambah data di tengah\n");
        printf("3. Tambah data di akhir\n");
        printf("4. Cetak isi list dari awal ke akhir\n");
        printf("5. Cetak isi list dari akhir ke awal\n");
        printf("6. Hapus data di awal\n");
        printf("7. Hapus data di tengah\n");
        printf("8. Hapus data di akhir\n");
        printf("9. Cari data\n");
        printf("A. Hitung jumlah data\n");
        printf("B. Jumlahkan semua data\n");
        printf("MASUKKAN PILIHAN (0 untuk keluar) : ");
        fflush(stdin);
        scanf("%c", &pilih);

        switch (pilih) {
            case '1':
                tambahAwal(&head);
                break;
            case '2':
                tambahTengah(&head);
                break;
            case '3':
                tambahAkhir(&head);
                break;
            case '4':
                tranverse(head);
                getch();
                break;
            case '5':
                tranverseReverse(head);
                getch();
                break;
            case '6':
                hapusAwal(&head);
                break;
            case '7':
                hapusTengah(&head);
                break;
            case '8':
                hapusAkhir(&head);
                break;
            case '9':
                cariData(head);
                break;
            case 'A':
                hitungJumlah(head);
                break;
            case 'B':
                jumlahData(head);
                break;
            case '0':
                printf("Keluar dari program...\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
                getch();
                break;
        }
    } while (pilih != '0');

    return 0;
}


//========================================================

// Fungsi untuk menambah data di awal
void tambahAwal(node **head) {
    int bil;
    node *pNew;

    system("cls");
    fflush(stdin);
    printf("Masukkan bilangan : ");
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = *head;
        pNew->prev = NULL;
        if (*head != NULL) {
            (*head)->prev = pNew;
        }
        *head = pNew;
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}


//========================================================

// Fungsi untuk menambah data di tengah
void tambahTengah(node **head) {
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    tranverse(*head);
    printf("\nposisi penyisipan setelah data bernilai : ");
    scanf("%d", &pos);
    printf("\nBilangan : ");
    scanf("%d", &bil);

    pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->next;
    }

    pNew = (node *)malloc(sizeof(node));

    if (pCur == NULL) {
        printf("\nNode tidak ditemukan");
        getch();
    } else if (pNew == NULL) {
        printf("\nAlokasi memori gagal");
        getch();
    } else {
        pNew->data = bil;
        pNew->next = pCur->next;
        pNew->prev = pCur;
        if (pCur->next != NULL) {
            pCur->next->prev = pNew;
        }
        pCur->next = pNew;
    }
}


//========================================================

// Fungsi untuk menambah data di akhir
void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    printf("Masukkan bilangan : ");
    scanf("%d", &bil);

    pNew = (node *)malloc(sizeof(node));

    if (pNew == NULL) {
        printf("Alokasi memori gagal");
        getch();
    } else {
        pNew->data = bil;
        pNew->next = NULL;
        if (*head == NULL) {
            pNew->prev = NULL;
            *head = pNew;
        } else {
            pCur = *head;
            while (pCur->next != NULL) {
                pCur = pCur->next;
            }
            pCur->next = pNew;
            pNew->prev = pCur;
        }
    }
}


//========================================================

// Fungsi untuk menghapus data di awal
void hapusAwal(node **head) {
    node *pTemp;

    if (*head == NULL) {
        printf("List kosong.\n");
        getch();
    } else {
        pTemp = *head;
        *head = (*head)->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        free(pTemp);
        printf("Data awal berhasil dihapus.\n");
        getch();
    }
}


//========================================================

// Fungsi untuk menghapus data di tengah
void hapusTengah(node **head) {
    int pos;
    node *pCur;

    system("cls");
    tranverse(*head);
    printf("\nHapus data setelah data bernilai: ");
    scanf("%d", &pos);

    pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->next;
    }

    if (pCur == NULL || pCur->next == NULL) {
        printf("\nNode tidak ditemukan atau tidak ada data setelahnya.");
        getch();
    } else {
        node *pDel = pCur->next;
        pCur->next = pDel->next;
        if (pDel->next != NULL) {
            pDel->next->prev = pCur;
        }
        free(pDel);
        printf("\nData di tengah berhasil dihapus.");
        getch();
    }
}


//========================================================

// Fungsi untuk menghapus data di akhir
void hapusAkhir(node **head) {
    node *pCur;

    if (*head == NULL) {
        printf("List kosong.\n");
        getch();
    } else {
        pCur = *head;
        while (pCur->next != NULL) {
            pCur = pCur->next;
        }
        if (pCur->prev != NULL) {
            pCur->prev->next = NULL;
        } else {
            *head = NULL;
        }
        free(pCur);
        printf("Data terakhir berhasil dihapus.\n");
        getch();
    }
}


//========================================================

// Fungsi untuk mencari data
void cariData(node *head) {
    int bil;
    node *pWalker;

    system("cls");
    printf("Masukkan data yang ingin dicari: ");
    scanf("%d", &bil);

    pWalker = head;
    while (pWalker != NULL) {
        if (pWalker->data == bil) {
            printf("Data ditemukan.\n");
            getch();
            return;
        }
        pWalker = pWalker->next;
    }

    printf("Data tidak ditemukan.\n");
    getch();
}


//========================================================

void hitungJumlah(node *head) {
    int count = 0;
    node *pCur = head;

    while (pCur != NULL) {
        count++;
        pCur = pCur->next;
    }

    printf("Jumlah node dalam list: %d\n", count);
    getch();
}


//========================================================

void jumlahData(node *head) {
    int sum = 0;
    node *pCur = head;

    while (pCur != NULL) {
        sum += pCur->data;
        pCur = pCur->next;
    }

    printf("Jumlah semua data dalam list: %d\n", sum);
    getch();
}


//========================================================

// Fungsi untuk mencetak data dari awal ke akhir
void tranverse(node *head) {
    node *pWalker;

    system("cls");
    pWalker = head;
    while (pWalker != NULL) {
        printf("%d -> ", pWalker->data);
        pWalker = pWalker->next;
    }
    printf("NULL\n");
}


//========================================================

// Fungsi untuk mencetak data dari akhir ke awal
void tranverseReverse(node *head) {
    node *pWalker = head;

    // Cari node terakhir
    if (pWalker == NULL) {
        printf("List kosong.\n");
        getch();
        return;
    }

    while (pWalker->next != NULL) {
        pWalker = pWalker->next;
    }

    // Cetak dari akhir ke awal
    while (pWalker != NULL) {
        printf("%d -> ", pWalker->data);
        pWalker = pWalker->prev;
    }
    printf("NULL\n");
}


//========================================================
