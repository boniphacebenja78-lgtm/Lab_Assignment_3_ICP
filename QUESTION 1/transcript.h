
#ifndef TRANSCRIPT_H
#define TRANSCRIPT_H

#include <string>
using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

struct CourseRecord {
    string code;
    double credits;
    int score;
};

struct GradeBand {
    int minimumScore;
    string letter;
    double points;
};

GradeBand lookupGrade(int score);

#endif
