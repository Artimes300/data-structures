/*
 * ISINMA PRATİĞİ: VETERİNER KLİNİĞİ ARAMA SİSTEMİ
 */

#include <stdio.h>
#include <string.h>

#define HAYVAN_SAYISI 4

// BÖLÜM 2 İÇİN STRUCT TANIMI
typedef struct {
  char cip[10];  // Çip numarası (Örn: "CP101")
  char isim[20]; // Hayvan adı
  int yas;       // Yaşı
} Hayvan;

/* ==========================================================================
 * GÖREV 1: KELİME DİZİSİNDE ARAMA (Linear Search)
 * ========================================================================== */
int isim_ara(const char *hedef, char liste[HAYVAN_SAYISI][20], int adet) {
  for (int i = 0; i < adet; i++) {
    if (strcmp(liste[i], hedef) == 0) {
      return i; // Bulundu!
    }
  }
  return -1; // Tüm döngü bitti ama bulunamadı
}

/* ==========================================================================
 * GÖREV 2: STRUCT DİZİSİNDE ÇİP NUMARASI ARAMA
 * ========================================================================== */
int cip_ara(const char *hedef_cip, const Hayvan liste[], int adet) {
  for (int i = 0; i < adet; i++) {
    if (strcmp(liste[i].cip, hedef_cip) == 0) {
      return i; // Bulundu!
    }
  }
  return -1; // Tüm döngü bitti ama bulunamadı
}

/* ==========================================================================
 * TEST EDİCİ (main fonksiyonu)
 * ========================================================================== */
int main() {
  printf("=========================================\n");
  printf("   VETERINER KLINIGI TEST PROGRAMI\n");
  printf("=========================================\n\n");

  // --- TEST 1: İSİM ARAMA ---
  char isimler[HAYVAN_SAYISI][20] = {"Pamuk", "Karabas", "Boncuk", "Duman"};

  const char *aranan_isim = "Boncuk";
  printf("[Test 1] Aranan Isim: %s\n", aranan_isim);

  int sonuc1 = isim_ara(aranan_isim, isimler, HAYVAN_SAYISI);
  if (sonuc1 != -1) {
    printf(">>> TEBRIKLER! %s, %d numarali kafeste bulundu!\n\n", aranan_isim,
           sonuc1);
  } else {
    printf(">>> HENUZ CALISMIYOR: isim_ara fonksiyonunu doldurmalisin.\n\n");
  }

  // --- TEST 2: STRUCT İÇİNDE ÇİP ARAMA ---
  Hayvan hastalar[HAYVAN_SAYISI] = {{"CP101", "Pamuk", 2},
                                    {"CP102", "Karabas", 5},
                                    {"CP103", "Boncuk", 1},
                                    {"CP104", "Duman", 3}};

  const char *aranan_cip = "CP103";
  printf("[Test 2] Aranan Cip: %s\n", aranan_cip);

  int sonuc2 = cip_ara(aranan_cip, hastalar, HAYVAN_SAYISI);
  if (sonuc2 != -1) {
    printf(">>> TEBRIKLER! Cip bulundu:\n");
    printf("    Ad: %s | Yas: %d | Kafes: %d\n\n", hastalar[sonuc2].isim,
           hastalar[sonuc2].yas, sonuc2);
  } else {
    printf(">>> HENUZ CALISMIYOR: cip_ara fonksiyonunu doldurmalisin.\n\n");
  }

  return 0;
}
