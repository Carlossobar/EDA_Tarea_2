#include "validator.h"

int validate_seismic(int level) {
    return level >= 1 && level <= 5;
}

int validate_risk(float risk) {
    return risk >= 0.0 && risk <= 100.0;
}