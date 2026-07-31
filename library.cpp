// library.cpp
#include "library.h"
#include <iostream>
#include <algorithm>
#include <fstream>

// AFIFA KHALID: RESPONSIBLE FOR THE CLASSES PERSON AND STUDENT
// PERSON CLASS
Person::Person() : full_name{""}, date_of_birth{""}, person_gender{other}{}

Person::Person(std::string name, std::string dob, gender g) 
    : full_name{name}, date_of_birth{dob}, person_gender{g} {}

Person::~Person(){}

void Person::display() const{
    std::cout << full_name << " " << date_of_birth << " " ;

    if(person_gender == male){
        std::cout << "male";
    } else if (person_gender == female){
        std::cout << "female";
    } else {
        std::cout << "other";
    }
}

// STUDENT CLASS
Student::Student() : Person{}, GPA{0.0}{}

Student::Student(std::string name, std::string dob, gender g, double gpa)
    : Person{name, dob, g}, GPA{gpa}{}

Student::Student(const Student& other)
    : Person{other.full_name, other.date_of_birth, other.person_gender}, courses{other.courses}, GPA{other.GPA}{}

Student::~Student(){
    std::cout << "Student Object has been destroyed" << std::endl;
}

void Student::display() const{
    Person::display();
    std::cout << " " << GPA << std::endl;
}

std::string Student::name() const{
    return full_name;
}

void Student::add_course(Course& course){
    try{
        course.add_student(*this);
        courses.push_back(&course);
    } catch(const char* error){
        std::cerr << "Error: " << error << std::endl; 
    }
}

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
// MOHAMMAD ZAKARI: RESPONSIBLE FOR THE CLASSES COURSE AND PROGRAM