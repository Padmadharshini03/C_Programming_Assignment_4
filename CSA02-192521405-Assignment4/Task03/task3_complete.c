#include <stdio.h>

enum kind { TEMPERATURE, HUMIDITY, STATUS };

struct reading {
    enum kind type;                 /* tag: tells which union member is valid */
    union {
        float celsius;
        int   percent;
        char  status[8];
    } value;
};

struct reading_struct {
    enum kind type;
    float celsius;
    int   percent;
    char  status[8];
};

void show(const struct reading *r)
{
    switch (r->type) {
        case TEMPERATURE:
            printf("Temp %.1f C\n", r->value.celsius);
            break;
        case HUMIDITY:
            printf("Humidity %d %%\n", r->value.percent);
            break;
        case STATUS:
            printf("Status %s\n", r->value.status);
            break;
    }
}

int main(void)
{
    struct reading log[3] = {
        {TEMPERATURE, {.celsius = 31.5f}},
        {HUMIDITY,    {.percent = 68}},
        {STATUS,      {.status = "OK"}}
    };
    printf("sizeof union = %zu, sizeof struct reading = %zu\n",
           sizeof log[0].value, sizeof log[0]);
    printf("sizeof full struct (no union) = %zu\n", sizeof(struct reading_struct));
    for (int i = 0; i < 3; i++) show(&log[i]);

    /* Task 3.4: Misuse Experiment */
    struct reading test;
    test.type = TEMPERATURE;
    test.value.celsius = 31.5f;
    printf("\n[Misuse Experiment] Stored float 31.5f, read int percent = %d (0x%08X)\n",
           test.value.percent, (unsigned int)test.value.percent);
    return 0;
}
