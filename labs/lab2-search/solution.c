/*
 * COMP 2233: DATA STRUCTURES LABORATORY - LAB 2
 * Search Algorithms & Complexity Benchmark
 *
 * Bu dosyayı sen dolduracaksın!
 * Her görevin başında yönergeler ve ipuçları bulunmaktadır.
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_ITEMS 10
#define MAX_NAME_LEN 16
#define PNR_LEN 7

/* ==========================================================================
 * VERİ YAPISI TANIMI (EXPERIMENT 2)
 * ========================================================================== */
typedef struct {
  char pnr[PNR_LEN];       // 6 karakterlik PNR kodu (Örn: "TK10A1") + '\0'
  char name[MAX_NAME_LEN]; // Yolcu adı
  int seatNumber;          // Koltuk numarası (1-180)
} Passenger;

/* ==========================================================================
 * EXPERIMENT 1: SUPERMARKET SHOPPING LIST SEARCH
 * ========================================================================== */

/*
 * Görev 1.1: Ayrık Değişkenler ile Arama (Discrete Variables)
 * Bu kısmı hazır bırakıyoruz; amaç dizi kullanmamanın ne kadar zor olduğunu
 * görmek!
 */
int search_shopping_list_discrete(const char *target, const char *item0,
                                  const char *item1, const char *item2,
                                  const char *item3, const char *item4,
                                  const char *item5, const char *item6,
                                  const char *item7, const char *item8,
                                  const char *item9) {
  if (strcmp(target, item0) == 0)
    return 0;
  if (strcmp(target, item1) == 0)
    return 1;
  if (strcmp(target, item2) == 0)
    return 2;
  if (strcmp(target, item3) == 0)
    return 3;
  if (strcmp(target, item4) == 0)
    return 4;
  if (strcmp(target, item5) == 0)
    return 5;
  if (strcmp(target, item6) == 0)
    return 6;
  if (strcmp(target, item7) == 0)
    return 7;
  if (strcmp(target, item8) == 0)
    return 8;
  if (strcmp(target, item9) == 0)
    return 9;
  return -1; // Bulunamadı
}

/*
 * Görev 1.2: Dizi ile Doğrusal Arama (Linear Search)
 *
 * Hedef: list dizisi içinde 'target' kelimesini ara.
 * Bulursan: Bulduğun indeks numarasını (0, 1, 2...) döndür.
 * Bulamazsan: -1 döndür.
 *
 * İPUÇLARI:
 * 1. 0'dan count'a kadar giden bir for döngüsü kur.
 * 2. C dilinde iki string'i karşılaştırmak için 'strcmp(str1, str2) == 0'
 * kullanılır.
 * 3. Eşleşme varsa hemen 'return i;' yap.
 * 4. Döngü biterse ve bulunamazsa fonksiyonun sonunda 'return -1;' de.
 */
int search_shopping_list_array(const char *target,
                               char list[MAX_ITEMS][MAX_NAME_LEN], int count) {
  // TODO 1.2: Kendi kodunu buraya yaz!
  for (int j = 0; j < count; j++) {
    if (strcmp(target, list[j]) == 0) {
      return j;
    }
  }

  return -1; // Bulunamadıysa -1 döndür
}

/* ==========================================================================
 * EXPERIMENT 2: FLIGHT PASSENGER MANIFEST SEARCH
 * ========================================================================== */

/*
 * Görev 2.1: Struct Dizisinde Doğrusal Arama (Linear Search)
 * Karmaşıklık: O(n)
 *
 * Hedef: 'manifest' dizisinde PNR kodu 'target_pnr' ile eşleşen yolcuyu bul.
 * Bulursan: Bulunan indeksi döndür.
 * Bulamazsan: -1 döndür.
 *
 * İPUÇLARI:
 * 1. for döngüsü ile 0'dan count - 1'e kadar tüm yolcuları gez.
 * 2. Her yolcunun PNR'ına erişmek için: manifest[i].pnr
 * 3. strcmp(manifest[i].pnr, target_pnr) == 0 şartını kontrol et.
 */
int search_manifest_linear(const char *target_pnr, const Passenger manifest[],
                           int count) {
  // TODO 2.1: Kendi kodunu buraya yaz!
  for (int i = 0; i < count; i++) {
    if (strcmp(target_pnr, manifest[i].pnr) == 0) {
      return i;
    }
  }
  return -1; // Bulunamadıysa -1 döndür
}

/*
 * Görev 2.2: Sıralı Struct Dizisinde İkili Arama (Binary Search)
 * Karmaşıklık: O(log n)
 *
 * Hedef: PNR koduna göre sıralı 'sorted_manifest' dizisinde 'target_pnr' ara.
 * Bulursan: Bulunan indeksi döndür.
 * Bulamazsan: -1 döndür.
 *
 * İPUÇLARI:
 * 1. İki sınır tanımla: int low = 0; int high = count - 1;
 * 2. while (low <= high) döngüsü kur.
 * 3. Ortanca indeksi hesapla: int mid = low + (high - low) / 2;
 * 4. strcmp sonucunu al: int cmp = strcmp(target_pnr,
 * sorted_manifest[mid].pnr);
 * 5. cmp == 0 ise: Buldun! 'return mid;'
 * 6. cmp < 0 ise: Aradığın PNR alfabetik olarak daha önce, o yüzden sol tarafa
 * git: 'high = mid - 1;'
 * 7. cmp > 0 ise: Aradığın PNR daha sonra, sağ tarafa git: 'low = mid + 1;'
 * 8. Döngüden çıkarsa eleman yok demektir: 'return -1;'
 */
int search_manifest_binary(const char *target_pnr,
                           const Passenger sorted_manifest[], int count) {
  // TODO 2.2: Kendi kodunu buraya yaz!
  int low = 0, high = count - 1;

  while (low <= high) {
    int mid = (low + high) / 2;
    int cmp = strcmp(target_pnr, sorted_manifest[mid].pnr);
    if (cmp == 0) {
      return mid;
    } else if (cmp < 0) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  return -1; // Bulunamadıysa -1 döndür
}

/* ==========================================================================
 * TEST VE BENCHMARK ÇALIŞTIRICILARI (Buraları değiştirmene gerek yok)
 * ========================================================================== */

void run_experiment_1() {
  printf("\n==================================================================="
         "===\n");
  printf("   EXPERIMENT 1: SUPERMARKET SHOPPING LIST SEARCH\n");
  printf("====================================================================="
         "=\n");

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

  char shopping_list[MAX_ITEMS][MAX_NAME_LEN] = {
      "apple",  "bread",  "milk", "cheese", "eggs",
      "butter", "coffee", "tea",  "sugar",  "water"};

  const char *target = "milk";
  printf("Aranan urun: %s\n", target);

  // 1. Ayrık değişkenler
  clock_t start1 = clock();
  int pos_discrete =
      search_shopping_list_discrete(target, item0, item1, item2, item3, item4,
                                    item5, item6, item7, item8, item9);
  clock_t end1 = clock();
  double time1 = (double)(end1 - start1) / CLOCKS_PER_SEC;

  printf("\n[1] Ayrik degiskenlerle arama: ");
  if (pos_discrete != -1)
    printf("Bulundu -> Pozisyon: %d\n", pos_discrete);
  else
    printf("Bulunamadi!\n");

  // 2. Dizi yapısı (Senin kodun!)
  clock_t start2 = clock();
  int pos_array = search_shopping_list_array(target, shopping_list, MAX_ITEMS);
  clock_t end2 = clock();
  double time2 = (double)(end2 - start2) / CLOCKS_PER_SEC;

  printf("[2] Dizi yapisiyla arama (Senin Kodun): ");
  if (pos_array != -1) {
    printf("TEBRIKLER! Bulundu -> Indeks: %d\n", pos_array);
  } else {
    printf("HENUZ CALISMIYOR (TODO 1.2'yi doldurmalisin)\n");
  }

  printf("\nSüre Kıyaslaması:\n");
  printf("Ayrik Degiskenler : %.8f sn | Karmaşıklık: O(n)\n", time1);
  printf("Dizi Yapisi       : %.8f sn | Karmaşıklık: O(n)\n", time2);
}

void run_experiment_2() {
  printf("\n==================================================================="
         "===\n");
  printf("   EXPERIMENT 2: FLIGHT PASSENGER MANIFEST SEARCH\n");
  printf("====================================================================="
         "=\n");

  Passenger manifest[MAX_ITEMS] = {
      {"TK10A1", "Ahmet Yilmaz", 12}, {"TK82F1", "Merve Kaya", 42},
      {"TK34C9", "Can Demir", 108},   {"TK99Z2", "Elif Sahin", 15},
      {"TK12B4", "Burak Celik", 88},  {"TK55M3", "Selin Arslan", 31},
      {"TK77K8", "Onur Ozturk", 102}, {"TK23P5", "Zeynep Aydin", 5},
      {"TK41R6", "Emre Kaan", 67},    {"TK60V0", "Deniz Yildiz", 150}};

  Passenger sorted_manifest[MAX_ITEMS] = {
      {"TK10A1", "Ahmet Yilmaz", 12},  {"TK12B4", "Burak Celik", 88},
      {"TK23P5", "Zeynep Aydin", 5},   {"TK34C9", "Can Demir", 108},
      {"TK41R6", "Emre Kaan", 67},     {"TK55M3", "Selin Arslan", 31},
      {"TK60V0", "Deniz Yildiz", 150}, {"TK77K8", "Onur Ozturk", 102},
      {"TK82F1", "Merve Kaya", 42},    {"TK99Z2", "Elif Sahin", 15}};

  const char *target_pnr = "TK82F1";
  printf("Aranan PNR: %s\n", target_pnr);

  // Linear Search (Senin kodun!)
  int idx_linear = search_manifest_linear(target_pnr, manifest, MAX_ITEMS);
  printf("\n[1] Linear Search (Senin Kodun): ");
  if (idx_linear != -1) {
    printf("TEBRIKLER! Bulundu -> %s, Koltuk: %d (Indeks: %d)\n",
           manifest[idx_linear].name, manifest[idx_linear].seatNumber,
           idx_linear);
  } else {
    printf("HENUZ CALISMIYOR (TODO 2.1'i doldurmalisin)\n");
  }

  // Binary Search (Senin kodun!)
  int idx_binary =
      search_manifest_binary(target_pnr, sorted_manifest, MAX_ITEMS);
  printf("[2] Binary Search (Senin Kodun): ");
  if (idx_binary != -1) {
    printf("TEBRIKLER! Bulundu -> %s, Koltuk: %d (Indeks: %d)\n",
           sorted_manifest[idx_binary].name,
           sorted_manifest[idx_binary].seatNumber, idx_binary);
  } else {
    printf("HENUZ CALISMIYOR (TODO 2.2'yi doldurmalisin)\n");
  }
}

int main() {
  run_experiment_1();
  run_experiment_2();
  return 0;
}
