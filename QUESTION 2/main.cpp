#include <iostream>
#include "Student.h"

// is failing functions
bool isFailing(const CourseRecord& c) {
    return c.score < 50;
}

int main() {
    // creating first student table 
    UndergraduateStudent s1("61242027", "Ama Serwaa Mensah", {12, 8, 2024}, "Computer Science", 200);
    
    // Print student header
    s1.printHeader();

    return 0;
}