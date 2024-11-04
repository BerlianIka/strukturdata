#include <stdio.h>
#include <conio.h>
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

int main()
{
  node *head;
  char pilih;

  head = NULL;
  do{
     system("cls");
     printf("Masukkan pilihan\n");
     printf("0. Tambah data di awal\n");
     printf("1. Tambah data di tengah list\n");
     printf("2. Tambah data di akhir\n");
     printf("3. Cetak isi list\n");
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
             tambahAwal(&head);
             break;
         case '1':
             tambahData(&head);
             break;
         case '2':
             tambahAkhir(&head);
             break;
         case '3':
             tranverse(head);
             getch();
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

void tambahAwal(node **head){
  int bil;
  node *pNew;

  system("cls");
  fflush(stdin);
  printf("Masukkan bilangan : ");
  scanf("%d", &bil);
  pNew = (node *)malloc(sizeof(node));

  if (pNew != NULL){
  	  pNew->data = bil;
      pNew->next = *head;
      *head = pNew;
  } else {
      printf("Alokasi memori gagal");
      getch();
  }
}

//========================================================

void tambahData(node **head){
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

  if (pCur == NULL){
     printf("\nNode tidak ditemukan");
     getch();
  }
  else if (pNew == NULL){
     printf("\nAlokasi memori gagal");
     getch();
  }
  else {
     pNew->data = bil;
     pNew->next = pCur->next;
     pCur->next = pNew;
  }
}

//========================================================

void tambahAkhir(node **head){
  int bil;
  node *pNew, *pCur;

  system("cls");
  printf("Masukkan bilangan : ");
  scanf("%d", &bil);

  pNew = (node *)malloc(sizeof(node));

  if (pNew == NULL){
      printf("Alokasi memori gagal");
      getch();
  } else {
      pNew->data = bil;
      pNew->next = NULL;
      if (*head == NULL) {
          *head = pNew;
      } else {
          pCur = *head;
          while (pCur->next != NULL) {
              pCur = pCur->next;
          }
          pCur->next = pNew;
      }
  }
}

//========================================================

void hapusAwal(node **head) {
    if (*head == NULL) {
        printf("List kosong, tidak ada yang dihapus.\n");
    } else {
        node *temp = *head;
        *head = (*head)->next;
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

    while (pCur != NULL && pCur->data != bil) {
        pPrev = pCur;
        pCur = pCur->next;
    }

    if (pCur == NULL) {
        printf("Data tidak ditemukan.\n");
    } else {
        if (pPrev == NULL) {
            *head = pCur->next;
        } else {
            pPrev->next = pCur->next;
        }
        free(pCur);
        printf("Data berhasil dihapus.\n");
    }
    getch();
}

//========================================================

void hapusAkhir(node **head) {
    if (*head == NULL) {
        printf("List kosong, tidak ada yang dihapus.\n");
    } else if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
    } else {
        node *pCur = *head;
        node *pPrev = NULL;

        while (pCur->next != NULL) {
            pPrev = pCur;
            pCur = pCur->next;
        }

        pPrev->next = NULL;
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
    while (pCur != NULL) {
        if (pCur->data == bil) {
            found = 1;
            break;
        }
        pCur = pCur->next;
    }

    if (found) {
        printf("Data %d ditemukan di list.\n", bil);
    } else {
        printf("Data %d tidak ditemukan.\n");
    }
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

void tranverse(node *head){
   node *pWalker;

   system("cls");
   pWalker = head;
   while (pWalker != NULL){
   	   printf("%d -> ", pWalker->data);
   	   pWalker = pWalker->next;
   }
   printf("NULL\n");
}
