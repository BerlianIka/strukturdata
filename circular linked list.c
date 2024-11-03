#include <stdio.h>
#include <stdlib.h>

//========================================================

struct node {
    int data;
    struct node *next;
};
typedef struct node node;

void tambahAwal(node **head);
void tambahData(node **head);
void tambahAkhir(node **head);
void hapusAwal(node **head);
void hapusTengah(node **head);
void hapusAkhir(node **head);
void cariData(node *head);
void hitungJumlah(node *head);
void jumlahData(node *head);
void tranverse(node *head);

//========================================================

int main() {
    node *head;
    char pilih;

    head = NULL;
    do {
        system("cls");
        printf("Masukkan pilihan\n");
        printf("0. Cetak isi list\n");
        printf("1. Tambah data di awal\n");
        printf("2. Tambah data di tengah\n");
        printf("3. Tambah data di akhir\n");
        printf("4. Hapus data di awal\n");
        printf("5. Hapus data di tengah\n");
        printf("6. Hapus data di akhir\n");
        printf("7. Cari data\n");
        printf("8. Hitung jumlah node\n");
        printf("9. Jumlah data di list\n");
        printf("MASUKKAN PILIHAN (tekan q untuk keluar) : ");
        fflush(stdin);
        scanf("%c", &pilih);

        switch(pilih) {
            case '0':
                tranverse(head);
                getch();
                break;
            case '1':
                tambahAwal(&head);
                break;
            case '2':
                tambahData(&head);
                break;
            case '3':
                tambahAkhir(&head);
                break;
            case '4':
                hapusAwal(&head);
                break;
            case '5':
                hapusTengah(&head);
                break;
            case '6':
                hapusAkhir(&head);
                break;
            case '7':
                cariData(head);
                break;
            case '8':
                hitungJumlah(head);
                break;
            case '9':
                jumlahData(head);
                break;
        }
    } while (pilih != 'q');

    return 0;
}

//========================================================

void tambahAwal(node **head) {
    int bil;
    node *pNew;

    system("cls");
    fflush(stdin);
    printf("masukkan bilangan : ");
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        if (*head == NULL) {
            *head = pNew;
            pNew->next = *head;
        } else {
            node *pCur = *head;
            while (pCur->next != *head) {
                pCur = pCur->next;
            }
            pCur->next = pNew;
            pNew->next = *head; // Circular link
        }
        *head = pNew; // Update head
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void tambahData(node **head) {
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    tranverse(*head);
    printf("\nposisi penyisipan setelah data bernilai : ");
    scanf("%d", &pos);
    printf("\nBilangan : ");
    scanf("%d", &bil);

    pCur = *head;

    // Pencarian node yang memiliki nilai data == pos
    if (pCur != NULL) {
        do {
            if (pCur->data == pos) {
                pNew = (node *)malloc(sizeof(node));
                if (pNew == NULL) {
                    printf("\nAlokasi memori gagal");
                    getch();
                    return;
                }
                pNew->data = bil;
                pNew->next = pCur->next;
                pCur->next = pNew;
                return;
            }
            pCur = pCur->next;
        } while (pCur != *head);
    }

    printf("\nNode tidak ditemukan\n");
    getch();
}

//========================================================

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
        if (*head == NULL) {
            *head = pNew;
            pNew->next = *head; // Circular link
        } else {
            pCur = *head;
            while (pCur->next != *head) {
                pCur = pCur->next;
            }
            pCur->next = pNew;
            pNew->next = *head; // Circular link
        }
    }
}

//========================================================

void hapusAwal(node **head) {
    if (*head == NULL) {
        printf("List kosong, tidak ada yang dihapus.\n");
    } else {
        node *temp = *head;
        if (temp->next == *head) {
            *head = NULL; // Only one node
        } else {
            node *pCur = *head;
            while (pCur->next != *head) {
                pCur = pCur->next;
            }
            *head = (*head)->next; // Update head
            pCur->next = *head; // Update last node's next
        }
        free(temp);
        printf("Data awal berhasil dihapus.\n");
    }
    getch();
}

//========================================================

void hapusTengah(node **head) {
    int bil;
    printf("Masukkan nilai data yang akan dihapus: ");
    scanf("%d", &bil);

    node *pCur = *head;
    node *pPrev = NULL;

    do {
        if (pCur->data == bil) {
            if (pPrev == NULL) {
                hapusAwal(head); // Use hapusAwal to remove the head
            } else {
                pPrev->next = pCur->next;
                free(pCur);
                printf("Data berhasil dihapus.\n");SSSS
            }
            return;
        }
        pPrev = pCur;
        pCur = pCur->next;
    } while (pCur != *head);

    printf("Data tidak ditemukan.\n");
    getch();
}

//========================================================

void hapusAkhir(node **head) {
    if (*head == NULL) {
        printf("List kosong, tidak ada yang dihapus.\n");
    } else if ((*head)->next == *head) {
        free(*head);
        *head = NULL;
    } else {
        node *pCur = *head;
        node *pPrev = NULL;

        while (pCur->next != *head) {
            pPrev = pCur;
            pCur = pCur->next;
        }

        pPrev->next = *head; // Update last node's next to head
        free(pCur);
    }
    printf("Data akhir berhasil dihapus.\n");
    getch();
}

//========================================================

void cariData(node *head) {
    int bil, found = 0;
    printf("Masukkan nilai data yang dicari: ");
    scanf("%d", &bil);

    node *pCur = head;
    do {
        if (pCur->data == bil) {
            found = 1;
            break;
        }
        pCur = pCur->next;
    } while (pCur != head);

    if (found) {
        printf("Data %d ditemukan di list.\n", bil);
    } else {
        printf("Data %d tidak ditemukan.\n", bil);
    }
    getch();
}

//========================================================

void hitungJumlah(node *head) {
    int count = 0;
    node *pCur = head;

    if (head != NULL) {
        do {
            count++;
            pCur = pCur->next;
        } while (pCur != head);
    }

    printf("Jumlah node dalam list: %d\n", count);
    getch();
}

//========================================================

void jumlahData(node *head) {
    int sum = 0;
    node *pCur = head;

    if (head != NULL) {
        do {
            sum += pCur->data;
            pCur = pCur->next;
        } while (pCur != head);
    }

    printf("Jumlah semua data dalam list: %d\n", sum);
    getch();
}

//========================================================

void tranverse(node *head) {
    node *pWalker;

    system("cls");
    if (head != NULL) {
        pWalker = head;
        do {
            printf("%d -> ", pWalker->data);
            pWalker = pWalker->next;
        } while (pWalker != head);
    }
    printf("(head)\n");
}
