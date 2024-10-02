#include "102300229_Code.h"
#include "./ui_102300229_Code.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

int MinEditDistance(const std::string &str1, const std::string &str2){//计算最小编辑距离
    int m=str1.length();
    int n=str2.length();
    std::vector<std::vector<int>> dp(m+1, std::vector<int>(n+1,0));
    for (int i=0; i<=m; ++i){
        for (int j=0; j<=n; ++j){
            if (i==0)
                dp[i][j]=j;
            else if (j==0)
                dp[i][j]=i;
            else if (str1[i - 1]==str2[j - 1])//如果两个字符相同，则不需要操作，直接等于前一个值
                dp[i][j]=dp[i - 1][j - 1];
            else//如果两个字符不同，则需要进行操作，取三个值的最小值+1
                dp[i][j]=1+std::min({dp[i][j-1], dp[i-1][j], dp[i-1][j-1]});
        }
    }

    return dp[m][n];
}

void strip_blank(std::string& content){
    //删除单行注释
    content=std::regex_replace(content, std::regex("//.*"), "");
    //删除多行注释
    content=std::regex_replace(content, std::regex("/\\*.*?\\*/"), "", std::regex_constants::format_default);
    //删除所有
    content=std::regex_replace(content, std::regex("\\s+"), "");
}



