#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <map>

class Date //日期
{
private:
    int year_, month_, day_;

public:
    Date(int year = 0, int month = 0, int day = 0); //构造函数
    Date(std::string &date, const char c = '/');    //以类似2001/1/2格式的参数构造Date,间隔符为char c
    Date(const Date &d);                            //复制构造函数
    ~Date();                                        //析构函数
    void SetYear(const int year = 0);
    void SetMonth(const int month = 0);
    void SetDay(const int day = 0);
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    void Print() const; //打印日期

    //重载比较符号，供map排序使用
    friend bool operator<(const Date &d1, const Date &d2);
    friend bool operator>(const Date &d1, const Date &d2);
    friend bool operator==(const Date &d1, const Date &d2);
};

class StudentInfo
{
public:
    int id_;
    std::string name_;
    std::string sex_;
    Date birthday_;
    int school_year_;
    std::string birthplace_;
    StudentInfo(const int id = 0, const std::string &name = 0, const std::string &sex = 0, const Date &birthday = 0, const int school_year = 0, const std::string &birthplace = 0);
    StudentInfo(const StudentInfo &s);
    ~StudentInfo();
    friend class Student;
};

class StudentCourse
{
public:
    int id_;
    std::map<std::string, std::pair<int, int>> Course_;
    StudentCourse(const int id = 0, const std::map<std::string, std::pair<int, int>> Course = std::map<std::string, std::pair<int, int>>());
    StudentCourse(const StudentCourse &s);
    ~StudentCourse();
    friend class Student;
};

class Student
{
public:
    int id_;
    std::string name_;
    std::string sex_;
    Date birthday_;
    int school_year_;
    std::string birthplace_;
    std::map<std::string, std::pair<int, int>> Course_;
    Student(const StudentInfo si, const StudentCourse sc = StudentCourse());
    Student(Student &s);
    ~Student();
    double Totalscore() const;//总分
    double Totalcredit() const;//总学分
    double averagescore() const;//平均分
    void print() const;
    bool operator<(Student &s); //重载各比较符号，为set自动排序以及删除函数服务
    bool operator>(Student &s);
    bool operator==(Student &s);
    friend class Student_manage;
};

bool operator<(const Date &d1, const Date &d2)
{
    bool m = false;
    if (d1.year_ < d2.year_)
    {
        m = true;
    }
    else if (d1.year_ == d2.year_)
    {
        if (d1.month_ < d2.month_)
        {
            m = true;
        }
        else if (d1.month_ == d2.month_)
        {
            if (d1.day_ < d2.day_)
            {
                m = true;
            }
        }
    }
    return m;
}
bool operator>(const Date &d1, const Date &d2)
{
    bool m = false;
    if (d1.year_ > d2.year_)
    {
        m = true;
    }
    else if (d1.year_ == d2.year_)
    {
        if (d1.month_ > d2.month_)
        {
            m = true;
        }
        else if (d1.month_ == d2.month_)
        {
            if (d1.day_ > d2.day_)
            {
                m = true;
            }
        }
    }
    return m;
}

bool operator==(const Date &d1, const Date &d2)
{

    return (d1.year_ == d2.year_ && d1.month_ == d2.month_ && d1.day_ == d2.day_);
}
Date::Date(int year, int month, int day) //构造函数
{
    year_ = year;
    month_ = month;
    day_ = day;
}
Date::Date(std::string &date, const char c)
{
    std::string t;
    std::stringstream d(date);
    getline(d, t, c);
    year_ = stoi(t);
    getline(d, t, c);
    month_ = stoi(t);
    getline(d, t, c);
    day_ = stoi(t);
}
Date::Date(const Date &d) //复制构造函数
{
    year_ = d.year_;
    month_ = d.month_;
    day_ = d.day_;
}
Date::~Date() //析构函数
{
}
void Date::SetYear(const int year)
{
    year_ = year;
}
void Date::SetMonth(const int month)
{
    month_ = month;
}
void Date::SetDay(const int day)
{
    day_ = day;
}

int Date::GetYear() const
{
    return year_;
}
int Date::GetMonth() const
{
    return month_;
}
int Date::GetDay() const
{
    return day_;
}
void Date::Print() const //打印日期
{
    std::cout << std::setw(4) << year_ << "/";
    if (month_ < 10)
    {
        std::cout << "0";
    }
    std::cout << month_ << "/";
    if (day_ < 10)
    {
        std::cout << "0";
    }
    std::cout << day_;
}

StudentInfo::StudentInfo(const int id, const std::string &name, const std::string &sex, const Date &birthday, const int school_year, const std::string &birthplace) : name_(name), sex_(sex), birthday_(birthday), birthplace_(birthplace)
{
    id_ = id;
    school_year_ = school_year;
}
StudentInfo::StudentInfo(const StudentInfo &s) : name_(s.name_), sex_(s.sex_), birthday_(s.birthday_), birthplace_(s.birthplace_)
{
    id_ = s.id_;
    school_year_ = s.school_year_;
}
StudentInfo::~StudentInfo()
{
}

StudentCourse::StudentCourse(const int id, std::map<std::string, std::pair<int, int>> Course)
{
    id_ = id;
    Course_ = Course;
}

StudentCourse::StudentCourse(const StudentCourse &s)
{
    id_ = s.id_;
    Course_ = s.Course_;
}
StudentCourse::~StudentCourse()
{
}

Student::Student(const StudentInfo si, const StudentCourse sc)
{
    id_ = si.id_;
    name_ = si.name_;
    sex_ = si.sex_;
    birthday_ = si.birthday_;
    school_year_ = si.school_year_;
    birthplace_ = si.birthplace_;
    Course_ = sc.Course_;
}
Student::Student(Student &s)
{
    id_ = s.id_;
    name_ = s.name_;
    sex_ = s.sex_;
    birthday_ = s.birthday_;
    school_year_ = s.school_year_;
    birthplace_ = s.birthplace_;
    Course_ = s.Course_;
}

Student::~Student()
{
}

void Student::print() const
{
    std::cout << std::setw(8) << id_ << std::setw(10) << name_ << std::setw(8) << sex_ << " ";
    birthday_.Print();
    std::cout << "  " << std::setw(6) << school_year_ << std::setw(12) << birthplace_ << std::endl;
    std::cout << "Course Information: " << std::endl;
    std::cout << std::setw(30) << "Course Name" << std::setw(10) << "Credits" << std::setw(10) << "Score" << std::endl;
    for (auto i : Course_)
    {
        std::cout << std::setw(30) << i.first << std::setw(10) << (i.second).first << std::setw(10) << (i.second).second << std::endl;
    }
    std::cout<<"Total score:"<<std::setw(5)<<Totalscore()<<"  Average:"<<std::setw(5)<<averagescore()<<std::endl;
}
double Student::Totalscore() const
{
    double Total = 0;
    for (auto i : Course_)
    {
        Total = Total + (i.second).second;
    }
    return Total;
}
double Student::Totalcredit() const
{
    double Total = 0;
    for (auto i : Course_)
    {
        Total = Total + (i.second).first;
    }
    return Total;
}

double Student::averagescore() const
{
    double Total = 0;
    int n=0;
    for (auto i : Course_)
    {
        Total = Total + (i.second).second;
        n++;
    }
    if (n==0)
    {
        return 0;
    }
    else
    {
        return (Total/n);
    }
    
    
}
//重载各比较符号，为set自动排序服务
bool Student::operator<(Student &s)
{
    return id_ < s.id_;
}
bool Student::operator>(Student &s)
{
    return id_ > s.id_;
}
bool Student::operator==(Student &s)
{
    return id_ == s.id_;
}
#endif