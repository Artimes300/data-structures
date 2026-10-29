/*
 * COMP 2233 — Pointers & Dynamic Memory
 *
 * Feynman: "Pointer = Bellek haritasında bir koordinat."
 *   int x = 5;       // x değişkeni değer tutar
 *   int *p = &x;     // p, x'in ADRESİNİ tutar
 *   *p = 10;         // p'nin gösterdiği yere 10 yaz → x=10
 *
 * TRICK: * ve & operatörleri
 *   &  "address of"  → & = "Adresini ver"   (p = &x)
 *   *  "dereference" → * = "Adrestekini ver" (*p = 10)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ─────────────────────────────────── POINTER BASICS ─────────────────────── */

void demo_pointer_basics(void) {
    printf("=== POINTER BASICS ===\n");

    int x = 42;
    int *p = &x;        /* p = x'in adresi */

    printf("x = %d\n", x);
    printf("&x (address of x) = %p\n", (void*)&x);
    printf("p (value of p)    = %p\n", (void*)p);
    printf("*p (what p points to) = %d\n", *p);

    *p = 100;           /* x'i pointer üzerinden değiştir */
    printf("After *p=100: x = %d\n\n", x);
}

/* ─────────────────────────────────── POINTER ARITHMETIC ─────────────────── */

void demo_pointer_arithmetic(void) {
    printf("=== POINTER ARITHMETIC ===\n");

    int arr[] = {10, 20, 30, 40, 50};
    int *p = arr;   /* arr = &arr[0] — dizi adı pointer'dır! */

    /* p++ = bir sonraki int'e git = +4 byte (32-bit int) */
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d | via pointer: *(p+%d) = %d\n",
               i, arr[i], i, *(p + i));
    }
    printf("\n");
}

/* ─────────────────────────────────── DYNAMIC MEMORY ─────────────────────── */

void demo_dynamic_memory(void) {
    printf("=== DYNAMIC MEMORY (malloc/calloc/free) ===\n");

    int n = 5;

    /* malloc: belleği tahsis et, içeriği TANIMLANMAMIŞ */
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) { printf("malloc failed!\n"); return; }

    /* Manuel doldur */
    for (int i = 0; i < n; i++) arr[i] = (i + 1) * 10;
    printf("malloc array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    free(arr);
    arr = NULL;   /* CRITICAL: free sonrası NULL yap! (dangling pointer önle) */

    /* calloc: belleği tahsis et VE SIFIRLA */
    int *zeros = (int *)calloc(n, sizeof(int));
    if (zeros == NULL) { printf("calloc failed!\n"); return; }
    printf("calloc array (all zeros): ");
    for (int i = 0; i < n; i++) printf("%d ", zeros[i]);
    printf("\n");
    free(zeros);
    zeros = NULL;

    /* realloc: boyutu değiştir */
    int *dyn = (int *)malloc(3 * sizeof(int));
    dyn[0]=1; dyn[1]=2; dyn[2]=3;
    dyn = (int *)realloc(dyn, 5 * sizeof(int));  /* 3→5 eleman */
    dyn[3]=4; dyn[4]=5;
    printf("realloc 3→5: ");
    for (int i = 0; i < 5; i++) printf("%d ", dyn[i]);
    printf("\n\n");
    free(dyn);
}

/* ─────────────────────────────────── DOUBLE POINTER ─────────────────────── */

/* TRICK: Fonksiyon içinden head'i değiştirmek istiyorsan **head lazım!
 *
 * BAD  (head dışarıda değişmez):
 *   void add(Node *head) { head = new_node; }  // kopyayı değiştiriyor!
 *
 * GOOD (head dışarıda değişir):
 *   void add(Node **head) { *head = new_node; }
 */

void allocate_array(int **ptr, int n) {
    *ptr = (int *)malloc(n * sizeof(int));  /* dış pointer'ı güncelle */
    for (int i = 0; i < n; i++) (*ptr)[i] = i * i;
}

void demo_double_pointer(void) {
    printf("=== DOUBLE POINTER ===\n");
    int *arr = NULL;
    allocate_array(&arr, 5);  /* arr artık heap'te */
    printf("Squares via double ptr: ");
    for (int i = 0; i < 5; i++) printf("%d ", arr[i]);
    printf("\n\n");
    free(arr);
}

/* ─────────────────────────────────── COMMON MISTAKES ────────────────────── */

void show_common_mistakes(void) {
    printf("=== COMMON POINTER MISTAKES (READ ONLY!) ===\n");
    printf("1. DANGLING: free(p); *p = 5;        // USE AFTER FREE — UB!\n");
    printf("2. MEMORY LEAK: p = malloc(); p = malloc();  // ilk blok kayıp!\n");
    printf("3. NULL DEREF: int *p = NULL; *p = 5; // CRASH\n");
    printf("4. DOUBLE FREE: free(p); free(p);      // UB!\n");
    printf("FIX: free(p); p = NULL; her zaman!\n\n");
}

int main(void) {
    demo_pointer_basics();
    demo_pointer_arithmetic();
    demo_dynamic_memory();
    demo_double_pointer();
    show_common_mistakes();
    return 0;
}
