#ifndef PROCESSOR_H
#define PROCESSOR_H

typedef struct {
    char city_name[50];
    int seismic_level;
    float risk_percent;
    int has_risk;
} CityData;

int load_data(const char *filename, CityData **cities);

#endif