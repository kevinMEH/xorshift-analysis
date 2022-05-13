#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include "random.h"

typedef u64 (*RandomFunction)(ShiftState*);
typedef struct Result {
    double chiScore;
    double averageSquaredDiffDist;
    double averageDist;
    double signedSquareDist;
} Result;

int main();
void metaSimulate1k(RandomFunction, ShiftState*, Result*, char*);
void simulate10k(RandomFunction, ShiftState*, Result*, char*);
void writeReport(FILE* , Result*, char*, char*);
int compareFloat(const void*, const void*);

#endif