/*
 * COMP 2233 LAB 2 — SOLUTION
 * Topics: Linear Search O(N) | Binary Search O(log N)
 *         Discrete Variables vs. Array Structure
 *
 * LAB 2 Experiments:
 *   Exp 1: Supermarket Shopping List — Discrete vars vs. Array
 *   Exp 2: Flight Passenger Manifest — Struct array, linear vs. binary search
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITEMS     10
#define MAX_NAME_LEN  16
#define PNR_LEN       7

/* ──────────────────────────────────────────────────────────────────────────
 * PASSENGER STRUCT (Experiment 2)
 * ────────────────────────────────────────────────────────────────────────── */
typedef struct {
    char pnr[PNR_LEN];
    char name[MAX_NAME_LEN];
    int  seatNumber;
} Passenger;

/* ──────────────────────────────────────────────────────────────────────────
 * EXPERIMENT 1 — Supermarket Shopping List Search
 *
 * Feynman: "Discrete vars" = her ürün ayrı değişken = 10 ayrı if
 *          "Array" = tek döngü = ölçeklenebilir
 * ────────────────────────────────────────────────────────────────────────── */

/* Task 1: Discrete variables — O(N) ama hardcoded, ölçeklenemez */
int search_shopping_list_discrete(const char *target,
    const char *item0, const char *item1, const char *item2,
    const char *item3, const char *item4, const char *item5,
    const char *item6, const char *item7, const char *item8,
    const char *item9) {
    if (strcmp(target, item0) == 0) return 0;
    if (strcmp(target, item1) == 0) return 1;
    if (strcmp(target, item2) == 0) return 2;
    if (strcmp(target, item3) == 0) return 3;
    if (strcmp(target, item4) == 0) return 4;
    if (strcmp(target, item5) == 0) return 5;
    if (strcmp(target, item6) == 0) return 6;
    if (strcmp(target, item7) == 0) return 7;
    if (strcmp(target, item8) == 0) return 8;
    if (strcmp(target, item9) == 0) return 9;
    return -1;
}

/* Task 2: Array structure — O(N * M), ölçeklenebilir, contiguous memory */
int search_shopping_list_array(const char *target,
    char list[MAX_ITEMS][MAX_NAME_LEN], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i], target) == 0)
            return i;
    }
    return -1;
}

void run_experiment_1(void) {
    printf("\n======================================================================\n");
    printf("   EXPERIMENT 1: SUPERMARKET SHOPPING LIST SEARCH\n");
    printf("======================================================================\n");

    const char *item0 = "apple";  const char *item1 = "bread";
    const char *item2 = "milk";   const char *item3 = "cheese";
    const char *item4 = "eggs";   const char *item5 = "butter";
    const char *item6 = "coffee"; const char *item7 = "tea";
    const char *item8 = "sugar";  const char *item9 = "water";

    char shopping_list[MAX_ITEMS][MAX_NAME_LEN] = {
        "apple","bread","milk","cheese","eggs",
        "butter","coffee","tea","sugar","water"
    };

    char target[MAX_NAME_LEN];
    printf("Enter item to search (e.g., milk): ");
    if (scanf("%15s", target) != 1) return;

    /* --- Discrete Search --- */
    clock_t t0 = clock();
    int pos_d = search_shopping_list_discrete(target,
        item0,item1,item2,item3,item4,
        item5,item6,item7,item8,item9);
    double time_d = (double)(clock()-t0)/CLOCKS_PER_SEC;

    printf("\n[1] Discrete Variables Search:\n");
    printf("    %s → %s (pos: %d) | Time: %.8fs | Big-O: O(N)\n",
           target, pos_d != -1 ? "FOUND" : "NOT FOUND", pos_d, time_d);

    /* --- Array Search --- */
    clock_t t1 = clock();
    int idx_a = search_shopping_list_array(target, shopping_list, MAX_ITEMS);
    double time_a = (double)(clock()-t1)/CLOCKS_PER_SEC;

    printf("[2] Array Structure Search:\n");
    printf("    %s → %s (idx: %d) | Time: %.8fs | Big-O: O(N)\n",
           target, idx_a != -1 ? "FOUND" : "NOT FOUND", idx_a, time_a);

    printf("\n>>> KEY INSIGHT: Same O(N) complexity, but array is:\n");
    printf("    - More scalable (loop, not hardcoded ifs)\n");
    printf("    - Cache-friendly (contiguous memory)\n");
}

/* ──────────────────────────────────────────────────────────────────────────
 * EXPERIMENT 2 — Flight Passenger Manifest Search
 *
 * Linear Search  → O(N)      — unsorted list
 * Binary Search  → O(log N)  — sorted by PNR (prerequisite!)
 *
 * TRICK to remember: Binary Search requires SORTED data.
 *   "You can only cut a phone book in half if it's alphabetized."
 * ────────────────────────────────────────────────────────────────────────── */

/* Task 1: Discrete variables manifest — same idea as Exp1 but with struct fields */
int search_manifest_discrete(const char *target_pnr,
    const char *p0, const char *n0, int s0,
    const char *p1, const char *n1, int s1,
    const char *p2, const char *n2, int s2,
    const char *p3, const char *n3, int s3,
    const char *p4, const char *n4, int s4,
    const char *p5, const char *n5, int s5,
    const char *p6, const char *n6, int s6,
    const char *p7, const char *n7, int s7,
    const char *p8, const char *n8, int s8,
    const char *p9, const char *n9, int s9,
    char *found_name, int *found_seat) {
    if (strcmp(target_pnr,p0)==0){strcpy(found_name,n0);*found_seat=s0;return 0;}
    if (strcmp(target_pnr,p1)==0){strcpy(found_name,n1);*found_seat=s1;return 1;}
    if (strcmp(target_pnr,p2)==0){strcpy(found_name,n2);*found_seat=s2;return 2;}
    if (strcmp(target_pnr,p3)==0){strcpy(found_name,n3);*found_seat=s3;return 3;}
    if (strcmp(target_pnr,p4)==0){strcpy(found_name,n4);*found_seat=s4;return 4;}
    if (strcmp(target_pnr,p5)==0){strcpy(found_name,n5);*found_seat=s5;return 5;}
    if (strcmp(target_pnr,p6)==0){strcpy(found_name,n6);*found_seat=s6;return 6;}
    if (strcmp(target_pnr,p7)==0){strcpy(found_name,n7);*found_seat=s7;return 7;}
    if (strcmp(target_pnr,p8)==0){strcpy(found_name,n8);*found_seat=s8;return 8;}
    if (strcmp(target_pnr,p9)==0){strcpy(found_name,n9);*found_seat=s9;return 9;}
    return -1;
}

/* Task 2: Struct array linear search — O(N) */
int search_manifest_struct_array(const char *target_pnr,
    const Passenger manifest[], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(manifest[i].pnr, target_pnr) == 0)
            return i;
    }
    return -1;
}

/* Task 3: Binary search on SORTED struct array — O(log N)
 * How it works:
 *   1. Look at middle element.
 *   2. If match → done.
 *   3. If target < middle → search left half.
 *   4. If target > middle → search right half.
 *   Each step halves the search space → log₂(N) steps.
 */
int search_manifest_binary(const char *target_pnr,
    const Passenger sorted_manifest[], int count) {
    int low = 0, high = count - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;  /* Avoids integer overflow vs (low+high)/2 */
        int cmp = strcmp(target_pnr, sorted_manifest[mid].pnr);
        if (cmp == 0) return mid;
        else if (cmp < 0) high = mid - 1;  /* Target is in left half */
        else              low  = mid + 1;  /* Target is in right half */
    }
    return -1;
}

void run_experiment_2(void) {
    printf("\n======================================================================\n");
    printf("   EXPERIMENT 2: FLIGHT PASSENGER MANIFEST SEARCH\n");
    printf("======================================================================\n");

    Passenger manifest[MAX_ITEMS] = {
        {"TK10A1","Ahmet Yilmaz",12}, {"TK82F1","Merve Kaya",42},
        {"TK34C9","Can Demir",108},   {"TK99Z2","Elif Sahin",15},
        {"TK12B4","Burak Celik",88},  {"TK55M3","Selin Arslan",31},
        {"TK77K8","Onur Ozturk",102}, {"TK23P5","Zeynep Aydin",5},
        {"TK41R6","Emre Kaan",67},    {"TK60V0","Deniz Yildiz",150}
    };
    Passenger sorted_manifest[MAX_ITEMS] = {
        {"TK10A1","Ahmet Yilmaz",12}, {"TK12B4","Burak Celik",88},
        {"TK23P5","Zeynep Aydin",5},  {"TK34C9","Can Demir",108},
        {"TK41R6","Emre Kaan",67},    {"TK55M3","Selin Arslan",31},
        {"TK60V0","Deniz Yildiz",150},{"TK77K8","Onur Ozturk",102},
        {"TK82F1","Merve Kaya",42},   {"TK99Z2","Elif Sahin",15}
    };

    char target_pnr[7];
    printf("Enter 6-char PNR Code (e.g., TK82F1): ");
    if (scanf("%6s", target_pnr) != 1) return;

    /* Linear search */
    clock_t t0 = clock();
    int idx_l = search_manifest_struct_array(target_pnr, manifest, MAX_ITEMS);
    double time_l = (double)(clock()-t0)/CLOCKS_PER_SEC;

    printf("\n[1] Linear Search O(N) — Unsorted Array:\n");
    if (idx_l != -1)
        printf("    FOUND: %s | Seat %d | Time: %.8fs\n",
               manifest[idx_l].name, manifest[idx_l].seatNumber, time_l);
    else
        printf("    NOT FOUND | Time: %.8fs\n", time_l);

    /* Binary search */
    clock_t t1 = clock();
    int idx_b = search_manifest_binary(target_pnr, sorted_manifest, MAX_ITEMS);
    double time_b = (double)(clock()-t1)/CLOCKS_PER_SEC;

    printf("[2] Binary Search O(logN) — Sorted Array:\n");
    if (idx_b != -1)
        printf("    FOUND: %s | Seat %d | Time: %.8fs\n",
               sorted_manifest[idx_b].name, sorted_manifest[idx_b].seatNumber, time_b);
    else
        printf("    NOT FOUND | Time: %.8fs\n", time_b);

    printf("\n>>> KEY INSIGHT: O(N) vs O(logN)\n");
    printf("    N=10:       Linear ≤10 comparisons, Binary ≤4 comparisons\n");
    printf("    N=1000000:  Linear ≤1M comparisons, Binary ≤20 comparisons!\n");
    printf("    PREREQUISITE: Binary search needs sorted data!\n");
}

int main(void) {
    int choice = 0;
    while (1) {
        printf("\n======================================================================\n");
        printf("  COMP 2233 LAB 2 — SEARCH ALGORITHMS\n");
        printf("======================================================================\n");
        printf("1. Experiment 1: Shopping List (Discrete Vars vs. Array)\n");
        printf("2. Experiment 2: Passenger Manifest (Linear vs. Binary Search)\n");
        printf("0. Exit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) break;
        if      (choice == 1) run_experiment_1();
        else if (choice == 2) run_experiment_2();
        else if (choice == 0) { printf("Goodbye!\n"); break; }
        else printf("Invalid choice.\n");
    }
    return 0;
}
