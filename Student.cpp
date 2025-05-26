#include <iostream>
#include <utility>
#include <list>
#include <map>
#include <algorithm>
#include <numeric>

class Student 
{
private:
    using Pair = std::pair<std::string, std::string>; // Имя и фамилия
    using Map = std::map<std::string, size_t>;        // Предмет -> оценка
    using ElementMap = std::pair<std::string, size_t>;   // Элемент Map

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
        return 0;
    }

    void printGrades() const 
    {
        std::cout << getFullName() << "'s\n";
        for (const auto& entry : grades) 
        {
            std::cout << "\t" << entry.first << ": " << entry.second << "\n";
        }
    }

    double getAverageGrade() const
    {
        if (grades.empty())
        {
            return 0.0;
        }

        double sum = std::accumulate(
            grades.begin(), grades.end(), 0.0,
            [](double acc, const ElementMap& pair)
            {
                return acc + pair.second;
            }
        );
        
        return sum / grades.size();
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
    }
    
    double getSubjectAverage(const std::string& subject) const
    {
        size_t count = 0;
        double sum = std::accumulate(
            students.begin(), students.end(), 0.0,
            [&](double acc, const Student& student)
            {
                size_t grade = student.getGrade(subject);
                if (grade > 0) 
                {
                    ++count;
                    return acc + grade;
                }
                return acc;
            }
        );
        return count ? sum / count : 0.0; 
    }

    void printGroupInfo() const 
    {
        std::cout << "------ Group Subjects ------\n";
        for (const auto& subject : subjects) 
        {
            std::cout << "   -> " << subject;
			double average = getSubjectAverage(subject);
			if (average == 0.0)
			{
				std::cout << " (No grades assigned)\n";
			}
			else
			{
				std::cout << " (Average: " << average << ")\n";
			}
		}

        std::cout << "\n------ Student's performance ------\n\n";
        for (const auto& student : students) 
        {
            std::cout << "   -> ";
            student.printGrades();
			std::cout << "\tAVERAGE GRADE: " << student.getAverageGrade() << "\n";
            std::cout<<"   ------------------------------\n";
        }
    }


};

int main() 
{
    Group group;

    for(const auto& subject : {"Economics","Psychology","Philosophy","Sociology", "Law" })
    {
        group.addSubject(subject);
    }

    Student s1("Petr", "Petrov");

    s1.addGrade("Economics", 90);
	s1.addGrade("Psychology", 85);
	s1.addGrade("Philosophy", 88);
	s1.addGrade("Sociology", 92);
	s1.addGrade("Law", 80);

    group.addStudent(s1); 
    group.addStudent(Student("Ivan", "Ivanov"));
	group.addStudent(Student("Sidor", "Sidorov"));

	group.assignGradeToStudent("Ivan Ivanov", "Economics", 85);
	group.assignGradeToStudent("Ivan Ivanov", "Psychology", 88);
	group.assignGradeToStudent("Ivan Ivanov", "Philosophy", 92);
	group.assignGradeToStudent("Ivan Ivanov", "Sociology", 80);
	group.assignGradeToStudent("Ivan Ivanov", "Law", 75);

	group.assignGradeToStudent("Sidor Sidorov", "Economics", 70);
	group.assignGradeToStudent("Sidor Sidorov", "Psychology", 68);
	group.assignGradeToStudent("Sidor Sidorov", "Philosophy", 72);
	group.assignGradeToStudent("Sidor Sidorov", "Sociology", 65);
    group.assignGradeToStudent("Sidor Sidorov", "Law", 75);

    group.printGroupInfo();


    return 0;
}
