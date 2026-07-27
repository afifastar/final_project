// library.h
#ifndef LIBRARY_H
#define LIBRARY_H
#include <string>
#include <vector>

const int COURSE_SIZE = 6;

enum gender {
    male,
    female,
    other
};

class Student;
class Course;
class Program;

class Person{
    protected:
        std::string full_name;
        std::string date_of_birth;
        gender person_gender;

    public:
        Person();
        Person(std::string name, std::string dob, gender g);

        virtual ~Person() = 0;
        virtual void display() const;
        virtual std::string name() const = 0;
};

class Student: public Person {
    private:
        std::vector<Course*> courses;
        double GPA;

    public:
        Student();
        Student(std::string name, std::string dob, gender g, double gpa);
        Student(const Student& other);
        ~Student();

        void display() const;
        std::string name() const;
        void add_course(Course& course);

        friend class Program;
};

class Course {
    private:
        std::string course_name;
        std::string course_code;
        std::vector<Student*> students;

    public:
        Course();
        Course(std::string name, std::string code);
        ~Course();

        void display() const;
        std::string code() const;
        void add_student(Student& student);
        void display_students() const;
};

class Program {
    private:
        std::string program_name;
        std::vector<Student*> students;
        std::vector<Course*> courses;

    public:
        Program(std::string name);
        ~Program();

        void add_student(Student& student);
        void add_course(Course& course);
        void honours_list();
        void save_to_file(const std::string& filename) const;
        void load_from_file(const std::string& filename);
};
#endif