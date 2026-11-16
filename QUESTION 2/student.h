#ifndef STUDENT_H
#define STUDENT_H

#include "Transcript.h"

// 2b. Base Class Student
class Student {
protected:
    std::string ID;
    std::string name;
    Date admissionDate;
    Transcript transcript;

public:
    Student(std::string id, std::string n, Date d);
    virtual ~Student() = default;

    // 2c. Overload < to compare GPAs
    bool operator<(const Student& other) const;
    
    // Virtual print function (will be overridden)
    virtual void printHeader() const;
};

// 2b. Derived Class UndergraduateStudent
class UndergraduateStudent : public Student {
private:
    std::string major;
    int level;

public:
    UndergraduateStudent(std::string id, std::string n, Date d, std::string m, int lvl);
    
    // Override header printing
    void printHeader() const override;

    // 2c. Overload ++ (prefix)
    UndergraduateStudent& operator++();
    
    // 2c. Overload ++ (postfix)
    int operator++(int);
};

#endif