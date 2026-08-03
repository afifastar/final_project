// library.cpp
#include "library.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

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
// COURSE CLASS
Course::Course()
    : course_name{""}, course_code{""} {}

Course::Course(std::string name, std::string code)
    : course_name{name}, course_code{code} {}

Course::~Course() {
    std::cout << "Course Object has been destroyed" << std::endl;
}

void Course::display() const {
    std::cout << course_name << " (" << course_code << ") "
              << students.size() << " student(s) enrolled" << std::endl;
}

std::string Course::code() const {
    return course_code;
}

std::string Course::name() const {
    return course_name;
}

void Course::add_student(Student& student) {
    // if already enrolled, do nothing
    if (std::find(students.begin(), students.end(), &student) != students.end()) {
        return;
    }

    if (students.size() >= static_cast<size_t>(COURSE_SIZE)) {
        throw "Course is already full.";
    }

    students.push_back(&student);
}

void Course::display_students() const {
    std::cout << "Students enrolled in " << course_code << ":" << std::endl;
    std::for_each(students.begin(), students.end(),
        [](Student* s) {
            std::cout << s->name() << std::endl;
        });
}

// PROGRAM CLASS
Program::Program(std::string name)
    : program_name{name} {}

Program::~Program() {
    students.clear();
    courses.clear();
    std::cout << "Program Object has been destroyed" << std::endl;
}

void Program::add_student(Student& student) {
    if (std::find(students.begin(), students.end(), &student) == students.end()) {
        students.push_back(&student);
    }
}

void Program::add_course(Course& course) {
    if (std::find(courses.begin(), courses.end(), &course) == courses.end()) {
        courses.push_back(&course);
    }
}

void Program::honours_list() {
    const double HONOURS_CUTOFF = 3.5;

    std::vector<Student*> honours_students;
    honours_students.reserve(students.size());

    std::copy_if(students.begin(), students.end(), std::back_inserter(honours_students),
                 [HONOURS_CUTOFF](Student* s) {
                     return s && s->GPA > HONOURS_CUTOFF;
                 });

    std::sort(honours_students.begin(), honours_students.end(),
              [](Student* a, Student* b) {
                  return a->GPA > b->GPA;
              });

    std::cout << "Honours list for " << program_name << ":" << std::endl;
    std::for_each(honours_students.begin(), honours_students.end(),
                  [](Student* s) {
                      std::cout << s->name() << " - GPA: " << s->GPA << std::endl;
                  });
}

void Program::save_to_file(const std::string& filename) const {
    std::ofstream output_file(filename);
    if (!output_file) {
        std::cerr << "Error: Could not open " << filename << " for writing." << std::endl;
        return;
    }

    // Format:
    // Line1: program_name
    // Line2: number_of_courses
    // Next N lines: course_code,course_name
    // Next line: number_of_students
    // Next M lines: full_name,date_of_birth,gender_int,GPA,code1;code2;...

    output_file << program_name << '\n';
    output_file << courses.size() << '\n';

    std::for_each(courses.begin(), courses.end(), [&output_file](const Course* course) {
        output_file << course->code() << ',' << course->name() << '\n';
    });

    output_file << students.size() << '\n';

    std::for_each(students.begin(), students.end(), [&output_file](const Student* student) {
        // build semicolon-separated course code list
        std::string codes;
        for (size_t i = 0; i < student->courses.size(); ++i) {
            const Course* c = student->courses[i];
            if (!c) continue;
            if (!codes.empty()) codes += ';';
            codes += c->code();
        }

        output_file << student->full_name << ','
                    << student->date_of_birth << ','
                    << static_cast<int>(student->person_gender) << ','
                    << student->GPA << ','
                    << codes << '\n';
    });
}

void Program::load_from_file(const std::string& filename) {
    std::ifstream input_file(filename);
    if (!input_file) {
        std::cerr << "Error: Could not open " << filename << " for reading." << std::endl;
        return;
    }

    // Clear current pointers (do not delete objects; header doesn't provide ownership tracking)
    students.clear();
    courses.clear();

    std::string line;

    if (!std::getline(input_file, program_name)) return;

    if (!std::getline(input_file, line)) return;
    int course_count = 0;
    try { course_count = std::stoi(line); } catch(...) { course_count = 0; }

    for (int i = 0; i < course_count; ++i) {
        if (!std::getline(input_file, line)) break;
        std::stringstream course_stream(line);
        std::string course_code;
        std::string course_name;
        std::getline(course_stream, course_code, ',');
        std::getline(course_stream, course_name);
        // create course on heap so program's courses vector can point to it
        Course* new_course = new Course(course_name, course_code);
        courses.push_back(new_course);
    }

    if (!std::getline(input_file, line)) return;
    int student_count = 0;
    try { student_count = std::stoi(line); } catch(...) { student_count = 0; }

    for (int i = 0; i < student_count; ++i) {
        if (!std::getline(input_file, line)) break;
        std::stringstream student_stream(line);
        std::string student_name;
        std::string dob;
        std::string gender_value;
        std::string gpa_value;
        std::string course_list;

        std::getline(student_stream, student_name, ',');
        std::getline(student_stream, dob, ',');
        std::getline(student_stream, gender_value, ',');
        std::getline(student_stream, gpa_value, ',');
        std::getline(student_stream, course_list);

        int gender_int = 2;
        double gpa = 0.0;
        try { gender_int = std::stoi(gender_value); } catch(...) { gender_int = 2; }
        try { gpa = std::stod(gpa_value); } catch(...) { gpa = 0.0; }

        Student* new_student = new Student(student_name, dob, static_cast<gender>(gender_int), gpa);
        students.push_back(new_student);

        // parse course codes separated by ';'
        std::stringstream cs(course_list);
        std::string code;
        while (std::getline(cs, code, ';')) {
            if (code.empty()) continue;
            auto it = std::find_if(courses.begin(), courses.end(), [&code](Course* c){
                return c && c->code() == code;
            });
            Course* found = nullptr;
            if (it != courses.end()) {
                found = *it;
            } else {
                Course* nc = new Course("", code);
                courses.push_back(nc);
                found = nc;
            }
            new_student->add_course(*found);
        }
    }
}
