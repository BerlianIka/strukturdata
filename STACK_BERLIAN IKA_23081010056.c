#include <stdio.h>
#include <stdlib.h>

#define MAX 3  // kapasitas maksimal stack

typedef struct {
    int data[MAX];
    int top;
} Stack;

// operasi stack
void initializeStack(Stack *s);
int isEmpty(Stack *s);
int isFull(Stack *s);
void push(Stack *s, int nilai);
int pop(Stack *s);
int stackTop(Stack *s);
int stackCount(Stack *s);
void destroyStack(Stack *s);

int main() {
    Stack s;
    int pilihan, nilai;

    initializeStack(&s);

    do {
        printf("\nMenu:\n");
        printf("1. Push Stack\n");
        printf("2. Pop Stack\n");
        printf("3. Stack Top\n");
        printf("4. Empty Stack\n");
        printf("5. Full Stack\n");
        printf("6. Stack Count\n");
        printf("7. Destroy Stack\n");
        printf("8. Exit\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                printf("Masukkan nilai untuk push: ");
                scanf("%d", &nilai);
                push(&s, nilai);
                break;
            case 2:
                nilai = pop(&s);
                if (nilai != -1) {
                    printf("Nilai yang di-pop: %d\n", nilai);
                }
                break;
            case 3:
                nilai = stackTop(&s);
                if (nilai != -1) {
                    printf("Nilai teratas stack: %d\n", nilai);
                }
                break;
            case 4:
                printf("Stack %s kosong.\n", isEmpty(&s) ? "adalah" : "tidak");
                break;
            case 5:
                printf("Stack %s penuh.\n", isFull(&s) ? "adalah" : "tidak");
                break;
            case 6:
                printf("Jumlah nilai dalam stack: %d\n", stackCount(&s));
                break;
            case 7:
                destroyStack(&s);
                printf("Stack dikosongkan.\n");
                break;
            case 8:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid, silahkan coba lagi.\n");
        }
    } while (pilihan != 8);

    return 0;
}

// menginisialisasi stack
void initializeStack(Stack *s) {
    s->top = -1;
}

// memeriksa apakah stack kosong
int isEmpty(Stack *s) {
    return s->top == -1;
}

// memeriksa apakah stack penuh
int isFull(Stack *s) {
    return s->top == MAX - 1;
}

// menambah nilai ke stack
void push(Stack *s, int nilai) {
    if (isFull(s)) {
        printf("Stack penuh, tidak bisa menambah nilai.\n");
    } else {
        s->data[++(s->top)] = nilai;
        printf("Nilai %d ditambahkan ke stack.\n", nilai);
    }
}

// menghapus nilai dari stack
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack kosong, tidak bisa menghapus nilai.\n");
        return -1;
    } else {
        return s->data[(s->top)--];
    }
}

// mendapatkan nilai teratas stack tanpa menghapusnya
int stackTop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack kosong.\n");
        return -1;
    } else {
        return s->data[s->top];
    }
}

// menghitung jumlah nilai dalam stack
int stackCount(Stack *s) {
    return s->top + 1;
}

// mengosongkan stack
void destroyStack(Stack *s) {
    s->top = -1;
}
