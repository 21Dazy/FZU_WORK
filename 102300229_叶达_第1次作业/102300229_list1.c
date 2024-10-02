//Copyright <c> 2024-2024 叶达<102300229>. ALL Rights Reserved
#include"102300229_list.h"
#include"102300229_list2.c"
//如果ide无法正常建立编译链接，在该文件目录的powershell终端输入gcc -o main 102300229_list1.c 102300229_list2.c 102300229_list.h命令手动建立编译链接

int main(){
    //SetConsoleOutputCP(65001);//看ide情况，如果执行程序后终端出现乱码（中文不能正常显示），则取消注释
    LinkNode *LinkHead=NULL;//链表头
    char choice;
	    while(1){//每一次循环为一次主菜单选择，只在选择退出时结束
	        if(DisplayOn){
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
	        scanf("%c",&choice);
	        getchar();
	        if(islower(choice)){
				choice=(char)(choice-32);
			}
	        switch(choice){
	            case 'C':
	            	printf("\n*******************************************************************************\n");
	                printf("*\tA:自定义生成链表\n");
	                printf("*\tB:随机生成链表\n");
	                printf("*******************************************************************************\n");
	                printf("请选择你的生成方式<输入A/B,不区分大小写>\n");
	                while (1){
	                    char Cchoice=0;
	                    scanf("%c",&Cchoice);
	                    if(Cchoice=='A'||Cchoice=='a'){
	                        printf("请输入链表的节点数:\n");
	                        int n;
	                        scanf("%d",&n);
	                        getchar();
	                        NodeNum=n;
	                        printf("正在生成链表......\n");
	                        LinkHead=SetLink(n);
	                        printf("共创建了%d个日期节点,1923<=年<=2025,1<=月<=12,1<=日<=31\n",n);
	                        break;
	                    }
	                    else if(Cchoice=='B'||Cchoice=='b'){
	                    	printf("请输入链表的节点数:\n");
	                    	int n;
							scanf("%d",&n);
							getchar();
							NodeNum=n;
	                        printf("正在生成链表......\n");
	                        LinkHead=RandomLink(n);
	                        printf("共创建了%d个日期节点,1923<=年<=2025,1<=月<=12,1<=日<=31\n",n);
	                        NodeNum=n;
	                        break;
	                    }
	                    printf("输入错误，请重新输入(输入A/B)");
	                }    //
	                printf("\n<按下回车键，返回主菜单>\n");
					getchar();
	                break;
	            case 'O':
	                if(!LinkHead){
	                    printf("链表为空，请先创建链表\n");
	                }
	                else{
	                    printf("你要显示前几个节点<输入0则全部输出>\n");
	                    int n;
	                    scanf("%d",&n);
	                    getchar();
	                    ShowLink(LinkHead,n);
	                }
	                printf("\n<按下回车键，返回主菜单>\n");
					getchar();
	                break;
	            case 'K':
	            	if(!LinkHead){
						printf("链表为空，请先创建链表\n");
					}
					else{
						SelectDate(LinkHead);
					}
					printf("\n<按下回车键，返回主菜单>\n");
					getchar();
	                break;
	            case 'S':
	            	if(!LinkHead){
					    printf("链表为空，请先创建链表\n");                
					}
					else{
						Save_to_File(LinkHead,FileNameS);
						printf("链表存入成功");
					}
					printf("\n<按下回车键，返回主菜单>\n");
					getchar();
	                break;
	            case 'R':
	            	if(LinkHead){
						printf("\n即将覆盖当前链表\n");//!!!后续增加一个选择功能，选择是否覆盖旧链表
						LinkHead=Read_to_Link(FileNameR);
					    printf("文件读入成功");
					}
	            	else{
	            		printf("\n已通过文件创建链表\n");
						LinkHead=Read_to_Link(FileNameR);
						printf("文件读入成功");
	            	}
	            	printf("\n<按下回车键，返回主菜单>\n");
					getchar();
					break;
	            case 'U':
	            	FileClear(FileNameS);
	            	printf("\n<按下回车键，返回主菜单>\n");
					getchar();
	                break;
	            case 'X':
	            	if(!LinkHead){
						printf("链表为空，请先创建链表\n");
	                }
	            	else{
	            	    ShowByPage(LinkHead);
	            	    system("cls");
	            	}
	                break;
	            case 'N':
	                if(!LinkHead){
	                    printf("链表为空，请先创建链表\n");
	                }
	                else{
	            	    ShowIllegal(LinkHead);
	                }
	                printf("\n<按下回车键，返回主菜单>\n");
					getchar();
	                break;
	            case 'D':
	                if(!LinkHead){
	                    printf("链表为空，请先创建链表\n");
	                }
	                else{
	                    LinkDelete(LinkHead);
	                }
	            	printf("\n<按下回车键，返回主菜单>\n");
					getchar();
	                break;
	            case 'I':
	            	if(!LinkHead){
					    printf("链表为空，请先创建链表\n");
					}
	                else{
	                    NodeInsert(LinkHead);
	                }
	                break;
	            case 'T':
	            	if(!LinkHead){
					    printf("链表为空，请先创建链表\n");
					}
					else{
					    DaysDiff(LinkHead);
					}
	            	printf("\n<按下回车键，返回主菜单>\n");
	            	getchar();
	                break;
	            case 'A':
	            	if(!LinkHead){
	                    printf("链表为空，请先创建链表\n");
	                }
	                else{
	                    printf("\n正在将链表按日期先后排序\n");
	                    printf("链表正在排序......");
	                    LinkSort(LinkHead);
	                    printf("排序完成\n");
	                }
	                printf("\n<按下回车键，返回主菜单>\n");
					getchar();
	                break;
	            case 'P':
	                if(!LinkHead){
	                    printf("链表为空，请先创建链表\n");
	                }
					else{
	                    ShowPrime(LinkHead);
	                }
	                printf("\n<按下回车键，返回主菜单>\n");
					getchar();
	                break;
	            case 'F':
	                if(!LinkHead){
	                    printf("链表为空，请先创建链表\n");
	                }
	                else{
	                    LinkReverse(LinkHead);
	                    printf("链表已翻转");
	                }
	                printf("\n<按下回车键，返回主菜单>\n");
					getchar();
	                break;
	            case 'E':
	            	if(!LinkHead){
					    printf("链表为空，请先创建链表\n");
					}
					else{
						LinkFree(&LinkHead);
					}
					printf("\n<按下回车键，返回主菜单>\n");
					getchar();
					break;
	            case 'Z':
	            	Settings();
	                break;
	            case 'Q':
	                printf("程序已退出\n");
	                exit(0);
	                break;
	            default:
	                printf("输入错误,请按要求输入\n");
	                printf("<按下回车键，返回主菜单>\n");
	                getchar();
	                system("cls"); 
	        }
	    }    
}
