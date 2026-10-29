/*
 * COMP 2233 — Arrays: 1D & 2D
 *
 * Feynman: "Dizi = Bellekte yan yana dizilmiş kutular"
 *   arr[0] arr[1] arr[2] ... arr[n-1]
 *   Her kutu aynı büyüklükte, aynı tipte.
 *   index × sizeof(type) + base_address → O(1) erişim!
 *
 * 2D Array: Satır-Major (Row-Major) düzen:
 *   arr[0][0] arr[0][1] arr[0][2] | arr[1][0] arr[1][1] arr[1][2] | ...
 *   (Hafızada tek satır olarak sıralı)
 */

#include <iostream>
#include <cassert>
using namespace std;

/* ─────────────────────────────────── 1D ARRAY ───────────────────────────── */

void demo_1d_array() {
    cout << "=== 1D ARRAY DEMO ===\n";

    /* Stack allocation: boyut derleme zamanında belli */
    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);  /* TRICK: eleman sayısı */

    cout << "Elements: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\n";

    /* CRUD Operations */
    // Read  → O(1)
    cout << "arr[2] = " << arr[2] << "\n";

    // Update → O(1)
    arr[2] = 99;
    cout << "After arr[2]=99: arr[2] = " << arr[2] << "\n";

    // Insert at position (shift right) → O(n)
    // [10, 20, 99, 40, 50] → insert 77 at index 2
    // [10, 20, 77, 99, 40] (50 falls off if no resize!)
    int insert_val = 77, insert_pos = 2;
    for (int i = n - 1; i > insert_pos; i--)
        arr[i] = arr[i - 1];   /* Shift right */
    arr[insert_pos] = insert_val;
    cout << "After insert 77 at idx 2: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\n";

    // Delete at position (shift left) → O(n)
    int del_pos = 2;
    for (int i = del_pos; i < n - 1; i++)
        arr[i] = arr[i + 1];   /* Shift left */
    cout << "After delete idx 2: ";
    for (int i = 0; i < n - 1; i++) cout << arr[i] << " ";
    cout << "\n\n";
}

/* ─────────────────────────────────── 2D ARRAY ───────────────────────────── */

void demo_2d_array() {
    cout << "=== 2D ARRAY DEMO ===\n";

    /* Row-Major layout: arr[row][col]
     * Memory: [0][0],[0][1],[0][2], [1][0],[1][1],[1][2], [2][0],[2][1],[2][2]
     */
    const int ROWS = 3, COLS = 4;
    int matrix[ROWS][COLS] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };

    /* Print matrix */
    cout << "Matrix (" << ROWS << "x" << COLS << "):\n";
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++)
            cout << matrix[r][c] << "\t";
        cout << "\n";
    }

    /* Row sum — cache friendly: row-major access */
    for (int r = 0; r < ROWS; r++) {
        int sum = 0;
        for (int c = 0; c < COLS; c++)
            sum += matrix[r][c];
        cout << "Row " << r << " sum: " << sum << "\n";
    }

    /* Transpose: matrix[r][c] ↔ matrix[c][r] (only for square) */
    const int N = 3;
    int sq[N][N] = {{1,2,3},{4,5,6},{7,8,9}};
    cout << "\nTranspose (3x3):\n";
    for (int r = 0; r < N; r++) {
        for (int c = r + 1; c < N; c++) {
            int tmp = sq[r][c];
            sq[r][c] = sq[c][r];
            sq[c][r] = tmp;
        }
    }
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++)
            cout << sq[r][c] << " ";
        cout << "\n";
    }
    cout << "\n";
}

/* ─────────────────────────────────── PASSING ARRAYS ────────────────────────── */

/* CRITICAL: 2D array fonksiyona geçirirken SÜTUN sayısı zorunlu!
 * Neden? C'nin adres hesabı:
 *   &arr[r][c] = base + (r * COLS + c) * sizeof(int)
 *   COLS bilinmezse satır atlayamaz! */
void print2D(int arr[][4], int rows) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < 4; c++)
            cout << arr[r][c] << " ";
        cout << "\n";
    }
}

/* ─────────────────────────────────── COMPLEXITY SUMMARY ────────────────────── */

void show_complexity() {
    cout << "=== Array Complexity Summary ===\n";
    cout << "Access  arr[i]           → O(1)\n";
    cout << "Search  (unsorted)       → O(n) linear\n";
    cout << "Search  (sorted, binary) → O(log n)\n";
    cout << "Insert  at end           → O(1)\n";
    cout << "Insert  at position i    → O(n) shift\n";
    cout << "Delete  at position i    → O(n) shift\n";
    cout << "sizeof trick:  int n = sizeof(arr)/sizeof(arr[0]);\n";
}

int main() {
    demo_1d_array();
    demo_2d_array();
    show_complexity();
    return 0;
}
