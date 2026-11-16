#include "Student.h"
#include <iostream>
#include <iomanip>

Student::Student(std::string id, std::string n, Date d) 
    : ID(id), name(n), admissionDate(d) {}

bool Student::operator<(const Student& other) const {
    return this->transcript.computeGPA() < other.transcript.computeGPA();
}

void Student::printHeader() const {
    std::cout << "Name: " << name << "  ID: " << ID 
              << "  Admitted: " << admissionDate.day << "/" 
              << admissionDate.month << "/" << admissionDate.year << "\n";
}

UndergraduateStudent::UndergraduateStudent(std::string id, std::string n, Date d, std::string m, int lvl)
    : Student(id, n, d), major(m), level(lvl) {}

void UndergraduateStudent::printHeader() const {
    std::cout << "Name: " << name << "  ID: " << ID 
              << "  Admitted: " << admissionDate.day << "/" 
              << admissionDate.month << "/" << admissionDate.year << "\n";
    std::cout << "Programme: " << major << "  Level: " << level << "\n";
}

// Prefix ++
UndergraduateStudent& UndergraduateStudent::operator++() {
    level = (level + 100 > 400) ? 400 : level + 100;
    return *this;
}

// Postfix ++
int UndergraduateStudent::operator++(int) {
    int oldLevel = level;
    level = (level + 100 > 400) ? 400 : level + 100;
    return oldLevel;
}