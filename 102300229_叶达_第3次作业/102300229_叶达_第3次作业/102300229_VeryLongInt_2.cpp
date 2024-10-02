/***************************************************************
【文件名】          102300229_VeryLongInt_2.cpp
【功能模块和目的】    VeryLongInt类的函数定义
【开发环境】         Visual Studio Code / MinGW gcc 8.1.0 / c++17
【开发者】           叶达 
****************************************************************/

#include "102300229_VeryLongInt.h"

const string HexDigits="0123456789ABCDEF";//十六进制字符集
const string Signs="+- ";//符号字符集(正号/符号/无符号)

time_t currentTime;
struct tm *localTime;
     
bool is_valid_number_dec(const string& num){//判断字符串是否为有效的十进制数字
    if(num[0]== '-' || num[0]=='+'){
        if(num[1]=='0' && num.length()>2){//除非数字就是0，否则不允许以0开头
            return false;
        }
        for (char digit : num.substr(1)){
            if (digit < '0' || digit > '9')return false;
        }
    }
    else{
        if(num[0]=='0' && num.length()>1){//除非数字就是0，否则不允许以0开头
            return false;
        }
        for (char digit : num){
            if (digit < '0' || digit > '9')return false;
        }
    }
    return true;
}

bool is_valid_number_hex(const string& num){//判断字符串是否为有效的十六进制数字
    if(num[0] == '0' && (num[1] == 'x' || num[1] == 'X') ){
        for (char digit : num.substr(2)){
            if((digit >= '0' && digit <= '9') || (digit >= 'a' && digit <= 'f') || (digit >= 'A' && digit <= 'F'))continue;
            else return false;
        }
    }
    else if( (num[0] == '-' || num[0] == '+') && num[1] == '0' && (num[2] == 'x' || num[2] == 'X')){
        for (char digit : num.substr(3)){
            if((digit >= '0' && digit <= '9') || (digit >= 'a' && digit <= 'f') || (digit >= 'A' && digit <= 'F'))continue;
            else return false;
        }
    }
    else{
        return false;
    }
    return true;
}

bool is_valid_number_oct(const string& num){//判断字符串是否为有效的八进制数字
    if(num[0] == '0'){
        for (char digit : num.substr(1)){
            if (digit < '0' || digit > '7')return false;
        }
    }
    else if((num[0] == '-' || num[0] == '+') && num[1] == '0'){
        for (char digit : num.substr(2)){
            if (digit < '0' || digit > '7')return false;
        }
    }
    else{
        return false;
    }
    return true;
}

bool is_valid_number(const string& num){//判断字符串是否为有效的数字
    if (is_valid_number_dec(num))return true;
    if (is_valid_number_hex(num))return true;
    if (is_valid_number_oct(num))return true;
    return false;
}

void balance_length(string& str_num1, string& str_num2){//调整两个表示长整数的字符串的长度，使得它们的长度相同
    int len1=str_num1.length();
    int len2=str_num2.length();
    if (len1 < len2){
        str_num1=string(len2 - len1, '0') + str_num1;
    }
    else if (len1 > len2){
        str_num2=string(len1 - len2, '0') + str_num2;
    }
    return;
}

void strip_zeros(string& str_num){//去除字符串中无效的前导零
    int len=str_num.length();
    int i=0;
    while (i < len && str_num[i] == '0')i++;
    if (i == len)str_num="0";
    else str_num=str_num.substr(i);
    return;
}

void strip_blank(string& str_num){//去除字符串中首尾的空格
    int len=str_num.length();
    int i=0,j=0;
    while (i < len){
        if (str_num[i] != ' ')
            str_num[j++]=str_num[i];
        i++;
    }
    str_num=str_num.substr(0,j);
    return;
}
void add_trailing_zeroes(string& num, size_t num_zeroes) {
    num += string(num_zeroes, '0');
}

bool str_is_pow10(const string& num){//判断字符串是否为10的整数次幂
    if (num[0] != '1')
        return false;
    for (size_t i = 1; i < num.size(); i++)
        if (num[i] != '0')
            return false;

    return true;    //如果字符串第一个字符不是1，或者后面有非0字符，则不是10的整数次幂
}
VeryLongInt VeryLongInt_pow10(size_t exp) {
    return VeryLongInt("1" + std::string(exp, '0'));
}
//构造函数定义
VeryLongInt::VeryLongInt(const string &str){
    if(str[0] == '-' || str[0] == '+'){//判断是否存在符号
        string str_num=str.substr(1);//去掉符号
        if(is_valid_number_dec(str_num)){
            digits=str_num;
            if(str[0] == '-' && digits!= "0")isNegative=true;//判断符号是否为负号
            else isNegative=false;//不是负号，则为正数
        }
        else if(is_valid_number_hex(str_num)){
            digits=hex_to_dec(str_num);
            if(str[0] == '-' && digits!= "0")isNegative=true;//判断符号是否为负号
            else isNegative=false;//不是负号，则为正数
        }
        else if(is_valid_number_oct(str_num)){
            digits=oct_to_dec(str_num);
            if(str[0] == '-' && digits!= "0")isNegative=true;//判断符号是否为负号
            else isNegative=false;//不是负号，则为正数
        }
        else{
            
            throw Invalid_VeryLongInt(str);
        }
    }
    else{
        if(is_valid_number_dec(str)){
            digits=str;
            isNegative=false;
        }
        else if(is_valid_number_hex(str)){
            digits=hex_to_dec(str);
            isNegative=false;
        }
        else if(is_valid_number_oct(str)){
            
            digits=oct_to_dec(str);
            isNegative=false;
        }
        else{
            throw Invalid_VeryLongInt(str);
        }
    }
}

VeryLongInt::VeryLongInt(const long long &num){
    if(num==LLONG_MIN){
        digits="9223372036854775808";
        isNegative=true;
        return;
    }
    digits=to_string(::abs(num));
    if(num < 0)isNegative=true;
    else isNegative=false;

}

VeryLongInt::VeryLongInt(const VeryLongInt &num){
    digits=num.digits;
    isNegative=num.isNegative;
}
//重载赋值运算符定义
VeryLongInt& VeryLongInt::operator=(const VeryLongInt &num){
    if(this != &num){
        VeryLongInt temp(num);
        digits=temp.digits;
        isNegative=temp.isNegative;
    }
    return *this;
}

VeryLongInt& VeryLongInt::operator=(const string &str){
    VeryLongInt temp(str);
    digits=temp.digits;
    isNegative=temp.isNegative;
    return *this;
}

VeryLongInt& VeryLongInt::operator=(const long long &num){
    VeryLongInt temp(num);
    digits=temp.digits;
    isNegative=temp.isNegative;
    return *this;
}
//重载加法运算符定义
VeryLongInt operator+(const VeryLongInt &num1, const VeryLongInt &num2){
    VeryLongInt result;
    result.digits="";
    string num1_str=num1.digits,num2_str=num2.digits;
    if(num1.isNegative && !num2.isNegative){//num1为负数，num2为正数
        return num2-(-num1);
    }
    else if(!num1.isNegative &&  num2.isNegative){//num1为正数，num2为负数
        return num1-(-num2);
    }
    else{//num1和num2都为正数或者都为负数
        int bit_sum=0,carry=0;//carry表示进位,bit_sum表示当前位的和
        balance_length(num1_str,num2_str);//调整两个数的长度，使得num1_str的长度等于num2_str的长度
        for(long i=num1_str.length()-1;i>=0;i--){
            bit_sum=carry+num1_str[i]-'0'+num2_str[i]-'0';
            result.digits=to_string(bit_sum%10)+result.digits;
            carry=bit_sum/10;
        }
        if(carry){
            result.digits=to_string(carry)+result.digits;
        }
        result.isNegative=num1.isNegative;
        return result;
    }
}

VeryLongInt operator+(const VeryLongInt &num1, const long long &num2){
    return num1+VeryLongInt(num2);
}

VeryLongInt operator+(const long long &num1, const VeryLongInt &num2){
    return VeryLongInt(num1)+num2;
}

VeryLongInt operator+(const VeryLongInt &num1, const string &num2){
    return num1+VeryLongInt(num2);
}

VeryLongInt operator+(const string &num1, const VeryLongInt &num2){
    return VeryLongInt(num1)+num2;
}
//重载减法运算符定义

VeryLongInt operator-(const VeryLongInt &num1, const VeryLongInt &num2){
    VeryLongInt result;
    result.digits="";
    string num1_str=num1.digits,num2_str=num2.digits;
    
    if(num1.isNegative && !num2.isNegative){//num1为负数，num2为正数,num1-num2=num1+(-num2)
         result=num1+(-num2);
         return result;
    }
    else if(!num1.isNegative &&  num2.isNegative){//num1为正数，num2为负数,num1-num2=num1+(-num2)
        result=num1+(-num2);//
        return result;
    }
    else{//num1和num2都为正数或者都为负数
        string abs_large_num,abs_smaller_num;
        if(num1.isNegative && num2.abs() >= num1.abs()){//num1和num2都为负数，但num2绝对值大于等于num1绝对值,num1-num2=abs(num2)-abs(num1)
            result.isNegative=false;
        }
        else if(num1.isNegative && num2.abs() < num1.abs()){//num1和num2都为负数，但num2绝对值小于num1绝对值,num1-num2=-(abs(num1)-abs(num2))
            result.isNegative=true;
        }
        else if(!num1.isNegative && num2.abs() > num1.abs()){//num1和num2都为正数，但num2绝对值大于num1绝对值,num1-num2=abs(num1)-abs(num2)
            result.isNegative=true;
        }
        else if(!num1.isNegative && num2.abs() <= num1.abs()){//num1和num2都为正数，但num2绝对值小于等于num1绝对值,num1-num2=abs(num1)-abs(num2)
            result.isNegative=false;
        }
        //abs(num1-num2)=abs(large_num-smaller_num),上述判断确定了符号位，现在只需要确定结果的绝对值
        if(num1.abs() >= num2.abs()){
            abs_large_num=num1.digits;
            abs_smaller_num=num2.digits;
        }
        else{
            abs_large_num=num2.digits;
            abs_smaller_num=num1.digits;
        }
        balance_length(abs_large_num,abs_smaller_num);//调整两个数的长度，使得abs_large_num的长度等于abs_smaller_num的长度
        int diff=0;//diff表示两数相减的差值，diff_carry表示退位
        long i,j;
        for(i=abs_large_num.length()-1;i >= 0;i--){
            diff=abs_large_num[i]-abs_smaller_num[i];
            if (diff < 0) {
                for (j=i-1;j >= 0;j--) {//此处发生借位，从i-1开始找第一个不是0的数，即能够借位的位置
                    if (abs_large_num[j] != '0') {
                        abs_large_num[j]--;    // 如果不是0，则减正常减1
                        break;
                    }
                }
                //这时候j是借出1的位置，我们要把不能借1的0都变成9，所以要先往低位移动移一位（j++），到不能借1开始的位置
                j++;
                while (j != i) {//所有0都不能借位，都要往高位借位，所以我们要把所有不能结位的0都变成9
                    abs_large_num[j] = '9'; 
                    j++;
                }
                diff += 10;   // add the borrow
            }
            result.digits=to_string(diff) + result.digits;
        }
        strip_zeros(result.digits);
        return result;
    }
    
}

VeryLongInt operator-(const VeryLongInt &num1, const long long &num2){
    return num1-VeryLongInt(num2);
}

VeryLongInt operator-(const long long &num1, const VeryLongInt &num2){
    return VeryLongInt(num1)-num2;
}

VeryLongInt operator-(const VeryLongInt &num1, const string &num2){
    return num1-VeryLongInt(num2);
}

VeryLongInt operator-(const string &num1, const VeryLongInt &num2){
    return VeryLongInt(num1)-num2;
}
//重载“*”运算符定义

VeryLongInt operator*(const VeryLongInt &num1, const VeryLongInt &num2){
    VeryLongInt product;
    if(num1.digits=="0" || num2.digits=="0")return VeryLongInt("0");
    else if(num1.digits=="1")return num2;
    else if(num2.digits=="1")return num1;
    else if(num1.abs() <= FLOOR_SQRT_LLONG_MAX && num2.abs() <= FLOOR_SQRT_LLONG_MAX){//如果两个数的绝对值都小于等于2^63-1，即在long long范围内，则直接用long long乘法
        return VeryLongInt(stoll(num1.digits)*stoll(num2.digits));
    }
    else if(num1.isPow10()){//有关10的整数幂的运算，直接添加相应次数的0
        string str_zeros(num1.digits.length()-1,'0');
        return VeryLongInt(num2.digits+str_zeros);
    }
    else if(num2.isPow10()){
        string str_zeros(num2.digits.length()-1,'0');
        return VeryLongInt(num1.digits+str_zeros);
    }
    else{
        int bit_mul=0,carry=0,pow_10=-1;
        string temp_num="";

        for(long i=num2.digits.length()-1;i>=0;i--){
            temp_num="";
            pow_10++;
            for(long j=num1.digits.length()-1;j>=0;j--){
                bit_mul=carry+(num2.digits[i]-'0')*(num1.digits[j]-'0');
                carry=bit_mul/10;
                temp_num=to_string(bit_mul%10)+temp_num;
            }
            if(carry){
                temp_num=to_string(carry)+temp_num;
                carry=0;
            }
            temp_num=temp_num+string(pow_10,'0');
            
            product=product+VeryLongInt(temp_num);
        }
    }
    strip_zeros(product.digits);
    product.isNegative=num1.isNegative ^ num2.isNegative;//异号则为负数
    return product;
}

VeryLongInt operator*(const VeryLongInt &num1, const long long &num2){
    return num1*VeryLongInt(num2);
}

VeryLongInt operator*(const long long &num1, const VeryLongInt &num2){
    return VeryLongInt(num1)*num2;
}

VeryLongInt operator*(const VeryLongInt &num1, const string &num2){
    return num1*VeryLongInt(num2);
}

VeryLongInt operator*(const string &num1, const VeryLongInt &num2){
    return VeryLongInt(num1)*num2;
}
//重载“/”运算符定义
VeryLongInt operator/(const VeryLongInt &num1, const VeryLongInt &num2){
    VeryLongInt result;
    if(num2.digits=="0")throw invalid_argument("Divide by zero!");//除数为0
    else if(num1.digits=="0")return VeryLongInt("0");//被除数为0
    else if(num1.abs() < num2.abs())return VeryLongInt("0");//被除数小于除数
    else if(num1.abs() <= LLONG_MAX && num2.abs() <= LLONG_MAX){//如果两个数的绝对值都小于等于2^63-1，即在long long范围内，则直接用long long除法
        return VeryLongInt(stoll(num1.digits)/stoll(num2.digits));
    }
    else if(num1.abs()==num2.abs()){
        result=1;
        result.isNegative=num1.isNegative ^ num2.isNegative;
        return result;
    }
    else if(str_is_pow10(num2.digits)){//num1长度大于等于num2长度，且num2为10的整数幂，则直接除以10的整数幂
        result=num1.digits.substr(0,num1.digits.length()-num2.digits.length()+1);
        result.isNegative=num1.isNegative ^ num2.isNegative;
        return result;
    }
    else{
        VeryLongInt abs_dividend=num1.abs();
        VeryLongInt abs_divisor=num2.abs();
        result.digits = "";    
        VeryLongInt chunk, chunk_result, chunk_remainder;
        size_t chunk_index = 0;
        chunk_remainder.digits = abs_dividend.digits.substr(chunk_index, abs_divisor.digits.size() - 1);
        chunk_index = abs_divisor.digits.size() - 1;//chunk_index表示当前处理的chunk的起始位置
        while (chunk_index < abs_dividend.digits.size()){//处理每一段
            chunk.digits = chunk_remainder.digits.append(1, abs_dividend.digits[chunk_index]);
            chunk_index++;
            while (chunk < abs_divisor){
                result.digits += "0";
                if (chunk_index < abs_dividend.digits.size()){
                    chunk.digits.append(1, abs_dividend.digits[chunk_index]);
                    chunk_index++;
                }
                else
                    break;
            }
            if (chunk == abs_divisor){
                result.digits += "1";
                chunk_remainder = 0;
            }
            else if (chunk > abs_divisor){
                strip_zeros(chunk.digits);
                tie(chunk_result, chunk_remainder) = divide(chunk, abs_divisor);
                result.digits += chunk_result.digits;
            }
        }
        strip_zeros(result.digits);
        result.isNegative=num1.isNegative ^ num2.isNegative;
        return result;
    }
}

VeryLongInt operator/(const VeryLongInt &num1, const long long &num2){
    return num1/VeryLongInt(num2);
}

VeryLongInt operator/(const long long &num1, const VeryLongInt &num2){
    return VeryLongInt(num1)/num2;
}

VeryLongInt operator/(const VeryLongInt &num1, const string &num2){
    return num1/VeryLongInt(num2);
}

VeryLongInt operator/(const string &num1, const VeryLongInt &num2){
    return VeryLongInt(num1)/num2;
}
//重载“%”运算符定义
VeryLongInt operator%(const VeryLongInt &num1, const VeryLongInt &num2){
    VeryLongInt result;
    if(num2.digits=="0")throw invalid_argument("Divide by zero!");
    else if(num1.digits=="0" || num2.digits=="1")return VeryLongInt("0");
    else if(num1.abs() < num2.abs())return num1;
    else if(num1.abs() <= LLONG_MAX && num2.abs() <= LLONG_MAX){//如果两个数的绝对值都小于等于2^63-1，即在long long范围内，则直接用long long除法
        return VeryLongInt(stoll(num1.digits)%stoll(num2.digits));
    }
    else if(num1.abs()==num2.abs()){
        return 0;
    }
    else if(str_is_pow10(num2.digits)){//num1长度大于等于num2长度，且num2为10的整数幂，则直接取模10的整数幂
        return num1.digits.substr(num1.digits.length()-num2.digits.length()+1);
    }
    else{
        VeryLongInt quotient=num1/num2;
        result=num1-quotient*num2;
        return result;
    }
}

VeryLongInt operator%(const VeryLongInt &num1, const long long &num2){
    return num1%VeryLongInt(num2);
}

VeryLongInt operator%(const long long &num1, const VeryLongInt &num2){
    return VeryLongInt(num1)%num2;
}

VeryLongInt operator%(const VeryLongInt &num1, const string &num2){
    return num1%VeryLongInt(num2);
}

VeryLongInt operator%(const string &num1, const VeryLongInt &num2){
    return VeryLongInt(num1)%num2;
}   
//重载"+",取
VeryLongInt VeryLongInt::operator+() const{
    return *this;
}

//重载"-",取相反数数
VeryLongInt VeryLongInt::operator-() const{
    VeryLongInt result(*this);
    if(result.digits!="0"){
        result.isNegative=!result.isNegative;
    }
    return result;
}

// abs() 成员函数，返回绝对值
VeryLongInt VeryLongInt::abs() const{
    VeryLongInt result(*this);
    result.isNegative=false;
    return result;
}

//abs普通函数，返回绝对值
VeryLongInt abs(const VeryLongInt &num){
    return num.abs();
}

//重载VeryLongInt间的比较运算符定义
bool operator==(const VeryLongInt &num1, const VeryLongInt &num2){
    if(num1.isNegative && !num2.isNegative)return false;
    else if(!num1.isNegative &&  num2.isNegative)return false;
    else{
        return num1.digits==num2.digits;
    }
}
bool operator<(const VeryLongInt &num1, const VeryLongInt &num2){
    if(num1.isNegative && !num2.isNegative)return true;
    else if(!num1.isNegative &&  num2.isNegative)return false;
    else if(num1.isNegative &&  num2.isNegative){
        string num1_str=num1.digits,num2_str=num2.digits;
        balance_length(num1_str,num2_str);
        if(num1_str<num2_str)return false;
        return true;
        
    }
    else{
        string num1_str=num1.digits,num2_str=num2.digits;
        balance_length(num1_str,num2_str);
        if(num1_str<num2_str)return true;
        return false;
    }
}

bool operator>(const VeryLongInt &num1, const VeryLongInt &num2){
    return !(num1<num2 || num1==num2);
}



bool operator<=(const VeryLongInt &num1, const VeryLongInt &num2){
    return !(num1>num2);
}


bool operator>=(const VeryLongInt &num1, const VeryLongInt &num2){
    return !(num1<num2);
}

bool operator!=(const VeryLongInt &num1, const VeryLongInt &num2){
    return !(num1==num2);
}

//重载VeryLongInt和long long间的比较运算符定义
bool operator==(const VeryLongInt &num1, const long long &num2){
    return num1==VeryLongInt(num2);
}

bool operator<(const VeryLongInt &num1, const long long &num2){
    return num1<VeryLongInt(num2);
}


bool operator>(const VeryLongInt &num1, const long long &num2){
    return num1>VeryLongInt(num2);
}

bool operator<=(const VeryLongInt &num1, const long long &num2){
    return num1<=VeryLongInt(num2);
}

bool operator>=(const VeryLongInt &num1, const long long &num2){
    return num1>=VeryLongInt(num2);
}

bool operator!=(const VeryLongInt &num1, const long long &num2){
    return num1!=VeryLongInt(num2);
}



//重载VeryLongInt和string间的比较运算符定义
bool operator==(const VeryLongInt &num1, const string &str){
    return num1==VeryLongInt(str);
}

bool operator==(const string &str, const VeryLongInt &num1){
    return VeryLongInt(str)==num1;
}

bool operator<(const VeryLongInt &num1, const string &str){
    return num1<VeryLongInt(str);
}

bool operator<(const string &str, const VeryLongInt &num1){
    return VeryLongInt(str)<num1;
}


bool operator>(const VeryLongInt &num1, const string &str){
    return num1>VeryLongInt(str);
}

bool operator>(const string &str, const VeryLongInt &num1){
    return VeryLongInt(str)>num1;
}

bool operator<=(const VeryLongInt &num1, const string &str){
    return num1<=VeryLongInt(str);
}

bool operator<=(const string &str, const VeryLongInt &num1){
    return VeryLongInt(str)<=num1;
}

bool operator>=(const VeryLongInt &num1, const string &str){
    return num1>=VeryLongInt(str);
}

bool operator>=(const string &str, const VeryLongInt &num1){
    return VeryLongInt(str)>=num1;
}

bool operator!=(const VeryLongInt &num1, const string &str){
    return num1!=VeryLongInt(str);
}

bool operator!=(const string &str, const VeryLongInt &num1){
    return VeryLongInt(str)!=num1;
}

//重载+=运算符定义
VeryLongInt& VeryLongInt::operator+=(const VeryLongInt &num){
    *this=*this+num;
    return *this;
}
VeryLongInt& VeryLongInt::operator+=(const long long &num){
    *this=*this+num;
    return *this;
}
VeryLongInt& VeryLongInt::operator+=(const string &num){
    *this=*this+num;
    return *this;
}

//重载-=运算符定义
VeryLongInt& VeryLongInt::operator-=(const VeryLongInt &num){
    *this=*this-num;
    return *this;
}
VeryLongInt& VeryLongInt::operator-=(const long long &num){
    *this=*this-num;
    return *this;
}

VeryLongInt& VeryLongInt::operator-=(const string &num){
    *this=*this-num;
    return *this;
}

//重载*=运算符定义
VeryLongInt& VeryLongInt::operator*=(const VeryLongInt &num){
    *this=*this*num;
    return *this;
}

VeryLongInt& VeryLongInt::operator*=(const long long &num){
    *this=*this*num;
    return *this;
}

VeryLongInt& VeryLongInt::operator*=(const string &num){
    *this=*this*num;
    return *this;
}

//重载 /= 运算符定义
VeryLongInt& VeryLongInt::operator/=(const VeryLongInt &num){
    *this=*this/num;
    return *this;
}

VeryLongInt& VeryLongInt::operator/=(const long long &num){    
    *this=*this/num;
    return *this;
}

VeryLongInt& VeryLongInt::operator/=(const string &num){
    *this=*this/num;
    return *this;
}


//重载%=运算符定义
VeryLongInt& VeryLongInt::operator%=(const VeryLongInt &num){
    *this=*this%num;
    return *this;
}


VeryLongInt& VeryLongInt::operator%=(const long long &num){
    *this=*this%num;
    return *this;
}


VeryLongInt& VeryLongInt::operator%=(const string &num){
    *this=*this%num;
    return *this;
}

//重载<<运算符定义
ostream& operator<<(ostream& os, const VeryLongInt& num){
    if(num.isNegative)os<<'-';
    //四位一逗号输出
    int count=0;
    string temp_str="";
    for(int i=num.digits.length()-1;i>=0;i--){
        temp_str=num.digits[i]+temp_str;
        count++;
        if(count%4==0 && i!=0)temp_str=","+temp_str;
    }
    os<<temp_str;   
    return os;
}

//重载>>运算符定义
istream& operator>>(istream& is, VeryLongInt& num){
    string str;
    is>>str;
    num=VeryLongInt(str);
    return is;
}
//在特定位置上加数字
void add_at_pos(vector<char> &number, int index, unsigned char x){
    if (x == 0){
        return;
    }
    int size = number.size();
    if (index >= size) {
        number.insert(number.end(), index - size + 1, 0);
        size = index + 1;
    }
    number[index] += x;
    while (index < size && number[index] >= 10){
        if (index + 1 == size) {
            number.emplace_back(number[index] / 10);
            size++;
        } else {
            number[index + 1] += number[index] / 10;
        }
        number[index] %= 10;
        index++;
    }
}
//重载“++”
VeryLongInt VeryLongInt::operator++(){
    return *this=*this+1;
}
VeryLongInt VeryLongInt::operator++(int no_use){
    VeryLongInt temp(*this);
    *this=*this+1;
    return temp;
}
//重载“--”
VeryLongInt VeryLongInt::operator--(){
    return *this=*this-1;
}
VeryLongInt VeryLongInt::operator--(int no_use){
    VeryLongInt temp(*this);
    *this=*this-1;
    return temp;
}

//长整数求最大公约数
VeryLongInt gcd(VeryLongInt num1, VeryLongInt num2){
    if(num1<num2)return gcd(num2,num1);
    VeryLongInt temp;
    while(num2!=0){
        temp=num1%num2;
        num1=num2;
        num2=temp;
    }
    return num1;
}

VeryLongInt VeryLongInt::gcd(const VeryLongInt& num) const{
    return ::gcd(*this,num);
}

VeryLongInt VeryLongInt::gcd(const long long num) const{
    return ::gcd(*this,VeryLongInt(num));
}

VeryLongInt VeryLongInt::gcd(const string& num) const{
    return ::gcd(*this,VeryLongInt(num));
}

//长整数求最小公倍数
VeryLongInt lcm(VeryLongInt num1, VeryLongInt num2){
    return num1*num2/gcd(num1,num2);
}

VeryLongInt VeryLongInt::lcm(const VeryLongInt& num) const{
    return ::lcm(*this,num);
}

VeryLongInt VeryLongInt::lcm(const long long num) const{
    return ::lcm(*this,VeryLongInt(num));
}

VeryLongInt VeryLongInt::lcm(const string& num) const{
    return ::lcm(*this,VeryLongInt(num));
}

//幂运算
VeryLongInt pow(const VeryLongInt& base, long long exp) {
    if (exp < 0){
        if (base == 0)
            throw logic_error("Cannot divide by zero");
        return abs(base) == 1 ? base : 0;
    }
    if (exp == 0){
        if (base == 0)
            throw logic_error("Zero cannot be raised to zero");
        return 1;
    }
    VeryLongInt result = base, result_odd = 1;
    while (exp > 1){
        if (exp % 2)
            result_odd *= result;
        result *= result;
        exp /= 2;
    }
    return result * result_odd;
}

VeryLongInt VeryLongInt::pow(long long exp) const{
    return ::pow(*this,exp);
}
//开方运算
VeryLongInt sqrt(const VeryLongInt& num) {
    if (num < 0)
        throw invalid_argument("Cannot compute square root of a negative integer");
    if (num == 0)
        return 0;
    else if (num < 4)
        return 1;
    else if (num < 9)
        return 2;
    else if (num < 16)
        return 3;
    VeryLongInt sqrt_prev = -1;
    VeryLongInt sqrt_current = VeryLongInt_pow10(num.toString().length()/2 - 1);
    while (abs(sqrt_current - sqrt_prev) > 1) {
        sqrt_prev = sqrt_current;
        sqrt_current = (num / sqrt_prev + sqrt_prev) / 2;
    }
    return sqrt_current;
}

VeryLongInt VeryLongInt::sqrt() const{
    return ::sqrt(*this);
}
//转化为字符串
string VeryLongInt::toString() const{
    if(isNegative)return "-" + digits;
    else return digits;
} 
//转化为long long
long long VeryLongInt::toLongLong() const{
    if(*this<LLONG_MIN)
        throw out_of_range("toLongLong_Error: Out of range:"+this->toString()+"\nLLONG_MIN:-9223372036854775808\n");
    if(*this>LLONG_MAX){
        throw out_of_range("toLongLong_Error: Out of range:"+this->toString()+"\nLLONG_MAX:9223372036854775807\n");
    }
    if(*this<0)return -stoll(digits);
    else return stoll(digits);
}
//转化为int
int VeryLongInt::toInt() const{
    if(*this<INT_MIN)
        throw out_of_range("toInt_Error: Out of range:"+this->toString()+"\nINT_MIN:-2147483648\n");
    if(*this>INT_MAX){
        throw out_of_range("toInt_Error: Out of range:"+this->toString()+"\nINT_MAX:2147483647\n");
    }
    if(*this<0)return -stoll(digits);
    else return stoll(digits);
}

//重载！
bool VeryLongInt::operator!() const{
    return digits=="0";
}

//转化为double




//生成指定正负的n位VeryLongInt型的数字
VeryLongInt randVeryLongInt(size_t num_digits,bool is_negative){
    chrono::high_resolution_clock::time_point seed = std::chrono::high_resolution_clock::now();
    default_random_engine rand_generator(seed.time_since_epoch().count());
    if (num_digits == 0){    
        num_digits = 1 + rand_generator() % MAX_RANDOM_LENGTH;//随机生成1到MAX_RANDOM_LENGTH位的数字
    }
    VeryLongInt verylong_rand;
    verylong_rand.digits = "";   
    verylong_rand.digits += to_string(1 + rand_generator() % 9);//保证第一个数字不为0
    while (verylong_rand.digits.size() < num_digits)
        verylong_rand.digits += to_string(rand_generator());
    if (verylong_rand.digits.size() != num_digits)
        verylong_rand.digits.erase(num_digits);   // 保证数字长度为num_digits
    if (is_negative)
        verylong_rand.isNegative = true;
    return verylong_rand;
}
//生成随机VeryLongInt型的数字，随机正负
VeryLongInt randVeryLongInt(size_t num_digits){
    string rand_str=rand_n_digit_x_random(num_digits,Dec);
    return VeryLongInt(rand_str);
}
//生成随机long long型的数字
long long randLongLong(){
    chrono::high_resolution_clock::time_point seed = std::chrono::high_resolution_clock::now();
    default_random_engine rand_generator(seed.time_since_epoch().count());
    return rand_generator() % LLONG_MAX;
}
//生成随机n位的x进制随机字符串
string rand_n_digit_x_random(int n,E_BASE base){
    chrono::high_resolution_clock::time_point seed = std::chrono::high_resolution_clock::now();
    default_random_engine rand_generator(seed.time_since_epoch().count());
    string result;
    if(base==Dec){
        result = "";
        if(n!=1){//若多于1位保证第一个数字不为0
            result+=to_string(1+rand_generator()%9);
        }
        else{//若只有1位则直接生成0-9之间的随机数
            result+=to_string(rand_generator()%10);
        }
        for (int i = 1; i < n; i++) {
            result+=to_string(rand_generator()%10);
        }
    }
    else if(base==Hex){
        result = "0x";
        for(int i=0;i<n;i++){
            result+=HexDigits[rand_generator()%16];
        }
    }
    else if(base==Oct){
        result = "0";
        for(int i=0;i<n;i++){
            result+=to_string(rand_generator()%8);
        }
    }
    else{
        throw invalid_argument("rand_n_digit_x_random_Error: Invalid base!");
    }
    result=Signs[rand_generator()%3]+result;
    strip_blank(result);
    return result;
}
tuple<VeryLongInt, VeryLongInt> divide(const VeryLongInt& dividend, const VeryLongInt& divisor){
    // 定义商和余数的变量
    VeryLongInt quotient, remainder, temp;
    // 把除数赋值给temp
    temp = divisor;
    // 初始化商为1
    quotient = 1;
    // 当temp小于被除数时，商加1，temp加上除数
    while (temp < dividend){
        quotient++;
        temp += divisor;
    }
    // 当temp大于被除数时，商减1，余数为被除数减去temp减去除数
    if (temp > dividend){
        quotient--;
        remainder = dividend - (temp - divisor);
    }
    // 返回一个元组，包含商和余数
    return make_tuple(quotient, remainder);
}

void ShowMenu(){//菜单函数
    printf("                                          巨型整数类功能菜单                                             ");
	printf("\n*******************************************************************************************************\n");
	printf("*                 A.测试通过long long类型构造VeryLongInt类\n");
	printf("*                 B.测试通过字符串类型构造VeryLongInt类\n");
	printf("*                 C.测试随机构造从1000位到100000位的VeryLongInt对象\n");
	printf("*                 D.测试非法构造\n");
	printf("*                 E.以学号和身份证号为基础构造巨型整数并进行运算(包括算术运算,关系运算,复合赋值运算)\n");
    printf("*                 F.测试93位操作数的构造及各种运算(包括算术运算,关系运算,复合赋值运算)\n");
    printf("*                 G.测试用8,16进制字符串构造巨型整数并测试进制转化\n");
    printf("*                 H.测试++,--运算符\n");
    printf("*                 I.测试类型转化\n");
    printf("*                 J.测试取\"-\"和\"+\"的操作符以及拷贝构造\n");
    printf("*                 K.测试 VeryLongInt类型 与  long long类型 间的运算(包括算术运算,关系运算,复合赋值运算)\n");
	printf("*                 L.测试 VeryLongInt类型 与  string类型 间的运算(包括算术运算,关系运算,复合赋值运算)\n");
    printf("*                 M.测试0的正负性,以及与0的运算和异常\n");
    printf("*                 N.自定义输入构造巨型整数并进行运算(测试重载的\">>\"运算符)\n");
    printf("*                 O.随机构造n位巨型整数并进行运算(包括算术运算,关系运算,复合赋值运算)\n");
    printf("*                 P.乘方测试\n");
    printf("*                 Q.连续赋值测试\n");
    printf("*                 R.测试求最小公倍数和最大公约数\n");
    printf("*                 S.测试求开方\n");
    printf("*                 T.退出程序\n");
    printf("*******************************************************************************************************  \n");
	printf("请输入选项编号:<输入范围内的字母>\n");
}
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
    printf("\n*******************************************************************************\n");
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
//字符串进制转换
int CharToDecimal(char c){
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
    if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
    return 0;
}
// 函数用于将一个十进制字符串乘以一个整数并加上另一个整数
string addAndMultiply(const string& number, int multiply, int add){
    string result;
    VeryLongInt num(number);
    num=num*multiply+add;
    result=num.toString();
    return result;
}
// 转换16进制字符串为10进制字符串
string hex_to_dec(const string hex){
    string temp=hex;
    if(hex[0]=='+' || hex[0]=='-'){
        temp=hex.substr(1);    
    }
    if(is_valid_number_hex(temp)){
        string result = "0";
        for (char c : temp.substr(2)){
            int currentDigit = CharToDecimal(c);
            result = addAndMultiply(result, 16, currentDigit);
        }
        return result;
    }
    else{
        throw invalid_argument("hex_to_dec_Error: Invalid hexadecimal number!");
    }
}
//8进制字符串转换为10进制字符串
string oct_to_dec(const string oct){
    string temp=oct;
    if(oct[0]=='+' || oct[0]=='-'){
        temp=oct.substr(1);    
    }
    if(is_valid_number_oct(temp)){
        string result = "0";
        for (char c : temp.substr(1)) {
            int currentDigit = CharToDecimal(c);
            result = addAndMultiply(result, 8, currentDigit);
        }
        return result;
    }
    else{
        throw invalid_argument("oct_to_dec_Error: Invalid octal number!");
    }
}
//10进制字符串转换为16进制字符串
string dec_to_hex(const string dec,bool show_base,bool upper_case){
    string temp=dec;
    if(dec[0]=='+' || dec[0]=='-'){
        temp=dec.substr(1);    
    }
    if(is_valid_number_dec(temp)){
        VeryLongInt num(temp);
        string result = "";
        while(num!=0){
            long long remainder = (num%16).toLongLong();
            char bit =upper_case?HexDigits[remainder]:tolower(HexDigits[remainder]);
            result = bit + result;
            num = num/16;
        }
        if(show_base){
            result = "0x" + result;
        }
        if(result==""){
            result="0";
        }
        if(dec[0]=='-'){
            result="-"+result;
        }
        return result;
    }
    else{
        throw invalid_argument("dec_to_hex_Error: Invalid decimal number!");
    }
}
//10进制字符串转换为8进制字符串
string dec_to_oct(const string dec,bool show_base,bool upper_case){
    string temp=dec;
    if(dec[0]=='+' || dec[0]=='-'){
        temp=dec.substr(1);    
    }
    if(is_valid_number_dec(temp)){
        VeryLongInt num(temp);
        string result = "";
        while(num!=0){
            long long remainder = (num%8).toLongLong();
            char bit =upper_case?HexDigits[remainder]:tolower(HexDigits[remainder]);
            result = bit + result;
            num = num/8;
        }
        if(show_base){
            result = "0" + result;
        }
        if(result==""){
            result="0";
        }
        if(dec[0]=='-'){
            result="-"+result;
        }
        return result;
    }
    else{
        throw invalid_argument("dec_to_oct_Error: Invalid decimal number!");
    }
}
//10进制VeryLongInt转换为16进制字符串
string VeryLongInt::Hex(bool show_base,bool upper_case) const{
    if(isNegative)return "-" + dec_to_hex(digits,show_base,upper_case);
    else return dec_to_hex(digits);
}
//10进制VeryLongInt转换为8进制字符串
string VeryLongInt::Oct(bool show_base,bool upper_case) const{
    if(isNegative)return "-" + dec_to_oct(digits,show_base,upper_case);
    else return dec_to_oct(digits);
}

void longlong_constructor_test(){//测试通过long long类型构造VeryLongInt类
     // 测试通过 long long 类型构造 VeryLongInt 类
    VeryLongInt num1(LLONG_MAX);
    cout << "执行 VeryLongInt(LLONG_MAX) 构造函数成功，结果为：" << "num1=" << num1 << endl;
    cout << "num1==LLONG_MAX: " << (num1 == LLONG_MAX) << endl;
    
    VeryLongInt num2(LLONG_MIN);
    cout << "执行 VeryLongInt(LLONG_MIN) 构造函数成功，结果为：" << "num2=" << num2 << endl;
    cout << "num2==LLONG_MIN: " << (num2 == LLONG_MIN) << endl;
    
    VeryLongInt num3(-0x12345abcdefll);
    cout << "执行 VeryLongInt(-0x12345abcdefll) 构造函数成功，结果为：" << "num3=" << num3 << endl;
    cout << "num3==-0x12345abcdefll: " << (num3 == -0x12345abcdefll) << endl;
    
    VeryLongInt num4(+027654321ll);
    cout << "执行 VeryLongInt(+027654321ll) 构造函数成功，结果为：" << "num4=" << num4 << endl;
    cout << "num4==+027654321ll: " << (num4 == +027654321ll) << endl;
    VeryLongInt num5(0);
    cout << "执行 VeryLongInt(0) 构造函数成功，结果为：" << "num5=" << num5 << endl;
    cout << "num5==0: " << (num5 == 0) << endl;
    
    VeryLongInt num6(+0);
    cout << "执行 VeryLongInt(+0) 构造函数成功，结果为：" << "num6=" << num6 << endl;
    cout << "num6==0: " << (num6 == 0) << endl;
    
    VeryLongInt num7(-0);
    cout << "执行 VeryLongInt(-0) 构造函数成功，结果为：" << "num7=" << num7 << endl;
    cout << "num7==0: " << (num7 == 0) << endl;
    
    VeryLongInt num8(+0x0000);
    cout << "执行 VeryLongInt(+0x0000) 构造函数成功，结果为：" << "num=" << num8 << endl;
    cout << "num8==0: " << (num8 == 0) << endl;
    
    VeryLongInt num9(-0x0000);
    cout << "执行 VeryLongInt(-0x0000) 构造函数成功，结果为：" << "num9=" << num9 << endl;
    cout << "num9==0: " << (num9 == 0) << endl;
    
    VeryLongInt num10(+00000);
    cout << "执行 VeryLongInt(+00000) 构造函数成功，结果为：" << "num10=" << num10 << endl;
    cout << "num10==0: " << (num10 == 0) << endl;
    
    VeryLongInt num11(-00000);
    cout << "执行 VeryLongInt(-00000) 构造函数成功，结果为：" << "num11=" << num11 << endl;
    cout << "num11==0: " << (num11 == 0) << endl;

    VeryLongInt num12(1234567890123456789ll);
    cout << "执行 VeryLongInt(1234567890123456789ll) 构造函数成功，结果为：" << "num12=" << num12 << endl;
    cout << "num12==1234567890123456789ll: " << (num12 == 1234567890123456789ll) << endl;

    cout<<"开始随机生成100000个随机long long型的数进行测试...<如果出现构造失败则会停止测试>"<<endl;
    cout<<"<按任意键开始测试...>";
    getch();
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            long long num=randLongLong();
            cout<<"执行 num=(randLongLong())"<<endl;
            VeryLongInt num4(num);
            cout << "执行 VeryLongInt num4(num) 构造函数成功，结果为：\n" << "num4=" << num4 << endl;
            cout<<"num="<<num<<endl;
            cout << "num4==num: " << (num4 == num) << endl;
            if(num4!=num){
                cout<<"构造失败,num4!=num"<<endl;
                cout<<"<测试失败,按任意键继续>"<<endl;
                getchar();
                return;
            }
        }
        system("cls");
    }
    cout<<"随机生成100000个随机long long型的数测试结束"<<endl;
    cout<<"<测试无误,按任意键继续>"<<endl;
    getch();
    return;
}

void string_constructor_test(){//测试通过字符串类型构造VeryLongInt类
    // 测试通过字符串类型构造 VeryLongInt 类
    cout<<"<开始测试通过字符串类型构造 VeryLongInt 类...>"<<endl;
    cout<<"<按任意键开始测试...>"<<endl;
    getch();
    cout<<"<测试0字符串构造的正确性>"<<endl;
    
    VeryLongInt num1("0");
    cout << "执行 VeryLongInt(\"0\") 构造函数成功，结果为：" << "num1=" << num1 << endl;
    cout << "num1==0: " << (num1 == 0) << endl;
    cout << "num1.isNegative: " << (num1.getIsNegative()) << endl;
    VeryLongInt num2("+0");
    cout << "执行 VeryLongInt(\"+0\") 构造函数成功，结果为：" << "num2=" << num2 << endl;
    cout << "num2==0: " << (num2 == 0) << endl;
    cout << "num2.isNegative: " << (num2.getIsNegative()) << endl;
    VeryLongInt num3("-0");
    cout << "执行 VeryLongInt(\"-0\") 构造函数成功，结果为：" << "num3=" << num3 << endl;
    cout << "num3==0: " << (num3 == 0) << endl;
    cout << "num3.isNegative: " << (num3.getIsNegative()) << endl;

    VeryLongInt num4("-00000");
    cout << "执行 VeryLongInt(\"00000\") 构造函数成功，结果为：" << "num4=" << num4 << endl;
    cout << "num4==0: " << (num4 == 0) << endl;
    cout << "num4.isNegative: " << (num4.getIsNegative()) << endl;
    
    VeryLongInt num5("+00000");
    cout << "执行 VeryLongInt(\"+00000\") 构造函数成功，结果为：" << "num5=" << num5 << endl;
    cout << "num5==0: " << (num5 == 0) << endl;
    cout << "num5.isNegative: " << (num5.getIsNegative()) << endl;

    VeryLongInt num6("-0x0000");
    cout << "执行 VeryLongInt(\"-0x0000\") 构造函数成功，结果为：" << "num6=" << num6 << endl;
    cout << "num6==0: " << (num6 == 0) << endl;
    cout << "num6.isNegative: " << (num6.getIsNegative()) << endl;

    VeryLongInt num7("+0X0000");
    cout << "执行 VeryLongInt(\"+0X0000\") 构造函数成功，结果为：" << "num7=" << num7 << endl;
    cout << "num7==0: " << (num7 == 0) << endl;
    cout << "num7.isNegative: " << (num7.getIsNegative()) << endl;

    cout<<"<开始随机生成100个 10位 10进制 字符串进行测试...>"<<endl;
    cout<<"<按任意键开始测试...>"<<endl;
    getch();
    for(int i=0;i<100;i++){
        string num=rand_n_digit_x_random(10,Dec);
        cout <<"执行 num=rand_n_digit_x_random(10,Dec)"<<endl;
        VeryLongInt num5(num);
        cout << "执行 VeryLongInt num5(num) 构造函数成功，结果为：\n" << "num5=" << num5 << endl;
        cout <<"num="<<num<<endl;
        cout << "num5==num: " << (num5 == num) << endl;
        if(num5!=num){
            cout<<"构造失败,num5!=VeryLongInt(num)"<<endl;
            cout<<"<测试失败,按任意键继续>"<<endl;
            getchar();
            return;
        }
    }

    cout<<"<开始随机生成100个 100位 10进制 字符串进行测试...>"<<endl;
    cout<<"<按任意键开始测试...>"<<endl;
    getch();
    for(int i=0;i<100;i++){
        string num=rand_n_digit_x_random(100,Dec);
        cout <<"执行 num=rand_n_digit_x_random(100,Dec)"<<endl;
        VeryLongInt num6(num);
        cout << "执行 VeryLongInt num6(num) 构造函数成功，结果为：\n" << "num6=" << num6 << endl;
        cout <<"num="<<num<<endl;
        cout << "num6==num: " << (num6 == num) << endl;
        if(num6!=num){
            cout<<"构造失败,num6!=VeryLongInt(num)"<<endl;
            cout<<"<测试失败,按任意键继续>"<<endl;
            getchar();
            return;
        }
    }

    cout<<"<开始随机生成100个 1000位 10进制 字符串进行测试...>"<<endl;
    cout<<"<按任意键开始测试...>"<<endl;
    getch();
    for(int i=0;i<100;i++){
        string num=rand_n_digit_x_random(1000,Dec);
        cout<<"执行 num=rand_n_digit_x_random(1000,Dec)"<<endl;
        VeryLongInt num7(num);
        cout << "执行 VeryLongInt num7(num) 构造函数成功，结果为：\n" << "num7=" << num7 << endl;
        cout <<"num="<<num<<endl;
        cout << "num7==num: \n" << (num7 == num) << endl;
        if(num7!=num){
            cout<<"构造失败,num7!=VeryLongInt(num)"<<endl;
            cout<<"<测试失败,按任意键继续>"<<endl;
            getchar();
            return;
        }
    }

    cout<<"<开始随机生成100个 10位 16进制 字符串进行测试...>"<<endl;
    cout<<"<按任意键开始测试...>"<<endl;
    getch();
    for(int i=0;i<100;i++){
        string num=rand_n_digit_x_random(10,Hex);
        cout<<"执行 num=rand_n_digit_x_random(10,Hex)"<<endl;
        VeryLongInt num8(num);
        cout << "执行 VeryLongInt num8(num) 构造函数成功，结果为：\n" << "num8=" << num8 << endl;
        cout <<"num8.Hex()="<<num8.Hex()<<endl;
        cout <<"num="<<num<<endl;
        cout << "num8==num: " << (num8 == num) << endl;
        if(num8!=num){
            cout<<"构造失败,num8!=VeryLongInt(num)"<<endl;
            cout<<"<测试失败,按任意键继续>"<<endl;
            getchar();
            return;
        }
    }

    cout<<"<开始随机生成100个 100位 16进制 字符串进行测试...>"<<endl;
    cout<<"<按任意键开始测试...>"<<endl;
    getch();
    for(int i=0;i<100;i++){
        string num=rand_n_digit_x_random(100,Hex);
        cout<<"执行 num=rand_n_digit_x_random(100,Hex)"<<endl;
        VeryLongInt num9(num);
        cout << "执行 VeryLongInt num9(num) 构造函数成功，结果为：\n" << "num9=" << num9 << endl;
        cout <<"num9.Hex()="<<num9.Hex()<<endl;
        cout <<"num="<<num<<endl;
        cout << "num9==num: " << (num9 == num) << endl;
        if(num9!=num){
            cout<<"构造失败,num9!=VeryLongInt(num)"<<endl;
            cout<<"<测试失败,按任意键继续>"<<endl;
            getchar();
            return;
        }
    }

    cout<<"<开始随机生成100个 10位 8进制 字符串进行测试...>"<<endl;
    cout<<"<按任意键开始测试...>"<<endl;
    getch();
    for(int i=0;i<100;i++){
        string num=rand_n_digit_x_random(10,Oct);
        cout<<"执行 num=rand_n_digit_x_random(10,Oct)"<<endl;
        VeryLongInt num10(num);
        cout << "执行 VeryLongInt num10(num) 构造函数成功，结果为：\n" << "num10=" << num10 << endl;
        cout <<"num10.Oct()="<<num10.Oct()<<endl;
        cout <<"num="<<num<<endl;
        cout << "num10==num: " << (num10 == num) << endl;
        if(num10!=num){
            cout<<"构造失败,num10!=VeryLongInt(num)"<<endl;
            cout<<"<测试失败,按任意键继续>"<<endl;
            getchar();
            return;
        }
    }

    cout<<"<开始随机生成100个 100位 8进制 字符串进行测试...>"<<endl;
    cout<<"<按任意键开始测试...>"<<endl;
    getch();
    for(int i=0;i<100;i++){
        string num=rand_n_digit_x_random(100,Oct);
        cout<<"执行 num=rand_n_digit_x_random(100,Oct)"<<endl;
        VeryLongInt num11(num);
        cout << "执行 VeryLongInt num11(num) 构造函数成功，结果为：\n" << "num11=" << num11 << endl;
        cout <<"num11.Oct()="<<num11.Oct()<<endl;
        cout <<"num="<<num<<endl;
        cout << "num11==num: " << (num11 == num) << endl;
        if(num11!=num){
            cout<<"构造失败,num11!=VeryLongInt(num)"<<endl;
            cout<<"<测试失败,按任意键继续>"<<endl;
            getchar();
            return;
        }
    }
    cout<<"<测试无误,按任意键继续>"<<endl;
    getch();
    return;

}

void two_thousand_constructor_test(){//测试两个两千位的构造VeryLongInt类
    // 测试两个两千位的构造 VeryLongInt 类
    cout<<"<开始测试任意长度正数巨型整数的随机构造...>"<<endl;
    cout<<"<从构造1000位整数开始,下一次构造在上一次构造长度的增加1000位长度,直到构造100000位整数>"<<endl;
    cout<<"<按任意键开始测试...>";
    getch();
    for(unsigned long long len=1000;len<=100000;len+=1000){
        VeryLongInt num=randVeryLongInt(len,false);
        system("cls");
        cout<<"执行 randVeryLongInt("<<len<<") 构造函数成功，结果为：" << "num=" << num << endl; 
        if(num.getLength()!=len){
            cout<<"<测试失败:希望构造的长度与实际长度不一致<<"<<endl;
            cout<<"<按任意键继续>"<<endl;
            getch();
            return;
        }
    }
    cout<<"<开始测试任意长度负数巨型整数的随机构造...>"<<endl;
    cout<<"<从构造1000位整数开始,下一次构造在上一次构造长度的增加1000位长度,直到构造100000位整数>"<<endl;
    cout<<"<按任意键开始测试...>";
    getch();
    for(unsigned long long len=1000;len<=100000;len+=1000){
        VeryLongInt num=randVeryLongInt(len,true);
        system("cls");
        cout<<"执行 randVeryLongInt("<<len<<") 构造函数成功，结果为：" << "num=" << num << endl; 
        if(num.getLength()!=len){
            cout<<"<测试失败:希望构造的长度与实际长度不一致<<"<<endl;
            cout<<"<按任意键继续>"<<endl;
            getch();
            return;
        }
    }
    cout<<"<测试无误,按任意键继续>"<<endl;
}

void invalid_constructor_test(){//测试非法构造
    // 测试非法构造
    cout<<"<开始测试非法构造...>"<<endl;
    cout<<"<按任意键开始测试...>"<<endl;
    getch();
    try{
        cout<<"执行 VeryLongInt(\"\") 构造函数"<<endl;
        VeryLongInt num1("");
    }
    catch(Invalid_VeryLongInt& e){
        cout<<"<构造失败:Invalid_VeryLongInt异常>"<<"异常值为: "<<e.get_error_str_num()<<endl;
        cout<<"<异常原因:不存在有效值>"<<endl;
    }
    try{
        cout<<"执行 VeryLongInt(\"0123456789ABCDEFG\") 构造函数"<<endl;
        VeryLongInt num2("0123456789ABCDEFG");
    }
    catch(Invalid_VeryLongInt& e){
        cout<<"<构造失败:Invalid_VeryLongInt异常>"<<"异常值为: "<<e.get_error_str_num()<<endl;
        cout<<"<异常原因:8进制字符串中包含非法数字>"<<endl;
    }
    try{
        cout<<"执行 VeryLongInt(\"1234EF\") 构造函数"<<endl;
        VeryLongInt num3("1234EF");
    }
    catch(Invalid_VeryLongInt& e){
        cout<<"<构造失败:Invalid_VeryLongInt异常>"<<"异常值为: "<<e.get_error_str_num()<<endl;
        cout<<"<异常原因:10进制字符串中包含非法数字>"<<endl;
    }
    try{
        cout<<"执行 VeryLongInt(\"123456789*\") 构造函数"<<endl;
        VeryLongInt num4("123456789*");
    }
    catch(Invalid_VeryLongInt& e){
        cout<<"<构造失败:Invalid_VeryLongInt异常>"<<"异常值为: "<<e.get_error_str_num()<<endl;
        cout<<"<异常原因:10进制字符串中包含非法数字>"<<endl;
    }
    try{
        cout<<"执行 VeryLongInt(\"0x123456789ABCDEFG\") 构造函数"<<endl;
        VeryLongInt num4("0x123456789ABCDEFG");
    }
    catch(Invalid_VeryLongInt& e){
        cout<<"<构造失败:Invalid_VeryLongInt异常>"<<"异常值为: "<<e.get_error_str_num()<<endl;
        cout<<"<异常原因:16进制字符串中包含非法数字>"<<endl;
    }
   
}

void stuid_id_constructor_test(VeryLongInt &id_num,VeryLongInt &stuid_num){//测试通过VeryLongInt类构造省份证号
    cout<<"<开始以18位身份证号为基础构造巨型整数对象进行测试...>"<<endl;
    cout<<"<按任意键开始构造...>";
    getch();
    cout<<"<是否选择自行输入身份证号进行测试? (Y/N)>"<<endl;
    cout<<"<若选择N,系统会自己随机构造18位巨型整数进行测试>"<<endl;
    char choice;
    string id;
    while(true){
        choice=toupper(getch());
        if(choice=='Y'){
            cout<<"请输入身份证号:"<<endl;
            try{
                cin>>id;
                id_num=VeryLongInt(id);
                cout<<"执行 VeryLongInt(id) 构造函数成功，结果为：" << "id=" << id_num << endl;
                break;
            }
            catch(Invalid_VeryLongInt& e){
                cout<<"<构造失败:Invalid_VeryLongInt异常>"<<"异常值为: "<<e.get_error_str_num()<<endl;
                cout<<"请重新输入身份证号:"<<endl;
            }
        }
        else if(choice=='N'){
            cout<<"随机构建18位巨型整数作为身份证号进行测试"<<endl;
            id_num=randVeryLongInt(18);
            cout<<"执行 randVeryLongInt(18) 构造函数成功，结果为：" << "id=" << id_num << endl;
            break;
        }
        else{
            cout<<"输入错误,请重新输入"<<endl;
        }
    }
    cout<<"<代表身份炸号的18位巨型整数构建完成: "<<id_num<<">"<<endl;
    cout<<"<开始以9位学号为基础构造巨型整数对象进行测试...>"<<endl;
    cout<<"<按任意键开始构造...>";
    getch();
    cout<<"<是否选择自行输入学号进行测试? (Y/N)>"<<endl;
    cout<<"<若选择N,系统会自己随机构造9位巨型整数进行测试>"<<endl;
    while(true){
        choice=toupper(getch());
        if(choice=='Y'){
            cout<<"请输入学号:"<<endl;
            try{
                cin>>id;
                stuid_num=VeryLongInt(id);
                cout<<"执行 VeryLongInt(id) 构造函数成功，结果为：" << "id=" << stuid_num << endl;
                break;
            }
            catch(Invalid_VeryLongInt& e){
                cout<<"<构造失败:Invalid_VeryLongInt异常>"<<"异常值为: "<<e.get_error_str_num() << endl;
                cout<<"请重新输学号"<<endl;
            }
        }
        else if(choice=='N'){
            cout<<"随机构建9位巨型整数作为学号进行测试"<<endl;
            stuid_num=randVeryLongInt(9);
            cout<<"执行 randVeryLongInt(9) 构造函数成功，结果为：" << "id=" << stuid_num << endl;
            break;
        }
        else{
            cout<<"输入错误,请重新输入"<<endl;
        }
    }
    cout<<"<代表学号的9位巨型整数构建完成: "<<stuid_num<<">"<<endl;
    cout<<"操作数1身份证号:"<<id_num<<endl;
    cout<<"操作数2学号:"<<stuid_num<<endl;
}
//不完全测试菜单
void SimpleTestMenu(){
    printf("----------------------------------------------\n");
    printf("<巨型整数类间运算测试菜单>\n");
    printf("A. 两个巨型整数类间的加法运算\n");
    printf("B. 两个巨型整数类间的减法运算\n");
    printf("C. 两个巨型整数类间的乘法运算\n");
    printf("D. 两个巨型整数类间的除法运算\n");
    printf("E. 两个巨型整数类间的取模运算\n");
    printf("F. 两个巨型整数类间的\">\"运算\n");
    printf("G. 两个巨型整数类间的\">=\"运算\n");
    printf("H. 两个巨型整数类间的\"<\"运算\n");
    printf("I. 两个巨型整数类间的\"<=\"运算\n");
    printf("J. 两个巨型整数类间的\"==\"运算\n");
    printf("K. 两个巨型整数类间的\"!=\"运算\n");
    printf("Q. 退出测试菜单\n");
    printf("----------------------------------------------\n");
}
//测试菜单
void TestMenu(){
     printf("----------------------------------------------\n");
    printf("<巨型整数类操作测试菜单>\n");
    printf("A. 两个巨型整数类间的加法运算\n");
    printf("B. 两个巨型整数类间的减法运算\n");
    printf("C. 两个巨型整数类间的乘法运算\n");
    printf("D. 两个巨型整数类间的除法运算\n");
    printf("E. 两个巨型整数类间的取模运算\n");
    printf("F. 两个巨型整数类间的\">\"运算\n");
    printf("G. 两个巨型整数类间的\">=\"运算\n");
    printf("H. 两个巨型整数类间的\"<\"运算\n");
    printf("I. 两个巨型整数类间的\"<=\"运算\n");
    printf("J. 两个巨型整数类间的\"==\"运算\n");
    printf("K. 两个巨型整数类间的\"!=\"运算\n");
    printf("L. 两个巨型整数类求最小公倍数\n");
    printf("M. 两个巨型整数类求最大公约数\n");
    printf("N. 巨型整数类取绝对值\n");
    printf("O. 测试num1+=num2\n");
    printf("P. 测试num1-=num2\n");
    printf("Q. 测试num1*=num2\n");
    printf("R. 测试num1/=num2\n");
    printf("S. 测试num1%=num2\n");
    printf("T. 求pow(num1,num2)\n");
    printf("U. 退出测试菜单\n");
    printf("ps: pow(num1,num2) 中建议 num1<=3000 num2<=3000\n");
    printf("----------------------------------------------\n");
}
//简易测试菜单内容
bool simple_switch_test_menu(const VeryLongInt &num1,const VeryLongInt &num2){
    bool quit=false;
    char choice;
    while(!quit){
        SimpleTestMenu();
        choice=toupper(getch());
        switch(choice){
            case 'A':
                cout<<"执行操作数1+操作数2"<<endl;
                cout<<num1<<"+"<<num2<<"="<<num1+num2<<endl;
                cout<<"执行操作数2学号+操作数1身份证号"<<endl;
                cout<<num2<<"+"<<num1<<"="<<num2+num1<<endl;
                cout<<"<按任意键继续>"<<endl;
                getch();
                break;
            case 'B':
                cout<<"执行操作数1-操作数2"<<endl;
                cout<<num1<<"-"<<num2<<"="<<num1-num2<<endl;
                cout<<"执行操作数2学号-操作数1身份证号"<<endl;
                cout<<num2<<"-"<<num1<<"="<<num2-num1<<endl;
                cout<<"<按任意键继续>"<<endl;
                getch();
                break;
            case 'C':
                cout<<"执行操作数1*操作数2"<<endl;
                cout<<num1<<"*"<<num2<<"="<<num1*num2<<endl;
                cout<<"执行操作数2学号*操作数1身份证号"<<endl;
                cout<<num2<<"*"<<num1<<"="<<num2*num1<<endl;
                cout<<"<按任意键继续>"<<endl;
                getch();
                break;
            case 'D':
                cout<<"执行操作数1/操作数2"<<endl;
                cout<<num1<<"/"<<num2<<"="<<num1/num2<<endl;
                cout<<"执行操作数2学号/操作数1身份证号"<<endl;
                cout<<num2<<"/"<<num1<<"="<<num2/num1<<endl;
                cout<<"<按任意键继续>"<<endl;
                getch();
                break;
            case 'E':
                cout<<"执行操作数1%操作数2"<<endl;
                cout<<num1<<"%"<<num2<<"="<<num1%num2<<endl;
                cout<<"执行操作数2学号%操作数1身份证号"<<endl;
                cout<<num2<<"%"<<num1<<"="<<num2%num1<<endl;
                cout<<"<按任意键继续>"<<endl;
                getch();
                break;
            case 'F':
                cout<<"执行操作数1>操作数2"<<endl;
                cout<<num1<<">"<<num2<<"="<<(num1>num2)<<endl;
                cout<<"执行操作数2学号>操作数1身份证号"<<endl;
                cout<<num2<<">"<<num1<<"="<<(num2>num1)<<endl;
                cout<<"<按任意键继续>"<<endl;
                getch();
                break;
            case 'G':
                cout<<"执行操作数1>=操作数2"<<endl;
                cout<<num1<<">="<<num2<<"="<<(num1>=num2)<<endl;
                cout<<"执行操作数2学号>=操作数1身份证号"<<endl;
                cout<<num2<<">="<<num1<<"="<<(num2>=num1)<<endl;
                cout<<"<按任意键继续>"<<endl;
                getch();
                break;
            case 'H':
                cout<<"执行操作数1<操作数2"<<endl;
                cout<<num1<<"<"<<num2<<"="<<(num1<num2)<<endl;
                cout<<"执行操作数2学号<操作数1身份证号"<<endl;
                cout<<num2<<"<"<<num1<<"="<<(num2<num1)<<endl;
                cout<<"<按任意键继续>"<<endl;
                getch();
                break;
            case 'I':
                cout<<"执行操作数1<=操作数2"<<endl; 
                cout<<num1<<"<="<<num2<<"="<<(num1<=num2)<<endl;
                cout<<"执行操作数2学号<=操作数1身份证号"<<endl;
                cout<<num2<<"<="<<num1<<"="<<(num2<=num1)<<endl;
                cout<<"<按任意键继续>"<<endl;
                getch();
                break;
            case 'J':
                cout<<"执行操作数1==操作数2"<<endl;
                cout<<num1<<"=="<<num2<<"="<<(num1==num2)<<endl;
                cout<<"执行操作数2学号==操作数1身份证号"<<endl;
                cout<<num2<<"=="<<num1<<"="<<(num2==num1)<<endl;
                cout<<"<按任意键继续>"<<endl;
                getch();
                break;
            case 'K':
                cout<<"执行操作数1!=操作数2"<<endl;
                cout<<num1<<"!="<<num2<<"="<<(num1!=num2)<<endl;
                cout<<"执行操作数2学号!=操作数1身份证号"<<endl;
                cout<<num2<<"!="<<num1<<"="<<(num2!=num1)<<endl;
                cout<<"<按任意键继续>"<<endl;
                getch();
                break;
            case 'Q':
                quit=true;
                break;
            default:
                cout<<"输入错误,请重新输入"<<endl;
                break;
        }
    }
    return quit;
}
//测试菜单内容
bool switch_test_menu(VeryLongInt &num1,VeryLongInt &num2){
    bool quit=false;
    char choice;
    while(!quit){
        TestMenu();
        choice=toupper(getch());
        switch(choice){
            case 'A':
                cout<<"执行操作数1+操作数2"<<endl;
                cout<<num1<<"+"<<num2<<"="<<num1+num2<<endl;
                break;
            case 'B':
                cout<<"执行操作数1-操作数2"<<endl;
                cout<<num1<<"-"<<num2<<"="<<num1-num2<<endl;
                break;
            case 'C':
                cout<<"执行操作数1*操作数2"<<endl;
                cout<<num1<<"*"<<num2<<"="<<num1*num2<<endl;
                break;
            case 'D':
                cout<<"执行操作数1/操作数2"<<endl;
                cout<<num1<<"/"<<num2<<"="<<num1/num2<<endl;
                break;
            case 'E':
                cout<<"执行操作数1%操作数2"<<endl;
                cout<<num1<<"%"<<num2<<"="<<num1%num2<<endl;
                break;
            case 'F':
                cout<<"执行操作数1>操作数2"<<endl;
                cout<<num1<<">"<<num2<<"="<<(num1>num2)<<endl;
                break;
            case 'G':
                cout<<"执行操作数1>=操作数2"<<endl;
                cout<<num1<<">="<<num2<<"="<<(num1>=num2)<<endl;
                break;
            case 'H':
                cout<<"执行操作数1<操作数2"<<endl;
                cout<<num1<<"<"<<num2<<"="<<(num1<num2)<<endl;
                break;
            case 'I':
                cout<<"执行操作数1<=操作数2"<<endl; 
                cout<<num1<<"<="<<num2<<"="<<(num1<=num2)<<endl;
                break;
            case 'J':
                cout<<"执行操作数1==操作数2"<<endl;
                cout<<num1<<"=="<<num2<<"="<<(num1==num2)<<endl;
                break;
            case 'K':
                cout<<"执行操作数1!=操作数2"<<endl;
                cout<<num1<<"!="<<num2<<"="<<(num1!=num2)<<endl;
                break;
            case 'L':
                cout<<"执行操作数1和操作数2的最小公倍数"<<endl;
                cout<<"最小公倍数为:"<<num1.lcm(num2)<<endl;
                break;
            case 'M':
                cout<<"执行操作数1和操作数2的最大公约数"<<endl;
                cout<<"最大公约数为:"<<num1.gcd(num2)<<endl;
                break;
            case 'N':
                cout<<"执行操作数的绝对值"<<endl;
                cout<<"绝对值为:"<<num1.abs()<<endl;
                break;
            case 'O':
                cout<<"执行 操作数1+=操作数2"<<endl;
                cout<<"操作数1="<<num1<<endl;
                cout<<"操作数2="<<num2<<endl;
                cout<<"num1+=num2  ->"<<(num1+=num2)<<endl;
                cout<<"num1="<<num1<<endl;
                break;
            case 'P':
                cout<<"执行 操作数1-=操作数2"<<endl;
                cout<<"操作数1="<<num1<<endl;
                cout<<"操作数2="<<num2<<endl;
                cout<<"num1-=num2  ->"<<(num1-=num2)<<endl;
                cout<<"num1="<<num1<<endl;
                break;
            case 'Q':
                cout<<"执行 操作数1*=操作数2"<<endl;
                cout<<"操作数1="<<num1<<endl;
                cout<<"操作数2="<<num2<<endl;
                cout<<"num1*=num2  ->"<<(num1*=num2)<<endl;
                cout<<"num1="<<num1<<endl;
                break;
            case 'R':
                cout<<"执行 操作数1/=操作数2"<<endl;
                cout<<"操作数1="<<num1<<endl;
                cout<<"操作数2="<<num2<<endl;
                try{
                    cout<<"num1/=num2  ->"<<(num1/=num2)<<endl;
                    cout<<"num1="<<num1<<endl;
                }
                catch(Invalid_VeryLongInt& e){
                    cout<<"执行失败,原因:"<<e.get_error_str_num()<<endl;
                }
                break;
            case 'S':
                cout<<"执行 操作数1%=操作数2"<<endl;
                cout<<"操作数1="<<num1<<endl;
                cout<<"操作数2="<<num2<<endl;
                try{
                    cout<<"num1%=num2  ->"<<(num1%=num2)<<endl;
                    cout<<"num1="<<num1<<endl;
                }
                catch(Invalid_VeryLongInt& e){
                    cout<<"执行失败,原因:"<<e.get_error_str_num()<<endl;
                }
                break;
            case 'T':
                cout<<"求 pow(操作数1,操作数2) 结果"<<endl;
                cout<<"操作数1="<<num1<<endl;
                cout<<"操作数2="<<num2<<endl;
                try{
                    cout<<"pow(num1,num2)="<<pow(num1,num2.toLongLong())<<endl;
                }
                catch(out_of_range& e){
                    cout<<"执行失败,原因:"<<e.what()<<endl;
                }
                break;
            case 'U':
                quit=true;
                break;
            default:
                cout<<"输入错误,请重新输入"<<endl;
                break;
        }
    }
    return quit;
}
//测试两个巨型整数类间的身份证号和学号的运算
void stuid_id_operation_test(VeryLongInt &id_num,VeryLongInt &stuid_num){//测试通过VeryLongInt类进行身份证号和学号的运算
    cout<<"<两个操作数如下：>"<<endl;
    cout<<"操作数1身份证号:"<<id_num<<endl;
    cout<<"操作数2学号:"<<stuid_num<<endl;
    cout<<"<按任意键开始测试...>";
    getch();
    cout<<"<开始测试两操作数间的算术运算和关系运算...>"<<endl;
    test_verylongint_operation(id_num,stuid_num,false);
    cout<<"<结束测试,按任意键返回主菜单...>"<<endl;
    getch();
}
//测试两个巨型整数类间的算术运算和关系运算
void test_verylongint_operation(VeryLongInt &num1,VeryLongInt &num2,bool simple_test){
    cout<<"<两个操作数如下：>"<<endl;
    cout<<"操作数1:"<<num1<<endl;
    cout<<"操作数2:"<<num2<<endl;
    cout<<"<按任意键开始测试...>"<<endl;
    getch();
    cout<<"<开始测试两操作数间的算术运算和关系运算...>"<<endl;
    if(simple_test){
        simple_switch_test_menu(num1,num2);
    }
    else{
        switch_test_menu(num1,num2);
    }
}

void correctness_test(){
    system("cls");
    ifstream add_test_data("add_test_data.txt");
    ifstream sub_test_data("sub_test_data.txt");
    ifstream mul_test_data("mul_test_data.txt");
    ifstream div_test_data("div_test_data.txt");
    ifstream mod_test_data("mod_test_data.txt");
    if(!add_test_data || !sub_test_data || !mul_test_data || !div_test_data || !mod_test_data){
        cout<<"测试数据文件打开失败"<<endl;
        return;
    }
    printf("-------------------------------------------------\n");
    cout<<"<巨型整数类四则运算正确性测试界面>"<<endl;
    cout<<"<ps:测试数据由python原生int类型生成,保证了正确性>"<<endl;
    cout<<"<ps:如果出现结果与测试数据不符的情况,会立即终止测试>"<<endl;
    printf("-------------------------------------------------\n");
    cout<<"<按任意键开始测试...>"<<endl;
    getch();
    VeryLongInt num1,num2,result;
    string str1,str2,result_str,line;
    cout<<"<开始加法正确性测试...>"<<endl;
    while(getline(add_test_data,line)){
        int pos1=line.find('+'),pos2=line.find('=');
        str1=line.substr(0,pos1);
        str2=line.substr(pos1+1,pos2-pos1-1);
        result_str=line.substr(pos2+1);
        num1=str1;
        num2=str2;
        result=num1+num2;
        if(result!=result_str){
            cout<<"测试失败,测试数据为:"<<str1<<"+"<<str2<<"="<<result_str<<",实际结果为:"<<result<<endl;
            cout<<"终止测试"<<endl;
            return;
        }
    }
    add_test_data.close();
    cout<<"<加法测试结束>"<<endl;
    cout<<"<按任意键继续进行减法正确性测试...>"<<endl;
    getch();
    cout<<"<开始减法正确性测试...>"<<endl;
    while(getline(sub_test_data,line)){
        int pos1=line.find('-'),pos2=line.find('=');
        str1=line.substr(0,pos1);
        str2=line.substr(pos1+1,pos2-pos1-1);
        result_str=line.substr(pos2+1);
        num1=str1;
        num2=str2;
        result=num1-num2;
        
        if(result!=result_str){
            cout<<"测试失败,测试数据为:"<<str1<<"-"<<str2<<"="<<result_str<<",实际结果为:"<<result<<endl;
            cout<<"终止测试"<<endl;
            return;
        }
    }
    sub_test_data.close();
    cout<<"<减法测试结束>"<<endl;
    cout<<"<按任意键继续进行乘法正确性测试...>"<<endl;
    getch();
    cout<<"<开始乘法正确性测试...>"<<endl;
    while(getline(mul_test_data,line)){
        int pos1=line.find('*'),pos2=line.find('=');
        str1=line.substr(0,pos1);
        str2=line.substr(pos1+1,pos2-pos1-1);
        result_str=line.substr(pos2+1);
        num1=str1;
        num2=str2;
        result=num1*num2;
        if(result!=result_str){
            cout<<"测试失败,测试数据为:"<<str1<<"*"<<str2<<"="<<result_str<<",实际结果为:"<<result<<endl;
            cout<<"终止测试"<<endl;
            return;
        }
    }
    mul_test_data.close();
    cout<<"<乘法测试结束>"<<endl;
    cout<<"<按任意键继续进行除法正确性测试...>"<<endl;
    getch();
    cout<<"<开始除法正确性测试...>"<<endl;
    while(getline(div_test_data,line)){
        int pos1=line.find('/'),pos2=line.find('=');
        str1=line.substr(0,pos1);
        str2=line.substr(pos1+1,pos2-pos1-1);
        result_str=line.substr(pos2+1);
        num1=str1;
        num2=str2;
        result=num1/num2;
        if(result!=result_str){
            cout<<"测试失败,测试数据为:"<<str1<<"/"<<str2<<"="<<result_str<<",实际结果为:"<<result<<endl;
            cout<<"终止测试"<<endl;
            return;
        }
    }
    div_test_data.close();
    cout<<"<除法测试结束>"<<endl;
    cout<<"<按任意键继续进行取模正确性测试...>"<<endl;
    getch();
    cout<<"<开始取模正确性测试...>"<<endl;
    while(getline(mod_test_data,line)){
        int pos1=line.find('%'),pos2=line.find('=');
        str1=line.substr(0,pos1);
        str2=line.substr(pos1+1,pos2-pos1-1);
        result_str=line.substr(pos2+1);
        num1=str1;
        num2=str2;
        result=num1%num2;
        if(result!=result_str){
            cout<<"测试失败,测试数据为:"<<str1<<"%"<<str2<<"="<<result_str<<",实际结果为:"<<result<<endl;
            cout<<"终止测试"<<endl;
            return;
        }
    }
    mod_test_data.close();
    cout<<"<取模测试结束>"<<endl;
    cout<<"<测试无误,按任意键返回主菜单...>"<<endl;
    getch();

}

VeryLongInt VeryLongInt::sum_by_bit() const{
    int sum=0;
    for(size_t i=0;i < this->getLength();i++){
        sum+=this->getDigit(i)-'0';
    }
    return sum;
}
