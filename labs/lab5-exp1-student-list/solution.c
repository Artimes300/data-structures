/*
 * COMP 2233 LAB 5 — EXPERIMENT 1 SOLUTION
 * Student Linked List — CRUD + Reverse
 *
 * Feynman: "Linked List = Hazine avı zinciri"
 *   Her node bir sonrakinin adresini (pointer) tutar.
 *   Hafıza fiziksel olarak dağınık olabilir → contiguous değil!
 *
 * KEY OPERATIONS:
 *   add_student    → sorted insert by number  O(n)
 *   remove_student → find prev + relink       O(n)
 *   reverse        → 3-pointer technique      O(n)
 *   free_students  → her node'u serbest bırak O(n)
 *
 * TRICK — Double Pointer (**head):
 *   add_student(**head) → head'in KENDİSİ değişebilir (yeni head)
 *   Eğer *head kullansaydık, dışarıda değişiklik görünmezdi!
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 64

typedef struct Student {
    int    number;
    char   name[NAME_LENGTH];
    double grade;
    struct Student *next;
} Student;

/* ─────────────────────────────────── FIND ────────────────────────────────── */

/* O(n): lineer arama */
Student *find_student(Student *head, int number) {
    Student *curr = head;
    while (curr != NULL) {
        if (curr->number == number)
            return curr;
        curr = curr->next;
    }
    return NULL;  /* Not found */
}

/* ─────────────────────────────────── ADD ─────────────────────────────────── */

/* O(n): sıralı ekle (number'a göre ascending)
 *
 * 3 durum:
 *   1) Liste boş veya yeni node en başa gelecek  → *head güncelle
 *   2) Ortaya veya sona ekle                     → prev->next güncelle
 */
void add_student(Student **head, int number, const char *name, double grade) {
    if (find_student(*head, number) != NULL) {
        printf("  ERROR: Student number %d already exists.\n", number);
        return;
    }

    /* Yeni node oluştur */
    Student *new_node = (Student *)malloc(sizeof(Student));
    if (new_node == NULL) {
        printf("  ERROR: Memory allocation failed.\n");
        return;
    }
    new_node->number = number;
    strncpy(new_node->name, name, NAME_LENGTH - 1);
    new_node->name[NAME_LENGTH - 1] = '\0';
    new_node->grade = grade;
    new_node->next  = NULL;

    /* Doğru konumu bul (ascending order) */
    if (*head == NULL || (*head)->number > number) {
        /* Case 1: Başa ekle */
        new_node->next = *head;
        *head = new_node;
    } else {
        /* Case 2: Ortaya/sona ekle */
        Student *prev = *head;
        while (prev->next != NULL && prev->next->number < number)
            prev = prev->next;
        new_node->next = prev->next;
        prev->next = new_node;
    }
    printf("  Student #%d (%s) added.\n", number, name);
}

/* ─────────────────────────────────── REMOVE ──────────────────────────────── */

/* O(n): önceki node'u bul, köprüyü atla, free et
 *
 * Trick: "unlink" işlemi:
 *   prev->next = target->next;  // köprüyü atla
 *   free(target);               // belleği bırak
 */
void remove_student(Student **head, int number) {
    if (*head == NULL) { printf("  ERROR: List is empty.\n"); return; }

    Student *curr = *head;
    Student *prev = NULL;

    /* node'u bul, prev'i takip et */
    while (curr != NULL && curr->number != number) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("  ERROR: Student #%d not found.\n", number);
        return;
    }

    if (prev == NULL) {
        *head = curr->next;    /* Baştaki node silindi */
    } else {
        prev->next = curr->next; /* Ortada/sonda silindi */
    }

    printf("  Removed: #%d %s\n", curr->number, curr->name);
    free(curr);
}

/* ─────────────────────────────────── UPDATE ──────────────────────────────── */

void update_student(Student *head, int number, const char *name, double grade) {
    Student *s = find_student(head, number);
    if (s == NULL) {
        printf("  ERROR: Student #%d not found.\n", number);
        return;
    }
    strncpy(s->name, name, NAME_LENGTH - 1);
    s->name[NAME_LENGTH - 1] = '\0';
    s->grade = grade;
    printf("  Updated: #%d → %s (%.2f)\n", number, name, grade);
}

/* ─────────────────────────────────── LIST ────────────────────────────────── */

void list_students(const Student *head) {
    if (head == NULL) { printf("  (List is empty)\n"); return; }
    printf("\n  === Student List ===\n");
    int count = 0;
    const Student *curr = head;
    while (curr != NULL) {
        printf("  #%d | %-20s | Grade: %.2f\n",
               curr->number, curr->name, curr->grade);
        curr = curr->next;
        count++;
    }
    printf("  Total: %d students\n", count);
}

/* ─────────────────────────────────── REVERSE ─────────────────────────────── */

/* O(n): 3-pointer technique
 *
 * Visualize:
 *   Before: NULL ← 1 → 2 → 3 → NULL
 *   After:  NULL ← 3 → 2 → 1 → NULL  (wait, reversed:)
 *   After:  NULL ← 1 ← 2 ← 3 → NULL  (correct!)
 *
 * Steps per iteration:
 *   next = curr->next
 *   curr->next = prev
 *   prev = curr
 *   curr = next
 */
void reverse_students(Student **head) {
    Student *prev = NULL;
    Student *curr = *head;
    Student *next = NULL;

    while (curr != NULL) {
        next        = curr->next;  /* Save next */
        curr->next  = prev;        /* Reverse link */
        prev        = curr;        /* Advance prev */
        curr        = next;        /* Advance curr */
    }
    *head = prev;  /* New head is last node */
    printf("  List reversed!\n");
}

/* ─────────────────────────────────── FREE ────────────────────────────────── */

/* O(n): her node'u serbest bırak
 * CRITICAL: free etmeden önce next'i kaydet! */
void free_students(Student **head) {
    Student *curr = *head;
    while (curr != NULL) {
        Student *next = curr->next;
        free(curr);
        curr = next;
    }
    *head = NULL;  /* Dangling pointer'a karşı NULL yap */
    printf("  All students freed.\n");
}

/* ─────────────────────────────────── MAIN ────────────────────────────────── */

int main(void) {
    Student *head = NULL;
    int choice, number;
    char name[NAME_LENGTH];
    double grade;
    int status = EXIT_SUCCESS;

    for (;;) {
        printf("\n1. Add student\n2. Remove student\n3. Update student\n");
        printf("4. Search student\n5. List students\n6. Reverse list\n");
        printf("7. Delete all students\n0. Exit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input.\n");
            status = EXIT_FAILURE; break;
        }
        if (choice == 0) break;
        if (choice >= 1 && choice <= 4) {
            printf("Student number: ");
            if (scanf("%d", &number) != 1 || number <= 0) {
                fprintf(stderr, "Invalid student number.\n");
                status = EXIT_FAILURE; break;
            }
        }
        switch (choice) {
            case 1:
            case 3:
                printf("Name: ");
                if (scanf(" %63[^\n]", name) != 1) {
                    fprintf(stderr, "Invalid name.\n");
                    free_students(&head);
                    return EXIT_FAILURE;
                }
                printf("Grade: ");
                if (scanf("%lf", &grade) != 1 || !(grade >= 0 && grade <= 100)) {
                    fprintf(stderr, "Invalid grade.\n");
                    free_students(&head);
                    return EXIT_FAILURE;
                }
                if (choice == 1) add_student(&head, number, name, grade);
                else             update_student(head, number, name, grade);
                break;
            case 2: remove_student(&head, number); break;
            case 4: {
                Student *s = find_student(head, number);
                if (s == NULL) printf("  Student not found.\n");
                else printf("  #%d | %s | %.2f\n", s->number, s->name, s->grade);
                break;
            }
            case 5: list_students(head);   break;
            case 6: reverse_students(&head); break;
            case 7: free_students(&head);  break;
            default: printf("Invalid choice.\n");
        }
    }
    free_students(&head);
    return status;
}
