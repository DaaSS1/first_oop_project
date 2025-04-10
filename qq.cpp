#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <numeric>
using namespace std;

class Group;
class Discipline;
class Person {
private:
     string name;
     int age;
public:
    Person() : name(""), age(0) {}
    Person(string n, int a) : name(n), age(a) {}

    string GetName() { return name; }
    int GetAge() const { return age; }

    void SetName(string n) { name = n; }
    void SetAge(int a) { age = a; }
    void Set(string n, int a) { name = n; age = a; }
    virtual void Show() {
        cout << "========================\n";
        cout << "Имя: " << name << "\n";
        cout << "Возраст: " << age << "\n";
        cout << "========================\n\n";
    }
};

class Student: public Person {
private:

    Group* group;
    vector<Discipline*> disciplines;

public:
    Student() : Person(), group(nullptr) {}
    Student(string n, int a) : Person(n, a), group(nullptr) {}


    Group* GetGroup() { return group; }

    void SetGroup(Group* g);
    void ShowGroup();
    void AddDiscipline(Discipline* discipline) { disciplines.push_back(discipline); }
    void ShowDisciplines();
    void ShowGrades();
    float GetAverageGrade();

    void Show(); // доработать имя
};

class Discipline {
private:
    string name;
    map<Student*, vector<float>> grades;

public:
    Discipline(string n) : name(n) {}

    string GetName() { return name; }
    void AddGrade(Student* student, float grade) {
        grades[student].push_back(grade);
    }
    vector<float> GetGrades(Student* student) {
        return grades.count(student) ? grades[student] : vector<float>();
    }
    float GetAverageGrade(Student* student) {
        if (!grades.count(student) || grades[student].empty()) return 0;
        const vector<float>& studentGrades = grades[student];
        return accumulate(studentGrades.begin(), studentGrades.end(), 0.0f) / studentGrades.size();
    }
    void ShowGrades();
    void ShowStudents();
};

class Group {
private:
    string groupName;
    vector<Student*> students;

public:
    Group(string gName) : groupName(gName) {}
    string GetGroupName() { return groupName; }
    void AddStudent(Student* student) { students.push_back(student); }
    void ShowStudents();
    void ShowGroupAverage();  // Новый метод для вывода среднего балла группы
    vector<Student*>& GetStudents() { return students; }

    float CalculateGroupAverage() {
        if (students.empty()) return 0;

        float totalSum = 0;
        int totalCount = 0;

        for (Student* student : students) {
            float studentAvg = student->GetAverageGrade();
            if (studentAvg > 0) {
                totalSum += studentAvg;
                totalCount++;
            }
        }

        return totalCount ? totalSum / totalCount : 0;
    }
};

void Student::SetGroup(Group* g) {
    group = g;
    g->AddStudent(this);
}

void Student::ShowGroup() {
    cout << (group ? "Группа: " + group->GetGroupName() : "Студент не прикреплен к группе.") << "\n";
}

void Student::ShowDisciplines() {
    cout << "Дисциплины:" << (disciplines.empty() ? " Нет дисциплин" : "") << "\n";
    for (Discipline* discipline : disciplines) {
        cout << " - " << discipline->GetName() << "\n";
    }
}

void Student::ShowGrades() {
    cout << "Оценки:" << (disciplines.empty() ? " Нет оценок" : "") << "\n";
    for (Discipline* discipline : disciplines) {
        vector<float> grades = discipline->GetGrades(this);
        cout << " - " << discipline->GetName() << ": ";
        if (grades.empty()) {
            cout << "нет оценок";
        } else {
            for (float grade : grades) {
                cout << grade << " ";
            }
            cout << "(среднее: " << discipline->GetAverageGrade(this) << ")";
        }
        cout << "\n";
    }
}

float Student::GetAverageGrade() {
    if (disciplines.empty()) return 0;
    float sum = 0;
    int count = 0;
    for (Discipline* discipline : disciplines) {
        float avg = discipline->GetAverageGrade(this);
        if (avg > 0) {
            sum += avg;
            count++;
        }
    }
    return count ? sum / count : 0;
}



void Discipline::ShowGrades() {
    cout << "=== Баллы по дисциплине: " << name << " ===\n";
    for (auto& pair : grades) {
        cout << pair.first->GetName() << ": ";
        for (float grade : pair.second) {
            cout << grade << " ";
        }
        cout << "(среднее: " << GetAverageGrade(pair.first) << ")\n";
    }
    cout << "============================\n\n";
}

void Discipline::ShowStudents() {
    cout << "=== Студенты, изучающие дисциплину: " << name << " ===\n";
    for (auto& pair : grades) {
        cout << " - " << pair.first->GetName() << "\n";
    }
    cout << "============================\n\n";
}

void Group::ShowStudents() {
    cout << "=== Студенты группы " << groupName << " ===\n";
    for (Student* student : students) {
        cout << " - " << student->GetName() << "\n";
    }
    cout << "============================\n\n";
}

void Group::ShowGroupAverage() {
    float avg = CalculateGroupAverage();
    cout << "=== Средний балл группы " << groupName << " ===\n";
    cout << "Средний балл: " << avg << "\n";
    cout << "============================\n\n";
}

int main() {
    Student student1("Иван Пензульский", 18);
    Student student2("Леха Маренков", 19);
    Student student3("Катя Ширшова", 18);
    Student student4("Женя Акмаев", 19);

    Group group1("ПИ-2024");
    Group group2("ИВТ-2023");

    student1.SetGroup(&group1);
    student2.SetGroup(&group1);
    student3.SetGroup(&group2);
    student4.SetGroup(&group2);

    Discipline math("Математика");
    Discipline physics("Физика");
    Discipline economics("Экономика");
    Discipline pe("Физра");
    Discipline oop("ООП");

    student1.AddDiscipline(&math);
    student1.AddDiscipline(&physics);
    student2.AddDiscipline(&math);
    student3.AddDiscipline(&economics);
    student3.AddDiscipline(&pe);
    student4.AddDiscipline(&oop);
    student4.AddDiscipline(&math);

    math.AddGrade(&student1, 4.5);
    math.AddGrade(&student1, 5.0);
    math.AddGrade(&student2, 5.0);
    math.AddGrade(&student2, 4.0);
    physics.AddGrade(&student1, 4.0);
    physics.AddGrade(&student1, 3.5);
    economics.AddGrade(&student3, 4.7);
    pe.AddGrade(&student3, 4.0);
    pe.AddGrade(&student3, 5.0);
    oop.AddGrade(&student4, 4.5);
    math.AddGrade(&student4, 4.86);
    math.AddGrade(&student4, 5.0);

    student1.Show();
    student2.Show();
    student3.Show();
    student4.Show();

    group1.ShowStudents();
    group2.ShowStudents();

    group1.ShowGroupAverage();
    group2.ShowGroupAverage();

    math.ShowGrades();
    physics.ShowGrades();
    economics.ShowGrades();
    pe.ShowGrades();
    oop.ShowGrades();

    return 0;
}

// добавить динамического добавление студентов
// добавить юнит-тесты