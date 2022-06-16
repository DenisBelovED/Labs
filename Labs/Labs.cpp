#include "people.h"

int main()
{
    std::string t("Anna Viktorovna");
    std::string s1("Misha");
    std::string s2("Vasya");
    std::string s3("Lena");
    std::string s4("Misha");
    auto s1p = new student(s2, 0.6);
    auto s2p = new student(s1, 0.3);
    auto s3p = new student(s3, 0.9);
    auto s4p = new student(s4, 0.1);

    teacher thr(t);
    auto students = new std::vector<student*>();
    students->push_back(s1p);
    students->push_back(s2p);
    students->push_back(s3p);
    students->push_back(s4p);

    for (auto st : *students)
        st->role();
    thr.role(students);
}