/*
 * ======================================================================================
 * COMP 2233: DATA STRUCTURES LABORATORY - LAB 2
 * ATTACHMENT C: C Code Starter Template (lab2_template.c)
 * 
 * Course: COMP 2233 Data Structures
 * Instructors: Assoc. Prof. Dr. Ömer ÇETİN, Res. Asst. Giray KILIÇ, Res. Asst. Hatice ÇAĞLAYANLAR
 * 
 * Topics Covered:
 *  - Experiment 1: Supermarket Shopping List Search (Discrete Variables vs. String Array)
 *  - Experiment 2: Flight Passenger Manifest Search (Discrete Variables vs. Struct Array)
 *  - Linear Search O(N) vs. Binary Search O(log N) Mechanics
 *  - Execution Time Measurement via <time.h>
 * ======================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITEMS 10
#define MAX_NAME_LEN 16
#define PNR_LEN 7

/* ======================================================================================
 * EXPERIMENT 2: DATA STRUCTURE DEFINITION
 * ======================================================================================
 */
typedef struct {
    char pnr[PNR_LEN];       /* 6-character PNR code + '\0' */
    char name[MAX_NAME_LEN]; /* Passenger Name + '\0' */
    int seatNumber;          /* Seat Number (1-180) */
} Passenger;

/* ======================================================================================
 * EXPERIMENT 1: SUPERMARKET SHOPPING LIST SEARCH
 * ======================================================================================
 */

/**
 * Experiment 1 - Task 1: Linear Search using Discrete Variables
 * Demonstrates hardcoded cascading logic when no array structure is used.
 * Time Complexity: O(N * M) | Space Complexity: O(N * M)
 */
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
    return -1; /* Not found */
}

/**
 * Experiment 1 - Task 2: Linear Search using String Array (Contiguous Memory)
 * Demonstrates iterative loop flexibility and O(1) random access indexing.
 * Time Complexity: O(N * M) | Space Complexity: O(N * M)
 */
int search_shopping_list_array(const char *target, char list[MAX_ITEMS][MAX_NAME_LEN], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i], target) == 0) {
            return i; /* Found at index i */
        }
    }
    return -1; /* Not found */
}

void run_experiment_1() {
    printf("\n======================================================================\n");
    printf("   EXPERIMENT 1: SUPERMARKET SHOPPING LIST SEARCH\n");
    printf("======================================================================\n");

    /* Discrete Variables Initialization */
    const char *item0 = "apple";
    const char *item1 = "bread";
    const char *item2 = "milk";
    const char *item3 = "cheese";
    const char *item4 = "eggs";
    const char *item5 = "butter";
    const char *item6 = "coffee";
    const char *item7 = "tea";
    const char *item8 = "sugar";
    const char *item9 = "water";

    /* Array Data Structure Initialization */
    char shopping_list[MAX_ITEMS][MAX_NAME_LEN] = {
        "apple", "bread", "milk", "cheese", "eggs",
        "butter", "coffee", "tea", "sugar", "water"
    };

    char target[MAX_NAME_LEN];
    printf("Enter item to search (e.g., milk): ");
    if (scanf("%15s", target) != 1) return;

    /* Search using Discrete Variables */
    clock_t start_discrete = clock();
    int pos_discrete = search_shopping_list_discrete(target,
                                                    item0, item1, item2, item3, item4,
                                                    item5, item6, item7, item8, item9);
    clock_t end_discrete = clock();
    double time_discrete = (double)(end_discrete - start_discrete) / CLOCKS_PER_SEC;

    printf("\n[1] Searching using discrete variables...\n");
    if (pos_discrete != -1) {
        printf("    Found at position %d.\n", pos_discrete);
    } else {
        printf("    Item not found in discrete variables.\n");
    }

    /* Search using Array Structure */
    clock_t start_array = clock();
    int index_array = search_shopping_list_array(target, shopping_list, MAX_ITEMS);
    clock_t end_array = clock();
    double time_array = (double)(end_array - start_array) / CLOCKS_PER_SEC;

    printf("\n[2] Searching using array structure...\n");
    if (index_array != -1) {
        printf("    Found at index %d.\n", index_array);
    } else {
        printf("    Item not found in array.\n");
    }

    printf("\n--- Performance & Complexity Summary (Experiment 1) ---\n");
    printf("Discrete Vars Execution Time : %.8f seconds | Big-O: O(N)\n", time_discrete);
    printf("Array Struct Execution Time  : %.8f seconds | Big-O: O(N)\n", time_array);
    printf("Memory Arrangement Note      : Array guarantees contiguous allocation & cache hits.\n");
}

/* ======================================================================================
 * EXPERIMENT 2: FLIGHT PASSENGER MANIFEST SEARCH
 * ======================================================================================
 */

/**
 * Experiment 2 - Task 1: Discrete Variables Manifest Search
 */
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
    if (strcmp(target_pnr, p0) == 0) { strcpy(found_name, n0); *found_seat = s0; return 0; }
    if (strcmp(target_pnr, p1) == 0) { strcpy(found_name, n1); *found_seat = s1; return 1; }
    if (strcmp(target_pnr, p2) == 0) { strcpy(found_name, n2); *found_seat = s2; return 2; }
    if (strcmp(target_pnr, p3) == 0) { strcpy(found_name, n3); *found_seat = s3; return 3; }
    if (strcmp(target_pnr, p4) == 0) { strcpy(found_name, n4); *found_seat = s4; return 4; }
    if (strcmp(target_pnr, p5) == 0) { strcpy(found_name, n5); *found_seat = s5; return 5; }
    if (strcmp(target_pnr, p6) == 0) { strcpy(found_name, n6); *found_seat = s6; return 6; }
    if (strcmp(target_pnr, p7) == 0) { strcpy(found_name, n7); *found_seat = s7; return 7; }
    if (strcmp(target_pnr, p8) == 0) { strcpy(found_name, n8); *found_seat = s8; return 8; }
    if (strcmp(target_pnr, p9) == 0) { strcpy(found_name, n9); *found_seat = s9; return 9; }
    return -1;
}

/**
 * Experiment 2 - Task 2: Struct Array Linear Search O(N)
 */
int search_manifest_struct_array(const char *target_pnr, const Passenger manifest[], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(manifest[i].pnr, target_pnr) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * Experiment 2 - Task 3: Struct Array Binary Search O(log N) - Requires PNR-sorted Manifest
 */
int search_manifest_binary(const char *target_pnr, const Passenger sorted_manifest[], int count) {
    int low = 0;
    int high = count - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int cmp = strcmp(target_pnr, sorted_manifest[mid].pnr);
        if (cmp == 0) {
            return mid; /* Found */
        } else if (cmp < 0) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1; /* Not found */
}

void run_experiment_2() {
    printf("\n======================================================================\n");
    printf("   EXPERIMENT 2: FLIGHT PASSENGER MANIFEST SEARCH\n");
    printf("======================================================================\n");

    /* Unsorted Passenger Manifest Array */
    Passenger manifest[MAX_ITEMS] = {
        {"TK10A1", "Ahmet Yilmaz", 12},
        {"TK82F1", "Merve Kaya",   42},
        {"TK34C9", "Can Demir",    108},
        {"TK99Z2", "Elif Sahin",   15},
        {"TK12B4", "Burak Celik",  88},
        {"TK55M3", "Selin Arslan", 31},
        {"TK77K8", "Onur Ozturk",  102},
        {"TK23P5", "Zeynep Aydin", 5},
        {"TK41R6", "Emre Kaan",    67},
        {"TK60V0", "Deniz Yildiz", 150}
    };

    /* Sorted Passenger Manifest Array (Sorted by PNR Code for Binary Search) */
    Passenger sorted_manifest[MAX_ITEMS] = {
        {"TK10A1", "Ahmet Yilmaz", 12},
        {"TK12B4", "Burak Celik",  88},
        {"TK23P5", "Zeynep Aydin", 5},
        {"TK34C9", "Can Demir",    108},
        {"TK41R6", "Emre Kaan",    67},
        {"TK55M3", "Selin Arslan", 31},
        {"TK60V0", "Deniz Yildiz", 150},
        {"TK77K8", "Onur Ozturk",  102},
        {"TK82F1", "Merve Kaya",   42},
        {"TK99Z2", "Elif Sahin",   15}
    };

    char target_pnr[7];
    printf("Enter 6-digit PNR Code (e.g., TK82F1): ");
    if (scanf("%6s", target_pnr) != 1) return;

    /* 1. Struct Array Linear Search */
    clock_t start_linear = clock();
    int idx_linear = search_manifest_struct_array(target_pnr, manifest, MAX_ITEMS);
    clock_t end_linear = clock();
    double time_linear = (double)(end_linear - start_linear) / CLOCKS_PER_SEC;

    printf("\n[1] Linear Search on Struct Array (Unsorted)...\n");
    if (idx_linear != -1) {
        printf("    [SUCCESS] Passenger Found!\n");
        printf("    Name: %s | Seat Number: %d (Index %d)\n",
               manifest[idx_linear].name, manifest[idx_linear].seatNumber, idx_linear);
    } else {
        printf("    [FAILED] PNR Code not found in manifest.\n");
    }

    /* 2. Struct Array Binary Search */
    clock_t start_binary = clock();
    int idx_binary = search_manifest_binary(target_pnr, sorted_manifest, MAX_ITEMS);
    clock_t end_binary = clock();
    double time_binary = (double)(end_binary - start_binary) / CLOCKS_PER_SEC;

    printf("\n[2] Binary Search on Sorted Struct Array...\n");
    if (idx_binary != -1) {
        printf("    [SUCCESS] Passenger Found!\n");
        printf("    Name: %s | Seat Number: %d (Sorted Index %d)\n",
               sorted_manifest[idx_binary].name, sorted_manifest[idx_binary].seatNumber, idx_binary);
    } else {
        printf("    [FAILED] PNR Code not found in sorted manifest.\n");
    }

    printf("\n--- Performance & Complexity Summary (Experiment 2) ---\n");
    printf("Linear Search Complexity : O(N)    | Exec Time: %.8f sec\n", time_linear);
    printf("Binary Search Complexity : O(logN) | Exec Time: %.8f sec\n", time_binary);
    printf("Prerequisite Note        : Binary Search requires manifest sorted by PNR key.\n");
}

int main() {
    int choice = 0;
    while (1) {
        printf("\n======================================================================\n");
        printf("  COMP 2233 LAB 2 STARTER TEMPLATE PROGRAM\n");
        printf("======================================================================\n");
        printf("1. Run Experiment 1: Supermarket Shopping List Search\n");
        printf("2. Run Experiment 2: Flight Passenger Manifest Search\n");
        printf("3. Exit Program\n");
        printf("Select an option (1-3): ");
        if (scanf("%d", &choice) != 1) break;

        if (choice == 1) {
            run_experiment_1();
        } else if (choice == 2) {
            run_experiment_2();
        } else if (choice == 3) {
            printf("\nExiting Lab 2 Template Program. Goodbye!\n");
            break;
        } else {
            printf("\nInvalid option! Please enter 1, 2, or 3.\n");
        }
    }
    return 0;
}
