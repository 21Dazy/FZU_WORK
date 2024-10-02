#ifndef _CODE_H
#define _CODE_H

#include <QApplication>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
#include <QTextStream>
#include <QMessageBox>
#include <regex>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

int MinEditDistance(const std::string &str1, const std::string &str2);
std::string readFile(const std::string& filePath);
void strip_blank(std::string &content);
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
};


class CodeSimilarityChecker : public QWidget{
    Q_OBJECT
    private:
        QTextEdit *file1_text_edit;
        QTextEdit *file2_text_edit;
        QLabel *similarity_label;
        QLabel *file1_name_label;
        QLabel *file2_name_label;

    public:
        CodeSimilarityChecker(QWidget *parent=0): QWidget(parent){
            // 创建界面组件
            file1_text_edit=new QTextEdit;
            file2_text_edit=new QTextEdit;
            QPushButton *browse_button_1=new QPushButton(tr("选择文件1"));
            QPushButton *browse_button_2=new QPushButton(tr("选择文件2"));
            QPushButton *calculate_button=new QPushButton(tr("计算相似度"));
            QLabel *result_label=new QLabel(tr("相似度百分比："));
            file1_name_label=new QLabel(tr("文件1："));
            file2_name_label=new QLabel(tr("文件2："));
            similarity_label=new QLabel;

            // 连接按钮的点击事件
            connect(browse_button_1, &QPushButton::clicked, this, &CodeSimilarityChecker::browseFile1);
            connect(browse_button_2, &QPushButton::clicked, this, &CodeSimilarityChecker::browseFile2);
            connect(calculate_button, &QPushButton::clicked, this, &CodeSimilarityChecker::calculateSimilarity);

            // 设置界面布局
            QHBoxLayout *layoutH=new QHBoxLayout;
            QVBoxLayout *layoutV=new QVBoxLayout;
            layoutH->addWidget(file1_text_edit);
            layoutH->addWidget(browse_button_1);
            layoutV->addWidget(file1_name_label);
            layoutH->addWidget(file2_text_edit);
            layoutH->addWidget(browse_button_2);
            layoutV->addWidget(file2_name_label);
            layoutH->addWidget(calculate_button);
            layoutH->addWidget(result_label);
            layoutH->addWidget(similarity_label);
            setLayout(layoutH);
            setLayout(layoutV);
        }

    private slots:
        void browseFile1(){
            QString file_name=QFileDialog::getOpenFileName(this, tr("选择文件1"));
            if(!file_name.isEmpty()){
                qDebug()<<"Selected file:"<<file_name;
                QFile file(file_name);
                if(!file.exists()){
                    qDebug()<<"File does not exist";
                    file1_text_edit->setPlainText("文件不存在");
                    return;
                }
                if(file_name==file1_name_label->text()){
                    return;
                }
                QFile file1(file_name);
                if(file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    qDebug()<<"File is open";
                    file1_name_label->setText(file_name);
                    QTextStream in(&file1);
                    QString content=in.readAll();
                    file1_text_edit->setPlainText(content);
                }
                else{
                    qDebug()<<"File cannot be opened";
                    file1_text_edit->setPlainText("文件无法打开");
                }
            }
            else{
                qDebug()<<"No file selected";
            }
        }
        void browseFile2(){
            QString file_name = QFileDialog::getOpenFileName(this, tr("选择文件2"));
            if(!file_name.isEmpty()) {
                qDebug()<<"Selected file:"<<file_name;

                QFile file(file_name);
                if(!file.exists()) {
                    qDebug()<<"File does not exist";
                    file2_text_edit->setPlainText("文件不存在");
                    return;
                }
                if(file_name==file2_name_label->text()){
                    return;
                }

                QFile file2(file_name);
                if(file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    qDebug()<<"File is open";
                    file2_name_label->setText(file_name);
                    QTextStream in(&file2);
                    QString content=in.readAll();
                    file2_text_edit->setPlainText(content);
                }
                else{
                    qDebug()<<"File cannot be opened";
                    file2_text_edit->setPlainText("文件无法打开");
                }
            }
            else{
                qDebug()<<"No file selected";
            }
        }

        void calculateSimilarity(){
            QString text1=file1_text_edit->toPlainText();
            QString text2=file2_text_edit->toPlainText();

            std::string str1=text1.toStdString();
            std::string str2=text2.toStdString();
            strip_blank(str1);
            strip_blank(str2);
            int distance=MinEditDistance(str1,str2);

            // 计算相似度百分比，假设两个文件的最大长度为max_len
            int max_len=std::max(str1.length(),str2.length());
            double similarity_percentage=100.0*(1.0-(double)distance/max_len);
            similarity_label->setText(QString::number(similarity_percentage,'f',2)+"%");
        }



};



#endif // _CODE_H
