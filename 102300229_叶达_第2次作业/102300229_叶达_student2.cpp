#include "102300229_叶达_student.h"
//全局变量


int qz[17]={7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};//权重
char mod[11]={'1','0','X','9','8','7','6','5','4','3','2'};//校验码
time_t CurTime=time(NULL);
tm *CurTm=localtime(&CurTime);//当前时间
int CurYear=CurTm->tm_year+1900;//当前年份
int CurMonth=CurTm->tm_mon+1;//当前月份
int CurDay=CurTm->tm_mday;//当前日期
string CurTimeStr=to_string(CurYear)+((CurMonth<10)?"-0":"-")+to_string(CurMonth)+((CurDay<10)?"-0":"-")+to_string(CurDay);//当前时间字符串

vector<string> Grade={"大一","大二","大三","大四","研究生","其它"};

vector<Stufield> Students_Saved;//存放所有正在操作学生的动态数组
vector<Stufield> Students_Unsaved;//存放所有未保存学生的动态数组
vector<Stufield> Students_Modified;//存放所有已经修改的学生的动态数组
vector<Stufield> Students_Deleted;//存放所有已经删除的学生的动态数组


vector<string> CityCodes;//存放所有城市的代码

map<int,string> Peoples;//民族
map<string,string> Colleges;//学院
map<int,string> EnrollWays;//入学方式
map<int,string> StuTypes;//学生类别
map<int,string> Politics;//政治面貌
map<int,string> Marriages;//婚姻状况
map<int,string> Nations;//国籍
map< string , map<string,string> > Majors;//专业  
map<string, vector<string> > Tutors_Cengci;//导员和层次
//类成员函数定义
Stufield::Stufield(vector<string> &vec){
    stu_id=vec[0];//学号
    name=vec[1];//姓名
    gender=vec[2];//性别
    age=stoi(vec[3]);//年龄
    nationality=vec[4];//国籍
    people=vec[5];//民族
    birthday=vec[6];//出生日期
    marriage=vec[7];//婚姻状况
    politics=vec[8];//政治面貌
    stu_type=vec[9];//学生类别
    enroll_date=vec[10];//入学日期
    enroll_way=vec[11];//入学方式
    college=vec[12];//学院编号
    major=vec[13];//专业编号
    grade=vec[14];//年级
    class_num=vec[15];//班级
    cengci=vec[16];//层次
    xuezhi=vec[17];//学制
    tutor=vec[18];//导师
    id=vec[19];//身份证号
}

bool Stufield::InputStuid(){//输入学号,且进行合法判断（判断是否是数字字符,判断长度合不合理,判断入学年份合不合理,学院编号是否是否合理在提交的时刻检查,输入完学号后）
    string s_id;
    cout<<"*******************************************"<<endl;
    cout<<"请输入学号"<<endl;
    cout<<"*******************************************"<<endl;
    cin>>s_id;
    if(s_id.length()==9){//如果输入的学号长度为9,进行下一部判断
        for(int i=0;i<9;i++){//判断学号是否全为数字
            if(!isdigit(s_id[i])){//如果学号中出现非数字字符,则不合法
                cout<<"输入的学号不合法<学号必须为纯数字>"<<endl;
                return false;
            }
        }
        stu_id=s_id;//将输入的学号赋值给stu_id
        cout<<"学号暂录取成功"<<endl;
        return true;
    }
    else{
        cout<<"输入的学号不合法<学号必须为9为数字>"<<endl;
        return false;
    }
}
bool Stufield::InputCollege(){//输入学院
cout<<"*******************************************"<<endl;
    cout << "学院的选择列表如下:" << endl;
    for (const auto &college : Colleges){//为什么要const auto&因为这样确保了遍历的时候不会修改键值
        cout <<"["<<college.first<<"]"<<":"<<college.second<<endl;//字典遍历,first表示键,second表示值
    }
    string user_choice;
    cout<<"*******************************************"<<endl;
    cout << "请选择你的学院:<按要求输入对应编号> "<<endl;
    cin >> user_choice;
    if(Colleges.find(user_choice)!=Colleges.end()){
        this->college =user_choice;//存编号,方便通过字典的形式查阅更多信息
        cout<<"学院暂录成功"<<endl;
        return true;
    }
    else{
        cout<<"<输入的编号不合法>"<<endl;
        return false;
    }
}
bool Stufield::InputNation(){//输入国家或地区
    cout<<"*******************************************"<<endl;
    cout << "国家或地区的选择列表如下:" << endl;
    for (const auto &nation : Nations){//为什么要const auto&因为这样确保了遍历的时候不会修改键值对
        cout <<"["<<nation.first<<"]"<<":"<<nation.second<<endl;//字典遍历,first表示键,second表示值
    }
    cout<<"*******************************************"<<endl;
    int user_choice;
    cout << "请选择你的国籍:<按要求输入对应编号> "<<endl;
    cin >> user_choice;
    if(Nations.find(user_choice)!=Nations.end()){
        this->nationality=Nations[user_choice];//存实际名称,方便后期输出显示
        cout<<"国籍暂录成功!"<<endl;
        return true;
    }
    else{
        cout<<">输入的编号不合法>"<<endl;//如果输入的编号不在1到203之间,则不合法,返回false,重新输入
        return false;
    }
}
bool Stufield::InputPeoples(){//民族
    cout<<"*******************************************"<<endl;
    cout << "民族的选择列表如下:" << endl;
    for (const auto &people : Peoples){//为什么要const auto&因为这样确保了遍历的时候不会修改键值对
        cout <<"["<<people.first<<"]"<<":"<<people.second<<endl;//字典遍历,first表示键,second表示值
        }
    cout<<"*******************************************"<<endl;
    int user_choice;
    cout << "请选择你的民族:<按要求输入对应编号> "<<endl;
    cin >> user_choice;
    if(Peoples.find(user_choice)!=Peoples.end()){
        this->people =Peoples[user_choice];//存实际名称,方便后期输出显示
        cout<<"民族暂录成功"<<endl;
        return true;
    }
    else{
        cout<<"<输入的编号不合法>"<<endl;
        return false;
    }
}
bool Stufield::InputEnrollWays(){//入学方式
    cout<<"*******************************************"<<endl;
    cout << "入学方式的选择列表如下:" << endl;
    for (const auto &way : EnrollWays){//为什么要const auto&因为这样确保了遍历的时候不会修改键值对
        cout <<"["<<way.first<<"]"<<":"<<way.second<<endl;//字典遍历,first表示键,second表示值
        }
    cout<<"*******************************************"<<endl;
    int user_choice;
    cout << "请选择你的入学方式:<按要求输入对应编号> "<<endl;
    cin >> user_choice;
    if(EnrollWays.find(user_choice)!=EnrollWays.end()){
        this->enroll_way=EnrollWays[user_choice];//
        cout<<"入学方式暂录成功"<<endl;
        return true;
    }
    else{
        cout<<"<输入的编号不合法>"<<endl;
        return false;
    }
}
bool Stufield::InputPolitics(){//政治面貌
    cout<<"*******************************************"<<endl;
    cout << "政治面貌的选择列表如下:" << endl;
    for (const auto &politics : Politics) {//为什么要const auto&因为这样确保了遍历的时候不会修改键值对
        cout <<"["<<politics.first<<"]"<<":"<<politics.second<<endl;//字典遍历,first表示键,second表示值
        }
    int user_choice;
    cout<<"*******************************************"<<endl;
    cout << "请选择你的政治面貌:<按要求输入对应编号> "<<endl;
    cin >> user_choice;
    if(Politics.find(user_choice)!=Politics.end()){
        this->politics =Politics[user_choice];//只存编号,如果要显示学院名称,通过ShowPeople显示
        cout<<"政治面貌暂录成功"<<endl;
        return true;
    }
    else{
        cout<<"<输入的编号不合法>"<<endl;
        return false;
    }
}
bool Stufield::InputStuClass(){//学生类别
cout<<"*******************************************"<<endl;
    cout << "学生类别的选择列表如下:" << endl;
    for (const auto& stu_class : StuTypes){//为什么要const auto&因为这样确保了遍历的时候不会修改键值
        cout <<"["<<stu_class.first<<"]"<<":"<<stu_class.second<<endl;//字典遍历,first表示键,second表示值
        }
    int user_choice;
    cout<<"*******************************************"<<endl;
    cout << "请选择你的学生类别:<按要求输入对应编号> "<<endl;
    cin >> user_choice;
    if(StuTypes.find(user_choice)!=StuTypes.end()){
        this->stu_type =StuTypes[user_choice];//存实际名称,方便后期输出显示
        cout<<"学生类别暂录成功"<<endl;
        return true;
    }
    else{
        cout<<"<输入的编号不合法>"<<endl;
        return false;
    }
}
bool Stufield::InputMarriage(){//输入婚姻状况
    cout<<"*******************************************"<<endl;
    cout << "婚姻状况的选择列表如下:" << endl;
    for (const auto &marriage : Marriages){//为什么要const auto&因为这样确保了遍历的时候不会修改键值对
        cout <<"["<<marriage.first<<"]"<<":"<<marriage.second<<endl;//字典遍历,first表示键,second表示值
    }
    cout<<"*******************************************"<<endl;
    int user_choice;
    cout << "请选择你的婚姻状况:<按要求输入对应编号> "<<endl;
    cin >> user_choice;
    if(Marriages.find(user_choice)!=Marriages.end()){
        this->marriage =Marriages[user_choice];//存实际名称,方便后期输出
        cout<<"婚姻状况暂录成功"<<endl;
        return true;
    }
    else{
        cout<<"<输入的编号不合法>"<<endl;
        return false;
    }
}
bool Stufield::InputBirthday(){//输入出生日期,因为要进行日期合法性校验所以要设置返回值,输入完日期自动生成年龄
    int year,month,day;
    Date temp;
    cout<<"*******************************************"<<endl;
    cout << "请输入你的生日(格式:yyyy-mm-dd):" << endl;
    cout<<"*******************************************"<<endl;
    scanf("%d-%d-%d",&year,&month,&day);
    temp.year=year;//只存编号,如果要显示学院名称,通过ShowPeople显示
    temp.month=month;
    temp.day=day;
    if(isLegal(temp) && (year<=CurYear)){//如果日期合法且年份小于等于当前年份,则生成年龄)
        int age_;
        age_=(CurMonth>=month && CurDay>=day)?CurYear-year:CurYear-year-1;//当前日期在生日之前,年龄减一
        if(age_<13 || age_>63){//限制入学年龄13到63岁
            cout<<"<未到合法入学年龄>"<<endl;
            return false;
        }
        this->birthday=Date_to_String(temp);
        age=age_;
        cout<<"出生日期暂录成功,同时为你自动填录你年龄"<<endl;
        return true;
    }
    else{
        cout<<"<输入的日期不合法>"<<endl;
        return false;
    }
}
bool Stufield::InputGender(){//输入性别
    int user_choice=1;
    cout<<"*******************************************"<<endl;
    cout << "性别选择列表如下:" << endl;
    cout << "[1]:男"<<endl;
    cout << "[2]:女"<<endl;
    cout<<"*******************************************"<<endl;
    cout << "请输入你的性别: "<<endl;
    cin >> user_choice;
    if(user_choice!=1 && user_choice!=2){
        cout<<"<输入的性别不合法>"<<endl;
        return false;
    }
    this->gender=(user_choice==1)?"男":"女";//存实际名称,方便后期输出显示
    cout<<"性别暂录成功"<<endl;
    return true;
}
bool Stufield::InputName(){//输入姓名
    string name;
    cout<<"*******************************************"<<endl;
    cout << "请输入你的姓名: "<<endl;
    cout<<"*******************************************"<<endl;
    cin >> name;
    if(isChinese(name) && name.length()<=40 && name.length()>=4){
        this->name=name;
        cout<<"姓名暂录成功"<<endl;
        return true;
    }
    else if(isEnglish(name) && name.length()<=40 && name.length()>=1){
        this->name=name;
        cout<<"姓名暂录成功"<<endl;
        return true;
    }
    else{
        cout<<"<输入的姓名不合法>"<<endl;
        return false;
    }
}
bool Stufield::InputEnrollDate(){
    cout<<"*******************************************"<<endl;
    cout<<"正在获取当前时间..."<<endl;
    cout<<"当前时间:"<<CurYear<<"-"<<CurMonth<<"-"<<CurDay<<endl;
    cout<<"系统为你输入了默认入学日期:"<<CurYear<<"-"<<CurMonth<<"-"<<CurDay<<endl;
    cout<<"*******************************************"<<endl;
    cout<<"入学时间是否正确?<输入 Y/N>"<<endl;
    char choice;
    while(true){
        choice=toupper(getch());
        if(choice=='Y' && (CurMonth<=10 && CurMonth>=8)){
            this->enroll_date=CurTimeStr;//
            cout<<"入学时间暂录成功"<<endl;
            return true;
        }
        else if(choice=='Y' && !(CurMonth<=10 && CurMonth>=8)){
            cout<<"<当前时间不是入学时间，请返回选择手动录入>"<<endl;
            return false;
        }
        else if(choice=='N'){
            cout<<"请输入你的入学日期(格式:yyyy-mm-dd):"<<endl;
            Date temp;
            int year,month,day;
            scanf("%d-%d-%d",&year,&month,&day);
            temp.year=year;//只存编号,如果要显示学院名称,通过ShowPeople显示
            temp.month=month;
            temp.day=day;
            if(isLegal(temp) && ((year==CurYear && month<=CurMonth && day<=CurDay)|| year<CurYear) && (month<=10 && month>=8) ){
                this->enroll_date=Date_to_String(temp);
                cout<<"入学时间暂录成功"<<endl;
                return true;
            }
            else{
                cout<<"<输入的时间不合法>"<<endl;
                return false;
            }
        }
        else{
            cout<<"请在\"Y\"和\"N\"之间选择输入!"<<endl;
        }
    }
}
bool Stufield::InputAge(){//输入年龄
    int age;
    cout<<"***************输入年龄***************\n"<<endl;
    cout<<"年龄:";
    cin>>age;
    if(age>=0){
        this->age=age;
        cout<<"年龄暂录成功"<<endl;
        return true;
    }
    else{
        cout<<"<输入的年龄不合法>"<<endl;
        return false;
    }
}
bool Stufield::InputId(){//输入身份证号,并进行格式合法性的检验
    string id_hat;
    cout<<"*******************************************"<<endl;
    cout<<"请输入你的身份证号: "<<endl;
    cout<<"*******************************************"<<endl;
    cin >> id_hat;
    if(IdCheck(id_hat)){
        this->id=id_hat;
        return  true;
    }
    else{
        cout<<"<输入的身份证号不合法>"<<endl;
        return false;
    }
}
bool Stufield::InputGrade(){//根据入学年份自动确定年级
    grade=enroll_date.substr(0,4)+"级";
    cout<<"你所在的年级为:"<<grade<<endl;
    return true;
}
bool Stufield::InputClass(){//输入班级
    string class_n;
    cout<<"*******************************************"<<endl;
    cout<<"请输入你的班级:<输入班级数字号即可,只能是1到9的数字>"<<endl;
    cout<<"*******************************************"<<endl;
    cin>>class_n;
    if(class_n.length()==1 && class_n[0]>='1' && class_n[0]<='9'){
        this->class_num=class_n;
        cout<<"班级暂录成功"<<endl;
        return true;
    }
    cout<<"<输入的班级不合法>"<<endl;
    return false;

}
bool Stufield::InputMajor(){
    cout<<"*******************************************"<<endl;
    cout<<Colleges.at(college)<<"的专业选择列表如下:"<<endl;
    int num=0;
    for(const auto &major : Majors[college]){//Majors表示所有学院的所有专业,Majors[college]表示一个学院的所有专业,major则遍历此学院下的各个专业
        cout<<"["<<major.first<<"]:"<<major.second<<endl;//输出 [专业编号]:[专业名称] ,由于设定的编号是从“00”开始连续的所以可以放心累加

    }//编号的素质即为名称在vector中的索引值
    cout<<"*******************************************"<<endl;
    string  user_choice;
    cout<<"请选择你的专业:<按要求输入对应编号> "<<endl;
    cin>>user_choice;
    if(Majors[college].find(user_choice)!=Majors[college].end()){//键值对存在
        this->major=this->college+user_choice;
        string detail_num=major;//学院编号+专业编号
        cout<<"专业信息暂录成功"<<endl;
        cout<<"*******************************************"<<endl;
        this->tutor=Tutors_Cengci[detail_num][2];
        cout<<"你的辅导员为"<<this->tutor<<endl;
        this->cengci=Tutors_Cengci[detail_num][1];
        cout<<"本专业层次为"<<this->cengci<<endl;
        this->xuezhi=Tutors_Cengci[detail_num][0];
        cout<<"本专业学制为"<<this->xuezhi<<endl;
        cout<<"*******************************************"<<endl;
        return true;
    }
    else{
        cout<<"<输入的编号不合法>"<<endl;
        return false;
    }
}
bool Stufield::InputTutor(){
    string tutor_name;
    cout<<"*******************************************"<<endl;
    cout << "请输入导师的姓名: "<<endl;
    cout<<"*******************************************"<<endl;
    cin >> tutor_name;
    if(isChinese(tutor_name) && tutor_name.length()<=40 && tutor_name.length()>=4){
        this->tutor=tutor_name;
        cout<<"导师姓名暂录成功"<<endl;
        return true;
    }
    else if(isEnglish(tutor_name) && tutor_name.length()<=40 && tutor_name.length()>=1){
        this->tutor=tutor_name;
        cout<<"导师姓名暂录成功"<<endl;
        return true;
    }
    else{
        cout<<"<输入的姓名不合法>"<<endl;
        return false;
    }
}
bool Stufield::InputCengci(){
    cout<<"*******************************************"<<endl;
    cout<<"* 1. 本科"<<endl;
    cout<<"* 2. 硕士"<<endl;
    cout<<"* 3. 博士"<<endl;
    cout<<"<请选择专业层次>"<<endl;
    cout<<"*******************************************"<<endl;
    int user_choice;
    cin >> user_choice;
    if(user_choice==1){
        this->cengci="本科";
        cout<<"专业层次暂录成功"<<endl;
        return true;
    }
    else if(user_choice==2){
        this->cengci="硕士";
        cout<<"专业层次暂录成功"<<endl;
        return true;
    }
    else if(user_choice==3){
        this->cengci="博士";
        cout<<"专业层次暂录成功"<<endl;
        return true;
    }
    else{
        cout<<"<输入的编号不合法>"<<endl;
        return false;
    }
}
bool Stufield::InputXuezhi(){
    cout<<"*******************************************"<<endl;
    cout <<"请输入学生的学制年限: "<<endl;
    cout<<"*******************************************"<<endl;
    cout << "请输入年份数: "<<endl;
    int year;
    if(scanf("%d",&year)!=1 || year<1 || year>10){
        cout<<"输入的年份数不合法,请重新输入！"<<endl;
        return false;
    }
    this->xuezhi=to_string(year)+"年";
    cout<<"学制年限输入成功"<<endl;
    return true;
}
bool Stufield::MainInput(bool clear_page){//主输入,往students动态数组存放学籍信息,调用一次只存放一个记录
    if(clear_page)system("cls");
    cout<<"你已经进入学籍信息录入界面<每次输入需要按下回车确认>"<<endl;
    while(!this->InputStuid()){//学号
        bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
        if(flag_continue){
            continue;
        }
        else{
           return false;
        }
    }
    while(!this->InputName()){//姓名
        bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
        if(flag_continue){
            continue;
        }
        else{
           return false;
        }
    }
    while(!this->InputGender()){//性别
        bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
        if(flag_continue){
            continue;
        }
        else{
           return false;
        }
    }
    while(!this->InputNation()){//国籍    
        bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
        if(flag_continue){
            continue;
        }
        else{
           return false;
        }
    }
    while(!this->InputPeoples()){//民族    
        bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
        if(flag_continue){
            continue;
        }
        else{
           return false;
        }
    }
    while(!this->InputBirthday()){//出生日期    
        bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
        if(flag_continue){
            continue;
        }
        else{
           return false;
        }
    }
    while(!this->InputMarriage()){//婚姻
        bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
        if(flag_continue){
            continue;
        }
        else{
           return false;
        }
    }
    while(!this->InputPolitics()){//政治面貌    
        bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
        if(flag_continue){
            continue;
        }
        else{
           return false;
        }
    }
    while(!this->InputStuClass()){//学生类别    
        bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
        if(flag_continue){
            continue;
        }
        else{
           return false;
        }
    }
    while(!this->InputEnrollDate()){//入学日期
        bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
        if(flag_continue){
            continue;
        }
        else{
           return false;
        } 
    }
    while(!this->InputEnrollWays()){//入学方式    
        bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
        if(flag_continue){
            continue;
        }
        else{
           return false;
        }
    }
    while(!this->InputCollege()){//学院
        bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
        if(flag_continue){
            continue;
        }
        else{
           return false;
        }   
    }
    while(!this->InputMajor()){//专业
        bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
        if(flag_continue){
            continue;
        }
        else{
           return false;
        }
    }
    while(!this->InputGrade()){//年级
        bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
        if(flag_continue){
            continue;
        }
        else{
           return false;
        }    
    }
    while(!this->InputClass()){//班级    
        bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
        if(flag_continue){
            continue;
        }
        else{
           return false;
        }
    }    
    while(!this->InputId()){//身份证号
        bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
        if(flag_continue){
            continue;
        }
        else{
           return false;
        }   
    }
    return true;//如果所有输入都合法,则返回true,否则返回false,重新输入
}
bool Stufield::DateCheck(){//检查身份证日期和出生日期是否冲突
    Date temp;
    string id_date=id.substr(6,8);//提取出生日期 
    temp=String_to_Date(id_date);
    id_date=Date_to_String(temp);//统一格式为yyyy-mm-dd
    return birthday==id_date;
}
bool Stufield::GenderCheck(){
    string id_gender=(stoi(id.substr(16,1)) % 2==1?"男":"女");//提取性别
    return id_gender==gender;
}
bool Stufield::CollegeCheck(){
    string stu_id_college=stu_id.substr(0,2);//提取学院编号
    return college==stu_id_college;
}
bool Stufield::MajorCheck(){
    string stu_id_major=stu_id.substr(4,2);//提取专业编号
    return major.substr(2,2)==stu_id_major;
}
bool Stufield::EnrollDateCheck(){
    string stu_id_year=stu_id.substr(2,2);//提取入学年份后两位
    return enroll_date.substr(2,2)==stu_id_year;//enroll_date格式为yyyy-mm-dd
}
bool Stufield::ClassCheck(){
    string stu_id_class=stu_id.substr(6,1);//提取班级编号
    return class_num==stu_id_class;
}
bool Stufield::MainCheck(){
    system("cls");//清屏,防止输出混乱,因为要输出学籍信息,所以清屏
    cout<<"你已经进入学籍信息检验界面"<<endl;//提示用户输入
    cout<<"你的学籍信息如下:"<<endl;//输出学籍信息,如果信息不完整,则提示用户补充信息,如果信息完整,则提示用户确认信息,如果用户确认信息,则返回true,否则返回false,重新输入
    this->ShowStudent();
    if(find_stu(Students_Saved,E_stu_id,stu_id).empty() && find_stu(Students_Saved,E_id,id).empty()){// 学号,身份证不能重复 学号组成：学院编号+入学年份+专业编号+班级编号+班级内位号 如：10 23 00 2 29
        while(!this->CollegeCheck()){
            cout<<"***************************************************"<<endl;
            cout<<"你选择的学院与学号上的学院编号冲突"<<endl;
            cout<<"1. 重新输入学院信息"<<endl;
            cout<<"2. 返回上一级菜单"<<endl;
            cout<<"***************************************************"<<endl;
            cout<<"请选择下一步操作:<按要求输入对应编号> "<<endl;
            char choice;
            choice=getch();
            if(choice=='1'){
                cout<<choice<<endl;
                while(!this->InputCollege());
            }
            else if(choice=='2'){
                cout<<choice<<endl;
                return false;
            }
            else{
                cout<<"输入错误,请按要求重新输入"<<endl;
            }
        }
        while(!this->MajorCheck()){
            cout<<"***************************************************"<<endl;
            cout<<"你选择的专业与学号上的专业编号冲突"<<endl;
            cout<<"1. 重新输入专业信息"<<endl;
            cout<<"2. 返回上一级菜单"<<endl;
            cout<<"***************************************************"<<endl;
            cout<<"请选择下一步操作:<按要求输入对应编号> "<<endl;
            char choice;
            choice=getch();
            if(choice=='1'){
                cout<<choice<<endl;
                while(!this->InputMajor());
            }
            else if(choice=='2'){
                cout<<choice<<endl;
                return false;
            }
            else{
                cout<<"输入错误,请按要求重新输入"<<endl;
            }
        }
        
        while(!this->EnrollDateCheck()){
            cout<<"***************************************************"<<endl;
            cout<<"你选择的入学日期与学号上的入学年份后两位冲突"<<endl;
            cout<<"1. 重新输入入学日期"<<endl;
            cout<<"2. 返回上一级菜单"<<endl;
            cout<<"***************************************************"<<endl;
            cout<<"请选择下一步操作:<按要求输入对应编号> "<<endl;
            char choice;
            choice=getch();
            if(choice=='1'){
                cout<<choice<<endl;
                while(!this->InputEnrollDate());
            }
            else if(choice=='2'){
                cout<<choice<<endl;
                return false;
            }
            else{
                cout<<"输入错误,请按要求重新输入"<<endl;
            }
        }
        grade=enroll_date.substr(0,4)+"级";
        while(!this->ClassCheck()){
            cout<<"***************************************************"<<endl;
            cout<<"你选择的班级与学号上的班级编号冲突"<<endl;
            cout<<"1. 重新输入班级信息"<<endl;
            cout<<"2. 返回上一级菜单"<<endl;
            cout<<"***************************************************"<<endl;
            cout<<"请选择下一步操作:<按要求输入对应编号> "<<endl;
            char choice;
            choice=getch();
            if(choice=='1'){
                cout<<choice<<endl;
                while(!this->InputClass());
            }
            else if(choice=='2'){
                cout<<choice<<endl;
                return false;
            }
            else{
                cout<<"输入错误,请按要求重新输入"<<endl;
            }
        }
        //学号与其他信息都匹配,继续确认其他信息之间的冲突
        while(!this->DateCheck()){
            cout<<"***************************************************"<<endl;
            cout<<"你选择的出生日期与身份证上的出生日期冲突"<<endl;
            cout<<"1. 重新输入出生日期"<<endl;
            cout<<"2. 重新输入身份证号"<<endl;
            cout<<"3. 返回上一级菜单"<<endl;
            cout<<"***************************************************"<<endl;
            cout<<"请选择下一步操作:<按要求输入对应编号> "<<endl;
            char choice;
            choice=getch();
            if(choice=='1'){
                cout<<choice<<endl;
                while(!this->InputBirthday());
            }
            else if(choice=='2'){
                cout<<choice<<endl;
                while(!this->InputId());
            }
            else if(choice=='3'){
                cout<<choice<<endl;
                return false;
            }
            else{
                cout<<"输入错误,请按要求重新输入"<<endl;
            }
        }
        while(!this->GenderCheck()){
            cout<<"***************************************************"<<endl;
            cout<<"你选择的性别与身份证上的性别冲突"<<endl;
            cout<<"1. 重新输入性别"<<endl;
            cout<<"2. 重新输入身份证号"<<endl;
            cout<<"3. 返回上一级菜单"<<endl;
            cout<<"***************************************************"<<endl;
            cout<<"请选择下一步操作:<按要求输入对应编号> "<<endl;
            char choice;
            choice=getch();
            if(choice=='1'){
                cout<<choice<<endl;
                while(!this->InputGender());
            }
            else if(choice=='2'){
                cout<<choice<<endl;
                while(!this->InputId());
            }
            else if(choice=='3'){
                cout<<choice<<endl;
                return false;
            }
            else{
                cout<<"输入错误,请按要求重新输入"<<endl;
            }
        }
        cout<<"<你的学籍信息检验已经完全合法,请再次确认信息是否正确并按任意键继续下一步操作......>"<<endl;
        getch();
        return true;
    }
    else if(find_stu(Students_Saved,E_stu_id,stu_id).empty()){
        cout<<"学号重复,请重新录入!"<<endl;
    }
    else{
        cout<<"身份证重复,请重新录入!"<<endl;
    }
    return false;
}
bool Stufield::SetCheck(){//在进入修改检查之前要查找原始信息，所以这时已经查重了
    system("cls");//清屏,防止输出混乱,因为要输出学籍信息,所以清屏
    cout<<"你已经进入学籍信息检验界面"<<endl;//提示用户输入
    cout<<"你更改后的学籍信息如下:"<<endl;//输出学籍信息,如果信息不完整,则提示用户补充信息,如果信息完整,则提示用户确认信息,如果用户确认信息,则返回true,否则返回false,重新输入
    this->ShowStudent();
    // 学号组成：学院编号+入学年份+专业编号+班级编号+班级内位号 如：10 23 00 2 29
    while(!this->CollegeCheck()){
        cout<<"***************************************************"<<endl;
        cout<<"你选择的学院与学号上的学院编号冲突"<<endl;
        cout<<"1. 重新输入学院信息"<<endl;
        cout<<"2. 返回上一级菜单"<<endl;
        cout<<"***************************************************"<<endl;
        cout<<"请选择下一步操作:<按要求输入对应编号> "<<endl;
        char choice;
        choice=getch();
        if(choice=='1'){
            cout<<choice<<endl;
            while(!this->InputCollege());
        }
        else if(choice=='2'){
            cout<<choice<<endl;
            return false;
        }
        else{
            cout<<"输入错误,请按要求重新输入"<<endl;
        }
    }
    while(!this->MajorCheck()){
        cout<<"***************************************************"<<endl;
        cout<<"你选择的专业与学号上的专业编号冲突"<<endl;
        cout<<"1. 重新输入专业信息"<<endl;
        cout<<"2. 返回上一级菜单"<<endl;
        cout<<"***************************************************"<<endl;
        cout<<"请选择下一步操作:<按要求输入对应编号> "<<endl;
        char choice;
        choice=getch();
        if(choice=='1'){
            cout<<choice<<endl;
            while(!this->InputMajor());
        }
        else if(choice=='2'){
            cout<<choice<<endl;
            return false;
        }
        else{
            cout<<"输入错误,请按要求重新输入"<<endl;
        }
    }
    while(!this->EnrollDateCheck()){
        cout<<"***************************************************"<<endl;
        cout<<"你选择的入学日期与学号上的入学年份后两位冲突"<<endl;
        cout<<"1. 重新输入入学日期"<<endl;
        cout<<"2. 返回上一级菜单"<<endl;
        cout<<"***************************************************"<<endl;
        cout<<"请选择下一步操作:<按要求输入对应编号> "<<endl;
        char choice;
        choice=getch();
        if(choice=='1'){
            cout<<choice<<endl;
            while(!this->InputEnrollDate());
        }
        else if(choice=='2'){
            cout<<choice<<endl;
            return false;
        }
        else{
            cout<<"输入错误,请按要求重新输入"<<endl;
        }
    }
    while(!this->ClassCheck()){
        cout<<"***************************************************"<<endl;
        cout<<"你选择的班级与学号上的班级编号冲突"<<endl;
        cout<<"1. 重新输入班级信息"<<endl;
        cout<<"2. 返回上一级菜单"<<endl;
        cout<<"***************************************************"<<endl;
        cout<<"请选择下一步操作:<按要求输入对应编号> "<<endl;
        char choice;
        choice=getch();
        if(choice=='1'){
            cout<<choice<<endl;
            while(!this->InputClass());
        }
        else if(choice=='2'){
            cout<<choice<<endl;
            return false;
        }
        else{
            cout<<"输入错误,请按要求重新输入"<<endl;
        }
    }
    //学号与其他信息都匹配,继续确认其他信息之间的冲突
    while(!this->DateCheck()){
        cout<<"***************************************************"<<endl;
        cout<<"你选择的出生日期与身份证上的出生日期冲突"<<endl;
        cout<<"1. 重新输入出生日期"<<endl;
        cout<<"2. 重新输入身份证号"<<endl;
        cout<<"3. 返回上一级菜单"<<endl;
        cout<<"***************************************************"<<endl;
        cout<<"请选择下一步操作:<按要求输入对应编号> "<<endl;
        char choice;
        choice=getch();
        if(choice=='1'){
            cout<<choice<<endl;
            while(!this->InputBirthday());
        }
        else if(choice=='2'){
            cout<<choice<<endl;
            while(!this->InputId());
        }
        else if(choice=='3'){
            cout<<choice<<endl;
            return false;
        }
        else{
            cout<<"输入错误,请按要求重新输入"<<endl;
        }
    }
    while(!this->GenderCheck()){
        cout<<"***************************************************"<<endl;
        cout<<"你选择的性别与身份证上的性别冲突"<<endl;
        cout<<"1. 重新输入性别"<<endl;
        cout<<"2. 重新输入身份证号"<<endl;
        cout<<"3. 返回上一级菜单"<<endl;
        cout<<"***************************************************"<<endl;
        cout<<"请选择下一步操作:<按要求输入对应编号> "<<endl;
        char choice;
        choice=getch();
        if(choice=='1'){
            cout<<choice<<endl;
            while(!this->InputGender());
        }
        else if(choice=='2'){
            cout<<choice<<endl;
            while(!this->InputId());
        }
        else if(choice=='3'){
            cout<<choice<<endl;
            return false;
        }
        else{
            cout<<"输入错误,请按要求重新输入"<<endl;
        }
    }
    cout<<"<你的学籍信息更改已经完全合法,请再次确认信息是否正确并按任意键继续下一步操作......>"<<endl;
    getch();
    return true; 
}

void Stufield::AgeUpdate(){//
    int year,month,day;
    year=stoi(birthday.substr(0,4));
    month=stoi(birthday.substr(5,2));
    day=stoi(birthday.substr(8,2));
    age=(CurMonth>=month && CurDay>=day)?CurYear-year:CurYear-year-1;//当前日期在生日之前,年龄减一

}

void Stufield::ShowStudent() const{//显示单个学生信息
    string major_num=major.substr(2,2);
    cout<<"\n*********************************************"<<endl;
    cout<<"* 学号:"<<stu_id<<endl;
    cout<<"* 姓名:"<<name<<endl;
    cout<<"* 性别:"<<gender<<endl;
    cout<<"* 年龄:"<<age<<endl;
    cout<<"* 国籍:"<<nationality<<endl;
    cout<<"* 民族:"<<people<<endl; 
    cout<<"* 出生日期:"<<birthday<<endl;
    cout<<"* 婚姻状况:"<<marriage<<endl;
    cout<<"* 政治面貌:"<<politics<<endl;
    cout<<"* 学生类别:"<<stu_type<<endl; 
    cout<<"* 入学时间:"<<enroll_date<<endl;  
    cout<<"* 入学方式:"<<enroll_way<<endl;  
    cout<<"* 学院:"<<Colleges[college]<<endl;
    cout<<"* 专业:"<<Majors[college][major_num]<<endl;
    cout<<"* 年级:"<<grade<<endl;
    cout<<"* 班级:"<<class_num<<endl;
    cout<<"* 层次:"<<cengci<<endl;
    cout<<"* 学制:"<<xuezhi<<endl;
    cout<<"* 导师:"<<tutor<<endl;
    cout<<"* 身份证号:"<<id<<endl;
    cout<<"*********************************************\n"<<endl; 
    return ;//返回
}
bool Stufield::StuSet(const Feature &by,bool administrate){//返回值为true表示修改成功或不再修改,false表示修改失败
    Stufield stu_temp=*this;
    //但凡要修改的信息,默认是已经经过录入是经过检验的合法的，修改完也必然合法
    if(by==E_name){//名字合法即可
        while(!stu_temp.InputName()){
            bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
            if(flag_continue){
                continue;
            }
            else{
                return false;
            }
        };
        *this=stu_temp;
        return true;
    }
    else if(by==E_gender){//性别和身份证挂钩
        while(!stu_temp.InputGender()){
            bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
                if(flag_continue){
                    continue;
                }
                else{
                    return false;
                }
        };
        //综合检验函数能检验出性别和身份证是否匹配，并强制更改
        if(stu_temp.SetCheck()){;
            *this=stu_temp;  
            return true;
        }
        return false;
    }
    else if(by==E_college){
        if(administrate){
            while(!stu_temp.InputCollege()){
                bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
                if(flag_continue){
                    continue;
                }
                else{
                    return false;
                }
            };
            while(!stu_temp.InputMajor()){
                bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
                if(flag_continue){
                    continue;
                }
                else{
                    return false;
                }
            };
            if(stu_temp.SetCheck()){;//bug我这里如果更改了进入MainCheck函数，是将this与Students_Saved查重，但this本身就在Students_Saved中，所以会导致死循环
                *this=stu_temp;
                return true;
            }
            return false;
        }
        else{
            cout<<"你没有权限修改学院信息"<<endl;
            return false;
        }
    }
    else if(by==E_major){
        if(administrate){
            while(!stu_temp.InputMajor()){
                bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
                if(flag_continue){
                    continue;
                }
                else{
                    return false;
                }
            };
            if(stu_temp.SetCheck()){;//bug我这里如果更改了进入MainCheck函数，是将this与Students_Saved查重，但this本身就在Students_Saved中，所以会导致死循环
                *this=stu_temp;
                return true;
            }
            return false;
        }
        else{
            cout<<"你没有权限修改专业信息"<<endl;
            return false;
        }
    }
    else if(by==E_grade){
        if(administrate){
            while(!stu_temp.InputGrade()){
                bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
                if(flag_continue){
                    continue;
                }
                else{
                    return false;
                }
            };
            *this=stu_temp;
            return true;
        }
        else{
            cout<<"你没有权限修改年级信息"<<endl;
            return false;
        }
    }
    else if(by==E_class_num){
        if(administrate){
            while(!stu_temp.InputClass()){
                bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
                if(flag_continue){
                    continue;
                }
                else{
                    return false;
                }
            };
            if(stu_temp.SetCheck()){;//bug我这里如果更改了进入MainCheck函数，是将this与Students_Saved查重，但this本身就在Students_Saved中，所以会导致死循环
                *this=stu_temp;
                return true;
            }
            return false;
        }
        else{
            cout<<"你没有权限修改班级信息"<<endl;
            return false;
        }
    }
    else if(by==E_people){
        if(administrate){
            while(!stu_temp.InputPeoples()){
                bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
                if(flag_continue){
                    continue;
                }
                else{
                    return false;
                }
            };
            *this=stu_temp;
            return true;
        }
        else{
            cout<<"你没有权限修改民族信息"<<endl;
            return false;
        }
    }
    else if(by==E_nationality){
        if(administrate){
            while(!stu_temp.InputNation()){
                bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
                if(flag_continue){
                    continue;
                }
                else{
                    return false;
                }
            };
            *this=stu_temp;
            return true;
        }
        else{
            cout<<"你没有权限修改国籍信息"<<endl;
            return false;
        }
    }        
    else if(by==E_politics){
        if(administrate){
            while(!stu_temp.InputPolitics()){
                bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
                if(flag_continue){
                    continue;
                }
                else{
                    return false;
                }
            };
            *this=stu_temp;
            return true;
        }
        else{
            cout<<"你没有权限修改政治面貌信息"<<endl;
            return false;
        }
    }
    else if(by==E_stu_type){
        if(administrate){
            while(!stu_temp.InputStuClass()){
                bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
                if(flag_continue){
                    continue;
                }
                else{
                    return false;
                }
            };
            *this=stu_temp;
            return true;
        }
        else{
            cout<<"你没有权限修改学生类别信息"<<endl;
            return false;
        }
        
    }
    else if(by==E_enroll_date){
        if(administrate){
            while(!stu_temp.InputEnrollDate()){
                bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
                if(flag_continue){
                    continue;
                }
                else{
                    return false;
                }
            };
            if(stu_temp.SetCheck()){;
                *this=stu_temp;
                return true;
            }
            return false;
        }
        else{
            cout<<"你没有权限修改入学日期信息"<<endl;
            return false;
        }
    }
    else if(by==E_marriage){
        while(!stu_temp.InputMarriage()){
            bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
            if(flag_continue){
                continue;
            }
            else{
                return false;
            }
        };  
        *this=stu_temp;
        return true;
    }
    else if(by==E_birthday){
        while(!stu_temp.InputBirthday()){
            bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
            if(flag_continue){
                continue;
            }
            else{
                return false;
            }
        };//更改出生日期，年龄也会随之改变，所以这里不会存在年龄和出生日期冲突
        if(stu_temp.SetCheck()){;//bug我这里如果更改了进入MainCheck函数，是将this与Students_Saved查重，但this本身就在Students_Saved中，所以会导致死循环
            *this=stu_temp;
            return true;
        }
        return false;
    }
    else if(by==E_enroll_way){
        if(administrate){
            while(!stu_temp.InputEnrollWays()){
                bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
                if(flag_continue){
                    continue;
                }
                else{
                    return false;
                }
            };
            *this=stu_temp;
            return true;
        }
        else{
            cout<<"你没有权限修改入学方式信息"<<endl;
            return false;
        }
    }
    else if(by==E_id){
        while(!stu_temp.InputId()){
            bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
            if(flag_continue){
                continue;
            }
            else{
                return false;
            }
        };
        if(stu_temp.SetCheck()){;//bug我这里如果更改了进入MainCheck函数，是将this与Students_Saved查重，但this本身就在Students_Saved中，所以会导致死循环
            *this=stu_temp;
            return true;
        }
        return false;
    }
    else if(by==E_tutor){
        if(administrate){
            while(!stu_temp.InputTutor()){
                bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
                if(flag_continue){
                    continue;
                }
                else{
                    return false;
                }
            };
            *this=stu_temp;
            return true;
        }
        else{
            cout<<"你没有权限修改导师信息"<<endl;
            return false;
        }
    }
    else if(by==E_cengci){
        if(administrate){
            while(!stu_temp.InputCengci()){
                bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
                if(flag_continue){
                    continue;
                }
                else{
                    return false;
                }
            };
            *this=stu_temp;
            return true;
        }
        else{
            cout<<"你没有权限修改层次信息"<<endl;
            return false;
        }
    }
    else if(by==E_xuezhi){
        if(administrate){
            while(!stu_temp.InputXuezhi()){
                bool flag_continue=ErrorReact();//错误输入反馈,返回true表示需要继续输入，返回false表示返回上一级菜单
                if(flag_continue){
                    continue;
                }
                else{
                    return false;
                }
            };
            *this=stu_temp;
            return true;
        }
        else{
            cout<<"你没有权限修改学制信息"<<endl;
            return false;
        }
    }
    else if(by==E_quit){
        return true;
    }
    return true;
}




//普通函数定义
int isLeap(int year){
    return (year%4==0&&year%100!=0)||(year%400==0);
};
int isLegal(Date date){
    if(date.month<1||date.month>12||date.day<1||date.day>31){
        return 0;
    }
    else if(date.month==2){
        if(isLeap(date.year)){
            return date.day<=29;
        }
        else{
            return date.day<=28;
        }
    }
    else if(date.month==4||date.month==6||date.month==9||date.month==11){
        return date.day<=30;
    }
    else{
        return 1;
    }
	
};
string Date_to_String(Date date){//格式为 yyyy-mm-dd
    return to_string(date.year) + ((date.month<10)?"-0":"-") + to_string(date.month) + ((date.day<10)?"-0":"-") + to_string(date.day);
}
Date String_to_Date(string str){//格式为 yyyymmdd
    Date date;
    date.year = stoi(str.substr(0,4));
    date.month = stoi(str.substr(4,2));
    date.day = stoi(str.substr(6,2));
    return date;
}
bool isChinese(const string& name){
    for(int i=0;i<name.length();i++){
        if(name[i]>=0 && name[i]<=127){
            return false;
        }
    }
    return true;
}
bool isEnglish(const string& name){
    for(int i=0;i<=name.length();i++){
        if(name[i]>127 || name[i]<0){
            return false;
        }
    }
    return true;
}


bool IdCheck(string &id){//身份证号合法性检验,只检验行政区划是否存在,出生日期是否合法,长度是否合法,校验码是否正确,其余不检查
    if(id.length()==18 && BirthCheck(id) && CityCodeCheck(id) && ModCheck(id)){
        return true;
    }
    return false;//默认不合法
}
bool ModCheck(string &id){//身份证号校验码检验
    int id_num[17];
    int sum=0;
    for(int i=0;i<17;i++){
        id_num[i]=id[i]-'0';//将字符转换为数字
        sum+=id_num[i]*qz[i];//计算前17位乘以系数之和
    }
    char mod_hat=mod[sum%11];//求余
    return mod_hat==id[17];
}//身份末尾校验码
bool CityCodeCheck(string &id){//身份证号行政区划编码检验
    for(const auto &city:CityCodes){
        if(city==id.substr(0,6))return true;
    }
    return false;
}
bool BirthCheck(string id){//身份证号出生日期检验
    string birth_code=id.substr(6,8);//初生日期编码
    Date birth=String_to_Date(birth_code);
    return isLegal(birth);
}

void ShowTime(){
    time_t currentTime;
    struct tm *localTime;
    time(&currentTime);         // 获取当前时间
    localTime = localtime(&currentTime); // 转换为本地时间
    printf("当前日期和时间：%d-%02d-%02d %02d:%02d:%02d\n",
           localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday,
           localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
    printf("\n*******************************************************************************\n");
};
void ShowCopyright(){
    printf("\n*******************************************************************************\n");
    printf("Copyright <c> 2024-2024 叶达<102300229>. ALL Rights Reserved\n");
};
Feature SearchMenu(){
    cout<<"*******************************************************************************\n";
    cout<<"* 1. 按学号查询\n";
    cout<<"* 2. 按姓名查询\n";
    cout<<"* 3. 按性别查询\n";
    cout<<"* 4. 按年龄查询\n";
    cout<<"* 5. 按国籍查询\n";
    cout<<"* 6. 按民族查询\n";
    cout<<"* 7. 按出生日期查询\n";
    cout<<"* 8. 按婚姻状况查询\n";
    cout<<"* 9. 按政治面貌查询\n";
    cout<<"* 10. 按学生类别查询\n";
    cout<<"* 11. 按入学时间查询\n";
    cout<<"* 12. 按入学方式查询\n";
    cout<<"* 13. 按学院查询\n";
    cout<<"* 14. 按专业查询\n";
    cout<<"* 15. 按年级查询\n";
    cout<<"* 16. 按班级查询\n";
    cout<<"* 17. 按层次查询\n";
    cout<<"* 18. 按学制查询\n";
    cout<<"* 19. 按导师查询\n";
    cout<<"* 20. 按身份证号查询\n";
    cout<<"* 21. 退出查询\n";
    cout<<"*******************************************************************************\n";
    cout<<"请输入查询方式编号:<输入范围内的数字>\n";
    int choice;
    while(true){
        cin>>choice;
        if(choice>=1 && choice<=21){
            return (Feature)choice;
        }
        else{
            cout<<"<输入有误,请重新输入>!\n";
        }
    }
}
bool WantedChoices_int_map(string &wanted,const map<int,string> &dict){//根据查询方式和查询内容,返回查询结果
    cout<<"<请选择你要查找的内容>"<<endl;
    for(const auto &item:dict){
        cout<<"["<<item.first<<"]"<<item.second<<endl;
    }
    cout<<"请输入你要查找的项的编号:<输入范围内的数字>"<<endl;
    int choice;
    cin>>choice;
    if(dict.find(choice)!=dict.end()){
        wanted=dict.at(choice);
        cout<<"<正在为你查找属性含["<<wanted<<"]的学生信息......>"<<endl;
        return true;
    }
    else{
        cout<<"<输入有误,请重新输入>!\n";
        return false;
    }
}
bool WantedChoices_str_map(string &wanted,const map<string,string> &dict){//根据查询方式和查询内容,返回查询结果
    cout<<"<请选择你要查找的内容>"<<endl;
    for(const auto &item:dict){
        cout<<"["<<item.first<<"]"<<item.second<<endl;
    }
    cout<<"请输入你要查找的项的编号:<输入范围内的数字>"<<endl;
    string choice;
    cin>>choice;
    if(dict.find(choice)!=dict.end()){
        wanted=dict.at(choice);
        cout<<"<正在为你查找属性含["<<wanted<<"]的学生信息......>"<<endl;
        return true;
    }
    else{
        cout<<"<输入有误,请重新输入>!\n";
        return false;
    }
}
bool WantedChoices_major(string &wanted,const map<string,map<string,string>> &dict){//根据查询方式和查询内容,返回查询结果
    cout<<"<请先选择你要查找的学院>"<<endl;
     for(const auto &item:Colleges){
        cout<<"["<<item.first<<"]"<<item.second<<endl;
    }
    cout<<"请输入你要查找的项的编号:<输入范围内的数字>"<<endl;
    string college_num;
    string college_name;
    cin>>college_num;
    if(Colleges.find(college_num)!=Colleges.end()){
        college_name=Colleges.at(college_num);
        cout<<"<正在为你显示学院为["<<college_name<<"]的专业......>"<<endl;
    }
    else{
        cout<<"<输入有误,请重新输入>!\n";
        return false;
    }
    cout<<"<请选择你要查找的专业>"<<endl;
    for(const auto &item: dict.at(college_num) ){
        cout<<"["<<item.first<<"]"<<item.second<<endl;
    }
    cout<<"请输入你要查找的项的编号:<输入范围内的数字>"<<endl;
    string major_num;
    cin>>major_num;
    if(dict.at(college_num).find(major_num)!=dict.at(college_num).end()){
        wanted=dict.at(college_num).at(major_num);
        cout<<"<正在为你查找专业为["<<wanted<<"]的学生信息......>"<<endl;
        return true;
    }
    else{
        cout<<"<输入有误,请重新输入>!\n";
        return false;
    }
}
bool WantedChoices_vector_str(string &wanted,const vector<string> &vec){//根据查询方式和查询内容,返回查询结果
    cout<<"<请选择你要查找的内容>"<<endl;
    int num=0;
    for(const auto &item:vec){
        cout<<"["<<++num<<"]"<<item<<endl;
    }
    cout<<"请输入你要查找的项的编号:<输入范围内的数字>"<<endl;
    int choice;
    cin>>choice;
    if(choice>=1 && choice<=num){
        wanted=vec[choice-1];
        cout<<"<正在为你查找属性含["<<wanted<<"]的学生信息......>"<<endl;
        return true;
    }
    else{
        cout<<"<输入有误,请重新输入>!\n";
        return false;
    }
}
bool WantedMenu(Feature by,string &wanted){//返回值为true表示正常查找,false表示返回上级菜单
    cout<<"*******************************************"<<endl;
    if(by==E_stu_id){
        while(!InputStuid(wanted)){
            while(true){
                cout<<"输入有误，是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    break;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
        }
        return true;

    }
    else if(by==E_name){
        while(!InputName_find(wanted)){
            while(true){
                cout<<"输入有误，是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    break;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
        }
        return true;
    }
    else if(by==E_gender){
        while(!InputGender_find(wanted)){
            while(true){
                cout<<"输入有误，是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    break;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
        }
        return true;
    }
    else if(by==E_age){
        while(!InputAge_find(wanted)){
            while(true){
                cout<<"输入有误，是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    break;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
        }
        return true;
    }
    else if(by==E_nationality){
        while(true){
            bool choice;
            choice=WantedChoices_int_map(wanted,Nations);
            if(!choice){
               while(true){
                    cout<<"是否重新输入? (Y/N)"<<endl;
                    char ch=getch();
                    if(ch=='Y' || ch=='y'){
                        break;
                    }
                    else if(ch=='N' || ch=='n'){
                        return false;
                    }
                    else{
                        cout<<"请在Y/N中选择"<<endl;
                    }
                }
            }
            else{
                return true;
            }     
        }
    }
    else if(by==E_politics){
        while(true){
            bool choice;
            choice=WantedChoices_int_map(wanted,Politics);
            if(!choice){
                while(true){
                    cout<<"是否重新输入? (Y/N)"<<endl;
                    char ch=getch();
                    if(ch=='Y' || ch=='y'){
                        break;
                    }
                    else if(ch=='N' || ch=='n'){
                        return false;
                    }
                    else{
                        cout<<"请在Y/N中选择"<<endl;
                    }
                }
            }
            else{
                return true;
            }   
        }
    }
    else if(by==E_stu_type){
        while(true){
            bool choice;
            choice=WantedChoices_int_map(wanted,StuTypes);
            if(!choice){
                while(true){
                    cout<<"是否重新输入? (Y/N)"<<endl;
                    char ch=getch();
                    if(ch=='Y' || ch=='y'){
                        break;
                    }
                    else if(ch=='N' || ch=='n'){
                        return false;
                    }
                    else{
                        cout<<"请在Y/N中选择"<<endl;
                    }
                }
            }
            else{
                return true;
            }      
        }
    }
    else if(by==E_enroll_way){
        while(true){
            bool choice;
            choice=WantedChoices_int_map(wanted,EnrollWays);
            if(!choice){
                while(true){
                    cout<<"是否重新输入? (Y/N)"<<endl;
                    char ch=getch();
                    if(ch=='Y' || ch=='y'){
                        break;
                    }
                    else if(ch=='N' || ch=='n'){
                        return false;
                    }
                    else{
                        cout<<"请在Y/N中选择"<<endl;
                    }
                }
            }
            else{
                return true;
            }      
        }
    }
    else if(by==E_people){
        while(true){
            bool choice;
            choice=WantedChoices_int_map(wanted,Peoples);
            if(!choice){
                while(true){
                    cout<<"是否重新输入? (Y/N)"<<endl;
                    char ch=getch();
                    if(ch=='Y' || ch=='y'){
                        break;
                    }
                    else if(ch=='N' || ch=='n'){
                        return false;
                    }
                    else{
                        cout<<"请在Y/N中选择"<<endl;
                    }
                }
            }
            else{
                return true;
            }      
        }
    }
    else if(by==E_college){
        while(true){
            bool choice;
            choice=WantedChoices_str_map(wanted,Colleges);
            if(!choice){
                while(true){
                    cout<<"是否重新输入? (Y/N)"<<endl;
                    char ch=getch();
                    if(ch=='Y' || ch=='y'){
                        break;
                    }
                    else if(ch=='N' || ch=='n'){
                        return false;
                    }
                    else{
                        cout<<"请在Y/N中选择"<<endl;
                    }
                }
            }
            else{
                return true;
            }      
        }
    }
    else if(by==E_major){
        while(true){
            bool choice;
            choice=WantedChoices_major(wanted,Majors);
            if(!choice){
                while(true){
                    cout<<"是否重新输入? (Y/N)"<<endl;
                    char ch=getch();
                    if(ch=='Y' || ch=='y'){
                        break;
                    }
                    else if(ch=='N' || ch=='n'){
                        return false;
                    }
                    else{
                        cout<<"请在Y/N中选择"<<endl;
                    }
                }
            }
            else{
                return true;
            }      
        }
    }
    else if(by==E_enroll_date){
        while(!InputEnroll_date_find(wanted)){
            while(true){
                cout<<"是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    break;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
        }
        return true;
    }
    else if(by==E_birthday){
         while(!InputBirth_find(wanted)){
            while(true){
                cout<<"是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    break;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
        }
        return true;
    }
    else if(by==E_marriage){
        while(true){
            bool choice;
            choice=WantedChoices_int_map(wanted,Marriages);
            if(!choice){
                cout<<"输入有误，是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    continue;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
            else{
                return true;
            }   
        }
    }
    else if(by==E_class_num){
        while(!InputClassNum_find(wanted)){
            while(true){
                cout<<"是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    break;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
        }
        return true;
    }
    else if(by==E_cengci){
        while(!InputCengci_find(wanted)){
            while(true){
                cout<<"是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    break;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
        }
        return true;
    }
    else if(by==E_xuezhi){
        while(!InputXuezhi_find(wanted)){
            while(true){
                cout<<"是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    break;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
        }
        return true;
    }
    else if(by==E_grade){
        while(true){
            bool choice;
            choice=WantedChoices_vector_str(wanted,Grade);
            if(!choice){
                cout<<"输入有误，是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    continue;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
            else{
                return true;
            }   
        }
    }
    else if(by==E_tutor){
        while(!InputTutor_find(wanted)){
            while(true){
                cout<<"是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    break;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
        }
        return true;
    }
    else if(by==E_quit){
        cout<<"<退出查询>"<<endl;
        return false;
    }
    return false;  
}
bool WantedMenu_delete(Feature by,string &wanted){
     cout<<"*******************************************"<<endl;
    if(by==E_stu_id){
        while(!InputStuid(wanted)){
            while(true){
                cout<<"输入有误，是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    break;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
        }
        return true;

    }
    else if(by==E_name){
        while(!InputName_find(wanted)){
            while(true){
                cout<<"输入有误，是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    break;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
        }
        return true;
    }
    else if(by==E_gender){
        while(!InputGender_find(wanted)){
            while(true){
                cout<<"输入有误，是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    break;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
        }
        return true;
    }
    else if(by==E_age){
        while(!InputAge_find(wanted)){
            while(true){
                cout<<"输入有误，是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    break;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
        }
        return true;
    }
    else if(by==E_nationality){
        while(true){
            bool choice;
            choice=WantedChoices_int_map(wanted,Nations);
            if(!choice){
               while(true){
                    cout<<"是否重新输入? (Y/N)"<<endl;
                    char ch=getch();
                    if(ch=='Y' || ch=='y'){
                        break;
                    }
                    else if(ch=='N' || ch=='n'){
                        return false;
                    }
                    else{
                        cout<<"请在Y/N中选择"<<endl;
                    }
                }
            }
            else{
                return true;
            }     
        }
    }
    else if(by==E_politics){
        while(true){
            bool choice;
            choice=WantedChoices_int_map(wanted,Politics);
            if(!choice){
                while(true){
                    cout<<"是否重新输入? (Y/N)"<<endl;
                    char ch=getch();
                    if(ch=='Y' || ch=='y'){
                        break;
                    }
                    else if(ch=='N' || ch=='n'){
                        return false;
                    }
                    else{
                        cout<<"请在Y/N中选择"<<endl;
                    }
                }
            }
            else{
                return true;
            }   
        }
    }
    else if(by==E_stu_type){
        while(true){
            bool choice;
            choice=WantedChoices_int_map(wanted,StuTypes);
            if(!choice){
                while(true){
                    cout<<"是否重新输入? (Y/N)"<<endl;
                    char ch=getch();
                    if(ch=='Y' || ch=='y'){
                        break;
                    }
                    else if(ch=='N' || ch=='n'){
                        return false;
                    }
                    else{
                        cout<<"请在Y/N中选择"<<endl;
                    }
                }
            }
            else{
                return true;
            }      
        }
    }
    else if(by==E_enroll_way){
        while(true){
            bool choice;
            choice=WantedChoices_int_map(wanted,EnrollWays);
            if(!choice){
                while(true){
                    cout<<"是否重新输入? (Y/N)"<<endl;
                    char ch=getch();
                    if(ch=='Y' || ch=='y'){
                        break;
                    }
                    else if(ch=='N' || ch=='n'){
                        return false;
                    }
                    else{
                        cout<<"请在Y/N中选择"<<endl;
                    }
                }
            }
            else{
                return true;
            }      
        }
    }
    else if(by==E_people){
        while(true){
            bool choice;
            choice=WantedChoices_int_map(wanted,Peoples);
            if(!choice){
                while(true){
                    cout<<"是否重新输入? (Y/N)"<<endl;
                    char ch=getch();
                    if(ch=='Y' || ch=='y'){
                        break;
                    }
                    else if(ch=='N' || ch=='n'){
                        return false;
                    }
                    else{
                        cout<<"请在Y/N中选择"<<endl;
                    }
                }
            }
            else{
                return true;
            }      
        }
    }
    else if(by==E_college){
        while(true){
            bool choice;
            choice=WantedChoices_str_map(wanted,Colleges);
            if(!choice){
                while(true){
                    cout<<"是否重新输入? (Y/N)"<<endl;
                    char ch=getch();
                    if(ch=='Y' || ch=='y'){
                        break;
                    }
                    else if(ch=='N' || ch=='n'){
                        return false;
                    }
                    else{
                        cout<<"请在Y/N中选择"<<endl;
                    }
                }
            }
            else{
                return true;
            }      
        }
    }
    else if(by==E_major){
        while(true){
            bool choice;
            choice=WantedChoices_major(wanted,Majors);
            if(!choice){
                while(true){
                    cout<<"是否重新输入? (Y/N)"<<endl;
                    char ch=getch();
                    if(ch=='Y' || ch=='y'){
                        break;
                    }
                    else if(ch=='N' || ch=='n'){
                        return false;
                    }
                    else{
                        cout<<"请在Y/N中选择"<<endl;
                    }
                }
            }
            else{
                return true;
            }      
        }
    }
    else if(by==E_enroll_date){
        while(!InputEnroll_date_find(wanted)){
            while(true){
                cout<<"是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    break;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
        }
        return true;
    }
    else if(by==E_birthday){
         while(!InputBirth_find(wanted)){
            while(true){
                cout<<"是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    break;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
        }
        return true;
    }
    else if(by==E_marriage){
        while(true){
            bool choice;
            choice=WantedChoices_int_map(wanted,Marriages);
            if(!choice){
                cout<<"输入有误，是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    continue;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
            else{
                return true;
            }   
        }
    }
    else if(by==E_class_num){
        while(!InputClassNum_find(wanted)){
            while(true){
                cout<<"是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    break;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
        }
        return true;
    }
    else if(by==E_cengci){
        while(!InputCengci_find(wanted)){
            while(true){
                cout<<"是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    break;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
        }
        return true;
    }
    else if(by==E_grade){
        while(true){
            bool choice;
            choice=WantedChoices_vector_str(wanted,Grade);
            if(!choice){
                cout<<"输入有误，是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    continue;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
            else{
                return true;
            }   
        }
    }
    else if(by==E_tutor){
        while(!InputTutor_find(wanted)){
            while(true){
                cout<<"是否重新输入? (Y/N)"<<endl;
                char ch=getch();
                if(ch=='Y' || ch=='y'){
                    break;
                }
                else if(ch=='N' || ch=='n'){
                    return false;
                }
                else{
                    cout<<"请在Y/N中选择"<<endl;
                }
            }
        }
        return true;
    }
    else if(by==E_quit){
        cout<<"<退出查询>"<<endl;
        return false;
    }
    return false;  
}
Feature SetMenu(bool administrate){
    if(administrate){
        cout<<"*******************************************************************************\n";
        cout<<"* 1. 修改姓名\n";
        cout<<"* 2. 修改性别\n";
        cout<<"* 3. 修改国籍\n";
        cout<<"* 4. 修改民族\n";
        cout<<"* 5. 修改出生日期\n";
        cout<<"* 6. 修改婚姻状况\n";
        cout<<"* 7. 修改政治面貌\n";
        cout<<"* 8. 修改学生类别\n";
        cout<<"* 9. 修改入学时间\n";
        cout<<"* 10. 修改入学方式\n";
        cout<<"* 11. 修改学院\n";
        cout<<"* 12. 修改专业\n";
        cout<<"* 13. 修改年级\n";
        cout<<"* 14. 修改班级\n";
        cout<<"* 15. 修改层次\n";
        cout<<"* 16. 修改学制\n";
        cout<<"* 17. 修改导师\n";
        cout<<"* 18. 修改身份证号\n";
        cout<<"* 19. 退出修改\n";
        cout<<"*******************************************************************************\n";
        cout<<"请输入修改选项编号:<输入范围内的数字>\n";
        int choice;
        while(true){
            cin>>choice;            
            if(choice>=1 && choice<=19){
                if(choice>=1 && choice<=2){
                    choice+=1;//因为学号的枚举值是1,而学号不能修改,所以修改选项编号要加1才是实际枚举值
                }
                else if(choice>=3){
                    choice+=2;
                }
                return (Feature)choice;
            }
            else{
                cout<<"<输入有误,请重新输入>!\n";
            }
        }
    }
    else{
        cout<<"*******************************************************************************\n";
        cout<<"* 1. 修改姓名\n";
        cout<<"* 2. 修改性别\n";
        cout<<"* 3. 修改出生日期\n";
        cout<<"* 4. 修改婚姻状况\n";
        cout<<"* 5. 修改身份证号\n";
        cout<<"* 6. 退出修改\n";
        cout<<"*******************************************************************************\n";
        cout<<"请输入修改选项编号:<输入范围内的数字>\n";
        int choice;
        while(true){
            cin>>choice;
            if(choice==1){return E_name;}
            else if(choice==2){return E_gender;}
            else if(choice==3){return E_birthday;}
            else if(choice==4){return E_marriage;}
            else if(choice==5){return E_id;}
            else if(choice==6){return E_quit;}
            else{
                cout<<"<输入有误,请重新输入>!\n";
            }
        }
    }
}
Feature SortMenu(bool administrate){
    if(administrate){
        cout<<"<学生信息排序界面>"<<endl;
        cout<<"*******************************************************************************\n";
        cout<<"* 1. 按学号排序\n";
        cout<<"* 2. 按姓名排序\n";
        cout<<"* 3. 按性别排序\n";
        cout<<"* 4. 按年龄排序\n";
        cout<<"* 5. 按国籍排序\n";
        cout<<"* 6. 按民族排序\n";
        cout<<"* 7. 按出生日期排序\n";
        cout<<"* 8. 按婚姻状况排序\n";
        cout<<"* 9. 按政治面貌排序\n";
        cout<<"* 10. 按学生类别排序\n";
        cout<<"* 11. 按入学时间排序\n";
        cout<<"* 12. 按入学方式排序\n";
        cout<<"* 13. 按学院排序\n";
        cout<<"* 14. 按专业排序\n";
        cout<<"* 15. 按年级排序\n";
        cout<<"* 16. 按班级排序\n";
        cout<<"* 17. 按层次排序\n"; 
        cout<<"* 18. 按学制排序\n";
        cout<<"* 19. 按导师排序\n";
        cout<<"* 20. 按身份证号排序\n";
        cout<<"* 21. 退出排序\n";
        cout<<"*******************************************************************************\n";
        cout<<"请输入排序方式编号:<输入范围内的数字>\n";
        int choice;
        while(true){
            cin>>choice;
            if(choice>=1 && choice<=21){
                return (Feature)choice;
            }
            else{
                cout<<"<输入有误,请重新输入>!\n";
            }
        }
    }
    else{
        cout<<"<你没有权限进行排序操作>"<<endl;
        return E_quit;
    }
}
Feature DeleteMenu(bool administrate){
    if(administrate){
        cout<<"<学生信息删除界面>"<<endl;
        cout<<"*******************************************************************************\n";
        cout<<"* 1. 删除特定学号的学生信息\n";
        cout<<"* 2. 删除特定姓名的学生信息\n";
        cout<<"* 3. 删除特定性别的学生信息\n";
        cout<<"* 4. 删除特定年龄的学生信息\n";
        cout<<"* 5. 删除特定国籍的学生信息\n";
        cout<<"* 6. 删除特定民族的学生信息\n";
        cout<<"* 7. 删除特定出生日期的学生信息\n";
        cout<<"* 8. 删除特定婚姻状况的学生信息\n";
        cout<<"* 9. 删除特定政治面貌的学生信息\n";
        cout<<"* 10. 删除特定学生类别的学生信息\n";
        cout<<"* 11. 删除特定入学时间的学生信息\n";
        cout<<"* 12. 删除特定入学方式的学生信息\n";
        cout<<"* 13. 删除特定学院的学生信息\n";
        cout<<"* 14. 删除特定专业的学生信息\n";
        cout<<"* 15. 删除特定年级的学生信息\n";
        cout<<"* 16. 删除特定班级的学生信息\n";
        cout<<"* 17. 删除特定层次的学生信息\n";
        cout<<"* 18. 删除特定学制的学生信息\n";
        cout<<"* 19. 删除特定导师的学生信息\n";
        cout<<"* 20. 删除特定身份证号的学生信息\n";
        cout<<"* 21. 退出删除界面\n";
        cout<<"*******************************************************************************\n";
        cout<<"请输入删除选项编号:<输入范围内的数字>\n";
        int choice;
        while(true){
            cin>>choice;
            if(choice>=1 && choice<=21){
                return (Feature)choice;
            }
            else{
                cout<<"<输入有误,请重新输入>!\n";
            }
        }
    }
    else{
        cout<<"<你没有权限进行删除操作>"<<endl;
        return E_quit;
    }
}
void ShowMenu(){//菜单函数
	printf("\n*******************************************************************************\n");
	printf("*************欢迎使用学生信息管理系统***************\n");
	printf("                                                  \n");
	printf("********************系统功能菜单********************\n");
	printf("*                                                  \n");
	printf("*                 A.添加学生信息\n");
	printf("*                 B.修改学生信息\n");
	printf("*                 C.查找学生信息\n");
	printf("*                 D.排序学生信息\n");
	printf("*                 E.以覆盖的方式保存当前正在操作的学生信息到数据库文件\n");
    printf("*                 F.以添加的方式保存当前正在操作的学生信息到数据库文件\n");
    printf("*                 G.显示已经保存在数据库中的学生信息\n");
    printf("*                 H.显示当前正在操作的学生信息\n");
    printf("*                 I.从数据库文件中导入学生信息\n");
	printf("*                 J.删除当前正在操作的学生信息\n");
    printf("*                 K.清空数据库文件\n");
    printf("*                 L.显示回收站中的学生信息\n");
    printf("*                 M.清空回收站\n");
    printf("*                 N.复原回收站的学生信息到当前正在操作的学生信息中\n");
    printf("*                 O.管理员模式\n");
    printf("*                 P.系统设置\n");
	printf("*                 Q.退出系统\n");
	printf("*******************************************************************************\n");
	printf("请输入选项编号:<输入范围内的字母>\n");
}
void SettingMenu(bool administrate){//设置系统的分页显示，分页显示的行数和列数
    if(administrate){
        char choice2='0';//二级菜单选项
        char choice3;
        system("cls");
        printf("\n******************************\n你已进入该系统设置界面\n******************************\n");
        while(1){
            system("cls");
            printf("******************************\n系统设置界面\n******************************\n");
            printf("\n******************\n");
            printf("*\t1.全局分屏显示设置\n");
            printf("*\t2.退出系统时自动保存功能设置\n");
            printf("*\t3.修改分屏显示情况下一页所能展示的学生数\n");
            printf("*\t4.修改学生信息存放的路径\n");
            printf("*\t5.修改要读取文件的路径\n");
            printf("*\t6.查看当前系统设置\n");
            printf("*\t7.返回上级菜单\n");
            printf("*******************\n");
            printf("请输入你的选择(1-7):\n");
            choice2=getch();
            cout<<choice2<<endl;
            switch(choice2){
                case '1':
                    cout<<"当前全局分屏显示设置为:"<<(ShowByPage_On?"开启":"关闭")<<endl;
                    while(1){
                        cout<<"你需要将全局分屏显示设置为:<Y/N>\n"<<endl;
                        choice3=toupper(getch());
                        if(choice3=='Y'){
                            ShowByPage_On=1;
                            cout<<"\n全局分屏显示已开启!\n"<<endl;
                            break;
                        }
                        else if(choice3=='N'){
                            ShowByPage_On=0;
                            cout<<"\n全局分屏显示已关闭!\n"<<endl;
                            break;
                        }
                        else{
                            cout<<"<输入有误,请重新输入>!\n"<<endl;
                        }
                    }
                    cout<<"<按任意键返回上级菜单......>"<<endl;
                    getch();
                    break;
                case '2':
                    cout<<"当前退出系统时自动保存功能设置为:"<<(AutoSave?"开启":"关闭")<<endl;
                    while(1){
                        cout<<"你需要将退出系统时自动保存功能设置为:<Y/N>\n"<<endl;
                        choice3=toupper(getch());
                        if(choice3=='Y'){
                            AutoSave=1;
                            cout<<"\n<自动保存功能已开启!>\n"<<endl;
                            break;
                        }
                        else if(choice3=='N'){
                            AutoSave=0;
                            cout<<"\n<退出系统时自动保存功能已关闭!>\n"<<endl;
                            break;
                        }
                        else{
                            cout<<"<输入有误,请重新输入>!\n"<<endl;
                        }
                    }
                    cout<<"<按任意键返回上级菜单......>"<<endl;
                    getch();
                    break;
                case '3':{
                    cout<<"当前每页最多显示的学生数量为:"<<PageSize<<endl;
                    cout<<"你需要将每页最多显示的学生数量设置为:<在下方输入数字>\n";
                    int temp_size;
                    cin>>temp_size;
                    if(temp_size<=0){
                        cout<<"<输入有误,不进行更改>!\n"<<endl;
                    }
                    else{
                        PageSize=temp_size;
                        cout<<"<每页最多显示的学生数量已设置为:"<<PageSize<<">"<<endl;
                    }
                    cout<<"<按任意键返回上级菜单......>"<<endl;
                    getch();
                    break;
                }
                case '4':{
                    cout<<"当前路径为:"<<FileNameS<<endl;//只能是csv文件
                    cout<<"你需要将你的学生信息存放路径更新为:<在下方输入文件名和后缀名>\n";//只能是csv文件
                    string FileNameS_temp;
                    cin>>FileNameS_temp;
                    if(FileNameS_temp.find(".csv")!=string::npos){//如果输入的文件名后缀名为csv
                        FileNameS=FileNameS_temp;
                        cout<<"<路径更新完毕>"<<endl;
                        cout<<"<当前路径为："<<FileNameS<<">"<<endl;
                    }
                    else{
                        cout<<"<输入有误,不会进行更改>!\n"<<endl;
                    }
                    cout<<"<按任意键返回上级菜单......>"<<endl;
                    getch();
                    break;
                }
                case '5':{
                    cout<<"当前路径为:"<<FileNameR<<endl;
                    cout<<"你需要将你的学生信息读取路径更新为:<在下方输入文件名和后缀名>\n";
                    string FileNameS_temp;
                    cin>>FileNameS_temp;
                    if(FileNameS_temp.find(".csv")!=string::npos){//如果输入的文件名后缀名为csv
                        FileNameS=FileNameS_temp;
                        cout<<"<路径更新完毕>"<<endl;
                        cout<<"<当前路径为："<<FileNameS<<">"<<endl;
                    }
                    else{
                        cout<<"<输入有误,不会进行更改>!\n"<<endl;
                    }
                    cout<<"<按任意键返回上级菜单......>"<<endl;
                    getch();
                    break;
                }
                case '6':
                    cout<<"当前系统设置如下:\n";
                    cout<<"全局分屏显示:"<<(ShowByPage_On?"开启":"关闭")<<endl;
                    cout<<"退出系统时自动保存功能:"<<(AutoSave?"开启":"关闭")<<endl;
                    cout<<"每页最多显示的学生数量:"<<PageSize<<endl;
                    cout<<"学生信息存放路径:"<<FileNameS<<endl;
                    cout<<"学生信息读取路径:"<<FileNameR<<endl;
                    cout<<"<按任意键返回上级菜单......>"<<endl;
                    getch();
                    break;
                case '7':
                    cout<<"<正在返回上级菜单......>"<<endl;
                    return;
                default:
                    cout<<"<输入有误,请重新输入>!\n"<<endl;
                    break;
            }
        }
    }
    else{
        cout<<"<你没有权限进行系统设置>"<<endl;
        cout<<"<按任意键返回主菜单......>"<<endl;
        getch();
        return;
    }
};
void ShowHead(bool display_on){
    if(display_on){
        system("cls");
        ShowCopyright();
        ShowTime();
        ShowMenu();
    }
    else{
        ShowCopyright();
        ShowTime();
        ShowMenu();
    }
    return;
}
bool DataInit_map_str(const string &filename,map<string,string> &dict){//初始化数据,读取文件中的学籍信息,存入dict字典
    ifstream file(filename);//打开文件
    if(file.is_open() &&  dict.empty()){//如果字典为空且文件可正常打开才正常读取,防止重复读取
      //dict["0"]="未注册";//
      string num,name;//num是编号,name是对应名称
      while(getline(file,num,',') && getline(file,name)){//注意是英文冒号
        dict[num]=name;//
      }
      file.close();//关闭文件
      return true;
    }
    else{
        cerr << "无法正常载入"<<filename<<"文件" << endl;
        return false;
    }
}
bool DataInit_map_int(const string &filename,map<int,string> &dict){//初始化数据,读取文件中的学籍信息,存入dict字典
    ifstream file(filename);//打开文件
    if(file.is_open() &&  dict.empty()){//如果字典为空且文件可正常打开才正常读取,防止重复读取
      //dict[0]="未注册";//
      int num=0;
      string token;//占位的
      string name;//num是编号,name是对应名称
      while(getline(file,token,',') && getline(file,name)){//注意是英文冒号
        dict[++num]=name;//
      }
      file.close();//关闭文件
      return true;
    }
    else{
        cerr << "无法正常载入"<<filename<<"文件"<< endl;
        return false;
    }
}
bool DataInit_vector(const string &filename, vector<string> &vec) {
    ifstream file(filename); // 打开文件
    if (!file.is_open()){
        cerr << "无法正常载入"<<filename<<"文件" << endl;
        return false;
    }
    string line;
    vec.push_back("初始化标记"); // 添加初始化标记
    while (getline(file, line)){
        vec.push_back(line); // 将文件中的每一行数据添加到vec中
    }
    file.close(); // 关闭文件
    return true;
}
bool MajorsInit_map_map(const string &filename,map<string,map<string,string>> &dict_major,map<string, vector<string> > &major_detail){//当选择专业的时候,学院信息是已知的,所以我们只希望使用者挑选当前学院下的专业
    //从包含学院,专业,学制,导员的csv文件里,提取学院和专业
    ifstream file(filename);//打开文件
    if(file.is_open() &&  dict_major.empty() && major_detail.empty()){//如果字典为空且文件可正常打开才正常读取,防止重复读取
        string line;
        getline(file,line);//跳过标题行
        while(getline(file,line)){
            vector<string> row;
            row=split(line,',');//row[0]为学院编号,row[1]为学院名,row[2]为专业编号,row[3]为专业名,row[4]为学制,row[5]为层次，row[6]为导师
                                //由于我们是直接存名字(方便显示),所以只用row[0]
            if(row[2].length()==1){row[2]="0"+row[2];}//如果专业编号是1位,则前面补0
            dict_major[row[0]][row[2]]=row[3];//将学院编号作为键,“专业编号(两位)：专业名”为键值对的字典作为值,存入字典,这样想要获取专业名就要通过Majors[学院编号][专业编号]
            major_detail[row[0]+row[2]].push_back(row[4]);//row[4]为学制,键为学院编号+专业编号,vector的第一个元素为学制
            major_detail[row[0]+row[2]].push_back(row[5]);//row[5]为层次,vector第二个元素为层次
            major_detail[row[0]+row[2]].push_back(row[6]);//row[6]为导师,vector第三个元素为导师
        }
        return true;
    }
    else{
        cout<<"无法正常载入专业文件"<<endl;
        return false;
    }
}
bool Append_to_Csv(const string &filename,vector<Stufield> &students){//将动态数组Students_Unsaved中的内容按一定格式写入csv文件
    ofstream csv_file(filename,ios::app);//追加方式写入文件
    if (csv_file.is_open()){
        // 写入学生信息
        for (const auto& student : students){
            csv_file<<student.stu_id<<",";
            csv_file<<student.name<<",";
            csv_file<<student.gender<<",";
            csv_file<<student.age<<",";
            csv_file<<student.nationality<<",";
            csv_file<<student.people<<",";
            csv_file<<student.birthday<<",";
            csv_file<<student.marriage<<",";
            csv_file<<student.politics<<",";
            csv_file<<student.stu_type<<",";
            csv_file<<student.enroll_date<<",";
            csv_file<<student.enroll_way<<",";
            csv_file<<student.college<<",";
            csv_file<<student.major<<",";
            csv_file<<student.grade<<",";
            csv_file<<student.class_num<<",";
            csv_file<<student.cengci<<",";
            csv_file<<student.xuezhi<<",";
            csv_file<<student.tutor<<",";
            csv_file<<student.id<<endl;
        }
        csv_file.close();
        cout<< "File write successful."<<std::endl;
        return true;
    } 
    else{
        cerr<<"Error opening the file."<<std::endl;
        return false;
    }
}
bool Write_to_Csv(const string &filename,vector<Stufield> &students){//将动态数组Students_Unsaved中的内容按一定格式写入csv文件
    ofstream csv_file(filename,ios::trunc);//覆盖写入文件,如果文件不存在则创建
    csv_file<<endl;
    if (csv_file.is_open()){
        // 写入学生信息
        for (const auto& student : students){
            csv_file<<student.stu_id<<",";
            csv_file<<student.name<<",";
            csv_file<<student.gender<<",";
            csv_file<<student.age<<",";
            csv_file<<student.nationality<<",";
            csv_file<<student.people<<",";
            csv_file<<student.birthday<<",";
            csv_file<<student.marriage<<",";
            csv_file<<student.politics<<",";
            csv_file<<student.stu_type<<",";
            csv_file<<student.enroll_date<<",";
            csv_file<<student.enroll_way<<",";
            csv_file<<student.college<<",";
            csv_file<<student.major<<",";
            csv_file<<student.grade<<",";
            csv_file<<student.class_num<<",";
            csv_file<<student.cengci<<",";
            csv_file<<student.xuezhi<<",";
            csv_file<<student.tutor<<",";
            csv_file<<student.id<<endl;
        }
        csv_file.close();
        cout<< "File write successful."<<std::endl;
        return true;
    } 
    else{
        cerr<<"Error opening the file."<<std::endl;
        return false;
    }
}
vector<string> split(const string &s, char delimiter){//根据将一行划分
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)){
        tokens.push_back(token);
    }
    return tokens;
}
vector<string> csv_split(const string &csv_name,int column_num){
    ifstream csv_file(csv_name+".csv");
    string line;
    vector<string> row;//一行数据按列进行划分
    vector<string> columns;//从每行中提取特定列
    if(csv_file.is_open()){
        getline(csv_file,line);//跳过第一行
        while(getline(csv_file,line)){
            row=split(line,',');
            if(column_num<row.size() && column_num>=0){
                columns.push_back(row[column_num]);
            }
            else{
                cout<<"列编号超出了范围"<<endl;
                break;
            }
        }
    }
    else{
        cout<<"文件不能正常打开"<<endl;
    }
    return columns;
}
bool InputStuid(string &stu_id){
    string s_id;
    cout<<"*******************************************"<<endl;
    cout<<"请输入你要修改学生信息的学号"<<endl;
    cout<<"*******************************************"<<endl;
    cin>>s_id;
    if(s_id.length()==9){//如果输入的学号长度为9,进行下一部判断
        for(int i=0;i<9;i++){//判断学号是否全为数字
            if(!isdigit(s_id[i])){//如果学号中出现非数字字符,则不合法
                cout<<"输入的学号不合法<学号必须为纯数字>"<<endl;
                return false;
            }
        }
        stu_id=s_id;//将输入的学号赋值给stu_id
        cout<<"学号输入成功"<<endl;
        return true;
    }
    else{
        cout<<"输入的学号不合法<学号必须为9为数字>"<<endl;
        return false;
    }
}
void ShowStudents(const vector<Stufield> &students, bool show_by_page){
    if(students.empty()){
        cout<<"<当前没有任何学生信息>"<<endl;
        return;
    }
    else{
        if (!show_by_page) {
            // 不按页显示,直接显示所有学生信息
            for (const auto &student : students){
                student.ShowStudent();
            }
            cout<<"<按任意键继续下一步操作......>"<<endl;
            getch();
            return;
        } 
        else{
            int total_students = students.size();
            int total_pages=(total_students+PageSize-1)/PageSize; // 计算总页数
            int current_page=0;//当前页数,起始页为0
            system("cls");//清屏
            while(true){
                system("cls");
                // 显示当前页的学生信息
                cout<<"Page:"<<current_page+1<<"/"<<total_pages<<":"<<endl;
                int start_index=current_page*PageSize;
                int end_index=min((current_page + 1)*PageSize, total_students);
                for (int i = start_index; i < end_index; ++i){
                    students[i].ShowStudent();
                }
                // 提示用户选择操作
                cout<<"按下 'A' 回到上一页, 按下 'D' 翻至下一页, 按下 'Q' 退出显示 ";
                // 显示页数在右下角
                cout<<setw(100)<<"Page:"<<current_page+1<<"/" << total_pages << endl;
                char choice;
                choice=getch();
                choice=toupper(choice);//将用户输入转换为大写
                // 根据用户选择更新当前页数
                if (choice=='A'){
                    if (current_page>0){
                        --current_page;
                    } 
                    else{
                        cout << "\n这已经是第一页了." << endl;
                    }
                } 
                else if (choice=='D'){
                    if (current_page<total_pages-1){
                        ++current_page;
                    } 
                    else{
                        cout << "\n这已经是最后一页了." << endl;
                    }
                }
                else if(choice=='Q'){
                    system("cls");
                    return;
                }
                else{
                    continue;
                }
            }//如果用户输入Q,则退出循环,否则继续显示下一页
        }
    }
}
bool InputStuid_find(string &stu_id_find){
    string s_id;
    cout<<"*******************************************"<<endl;
    cout<<"请输入你要查找的学生的学号"<<endl;
    cout<<"*******************************************"<<endl;
    cin>>s_id;
    if(s_id.length()==9){//如果输入的学号长度为9,进行下一部判断
        for(int i=0;i<9;i++){//判断学号是否全为数字
            if(!isdigit(s_id[i])){//如果学号中出现非数字字符,则不合法
                cout<<"输入的学号不合法<学号必须为纯数字>"<<endl;
                return false;
            }
        }
        stu_id_find=s_id;//将输入的学号赋值给stu_id
        cout<<"学号输入成功"<<endl;
        cout<<"<正在为你查找学号为"<<stu_id_find<<"的学生信息......>"<<endl;
        stu_id_find=s_id;
        return true;
    }
    else{
        cout<<"输入的学号不合法<学号必须为9为数字>"<<endl;
        return false;
    }
}
bool InputName_find(string &name_find){
    string name;
    cout<<"*******************************************"<<endl;
    cout << "请输入你要查找的学生的姓名: "<<endl;
    cout<<"*******************************************"<<endl;
    cin >> name;
    if(isChinese(name) && name.length()<=10 && name.length()>=2){
        name_find=name;
        cout<<"姓名输入成功"<<endl;
        cout<<"<正在为你查找姓名为"<<name_find<<"的学生信息......>"<<endl;
        return true;
    }
    else if(isEnglish(name) && name.length()<=40 && name.length()>=1){
        name_find=name;
        cout<<"姓名输入成功"<<endl;
        cout<<"<正在为你查找姓名为"<<name_find<<"的学生信息......>"<<endl;
        return true;
    }
    else{
        cout<<"输入的姓名不合法,请重新输入!"<<endl;
        return false;
    }
}
bool InputTutor_find(string &tutor_find){
    string name;
    cout<<"*******************************************"<<endl;
    cout << "请输入你要查找的的学生的导师的姓名: "<<endl;
    cout<<"*******************************************"<<endl;
    cin >> name;
    if(isChinese(name) && name.length()<=10 && name.length()>=2){
        tutor_find=name;
        cout<<"姓名输入成功"<<endl;
        cout<<"<正在为你查找导师姓名为"<<tutor_find<<"的学生信息......>"<<endl;
        return true;
    }
    else if(isEnglish(name) && name.length()<=40 && name.length()>=1){
        tutor_find=name;
        cout<<"姓名输入成功"<<endl;
        cout<<"<正在为你查找导师姓名为"<<tutor_find<<"的学生信息......>"<<endl;
        return true;
    }
    else{
        cout<<"输入的姓名不合法,请重新输入!"<<endl;
        return false;
    }
}
bool InputGender_find(string &gender_find){
    int user_choice=1;
    cout<<"*******************************************"<<endl;
    cout << "性别选择列表如下:" << endl;
    cout << "[1]:男"<<endl;
    cout << "[2]:女"<<endl;
    cout<<"*******************************************"<<endl;
    cout << "请输入你要查找的学生的性别: "<<endl;
    cin >> user_choice;
    if(user_choice!=1 && user_choice!=2){
        cout<<"输入的性别不合法,请重新输入！"<<endl;
        return false;
    }
    gender_find=(user_choice==1)?"男":"女";//存实际名称,方便后期输出显示
    cout<<"性别输入成功"<<endl;
    cout<<"<正在为你查找性别为"<<gender_find<<"的学生信息......>"<<endl;
    return true;
}
bool InputAge_find(string &age_find){
    int age;
    cout<<"*******************************************"<<endl;
    cout << "请输入你要查找的学生的年龄: "<<endl;
    cout<<"*******************************************"<<endl;
    cin >> age;
    if(age>=10 && age<=80){
        age_find=to_string(age);
        cout<<"年龄输入成功"<<endl;
        cout<<"<正在为你查找年龄为"<<age_find<<"的学生信息......>"<<endl;
        return true;
    }
    else{
        cout<<"输入的年龄不合法,请重新输入！"<<endl;
        return false;
    }
}
bool InputClassNum_find(string &class_num_find){
    string class_num;
    cout<<"*******************************************"<<endl;
    cout<<"请输入你的班级:<输入班级数字号即可,只能是>"<<endl;
    cout<<"*******************************************"<<endl;
    cin>>class_num;
    if(class_num.length()==1){
        class_num_find=class_num;
        cout<<"班级输入成功"<<endl;
        cout<<"<正在为你查找班级为"<<class_num_find<<"的学生信息......>"<<endl;
        return true;
    }
    return false;
}
bool InputEnroll_date_find(string &enroll_date_find){
    cout<<"*******************************************"<<endl;
    cout << "请输入你要查找的学生的入学日期: <格式为yyyy-mm-dd>"<<endl;
    cout<<"*******************************************"<<endl;
    Date temp;
    int year,month,day;
    scanf("%d-%d-%d",&year,&month,&day);
    temp.year=year;//只存编号,如果要显示学院名称,通过ShowPeople显示
    temp.month=month;
    temp.day=day;
    if(isLegal(temp) && year<=CurYear){
        enroll_date_find=Date_to_String(temp);
        cout<<"<正在为你查找入学日期为"<<enroll_date_find<<"的学生信息......>"<<endl;
        return true;
    }
    else{
        cout<<"输入的入学日期不合法,请重新输入！"<<endl;
        return false;
    }
}
bool InputCengci_find(string &cengci_find){
    cout<<"*******************************************"<<endl;
    cout <<"请选择你要查找的学生的层次: "<<endl;
    cout<<"[1]: 本科"
          "[2]: 硕士"
          "[3]: 博士"<<endl;
    cout<<"*******************************************"<<endl;
    cout << "请选择: "<<endl;
    int user_choice;
    cin >> user_choice;
    if(user_choice<1 || user_choice>3){
        cout<<"输入的性别不合法,请重新输入！"<<endl;
        return false;
    }
    if(user_choice==1){
        cengci_find="本科";
    }
    else if(user_choice==2){
        cengci_find="硕士";
    }
    else if(user_choice==3){
        cengci_find="博士";
    }
    cout<<"层次输入成功"<<endl;
    cout<<"<正在为你查找层次为"<<cengci_find<<"的学生信息......>"<<endl;
    return true;
}
bool InputXuezhi_find(string &xuezhi_find){
    cout<<"*******************************************"<<endl;
    cout <<"请输入你要查找的学生的学制年限: "<<endl;
    cout<<"*******************************************"<<endl;
    cout << "请输入年份数: "<<endl;
    int year;
    if(scanf("%d",&year)!=1 || year<1 || year>10){
        cout<<"输入的年份数不合法,请重新输入！"<<endl;
        return false;
    }
    xuezhi_find=to_string(year)+"年";
    cout<<"学制年限输入成功"<<endl;
    cout<<"<正在为你查找学制年限为"<<xuezhi_find<<"的学生信息......>"<<endl;
    return true;
}   
bool InputBirth_find(string &birthday_find){
    cout<<"*******************************************"<<endl;
    cout << "请输入你要查找的学生的出生日期:<格式为yyyy-mm-dd> "<<endl;
    cout<<"*******************************************"<<endl;
    Date temp;
    int year,month,day;
    scanf("%d-%d-%d",&year,&month,&day);
    temp.year=year;//只存编号,如果要显示学院名称,通过ShowPeople显示
    temp.month=month;
    temp.day=day;
    if(isLegal(temp) && year<=CurYear){
        birthday_find=Date_to_String(temp);
        cout<<"<正在为你查找出生日期为"<<birthday_find<<"的学生信息......>"<<endl;
        return true;
    }
    else{
        cout<<"输入的出生日期不合法,请重新输入！"<<endl;
        return false;
    }
}

//友元函数定义
bool Load_from_Csv(const string &filename,vector<Stufield> &students){//从csv文件中读取学籍信息,存入动态数组students
    ifstream csv_file(filename);
    vector<Stufield> temp_students;
    if(csv_file.is_open()){
        string line;
        vector<string> row;
        getline(csv_file,line);//跳过第一行
        while(getline(csv_file,line)){
            row=split(line,',');
            if(row.size()==20){
                Stufield student(row);
                temp_students.push_back(student);
            }
        }
        students=temp_students;
        csv_file.close();
        return true;
    }
    else{
        cerr<<"无法正常载入csv文件中的学生信息"<<endl;
        return false;
    }
}
bool MainStuSearch(vector<Stufield> &students){
    vector<int> result_index;
    vector<Stufield> temp_students=students;
    vector<Stufield> result_students={};
    string wanted;
    Feature by;
    while(true){//只在选择E_quit退出
        by=SearchMenu();//选择查找方式
        if(by==E_quit){
                cout<<"<按任意键返回主菜单......>"<<endl;
                getch();
                break;
        }
        else if(E_stu_id<=by && by<=E_id){
            while(true){//WantedChoices返回false表示放弃继续查找
                bool flag_continue=true;
                flag_continue=WantedMenu(by,wanted);
                if(!flag_continue){
                    return false;
                }
                result_index=find_stu(temp_students,by,wanted);
                if(result_index.empty()){
                    cout<<"未找到符合条件的记录"<<endl;
                    cout<<"<按任意键返回上级菜单......>"<<endl;
                    getch();
                    
                }
                else{
                    cout<<"符合条件的记录如下:"<<endl;
                    for(int i=0;i<result_index.size();i++){
                        result_students.push_back(temp_students[result_index[i]]);
                    }
                    ShowStudents(result_students,false);
                }
                cout<<"*******************************************"<<endl;
                cout<<"<是否在当前查找结果的基础上进行下一步查找?>"<<endl;
                cout<<"1. 保留结果继续查找"<<endl;
                cout<<"2. 重置结果重新查找"<<endl;
                cout<<"3. 退出查找"<<endl;
                cout<<"*******************************************"<<endl;
                cout<<"请输入你的选择<按要求输入对应编号>"<<endl;
                char choice;
                while(true){
                    choice=getch();
                    if(choice=='1'){
                        if(result_students.empty()){
                            cout<<"<当前查找结果为空,自动为你保留至查找前的结果>"<<endl;
                            result_students.clear();
                            by=SearchMenu();
                            break;
                        }
                        temp_students=result_students;
                        result_students.clear();
                        cout<<"<已经保留了当前查找结果>"<<endl;
                        by=SearchMenu();
                        break;
                    }
                    else if(choice=='2'){
                        result_students.clear();
                        temp_students=students;
                        cout<<"<已经重置了查找结果>"<<endl;
                        by=SearchMenu();
                        break;
                    }
                    else if(choice=='3'){
                        cout<<"<正在返回主菜单......>"<<endl;
                        return true;
                    }
                    else{
                        cout<<"输入错误,请重新输入"<<endl;
                    }
                }
            }
            
        }
    }
    return true;
}
vector<int> find_stu(const vector<Stufield> &students,const Feature &by,const string &wanted){//查找某一种属性在动态数组students中的位置,返回所有符号位置的索引,如果找不到则返回
    vector<int> result_vec={};
    //E 前缀表示enum类型,与类成员进行区分
    for(int i=0;i<students.size();i++){
        if(by==E_name){
            if(students[i].name==wanted){result_vec.push_back(i);}//返回索引
        }
        else if(by==E_gender){
            if(students[i].gender==wanted){result_vec.push_back(i);}//返回索引
        }
        else if(by==E_age){
            if(students[i].age==stoi(wanted)){result_vec.push_back(i);}//返回索引
        }
        else if(by==E_stu_id){
            if(students[i].stu_id==wanted){result_vec.push_back(i);}//返回索引
        }
        else if(by==E_college){
            string college_name=Colleges[students[i].college];
            if(college_name==wanted){result_vec.push_back(i);}//返回索引
        }
        else if(by==E_major){
            string major_name=Majors[students[i].college][(students[i].major).substr(2,2)];
            if(major_name==wanted){result_vec.push_back(i);}//返回索引
        }
        else if(by==E_grade){
            if(students[i].grade==wanted){result_vec.push_back(i);}//返回索引
        }
        else if(by==E_class_num){
            if(students[i].class_num==wanted){result_vec.push_back(i);}//返回索引
        }
        else if(by==E_people){
            if(students[i].people==wanted){result_vec.push_back(i);}
        }
        else if(by==E_nationality){
            if(students[i].nationality==wanted){result_vec.push_back(i);}//返回索引
        }
        else if(by==E_politics){
            if(students[i].politics==wanted){result_vec.push_back(i);}//返回索引
        }
        else if(by==E_stu_type){
            if(students[i].stu_type==wanted){result_vec.push_back(i);}//返回索引
        }
        else if(by==E_cengci){
            if(students[i].cengci==wanted){result_vec.push_back(i);}//返回索引
        }
        else if(by==E_enroll_date){
            if(students[i].enroll_date==wanted){result_vec.push_back(i);}//返回索引
        }
        else if(by==E_marriage){
            if(students[i].marriage==wanted){result_vec.push_back(i);}//返回索引
        }
        else if(by==E_birthday){
            if(students[i].birthday==wanted){result_vec.push_back(i);}//返回索引
        }
        else if(by==E_enroll_way){
            if(students[i].enroll_way==wanted){result_vec.push_back(i);}//返回索引
        }
        else if(by==E_id){
            if(students[i].id==wanted){result_vec.push_back(i);}//返回索引
        }
        else if(by==E_tutor){
            if(students[i].tutor==wanted){result_vec.push_back(i);}//返回索引
        }
        else if(by==E_xuezhi){
            if(students[i].xuezhi==wanted){result_vec.push_back(i);}//返回索引
        }
    }
    return result_vec;//返回空vec表示找不到
}
bool ErrorReact(){//错误反应函数,返回false表示放弃继续查找
    while(true){
        cout<<"*******************************************"<<endl;
        cout<<"<输入错误！请选择下一步操作>"<<endl;
        cout<<"1. 重新输入"<<endl;
        cout<<"2. 返回上一级菜单"<<endl;
        cout<<"*******************************************"<<endl;
        char choice;
        while(true){
            choice=getch();
            if(choice=='1'){
                cout<<choice<<endl;
                return true;
            }
            else if(choice=='2'){
                return false;
            }
            else{
                cout<<"<输入错误,请重新输入对应选项数字>"<<endl;
            }
        }
    }
}
bool AddStudents(vector<Stufield> &students){
    cout<<"*******************************************"<<endl;
    cout<<"你已进入学生信息添加界面"<<endl;
    cout<<"*******************************************"<<endl;
    int i=1;
    int num_to_add;
    cout<<"请输入你要添加的学生数目"<<endl;
    if(scanf("%d",&num_to_add)!=1 || num_to_add<=0){
        cout<<"<输入错误,返回主菜单>"<<endl;
        return false;
    }
    getchar();//清空缓冲区
    while(i<=num_to_add){
        Stufield student;
        cout<<"请输入第"<<i<<"个学生的信息"<<endl;
        bool flag_continue=student.MainInput();//若返回为true,则表示输入信息成功,否则表示输入未完全，不再进行校验
        if(flag_continue){
            if(student.MainCheck()){
                //student.AgeUpdate();
                students.push_back(student);
                cout<<"第"<<i<<"个学生信息添加成功"<<endl;
                cout<<"<按任意键继续添加......>"<<endl;
                getch();
                i++;
            }
            else{
                cout<<"*******************************************"<<endl;
                cout<<"第"<<i<<"个学生信息添加失败"<<endl;
                cout<<"1. 重新输入所有信息"<<endl;
                cout<<"2. 退出添加"<<endl;
                cout<<"*******************************************"<<endl;
                char choice;
                choice=getch();
                if(choice=='1'){
                    cout<<choice<<endl;
                    cout<<"<按任意键开始重新新输入......>"<<endl;
                    getch();
                }
                else if(choice=='2'){
                    cout<<"<按任意键返回主菜单......>"<<endl;
                    getch();
                    return false;
                }
            }
        }
        else{
            return false;//返回false表示中途退出添加
        }
    }
    return true;//返回true表示完全添加成功
}
bool MainStuSet(vector<Stufield> &students,string stu){//只有成功更改学生信息或创建学生信息时才返回true,否则返回false
    vector<int> result_index=find_stu(students,E_stu_id,stu);
    if(result_index.size()==1){
        cout<<"已记录的学生信息如下"<<endl;
        students[result_index[0]].ShowStudent();
        Feature by;
        while((by=SetMenu(Administrate)) != E_quit){
            students[result_index[0]].StuSet(by,Administrate);
        }
        students[result_index[0]].AgeUpdate();
        cout<<"<按任意键返回主菜单......>"<<endl;
        getch();
        return true;
    }
    else if(result_index.size()==0){
        cout<<"*********************************************"<<endl;
        cout<<"并不存在该学生的信息，是否选择创建学生信息？"<<endl;
        cout<<"1. 创建学生信息"<<endl;
        cout<<"2. 返回主菜单"<<endl;
        cout<<"*********************************************"<<endl;
        cout<<"请输入你的选择<按要求输入对应编号>"<<endl;
        char choice;
        while(true){
            choice=getch();
            if(choice=='1'){
                cout<<"<按任意键开始创建学生信息......>"<<endl;
                Stufield student;
                bool flag_continue=student.MainInput();
                if(flag_continue){
                    if(student.MainCheck()){
                        students.push_back(student);
                        return true;
                    }
                }
                else{
                    return false;
                }
            }
            else if(choice=='2'){
                cout<<"<按任意键返回主菜单......>"<<endl;
                getch();
                return false;
            }
            else{
                cout<<"<输入错误,请重新输入>"<<endl;
            }
        }
    }
    else{
        cout<<"*********************************************"<<endl;
        cout<<"存在多个符合条件的记录！"<<endl;
        cout<<"*********************************************"<<endl;
        return false;
    }
}
bool DeleteStudents(vector<Stufield> &students,vector<Stufield> &students_deleted,Feature by,string wanted){//删除vector<Stufield>中符合条件的记录,返回删除的记录，如果没有则返回空vec
    vector<int> result_index=find_stu(students,by,wanted);
    if(result_index.empty()){
        cout<<"没有需要删除的记录"<<endl;
        return false;
    }
    else{
        for(int i=result_index.size()-1;i>=0;i--){//倒序删除是为了防止删除过程中索引变化导致错误
            students_deleted.push_back(students[result_index[i]]);
            students.erase(students.begin() + result_index[i]);
        }
        cout<<"已删除符合条件的记录"<<endl;
    }
    return true;
}

bool UpdateAge(vector<Stufield> &students){
    for(auto &student : students){
        int year,month,day;
        try{
            year=stoi(student.birthday.substr(0,4));
            month=stoi(student.birthday.substr(5,2));
            day=stoi(student.birthday.substr(8,2));
            student.age=(CurMonth>=month && CurDay>=day)?CurYear-year:CurYear-year-1;//当前日期在生日之前,年龄减一
        }
        catch(...){
            cout<<"生日格式错误"<<endl;
        }
    }
    return true;
}
bool SortStudents(vector<Stufield> &students,Feature by,bool reverse){
    if(by==E_name){
        sort(students.begin(),students.end(),[&](const Stufield &stu1,const Stufield &stu2){
            return reverse? (stu2.name < stu1.name) : (stu1.name < stu2.name);
        });
    }
    else if(by==E_gender){
        sort(students.begin(),students.end(),[&](const Stufield &stu1,const Stufield &stu2){
            return reverse? (stu2.gender < stu1.gender) : (stu1.gender < stu2.gender);
        });
    }
    else if(by==E_age){
        sort(students.begin(),students.end(),[&](const Stufield &stu1,const Stufield &stu2){
            return reverse? (stu2.age < stu1.age) : (stu1.age < stu2.age);
        });
    }
    else if(by==E_stu_id){
        sort(students.begin(),students.end(),[&](const Stufield &stu1,const Stufield &stu2){
            return  reverse? (stu2.stu_id < stu1.stu_id) : (stu1.stu_id < stu2.stu_id);
        });
    }
    else if(by==E_college){//按学院编号排序
        sort(students.begin(),students.end(),[&](const Stufield &stu1,const Stufield &stu2){
            return  reverse? (stu2.college < stu1.college) : (stu1.college < stu2.college);
        });
    }
    else if(by==E_major){//按专业编号排序
        sort(students.begin(),students.end(),[&](const Stufield &stu1,const Stufield &stu2){
            return  reverse? (stu2.major < stu1.major) : (stu1.major < stu2.major);
        });
    }
    else if(by==E_grade){
        sort(students.begin(),students.end(),[&](const Stufield &stu1,const Stufield &stu2){
            return  reverse? (stu2.grade < stu1.grade) : (stu1.grade < stu2.grade);
        });
    }
    else if(by==E_class_num){
        sort(students.begin(),students.end(),[&](const Stufield &stu1,const Stufield &stu2){
            return  reverse? (stu2.class_num < stu1.class_num) : (stu1.class_num < stu2.class_num);
        });
    }
    else if(by==E_people){
        sort(students.begin(),students.end(),[&](const Stufield &stu1,const Stufield &stu2){
            return  reverse? (stu2.people < stu1.people) : (stu1.people < stu2.people);
        });
    }
    else if(by==E_nationality){
        sort(students.begin(),students.end(),[&](const Stufield &stu1,const Stufield &stu2){
            return  reverse? (stu2.nationality < stu1.nationality) : (stu1.nationality < stu2.nationality);
        });
    }
    else if(by==E_politics){
        sort(students.begin(),students.end(),[&](const Stufield &stu1,const Stufield &stu2){
            return  reverse? (stu2.politics < stu1.politics) : (stu1.politics < stu2.politics);
        });
    }
    else if(by==E_stu_type){
        sort(students.begin(),students.end(),[&](const Stufield &stu1,const Stufield &stu2){
            return  reverse? (stu2.stu_type < stu1.stu_type) : (stu1.stu_type < stu2.stu_type);
        });
    }
    else if(by==E_cengci){
        sort(students.begin(),students.end(),[&](const Stufield &stu1,const Stufield &stu2){
            return  reverse? (stu2.cengci < stu1.cengci) : (stu1.cengci < stu2.cengci);
        });
    }
    else if(by==E_xuezhi){
        sort(students.begin(),students.end(),[&](const Stufield &stu1,const Stufield &stu2){
            return  reverse? (stu2.xuezhi < stu1.xuezhi) : (stu1.xuezhi < stu2.xuezhi);
        });
    }
    else if(by==E_enroll_date){
        sort(students.begin(),students.end(),[&](const Stufield &stu1,const Stufield &stu2){
            return  reverse? (stu2.enroll_date < stu1.enroll_date) : (stu1.enroll_date < stu2.enroll_date);
        });
    }
    else if(by==E_marriage){
        sort(students.begin(),students.end(),[&](const Stufield &stu1,const Stufield &stu2){
            return  reverse? (stu2.marriage < stu1.marriage) : (stu1.marriage < stu2.marriage);
        });
    }
    else if(by==E_birthday){
        sort(students.begin(),students.end(),[&](const Stufield &stu1,const Stufield &stu2){
            return  reverse? (stu2.birthday < stu1.birthday) : (stu1.birthday < stu2.birthday);
        });
    }
    else if(by==E_enroll_way){
        sort(students.begin(),students.end(),[&](const Stufield &stu1,const Stufield &stu2){
            return  reverse? (stu2.enroll_way < stu1.enroll_way) : (stu1.enroll_way < stu2.enroll_way);
        });
    }
    else if(by==E_id){
        sort(students.begin(),students.end(),[&](const Stufield &stu1,const Stufield &stu2){
            return  reverse? (stu2.id < stu1.id) : (stu1.id < stu2.id);
        });
    }
    else if(by==E_tutor){
        sort(students.begin(),students.end(),[&](const Stufield &stu1,const Stufield &stu2){
            return  reverse? (stu2.tutor < stu1.tutor) : (stu1.tutor < stu2.tutor);
        });
    }
    else if(by==E_quit){
        cout<<"已退出排序"<<endl;
        return false;
    }
    else{
        cout<<"排序方式错误"<<endl;
        return false;
    }
    return true;
}
bool MainStuSort(vector<Stufield> &students){
    vector<Stufield> temp_students=students;
    Feature by;
    bool reverse=false;
    while(true){
        system("cls");
        by=SortMenu();
        if(E_stu_id<=by && by<=E_id){
            cout<<"*******************************************************************************\n";
            cout<<"* 1.升序排序"<<endl;
            cout<<"* 2.降序排序"<<endl;
            cout<<"*******************************************************************************\n";
            cout<<"请输入你的选择<按要求输入对应编号>"<<endl;
            while(true){
                char choice;
                choice=getch();
                if(choice=='1'){
                    reverse=false;
                    break;
                }
                else if(choice=='2'){
                    reverse=true;
                    break;
                }
                else{
                    cout<<"输入错误，请重新输入"<<endl;
                }
            }
            cout<<"<正在排序......>"<<endl;
            SortStudents(temp_students,by,reverse);
            ShowStudents(temp_students);
            cout<<"<是否对当前结果继续排序？ (Y/N)>"<<endl;
            while(true){
                char choice;
                choice=toupper(getch());
                if(choice=='Y'){
                    
                    break;
                }
                else if(choice=='N'){
                    temp_students=students;
                    cout<<"已经复原到原始顺序"<<endl;
                    break;
                }
                else{
                    cout<<"输入错误，请重新输入"<<endl;
                }
            }
        }
        else if(by==E_quit){
            cout<<"即将退出排序"<<endl;
            cout<<"是否保存排序结果？ (Y/N)>"<<endl;
            while(true){
                char choice;
                choice=toupper(getch());
                if(choice=='Y'){
                    students=temp_students;
                    cout<<"排序结果已保存"<<endl;
                    return true;
                }
                else if(choice=='N'){
                    cout<<"排序结果已丢弃"<<endl;
                    return true;
                }
                else{
                    cout<<"输入错误，请重新输入"<<endl;
                }
            }
        }
        cout<<"<按任意键继续......>"<<endl;
        getch();
    }
    return true;
}
bool MainStuDelete(vector<Stufield> &students){
    Feature by;
    vector<Stufield> deleted_students;
    system("cls");
    while(true){
        by=DeleteMenu(Administrate);
        if(by==E_quit){ 
            cout<<"<即将退出删除......>"<<endl;
            cout<<"<是否将被删除的记录放入回收站？ (Y/N)>"<<endl;
            while(true){
                char choice;
                choice=toupper(getch());
                if(choice=='Y'){
                    cout<<"<正在将被删除的记录放入回收站......>"<<endl;
                    Append_to_Csv("students_deleted.csv",deleted_students);
                    cout<<"<已将被删除的记录放入回收站>"<<endl;
                    return true;
                }
                else if(choice=='N'){
                    cout<<"<删除结果已丢弃>"<<endl;
                    return true;
                }
                else{
                    cout<<"<输入错误，请重新输入>"<<endl;
                }
            }
        }
        else{
            string wanted;
            cout<<"请输入你要删除的具体条件"<<":<输入*代表全部删除>"<<endl;
            cin>>wanted;
            if(wanted=="*"){
                cout<<"你确定要删除全部学生信息？"<<endl;
                cout<<"1. 确认删除"<<endl;
                cout<<"2. 取消删除"<<endl;
                cout<<"请输入你的选择<按要求输入对应编号>"<<endl;
                while(true){
                    char choice;
                    choice=getch();
                    if(choice=='1'){
                        cout<<"正在删除全部学生信息"<<endl;
                        for(auto &student : students){
                            deleted_students.push_back(student);
                        }
                        students.clear();
                        cout<<"全部学生信息已删除"<<endl;
                        cout<<"<按任意键返回上级菜单......>"<<endl;
                        getch();
                        break;
                    }
                    else if(choice=='2'){
                        cout<<"取消删除"<<endl;
                        cout<<"<按任意键返回上级菜单......>";
                        getch();
                        break;
                    }
                    else{
                        cout<<"输入错误，请重新输入"<<endl;
                    }
                }
            }
            else{
                cout<<"<正在删除符合条件的记录>"<<endl;
                DeleteStudents(students,deleted_students,by,wanted);  
            }
        }
    }
}
