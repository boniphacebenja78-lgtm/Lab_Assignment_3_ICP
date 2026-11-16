#ifndef STUDENT_H
#define STUDENT_H

#include "Transcript.h"

// base Class Student
class Student {
protected:
    std::string ID;
    std::string name;
    Date admissionDate;
    Transcript transcript;

public:
    Student(std::string id, std::string n, Date d);
    virtual ~Student() = default;

    // overload to compare the GPAs
    bool operator<(const Student& other) const;
    
    virtual void printHeader() const;
};

// class UndergraduateStudent
class UndergraduateStudent : public Student {
private:
    std::string major;
    int level;

public:
    UndergraduateStudent(std::string id, std::string n, Date d, std::string m, int lvl);
    
    void printHeader() const override;

    // overload prexfix ++
    UndergraduateStudent& operator++();
    
    // overload postfix
    int operator++(int);
};

#endif