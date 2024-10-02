#include "102300229_Code.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CodeSimilarityChecker window;
    window.setWindowTitle("C++代码相似性检测");
    window.show();
    return app.exec();
}
