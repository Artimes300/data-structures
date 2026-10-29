/*
 * COMP 2233 — Linked Lists: Singly Linked List
 *
 * Feynman: "Linked List = Hazine avı zinciri"
 *   HEAD → [1|*] → [2|*] → [3|NULL]
 *   Her kutu: data + next pointer
 *
 * Array vs Linked List:
 *   Array → O(1) erişim, O(n) ekleme (shift gerekir)
 *   List  → O(n) erişim, O(1) ekleme başa (pointer değiştir)
 *
 * Kullanım senaryosu:
 *   Sık ekleme/silme başa/ortaya → Linked List kazanır
 *   Sık random access (arr[i])   → Array kazanır
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

/* ─────────────────────────────────── CREATE NODE ───────────────────────── */

Node *create_node(int value) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) { fprintf(stderr, "malloc failed!\n"); exit(1); }
    n->value = value;
    n->next  = NULL;
    return n;
}

/* ─────────────────────────────────── INSERT ─────────────────────────────── */

/* Başa ekle — O(1) */
void push_front(Node **head, int value) {
    Node *n = create_node(value);
    n->next  = *head;   /* Yeni node eski head'e işaret etsin */
    *head    = n;       /* head güncelle */
}

/* Sona ekle — O(n) (tail pointer olmadan) */
void push_back(Node **head, int value) {
    Node *n = create_node(value);
    if (*head == NULL) { *head = n; return; }
    Node *curr = *head;
    while (curr->next != NULL) curr = curr->next;  /* Sona git */
    curr->next = n;
}

/* Ortaya ekle (pos'tan sonra) — O(n) bul + O(1) ekle */
void insert_after(Node *pos_node, int value) {
    if (pos_node == NULL) return;
    Node *n = create_node(value);
    n->next        = pos_node->next;
    pos_node->next = n;
}

/* ─────────────────────────────────── DELETE ─────────────────────────────── */

/* Belirli değeri sil — O(n) bul + O(1) unlink
 * TRICK: prev pointer tut veya dummy head kullan
 */
void delete_node(Node **head, int value) {
    if (*head == NULL) return;

    /* Baştaki node silinecekse */
    if ((*head)->value == value) {
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    /* Ortada/sonda: prev + curr ile ilerle */
    Node *prev = *head;
    Node *curr = (*head)->next;
    while (curr != NULL && curr->value != value) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) return;  /* Bulunamadı */
    prev->next = curr->next;   /* Köprüyü atla */
    free(curr);
}

/* ─────────────────────────────────── SEARCH ─────────────────────────────── */

Node *search(Node *head, int value) {
    while (head != NULL) {
        if (head->value == value) return head;
        head = head->next;
    }
    return NULL;
}

/* ─────────────────────────────────── REVERSE ────────────────────────────── */

/* O(n): 3-pointer iterative reverse
 *
 *   Adım adım:
 *   NULL ← A → B → C → NULL
 *
 *   1. next=B, A→NULL, prev=A, curr=B
 *   2. next=C, B→A,    prev=B, curr=C
 *   3. next=NULL, C→B, prev=C, curr=NULL
 *   → head = prev = C
 */
void reverse(Node **head) {
    Node *prev = NULL, *curr = *head, *next = NULL;
    while (curr != NULL) {
        next        = curr->next;
        curr->next  = prev;
        prev        = curr;
        curr        = next;
    }
    *head = prev;
}

/* ─────────────────────────────────── PRINT & FREE ───────────────────────── */

void print_list(const char *label, Node *head) {
    printf("%s: HEAD", label);
    while (head != NULL) {
        printf(" → %d", head->value);
        head = head->next;
    }
    printf(" → NULL\n");
}

void free_list(Node **head) {
    Node *curr = *head;
    while (curr != NULL) {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
    *head = NULL;
}

/* ─────────────────────────────────── LENGTH & COUNT ────────────────────── */

int length(Node *head) {
    int n = 0;
    while (head != NULL) { n++; head = head->next; }
    return n;
}

/* ─────────────────────────────────── MAIN ────────────────────────────────── */

int main(void) {
    Node *list = NULL;

    /* Build: 1 → 2 → 3 → 4 → 5 */
    for (int i = 1; i <= 5; i++) push_back(&list, i);
    print_list("Initial", list);

    /* Insert at front */
    push_front(&list, 0);
    print_list("After push_front(0)", list);

    /* Delete middle */
    delete_node(&list, 3);
    print_list("After delete(3)", list);

    /* Search */
    Node *found = search(list, 4);
    printf("Search(4): %s\n", found ? "FOUND" : "NOT FOUND");

    /* Reverse */
    reverse(&list);
    print_list("After reverse", list);

    /* Length */
    printf("Length: %d\n", length(list));

    free_list(&list);
    printf("List freed. head = %p\n", (void*)list);  /* NULL expected */
    return 0;
}
