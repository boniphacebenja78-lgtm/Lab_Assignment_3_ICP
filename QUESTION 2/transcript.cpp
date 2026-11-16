#include "Transcript.h"
#include <iomanip>

// grade table
GradeBand gradeTable[] = {
    {80, "A", 4.0}, {75, "B+", 3.5}, {70, "B", 3.0}, {65, "C+", 2.5},
    {60, "C", 2.0}, {55, "D+", 1.5}, {50, "D", 1.0}, {0, "F", 0.0}
};

GradeBand lookupGrade(int score) {
    for (int i = 0; i < 8; i++) {
        int maxScore = (i == 0) ? 100 : gradeTable[i-1].minScore - 1;
        if (score >= gradeTable[i].minScore && score <= maxScore) return gradeTable[i];
    }
    return gradeTable[7];
}

Transcript::Transcript() {
    capacity = 2;
    count = 0;
    courses = new CourseRecord[capacity];
}

Transcript::~Transcript() {
    delete[] courses;
}

//overload to add course records
Transcript& Transcript::operator+=(const CourseRecord& c) {
    if (count == capacity) {
        capacity *= 2;
        CourseRecord* newCourses = new CourseRecord[capacity];
        for (int i = 0; i < count; i++) {
            newCourses[i] = courses[i];
        }
        delete[] courses;
        courses = newCourses;
    }
    courses[count++] = c;
    return *this;
}

//oveload to print course table
std::ostream& operator<<(std::ostream& os, const Transcript& t) {
    os << std::left << std::setw(10) << "Course" << std::setw(10) << "Credits" 
       << std::setw(10) << "Score" << std::setw(10) << "Grade" << "Points\n";
    
    for (int i = 0; i < t.count; i++) {
        GradeBand gb = lookupGrade(t.courses[i].score);
        os << std::left << std::setw(10) << t.courses[i].code
           << std::fixed << std::setprecision(1) << std::setw(10) << t.courses[i].credits
           << std::setw(10) << t.courses[i].score
           << std::setw(10) << gb.letter
           << std::fixed << std::setprecision(2) << gb.points << "\n";
    }
    
    os << "GPA: " << std::fixed << std::setprecision(2) << t.computeGPA() 
       << "  Credits earned: " << std::setprecision(1) << t.computeCreditsEarned() << "\n";
    return os;
}

double Transcript::computeGPA() const {
    double totalPoints = 0, totalCredits = 0;
    for (int i = 0; i < count; i++) {
        GradeBand gb = lookupGrade(courses[i].score);
        totalPoints += (gb.points * courses[i].credits);
        totalCredits += courses[i].credits;
    }
    return (totalCredits == 0) ? 0.0 : totalPoints / totalCredits;
}

double Transcript::computeCreditsEarned() const {
    double earned = 0;
    for (int i = 0; i < count; i++) {
        if (courses[i].score >= 50) earned += courses[i].credits;
    }
    return earned;
}

//print course that meet the conditions
void Transcript::printWhere(bool (*keep)(const CourseRecord&)) {
    std::cout << std::left << std::setw(10) << "Course" << std::setw(10) << "Credits" 
              << std::setw(10) << "Score" << std::setw(10) << "Grade" << "Points\n";
    for (int i = 0; i < count; i++) {
        if (keep(courses[i])) {
            GradeBand gb = lookupGrade(courses[i].score);
            std::cout << std::left << std::setw(10) << courses[i].code
                      << std::fixed << std::setprecision(1) << std::setw(10) << courses[i].credits
                      << std::setw(10) << courses[i].score
                      << std::setw(10) << gb.letter
                      << std::fixed << std::setprecision(2) << gb.points << "\n";
        }
    }
}