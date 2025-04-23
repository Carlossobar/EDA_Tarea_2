#include "sorter.h"
#include <string.h>

int compare(CityData a, CityData b) {
    // 1. Mayor nivel sísmico primero
    if (a.seismic_level != b.seismic_level)
        return b.seismic_level - a.seismic_level;

    // 2. Si están en nivel 4 o 5: el que NO tiene risk va primero
    if (a.seismic_level >= 4) {
        if (a.has_risk != b.has_risk)
            return a.has_risk - b.has_risk; // el que NO tiene risk va primero
    }

    // 3. Si están en nivel 3: el que tiene risk va primero (faltante al medio)
    if (a.seismic_level == 3) {
        if (a.has_risk != b.has_risk)
            return b.has_risk - a.has_risk;
    }

    // 4. Si están en nivel 1-2: el que tiene risk va primero (faltante al final)
    if (a.seismic_level <= 2) {
        if (a.has_risk != b.has_risk)
            return b.has_risk - a.has_risk;
    }

    // 5. Si ambos tienen risk, comparar por porcentaje
    if (a.has_risk && b.has_risk) {
        if (a.risk_percent != b.risk_percent)
            return (b.risk_percent > a.risk_percent) - (b.risk_percent < a.risk_percent);
    }

    // 6. Desempate por orden alfabético inverso
    return strcmp(b.city_name, a.city_name);
}



void swap(CityData *a, CityData *b) {
    CityData tmp = *a;
    *a = *b;
    *b = tmp;
}

void quicksort(CityData *arr, int left, int right) {
    if (left >= right) return;
    CityData pivot = arr[(left + right) / 2];
    int i = left, j = right;

    while (i <= j) {
        while (compare(arr[i], pivot) < 0) i++;
        while (compare(arr[j], pivot) > 0) j--;
        if (i <= j) {
            swap(&arr[i], &arr[j]);
            i++; j--;
        }
    }

    quicksort(arr, left, j);
    quicksort(arr, i, right);
}