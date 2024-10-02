import random
import tkinter as tk
import pathlib
from tkinter import filedialog



operators = ['+','-','*','/','%']

def generate_random_test_data(n,m,operator=None):#生成n组m位整数的测试数据
    test_data = []
    for i in range(n):
        tuple_case=generate_random_test_case(m,operator)
        case=f'{tuple_case[0]}{tuple_case[2]}{tuple_case[1]}={tuple_case[3]}'
        test_data.append(case)
    return test_data
    
    
def generate_random_int(n):#生成n位随机整数
    return random.randint(10**(n-1),10**n-1)

def generate_random_operator():#生成随机运算符
    return random.choice(operators)

def generate_random_test_case(n,operator=None):#生成两个n位整数和一个运算符组成的随机测试用例
    num1 = generate_random_int(n)
    num2 = generate_random_int(n)
    if(operator == None):
        operator = generate_random_operator()
    result = 0
    if(operator == '+'):
        result = num1 + num2
    elif(operator == '-'):
        result = num1 - num2
    elif(operator == '*'):
        result = num1 * num2
    elif(operator == '/'):
        if(num2 == 0):
            result = 'undefined'
        else:
            result = num1 // num2
    elif(operator == '%'):
        if(num2 == 0):
            result = 'undefined'
        else:
            result = num1 % num2
    return (num1,num2,operator,result)
def test_data_save(test_data,filename):#将测试数据保存到文件
    with open(filename,'w+') as f:
        for case in test_data:
            f.write(case+'\n')


def select_path(lable):
    global path
    path = filedialog.askdirectory()
    if(path == ''):
        lable.config(text="<请选择保存目录>")
    else:
        lable.config(text="保存目录: "+path)


def Window():
    root = tk.Tk()
    root.title("巨型整数简单四则运算测试数据生成器v1.0 ")
    root.geometry("650x300")
    label1 = tk.Label(root, text="测试数据生成器", font=("Arial", 18))
    label1.pack()
    label2 = tk.Label(root, text="请输入测试用例数量：")
    label2.pack()
    cases_num = tk.Entry(root)
    cases_num.pack()
    label3 = tk.Label(root, text="请输入整数位数：")
    label3.pack()
    digits_num = tk.Entry(root)
    digits_num.pack()
    author = tk.Label(root, text="作者: 叶达\n版本: 1.0\n开发日期: 2024.05.24")
    author.pack()
    lable=tk.Label(root, text="<请选择保存目录> "+path)
    lable.pack()
    button2 = tk.Button(root, text="选择保存目录", command=lambda:select_path(lable))
    button2.pack()
    print(path)
   
    
    def generate_test_data():
        if(path == ''):
            #在GUI中弹出提示框
            tk.messagebox.showerror('错误','请选择保存目录')
            return
        cases_num_value = int(cases_num.get())
        digits_num_value = int(digits_num.get())
        test_data = generate_random_test_data(cases_num_value,digits_num_value,"/")
        test_data_save(test_data,path+'/div_test_data.txt')
        test_data = generate_random_test_data(cases_num_value,digits_num_value,"*")
        test_data_save(test_data,path+'/mul_test_data.txt')
        test_data = generate_random_test_data(cases_num_value,digits_num_value,"+")
        test_data_save(test_data,path+'/add_test_data.txt')
        test_data = generate_random_test_data(cases_num_value,digits_num_value,"-")
        test_data_save(test_data,path+'/sub_test_data.txt')
        test_data = generate_random_test_data(cases_num_value,digits_num_value,"%")
        test_data_save(test_data,path+'/mod_test_data.txt')
        root.destroy()
    button1 = tk.Button(root, text="生成测试数据", command=generate_test_data)
    button1.pack()
    root.mainloop()
            
if __name__ == '__main__':
    path = ''
    Window()