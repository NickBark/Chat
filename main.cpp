#include "mainframe.h"
#include "dependence_qt.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Setup detaled application style
    QFile styleFile(":/style/DarkGray.qss");
    if( styleFile.open(QFile::ReadOnly) ) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        a.setStyleSheet(styleSheet);
    }
    else {
        qDebug() << "Style can't be loaded.";
    }

    MainFrame w;
    w.show();

    return a.exec();
}
