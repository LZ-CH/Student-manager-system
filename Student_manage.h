#ifndef STUDENT_MANAGE_H
#define STUDENT_MANAGE_H
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include "Student.h"

class Student_manage
{
private:
    std::vector<Student *> rawdate_;                                         //原始数据，用于最后的内存清理
    std::map<int, Student *> stu_sortbyid;                                   //以ID排序的容器
    std::multimap<std::string, Student *> stu_sortbyname;                    //以Name排序的容器
    std::multimap<std::string, Student *> stu_sortbysex;                     //以sex排序的容器
    std::multimap<Date, Student *> stu_sortbybirthday;                       //以bithday排序的容器
    std::multimap<int, Student *> stu_sortbyschool_year;                     //以school_year排序的容器
    std::multimap<double, Student *> stu_sortbytotalscore;                   //以总分排序的容器
    std::multimap<double, Student *> stu_sortbyaveragescore;                 //以平均分排序的容器
    std::multimap<double, Student *> stu_sortbytotalcredits;                 //以已修学分排序的容器
    std::map<std::string, std::multimap<double, Student *>> stu_sortbyscore; //以单科成绩排序的容器

public:
    Student_manage(std::vector<Student *> rawdate);
    ~Student_manage();
    void SortById() const;
    void SortByName() const;
    void SortBySchool_year() const;
    void SortByTotalScore() const;
    void SortByScore(std::string couesename) const;
    void SortBysex() const;
    void SortBybirthday() const;
    void SortByaveragescore() const;
    std::set<Student *> Id_condition(const int min, const int max) const;                                              //id条件
    std::set<Student *> Name_condition(const std::string &min, const std::string &max) const;                          //name条件
    std::set<Student *> Sex_consiton(const std::string &sex) const;                                                    //sex条件
    std::set<Student *> Birthday_condition(const Date &min, const Date &max) const;                                    //birthday条件
    std::set<Student *> School_year_condition(const int min, const int max = -1) const;                                //School_year条件
    std::set<Student *> TotalScore_condition(const int min, const int max) const;                                      //Totalscore条件
    std::set<Student *> Totalcredit_condition(const int min, const int max) const;                                     //Totalcredit条件
    std::set<Student *> Course_condition(const std::string &coursename, const int min = -1, const int max = -1) const; //course条件
    std::set<Student *> Averagescore_condition(const int min, const int max = 1000) const;                             //平均分条件
    std::set<Student *> Search(std::set<Student *> search_student);                                                    //查询
    void Delete(std::set<Student *> delete_student);                                                                   //删除
    void Credits_Isenough(const double credits);                                                                       //查询是否每个学生都修满credits学分
    friend std::set<Student *> operator&&(std::set<Student *> set_stu1, std::set<Student *> set_stu2);                 //重载&&，为多条目查询服务
    friend std::set<Student *> operator||(std::set<Student *> set_stu1, std::set<Student *> set_stu2);                 //重载||，为多条目查询服务
    void show() const;                                                                                                 //默认id排序
};

Student_manage::Student_manage(std::vector<Student *> rawdate)
{
    for (auto i : rawdate) //初始化各容器
    {
        rawdate_.push_back(new Student(*i));
        stu_sortbyid[i->id_] = i;
        stu_sortbyname.insert(std::make_pair(i->name_, i));
        stu_sortbysex.insert(std::make_pair(i->sex_, i));
        stu_sortbybirthday.insert(std::make_pair(i->birthday_, i));
        stu_sortbyschool_year.insert(std::make_pair(i->school_year_, i));
        stu_sortbytotalscore.insert(std::make_pair(i->Totalscore(), i));
        stu_sortbytotalcredits.insert(std::make_pair(i->Totalcredit(), i));
        stu_sortbyaveragescore.insert(std::make_pair(i->averagescore(), i));
        for (auto j : i->Course_)
        {
            stu_sortbyscore[j.first].insert(std::make_pair(j.second.second, i));
        }
    }
}
Student_manage::~Student_manage() //清理内存
{
    for (auto i : rawdate_)
    {
        delete[] i;
    }
}
void Student_manage::SortByName() const
{
    for (auto i : stu_sortbyname)
    {
        i.second->print();
    }
}
void Student_manage::SortBySchool_year() const
{
    for (auto i : stu_sortbyschool_year)
    {
        i.second->print();
    }
}
void Student_manage::SortByTotalScore() const
{
    for (auto i : stu_sortbytotalscore)
    {
        i.second->print();
    }
}

void Student_manage::SortByScore(std::string coursename) const
{
    auto course = stu_sortbyscore.at(coursename);
    for (auto i : course)
    {
        i.second->print();
    }
}

void Student_manage::SortBysex() const
{
    for (auto i : stu_sortbysex)
    {
        i.second->print();
    }
}

void Student_manage::SortBybirthday() const
{
    for (auto i : stu_sortbybirthday)
    {
        i.second->print();
    }
}
std::set<Student *> Student_manage::Id_condition(const int min, const int max) const
{

    std::set<Student *> t_set;
    if (min < max || min == max)
    {
        if (min == max)
        {
            auto id = stu_sortbyid.lower_bound(min);
            t_set.insert(id->second);
        }
        else
        {
            auto t_min = stu_sortbyid.lower_bound(min);
            auto t_max = stu_sortbyid.lower_bound(max);
            for (auto i = t_min; i != t_max; i++)
            {
                t_set.insert(i->second);
            }
        }
    }

    return t_set;
}

std::set<Student *> Student_manage::Name_condition(const std::string &min, const std::string &max) const
{

    std::set<Student *> t_set;
    if (min < max || min == max)
    {
        if (min == max)
        {
            auto t = stu_sortbyname.lower_bound(min);
            t_set.insert(t->second);
        }
        else
        {
            auto t_min = stu_sortbyname.lower_bound(min);
            auto t_max = stu_sortbyname.lower_bound(max);
            for (auto i = t_min; i != t_max; i++)
            {
                t_set.insert(i->second);
            }
        }
    }

    return t_set;
}

std::set<Student *> Student_manage::Sex_consiton(const std::string &sex) const
{
    std::set<Student *> t_set;
    auto t = stu_sortbysex.find(sex);
    auto end = stu_sortbysex.end();
    for (auto i = t; i != end && (i->second)->sex_ != sex; i++)
    {
        t_set.insert(i->second);
    }
    return t_set;
}

std::set<Student *> Student_manage::Birthday_condition(const Date &min, const Date &max) const
{
    std::set<Student *> t_set;
    if (min < max || min == max)
    {
        if (min == max)
        {
            auto t = stu_sortbybirthday.lower_bound(min);
            t_set.insert(t->second);
        }
        else
        {
            auto t_min = stu_sortbybirthday.lower_bound(min);
            auto t_max = stu_sortbybirthday.lower_bound(max);
            for (auto i = t_min; i != t_max; i++)
            {
                t_set.insert(i->second);
            }
        }
    }

    return t_set;
}
std::set<Student *> Student_manage::School_year_condition(const int min, const int max) const
{
    std::set<Student *> t_set;
    if (max == -1 || min == max) //此时为查询学年为min的学生
    {
        auto t_max = stu_sortbyschool_year.find(max);
        for (auto i = stu_sortbyschool_year.find(min); i != t_max; i++)
        {
            t_set.insert(i->second);
        }
    }

    else if (min < max)
    {

        auto t_min = stu_sortbyschool_year.lower_bound(min);
        auto t_max = stu_sortbyschool_year.lower_bound(max);
        for (auto i = t_min; i != t_max; i++)
        {
            t_set.insert(i->second);
        }
    }
    return t_set;
}

std::set<Student *> Student_manage::TotalScore_condition(const int min, const int max) const
{
    std::set<Student *> t_set;
    if (min < max || min == max)
    {
        if (min == max)
        {
            auto t = stu_sortbytotalscore.lower_bound(min);
            t_set.insert(t->second);
        }
        else
        {
            auto t_min = stu_sortbytotalscore.lower_bound(min);
            auto t_max = stu_sortbytotalscore.lower_bound(max);
            for (auto i = t_min; i != t_max; i++)
            {
                t_set.insert(i->second);
            }
        }
    }
    return t_set;
}
std::set<Student *> Student_manage::Totalcredit_condition(const int min, const int max) const
{
    std::set<Student *> t_set;
    if (min < max || min == max)
    {
        if (min == max)
        {
            auto t = stu_sortbytotalscore.lower_bound(min);
            t_set.insert(t->second);
        }
        else
        {
            auto t_min = stu_sortbytotalscore.lower_bound(min);
            auto t_max = stu_sortbytotalscore.lower_bound(max);
            for (auto i = t_min; i != t_max; i++)
            {
                t_set.insert(i->second);
            }
        }
    }
    return t_set;
}

std::set<Student *> Student_manage::Course_condition(const std::string &coursename, const int min, const int max) const
{
    std::set<Student *> t_set;
    if (max == -1) //此时为查询已选该课程的学生
    {
        for (auto i = stu_sortbyscore.at(coursename).begin(); i != stu_sortbyscore.at(coursename).end(); i++)
        {
            t_set.insert(i->second);
        }
    }

    else
    {

        if (min < max || min == max)
        {
            if (min == max)
            {
                auto t = (stu_sortbyscore.at(coursename)).lower_bound(min); //error
                t_set.insert(t->second);
            }
            else
            {
                auto t_min = (stu_sortbyscore.at(coursename)).lower_bound(min);
                auto t_max = (stu_sortbyscore.at(coursename)).lower_bound(max);
                for (auto i = t_min; i != t_max; i++)
                {
                    t_set.insert(i->second);
                }
            }
        }
    }

    return t_set;
}
std::set<Student *> Student_manage::Averagescore_condition(const int min, const int max) const
{

    std::set<Student *> t_set;
    if (min < max || min == max)
    {
        if (min == max)
        {
            auto t = stu_sortbyaveragescore.lower_bound(min);
            t_set.insert(t->second);
        }
        else
        {
            auto t_min = stu_sortbyaveragescore.lower_bound(min);
            auto t_max = stu_sortbyaveragescore.lower_bound(max);
            for (auto i = t_min; i != t_max; i++)
            {
                t_set.insert(i->second);
            }
        }
    }
    return t_set;
}

std::set<Student *> Student_manage::Search(std::set<Student *> search_student)
{
    for (auto i : search_student)
    {
        i->print();
    }
    return search_student;
}
void Student_manage::Delete(std::set<Student *> delete_student)
{
    //在各器中删除对应的学生信息
    for (auto i : delete_student)
    {
        for (auto j = stu_sortbyid.begin(); j != stu_sortbyid.end(); j++)
        {
            if (j->second->id_ == i->id_)
            {
                stu_sortbyid.erase(j);
                j--; //让j回到被删除结点的上一位置
            }
        }
        for (auto j = stu_sortbyname.begin(); j != stu_sortbyname.end(); j++)
        {
            if (j->second->id_ == i->id_)
            {
                stu_sortbyname.erase(j);
                j--; //让j回到被删除结点的上一位置
            }
        }
        for (auto j = stu_sortbysex.begin(); j != stu_sortbysex.end(); j++)
        {
            if (j->second->id_ == i->id_)
            {
                stu_sortbysex.erase(j);
                j--; //让j回到被删除结点的上一位置
            }
        }
        for (auto j = stu_sortbybirthday.begin(); j != stu_sortbybirthday.end(); j++)
        {
            if (j->second->id_ == i->id_)
            {
                stu_sortbybirthday.erase(j);
                j--; //让j回到被删除结点的上一位置
            }
        }

        for (auto j = stu_sortbyschool_year.begin(); j != stu_sortbyschool_year.end(); j++)
        {
            if (j->second->id_ == i->id_)
            {
                stu_sortbyschool_year.erase(j);
                j--; //让j回到被删除结点的上一位置
            }
        }
        for (auto j = stu_sortbytotalscore.begin(); j != stu_sortbytotalscore.end(); j++)
        {
            if (j->second->id_ == i->id_)
            {
                stu_sortbytotalscore.erase(j);
                j--; //让j回到被删除结点的上一位置
            }
        }
        for (auto j = stu_sortbytotalcredits.begin(); j != stu_sortbytotalcredits.end(); j++)
        {
            if (j->second->id_ == i->id_)
            {
                stu_sortbytotalcredits.erase(j);
                j--; //让j回到被删除结点的上一位置
            }
        }
        for (auto j = stu_sortbyaveragescore.begin(); j != stu_sortbyaveragescore.end(); j++)
        {
            if (j->second->id_ == i->id_)
            {
                stu_sortbyaveragescore.erase(j);
                j--; //让j回到被删除结点的上一位置
            }
        }
        for (auto k = stu_sortbyscore.begin(); k != stu_sortbyscore.end(); k++)
        {
            for (auto j = k->second.begin(); j != k->second.end(); j++)
            {
                if (j->second->id_ == i->id_)
                {
                    k->second.erase(j);
                    j--; //让j回到被删除结点的上一位置
                }
            }
        }
    }
}

void Student_manage::Credits_Isenough(const double credits)
{
    if (stu_sortbytotalcredits.upper_bound(credits) == stu_sortbytotalcredits.begin())
    {
        std::cout << "All the students completed " << credits << " credits." << std::endl;
    }
    else
    {
        std::cout << "Not all the students completed " << credits << " credits." << std::endl;
    }
}

void Student_manage::show() const
{
    for (auto i : stu_sortbyid)
    {
        i.second->print();
    }
}
void Student_manage::SortById() const
{
    for (auto i : stu_sortbyid)
    {
        i.second->print();
    }
}
void Student_manage::SortByaveragescore() const
{

    for (auto i : stu_sortbyaveragescore)
    {
        i.second->print();
    }
}
std::set<Student *> operator&&(std::set<Student *> set_stu1, std::set<Student *> set_stu2)
{
    std::set<Student *> I;
    set_intersection(set_stu1.begin(), set_stu1.end(), set_stu2.begin(), set_stu2.end(), inserter(I, I.begin()));
    return I;
}

std::set<Student *> operator||(std::set<Student *> set_stu1, std::set<Student *> set_stu2)
{
    std::set<Student *> I;
    set_union(set_stu1.begin(), set_stu1.end(), set_stu2.begin(), set_stu2.end(), inserter(I, I.begin()));
    return I;
}
#endif
