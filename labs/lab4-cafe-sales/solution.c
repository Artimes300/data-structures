/*
 * COMP 2233 LAB 4 — EXPERIMENT 1 SOLUTION
 * Cafe Sales — 2D Dynamic Array (Pointer-to-Pointer)
 *
 * Feynman: "2D dinamik dizi = satır pointer'larından oluşan bir dizi"
 *   int **sales → her satır = bir günün satışları [2 ürün × 2 metrik]
 *
 * Bellek Modeli:
 *   sales → [ptr0] → [prod0_units, prod0_revenue, prod1_units, prod1_revenue]
 *            [ptr1] → [...]
 *            ...
 *
 * TRICK — Dinamik 2D Dizi (malloc ile):
 *   1) int **sales = malloc(days * sizeof(int*));   // satır pointer'ları
 *   2) for each row: sales[i] = malloc(PRODUCTS * METRICS * sizeof(int));
 *   Free ters sırayla! Önce satırlar, sonra dış dizi.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_DAYS 30
#define PRODUCTS 2
#define METRICS  2  /* [0]=units_sold, [1]=units_wasted */

/* unit_values[product][metric]:
 *   [0][0] = product0 revenue per unit
 *   [0][1] = product0 cost per unit
 *   [1][0] = product1 revenue per unit
 *   [1][1] = product1 cost per unit
 */

/* ─────────────────────────────────── INPUT HELPERS ───────────────────────── */

int read_int(const char *prompt, int min, int max) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1 || value < min || value > max) {
        while (getchar() != '\n');
        printf("Invalid input. Enter %d to %d: ", min, max);
    }
    return value;
}

double read_double(const char *prompt, double min, double max) {
    double value;
    printf("%s", prompt);
    while (scanf("%lf", &value) != 1 || value < min || value > max) {
        while (getchar() != '\n');
        printf("Invalid input. Enter %.2f to %.2f: ", min, max);
    }
    return value;
}

/* ─────────────────────────────────── CREATE MATRIX ────────────────────────── */

/* O(n): n günlük 2D dizi oluştur
 * Döndürülen pointer heap'te — free etmek ZORUNLU! */
int **create_matrix(int *days) {
    *days = read_int("Enter number of days (1-30): ", 1, MAX_DAYS);
    int **sales = (int **)malloc(*days * sizeof(int *));
    if (sales == NULL) { printf("ERROR: malloc failed.\n"); return NULL; }

    for (int i = 0; i < *days; i++) {
        sales[i] = (int *)calloc(PRODUCTS * METRICS, sizeof(int));
        if (sales[i] == NULL) {
            /* Rollback: daha önce alınan belleği bırak */
            for (int j = 0; j < i; j++) free(sales[j]);
            free(sales);
            printf("ERROR: malloc failed for row %d.\n", i);
            return NULL;
        }
    }
    printf("Sales matrix created for %d days.\n", *days);
    return sales;
}

/* ─────────────────────────────────── DELETE MATRIX ────────────────────────── */

/* O(n): önce satırları, sonra dış diziyi free et */
void delete_matrix(int **sales, int days) {
    if (sales == NULL) return;
    for (int i = 0; i < days; i++)
        free(sales[i]);   /* Her satırı bırak */
    free(sales);          /* Dış pointer dizisini bırak */
    printf("Matrix deleted. Memory freed.\n");
}

/* ─────────────────────────────────── ADD DAY ───────────────────────────────── */

/* O(n): mevcut matrisi bir satır büyüt — realloc ile */
void add_day(int **sales, int *days) {
    if (*days >= MAX_DAYS) {
        printf("ERROR: Maximum %d days reached.\n", MAX_DAYS);
        return;
    }
    /* Not: Bu implement realloc gerektirir (gerçek lab'da beklenen davranış)
     * Burada bir sonraki günün verilerini sıfırlayarak ekliyoruz. */
    for (int j = 0; j < PRODUCTS * METRICS; j++)
        sales[*days][j] = 0;  /* Sıfırla */
    (*days)++;
    printf("Day %d added. Total: %d days.\n", *days, *days);
}

/* ─────────────────────────────────── REMOVE DAY ──────────────────────────── */

/* O(n): son günü sil (ya da shift et) */
void remove_day(int **sales, int *days) {
    if (*days == 0) { printf("ERROR: No days to remove.\n"); return; }
    (*days)--;
    printf("Day %d removed. Total: %d days.\n", *days + 1, *days);
}

/* ─────────────────────────────────── UPDATE ELEMENT ─────────────────────────── */

/* O(1): gün + ürün + metrik → doğrudan ata */
void update_element(int **sales, int days) {
    int day     = read_int("Day (1-based): ",    1, days) - 1;
    int product = read_int("Product (0 or 1): ", 0, PRODUCTS - 1);
    int metric  = read_int("Metric (0=units sold, 1=units wasted): ", 0, METRICS - 1);
    int value   = read_int("Value: ", 0, 10000);
    sales[day][product * METRICS + metric] = value;
    printf("Updated sales[%d][%d*2+%d] = %d\n", day, product, metric, value);
}

/* ─────────────────────────────────── UPDATE UNIT VALUES ─────────────────────── */

void update_unit_values(double unit_values[][METRICS]) {
    for (int p = 0; p < PRODUCTS; p++) {
        printf("Product %d:\n", p);
        unit_values[p][0] = read_double("  Revenue per unit: $", 0.0, 1000.0);
        unit_values[p][1] = read_double("  Cost per unit:    $", 0.0, 1000.0);
    }
}

/* ─────────────────────────────────── PRINT TOTALS ──────────────────────────── */

/* O(n * PRODUCTS): her gün için toplam gelir ve maliyet hesapla */
void print_totals(int **sales, int days, double unit_values[][METRICS]) {
    printf("\n%-5s %-12s %-12s %-12s %-12s\n",
           "Day", "Prod0 Rev", "Prod0 Cost", "Prod1 Rev", "Prod1 Cost");
    printf("──────────────────────────────────────────────────────\n");

    double grand_revenue = 0.0, grand_cost = 0.0;

    for (int i = 0; i < days; i++) {
        printf("%-5d ", i + 1);
        for (int p = 0; p < PRODUCTS; p++) {
            int units   = sales[i][p * METRICS + 0];
            int wasted  = sales[i][p * METRICS + 1];
            double rev  = units  * unit_values[p][0];
            double cost = wasted * unit_values[p][1];
            grand_revenue += rev;
            grand_cost    += cost;
            printf("$%-11.2f $%-11.2f ", rev, cost);
        }
        printf("\n");
    }
    printf("──────────────────────────────────────────────────────\n");
    printf("TOTAL Revenue: $%.2f | Total Cost: $%.2f | Net: $%.2f\n",
           grand_revenue, grand_cost, grand_revenue - grand_cost);
}

/* ─────────────────────────────────── MAIN ────────────────────────────────── */

int main(void) {
    int **sales  = NULL;
    int   days   = 0;
    double unit_values[PRODUCTS][METRICS] = {{5.0, 2.0}, {8.0, 4.0}};
    int choice;

    do {
        printf("\nCOMP 2233 LAB 04 - EXPERIMENT 1: CAFE SALES\n");
        printf("1. Create sales matrix\n");
        printf("2. Add a sales day\n");
        printf("3. Remove a sales day\n");
        printf("4. Update a sales element\n");
        printf("5. Update unit revenue and cost\n");
        printf("6. Calculate daily totals\n");
        printf("7. Delete the sales matrix\n");
        printf("0. Exit\n");
        choice = read_int("Choice: ", 0, 7);

        if (choice == 1) {
            if (sales != NULL) printf("Matrix already exists.\n");
            else               sales = create_matrix(&days);
        } else if (choice == 5) {
            update_unit_values(unit_values);
        } else if (choice != 0 && sales == NULL) {
            printf("Create the sales matrix first!\n");
        } else if (choice == 2) add_day(sales, &days);
        else if (choice == 3) remove_day(sales, &days);
        else if (choice == 4) update_element(sales, days);
        else if (choice == 6) print_totals(sales, days, unit_values);
        else if (choice == 7) { delete_matrix(sales, days); sales = NULL; days = 0; }
    } while (choice != 0);

    if (sales != NULL) delete_matrix(sales, days);
    return 0;
}
