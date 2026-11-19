#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 50
#define MAX_COMBO_PARTS 3

typedef enum { PACKAGED, COOKED, COMBO } ItemKind;

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int hour;
    int minute;
} Time;

typedef struct {
    int subItemIds[MAX_COMBO_PARTS];
    int partCount;
} ComboDetails;

typedef union {
    Date expiryDate;
    Time prepTime;
    ComboDetails combo;
} ItemMeta;

typedef struct {
    int id;
    char name[30];
    ItemKind kind;
    float price;
    int stock;
    int unitsSold;
    float revenue;
    ItemMeta meta;
} MenuItem;

static int totalTransactions = 0;

/* Helper: convert Date to approximate serial day count for comparison */
long toSerialDays(Date d) {
    return (long)d.year * 365 + (long)d.month * 30 + d.day;
}

int recordSale(MenuItem items[], int count, int itemId, int qty) {
    for (int i = 0; i < count; i++) {
        if (items[i].id == itemId) {
            if (qty <= 0) {
                printf("[ERROR] Invalid quantity %d for %s.\n", qty, items[i].name);
                return 0;
            }
            if (items[i].stock < qty) {
                printf("[WARN] Insufficient stock for %s (Requested: %d, Available: %d). Sale aborted.\n",
                       items[i].name, qty, items[i].stock);
                return 0;
            }
            items[i].stock -= qty;
            items[i].unitsSold += qty;
            items[i].revenue += items[i].price * qty;
            totalTransactions++;
            printf("[SALE #%d] Sold %d x %s @ Rs.%.2f = Rs.%.2f | Remaining Stock: %d\n",
                   totalTransactions, qty, items[i].name, items[i].price,
                   items[i].price * qty, items[i].stock);
            return 1;
        }
    }
    printf("[ERROR] Item ID %d not found.\n", itemId);
    return 0;
}

void warnExpiringItems(const MenuItem items[], int count, Date today) {
    printf("\n--- Expiry Warning Check (Date: %02d/%02d/%04d, Threshold: <= 2 days) ---\n",
           today.day, today.month, today.year);
    long todaySerial = toSerialDays(today);
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (items[i].kind == PACKAGED) {
            long diff = toSerialDays(items[i].meta.expiryDate) - todaySerial;
            if (diff >= 0 && diff <= 2) {
                printf("[EXPIRY ALERT] ID %d: %-18s expires on %02d/%02d/%04d (%ld day(s) left, Stock: %d)\n",
                       items[i].id, items[i].name,
                       items[i].meta.expiryDate.day, items[i].meta.expiryDate.month,
                       items[i].meta.expiryDate.year, diff, items[i].stock);
                found = 1;
            }
        }
    }
    if (!found) printf("No packaged items expiring within 2 days.\n");
}

void printSortedRevenueSummary(MenuItem items[], int count) {
    /* Selection sort descending by revenue */
    for (int i = 0; i < count - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < count; j++) {
            if (items[j].revenue > items[max_idx].revenue) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            MenuItem temp = items[i];
            items[i] = items[max_idx];
            items[max_idx] = temp;
        }
    }

    float grandTotal = 0.0f;
    printf("\n=== DAY'S BILL SUMMARY (SORTED BY REVENUE DESCENDING) ===\n");
    printf("%-4s | %-20s | %-8s | %-7s | %-5s | %-9s\n",
           "ID", "Item Name", "Type", "Price", "Sold", "Revenue");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        const char *typeStr = (items[i].kind == PACKAGED) ? "Packaged" :
                              (items[i].kind == COOKED)   ? "Cooked"   : "Combo";
        printf("%-4d | %-20s | %-8s | %7.2f | %-5d | %9.2f\n",
               items[i].id, items[i].name, typeStr,
               items[i].price, items[i].unitsSold, items[i].revenue);
        grandTotal += items[i].revenue;
    }
    printf("------------------------------------------------------------------\n");
    printf("Total Transactions: %d | Grand Total Revenue: Rs.%.2f\n", totalTransactions, grandTotal);
}

int main(void) {
    MenuItem menu[4] = {
        {101, "Mango Juice 200ml", PACKAGED, 35.0f, 20, 0, 0.0f, {.expiryDate = {20, 11, 2026}}},
        {102, "Veg Fried Rice",    COOKED,   80.0f, 15, 0, 0.0f, {.prepTime = {12, 30}}},
        {103, "Biscuit Pack",      PACKAGED, 20.0f, 30, 0, 0.0f, {.expiryDate = {28, 11, 2026}}},
        {104, "Lunch Combo",       COMBO,   105.0f, 10, 0, 0.0f, {.combo = {{102, 101, 0}, 2}}}
    };
    Date today = {19, 11, 2026};

    /* 1. Normal sales */
    recordSale(menu, 4, 102, 4);
    recordSale(menu, 4, 104, 3);
    recordSale(menu, 4, 101, 5);

    /* 2. Sale exceeding stock */
    recordSale(menu, 4, 102, 20);

    /* 3. Expiring item warning */
    warnExpiringItems(menu, 4, today);

    /* 4. Sorted summary */
    printSortedRevenueSummary(menu, 4);
    return 0;
}
