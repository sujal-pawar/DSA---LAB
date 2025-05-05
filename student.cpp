#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int roll;
    string name;
    char division;
    string address;

    void input() {
        cout << "Enter Roll No: ";
        cin >> roll;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Division (A/B/C): ";
        cin >> division;
        cin.ignore();
        cout << "Enter Address: ";
        getline(cin, address);
    }

    void display() {
        cout << "\nRoll No: " << roll
             << "\nName: " << name
             << "\nDivision: " << division
             << "\nAddress: " << address << endl;
    }
};

// Function to add a record
void addRecord() {
    ofstream file("student.txt", ios::app);
    Student s;
    s.input();
    file << s.roll << "\n" << s.name << "\n" << s.division << "\n" << s.address << "\n";
    file.close();
    cout << "Record added successfully.\n";
}

// Function to display a particular student
void displayStudent(int rollNo) {
    ifstream file("student.txt");
    Student s;
    bool found = false;

    while (file >> s.roll) {
        file.ignore();
        getline(file, s.name);
        file >> s.division;
        file.ignore();
        getline(file, s.address);

        if (s.roll == rollNo) {
            s.display();
            found = true;
            break;
        }
    }

    file.close();
    if (!found)
        cout << "Student record not found.\n";
}

// Function to delete a student record
void deleteStudent(int rollNo) {
    ifstream file("student.txt");
    ofstream temp("temp.txt");
    Student s;
    bool found = false;

    while (file >> s.roll) {
        file.ignore();
        getline(file, s.name);
        file >> s.division;
        file.ignore();
        getline(file, s.address);

        if (s.roll != rollNo) {
            temp << s.roll << "\n" << s.name << "\n" << s.division << "\n" << s.address << "\n";
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();
    remove("student.txt");
    rename("temp.txt", "student.txt");

    if (found)
        cout << "Record deleted successfully.\n";
    else
        cout << "Student record not found.\n";
}

// Main function
int main() {
    int choice, rollNo;

    do {
        cout << "\n=== Student Record Menu ===\n";
        cout << "1. Add Student\n";
        cout << "2. Display Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                cout << "Enter Roll No to search: ";
                cin >> rollNo;
                displayStudent(rollNo);
                break;
            case 3:
                cout << "Enter Roll No to delete: ";
                cin >> rollNo;
                deleteStudent(rollNo);
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
