#ifndef STU_H
#define STU_H
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <map>
#include <string.h>
#include <windows.h>
#include <algorithm>
#include <conio.h>
#include <iomanip>
using namespace std;
//后期需要创立一个包含类属性的枚举结构
enum Feature{E_stu_id=1,E_name,E_gender,E_age,E_nationality,E_people,
             E_birthday,E_marriage,E_politics,E_stu_type,
             E_enroll_date,E_enroll_way,E_college,E_major,E_grade,
             E_class_num,E_cengci,E_xuezhi,E_tutor,E_id,E_quit};
//enum Marriage{single,married,divorced,widowed,other};//婚姻状况
//enum Politics{gqty,citizen,communist,officer,soldier,other};//政治面貌,如果国籍为中国，政治面貌默认为少先队员
//enum Stuclass{urban_fresh,country_fresh};//学生类别，城市应届生和农村应届生
//enum Enrollway{normal=0,recruit,transfer,other};//入学方式
//enum Grade{freshman=1,sophomore,junior,senior};//大一和1对应
string FileNameR="students.csv";//读取路径
string FileNameS="students.csv";//保存路径
bool ShowByPage_On=false;
bool AutoSave=false;
//管理员权限
bool Administrate=true;//是否为管理员
int PageSize=10; // 每页最多显示的学生数量
struct Date{
    int year;
    int month;
    int day;
};
class Stufield{
    private:
        string stu_id;//学号 *
        string name;//姓名，中国人（2-20个汉字），其他人（不超过四十个字符） *
        string gender;//性别 存字符串是为了方便输出显示 *
        int age;//年龄 *
        string nationality;//国籍 *
        string people;//民族 *
        string birthday;//出生日期,考虑到后面要排序和搜索，所以存储为字符串更好排序和搜索 *
        string marriage;//婚姻状况 *
        string politics;//政治面貌 *
        string stu_type;//学生类别 *
        string enroll_date;//入学时间 yyyy-mm-dd格式 存为字符串方便排序查找
        string enroll_way;//入学方式 *
        string college;//学院编号2位  *
        string major;//专业编号4位 存四位是为了可以直接根据专业编号排序
        string grade;//年级 *
        string class_num;//班级，1位数字，如“1-9
        string cengci;//层次 输入完专业自动确定
        string xuezhi;//学制 输入完专业自动确定
        string tutor;//导师 输入完专业自动确定
        string id;//身份证号 18 *
    public:
        Stufield(){//构造函数，构造一个合法或非法的数据用于测试
            stu_id="NAN";
            name="NAN";
            gender="男";
            age=0;
            nationality="中国";
            people="汉族";
            birthday="NAN";
            marriage="未婚";
            politics="共青团员";
            stu_type="农村应届生";
            enroll_date="NAN";
            enroll_way="普通入学";
            college="NAN";
            major="NAN";
            grade="NAN";
            class_num="1";
            cengci="本科";
            xuezhi="4年";
            tutor="NAN";
            id="NAN";       
        }
        Stufield(vector<string> &vec);// 用vector初始化构造
        bool InputNation();//输入国家 *
        bool InputPeoples();//输入民族 *
        bool InputCollege();//输入学院
        bool InputMajor();//输入专业
        bool InputEnrollWays();//输入入学方式
        bool InputStuClass();//输入学生类别
        bool InputPolitics();//输入政治面貌
        bool InputMarriage();//输入婚姻状况
        bool InputStuid();//输入学号 *
        bool InputName();//输入姓名
        bool InputGender();//输入性别
        bool InputBirthday();//输入出生日期
        bool InputEnrollDate();//输入入学时间
        bool InputId();//输入身份证号
        bool InputAge();//输入年龄
        bool InputGrade();//输入年级
        bool InputClass();//输入班级
        bool InputCengci();//输入层次
        bool InputXuezhi();//输入学制
        bool InputTutor();//输入导师
        bool MainInput(bool clear_page=true);//输入所有信息
        
        bool GenderCheck();//检查性别是与身份证上的性别否冲突
        bool DateCheck();//检查出生日期与身份证的出生日期是否冲突
        void AgeUpdate();//年龄更新，根据系统时间更新年龄，年龄不需要检查，只需要更新
        bool CollegeCheck();//检查学院是否与学号上的学院冲突
        bool MajorCheck();//检查专业是否与学号上的专业冲突
        bool ClassCheck();//检查班级是否与学号上的班级冲突
        bool EnrollDateCheck();//检查入学时间是否与学号上的入学时间冲突
        bool MainCheck();//检查数据是否有冲突
        
        bool SetCheck();//*检查数据是否合法，不检查,合法返回true，不合法返回false
        bool StuSet(const Feature &by,bool administrate=false);//修改单个学生的某个信息
        
        void ShowStudent() const;//显示学生信息
        
        friend bool SortStudents(vector<Stufield> &students,Feature by,bool reverse);//排序学生信息的总函数
        friend bool UpdateAge(vector<Stufield> &students);//根据系统时间更新学生年龄的总函数
        friend bool DeleteStudents(vector<Stufield> &students,vector<Stufield> &students_deleted,Feature by,string wanted);//删除学生信息的总函数
        friend bool MainStuSet(vector<Stufield> &students,string stu);//修改学生信息的总函数
        friend bool AddStudents(vector<Stufield> &students);//添加学生数据
        friend bool Write_to_Csv(const string &filename,vector<Stufield> &students);//将学生数据保存到csv文件中
        friend bool Append_to_Csv(const string &filename,vector<Stufield> &students);//将学生数据保存到csv文件中
        friend bool MainStuSearch(vector<Stufield> &students);
        friend bool Load_from_Csv(const string &filename,vector<Stufield> &students);//从csv文件中读取学生数据
        friend bool MainStuSort(vector<Stufield> &students);
        friend bool MainStuDelete(vector<Stufield> &students);
        friend vector<int> find_stu(const vector<Stufield> &students,const Feature &by,const string &wanted);
};          
//普通函数声明
Feature SetMenu(bool administrate=false);//;//修改菜单，显示修改选项，返回选择的
Feature SearchMenu();//搜索菜单，显示搜索方式，返回选择的
Feature SortMenu(bool administrate=true);//排序菜单，显示排序选项，返回选择的
Feature DeleteMenu(bool administrate=false);//删除菜单，显示删除选项，返回选择的
void SettingMenu(bool adiministrate=false);//设置菜单，显示设置选项，返回选择的
bool WantedMenu(Feature by,string &wanted);//输入想要修改或搜索的学生信息，返回是否输入成功

bool WantedChoices(Feature by,string &wanted);//通过选择的方式来查找一些信息，返回是否选择成功
bool WantedChoices_vector_str(string &wanted,const vector<string> &vec);
bool WantedChoices_str_map(string &wanted,const map<string,string> &dict);
bool WantedChoices_int_map(string &wanted,const map<int,string> &dict);
bool WantedChoices_major(string &wanted,const map<string,map<string,string>> &dict);

bool ErrorReact();//错误反应函数，返回true表示重新输入，false表示返回上级菜单

void ShowCopyright();//显示版权信息
void ShowMenu();//显示菜单
void ShowTime();//显示当前时间
void ShowHead(bool display_on);//显示所有前置信息

void MainInput();//单个学生学籍所有信息输入
bool MajorsInit_map_map(const string &filename,map<string,map<string,string> > &dict_major,map<string,vector<string>> &dict_tutor);//初始化Major数据 键为字符串，值为vector<string>型数据,由于操作特殊，所以单定义一个函数
bool DataInit_map_str(const string &filename,map<string,string> &dict);//初始化map型数据 键为字符串，值也为字符串
bool DataInit_map_int(const string &filename,map<int,string> &dict);//初始化map型数据 键为整数，值为字符串
bool DataInit_vector(const string &filename,vector<string> &vec);//初始化vector型数据 

bool Load_from_Csv(const string &filename,vector<Stufield> &students);//从csv文件中读取学生数据
vector<string> split(const string &s, char delimiter);//字符串分割函数，用于csv文件
vector<string> csv_split(const string &csv_name,int column_num);//提取csv文件中的某一列数据
void ShowStudents(const vector<Stufield> &students,bool show_by_page=false);//显示所有学生信息

bool InputStuid(string &stu_id);//输入学生学号

int isLeap(int year);//判断是否为闰年
int isLegal(Date date);//判断日期是否合法
string Date_to_String(Date date);//将Date类型转化为string类型
Date String_to_Date(string str);//将string类型转化为Date类型

bool isChinese(const string& name);//判断是否为中文名字
bool isEnglish(const string& name);//判断是否为英文名字

bool IdCheck(string &id);//判断身份证号是否合法
bool ModCheck(string &id);//判断身份证校验码是否正确
bool CityCodeCheck(string &id);//判断身份证城市代码是否正确
bool BirthCheck(string id);//判断身份证出生日期是否合法

bool InputStuid_find(string &stu_id);//输入查找的学生学号
bool InputName_find(string &name_find);//输入查找学生姓名
bool InputGender_find(string &gender_find);//输入查找学生性别
bool InputCengci_find(string &cengci_find);
bool InputXuezhi_find(string &xuezhi_find);
bool InputEnroll_date_find(string &enroll_date_find);//输入查找学生入学日期
bool InputClassNum_find(string &class_num_find);//输入查找学生班级号
bool InputAge_find(string &age_find);//输入查找学生年龄
bool InputBirth_find(string &birthday_find);//以出生日期查找学生
bool InputTutor_find(string &tutor_find);//以导师查找学生

#endif
