#include "processor.h"
#include "validator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_data(const char *filename, CityData **cities) {
    FILE *file = fopen(filename, "r");
    if (!file) return -1;

    char line[128];
    int count = 0, capacity = 1000;
    *cities = malloc(capacity * sizeof(CityData));
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        if (count >= capacity) {
            capacity *= 2;
            *cities = realloc(*cities, capacity * sizeof(CityData));
        }

        CityData c;
        char *token = strtok(line, " \t\n");	

        if (!token) continue;
        strcpy(c.city_name, token);

        token = strtok(NULL, " \t\n");
        if (!token) continue;
        c.seismic_level = atoi(token);

        token = strtok(NULL, " \t\n");
        if (token) {
            c.risk_percent = atof(token);
            c.has_risk = 1;
        } else {
            c.risk_percent = 0.0;
            c.has_risk = 0;
        }

        (*cities)[count++] = c;
    }

    fclose(file);
    return count;
}