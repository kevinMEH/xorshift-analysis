#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "main.h"
#include "random.h"

#define PATH "./test/"

FILE* report;
FILE* raw;
FILE* sorted;

int main() {
    report = fopen(PATH "report.txt", "w");
    raw = fopen(PATH "raw.txt", "w");
    sorted = fopen(PATH "sorted.txt", "w");


    ShiftState original;
    original.x[0] = 0b1101010000110100111010111101011000000111100010110110011101001100;
    original.x[1] = 0b0110110111110000011111110110000110011010111101111111101111010000
                    + (time(NULL) + 1) * (time(NULL) + 1) * time(NULL) * time(NULL);
    ShiftState state;

    memcpy(&state, &original, sizeof(state));
    simulate10k(&xorshift, &state, "Default Implementation:");
    memcpy(&state, &original, sizeof(state));
    simulate10k(&xorshiftAlt1, &state, "Alternative Implementation 1:");
    memcpy(&state, &original, sizeof(state));
    simulate10k(&xorshiftAlt2, &state, "Alternative Implementation 2:");
    memcpy(&state, &original, sizeof(state));
    simulate10k(&xorshiftAlt3, &state, "Alternative Implementation 3:");
    memcpy(&state, &original, sizeof(state));
    simulate10k(&xorshiftAlt4, &state, "Alternative Implementation 4:");

    fclose(report);
    fclose(raw);
    fclose(sorted);

    return 0;
}

void simulate10k(RandomFunction function, ShiftState* state, char* name) {
    fprintf(report, name);
    fprintf(report, "\n");
    fprintf(raw, name);
    fprintf(raw, "\n");
    fprintf(sorted, name);
    fprintf(sorted, "\n");

    double numbers[10000];

    double totalDist = 0.0;
    double signedSquareDist = 0.0;

    u64 first = function(state);
    double last = (double) first / ((double) 0x8000000000000000u * 2.0);
    numbers[0] = last;
    
    for(int i = 1; i < 10000; i++) {
        u64 num = function(state);
        double normalized = (double) num / ((double) 0x8000000000000000u * 2.0);
        numbers[i] = normalized;
        
        totalDist += fabs(last - normalized);
        signedSquareDist += fabs(last - normalized) * (last - normalized);
        last = normalized;

        fprintf(raw, "%0.20lf\n", normalized);
    }
    
    double averageDist = totalDist / 9999;

    qsort(numbers, 10000, sizeof(double), &compareFloat);

    // Chi squared: Interval categorization
    int freq[250] = { 0 };
    const double chiDivision = 0.004;

    int j = 0;
    for(int i = 0; i < 10000; i++) {
        double number = numbers[i];
        fprintf(sorted, "%0.20lf\n", number);
        for( ; j < 250; j++) {
            if(number < chiDivision * (j + 1)) {
                freq[j]++;
                break;
            }
        }
    }

    // Calculating the chi score.
    double chiScore = 0.0;
    for(int i = 0; i < 250; i++) {
        int frequency = freq[i];
        double score = (frequency - 40) * (frequency - 40) / 40.0;
        chiScore += score;
    }

    // Comparison to expected values
    const double expDivision = 0.0001;
    const double offset = 0.000033333333;
    double totalSquaredDiffDist = 0.0;
    for(int i = 0; i < 10000; i++) {
        double number = numbers[i];
        double expected = offset + expDivision * i;
        double squaredDiffDist = (number - expected) * (number - expected);
        totalSquaredDiffDist += squaredDiffDist;
    }

    fprintf(report, "Chi Squared Score For 250 Subdivisions of the Interval 0 - 1: %lf\n", chiScore);
    fprintf(report, "Total Squared Difference Between Actual and Expected: %lf\n", totalSquaredDiffDist);
    fprintf(report, "Average Distance Between Numbers: %lf\n", averageDist);
    fprintf(report, "Signed Square Distance Between Numbers: %lf\n", signedSquareDist);
    fprintf(report, "\n");
}

int compareFloat(const void* one, const void* two) {
    double result = *((double*)one) - *((double*)two);
    if(result < 0) return -1;
    if(result > 0) return 1;
    if(result == 0) return 0;
    else {
        printf("Error: compareFloat: Wtf???");
        return 0;
    }
}