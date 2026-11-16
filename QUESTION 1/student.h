
#ifndef STUDENT_H
#define STUDENT_H

#include "transcript.h"

class Student {
private:
    string ID;
    string name;
    Date admissionDate;
    CourseRecord courses[10];
    int courseCount;

    static int totalStudents;

public:
    Student(string id, string name, Date admissionDate);

    string getID() const;
    string getName() const;
    Date getAdmissionDate() const;

    void addCourse(string code, double credits, int score);
    double computeGPA() const;
    double computeCreditsEarned() const;
    void printTranscript() const;

    static int getCount();
};

#endif
