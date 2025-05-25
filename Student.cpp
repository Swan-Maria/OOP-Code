#include <iostream>
#include <utility>
#include <list>
#include <map>
#include <algorithm>

class Student 
{
private:
    using Pair = std::pair<std::string, std::string>; // Имя и фамилия
    using Map = std::map<std::string, size_t>;        // Предмет -> оценка

    Pair student;
    Map grades;

public:
    Student(const std::string& firstName, const std::string& lastName)
        : student(firstName, lastName) 
    { }

    void addGrade(const std::string& subject, size_t grade) 
    {
        grades[subject] = grade;
    }

    std::string getFullName() const 
    {
        return student.first + " " + student.second;
    }

    size_t getGrade(const std::string& subject) const 
    {
        auto it = grades.find(subject);
        if (it != grades.end()) 
        {
            return it->second;
        }
        std::cerr<<"Subject not found.";
    }

    void printGrades() const 
    {
        std::cout << getFullName() << "'s\n";
        for (const auto& entry : grades) 
        {
            std::cout << "\t" << entry.first << ": " << entry.second << "\n";
        }
    }
};

class Group
{
private:
    using Students = std::list<Student>;
    using Subjects = std::list<std::string>;

    Students students;
    Subjects subjects;

public:

    void addSubject(const std::string& subject) 
    {
        subjects.push_back(subject);
    }

    void addStudent(const Student& student) 
    {
        students.push_back(student);
    }

    void assignGradeToStudent(const std::string& fullName, const std::string& subject, size_t grade) 
    {
        auto it = std::find_if
        (
            students.begin(), 
            students.end(), 
            [fullName](const Student& s) {return s.getFullName() == fullName;}
        );

        if (it != students.end()) 
        {
            it->addGrade(subject, grade);
        }
        else 
        {
           std::cerr<<"Student not found.";
        }
    }
    
    void printGroupInfo() const 
    {
        std::cout << "--- Group Subjects ---\n";
        for (const auto& subject : subjects) 
        {
            std::cout << "   -> " << subject << "\n";
        }

        std::cout << "\n--- Student's performance ---\n";
        for (const auto& student : students) 
        {
            std::cout << "   -> ";
            student.printGrades();
            //std::cout << "\n";
        }
    }
};

int main() 
{
    Group group;

    for(const auto& subject : {"Math Logic", "Operating Systems", "OOP", "DSA"}) 
    {
        group.addSubject(subject);
    }

    Student s1("Maria", "Lebedieva");

    s1.addGrade("OOP", 95);
    s1.addGrade("DSA", 95);

    group.addStudent(s1); 
    group.addStudent(Student("Daria", "Togan"));

    group.assignGradeToStudent("Daria Togan", "OOP", 95);
    group.assignGradeToStudent("Daria Togan", "DSA", 95);

    group.printGroupInfo();

    return 0;
}
