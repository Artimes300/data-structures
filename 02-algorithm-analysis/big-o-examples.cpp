/*
 * COMP 2233 — Big-O Examples & Time Complexity Demos
 *
 * Her fonksiyon farklı bir complexity class'ı gösterir.
 * Active recall: Her fonksiyonun O() notasyonunu söyle,
 *                sonra aşağıdaki yorum satırını oku.
 */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// ─────────────────────────────────────────────
// O(1) — Constant Time
// İpucu: n ne kadar büyük olursa olsun 1 işlem.
// ─────────────────────────────────────────────
int getFirst(int arr[], int n) {
    return arr[0];  // n'den bağımsız → O(1)
}

// ─────────────────────────────────────────────
// O(log n) — Logarithmic
// Binary Search: Her adımda arama alanını yarıya indirir.
// n = 1.000.000 → sadece ~20 adım!
// ─────────────────────────────────────────────
int binarySearch(int arr[], int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high) {           // log₂(n) kez döner
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// ─────────────────────────────────────────────
// O(n) — Linear Time
// Her eleman bir kez gezilir.
// ─────────────────────────────────────────────
int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {   // n kez döner → O(n)
        if (arr[i] == target) return i;
    }
    return -1;
}

int sumArray(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)     // O(n)
        sum += arr[i];
    return sum;
}

// ─────────────────────────────────────────────
// O(n²) — Quadratic Time
// İç içe döngü: n * n = n² işlem
// Bubble Sort — en basit, en yavaş sıralama.
// ─────────────────────────────────────────────
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {          // n kez
        for (int j = 0; j < n - 1 - i; j++) {  // n kez
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];              // Swap
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}   // Toplam: O(n²)

// ─────────────────────────────────────────────
// O(n²) — Çift döngü ama j=i'den başlıyor
// Dikkat: hâlâ O(n²)! Sabit katsayıyı atacağız.
// Toplam işlem ≈ n(n-1)/2 → O(n²/2) → O(n²)
// ─────────────────────────────────────────────
void printPairs(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {  // j = i+1 başlıyor
            cout << "(" << arr[i] << ", " << arr[j] << ")\n";
        }
    }
}   // O(n²) — katsayıyı atarız

// ─────────────────────────────────────────────
// O(n + m) — İki farklı girdi
// İki ayrı döngü = O(n) + O(m) = O(n + m)
// n = m ise → O(2n) → O(n)
// ─────────────────────────────────────────────
void printBothArrays(int a[], int n, int b[], int m) {
    for (int i = 0; i < n; i++) cout << a[i] << " ";  // O(n)
    for (int i = 0; i < m; i++) cout << b[i] << " ";  // O(m)
}   // Toplam: O(n + m)

// ─────────────────────────────────────────────
// O(2ⁿ) — Exponential (KAÇIN!)
// Naif Fibonacci: Her çağrı 2 dal açar → 2ⁿ toplam çağrı.
// n=50 → ~10¹⁵ işlem (binlerce yıl!)
// ─────────────────────────────────────────────
int fibonacci_naive(int n) {
    if (n <= 1) return n;
    return fibonacci_naive(n - 1) + fibonacci_naive(n - 2);  // 2 dal!
}

// Doğru çözüm: Iteration ile O(n)
int fibonacci_fast(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1;
    for (int i = 2; i <= n; i++) {  // O(n)
        int c = a + b;
        a = b; b = c;
    }
    return b;
}

// ─────────────────────────────────────────────
// DEMO: Farklı complexity'leri gözlemle
// ─────────────────────────────────────────────
int main() {
    cout << "=== Big-O Complexity Demo ===\n\n";

    int arr[] = {3, 5, 2, 4, 1, 8, 7, 6};
    int n = 8;
    int sorted[] = {1, 2, 3, 4, 5, 6, 7, 8};

    // O(1)
    cout << "O(1) getFirst: " << getFirst(arr, n) << "\n";

    // O(n)
    cout << "O(n) sum: " << sumArray(arr, n) << "\n";
    cout << "O(n) linearSearch(7): index = " << linearSearch(arr, n, 7) << "\n";

    // O(log n)
    cout << "O(logN) binarySearch(5): index = " << binarySearch(sorted, n, 5) << "\n";

    // O(n²) — Bubble sort
    int toBubble[] = {5, 3, 8, 1, 2};
    bubbleSort(toBubble, 5);
    cout << "O(n²) bubbleSort result: ";
    for (int i = 0; i < 5; i++) cout << toBubble[i] << " ";
    cout << "\n";

    // O(2ⁿ) vs O(n)
    cout << "\nFibonacci(10):\n";
    cout << "  Naive O(2^n): " << fibonacci_naive(10) << "\n";
    cout << "  Fast  O(n):   " << fibonacci_fast(10) << "\n";

    return 0;
}
