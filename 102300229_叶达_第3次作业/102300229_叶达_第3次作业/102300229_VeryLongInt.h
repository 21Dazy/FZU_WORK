/***************************************************************
【文件名】          102300229_VeryLongInt.h
【功能模块和目的】    VeryLongInt类的头文件
【开发环境】         Visual Studio Code / MinGW gcc 8.1.0 / c++17
【开发者】           叶达 
****************************************************************/

/***************************************************************
【类名】            VeryLongInt
【功能】         1. 存储巨型整数，支持无参构造，通过string构造，通过long long构造，通过VeryLongInt拷贝构造
                2. 支持VeryLongInt与string，long long，VeryLongInt之间的的四则运算
                   比较、取模、取余、取整等操作（运算符已经重载）
                3. 支持随机生成n位巨型整数
                4. 支持进制转换
                5. 支持正整数次幂的运算
                6. 支持VeryLongInt与string,int,long long等类型之间的转换
                7. 支持比较运算
                8. 可以求最小公倍数
                9. 可以求最大公约数
                10. 赋值运算符与复合赋值运算符重载
                11. ++，--运算符重载
                12. 支持开方
                13. 支持取绝对值
                14. 单目运算符“+”、“-”重载
                15. 支持输入输出（重载了<<，>>）
                16. 内置部分测试函数
****************************************************************/

#ifndef VeryLongInt_H
#define VeryLongInt_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <tuple>
#include <limits>
#include <random>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <chrono>
#include <fstream>

using namespace std;

#define MAX_RANDOM_LENGTH 1000//默认参数情况下随机数生成的最大长度

enum E_BASE{Dec=10, Hex=16, Oct=8};//进制枚举类型

const long long FLOOR_SQRT_LLONG_MAX = 3037000499;

class math_error : public exception{
    public:
        const char* what() const throw(){
            return "math error";
        }
};
class zero_divide : public math_error{
    public:
        const char* what() const throw(){
            return "error: division by zero";
        }
};
class Invalid_VeryLongInt : math_error{
    private:
        string error_str_num;
    public:
        Invalid_VeryLongInt(const string& str_num){
            error_str_num=str_num;
        }
        string get_error_str_num() const{
            return error_str_num;
        }
        
};

bool is_valid_number_dec(const string& num);//判断字符串是否为有效的十进制数字
bool is_valid_number_hex(const string& num);//判断字符串是否为有效的十六进制数字
bool is_valid_number_oct(const string& num);//判断字符串是否为有效的八进制数字
bool is_valid_number(const string& num);//判断字符串是否为有效的数字
void balance_length(string& str_num1, string& str_num2);//调整两个表示长整数的字符串的长度，使得它们的长度相同
void strip_zeros(string& str_num);//去除字符串中无效的前导零
void add_trailing_zeroes(string& num, size_t num_zeroes);//在数字的末尾添加指定数量的零
bool str_is_pow10(const string& num);//判断字符串是否为10的整数次幂

class VeryLongInt{
    private:
        //私有成员变量
        string digits;//存储数字，从高位到低位排列，注意转换时要注意高低端问题
        bool isNegative;//符号位
    public:
        //构造函数
        VeryLongInt(){
            digits="0";
            isNegative=false;
        };//默认构造函数
        VeryLongInt(const string& str);//构造函数，将字符串转换为数字
        VeryLongInt(const VeryLongInt& num);//拷贝构造函数
        VeryLongInt(const long long& num);//构造函数，将长整数转换为数字
    
        //析构函数
        ~VeryLongInt(){
            digits.clear();//清空数组
        }
        //重载赋值运算符
        VeryLongInt& operator=(const VeryLongInt &num);//重载对于VeryLongInt的赋值运算符
        VeryLongInt& operator=(const long long &num);//重载对于long long的赋值运算符
        VeryLongInt& operator=(const string &str);//重载对于string的赋值运算符
        //重载"+"运算符
        friend VeryLongInt operator+(const VeryLongInt &num1, const long long &num2);//重载对于long long和VeryLongInt的加法运算符
        friend VeryLongInt operator+(const VeryLongInt &num1, const string &num2);//重载对于string和VeryLongInt的加法运算符
        friend VeryLongInt operator+(const string &num1, const VeryLongInt &num2);//重载对于string和VeryLongInt的加法运算符
        friend VeryLongInt operator+(const VeryLongInt& num1, const VeryLongInt& num2);//重载对于VeryLongInt和VeryLongInt的加法运算符
        friend VeryLongInt operator+(const long long &num1, const VeryLongInt &num2);
        //重载"-"运算符
        friend VeryLongInt operator-(const VeryLongInt &num1, const long long &num2);//重载对于long long和VeryLongInt的减法运算符
        friend VeryLongInt operator-(const VeryLongInt &num1, const string &num2);//重载对于string和VeryLongInt的减法运算符
        friend VeryLongInt operator-(const VeryLongInt& num1, const VeryLongInt& num2);//重载对于VeryLongInt和VeryLongInt的减法运算符
        friend VeryLongInt operator-(const string &num1, const VeryLongInt &num2);
        friend VeryLongInt operator-(const long long &num1, const VeryLongInt &num2);
        //重载"*"运算符
        friend VeryLongInt operator*(const VeryLongInt &num1, const long long &num2);//重载对于long long和VeryLongInt的乘法运算符
        friend VeryLongInt operator*(const VeryLongInt &num1, const string &num2);//重载对于string和VeryLongInt的乘法运算符
        friend VeryLongInt operator*(const VeryLongInt& num1, const VeryLongInt& num2);//重载对于VeryLongInt和VeryLongInt的乘法运算符
        friend VeryLongInt operator*(const string &num1, const VeryLongInt &num2);
        friend VeryLongInt operator*(const long long &num1, const VeryLongInt &num2);
        //重载"/"运算符
        friend VeryLongInt operator/(const VeryLongInt &num1, const long long &num2);//重载对于long long和VeryLongInt的除法运算符
        friend VeryLongInt operator/(const VeryLongInt &num1, const string &num2);//重载对于string和VeryLongInt的除法运算符
        friend VeryLongInt operator/(const VeryLongInt& num1, const VeryLongInt& num2);//重载对于VeryLongInt和VeryLongInt的除法运算符
        friend VeryLongInt operator/(const string &num1, const VeryLongInt &num2);
        friend VeryLongInt operator/(const long long &num1, const VeryLongInt &num2);
        //重载"%"运算符
        friend VeryLongInt operator%(const VeryLongInt &num1, const long long &num2);//重载对于long long和VeryLongInt的取模运算符
        friend VeryLongInt operator%(const VeryLongInt &num1, const string &num2);//重载对于string和VeryLongInt的取模运算符
        friend VeryLongInt operator%(const VeryLongInt& num1, const VeryLongInt& num2);//重载对于VeryLongInt和VeryLongInt的取模运算符
        friend VeryLongInt operator%(const string &num1, const VeryLongInt &num2);
        friend VeryLongInt operator%(const long long &num1, const VeryLongInt &num2);
        //重载"=="运算符
        friend bool operator==(const VeryLongInt &num1, const long long &num2);//重载对于long long和VeryLongInt的相等运算符
        friend bool operator==(const VeryLongInt &num1, const string &num2);//重载对于string和VeryLongInt的相等运算符
        friend bool operator==(const VeryLongInt& num1, const VeryLongInt& num2);//重载对于VeryLongInt和VeryLongInt的相等运算符
        //friend bool operator==(const string &num1, const VeryLongInt &num2);
        //重载"<"运算符
        friend bool operator<(const VeryLongInt &num1, const long long &num2);//重载对于long long和VeryLongInt的小于运算符
        friend bool operator<(const VeryLongInt &num1, const string &num2);//重载对于string和VeryLongInt的小于运算符
        friend bool operator<(const VeryLongInt& num1, const VeryLongInt& num2);//重载对于VeryLongInt和VeryLongInt的小于运算符
        //friend bool operator<(const string &num1, const VeryLongInt &num2);
        //重载">"运算符
        friend bool operator>(const VeryLongInt &num1, const long long &num2);//重载对于long long和VeryLongInt的大于运算符
        friend bool operator>(const VeryLongInt &num1, const string &num2);//重载对于string和VeryLongInt的大于运算符
        friend bool operator>(const VeryLongInt& num1, const VeryLongInt& num2);//重载对于VeryLongInt和VeryLongInt的大于运算符
       // friend bool operator>(const string &num1, const VeryLongInt &num2);
        //重载"<="运算符
        friend bool operator<=(const VeryLongInt &num1, const long long &num2);//重载对于long long和VeryLongInt的小于等于运算符
        friend bool operator<=(const VeryLongInt &num1, const string &num2);//重载对于string和VeryLongInt的小于等于运算符
        friend bool operator<=(const VeryLongInt& num1, const VeryLongInt& num2);//重载对于VeryLongInt和VeryLongInt的小于等于运算符
       // friend bool operator<=(const string &num1, const VeryLongInt &num2);
        //重载">="运算符
        friend bool operator>=(const VeryLongInt &num1, const long long &num2);//重载对于long long和VeryLongInt的大于等于运算符
        friend bool operator>=(const VeryLongInt &num1, const string &num2);//重载对于string和VeryLongInt的大于等于运算符
        friend bool operator>=(const VeryLongInt& num1, const VeryLongInt& num2);//重载对于VeryLongInt和VeryLongInt的大于等于运算符
        friend bool operator>=(const string &num1, const VeryLongInt &num2);
        //重载"!="运算符
        friend bool operator!=(const VeryLongInt &num1, const long long &num2);//重载对于long long和VeryLongInt的不等于运算符
        friend bool operator!=(const VeryLongInt &num1, const string &num2);//重载对于string和VeryLongInt的不等于运算符
        friend bool operator!=(const VeryLongInt& num1, const VeryLongInt& num2);//重载对于VeryLongInt和VeryLongInt的不等于运算符
        friend bool operator!=(const string &num1, const VeryLongInt &num2);
        //重载+=运算符
        VeryLongInt& operator+=(const VeryLongInt& num);//重载对于VeryLongInt的+=运算符
        VeryLongInt& operator+=(const long long& num);//重载对于long long的+=运算符
        VeryLongInt& operator+=(const string& str);//重载对于string的+=运算符
        //重载-=运算符
        VeryLongInt& operator-=(const VeryLongInt& num);//重载对于VeryLongInt的-=运算符
        VeryLongInt& operator-=(const long long& num);//重载对于long long的-=运算符
        VeryLongInt& operator-=(const string& str);//重载对于string的-=运算符
        //重载*=运算符
        VeryLongInt& operator*=(const VeryLongInt& num);//重载对于VeryLongInt的*=运算符
        VeryLongInt& operator*=(const long long& num);//重载对于long long的*=运算符
        VeryLongInt& operator*=(const string& str);//重载对于string的*=运算符
        //重载/=运算符
        VeryLongInt& operator/=(const long long& num);//重载对于long long的/运算符
        VeryLongInt& operator/=(const string& str);//重载对于string的/运算符
        VeryLongInt& operator/=(const VeryLongInt& num);//重载对于VeryLongInt的/运算符
        //重载%=运算符
        VeryLongInt& operator%=(const VeryLongInt& num);//重载对于VeryLongInt的%运算符
        VeryLongInt& operator%=(const long long& num);//重载对于long long的%运算符
        VeryLongInt& operator%=(const string& str);//重载对于string的%运算符
        //重载"++"运算符
        VeryLongInt operator++();//重载对于VeryLongInt的前置自增运算符
        VeryLongInt operator++(int no_use);//重载对于VeryLongInt的后置自增运算符
        //重载"--"运算符
        VeryLongInt operator--();//重载对于VeryLongInt的前置自减运算符
        VeryLongInt operator--(int no_use);//重载对于VeryLongInt的后置自减运算符
        //重载"+", 取正
        VeryLongInt operator+() const;//重载对于VeryLongInt的取正运算符
        //重载"-"，取负
        VeryLongInt operator-() const;//重载对于VeryLongInt的取负运算符
        //重载"!",取非
        bool operator!() const;//重载对于VeryLongInt的取非运算符
        //重载"<<"运算符
        friend ostream& operator<<(ostream& os,const VeryLongInt& num);//重载对于ostream的输出运算符
        //重载"<<"运算符
        friend istream& operator>>(istream& is,VeryLongInt& num);//重载对于istream的输入运算符
        //获取数字的长度
        unsigned long long getLength() const{
            return digits.length();
        };
        //获取数字的数组
        string getDigits() const{
            return digits;
        };
        int getDigit(size_t index) const{
            return digits[index] - '0';
        };
        void setDigit(size_t index, int digit){
            digits[index] = digit + '0';
        };
        //获取是否为负数
        bool getIsNegative() const{
            return isNegative;
        };
        //设置是否为负数
        void setIsNegative(bool isNegative){
            this->isNegative=isNegative;
        };
        string toString() const;
        int toInt() const;
        long long toLongLong() const;//
    
        //进制转换
        string Hex(bool show_base=true,bool upper_case=false) const;
        string Oct(bool show_base=true,bool upper_case=false) const;
        //进制转换
        VeryLongInt abs() const;//取绝对值
        VeryLongInt pow(long long exp) const;//幂运算
        VeryLongInt sqrt() const;//开平方
        VeryLongInt gcd(const VeryLongInt& num) const;//最大公约数
        VeryLongInt gcd(const long long num) const;//最大公约数
        VeryLongInt gcd(const string& num) const;//最大公约数
        VeryLongInt lcm(const string &num) const;//最小公倍数
        VeryLongInt lcm(const long long num) const;//最小公倍数
        VeryLongInt lcm(const VeryLongInt& num) const;//最小公倍数
        VeryLongInt sum_by_bit() const;//按位求和
        //判断是否为10的整数次幂
        bool isPow10() const{
            return str_is_pow10(digits);
        };
        //判断是否为质数
        friend VeryLongInt randVeryLongInt(size_t num_digits,bool is_negative);//随机生成一个VeryLongInt,可指定正负
        friend VeryLongInt randVeryLongInt(size_t num_digits);//随机生成一个VeryLongInt，正负随机
};

VeryLongInt abs(const VeryLongInt& num);//取绝对值
VeryLongInt pow(const VeryLongInt& base, long long exp);
VeryLongInt gcd(VeryLongInt num1,VeryLongInt num2);//最大公约数
VeryLongInt lcm(VeryLongInt num1,VeryLongInt num2);//最小公倍数
VeryLongInt fac(const VeryLongInt& num);//阶乘

tuple<VeryLongInt, VeryLongInt> divide(const VeryLongInt& dividend, const VeryLongInt& divisor);//除法

void SimpleTestMenu();
void TestMenu();
void ShowMenu();
void ShowTime();
void ShowCopyright();
void ShowHead(bool display_only=false);

bool simple_switch_test_menu(const VeryLongInt &num1,const VeryLongInt &num2);
bool switch_test_menu(VeryLongInt &num1,VeryLongInt &num2);

int CharToDecimal(char c);//将字符转换为十进制数字
string addAndMultiply(const string& number, int multiply, int add);//函数用于将一个十进制字符串乘以一个整数并加上另一个整数
string hex_to_dec(const string hex_str);
string oct_to_dec(const string oct_str);

string dec_to_hex(const string dec_str,bool show_base=true,bool upper_case=false);
string dec_to_oct(const string dec_str,bool show_base=true,bool upper_case=false);

string rand_n_digit_x_random(int n,E_BASE base);

void longlong_constructor_test();
void string_constructor_test();
void two_thousand_constructor_test();
void invalid_constructor_test();
void stuid_id_operation_test(VeryLongInt &id_num,VeryLongInt &stuid_num);
void stuid_id_constructor_test(VeryLongInt &id_num,VeryLongInt &stuid_num);
void test_verylongint_operation(VeryLongInt &num1,VeryLongInt &num2,bool simple_test=true);
void correctness_test();

#endif
