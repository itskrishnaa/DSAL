#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    string name, address;
    int rollno;
    char div;
};

void addData(int rollno, string name, string address, char div) {
    fstream file("student.txt", ios::out | ios::app);
    if (file) {
        file << rollno << "\n" << name << "\n" << div << "\n" << address << "\n";
        cout << "Student data added successfully!\n";
    } else {
        cout << "Error opening file!\n";
    }
}

void readData(int rollno) {
    fstream file("student.txt", ios::in);
    if (file) {
        Student s;
        bool found = false;
        while (file >> s.rollno) {
            file.ignore();
            getline(file, s.name);
            file >> s.div;
            file.ignore();
            getline(file, s.address);
            if (s.rollno == rollno) {
                cout << "Roll No: " << s.rollno << "\nName: " << s.name 
                     << "\nDivision: " << s.div << "\nAddress: " << s.address << endl;
                found = true;
                break;
            }
        }
        if (!found) cout << "No record found for Roll No " << rollno << endl;
    } else {
        cout << "Error opening file!\n";
    }
}

void deleteData(int rollno) {
    fstream file("student.txt", ios::in), temp("temp.txt", ios::out);
    if (file && temp) {
        Student s;
        bool found = false;
        while (file >> s.rollno) {
            file.ignore();
            getline(file, s.name);
            file >> s.div;
            file.ignore();
            getline(file, s.address);
            if (s.rollno != rollno) {
                temp << s.rollno << "\n" << s.name << "\n" << s.div << "\n" << s.address << "\n";
            } else {
                found = true;
            }
        }
        file.close();
        temp.close();
        remove("student.txt");
        rename("temp.txt", "student.txt");
        cout << (found ? "Record deleted!\n" : "No record found!\n");
    } else {
        cout << "Error opening file!\n";
    }
}

int main() {
    int choice, rollno;
    string name, address;
    char div;

    while (true) {
        cout << "\n1. Add Data\n2. Read Data\n3. Delete Data\n4. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                cout << "Name: "; getline(cin, name);
                cout << "Roll No: "; cin >> rollno;
                cout << "Division: "; cin >> div;
                cin.ignore();
                cout << "Address: "; getline(cin, address);
                addData(rollno, name, address, div);
                break;
            case 2:
                cout << "Roll No: "; cin >> rollno;
                readData(rollno);
                break;
            case 3:
                cout << "Roll No: "; cin >> rollno;
                deleteData(rollno);
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}