#ifndef TRANSCRIPT_H
#define TRANSCRIPT_H

#include <iostream>
#include <string>

// Structs
struct Date {
    int day;
    int month;
    int year;
};

struct CourseRecord {
    std::string code;
    double credits;
    int score;
};

struct GradeBand {
    int minScore;
    std::string letter;
    double points;
};

// lookup functionsake for her,
GradeBand lookupGrade(int score);

class Transcript {
private:
    CourseRecord* courses;
    int capacity;
    int count;

public:
    Transcript();
    ~Transcript();
    
    // disable copying
    Transcript(const Transcript&) = delete;
    Transcript& operator=(const Transcript&) = delete;

    // operator overloads
    Transcript& operator+=(const CourseRecord& c);
    friend std::ostream& operator<<(std::ostream& os, const Transcript& t);

    // moethods
    void printWhere(bool (*keep)(const CourseRecord&));
    double computeGPA() const;
    double computeCreditsEarned() const;
    
    // helper for students
    const CourseRecord* getCourses() const { return courses; }
    int getCount() const { return count; }
};

#endif