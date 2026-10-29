/*
 * COMP 2233 LAB 3 — EXPERIMENT 1 SOLUTION
 * Music Playlist using a C Array
 *
 * Feynman: Dizi bir "sabit uzunluklu raf"tır.
 *   - add_song   → sona ekle, count++
 *   - remove_song → çıkar, sağdakileri sola kaydır, count--  [O(n) shift!]
 *   - update_song → doğrula, üstüne yaz
 *   - swap_songs  → iki pozisyon değiştir (tek temp string ile)
 *
 * TRICK: "Remove = Shift + Shrink"
 *   Ortadan eleman silerken sağ elemanlar bir adım sola kayar → O(n)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SONGS    10
#define TITLE_LENGTH 64

/* ─────────────────────────────────── HELPERS ─────────────────────────────── */

void read_text(const char *prompt, char *destination, int capacity) {
    int character, index;
    printf("%s", prompt);
    if (fgets(destination, capacity, stdin) == NULL) {
        destination[0] = '\0';
        return;
    }
    index = 0;
    while (destination[index] != '\n' && destination[index] != '\0') index++;
    if (destination[index] == '\n') destination[index] = '\0';
    else while ((character = getchar()) != '\n' && character != EOF);
}

int read_int(const char *prompt) {
    char line[32];
    char *end;
    long value;
    read_text(prompt, line, sizeof(line));
    value = strtol(line, &end, 10);
    return end == line ? -1 : (int)value;
}

/* ─────────────────────────────────── OPERATIONS ─────────────────────────── */

/* VIEW — O(n): her elemanı bir kez yazdır */
void list_songs(char songs[][TITLE_LENGTH], int count) {
    if (count == 0) {
        printf("  (Playlist is empty)\n");
        return;
    }
    printf("\n  === Playlist (%d/%d songs) ===\n", count, MAX_SONGS);
    for (int i = 0; i < count; i++) {
        printf("  [%d] %s\n", i + 1, songs[i]);  /* 1-based display */
    }
}

/* ADD — O(1): sona ekle, count++ */
void add_song(char songs[][TITLE_LENGTH], int *count) {
    if (*count >= MAX_SONGS) {
        printf("  ERROR: Playlist is full (%d/%d).\n", *count, MAX_SONGS);
        return;
    }
    read_text("  Enter song title: ", songs[*count], TITLE_LENGTH);
    if (songs[*count][0] == '\0') {
        printf("  ERROR: Title cannot be empty.\n");
        return;
    }
    (*count)++;
    printf("  Added! Playlist now has %d songs.\n", *count);
}

/* REMOVE — O(n): bul + sola kaydır + count--
 * Bu neden O(n)?
 *   Worst case: ilk elemanı sil → diğer n-1 elemanı bir adım sola kaydır.
 */
void remove_song(char songs[][TITLE_LENGTH], int *count) {
    if (*count == 0) { printf("  ERROR: Playlist is empty.\n"); return; }
    list_songs(songs, *count);
    int pos = read_int("  Enter position to remove (1-based): ");
    if (pos < 1 || pos > *count) {
        printf("  ERROR: Invalid position. Must be 1 to %d.\n", *count);
        return;
    }
    int idx = pos - 1;
    printf("  Removing: \"%s\"\n", songs[idx]);

    /* Shift left — sağdaki her elemanı bir adım sola kaydır */
    for (int i = idx; i < *count - 1; i++) {
        strcpy(songs[i], songs[i + 1]);  /* songs[i] ← songs[i+1] */
    }
    (*count)--;
    printf("  Done. Playlist now has %d songs.\n", *count);
}

/* UPDATE — O(1): doğrudan index'e yaz */
void update_song(char songs[][TITLE_LENGTH], int count) {
    if (count == 0) { printf("  ERROR: Playlist is empty.\n"); return; }
    list_songs(songs, count);
    int pos = read_int("  Enter position to update (1-based): ");
    if (pos < 1 || pos > count) {
        printf("  ERROR: Invalid position.\n");
        return;
    }
    char new_title[TITLE_LENGTH];
    read_text("  Enter new title: ", new_title, TITLE_LENGTH);
    if (new_title[0] == '\0') {
        printf("  ERROR: Title cannot be empty.\n");
        return;
    }
    strcpy(songs[pos - 1], new_title);
    printf("  Updated position %d.\n", pos);
}

/* SWAP — O(1): iki pozisyonu değiştir
 * Trick: string swap için temp buffer kullan (int gibi basit swap yok!)
 */
void swap_songs(char songs[][TITLE_LENGTH], int count) {
    if (count < 2) { printf("  ERROR: Need at least 2 songs.\n"); return; }
    list_songs(songs, count);
    int pos1 = read_int("  Enter first position: ");
    int pos2 = read_int("  Enter second position: ");
    if (pos1 < 1 || pos1 > count || pos2 < 1 || pos2 > count) {
        printf("  ERROR: Invalid positions.\n");
        return;
    }
    if (pos1 == pos2) { printf("  Same position, nothing to swap.\n"); return; }

    char temp[TITLE_LENGTH];
    strcpy(temp,            songs[pos1 - 1]);
    strcpy(songs[pos1 - 1], songs[pos2 - 1]);
    strcpy(songs[pos2 - 1], temp);
    printf("  Swapped positions %d and %d.\n", pos1, pos2);
}

/* ─────────────────────────────────── MAIN ────────────────────────────────── */

int main(void) {
    char songs[MAX_SONGS][TITLE_LENGTH] = {
        "Imagine", "Take Five", "Billie Jean"
    };
    int count = 3;
    int choice;

    do {
        printf("\n=== COMP 2233 LAB 3 - EXPERIMENT 1: MUSIC PLAYLIST ===\n");
        printf("1. Add Song       [O(1)]\n");
        printf("2. Remove Song    [O(n) - shift]\n");
        printf("3. Update Song    [O(1)]\n");
        printf("4. Swap Songs     [O(1)]\n");
        printf("5. View Playlist  [O(n)]\n");
        printf("0. Exit\n");
        choice = read_int("Choice: ");
        switch (choice) {
            case 1: add_song(songs, &count);  break;
            case 2: remove_song(songs, &count); break;
            case 3: update_song(songs, count);  break;
            case 4: swap_songs(songs, count);   break;
            case 5: list_songs(songs, count);   break;
            case 0: printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}
