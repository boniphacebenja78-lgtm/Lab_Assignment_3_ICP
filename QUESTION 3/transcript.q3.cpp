#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <iomanip>

using namespace std;

// ==========================================
// Part A: Structs and Custom Exceptions
// ==========================================

struct Course {
    string code;
    string title;
    double credits;
    int score;
};

struct Student {
    string ID;
    string name;
    vector<Course> courses;
};

// Custom Exception for invalid score
class InvalidScoreException : public invalid_argument {
public:
    InvalidScoreException(const string& msg) : invalid_argument(msg) {}
};

// Custom Exception for unknown student ID
class UnknownStudentException : public runtime_error {
public:
    UnknownStudentException(const string& msg) : runtime_error(msg) {}
};

// Helper function for grade lookup (from previous questions)
string getLetterGrade(int score) {
    if (score >= 80) return "A";
    if (score >= 75) return "B+";
    if (score >= 70) return "B";
    if (score >= 65) return "C+";
    if (score >= 60) return "C";
    if (score >= 55) return "D+";
    if (score >= 50) return "D";
    return "F";
}

double getGradePoints(int score) {
    if (score >= 80) return 4.0;
    if (score >= 75) return 3.5;
    if (score >= 70) return 3.0;
    if (score >= 65) return 2.5;
    if (score >= 60) return 2.0;
    if (score >= 55) return 1.5;
    if (score >= 50) return 1.0;
    return 0.0;
}

// ==========================================
// Main Function (Part B, C, D)
// ==========================================
int main() {
    ifstream infile("records.txt");
    ofstream errfile("errors.log");

    if (!infile.is_open()) {
        cerr << "Error: Could not open records.txt" << endl;
        return 1;
    }

    map<string, Student> students;
    string line;
    int lineNumber = 0;

    // --- Part B: Read file line by line ---
    while (getline(infile, line)) {
        lineNumber++;
        if (line.empty()) continue;

        try {
            istringstream iss(line);
            string type;
            iss >> type;

            if (type == "STUDENT") {
                string id, name;
                iss >> id;
                
                // Read quoted name
                char quote;
                iss >> quote; // read opening quote
                if (quote != '"') {
                    throw runtime_error("Malformed name: missing opening quote");
                }
                getline(iss, name, '"'); // read until closing quote
                
                students[id] = {id, name, {}};
            } 
            else if (type == "COURSE") {
                string id, code, title;
                double credits;
                int score;
                
                iss >> id >> code;
                
                // Read quoted title
                char quote;
                iss >> quote;
                if (quote != '"') {
                    throw runtime_error("Malformed title: missing opening quote");
                }
                getline(iss, title, '"');
                
                iss >> credits >> score;

                // Check if student exists
                if (students.find(id) == students.end()) {
                    throw UnknownStudentException("Unknown student ID: " + id);
                }

                // Check if score is valid
                if (score < 0 || score > 100) {
                    throw InvalidScoreException("Score " + to_string(score) + " out of range 0-100 for course " + code);
                }

                students[id].courses.push_back({code, title, credits, score});
            } 
            else {
                // Part C: runtime_error for lines not starting with STUDENT or COURSE
                throw runtime_error("Line does not start with STUDENT or COURSE");
            }

        } 
        // --- Part C: Catch exceptions by const reference, most specific first ---
        catch (const InvalidScoreException& e) {
            errfile << "Line " << lineNumber << ": InvalidScoreException - " << e.what() << endl;
        } 
        catch (const UnknownStudentException& e) {
            errfile << "Line " << lineNumber << ": UnknownStudentException - " << e.what() << endl;
        } 
        catch (const runtime_error& e) {
            errfile << "Line " << lineNumber << ": runtime_error - " << e.what() << endl;
        }
    }

    infile.close();
    errfile.close();

    // --- Part D: Write transcript_<ID>.txt for each student ---
    for (auto const& [id, student] : students) {
        string filename = "transcript_" + id + ".txt";
        ofstream outfile(filename);

        outfile << "Name: " << student.name << "  ID: " << student.ID << "\n";
        outfile << left << setw(10) << "Code" 
                << setw(35) << "Title" 
                << setw(10) << "Credits" 
                << setw(10) << "Score" 
                << "Grade" << "\n";

        double totalPoints = 0;
        double totalCredits = 0;
        double creditsEarned = 0;

        for (const auto& course : student.courses) {
            string letter = getLetterGrade(course.score);
            outfile << left << setw(10) << course.code 
                    << setw(35) << course.title 
                    << fixed << setprecision(1) << setw(10) << course.credits 
                    << setw(10) << course.score 
                    << letter << "\n";

            totalPoints += (getGradePoints(course.score) * course.credits);
            totalCredits += course.credits;
            if (course.score >= 50) creditsEarned += course.credits;
        }

        double gpa = (totalCredits == 0) ? 0.0 : totalPoints / totalCredits;
        string standing = (gpa < 2.00) ? "Academic Probation" : "Good Standing";

        outfile << fixed << setprecision(2) << "GPA: " << gpa 
                << "  Credits earned: " << fixed << setprecision(1) << creditsEarned 
                << "  Standing: " << standing << "\n";

        outfile.close();
    }

    return 0;
}