/*
 * COMP 2233 LAB 5 — EXPERIMENT 2 SOLUTION
 * Merge Two Sorted Linked Lists
 *
 * Feynman: "İki sıralı liste düşün. Her defasında hangisinin başı küçükse
 *           onu al, o listeyi ilerlet. Biri bitince diğerini yapıştır."
 *
 * Algorithm — Merge (like Merge Sort's merge step):
 *   while both lists non-empty:
 *     pick the smaller head → append to merged list
 *     advance that list's pointer
 *   append remaining list (whichever is not empty)
 *
 * Time Complexity: O(n + m) — her iki listenin toplam eleman sayısı kadar adım
 * Space Complexity: O(1) — yeni node oluşturmaz, pointer'ları yeniden bağlarız
 *
 * TRICK: append_node için **tail pointer kullan → O(1) tail insert
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

/* ─────────────────────────────────── HELPERS ─────────────────────────────── */

/* append_node: listenin SONUNA ekle → O(1) amortized with tail trick
 * Returns 1 on success, 0 on malloc failure. */
int append_node(Node **head, int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "  ERROR: malloc failed.\n");
        return 0;
    }
    new_node->value = value;
    new_node->next  = NULL;

    if (*head == NULL) {
        *head = new_node;  /* İlk node */
        return 1;
    }

    /* Sona kadar git — O(n). İyileştirme: tail pointer tut */
    Node *curr = *head;
    while (curr->next != NULL)
        curr = curr->next;
    curr->next = new_node;
    return 1;
}

void print_list(const Node *head) {
    if (head == NULL) { printf("(empty)\n"); return; }
    const Node *curr = head;
    while (curr != NULL) {
        printf("%d", curr->value);
        if (curr->next != NULL) printf(" → ");
        curr = curr->next;
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

/* ─────────────────────────────────── MERGE ──────────────────────────────── */

/*
 * merge_lists: two sorted lists → one sorted merged list
 *
 * PRE-CONDITION: Both lists must be in non-decreasing order!
 *
 * After merge:
 *   - *first  = NULL (transferred to merged)
 *   - *second = NULL (transferred to merged)
 *   - Return value = head of new merged list
 *
 * Detailed walkthrough:
 *   List1: 1 → 3 → 5 → NULL
 *   List2: 2 → 4 → 6 → NULL
 *
 *   Step 1: 1 < 2 → take 1, list1 = 3→5
 *   Step 2: 2 < 3 → take 2, list2 = 4→6
 *   Step 3: 3 < 4 → take 3, list1 = 5
 *   Step 4: 4 < 5 → take 4, list2 = 6
 *   Step 5: 5 < 6 → take 5, list1 = NULL
 *   Step 6: list1 empty → append remaining list2: 6
 *   Result: 1 → 2 → 3 → 4 → 5 → 6 → NULL
 */
Node *merge_lists(Node **first, Node **second) {
    Node dummy;         /* Dummy head — gerçek merged listenin başında sahte node */
    dummy.next = NULL;
    Node *tail = &dummy; /* tail her zaman en sona işaret eder */

    Node *p1 = *first;
    Node *p2 = *second;

    /* Her iki liste de boş değilken karşılaştır */
    while (p1 != NULL && p2 != NULL) {
        if (p1->value <= p2->value) {
            tail->next = p1;   /* p1'i al */
            p1 = p1->next;
        } else {
            tail->next = p2;   /* p2'yi al */
            p2 = p2->next;
        }
        tail = tail->next;     /* tail'i ilerlet */
    }

    /* Kalan listeyi doğrudan yapıştır — O(1)! */
    tail->next = (p1 != NULL) ? p1 : p2;

    /* Orijinal listeleri sıfırla (responsibility transfer) */
    *first  = NULL;
    *second = NULL;

    return dummy.next;  /* Gerçek merged listenin başı */
}

/* ─────────────────────────────────── MAIN ────────────────────────────────── */

int main(void) {
    Node *lists[2]  = {NULL, NULL};
    Node *merged    = NULL;
    int   status    = EXIT_SUCCESS;

    for (int list = 0; list < 2 && status == EXIT_SUCCESS; list++) {
        int count, previous = 0;
        printf("List %d (enter values in non-decreasing order)\n", list + 1);
        printf("Number of elements: ");
        if (scanf("%d", &count) != 1 || count < 0) {
            fprintf(stderr, "Invalid element count.\n");
            status = EXIT_FAILURE; break;
        }
        for (int idx = 0; idx < count; idx++) {
            int value;
            printf("  Value [%d/%d]: ", idx + 1, count);
            if (scanf("%d", &value) != 1 || (idx > 0 && value < previous)) {
                fprintf(stderr, "Invalid value or list not sorted.\n");
                status = EXIT_FAILURE; break;
            }
            if (!append_node(&lists[list], value)) {
                status = EXIT_FAILURE; break;
            }
            previous = value;
        }
        printf("  List %d: ", list + 1);
        print_list(lists[list]);
    }

    if (status == EXIT_SUCCESS) {
        printf("\nMerging...\n");
        merged = merge_lists(&lists[0], &lists[1]);
        printf("Merged list: ");
        print_list(merged);
        printf("\nTime Complexity: O(n + m) | Space: O(1) [no new nodes]\n");
    }

    free_list(&lists[0]);
    free_list(&lists[1]);
    free_list(&merged);
    return status;
}
