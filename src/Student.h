#include <string>
#include <utility>
#pragma once
using namespace std;

class Student {
    // Student name and Gator ID
    string NAME;
    string ID;
public:
    // Default constructor
    Student() = default;

    // Constructor with name and ID parameters
    Student(string name, string id) {
        NAME = name;
        ID = id;
    }

    // Getter methods
    string getID() {
        return ID;
    }

    string getName() {
        return NAME;
    }
};