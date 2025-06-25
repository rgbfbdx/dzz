// Student.h
#ifndef STUDENT_H
#define STUDENT_H
#include <string>
using namespace std;

class Student {
public:
    string name;
    int age;
    string university;
    double grade;

    Student();
    Student(string n, int a, string u, double g);
};

#endif

// Student.cpp
#include "Student.h"

Student::Student() {
    name = "";
    age = 0;
    university = "";
    grade = 0.0;
}

Student::Student(string n, int a, string u, double g) {
    name = n;
    age = a;
    university = u;
    grade = g;
}

// Group.h
#ifndef GROUP_H
#define GROUP_H
#include "Student.h"

class Group {
private:
    string groupName;
    Student* students;
    int size;
    int capacity;
    void resize();

public:
    Group(string name);
    ~Group();

    void addStudent(const Student& s);
    void removeStudent(int index);
    void showStudents() const;
    string getGroupName() const;
    void setGroupName(string name);
};

#endif

// Group.cpp
#include "Group.h"
#include <iostream>
using namespace std;

Group::Group(string name) {
    groupName = name;
    size = 0;
    capacity = 2;
    students = new Student[capacity];
}

Group::~Group() {
    delete[] students;
}

void Group::resize() {
    capacity *= 2;
    Student* temp = new Student[capacity];
    for (int i = 0; i < size; i++) {
        temp[i] = students[i];
    }
    delete[] students;
    students = temp;
}

void Group::addStudent(const Student& s) {
    if (size >= capacity) resize();
    students[size++] = s;
}

void Group::removeStudent(int index) {
    if (index < 0 || index >= size) return;
    for (int i = index; i < size - 1; i++) {
        students[i] = students[i + 1];
    }
    size--;
}

void Group::showStudents() const {
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". Name: " << students[i].name
             << ", Age: " << students[i].age
             << ", University: " << students[i].university
             << ", Grade: " << students[i].grade << endl;
    }
}

string Group::getGroupName() const {
    return groupName;
}

void Group::setGroupName(string name) {
    groupName = name;
}

// main.cpp
#include "Group.h"
#include <iostream>
using namespace std;

int main() {
    Group* group = nullptr;
    int choice;

    do {
        cout << "1. Create Group\n2. Add Student\n3. Remove Student\n4. Show Students\n0. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string name;
            cout << "Enter group name: ";
            getline(cin, name);
            delete group;
            group = new Group(name);
        } else if (choice == 2 && group) {
            string name, university;
            int age;
            double grade;
            cout << "Enter student name: "; getline(cin, name);
            cout << "Enter age: "; cin >> age;
            cin.ignore();
            cout << "Enter university: "; getline(cin, university);
            cout << "Enter grade: "; cin >> grade;
            cin.ignore();
            group->addStudent(Student(name, age, university, grade));
        } else if (choice == 3 && group) {
            int index;
            cout << "Enter student index to remove: ";
            cin >> index;
            cin.ignore();
            group->removeStudent(index - 1);
        } else if (choice == 4 && group) {
            group->showStudents();
        }
    } while (choice != 0);

    delete group;
    return 0;
}