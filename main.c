#include <stdio.h>
#include <stdlib.h>
#include "processor.h"
#include "sorter.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <input> <N> <output>\n", argv[0]);
        return 1;
    }

    CityData *cities;
    int total = load_data(argv[1], &cities);
    if (total <= 0) {
        fprintf(stderr, "Error cargando datos.\n");
        return 2;
    }

    quicksort(cities, 0, total - 1);

    int n = atoi(argv[2]);
    FILE *out = fopen(argv[3], "w");
    if (!out) return 3;

    for (int i = 0; i < n && i < total; ++i) {
        if (cities[i].has_risk)
            fprintf(out, "%s %d %.1f\n", cities[i].city_name, cities[i].seismic_level, cities[i].risk_percent);
        else
            fprintf(out, "%s %d\n", cities[i].city_name, cities[i].seismic_level);
    }

    fclose(out);
    free(cities);
    return 0;
}