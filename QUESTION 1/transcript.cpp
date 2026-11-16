
#include "transcript.h"

GradeBand gradeTable[] = {
    {80, "A", 4.0},
    {75, "B+", 3.5},
    {70, "B", 3.0},
    {65, "C+", 2.5},
    {60, "C", 2.0},
    {55, "D+", 1.5},
    {50, "D", 1.0},
    {0, "F", 0.5}
};

int numGrades = 8;

GradeBand lookupGrade(int score) {
    for (int i = 0; i < numGrades; i++) {
        int maximumScore = (i == 0) ? 100 : gradeTable[i - 1].minimumScore - 1;

        if (score >= gradeTable[i].minimumScore && score <= maximumScore) {
            return gradeTable[i];
        }
    }

    return gradeTable[numGrades - 1];
}
