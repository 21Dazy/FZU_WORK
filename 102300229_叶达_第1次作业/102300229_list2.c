#include "102300229_list.h"

int DisplayOn=0;//是否分显示,默认为0，即不分页
Date origin={1903,1,1};//计算相差天数的起点值
int NodeNum=0;//统计节点数
const int days[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int Row=30;//分页输出时一页的行数
int Col=6;//分页输出时一页的列数
char FileNameR[100]="LinkData.txt";//读取路径
char FileNameS[100]="LinkData.txt";//保存路径

void ShowCopyright(){
    printf("\n*******************************************************************************\n");
    printf("Copyright <c> 2024-2024 叶达<102300229>. ALL Rights Reserved\n");
};
void ShowTime(){
    time_t currentTime;
    struct tm *localTime;
    time(&currentTime);         // 获取当前时间
    localTime = localtime(&currentTime); // 转换为本地时间
    printf("当前日期和时间：%d-%02d-%02d %02d:%02d:%02d\n",
           localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday,
           localTime->tm_hour, localTime->tm_min, localTime->tm_sec);

};
void ShowMenu(){
	//需要修改菜单美观性
	printf("*******************************************************************************\n");
    printf("*\tC:创建一个存放日期的<无序>链表                                             \n");
    printf("*\tO:显示链表前几个节点的日期数据                                             \n");
    printf("*\tK:输出特定日期的数据                                                       \n");
	printf("*\tS:将整个链表的所有数据存入文件中                                           \n");
    printf("*\tR:从文件中读取链表                                                         \n");
    printf("*\tU:清除文件中的所有内容                                                     \n");
    printf("*\tX:分屏显示链表的<全部>内容                                         \n");
    printf("*\tN:显示不能构成合法日期的<所有>节点                                         \n");
    printf("*\tD:删除链表的第一个、最后一个、不能构成合法日期的节点                       \n");
    printf("*\tI: 插入结点<至链头、链尾、结点之前、结点之后>                              \n");
	printf("*\tT: 显示结点的日期对应的天数                                                \n");
	printf("*\tA:链表按日期从小到大排序                                                   \n");
	printf("*\tP:查找链表中“年月日”都是素数的结点                                        \n");
	printf("*\tF:<单向>链表翻转                                                           \n");
	printf("*\tE:释放链表                                                           \n");
	printf("*\tZ:设置                                                                     \n");
	printf("*\tQ:退出系统                                                                 \n");
    printf("*******************************************************************************\n");
    printf("你的选择是:<请输入对应字母(不区分大小写)并按下回车键位做出选择>\n");
};
LinkNode* SetLink(int n){
    LinkNode *head=(LinkNode*)malloc(sizeof(LinkNode));
    LinkNode *p=head;
    for(int i=1;i<=n;i++){
    	printf("\n输入第%d个节点的日期数据<输入格式为：年/月/日>\n",i);
        LinkNode *temp=(LinkNode*)malloc(sizeof(LinkNode));
        scanf("%d/%d/%d",&temp->val.year,&temp->val.month,&temp->val.day);
        getchar();
        temp->next=NULL;
        p->next=temp;
        p=temp;
    }
    return head;
};
LinkNode *RandomLink(int n){//随机创建一个具有n个节点的链表
	srand(time(NULL));//设置随机种子
    LinkNode *head=(LinkNode*)malloc(sizeof(LinkNode));
    LinkNode *p=head;
    for(int i=1;i<=n;i++){
        LinkNode *temp=(LinkNode*)malloc(sizeof(LinkNode));
        temp->val.year=rand()%103+1923;//1923-2025
        temp->val.month=rand()%12+1;//1-12
        temp->val.day=rand()%31+1;//1-28
        temp->next=NULL;
        p->next=temp;
        p=temp;
    }
    return head;
};
void ShowLink(LinkNode *head,int n){
    LinkNode *p=head->next;
    if(n==0){
    	printf("\n<按下回车键，开始输出整个链表>\n");
    	getchar();
		while(p!=NULL){
		    printf("%d年%d月%d日\n",p->val.year,p->val.month,p->val.day);
		    p=p->next;
		}	
		printf("已经显示链表所有的%d个节点",NodeNum);
	}
	else{
		int num=n;
	    while(p!=NULL && n--){
	        printf("%d年%d月%d日\n",p->val.year,p->val.month,p->val.day);
	        p=p->next;
	    }
	 	printf("已经显示链表前%d个节点<链表总结点数为%d>\n",num,NodeNum) ;  
	}
};
void ShowIllegal(LinkNode *head){
    LinkNode *p=head->next;
    int flag=0;
    while(p!=NULL){
        if(!isLegal(p->val)){
            printf("%d年%d月%d日\n",p->val.year,p->val.month,p->val.day);
            flag=1;
        }
        p=p->next;
    }
    if(!flag){
		printf("无非法日期节点\n");
    }
    else{
		printf("以上日期节点不合法\n");
	}
};
void ShowPrime(LinkNode *head){
    printf("\n以下节点的年月日都为素数：\n");
    LinkNode *p=head->next;
    while(p!=NULL){
        if(isPrime(p->val.year) && isPrime(p->val.month) && isPrime(p->val.day)){
            printf("%d年%d月%d日\n",p->val.year,p->val.month,p->val.day);
        }
        p=p->next;
    }
    
};
void SelectDate(LinkNode *head){
	printf("\n******************\n");
	printf("*\tY.特定年份\n");
	printf("*\tM.特定月份\n");
	printf("*\tD.特定日期\n");
	printf("*\tA.特定 年/月/日\n");
	printf("*\tZ.返回上级菜单\n");
	printf("*******************\n");
	char choice;
	scanf("%c",&choice);
	getchar();
	LinkNode *p=head->next;
	if(choice=='Y' || choice=='y'){
		int year=0;
		int flag=0;
		printf("\n请输入你需要的年份:\n");
		scanf("%d",&year);
        getchar();
		while(p){
			if(p->val.year==year){
				printf("%d年%d月%d日\n",p->val.year,p->val.month,p->val.day);
				flag=1;
			}
			p=p->next;
		}
		if(!flag)printf("链表中不存在该年份的节点");
	}
    else if(choice=='M' || choice=='m'){
        int month=0;
        int flag=0;
        printf("\n请输入你需要的月份:\n");
        scanf("%d",&month);
        getchar();
        while(p){
            if(p->val.month==month){
                printf("%d年%d月%d日\n",p->val.year,p->val.month,p->val.day);
                flag=1;
            }
            p=p->next;
        }
		if(!flag)printf("链表中不存在该月份的节点");
    }
    else if(choice=='D' || choice=='d'){
        int day=0;
        int flag=0;//判断有没有该日期的数据
        printf("\n请输入你需要的日期:\n");
        scanf("%d",&day);
        getchar();
        while(p){
            if(p->val.day==day){
                printf("%d年%d月%d日\n",p->val.year,p->val.month,p->val.day);
                flag=1;
            }
            p=p->next;
        }
        if(!flag)printf("链表中不存在该日期的节点");
    }
    else if(choice=='A' || choice=='a'){
	    Date date={0,0,0};    
	    int flag=0;//判断有没有该日期的数据
	    printf("\n请输入 你需要的 年/月/日:<按照 年/月/日 格式输入>\n");
	    scanf("%d/%d/%d",&(date.year),&(date.month),&(date.day));
	    getchar();
	    while(p){
	        if(p->val.day==date.day && p->val.month==date.month && p->val.year==date.year && !flag){//只用找到输出一次就行
	            printf("存在符合要求的节点\n");
	            flag=1;
	        }
	    	p=p->next;
	    }
	    if(!flag)printf("链表中不存在该年月日的节点");
	}
    else if(choice=='Z' || choice=='z'){
		printf("\n为你返回上级菜单\n");
	}
	else{
        printf("输入错误!,回到主菜单\n");
    }
};
void LinkReverse(LinkNode *head){//反转列表
    LinkNode *p=head->next;
    LinkNode *q=p->next;
    p->next=NULL;
    while(q!=NULL){
        LinkNode *temp=q->next;
        q->next=p;
        p=q;
        q=temp;
    }
    head->next=p;
    return;
};
void LinkDelete(LinkNode *head){//删除日期非法的节点
    int sum=0;//统计删除数量
	LinkNode *p=head->next;
    LinkNode *q=p->next;
    printf("删除的非法节点有：\n");
    if(!isLegal(p->val)){
        printf("%d年%d月%d日\n",p->val.year,p->val.month,p->val.day);
    	sum++;
        head->next=q;
        free(p);
        p=q;
        q=p->next;
    }
    while(q!=NULL){
        if(!isLegal(q->val)){
        	printf("%d年%d月%d日\n",q->val.year,q->val.month,q->val.day);
        	sum++;
            p->next=q->next;
            free(q);
            q=p->next;
        }
        else{
			p=q;
			q=q->next;
		}
    }
    NodeNum-=sum;
    printf("\n删除%d个非法节点,链表当前有%d个节点\n",sum,NodeNum);
};
void LinkSort(LinkNode *head){//将链表根据节点日期先后进行排序，
    if (head == NULL || head->next == NULL) {
        return;
    }
    int swapped=0;
    LinkNode* p;
    LinkNode* q = NULL;
    do {
        swapped = 0;
        p = head;

        while (p->next != q) {
            if (!DateCmp(p->val, p->next->val)){//日期后的往后放
                Date temp = p->val;
                p->val = p->next->val;
                p->next->val = temp;
                swapped = 1;
            }
            p = p->next;
        }
        q = p;
    } while (swapped);
};
void FileClear(char *fileName){
    FILE *fp=fopen(fileName,"w");
    fclose(fp);
    fp=fopen(fileName,"w");
    fclose(fp);
    printf("文件已清空\n");
    return ;
};
LinkNode* Read_to_Link(char *fileName){
	NodeNum=0;//以覆盖的方式读入链表
    FILE *fp=fopen(fileName,"r");
    if(fp){
        printf("打开文件成功\n");
        LinkNode *head=(LinkNode*)malloc(sizeof(LinkNode));
        head->next=(LinkNode*)malloc(sizeof(LinkNode));
        LinkNode *p=head->next;
        //LinkNode *q=(LinkNode*)malloc(sizeof(LinkNode));
        while(!feof(fp)){
            fscanf(fp,"%d年%d月%d日\n",&(p->val.year),&(p->val.month),&(p->val.day));
            NodeNum++;
            if(!feof(fp)){
            	LinkNode *q=(LinkNode*)malloc(sizeof(LinkNode));
            	q->next=NULL;
            	p->next=q;
            	p=p->next;
            }
            else{
            	break;
			}
        }
        fclose(fp);
        return head;
    }
    else{
        printf("打开文件失败\n");
        return NULL;
        
    }
};
void Save_to_File(LinkNode *head,char* filename){
    FILE* fp=fopen(filename,"w+");
    LinkNode *p=head->next;
    while(p!=NULL){
        fprintf(fp,"%d年%d月%d日\n",p->val.year,p->val.month,p->val.day);
        p=p->next;
    }
    fclose(fp);
};
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
int Days_in_Month(int year, int month) {
    if (month == 2) {
        return isLeap(year) ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        return 31;
    }
};
int isPrime(int n){
    int i;
    if(n<2) return 0;
    for(i=2;i*i<=n;i++){
        if(n%i==0) return 0;
    }
    return 1;
};
int DateCmp(Date d1,Date d2){//比较日期先后
    if(d1.year<d2.year){
        return 1;
    }
    else if(d1.year==d2.year){
        if(d1.month<d2.month){
            return 1;
        }
        else if(d1.month==d2.month){
            if(d1.day<d2.day){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
        
    }
    else{
        return 0;
    }
};
int CalDays(Date date){//算日期到元年的天数
	 int days = 0;
	    for (int y = 1; y < date.year; ++y) {
	        days += isLeap(y) ? 366 : 365;
	    }
	    for (int m = 1; m < date.month; ++m) {
	        days += Days_in_Month(date.year, m);
	    }
	    days += date.day;
	    return days;
};
void DaysDiff(LinkNode *head){
	LinkNode *p=head->next;
	int n=0;
	printf("你需要链表中前几个日期的数据?<请输入一个正整数>\n");
	scanf("%d",&n);
	getchar();
	printf("\n以下为前%d个节点的日期距离%d年%d月%d日的天数:\n",n,origin.year,origin.month,origin.day);
	 printf("\n*******************************************************************************\n");
	while(p!=NULL && n--){
		printf("\t%d年%d月%d日距离%d年%d月%d日的天数为%d\n",
        p->val.year,p->val.month,p->val.day,origin.year,origin.month,origin.day,CalDays(p->val)-CalDays(origin));
		p=p->next;
	
	
		//TODO
	}
	printf("\n*******************************************************************************\n");
	printf("输出完毕\n");
	
};
void NodeInsert(LinkNode *head){
    printf("正在进行插入节点操作");
    char choice2='0';//二级菜单选择项
    int flag=1;//用于判断二级菜单的终结
    while(1){
        printf("是否继续插入节点?<Y/N>\n");
        scanf("%c",&choice2);
        getchar();
        if(choice2=='Y'||choice2=='y'){
            char choice3='0';//三级菜单选择项
            while(flag){
                printf("\n*******************************************************************************\n");
	            printf("*\t1.插入至头部\n");
	            printf("*\t2.插入至尾部\n");
	            printf("*\t3.插入至第一个日期比该节点小的节点的下一位\n");
	            printf("*\t4.插入至第一个日期比该节点大的前一位\n");
                printf("*\t5.返回上级菜单\n");
	            printf("*******************************************************************************\n");
	            printf("请输入你的选择:");
	            scanf("%c",&choice3);
	            getchar();
	            switch(choice3){
	                case '1':
	                    InsertHead(head);
	                    break;
	                case '2':
	                    InsertTail(head);
	                    break;
	                case '3':
	                    InsertBefore(head);
	                    break;
	                case '4':
	                    InsertAfter(head);
	                    break;
	                case '5':
	                	flag=0;
	                    break;
	                default:
	                    printf("输入错误，请重新输入!\n");
	            }
            }
        }
        else if(choice2=='N'||choice2=='n'){
            return;
        }
    }
};
void InsertHead(LinkNode *head){
    LinkNode *new=(LinkNode *)malloc(sizeof(LinkNode));
    printf("请输入日期:<输入格式为：年/月/日>\n");
    scanf("%d/%d/%d",&(new->val.year),&(new->val.month),&(new->val.day));
    getchar();
    new->next=head->next;
    head->next=new;
    printf("插入成功!\n");
    NodeNum++;
};
void InsertTail(LinkNode *head){
    LinkNode *new=(LinkNode *)malloc(sizeof(LinkNode));
    printf("请输入日期:<输入格式为：年/月/日>\n");
    scanf("%d/%d/%d",&(new->val.year),&(new->val.month),&(new->val.day));
    getchar();
    new->next=NULL;
    LinkNode *p=head->next;
    while(p->next!=NULL){
        p=p->next;
    }
    p->next=new;
    printf("插入成功!\n");
    NodeNum++;
};
void InsertBefore(LinkNode *head){
    LinkNode *new=(LinkNode *)malloc(sizeof(LinkNode));
    printf("请输入日期:<输入格式为：年/月/日>\n");
    scanf("%d/%d/%d",&(new->val.year),&(new->val.month),&(new->val.day));
    getchar();
    LinkNode *p=head->next;
    LinkNode *q=p->next;
    if(DateCmp(new->val,p->val)==1){
        new->next=p;
        head->next=new;
        printf("插入成功!\n");
        NodeNum++;
        return;
    }
    while(p!=NULL){
        if(DateCmp(new->val,p->val)==1){
            new->next=q;
            p->next=new;
            printf("插入成功!\n");
            NodeNum++;
            return;
        }
        p=q;
        q=q->next;
    }
    printf("插入失败!\n");
    return;
};
void InsertAfter(LinkNode *head){
    LinkNode *new=(LinkNode *)malloc(sizeof(LinkNode));
    printf("请输入日期:<输入格式为：年/月/日>\n");
    scanf("%d/%d/%d",&(new->val.year),&(new->val.month),&(new->val.day));
    getchar();
    LinkNode *p=head->next;
    LinkNode *q=p->next;
    while(p!=NULL){
        if(DateCmp(new->val,p->val)==0){
            new->next=q;
            p->next=new;
            printf("插入成功!\n");
            NodeNum++;
            return;
        }
        p=q;
        q=q->next;
    }
    printf("插入失败!\n");
    return;
};
void ShowByPage(LinkNode *head){//一页一页的显示链表节点数据，每显示一页刷新一次输出缓冲区
	LinkNode *p=head->next;
	system("cls");
    while(1){
        for(int i=0;i<Row;i++){
            for(int j=0;j<Col;j++){
                if(p==NULL){
                    printf("\n输出完毕,按任意键返回主菜单\n");
                    getchar();
                    return;
                }
                printf("%d年/%d月/%d日  ",p->val.year,p->val.month,p->val.day);
                p=p->next;
            }
            printf("\n");
        }
        printf("按任意键继续显示下一页");
        getchar();
        system("cls");
    }
};
void LinkFree(LinkNode **head){
	char choice2=0;//二级菜单选项
    while(1){
        printf("是否释放链表内存(Y/N):");
        scanf("%c",&choice2);
        getchar();
        if(choice2=='Y'||choice2=='y'){
            LinkNode *p=(*head)->next;
            LinkNode *q=p->next;
            while(p!=NULL){
                free(p);
                p=q;
                if(q!=NULL){
                    q=q->next;
                }
            }
            (*head)->next=NULL;
            free(*head);
            *head=NULL;
            printf("\n链表释放成功!\n");
            return;
        }
        else if(choice2=='N'||choice2=='n'){
            printf("不释放!\n");
            return;
        }
        else{
            printf("输入错误,请按要求格式输入!\n");
        }   
    }  
};
void Settings(){//设置系统的分页显示，分页显示的行数和列数
    int choice2=0;//二级菜单选项
    char choice3=0;
    system("cls");
    printf("\n******************************\n你已进入该系统设置界面\n******************************\n");
    while(1){
    	system("cls");
    	printf("******************************\n系统设置界面\n******************************\n");
        printf("\n******************\n");
	    printf("*\t1.全局分屏显示设置\n");
	    printf("*\t2.修改天数计算的起点\n");
	    printf("*\t3.修改分屏显示情况下一页所能展示的节点列数和行数\n");
	    printf("*\t4.修改链表存放的路径\n");
	    printf("*\t5.修改要读取文件的路径\n");
        printf("*\t6.返回上级菜单\n");
	    printf("*******************\n");
        printf("请输入你的选择(1-6):\n");
        scanf("%d",&choice2);
        getchar();
        switch(choice2){
            case 1:
                printf("\n全局分屏显示开启还是关闭<Y/N>  (当前为%s)\n",DisplayOn?"开启":"关闭");
                scanf("%c",&choice3);
                getchar();
                if(choice3=='Y'||choice3=='y'){
                    DisplayOn=1;
                    printf("\n全局分屏显示已开启!\n");
                }
                else if(choice3=='N'||choice3=='n'){
                    DisplayOn=0;
                    printf("\n全局分屏显示已关闭!\n");
                }
                else{
                    printf("\n输入错误,请按要求格式输入!\n");
                }
                break;
            case 2:
                printf("\n请输入新的起点日期(当前为%d年%d月%d日):\n",origin.year,origin.month,origin.day);
                printf("年:");
                scanf("%d",&origin.year);
                getchar();
                printf("月:");
                scanf("%d",&origin.month);
                getchar();
                printf("日:");
                scanf("%d",&origin.day);
                getchar();
                printf("\n新的起点日期为%d年%d月%d日!\n",origin.year,origin.month,origin.day);
                break;
            case 3:
                printf("\n请输入一次分屏显示日期中你需要的行数和列数:(当前呈%d行%d列显示)",Row,Col);
                printf("\n行数:");
                scanf("%d",&Row);
                getchar();
                printf("列数:");
                scanf("%d",&Col);
                getchar();
                printf("\n新的行数和列数为%d行%d列!\n",Row,Col);
                break;
            case 4:
            	printf("\n当前路径为：%s\n",FileNameS);
            	printf("你需要将你的链表保存路径更新为:<在下方输入文件名和后缀名>\n");
            	scanf("%s",FileNameS);
            	getchar();
            	printf("路径更新完毕");
            	break;
            case 5:
            	printf("\n当前路径为：%s\n",FileNameR);
            	printf("你需要将你要读取的文件的路径更新为:<在下方输入文件名和后缀名>\n");
            	scanf("%s",FileNameR);
            	getchar();
            	printf("路径更新完毕");
            	break;
            case 6:
                printf("\n即将返回上级菜单......\n");
                return;
            default:
                printf("\n输入错误,请按要求格式输入!\n");
        }
    }
};
