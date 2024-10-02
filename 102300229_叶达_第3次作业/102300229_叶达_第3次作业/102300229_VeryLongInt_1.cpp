/***************************************************************
【文件名】          102300229_VeryLongInt_1.cpp
【功能模块和目的】  测试巨型整数类的计算和各功能
【开发环境】         Visual Studio Code / MinGW gcc 8.1.0 / c++17
【开发者】     叶达 
****************************************************************/
#include "102300229_VeryLongInt.h"
#include "102300229_VeryLongInt_2.cpp"

int main(){
    //SetConsoleOutputCP(65001);
    while(true){
        char choice1;
        while(true){
            ShowHead();
            choice1=getch();
            if(isalpha(choice1) && (cout<<(choice1=toupper(choice1))<<endl)){//判断输入是否为字母
                switch(choice1){
                    case 'A':{//测试通过long long类型构造VeryLongInt对象
                        longlong_constructor_test();
                        break;
                    }
                    case 'B':{//测试通过string类型构造VeryLongInt对象
                        string_constructor_test();
                        break;
                    }
                    case 'C':{
                        cout<<"<按下任意键随机构造1个2000位负数巨型整数>"<<endl;
                        getch();
                        VeryLongInt num1=randVeryLongInt(2000,true);
                        cout<<"随机构造的负数巨型整数为: "<<num1<<endl;
                        cout<<"num1.length() ->"<<num1.getLength()<<endl;
                        cout<<"num1.isNegative() ->"<< (num1.getIsNegative())<<endl;
                        cout<<"<按下任意键随机构造1个2000位正数巨型整数>"<<endl;
                        getch();
                        VeryLongInt num2=randVeryLongInt(2000,false);
                        cout<<"随机构造的正数巨型整数为: "<<num2<<endl;
                        cout<<"num2.length() ->"<<num2.getLength()<<endl;
                        cout<<"num2.isNegative() ->"<< (num2.getIsNegative())<<endl;


                        two_thousand_constructor_test();
                        system("cls");
                        break;
                    }
                    case 'D':{
                        invalid_constructor_test();
                        break;
                    }
                    case 'E':{
                        cout<<"<以设定的身份证号码和学号构造两个巨型整数对象进行测试>"<<endl;
                        VeryLongInt id_num("332522200408264393");
                        VeryLongInt stuid_num("102300229");
                        VeryLongInt temp_id=id_num;
                        VeryLongInt temp_stuid=stuid_num;

                        cout<<"id_num="<<id_num<<endl;
                        cout<<"stuid_num="<<stuid_num<<endl;

                        cout<<"id_num.length() ->"<<id_num.getLength()<<endl;
                        cout<<"stuid_num.length() ->"<<stuid_num.getLength()<<endl;

                        cout<<"id_num.isNegative() ->"<< (id_num.getIsNegative())<<endl;
                        cout<<"stuid_num.isNegative() ->"<< (stuid_num.getIsNegative())<<endl;

                        cout<<"id_num+stuid_num="<<id_num+stuid_num<<endl;
                        cout<<"id_num-stuid_num="<<id_num-stuid_num<<endl;
                        cout<<"id_num*stuid_num="<<id_num*stuid_num<<endl;
                        cout<<"id_num/stuid_num="<<id_num/stuid_num<<endl;
                        cout<<"id_num%stuid_num="<<id_num%stuid_num<<endl;
                        cout<<"id_num < stuid_num ->"<< (id_num < stuid_num)<<endl;
                        cout<<"id_num > stuid_num ->"<< (id_num > stuid_num)<<endl;
                        cout<<"id_num == stuid_num ->"<< (id_num == stuid_num)<<endl;
                        cout<<"id_num!= stuid_num ->"<< (id_num!= stuid_num)<<endl;
                        cout<<"id_num <= stuid_num ->"<< (id_num <= stuid_num)<<endl;
                        cout<<"id_num >= stuid_num ->"<< (id_num >= stuid_num)<<endl;

                        cout<<"执行 id_num+=stuid_num前"<<endl;
                        cout<<"id_num="<<id_num<<endl;
                        cout<<"stuid_num="<<stuid_num<<endl;
                        cout<<"id_num+=stuid_num->"<< (id_num+=stuid_num) <<endl;
                        cout<<"执行 id_num+=stuid_num后"<<endl;
                        cout<<"id_num="<<id_num<<endl;
                        cout<<"stuid_num="<<stuid_num<<endl;
                        id_num=temp_id;
                        stuid_num=temp_stuid;

                        cout<<"执行 id_num-=stuid_num前"<<endl;
                        cout<<"id_num="<<id_num<<endl;
                        cout<<"stuid_num="<<stuid_num<<endl;
                        cout<<"id_num-=stuid_num->"<< (id_num-=stuid_num) <<endl;
                        cout<<"执行 id_num-=stuid_num后"<<endl;
                        cout<<"id_num="<<id_num<<endl;
                        cout<<"stuid_num="<<stuid_num<<endl;
                        id_num=temp_id;
                        stuid_num=temp_stuid;

                        cout<<"执行 id_num*=stuid_num前"<<endl;
                        cout<<"id_num="<<id_num<<endl;
                        cout<<"stuid_num="<<stuid_num<<endl;
                        cout<<"id_num*=stuid_num->"<< (id_num*=stuid_num) <<endl;
                        cout<<"执行 id_num*=stuid_num后"<<endl;
                        cout<<"id_num="<<id_num<<endl;
                        cout<<"stuid_num="<<stuid_num<<endl;
                        id_num=temp_id;
                        stuid_num=temp_stuid;

                        cout<<"执行 id_num/=stuid_num前"<<endl;
                        cout<<"id_num="<<id_num<<endl;
                        cout<<"stuid_num="<<stuid_num<<endl;
                        cout<<"id_num/=stuid_num->"<< (id_num/=stuid_num) <<endl;
                        cout<<"执行 id_num/=stuid_num后"<<endl;
                        cout<<"id_num="<<id_num<<endl;
                        cout<<"stuid_num="<<stuid_num<<endl;
                        id_num=temp_id;
                        stuid_num=temp_stuid;

                        cout<<"执行 id_num%=stuid_num前"<<endl;
                        cout<<"id_num="<<id_num<<endl;
                        cout<<"stuid_num="<<stuid_num<<endl;
                        cout<<"id_num%=stuid_num->"<< (id_num%=stuid_num) <<endl;
                        cout<<"执行 id_num%=stuid_num后"<<endl;
                        cout<<"id_num="<<id_num<<endl;
                        cout<<"stuid_num="<<stuid_num<<endl;
                        id_num=temp_id;
                        stuid_num=temp_stuid;
                        
                        cout<<"<按下任意键进行更加复杂的测试>"<<endl;
                        stuid_id_constructor_test(id_num,stuid_num);
                        stuid_id_operation_test(id_num,stuid_num);
                        break;
                    }
                    case 'F':{
                        bool quit=false;
                        while(!quit){          
                            cout<<"<以预设的两个93位巨型整数进行测试>"<<endl;
                            VeryLongInt num1("723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848");
                            VeryLongInt num2("689556894861559021560958760392180228230999829389355664204870497865175476745363547571229155341");

                            cout<<"num1="<<num1<<endl;
                            cout<<"num2="<<num2<<endl;
                            cout<<"num1.length() ->"<<num1.getLength()<<endl;
                            cout<<"num2.length() ->"<<num2.getLength()<<endl;
                            cout<<"num1.isNegative() ->"<< (num1.getIsNegative())<<endl;
                            cout<<"num2.isNegative() ->"<< (num2.getIsNegative())<<endl;

                            cout<<"num1+num2="<<num1+num2<<endl;
                            cout<<"num1-num2="<<num1-num2<<endl;
                            cout<<"num1*num2="<<num1*num2<<endl;
                            cout<<"num1/num2="<<num1/num2<<endl;
                            cout<<"num1%num2="<<num1%num2<<endl;
                            cout<<"num1 < num2 ->"<< (num1 < num2)<<endl;
                            cout<<"num1 > num2 ->"<< (num1 > num2)<<endl;
                            cout<<"num1 == num2 ->"<< (num1 == num2)<<endl;
                            cout<<"num1!= num2 ->"<< (num1 != num2)<<endl;
                            cout<<"num1 <= num2 ->"<< (num1 <= num2)<<endl;
                            cout<<"num1 >= num2 ->"<< (num1 >= num2)<<endl;

                            cout<<"执行 num1+=num2前"<<endl;
                            cout<<"num1="<<num1<<endl;
                            cout<<"num2="<<num2<<endl;
                            cout<<"num1+=num2->"<< (num1+=num2) <<endl;
                            cout<<"执行 num1+=num2后"<<endl;
                            cout<<"num1="<<num1<<endl;
                            cout<<"num2="<<num2<<endl;
                            num1=VeryLongInt("723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848");
                            num2=VeryLongInt("689556894861559021560958760392180228230999829389355664204870497865175476745363547571229155341");

                            cout<<"执行 num1-=num2前"<<endl;
                            cout<<"num1="<<num1<<endl;
                            cout<<"num2="<<num2<<endl;
                            cout<<"num1-=num2->"<< (num1-=num2) <<endl;
                            cout<<"执行 num1-=num2后"<<endl;
                            cout<<"num1="<<num1<<endl;
                            cout<<"num2="<<num2<<endl;
                            num1=VeryLongInt("723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848");
                            num2=VeryLongInt("689556894861559021560958760392180228230999829389355664204870497865175476745363547571229155341");

                            cout<<"执行 num1*=num2前"<<endl;
                            cout<<"num1="<<num1<<endl;
                            cout<<"num2="<<num2<<endl;
                            cout<<"num1*=num2->"<< (num1*=num2) <<endl;
                            cout<<"执行 num1*=num2后"<<endl;
                            cout<<"num1="<<num1<<endl;
                            cout<<"num2="<<num2<<endl;
                            num1=VeryLongInt("723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848");

                            cout<<"执行 num1/=num2前"<<endl;
                            cout<<"num1="<<num1<<endl;
                            cout<<"num2="<<num2<<endl;
                            cout<<"num1/=num2->"<< (num1/=num2) <<endl;
                            cout<<"执行 num1/=num2后"<<endl;
                            cout<<"num1="<<num1<<endl;
                            cout<<"num2="<<num2<<endl;
                            num1=VeryLongInt("723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848");
                            num2=VeryLongInt("689556894861559021560958760392180228230999829389355664204870497865175476745363547571229155341");

                            cout<<"执行 num1%=num2前"<<endl;
                            cout<<"num1="<<num1<<endl;
                            cout<<"num2="<<num2<<endl;
                            cout<<"num1%=num2->"<< (num1%=num2) <<endl;
                            cout<<"执行 num1%=num2后"<<endl;
                            cout<<"num1="<<num1<<endl;
                            cout<<"num2="<<num2<<endl;
                            num1=VeryLongInt("723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848");
                            num2=VeryLongInt("689556894861559021560958760392180228230999829389355664204870497865175476745363547571229155341");

                            cout<<"<按下任意键进行更加复杂的测试>"<<endl;
                            getch();

                            cout<<"<按下任意键随机构造两个93位巨型整数>"<<endl;
                            getch();
    
                            num1=randVeryLongInt(93);
                           
                            num2=randVeryLongInt(93);
                            test_verylongint_operation(num1,num2,false);
                            cout<<"<是否继续随机构造并测试？(Y/N)>"<<endl;
                            char choice2;
                            while(true){
                                choice2=toupper(getch());
                                if(choice2=='Y'){
                                    break;
                                }
                                else if(choice2=='N'){
                                    quit=true;
                                    break;
                                }
                                else{
                                    cout<<"请输入有效的选项!"<<endl;
                                }
                            }
                        }
                        cout<<"<按下任意键进入四则运算正确性测试界面>"<<endl;
                        getch();
                        correctness_test();
                        system("cls");
                        break;
                    }
                    case 'G':{
                        VeryLongInt num1_base8,num2_base16,num3_base10;
                        cout<<"<测试正确的8进制、10进制、16进制字符串构造>"<<endl;
                    
                        num1_base8=VeryLongInt("01234567023123122455467623");
                        num2_base16=VeryLongInt("0x123456789ABCDEF232Ef");
                        num3_base10=VeryLongInt("12345678901234567890");
                        
                        cout<<"执行 num1_base8=VeryLongInt(\"01234567023123122455467623\")"<<endl;
                        cout<<"执行 num2_base16=VeryLongInt(\"0x123456789ABCDEF232Ef\")"<<endl;
                        cout<<"执行 num3_base10=VeryLongInt(\"1234567890\")"<<endl;

                        cout<<"num1_base8="<<num1_base8<<endl;
                        cout<<"num1_base8.Oct() ->"<<num1_base8.Oct()<<endl;
                        cout<<"num2_base16="<<num2_base16<<endl;
                        cout<<"num2_base16.Hex() ->"<<num2_base16.Hex()<<endl;
                        cout<<"num3_base10="<<num3_base10<<endl;
                        cout<<"num3.Hex() ->"<<num3_base10.Hex()<<endl;
                        cout<<"num3.Oct() ->"<<num3_base10.Oct()<<endl;

                        num1_base8=VeryLongInt("+01234567");
                        num2_base16=VeryLongInt("-0X123456789ABCDEF");

                        cout<<"执行 num1_base8=VeryLongInt(\"+01234567\")"<<endl;
                        cout<<"执行 num2_base16=VeryLongInt(\"-0X123456789ABCDEF\")"<<endl;
                        
                        cout<<"num1_base8="<<num1_base8<<endl;
                        cout<<"num1_base8.Oct() ->"<<num1_base8.Oct()<<endl;
                        cout<<"num2_base16="<<num2_base16<<endl;
                        cout<<"num2_base16.Hex() ->"<<num2_base16.Hex()<<endl;

                        cout<<"<测试随机构造构造93位巨型整数进行进制转化>"<<endl;
                        VeryLongInt num1=randVeryLongInt(93);
                        cout<<"执行 num1=randVeryLongInt(93)"<<endl;
                        cout<<"num1="<<num1<<endl;
                        auto start=chrono::high_resolution_clock::now();
                        cout<<"num1.Oct() ->"<<num1.Oct()<<endl;
                        auto end=chrono::high_resolution_clock::now();
                        auto duration=chrono::duration_cast<chrono::microseconds>(end - start);
                        cout<<"num1.Oct() 耗时:"<<duration.count()/1000000.0<<"s"<<endl;
                        start=chrono::high_resolution_clock::now();
                        cout<<"num1.Hex() ->"<<num1.Hex()<<endl;
                        end=chrono::high_resolution_clock::now();
                        duration=chrono::duration_cast<chrono::microseconds>(end - start);
                        cout<<"num1.Hex() 耗时:"<<duration.count()/1000000.0<<"s"<<endl;

                        cout<<"<测试随机构造构造1000位巨型整数进行进制转化>"<<endl;
                        num1=randVeryLongInt(1000);
                        cout<<"执行 num1=randVeryLongInt(1000)"<<endl;
                        cout<<"num1="<<num1<<endl;
                        start=chrono::high_resolution_clock::now();
                        cout<<"num1.Oct() ->"<<num1.Oct()<<endl;
                        end=chrono::high_resolution_clock::now();
                        duration=chrono::duration_cast<chrono::microseconds>(end - start);
                        cout<<"num1.Oct() 耗时:"<<duration.count()/1000000.0<<"s"<<endl;
                        start=chrono::high_resolution_clock::now();
                        cout<<"num1.Hex() ->"<<num1.Hex()<<endl;
                        end=chrono::high_resolution_clock::now();
                        duration=chrono::duration_cast<chrono::microseconds>(end - start);
                        cout<<"num1.Hex() 耗时:"<<duration.count()/1000000.0<<"s"<<endl;

                        cout<<"<测试错误的8进制字符串构造>"<<endl;
                        try{
                            cout<<"执行 num1_base8=VeryLongInt(\"0123456702312312245546762318\")"<<endl;
                            num1_base8=VeryLongInt("0123456702312312245546762318");

                        }
                        catch(Invalid_VeryLongInt &ex){
                            cout<<"错误原因:8进制字中出现非法数字"<<endl;
                            cout<<"异常值: "<<ex.get_error_str_num()<<endl;
                        }

                        try{
                            cout<<"执行 num1_base8=VeryLongInt(\"-0123456702312312245546762a\")"<<endl;
                            num1_base8=VeryLongInt("-0123456702312312245546762a");
                        }
                        catch(Invalid_VeryLongInt &ex){
                            cout<<"错误原因:8进制字中出现非法字符"<<endl;
                            cout<<"异常值: "<<ex.get_error_str_num()<<endl;
                        }

                        cout<<"<测试错误的16进制字符串构造>"<<endl;
                        try{
                            cout<<"执行 num2_base16=VeryLongInt(\"0x123456789ABCDEF232Efg\")"<<endl;
                            num2_base16=VeryLongInt("0x123456789ABCDEF232Efg");
                        }
                        catch(Invalid_VeryLongInt &ex){
                            cout<<"错误原因:16进制字中出现非法数字"<<endl;
                            cout<<"异常值: "<<ex.get_error_str_num()<<endl;
                        }

                        try{
                            cout<<"执行 num2_base16=VeryLongInt(\"-0xz23456789ABCDEF232Efg\")"<<endl;
                            num2_base16=VeryLongInt("-0xz23456789ABCDEF232Efg");
                        }
                        catch(Invalid_VeryLongInt &ex){
                            cout<<"错误原因:16进制字中出现非法字符"<<endl;
                            cout<<"异常值: "<<ex.get_error_str_num()<<endl;
                        }

                        cout<<"<测试错误的10进制字符串构造>"<<endl;
                        try{
                            cout<<"执行 num3_base10=VeryLongInt(\"12345678901E\")"<<endl;
                            num3_base10=VeryLongInt("123456789012345678901E");
                        }
                        catch(Invalid_VeryLongInt &ex){
                            cout<<"错误原因:10进制字中出现非法字符"<<endl;
                            cout<<"异常值: "<<ex.get_error_str_num()<<endl;
                        }

                        try{
                            cout<<"执行 num3_base10=VeryLongInt(\"-12345678901E\")"<<endl;
                            num3_base10=VeryLongInt("-12345678901E");
                        }
                        catch(Invalid_VeryLongInt &ex){
                            cout<<"错误原因:10进制字中出现非法字符"<<endl;
                            cout<<"异常值: "<<ex.get_error_str_num()<<endl;
                        }

                        break;
                    }
                    case 'H':{
                        cout<<"<测试重载过的++,--运算符>"<<endl;
                        cout<<"<随机构造一个100位巨型整数进行测试>"<<endl;
                        VeryLongInt temp=randVeryLongInt(100);
                        VeryLongInt num=temp;
                        cout<<"num="<<num<<endl;
                        cout<<"++num="<<++num<<"\n这之后 num="<<num<<endl;
                        num=temp;
                        cout<<"num++="<<num++<<"\n这之后 num="<<num<<endl;
                        num=temp;
                        cout<<"--num="<<--num<<"\n这之后 num="<<num<<endl;
                        num=temp;
                        cout<<"num--="<<num--<<"\n这之后 num="<<num<<endl;
                        
                        cout<<"<构造VeryLongInt型的0进行测试>"<<endl;
                        VeryLongInt num2(0);

                        cout<<"num2="<<num2<<endl;
                        cout<<"++num2="<<++num2<<"\n这之后 num2="<<num2<<endl;
                        num2=0;
                        cout<<"num2++="<<num2++<<"\n这之后 num2="<<num2<<endl;
                        num2=0;
                        cout<<"--num2="<<--num2<<"\n这之后 num2="<<num2<<endl;
                        num2=0;
                        cout<<"num2--="<<num2--<<"\n这之后 num2="<<num2<<endl;

                        cout<<"<用默认构造与93位巨型整数的进行测试>"<<endl;
                        VeryLongInt num3,num4;
                        num4=VeryLongInt("689556894861559021560958760392180228230999829389355664204870497865175476745363547571229155341");

                        cout<<"执行 num3=++num4 之前"<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"num4="<<num4<<endl;
                        num3=++num4;
                        cout<<"执行 num3=++num4 之后"<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"num4="<<num4<<endl;

                        cout<<"执行 num3=num4++ 之前"<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"num4="<<num4<<endl;
                        num3=num4++;
                        cout<<"执行 num3=num4++ 之后"<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"num4="<<num4<<endl;

                        cout<<"执行 num3=--num4 之前"<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"num4="<<num4<<endl;
                        num3=--num4;
                        cout<<"执行 num3=--num4 之后"<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"num4="<<num4<<endl;

                        cout<<"执行 num3=num4-- 之前"<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"num4="<<num4<<endl;
                        num3=num4--;
                        cout<<"执行 num3=num4-- 之后"<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"num4="<<num4<<endl;

                        break;
                    }
                    case 'I':{
                        cout<<"<测试VeryLongInt转化为string类型>"<<endl;
                        VeryLongInt num1=randVeryLongInt(100);
                        string str1=num1.toString();
                        cout<<"执行 VeryLongInt num1=randVeryLongInt(100)"<<endl;
                        cout<<"执行 string str1=num1.toString()"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"str1="<<str1<<endl;

                        VeryLongInt num2=-0;
                        string str2=num2.toString();
                        cout<<"执行 VeryLongInt num2=-0"<<endl;
                        cout<<"执行 string str2=num2.toString()"<<endl;
                        cout<<"num2="<<num2<<endl;
                        cout<<"str2="<<str2<<endl;

                        VeryLongInt num3("-0x123456789ABCDEF");
                        string str3=num3.toString();
                        cout<<"执行 VeryLongInt num3=\"-0x123456789ABCDEF\""<<endl; 
                        cout<<"执行 string str3=num3.toString()"<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"str3="<<str3<<endl;

                        VeryLongInt num4("-0");    
                        string str4=num4.toString();
                        cout<<"执行 VeryLongInt num4=\"-0\""<<endl;
                        cout<<"执行 string str4=num4.toString()"<<endl;
                        cout<<"num4="<<num4<<endl;
                        cout<<"str4="<<str4<<endl;

                        VeryLongInt num5("-013312412424323535321");
                        string str5=num5.toString();
                        cout<<"执行 VeryLongInt num5=\"-013312412424323535321\""<<endl;
                        cout<<"执行 string str5=num5.toString()"<<endl;
                        cout<<"num5="<<num5<<endl;
                        cout<<"str5="<<str5<<endl;
                        cout<<"dec_to_oct(str5) ->"<<dec_to_oct(str5)<<endl;
                        cout<<"num5.Oct() ->"<<num5.Oct()<<endl;

                        VeryLongInt num6("-0x123456789ABCDEF");
                        string str6=num6.toString();
                        cout<<"执行 VeryLongInt num6(\"-0x123456789ABCDEF\")"<<endl;
                        cout<<"执行 string str6=num6.toString()"<<endl;
                        cout<<"num6="<<num6<<endl;
                        cout<<"str6="<<str6<<endl;
                        cout<<"dec_to_hex(str6) ->"<<dec_to_hex(str6)<<endl;
                        cout<<"num6.Hex() ->"<<num6.Hex()<<endl;
                        
                        cout<<"<按下任意键继续测试>"<<endl;
                        getch();
                        cout<<"<测试VeryLongInt转化为long long 类型>"<<endl;
                        VeryLongInt num7("-3123141232143112312");
                        cout<<"执行 VeryLongInt num7=\"-3123141232143112312\""<<endl;
                        try{
                            cout<<"执行 long long num7_long=num7.toLongLong()"<<endl;
                            long long num7_long=num7.toLongLong();
                            cout<<"num7_long="<<num7_long<<endl;
                        }
                        catch(out_of_range &ex){
                            cout<<"转化失败,超出long long类型范围"<<endl;
                            cout<<"异常值: "<<ex.what()<<endl;
                        }

                        VeryLongInt num8("-0x123456789ABCDEF");
                        cout<<"执行 VeryLongInt num8=\"-0x123456789ABCDEF\""<<endl;
                        try{
                            cout<<"执行 long long num8_long=num8.toLongLong()"<<endl;
                            long long num8_long=num8.toLongLong();
                            cout<<"num8_long="<<num8_long<<endl;
                        }
                        catch(out_of_range &ex){
                            cout<<"转化失败,超出long long类型范围"<<endl;
                            cout<<"异常值: "<<ex.what()<<endl;
                        }

                        VeryLongInt num9("1231244");
                        cout<<"执行 VeryLongInt num9=\"1231244\""<<endl;
                        try{
                            cout<<"执行 long long num9_long=num9.toLongLong()"<<endl;
                            long long num9_long=num9.toLongLong();
                            cout<<"num9_long="<<num9_long<<endl;
                        }
                        catch(out_of_range &ex){
                            cout<<"转化失败,超出long long类型范围"<<endl;
                            cout<<"异常值: "<<ex.what()<<endl;
                        }

                        VeryLongInt num10("0x12323fe");
                        cout<<"执行 VeryLongInt num10=\"0x12323fe\""<<endl;
                        try{
                            cout<<"执行 long long num10_long=num10.toLongLong()"<<endl;
                            long long num10_long=num10.toLongLong();
                            cout<<"num10_long="<<num10_long<<endl;
                        }
                        catch(out_of_range &ex){
                            cout<<"转化失败,超出long long类型范围"<<endl;
                            cout<<"异常值: "<<ex.what()<<endl;
                        }

                        VeryLongInt num11("-012345670231231");
                        cout<<"执行 VeryLongInt num11=\"-012345670231231\""<<endl;
                        try{
                            cout<<"执行 long long num11_long=num11.toLongLong()"<<endl;
                            long long num11_long=num11.toLongLong();
                            cout<<"num11_long="<<num11_long<<endl;
                        }
                        catch(out_of_range &ex){
                            cout<<"转化失败,超出long long类型范围"<<endl;
                            cout<<"异常值: "<<ex.what()<<endl;
                        }

                        VeryLongInt num12("0x1234567023123122455467623fff");
                        cout<<"执行 VeryLongInt num12=\"0x1234567023123122455467623fff\""<<endl;
                        try{
                            cout<<"执行 long long num12_long=num12.toLongLong()"<<endl;
                            long long num12_long=num12.toLongLong();
                            cout<<"num12_long="<<num12_long<<endl;
                        }
                        catch(out_of_range &ex){
                            cout<<"转化失败,超出long long类型范围"<<endl;
                            cout<<"异常值: "<<ex.what()<<endl;
                        }
                        
                        VeryLongInt num13_min("-0x1234567890ffffffffffffffffffffffff");
                        try{
                            cout<<"执行 long long num13_long_min=num13_min.toLongLong()"<<endl;
                            long long num13_long_min=num13_min.toLongLong();
                            cout<<"num13_long_min="<<num13_long_min<<endl;
                        }
                        catch(out_of_range &ex){
                            cout<<"转化失败,超出long long类型范围"<<endl;
                            cout<<"异常值: "<<ex.what()<<endl;
                        }

                        cout<<"<按下任意键继续测试>"<<endl;
                        getch();
                        cout<<"<测试VeryLongInt转化为int类型>"<<endl;
                        VeryLongInt num13("12345678901234567890");
                        cout<<"执行 VeryLongInt num13=\"12345678901234567890\""<<endl;
                        try{
                            cout<<"执行 int num13_int=num13.toInt()"<<endl;
                            int num13_int=num13.toInt();
                            cout<<"num13_int="<<num13_int<<endl;
                        }
                        catch(out_of_range &ex){
                            cout<<"转化失败,超出int类型范围"<<endl;
                            cout<<"异常值: "<<ex.what()<<endl;
                        }

                        VeryLongInt num14("-0x123456789ABCDEF");
                        cout<<"执行 VeryLongInt num14=\"-0x123456789ABCDEF\""<<endl;
                        try{
                            cout<<"执行 int num14_int=num14.toInt()"<<endl;
                            int num14_int=num14.toInt();
                            cout<<"num14_int="<<num14_int<<endl;
                        }
                        catch(out_of_range &ex){
                            cout<<"转化失败,超出int类型范围"<<endl;
                            cout<<"异常值: "<<ex.what()<<endl;
                        }

                        VeryLongInt num15("-012345670231231");
                        cout<<"执行 VeryLongInt num15=\"-012345670231231\""<<endl;
                        try{
                            cout<<"执行 int num15_int=num15.toInt()"<<endl;
                            int num15_int=num15.toInt();
                            cout<<"num15_int="<<num15_int<<endl;
                        }
                        catch(out_of_range &ex){
                            cout<<"转化失败,超出int类型范围"<<endl;
                            cout<<"异常值: "<<ex.what()<<endl;
                        }

                        VeryLongInt num16("-0x1234567023123122455467623fff");
                        cout<<"执行 VeryLongInt num16=\"0x1234567023123122455467623fff\""<<endl;
                        try{
                            cout<<"执行 int num16_int=num16.toInt()"<<endl;
                            int num16_int=num16.toInt();
                            cout<<"num16_int="<<num16_int<<endl;
                        }
                        catch(out_of_range &ex){
                            cout<<"转化失败,超出int类型范围"<<endl;
                            cout<<"异常值: "<<ex.what()<<endl;
                        }
                        
                        VeryLongInt num17("1234567890");
                        cout<<"执行 VeryLongInt num17=\"1234567890\""<<endl;
                        try{
                            cout<<"执行 int num17_int=num17.toInt()"<<endl;
                            int num17_int=num17.toInt();
                            cout<<"num17_int="<<num17_int<<endl;
                        }
                        catch(out_of_range &ex){
                            cout<<"转化失败,超出int类型范围"<<endl;
                            cout<<"异常值: "<<ex.what()<<endl;
                        }

                        break;
                    }
                    case 'J':{
                        cout<<"<测试取\"-\"和\"+\"符号>"<<endl;
                        VeryLongInt num1("-723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848");
                        cout<<"执行 VeryLongInt num1=\"-723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848\""<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"-num1="<<-num1<<endl;
                        cout<<"+num1="<<num1<<endl;

                        VeryLongInt num2("+1234567890");
                        cout<<"执行 VeryLongInt num2=\"+1234567890\""<<endl;
                        cout<<"num2="<<num2<<endl;
                        cout<<"-num2="<<-num2<<endl;
                        cout<<"+num2="<<num2<<endl;

                        VeryLongInt num3("0");
                        cout<<"执行 VeryLongInt num3=\"0\""<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"-num3="<<-num3<<endl;
                        cout<<"+num3="<<num3<<endl;

                        VeryLongInt num4(0xffff);
                        cout<<"执行 VeryLongInt num4=0xffff"<<endl;
                        cout<<"num4="<<num4<<endl;
                        cout<<"-num4="<<-num4<<endl;
                        cout<<"+num4="<<num4<<endl;

                        VeryLongInt num5("-0x123456789ABCDEF");
                        cout<<"执行 VeryLongInt num5=\"-0x123456789ABCDEF\""<<endl;
                        cout<<"num5="<<num5<<endl;
                        cout<<"-num5="<<-num5<<endl;
                        cout<<"+num5="<<num5<<endl;
                        
                        VeryLongInt num6("+0x123456789ABCDEF");
                        cout<<"执行 VeryLongInt num6=\"+0x123456789ABCDEF\""<<endl;
                        cout<<"num6="<<num6<<endl;
                        cout<<"-num6="<<-num6<<endl;
                        cout<<"+num6="<<num6<<endl;

                        VeryLongInt num7("-012345670231231");
                        cout<<"执行 VeryLongInt num7=\"-012345670231231\""<<endl;
                        cout<<"num7="<<num7<<endl;
                        cout<<"-num7="<<-num7<<endl;
                        cout<<"+num7="<<num7<<endl;

                        VeryLongInt num8("+012345670231231");
                        cout<<"执行 VeryLongInt num8=\"+012345670231231\""<<endl;
                        cout<<"num8="<<num8<<endl;
                        cout<<"-num8="<<-num8<<endl;
                        cout<<"+num8="<<num8<<endl;

                        cout<<"<按下任意键测试拷贝构造>"<<endl;
                        getch();

                        VeryLongInt num9(num1);
                        cout<<"执行 VeryLongInt num9(num1)"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num9="<<num9<<endl;
                        cout<<"num1.isNegative ->"<< (num1.getIsNegative()) <<endl;
                        cout<<"num9.isNegative ->"<< (num9.getIsNegative()) <<endl;
                        cout<<"num1位数:"<< (num1.getLength()) <<endl;
                        cout<<"num9位数:"<< (num9.getLength()) <<endl;
                        cout<<"-num9="<<(-num9)<<endl;

                        break;
                    }
                    case 'K':{
                        cout<<"<测试 VeryLongInt类型 与 long long类型 间的运算>"<<endl;
                        VeryLongInt num1("-723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848");
                        cout<<"执行 VeryLongInt num1=\"-723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848\""<<endl;
                        long long num2=1234567890;
                        cout<<"执行 long long num2=1234567890"<<endl;
                        cout<<"num1+num2="<<num1+num2<<endl;
                        cout<<"num1-num2="<<num1-num2<<endl;
                        cout<<"num1*num2="<<num1*num2<<endl;
                        cout<<"num1/num2="<<num1/num2<<endl;
                        cout<<"num1\%num2="<<num1%num2<<endl;
                        
                        cout<<"num1<num2="<< (num1<num2)<<endl;
                        cout<<"num1>num2="<< (num1>num2)<<endl;
                        cout<<"num1<=num2="<< (num1<=num2)<<endl;
                        cout<<"num1>=num2="<< (num1>=num2)<<endl;
                        cout<<"num1==num2="<< (num1==num2)<<endl;
                        cout<<"num1!=num2="<< (num1!=num2)<<endl;
                        

                        cout<<"执行 num1+=num2 之前"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        cout<<"num1+=num2 ->"<< (num1+=num2)<<endl; 
                        cout<<"执行 num1+=num2 之后"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        num1="-723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848";

                        cout<<"执行 num1-=num2 之前"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        cout<<"num1-=num2 ->"<< (num1-=num2)<<endl; 
                        cout<<"执行 num1-=num2 之后"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        num1="-723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848";

                        cout<<"执行 num1*=num2 之前"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        cout<<"num1*=num2 ->"<< (num1*=num2)<<endl; 
                        cout<<"执行 num1*=num2 之后"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        num1="-723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848";

                        cout<<"执行 num1/=num2 之前"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        cout<<"num1/=num2 ->"<< (num1/=num2)<<endl; 
                        cout<<"执行 num1/=num2 之后"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        num1="-723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848";

                        cout<<"执行 num1%=num2 之前"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        cout<<"num1%=num2 ->"<< (num1%=num2)<<endl; 
                        cout<<"执行 num1%=num2 之后"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        num1="-723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848";

                        VeryLongInt num3("-1234567890000000000");
                        cout<<"执行 VeryLongInt num3=\"-1234567890000000000\""<<endl;
                        long long num4=-1234567;
                        cout<<"执行 long long num4=-1234567"<<endl;
                        cout<<"num3+num4="<<num3+num4<<endl;
                        cout<<"num3-num4="<<num3-num4<<endl;
                        cout<<"num3*num4="<<num3*num4<<endl;
                        cout<<"num3/num4="<<num3/num4<<endl;
                        cout<<"num3\%num4="<<num3%num4<<endl;
                       
                        cout<<"num3<num4="<< (num3<num4)<<endl;
                        cout<<"num3>num4="<< (num3>num4)<<endl;
                        cout<<"num3<=num4="<< (num3<=num4)<<endl;
                        cout<<"num3>=num4="<< (num3>=num4)<<endl;
                        cout<<"num3==num4="<< (num3==num4)<<endl;
                        cout<<"num3!=num4="<< (num3!=num4)<<endl;

                        cout<<"执行 num3+=num4 之前"<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"num4="<<num4<<endl;
                        cout<<"num3+=num4 ->"<< (num3+=num4)<<endl; 
                        cout<<"执行 num3+=num4 之后"<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"num4="<<num4<<endl;
                        num3="-1234567890000000000";

                        cout<<"执行 num3-=num4 之前"<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"num4="<<num4<<endl;
                        cout<<"num3-=num4 ->"<< (num3-=num4)<<endl; 
                        cout<<"执行 num3-=num4 之后"<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"num4="<<num4<<endl;
                        num3="-1234567890000000000";

                        cout<<"执行 num3*=num4 之前"<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"num4="<<num4<<endl;
                        cout<<"num3*=num4 ->"<< (num3*=num4)<<endl; 
                        cout<<"执行 num3*=num4 之后"<<endl; 
                        cout<<"num3="<<num3<<endl;
                        cout<<"num4="<<num4<<endl;
                        num3="-1234567890000000000";

                        cout<<"执行 num3/=num4 之前"<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"num4="<<num4<<endl;
                        cout<<"num3/=num4 ->"<< (num3/=num4)<<endl; 
                        cout<<"执行 num3/=num4 之后"<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"num4="<<num4<<endl;
                        num3="-1234567890000000000";

                        cout<<"执行 num3%=num4 之前"<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"num4="<<num4<<endl;
                        cout<<"num3%=num4 ->"<< (num3%=num4)<<endl; 
                        cout<<"执行 num3%=num4 之后"<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"num4="<<num4<<endl;
                        num3="-1234567890000000000";

                        VeryLongInt num5=randVeryLongInt(1000);
                        VeryLongInt temp=num5;
                        cout<<"执行 VeryLongInt num5=randVeryLongInt(1000) 1000位随机数"<<endl;
                        long long num6=232421132123214ll;
                        cout<<"执行 long long num6=232421132123214ll"<<endl;
                        cout<<"num5+num6="<<num5+num6<<endl;
                        cout<<"num5-num6="<<num5-num6<<endl;
                        cout<<"num5*num6="<<num5*num6<<endl;
                        cout<<"num5/num6="<<num5/num6<<endl;
                        cout<<"num5\%num6="<<num5%num6<<endl;
                        
                        cout<<"num5<num6="<< (num5<num6)<<endl;
                        cout<<"num5>num6="<< (num5>num6)<<endl;
                        cout<<"num5<=num6="<< (num5<=num6)<<endl;
                        cout<<"num5>=num6="<< (num5>=num6)<<endl;
                        cout<<"num5==num6="<< (num5==num6)<<endl;
                        cout<<"num5!=num6="<< (num5!=num6)<<endl;

                        cout<<"执行 num5+=num6 之前"<<endl;
                        cout<<"num5="<<num5<<endl;
                        cout<<"num6="<<num6<<endl;
                        cout<<"num5+=num6 ->"<< (num5+=num6)<<endl; 
                        cout<<"执行 num5+=num6 之后"<<endl;
                        cout<<"num5="<<num5<<endl;
                        cout<<"num6="<<num6<<endl;
                        num5=temp;

                        cout<<"执行 num5-=num6 之前"<<endl;
                        cout<<"num5="<<num5<<endl;
                        cout<<"num6="<<num6<<endl;
                        cout<<"num5-=num6 ->"<< (num5-=num6)<<endl; 
                        cout<<"执行 num5-=num6 之后"<<endl;
                        cout<<"num5="<<num5<<endl;
                        cout<<"num6="<<num6<<endl;
                        num5=temp;

                        cout<<"执行 num5*=num6 之前"<<endl;
                        cout<<"num5="<<num5<<endl;
                        cout<<"num6="<<num6<<endl;
                        cout<<"num5*=num6 ->"<< (num5*=num6)<<endl; 
                        cout<<"执行 num5*=num6 之后"<<endl;
                        cout<<"num5="<<num5<<endl;
                        cout<<"num6="<<num6<<endl;
                        num5=temp;

                        cout<<"执行 num5/=num6 之前"<<endl;
                        cout<<"num5="<<num5<<endl;
                        cout<<"num6="<<num6<<endl;
                        cout<<"num5/=num6 ->"<< (num5/=num6)<<endl; 
                        cout<<"执行 num5/=num6 之后"<<endl;
                        cout<<"num5="<<num5<<endl;
                        cout<<"num6="<<num6<<endl;
                        num5=temp;

                        cout<<"执行 num5%=num6 之前"<<endl;
                        cout<<"num5="<<num5<<endl;
                        cout<<"num6="<<num6<<endl;
                        cout<<"num5%=num6 ->"<< (num5%=num6)<<endl; 
                        cout<<"执行 num5%=num6 之后"<<endl;
                        cout<<"num5="<<num5<<endl;
                        cout<<"num6="<<num6<<endl;
                        num5=temp;

                        break;
                       
                    }
                    case 'L':{
                        cout<<"<测试 VeryLongInt类型 与 string类型 间的运算>"<<endl;
                        VeryLongInt num1("-723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848");
                        cout<<"执行 VeryLongInt num1=\"-723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848\""<<endl;
                        string num2="1234567890";
                        cout<<"执行 string num2=\"1234567890\""<<endl;
                        cout<<"num1+num2="<<num1+num2<<endl;
                        cout<<"num1-num2="<<num1-num2<<endl;    
                        cout<<"num1*num2="<<num1*num2<<endl;
                        cout<<"num1/num2="<<num1/num2<<endl;
                        cout<<"num1%num2="<<num1%num2<<endl;
                      
                        cout<<"num1<num2="<< (num1<num2)<<endl;
                        cout<<"num1>num2="<< (num1>num2)<<endl;
                        cout<<"num1<=num2="<< (num1<=num2)<<endl;
                        cout<<"num1>=num2="<< (num1>=num2)<<endl;
                        cout<<"num1==num2="<< (num1==num2)<<endl;
                        cout<<"num1!=num2="<< (num1!=num2)<<endl;

                        cout<<"执行 num1+=num2 之前"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        cout<<"num1+=num2 ->"<< (num1+=num2)<<endl;
                        cout<<"num1+=num2 之后"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        num1="-723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848";

                        cout<<"执行 num1-=num2 之前"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        cout<<"num1-=num2 ->"<< (num1-=num2)<<endl;
                        cout<<"num1-=num2 之后"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        num1="-723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848";

                        cout<<"执行 num1*=num2 之前"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        cout<<"num1*=num2 ->"<< (num1*=num2)<<endl;
                        cout<<"num1*=num2 之后"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        num1="-723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848";

                        cout<<"执行 num1/=num2 之前"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        cout<<"num1/=num2 ->"<< (num1/=num2)<<endl;
                        cout<<"num1/=num2 之后"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        num1="-723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848";

                        cout<<"执行 num1%=num2 之前"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        cout<<"num1%=num2 ->"<< (num1%=num2)<<endl;
                        cout<<"num1%=num2 之后"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        num1="-723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848";

                        VeryLongInt num3("-1234567890000000000");
                        cout<<"执行 VeryLongInt num3=\"-1234567890000000000\""<<endl;
                        string num4="-1234567";
                        cout<<"执行 string num4=\"-1234567\""<<endl;
                        cout<<"num3+num4="<<num3+num4<<endl;
                        cout<<"num3-num4="<<num3-num4<<endl;
                        cout<<"num3*num4="<<num3*num4<<endl;
                        cout<<"num3/num4="<<num3/num4<<endl;
                        cout<<"num3%num4="<<num3%num4<<endl;
                        cout<<"num3+=num4  ->"<< (num3+=num4)<<endl;
                        cout<<"num3-=num4  ->"<< (num3-=num4)<<endl;
                        cout<<"num3*=num4  ->"<< (num3*=num4)<<endl;
                        cout<<"num3/=num4  ->"<< (num3/=num4)<<endl;
                        cout<<"num3%=num4  ->"<< (num3%=num4)<<endl;
                        cout<<"num3<num4="<< (num3<num4)<<endl;
                        cout<<"num3>num4="<< (num3>num4)<<endl;
                        cout<<"num3<=num4="<< (num3<=num4)<<endl;
                        cout<<"num3>=num4="<< (num3>=num4)<<endl;
                        cout<<"num3==num4="<< (num3==num4)<<endl;
                        cout<<"num3!=num4="<< (num3!=num4)<<endl;
         
                        VeryLongInt num5=randVeryLongInt(1000);
                        VeryLongInt temp=num5;
                        cout<<"执行 VeryLongInt num5=randVeryLongInt(1000) 1000位随机数"<<endl;
                        string num6=to_string(232421132123214);
                        cout<<"执行 string num6=to_string(232421132123214)"<<endl;
                        cout<<"num5+num6="<<num5+num6<<endl;
                        cout<<"num5-num6="<<num5-num6<<endl;
                        cout<<"num5*num6="<<num5*num6<<endl;
                        cout<<"num5/num6="<<num5/num6<<endl;
                        cout<<"num5%num6="<<num5%num6<<endl;
                        
                        cout<<"num5<num6="<< (num5<num6)<<endl;
                        cout<<"num5>num6="<< (num5>num6)<<endl;
                        cout<<"num5<=num6="<< (num5<=num6)<<endl;
                        cout<<"num5>=num6="<< (num5>=num6)<<endl;
                        cout<<"num5==num6="<< (num5==num6)<<endl;
                        cout<<"num5!=num6="<< (num5!=num6)<<endl;

                        cout<<"执行 num5+=num6 之前"<<endl;
                        cout<<"num5="<<num5<<endl;
                        cout<<"num6="<<num6<<endl;
                        cout<<"num5+=num6 ->"<< (num5+=num6)<<endl;
                        cout<<"num5+=num6 之后"<<endl;
                        cout<<"num5="<<num5<<endl;
                        cout<<"num6="<<num6<<endl;
                        num5=temp;

                        cout<<"执行 num5-=num6 之前"<<endl;
                        cout<<"num5="<<num5<<endl;
                        cout<<"num6="<<num6<<endl;
                        cout<<"num5-=num6 ->"<< (num5-=num6)<<endl;
                        cout<<"num5-=num6 之后"<<endl;
                        cout<<"num5="<<num5<<endl;
                        cout<<"num6="<<num6<<endl;
                        num5=temp;

                        cout<<"执行 num5*=num6 之前"<<endl;
                        cout<<"num5="<<num5<<endl;
                        cout<<"num6="<<num6<<endl;
                        cout<<"num5*=num6 ->"<< (num5*=num6)<<endl;
                        cout<<"num5*=num6 之后"<<endl;
                        cout<<"num5="<<num5<<endl;  
                        cout<<"num6="<<num6<<endl;
                        num5=temp;

                        cout<<"执行 num5/=num6 之前"<<endl;
                        cout<<"num5="<<num5<<endl;
                        cout<<"num6="<<num6<<endl;
                        cout<<"num5/=num6 ->"<< (num5/=num6)<<endl; 
                        cout<<"num5/=num6 之后"<<endl;
                        cout<<"num5="<<num5<<endl;
                        cout<<"num6="<<num6<<endl;
                        num5=temp;

                        cout<<"执行 num5%=num6 之前"<<endl;
                        cout<<"num5="<<num5<<endl;
                        cout<<"num6="<<num6<<endl;
                        cout<<"num5%=num6 ->"<< (num5%=num6)<<endl; 
                        cout<<"num5%=num6 之后"<<endl;
                        cout<<"num5="<<num5<<endl;
                        cout<<"num6="<<num6<<endl;
                        num5=temp;

                        break;
                    }
                    case 'M':{
                        cout<<"<测试 0 的符号>"<<endl;
                        VeryLongInt num0_str1("0");
                        cout<<"执行 VeryLongInt num0_str1=\"0\""<<endl;
                        cout<<"num0_str1="<<num0_str1<<endl;
                        cout<<"num0_str1.getIsNegative()="<<num0_str1.getIsNegative()<<endl;

                        VeryLongInt num0_str2("-0");
                        cout<<"执行 VeryLongInt num0_str2=\"-0\""<<endl;
                        cout<<"num0_str2="<<num0_str2<<endl;
                        cout<<"num0_str2.getIsNegative()="<<num0_str2.getIsNegative()<<endl;

                        VeryLongInt num0_int1(0);
                        cout<<"执行 VeryLongInt num0_int1=0"<<endl;
                        cout<<"num0_int1="<<num0_int1<<endl;
                        cout<<"num0_int1.getIsNegative()="<<num0_int1.getIsNegative()<<endl;
                        
                        VeryLongInt num0_int2(-0);
                        cout<<"执行 VeryLongInt num0_int2=-0"<<endl;
                        cout<<"num0_int2="<<num0_int2<<endl;
                        cout<<"num0_int2.getIsNegative()="<<num0_int2.getIsNegative()<<endl;

                        cout<<"<按下任意键继续测试>"<<endl;
                        getch();

                        cout<<"<测试与int 类型0的运算>"<<endl;
                        VeryLongInt num1=randVeryLongInt(100);
                        cout<<"执行 VeryLongInt num1=randVeryLongInt(100) 100位随机数"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num1+0="<<num1+0<<endl;
                        cout<<"num1-0="<<num1-0<<endl;
                        cout<<"num1*0="<<num1*0<<endl;
                        cout<<"0/num1="<<0/num1<<endl;
                        cout<<"0\%num1="<<0%num1<<endl;
                        cout<<"num1+=0  ->" << (num1+=0) <<endl;
                        cout<<"num1-=0  ->" << (num1+=0) <<endl;
                        cout<<"num1*=0  ->" << (num1*=0) <<endl;

                        cout<<"<按下任意键继续测试>"<<endl;
                        getch();
                        cout<<"<测试与long long 类型0的运算>"<<endl;
                        VeryLongInt num2=randVeryLongInt(100);
                        cout<<"执行 VeryLongInt num2=randVeryLongInt(100) 100位随机数"<<endl;
                        cout<<"num2="<<num2<<endl;
                        cout<<"num2+0LL="<<num2+0LL<<endl;
                        cout<<"num2-0LL="<<num2-0LL<<endl;
                        cout<<"num2*0LL="<<num2*0LL<<endl;
                        cout<<"0LL/num2="<<0ll/num2<<endl;
                        cout<<"0LL\%num2="<<0ll%num2<<endl;
                        cout<<"num2+=0LL  ->" << (num2+=0LL) <<endl;
                        cout<<"num2-=0LL  ->" << (num2+=0LL) <<endl;
                        cout<<"num2*=0LL  ->" << (num2*=0LL) <<endl;

                        cout<<"<按下任意键继续测试>"<<endl;
                        getch();
                        cout<<"<测试与string类型\"0\"的运算>"<<endl;
                        VeryLongInt num3=randVeryLongInt(100);
                        cout<<"执行 VeryLongInt num3=randVeryLongInt(100) 100位随机数"<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"num3+\"0\"="<<num3+"0"<<endl;
                        cout<<"num3-\"0\"="<<num3-"0"<<endl;
                        cout<<"num3*\"0\"="<<num3*"0"<<endl;
                        cout<<"\"0\"/num3="<<"0"/num3<<endl;
                        cout<<"\"0\"%num3="<<"0"%num3<<endl;
                        cout<<"num3+=0  ->" << (num3+=0) <<endl;
                        cout<<"num3-=0  ->" << (num3+=0) <<endl;
                        cout<<"num3*=0  ->" << (num3*=0) <<endl;
                        
                        cout<<"<按下任意键继续测试>"<<endl;
                        getch();
                        cout<<"<测试与VeryLongInt类型0的运算>"<<endl;
                        VeryLongInt num4=randVeryLongInt(100);
                        cout<<"执行 VeryLongInt num4=randVeryLongInt(100) 100位随机数"<<endl;
                        cout<<"num4="<<num4<<endl;
                        cout<<"num4+VeryLongInt(0)="<<num4+VeryLongInt(0)<<endl;
                        cout<<"num4-VeryLongInt(0)="<<num4-VeryLongInt(0)<<endl;
                        cout<<"num4*VeryLongInt(0)="<<num4*VeryLongInt(0)<<endl;
                        cout<<"VeryLongInt(0)/num4="<<VeryLongInt(0)/num4<<endl;
                        cout<<"VeryLongInt(0)%num4="<<VeryLongInt(0)%num4<<endl;
                        cout<<"num4+=VeryLongInt(0)  ->" << (num4+=VeryLongInt(0)) <<endl;  
                        cout<<"num4-=VeryLongInt(0)  ->" << (num4+=VeryLongInt(0)) <<endl;
                        cout<<"num4*=VeryLongInt(0)  ->" << (num4*=VeryLongInt(0)) <<endl;

                        cout<<"<按下任意键继续测试>"<<endl;
                        getch();
                        cout<<"<测试除以0的异常>"<<endl;

                        try{
                            VeryLongInt num5=randVeryLongInt(100);
                            cout<<"执行 VeryLongInt num5=randVeryLongInt(100) 100位随机数"<<endl;
                            cout<<"num5="<<num5<<endl;
                            cout<<"num5/0="<<num5/0<<endl;
                        }
                        catch(const invalid_argument &ex){
                            cout<<"异常信息: "<<ex.what()<<endl;
                        }

                        try{
                            VeryLongInt num6=randVeryLongInt(100);
                            cout<<"执行 VeryLongInt num6=randVeryLongInt(100) 100位随机数"<<endl;
                            cout<<"num6="<<num6<<endl;
                            cout<<"num6/=0  ->"<< (num6/=0) <<endl;
                        }
                        
                        catch(const invalid_argument &ex){
                            cout<<"异常信息: "<<ex.what()<<endl;
                        }

                        cout<<"<测试取余0的异常>"<<endl;

                        try{
                            VeryLongInt num7=randVeryLongInt(100);
                            cout<<"执行 VeryLongInt num6=randVeryLongInt(100) 100位随机数"<<endl;
                            cout<<"num7="<<num7<<endl;
                            cout<<"num7%0=  ->"<<num7%0<<endl;
                        }
                        catch(const invalid_argument &ex){
                            cout<<"异常信息: "<<ex.what()<<endl;
                        }

                        try{
                            VeryLongInt num8=randVeryLongInt(100);
                            cout<<"执行 VeryLongInt num8=randVeryLongInt(100) 100位随机数"<<endl;
                            cout<<"num8="<<num8<<endl;
                            cout<<"num8%=0  ->"<< (num8%=0) <<endl;
                        }
                        catch(const invalid_argument &ex){
                            cout<<"异常信息: "<<ex.what()<<endl;
                        }

                        break;
                    }
                    case 'N':{//测试自定义输入构造
                        cout<<"<测试自定义输入构造>"<<endl;
                        string input_str;
                        VeryLongInt num1,num2;
                        try{
                            cout<<"请输入 num1: ";
                            cin>>num1;
                            cout<< "执行 cin>>num1"<<endl;
                            cout<< "num1="<<num1<<endl;
                            cout<< "num1的位数"<< num1.getLength()<<endl;
                            cout<< "num1的符号"<< (num1.getIsNegative()?'-':'+')<<endl;
                        }
                        catch(const Invalid_VeryLongInt &ex){
                            cout<<"异常信息: "<<ex.get_error_str_num()<<endl;
                        }

                        try{
                            cout<<"请输入 num2: ";
                            cin>>num2;
                            cout<< "执行 cin>>num2"<<endl;
                            cout<< "num2="<<num2<<endl;
                            cout<< "num2的位数"<< num2.getLength()<<endl;
                            cout<< "num2的符号"<< (num2.getIsNegative()?'-':'+')<<endl;
                        }
                        catch(const Invalid_VeryLongInt &ex){
                            cout<<"异常信息: "<<ex.get_error_str_num()<<endl;
                        }
                
                        test_verylongint_operation(num1,num2,false);
                        break;
                        
                    }
                    case 'O':{//测试随机构造n位巨型整数
                        cout<<"<测试随机构造n位巨型整数>"<<endl;
                        bool quit=false;
                        while(!quit){
                            size_t n=0;
                            VeryLongInt num1,num2;
                            printf("请输入num1的构造的位数(%d到%llu位): ",0,ULLONG_MAX);
                            cin>>n;
                            if(n>0 && n<=ULLONG_MAX){
                                num1=randVeryLongInt(n);
                                cout<<"执行 randVeryLongInt(n) 得到的随机数为: "<<num1<<endl;
                                cout<<"num的位数"<< num1.getLength()<<endl;
                                cout<<"num的符号"<< (num1.getIsNegative()?'-':'+')<<endl;
                               
                            }
                            else{
                                cout<<"输入的n超出范围!"<<endl;
                                cout<<"<按下任意键重新开始测试随机构造>"<<endl;
                                getch();
                                continue;
                            }
                            printf("请输入num2的构造的位数(%d到%llu位): ",0,ULLONG_MAX);
                            cin>>n;
                            if(n>0 && n<=ULLONG_MAX){
                                num2=randVeryLongInt(n);
                                cout<<"执行 randVeryLongInt(n) 得到的随机数为: "<<num2<<endl;
                                cout<<"num的位数"<< num2.getLength()<<endl;
                                cout<<"num的符号"<< (num2.getIsNegative()?'-':'+')<<endl;
                            }
                            else{
                                cout<<"输入的n超出范围!"<<endl;
                                cout<<"<按下任意键重新开始测试随机构造>"<<endl;
                                getch();
                                continue;
                            }
                            cout<<"<按任意键开始测试两数的运算>"<<endl;
                            getch();
                            test_verylongint_operation(num1,num2,false);
                            cout<<"<是否继续测试随机构造? (Y/N): "<<endl;
                            char choice;
                            while(true){
                                choice=toupper(getch());
                                if(choice=='Y'){
                                    break;
                                }
                                else if(choice=='N'){
                                    quit=true;
                                    break;
                                }
                                cout<<"请输入有效的选项!"<<endl;
                            }
                        }
                        break;
                    }
                    case 'P':{//测试乘方
                        VeryLongInt num1=2812,num2=3312;
                        cout<<"执行 VeryLongInt num1=2812,num2=3312"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        cout<<"num1的位数"<< num1.getLength()<<endl;
                        cout<<"num1的符号"<< (num1.getIsNegative()?'-':'+')<<endl;
                        cout<<"num2的位数"<< num2.getLength()<<endl;
                        cout<<"num2的符号"<< (num2.getIsNegative()?'-':'+')<<endl;
                        cout<<"pow(num1,num2.toLongLong())="<<pow(num1,num2.toLongLong())<<endl;

                        VeryLongInt num3("0x1100"),num4("02222");
                        cout<<"执行 VeryLongInt num3=\"0x1100\",num4=\"02222\""<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"num4="<<num4<<endl;
                        cout<<"num3的位数"<< num3.getLength()<<endl;
                        cout<<"num3的符号"<< (num3.getIsNegative()?'-':'+')<<endl;
                        cout<<"num4的位数"<< num4.getLength()<<endl;
                        cout<<"num4的符号"<< (num4.getIsNegative()?'-':'+')<<endl;
                        cout<<"pow(num3,num4.toLongLong())="<<pow(num3,num4.toLongLong())<<endl;


                        break;
                    }
                    case 'Q':{//连续赋值测试

                        cout<<"<测试连续赋值测试>"<<endl;
                        VeryLongInt num1,num2,num3,num4;
                        num4="-723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848";

                        cout<<"执行 VeryLongInt num1,num2,num3,num4;"<<endl;
                        cout<<"执行 num4=\"-723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848\""<<endl;
                        cout<<"num4="<<num4<<endl;
                        cout<<"num4的位数"<< num4.getLength()<<endl;
                        cout<<"num4的符号"<< (num4.getIsNegative()?'-':'+')<<endl;

                        cout<<"执行 num1=num2=num3=num4; 之前"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"num4="<<num4<<endl;
                        num1=num2=num3=num4;
                        cout<<"执行 num1=num2=num3=num4; 之后"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        cout<<"num3="<<num3<<endl;
                        cout<<"num4="<<num4<<endl;

                        break;
                    }
                    case 'R':{//测试求最小公倍数和最大公约数
                        cout<<"<测试求最小公倍数和最大公约数>"<<endl;
                        VeryLongInt num1("723717357166038747208188034596004281260282262115007489309813754419851988469652091931023768848");
                        VeryLongInt num2("689556894861559021560958760392180228230999829389355664204870497865175476745363547571229155341");
                        cout<<"执行 VeryLongInt num1=1234567890,num2=98765432109876543210"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        cout<<"num1和num2的最小公倍数为:\n"<<num1.lcm(num2)<<endl;
                        cout<<"num1和num2的最大公约数为:\n"<<num1.gcd(num2)<<endl;

                        num1="1234567890555555555555555";
                        num2="23455678905";
                        cout<<"执行 VeryLongInt num1=\"1234567890555555555555555\",num2=\"23455678905\""<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"num2="<<num2<<endl;
                        cout<<"num1和num2的最小公倍数为:\n"<<num1.lcm(num2)<<endl;
                        cout<<"num1和num2的最大公约数为:\n"<<num1.gcd(num2)<<endl;

                        break;
                    
                    }
                    case 'S':{//测试开方
                        cout<<"<测试开方>"<<endl;
                        VeryLongInt num1(4);
                        cout<<"执行 num1=4"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"sqrt(num1)="<<sqrt(num1)<<endl;

                        num1=16;
                        cout<<"执行 num1=16"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"sqrt(num1)="<<sqrt(num1)<<endl;
                        
                        num1="8888888888888888888123241412414124124141412421414141412414141414141242";
                        cout<<"执行 num1=\"8123241412414124124141412421414141412414141414141242\""<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"sqrt(num1)="<<sqrt(num1)<<endl;

                        num1=-1;
                        cout<<"执行 num1=-1"<<endl;
                        cout<<"num1="<<num1<<endl;
                        cout<<"执行sqrt(num1)"<<endl;
                        try{
                            cout<<"sqrt(num1)="<<sqrt(num1)<<endl;
                        }
                        catch(const invalid_argument &ex){
                            cout<<"异常信息: "<<ex.what()<<endl;
                        }
                        
                        num1=randVeryLongInt(1000,false);//生成1000位随机数,且是正数
                        cout<<"执行 num1=randVeryLongInt(1000)"<<endl;
                        cout<<"num1="<<num1<<endl;
                        auto start=chrono::high_resolution_clock::now();
                        cout<<"sqrt(num1)="<<sqrt(num1)<<endl;
                        auto end=chrono::high_resolution_clock::now();
                        auto duration=chrono::duration_cast<chrono::microseconds>(end - start);
                        cout<<"执行 sqrt(num1) 耗时: "<<duration.count()/1000000.0<<"s"<<endl;
                        break;
                    }
                    case 'T':{//退出程序
                        cout<<"退出程序"<<endl;
                        exit(0);
                        break;
                    }

                    default:
                        cout<<"请输入有效的选项编号!"<<endl;
                        break;
                }
            }
        }
    }
}
