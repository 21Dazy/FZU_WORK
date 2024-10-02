#include "102300229_叶达_student.h"
#include "102300229_叶达_student2.cpp"
using namespace std;
bool Setted=false;//是否更改过学生信息
int main(){
    ios_base::sync_with_stdio(false);//关闭缓冲区同步
    //SetConsoleOutputCP(65001);
	
	MajorsInit_map_map("学院专业.csv",Majors,Tutors_Cengci);//初始化专业与导师信息
    DataInit_map_int("国籍.csv",Nations);///初始化国籍表信息
    DataInit_map_int("民族.csv",Peoples);//初始化民族信息
    DataInit_map_int("政治面貌.csv",Politics);//初始化政治面貌信息
    DataInit_map_int("婚姻状况.csv",Marriages);//初始化婚姻状况信息
    DataInit_map_int("学生类别.csv",StuTypes);//初始化学生类别信息
    DataInit_map_str("学院与编号.csv",Colleges);//初始化学院与编号信息
    DataInit_map_int("入学方式.csv",EnrollWays);//初始化入学方式信息
    DataInit_vector("行政区划代码.csv",CityCodes);//初始化行政区划代码信息
	Load_from_Csv(FileNameR,Students_Saved);//从要读取的csv文件中载入已经保存的学生信息
	UpdateAge(Students_Saved);//更新学生年龄信息
	cout<<"<自动从数据库中载入学生信息......>"<<endl;
    while(true){
    	char choice1;//获取用户选择
      	while(true){//选择主体循环
      		ShowHead(ShowByPage_On);//显示版权信息，当前时间，菜单信息
        	choice1=getch();//获取用户输入的字母，不显示在屏幕上
        	if(isalpha(choice1) && (cout<<(choice1=toupper(choice1))<<endl)){//判断输入是否为字母
        		switch (choice1){
					case 'A':{	//添加学生信息
						AddStudents(Students_Saved);//存放所有没有写进数据库的学生信息
						break;
					}
					case 'B':{// 修改指定学号的学生信息
						string stu_id;
						bool flag_continue=1;
						bool flag_legal=0;
						while(flag_continue){//如果输入的学号不合法，则提示重新输入，直到输入合法为止
							//循环结束要么输入合法学号，要么用户选择退出，此时flag_continue=0
							flag_legal=InputStuid(stu_id);
							if(!flag_legal){
								cout<<"<是否要继续输入学号?(Y/N)>"<<endl;
								while(true){
									char choice2=getch();
									if(choice2=='Y' || choice2=='y'){
										cout<<choice2<<endl;
										break;
									}
									else if(choice2=='N' || choice2=='n'){
										cout<<choice2<<endl;
										flag_continue=0;
										break;
									}
									else{
										cout<<"请按要求输入字母！"<<endl;
									}
								}
							}
							else{
								flag_continue=0;
							}
						}
						if(flag_legal==1){
							MainStuSet(Students_Saved,stu_id);
						}
						else{
							cout<<"已退出修改"<<endl;
							cout<<"<按下任意返回主菜单......>"<<endl;
							getch();
						}
						break;
					}
					case 'C':{//搜索学生信息
						MainStuSearch(Students_Saved);	
						break;
					}
					case 'D':{//排序功能
						MainStuSort(Students_Saved);
						break;
					}
					case 'E':{
						cout<<"<正在将本次操作编辑过的信息以覆盖的方式保存到数据库......>"<<endl;
						Write_to_Csv(FileNameS,Students_Saved);
						cout<<"<保存成功>!"<<endl;
						break;
					}
					case 'F':{//以添加的方式导入学生信息到数据库
						cout<<"<正在以添加的方式导入学生信息到数据库......>"<<endl;
						Append_to_Csv(FileNameR,Students_Saved);
						cout<<"<导入成功>!"<<endl;
						break;
					}
					case 'G':{//显示数据库内的学生信息
						vector<Stufield> students_temp;
						Load_from_Csv(FileNameR,students_temp);
						ShowStudents(students_temp,true);
						break;
					}
					case 'H':{//显示当前正在操作的学生信息
						ShowStudents(Students_Saved,true);
						break;
					}
					case 'I':{//将数据库的信息导入到程序中
						Load_from_Csv(FileNameR,Students_Saved);
						UpdateAge(Students_Saved);//更新学生年龄信息
						cout<<"<导入成功>!"<<endl;
						break;
					}
					case 'J':{//删除指定学生或所有信息并将其放入回收站
						MainStuDelete(Students_Saved);
						break;
					}
					case 'K':{//清空数据库中的所有信息
						while(true){
							cout<<"<是否要清空数据库文件?(Y/N)>"<<endl;
							char choice=getch();
							if(choice=='Y' || choice=='y'){
								cout<<"<正在清空数据库文件......>"<<endl;
								ofstream file_deleted("students.csv",ios::trunc);
								Load_from_Csv("students.csv",Students_Deleted);
								Append_to_Csv("students_deleted.csv",Students_Deleted);
								cout<<"<已先将所有信息自动保存到回收站>"<<endl;
								Students_Deleted.clear();
								file_deleted.clear();
								cout<<"<已清空数据库文件>"<<endl;
								break;
							}
							else if(choice=='N' || choice=='n'){
								cout<<"<已取消操作>"<<endl;
								break;
							}
							else{
								cout<<"<请按要求输入字母!>"<<endl;
							}
						}
						break;
					}
					case 'L':{//显示回收站文件中的学生信息
						vector<Stufield> students_temp;
						Load_from_Csv("students_deleted.csv",students_temp);
						ShowStudents(students_temp,true);
						break;
					}
					case 'M':{//清空回收站储存信息
						while(true){
							cout<<"<是否要清空回收站?(Y/N)>"<<endl;
							char choice=getch();
							if(choice=='Y' || choice=='y'){
								cout<<"<正在清空回收站......>"<<endl;
								ofstream file_deleted("students_deleted.csv",ios::trunc);
								file_deleted.clear();
								cout<<"<已清空回收站>"<<endl;
								break;
							}
							else if(choice=='N' || choice=='n'){
								cout<<"已取消操作"<<endl;
								break;
							}
							else{
								cout<<"请按要求输入字母！"<<endl;
							}
						}
						break;
					}
					case 'N':{//复原回收站信息
						while(true){
							cout<<"<是否要将回收站信息复原到当前操作的学生信息中?(Y/N)>"<<endl;
							char choice=getch();
							if(choice=='Y' || choice=='y'){
								cout<<"<正在复原回收站信息......>"<<endl;
								Load_from_Csv("students_deleted.csv",Students_Deleted);
								Students_Saved.insert(Students_Saved.end(),Students_Deleted.begin(),Students_Deleted.end());
								cout<<"<已复原回收站信息>"<<endl;
								break;
							}
							else if(choice=='N' || choice=='n'){
								cout<<"已取消操作"<<endl;
								break;
							}
							else{
								cout<<"请按要求输入字母！"<<endl;
							}
						}
						break;
					}
					case 'O':{//管理员模式，实现管理员登录功能
						bool flag_continue=1;
						while(flag_continue){
							cout<<"<请输入管理员密码>"<<endl;
							string password;
							cin>>password;
							if(password=="password"){
								cout<<"<管理员登录成功>"<<endl;
								Administrate=true;
								break;
							}
							else{
								cout<<"<密码错误!>"<<endl;
								cout<<"<是否要重新输入?(Y/N)>"<<endl;
								while(true){
									char choice=getch();
									if(choice=='Y' || choice=='y'){
										continue;
									}
									else if(choice=='N' || choice=='n'){
										flag_continue=0;
										break;
									}
									else{
										cout<<"请按要求输入字母！"<<endl;
									}
								}
							}
						}
						break;
					}
					case 'P':{//设置功能，调整文件存放路径，调整全局分页显示
						SettingMenu(Administrate);
						break;
					}
					case 'Q':{
						cout<<"正在退出系统......"<<endl;
						if(AutoSave){
							Write_to_Csv("students.csv",Students_Saved);
						}
						//Append_to_Csv("students_deleted.csv",Students_Deleted);//需要保存的
						exit(0);
					}
					default://非选择项反馈
						cout<<"\n未知操作,请重新输入！"<<endl;
						break;

				}
			}
			else{//非法输入反馈
				cout<<"请按要求输入字母！"<<endl;
				cout<<"<按下任意键继续>......"<<endl;
				getch();
				break;
			}

      	}
    }
}
