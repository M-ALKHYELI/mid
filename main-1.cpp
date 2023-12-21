#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Base class
class Course {
public:
    string courseCode;
    string courseTitle;
    int maxCapacity;
    int currentEnrollment;

    Course(string code, string title, int capacity)
        : courseCode(code), courseTitle(title), maxCapacity(capacity), currentEnrollment(0) {}

    virtual void displayDetails() const {
        cout << "Course Code: " << courseCode << ", ";
        cout << "Course Title: " << courseTitle << ", ";
        cout << "Max Capacity: " << maxCapacity << ", ";
        cout << "Current Enrollment: " << currentEnrollment << ", ";
    }

    virtual void editDetails() {
        cout << endl;
        cout << "Enter new course title: ";
        cin >> courseTitle;
        cout << "Enter new max capacity: ";
        cin >> maxCapacity;
    }

    virtual bool checkEligibility() const {
        return true;
    }
};

// Derived class for required courses
class RequiredCourse : public Course {
public:
    string prerequisite;

    RequiredCourse(string code, string title, int capacity, string prereq)
        : Course(code, title, capacity), prerequisite(prereq) {}

    void displayDetails() const override {
        Course::displayDetails();
        cout << "Prerequisite: " << prerequisite << endl;
    }

    void editDetails() override {
        Course::editDetails();
        cout << "Enter new prerequisite: ";
        cin >> prerequisite;
    }

    bool checkEligibility() const {
        string prereq;
        cout << "\nEnter your pre-requisite course: ";
        cin >> prereq;
        return prerequisite == prereq;
    }
};

// Derived class for elective courses
class ElectiveCourse : public Course {
public:
    int minimumLevel;

    ElectiveCourse(string code, string title, int capacity, int minLevel)
        : Course(code, title, capacity), minimumLevel(minLevel) {}

    void displayDetails() const override {
        Course::displayDetails();
        cout << "Minimum Level: " << minimumLevel << endl;
    }

    void editDetails() override {
        Course::editDetails();
        cout << "Enter new minimum level: ";
        cin >> minimumLevel;
    }

    bool checkEligibility() const {
        int level;
        cout << "\nEnter your level: ";
        cin >> level;
        return level >= minimumLevel;
    }
};

int main() {
    vector<Course*> courses;
    cout << "***************************Welcome to ULV**************************" << endl;

    while (true) {
        cout << "\nChoose one of the following options: \n" << endl;
        cout << "   (1) Add a Class\n";
        cout << "   (2) Edit a Class\n";
        cout << "   (3) Register a Class\n";
        cout << "   (4) Drop a Class\n";
        cout << "   (5) Override a Class\n";
        cout << "   (0) Exit\n";
        cout<<"\nEnter the option: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string code, title;
                int capacity, courseType;

                cout << "\nEnter course type (1 for Required, 2 for Elective): ";
                cin >> courseType;
                if(courseType == 1 || courseType == 2) {
                    cout << "\nEnter course code: ";
                    cin >> code;
                    cout << "Enter course title: ";
                    cin >> title;
                    cout << "Enter max capacity: ";
                    cin >> capacity;

                    if (courseType == 1) {
                        string prereq;
                        cout << "Enter prerequisite: ";
                        cin >> prereq;
                        Course *crs = new RequiredCourse(code, title, capacity, prereq);
                        courses.push_back(crs);
                    } else if (courseType == 2) {
                        int minLevel;
                        cout << "Enter minimum level: ";
                        cin >> minLevel;
                        Course *crs = new ElectiveCourse(code, title, capacity, minLevel);
                        courses.push_back(crs);
                    }
                    cout << "\n  > Class added successfully!" << endl;
                }
                else {
                    cout << "\n  > Invalid course type!" << endl;
                }
                break;
            }

            case 2: {
                cout << "\nEnter course code: ";
                string code;
                cin >> code;

                bool found = false;
                for (Course* course : courses) {
                    if (course->courseCode == code) {
                        cout<<"\n  > Course found!" <<endl <<endl;
                        course->displayDetails();
                        course->editDetails();
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "\n  > Course not found!" << endl;
                }
                else {
                    cout << "\n  > Course modified successfully!" << endl;
                }

                break;
            }

            case 3: {

                if(courses.size() == 0) {
                    cout << "\n  > No classes available!" << endl;
                }
                else {
                    cout << "\nAvailable Classes:" << endl <<endl;
                    for (const Course* course : courses) {
                        course->displayDetails();
                    }

                    cout << "\nEnter course code to register: ";
                    string code;
                    cin >> code;

                    for (Course* course : courses) {
                        if (course->courseCode == code) {
                            if (course->checkEligibility()) {
                                course->currentEnrollment++;
                                cout << "\n  > Student enrolled successfully!" << endl;
                            } else {
                                cout << "\n  > Student is not eligible to enroll in this course!" << endl;
                            }
                            break;
                        }
                    }
                }
                break;
            }

            case 4: {
                cout << "\nEnter course code to drop: ";
                string code;
                cin >> code;
                bool found = false;
                for (Course* course : courses) {
                    if (course->courseCode == code) {
                        if(course->currentEnrollment == 0) {
                            cout << "\n  > No student enrolled in this course!" << endl;
                        }
                        else {
                            course->currentEnrollment--;
                            cout << "\n  > Student dropped successfully!" << endl;
                        }
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "\n  > Course not found!" << endl;
                }
                break;
            }

            case 5: {
                cout << "\nEnter course code: ";
                string code;
                cin >> code;

                bool found = false;
                for (Course* course : courses) {
                    if (course->courseCode == code) {
                        cout<<"\n  > Course found!" <<endl <<endl;
                        course->displayDetails();
                        course->editDetails();
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "\n  > Course not found!" << endl;
                }
                else {
                    cout << "\n  > Course override successfully!" << endl;
                }
                break;
            }

            case 0: {
                // Deallocating memory while exiting
                for (Course* course : courses) {
                    delete course;
                }
                break;
            }

            default:
                cout << "\n  > Invalid choice!" << endl;
        }

        if(choice == 0)
            break;
    }

    return 0;
}
