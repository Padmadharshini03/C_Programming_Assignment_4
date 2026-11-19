#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int systolic;
    int diastolic;
} BloodPressure;

typedef struct {
    char name[50];
    int age;
    char phone[15];
    BloodPressure bp;
    Date visitDate;
} Patient;

typedef struct {
    Patient records[MAX_PATIENTS];
    int count;
} PatientRegister;

int addPatient(PatientRegister *reg, const Patient *p) {
    if (reg == NULL || p == NULL || reg->count >= MAX_PATIENTS) {
        return 0; /* Overflow or invalid pointer prevented */
    }
    reg->records[reg->count] = *p;
    reg->count++;
    return 1;
}

void sortByAge(PatientRegister *reg) {
    for (int i = 0; i < reg->count - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < reg->count; j++) {
            if (reg->records[j].age < reg->records[min_idx].age) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            Patient temp = reg->records[i];
            reg->records[i] = reg->records[min_idx];
            reg->records[min_idx] = temp;
        }
    }
}

void printRegister(const PatientRegister *reg) {
    for (int i = 0; i < reg->count; i++) {
        const Patient *p = &reg->records[i];
        printf("%-18s | Age: %2d | Phone: %-12s | BP: %3d/%-3d | Visit: %02d/%02d/%04d\n",
               p->name, p->age, p->phone,
               p->bp.systolic, p->bp.diastolic,
               p->visitDate.day, p->visitDate.month, p->visitDate.year);
    }
}

int main(void) {
    PatientRegister phc = { .count = 0 };
    Patient p1 = {"Ananya Krishnan", 42, "9840123456", {120, 80}, {18, 11, 2026}};
    Patient p2 = {"Ramesh Babu", 65, "9841987654", {145, 92}, {19, 11, 2026}};
    Patient p3 = {"Kavitha Devi", 29, "9176543210", {112, 74}, {19, 11, 2026}};

    addPatient(&phc, &p1);
    addPatient(&phc, &p2);
    addPatient(&phc, &p3);

    printf("sizeof(Patient) = %zu bytes\n", sizeof(Patient));
    printf("--- Before Sorting ---\n");
    printRegister(&phc);

    sortByAge(&phc);
    printf("\n--- After Sorting by Age ---\n");
    printRegister(&phc);
    return 0;
}
