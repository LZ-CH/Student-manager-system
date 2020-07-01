#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Student.h"
#include "Student_manage.h"

using namespace std;

vector<StudentInfo *> FiretoStudentInfo(const string &filename) //获取StudentInfo.txt里的数据信息
{
    vector<StudentInfo *> firetostudentinfo;
    ifstream file(filename);

    if (file.is_open())
    {
        string line;
        int id;
        string name;
        string sex;
        string birthday;
        int school_year;
        string birthplace;

        while (getline(file, line))
        {
            if (line[0] != '#')
            {
                stringstream ss(line);
                ss >> id >> name >> sex >> birthday >> school_year >> birthplace;
                firetostudentinfo.push_back(new StudentInfo(id, name, sex, Date(birthday), school_year, birthplace));
            }
        }
    }
    return firetostudentinfo;
}

vector<StudentCourse *> FiletoStudentCourse(const string &filename) //获取StudetCourse.txt里的数据信息
{
    vector<StudentCourse *> filetostudentcourse;
    ifstream file(filename);
    if (file.is_open())
    {
        std::map<int, std::map<std::string, std::pair<int, int>>> map_id_course; //用于保存id对应的课程数据
        std::pair<int, int> credits_score;
        std::map<std::string, std::pair<int, int>> name_c_s;
        string line;
        int id;
        string coursename;
        string t; //用于处理课程名的过渡变量
        double credits;
        double score;
        while (getline(file, line))
        {
            if (line[0] != '#')
            {
                stringstream ss(line);
                ss >> id;
                ss >> coursename;
                while (ss >> t)
                {
                    if (t[0] < '0' || t[0] > '9')
                    {
                        coursename = coursename + " " + t;
                    }
                    else
                    {
                        break;
                    }
                }
                credits = stod(t);
                ss >> score;
                map_id_course[id].insert(make_pair(coursename, make_pair(credits, score)));
            }
        }
        for (auto i : map_id_course)
        {
            filetostudentcourse.push_back(new StudentCourse(i.first, i.second));
        }
    }

    return filetostudentcourse;
}

vector<Student *> StudentInfo_Course(vector<StudentInfo *> &SF, vector<StudentCourse *> &SC) //联表
{
    vector<Student *> studentinfo_course;
    for (auto i = SF.begin(); i < SF.end(); i++)
    {
        for (auto j = SC.begin(); j < SC.end(); j++)
        {
            if ((*i)->id_ == (*j)->id_)
            {
                studentinfo_course.push_back(new Student(**i, **j));
                SC.erase(j);
                break;
            }
        }
    }
    return studentinfo_course;
}

int main()
{
    vector<StudentInfo *> studentinfo = FiretoStudentInfo("StudentInfo.txt");
    vector<StudentCourse *> studentcourse = FiletoStudentCourse("StudentCourse.txt");
    vector<Student *> student = StudentInfo_Course(studentinfo, studentcourse);
    Student_manage student_manage(student);
    cout << "Raw date of the student :" << endl;
    student_manage.show(); //打印原始学生信息
    cout << endl
         << "School_year=2018 && select C Programming Language && C Programming Language's score<60 :" << endl;
    student_manage.Search(student_manage.School_year_condition(2018) && student_manage.Course_condition("C Programming Language", 0, 60));
    cout << endl
         << "average >=80 :" << endl;
    student_manage.Search(student_manage.Averagescore_condition(80, 101)); //查询平均分大于等于80的学生
    student_manage.Credits_Isenough(10);                                   //查询是否全部学生修满10学分
    student_manage.Delete(student_manage.School_year_condition(2018));     //查询2018学年的学生
    cout << endl
         << "After deleting School_year=2018 's student :" << endl
         << endl;
    student_manage.show();
    ofstream file("result.txt"); //新建文件或清空文件内容
    file.close();
    system("main.exe >> result.txt"); //将控制台窗口打印的内容输出到result.txt中

    return 0;
}