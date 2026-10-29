# 02 — Algorithm Analysis & Time Complexity

## 📖 Feynman Özeti

**Zaman karmaşıklığı**, bir algoritmanın girdi boyutu (n) arttıkça ne kadar yavaşladığını ölçer.
Sabit katsayıları ve küçük terimleri **atarız** → sadece baskın terimi tutarız.

**Örnek:** `5n² + 3n + 7` → **O(n²)**  
Çünkü n büyüdükçe `n²` terimi diğerlerini ezer.

---

## ⚡ Big-O Hızlı Referans

| Notasyon | İsim | Örnek Algoritma | Trick |
|----------|------|-----------------|-------|
| O(1) | Sabit | Diziye index ile erişim | "Doğrudan git" |
| O(log n) | Logaritmik | Binary Search | "Her adımda yarıya böl" |
| O(n) | Doğrusal | Linear Search | "Her elemanı bir kez gör" |
| O(n log n) | Linearitmik | Merge Sort, Heap Sort | "Sırala ama akıllıca" |
| O(n²) | Karesel | Bubble Sort, iç içe döngü | "Her eleman için hepsine bak" |
| O(2ⁿ) | Üstel | Recursive Fibonacci (naif) | "Her karar iki dal açar" |

### Görsel Karşılaştırma (n = 1.000.000)
```
O(1)       →          1 işlem
O(log n)   →         20 işlem
O(n)       →  1,000,000 işlem
O(n²)      → 10¹² işlem (≈ 31 yıl @ 1GHz!)
```

---

## 🎯 Döngü → Karmaşıklık Analizi Kuralları

```cpp
// Kural 1: Tek döngü → O(n)
for (int i = 0; i < n; i++) { ... }

// Kural 2: İç içe döngü → O(n²)
for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) { ... }

// Kural 3: Her adımda yarıya bölme → O(log n)
while (n > 1) { n = n / 2; }

// Kural 4: Ardışık bloklar → En büyüğünü al
O(n) + O(n²) = O(n²)

// Kural 5: Katsayıları at
O(3n) = O(n)
```

---

## 📁 Dosyalar

- [`time-complexity.cpp`](./time-complexity.cpp) — Çeşitli Big-O örnekleri
- [`big-o-examples.cpp`](./big-o-examples.cpp) — LAB 2 bağlantılı örnekler

---

## 🔍 Active Recall Soruları

1. `for(i=0; i<n; i++) for(j=i; j<n; j++)` → O(?)  
   *(İpucu: j i'den başlıyor! Cevap: O(n²) ama sabit 2x daha hızlı)*

2. Binary Search neden O(log n)? Matematiğini açıkla.

3. n=100 için O(n²) vs O(n log n) kaç işlem farkı?

4. `sum += arr[i]` satırının Big-O'su tek başına nedir?

---

*Kaynak: h2 (1).pdf — COMP 2233 Week 2 Lecture Slides*
