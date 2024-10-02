#ifndef _LINKDEMO_H_
#define _LINKDEMO_H_

#include<stdio.h>
#include <time.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>

typedef struct Date{
    int year;
    int month;
    int day;
}Date;
typedef struct LinkNode{
    Date val;
    struct LinkNode *next;
}LinkNode;

extern int DisplayOn;//是否分显示,默认为0，即不分页
extern Date origin;//计算相差天数的起点值
extern int NodeNum;//统计节点数
extern const int days[];
extern int Row;//分页输出时一页的行数
extern int Col;//分页输出时一页的列数
extern char FileNameR[];//读取路径
extern char FileNameS[];//保存路径

int isPrime(int n);//判断素数
int isLeap(int year);//判断闰年
int isLegal(Date date);// 检验输入日期合法性
int Days_in_Month(int year ,int month);
int DateCmp(Date d1,Date d2);//比较两个日期的大小

void ShowCopyright();//显示版权信息
void ShowTime();//显示系统时间
void ShowMenu();//显示菜单
void SelectDate(LinkNode *head);//显示特定日期的数据
void ShowLink(LinkNode *head,int n);//显示链表
void ShowIllegal(LinkNode *head);//显示非法日期
void ShowPrime(LinkNode *head);//显示年月日都为素数的节点
void ShowByPage(LinkNode *head);//分页显示

LinkNode* SetLink(int n);//创建n个节点的链表
LinkNode* RandomLink(int n);//创建一个有n个节点的(无序)链表，链表每个结点存放的数据为[1923,2025]之间的日期（年、月、日）数据（随机产生）

void ShowLink(LinkNode *head,int n);//显示链表
void ShowIllegal(LinkNode *head);//显示非法日期
void ShowPrime(LinkNode *head);//显示年月日都为素数的节点
void ShowByPage(LinkNode *head);//分页显示

void DaysDiff(LinkNode *head);//显示前n个节点日期到1902.1.1的天数

LinkNode* Read_to_Link(char *fileName);//读取文件
void FileClear(char *filename);//清除文件内容
void LinkReverse(LinkNode *head);//
void Save_to_File(LinkNode *head,char *filename);//将链表保存到文件

void LinkSort(LinkNode *head);//根据日期先后将链表排序
void LinkDelete(LinkNode *head);//删除非法节点
void NodeInsert(LinkNode *head);//在链表中插入一个节点
void InsertHead(LinkNode *head);//在链表头部插入一个节点
void InsertTail(LinkNode *head);//在链表尾部插入一个节点
void InsertBefore(LinkNode *head);//将用当前日期构造的一个新结点插入到第一个大于该结点日期的前面
void InsertAfter(LinkNode *head);//将用当前日期构造的一个新结点插入到第一个小于该结点日期的后面
void LinkFree(LinkNode **head);//释放链表

void Settings();//调整系统各项的选择

#endif
