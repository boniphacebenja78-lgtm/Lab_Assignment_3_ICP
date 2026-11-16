
#include <iostream>
#include <iomanip>
#include "student.h"

using namespace std;

int Student::totalStudents = 0;

Student::Student(string id, string name, Date admissionDate) {
    ID = id;
    this->name = name;
    this->admissionDate = admissionDate;
    courseCount = 0;
    totalStudents++;
}

string Student::getID() const {
    return ID;
}

string Student::getName() const {
    return name;
}

Date Student::getAdmissionDate() const {
    return admissionDate;
}

void Student::addCourse(string code, double credits, int score) {
    if (courseCount < 10) {
        courses[courseCount].code = code;
        courses[courseCount].credits = credits;
        courses[courseCount].score = score;
        courseCount++;
    } else {
        cout << "Error, Maximum course limit reached for " << name << endl;
    }
}

double Student::computeGPA() const {
    double totalPoints = 0.0;
    double totalCredits = 0.0;

    for (int i = 0; i < courseCount; i++) {
        GradeBand gb = lookupGrade(courses[i].score);

        totalPoints += gb.points * courses[i].credits;
        totalCredits += courses[i].credits;
    }

    if (totalCredits == 0) {
        return 0.0;
    }

    return totalPoints / totalCredits;
}

double Student::computeCreditsEarned() const {
    double earned = 0.0;

    for (int i = 0; i < courseCount; i++) {
        if (courses[i].score >= 50) {
            earned += courses[i].credits;
        }
    }

    return earned;
}

void Student::printTranscript() const {
    cout << "\nName: " << name << " ID: " << ID
         << " Admitted: " << admissionDate.day << "/"
         << admissionDate.month << "/" << admissionDate.year << endl;

    cout << left << setw(10) << "Course"
         << setw(10) << "Credits"
         << setw(10) << "Score"
         << setw(10) << "Grade"
         << "Points" << endl;

    for (int i = 0; i < courseCount; i++) {
        GradeBand gb = lookupGrade(courses[i].score);

        cout << left << setw(10) << courses[i].code
             << fixed << setprecision(1) << setw(10) << courses[i].credits
             << setw(10) << courses[i].score
             << setw(10) << gb.letter
             << fixed << setprecision(2) << gb.points << endl;
    }

    double gpa = computeGPA();
    double creditsEarned = computeCreditsEarned();

    string standing = (gpa < 2.00) ? "Academic Probation" : "Good Standing";

    cout << fixed << setprecision(2) << "GPA: " << gpa
         << " Credits earned: " << setprecision(1) << creditsEarned
         << " Standing: " << standing << endl;
}

int Student::getCount() {
    return totalStudents;
}
