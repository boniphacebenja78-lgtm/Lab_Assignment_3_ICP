
#include <iostream>
#include <string>
#include <limits>
#include "student.h"

using namespace std;

int main() {
    string tempID, tempName;

    while (true) {
        cin >> tempID;

        if (tempID == "0") {
            break;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, tempName);

        Date d;
        cin >> d.day >> d.month >> d.year;

        Student s(tempID, tempName, d);

        string courseCode;
        double credits;
        int score;

        while (true) {
            cin >> courseCode;

            if (courseCode == "END") {
                break;
            }

            cin >> credits >> score;

            if (score < 0 || score > 100) {
                cout << "Invalid score " << score << " for "
                     << courseCode << "; course skipped" << endl;
            } else {
                s.addCourse(courseCode, credits, score);
            }
        }

        s.printTranscript();

        cout << endl;
    }

    cout << "Students processed: " << Student::getCount() << endl;

    return 0;
}
