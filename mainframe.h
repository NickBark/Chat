#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "dependence_qt.h"

class Chat;
class Rsa;

class MainFrame : public QFrame
{
    Q_OBJECT

public:
    MainFrame(QFrame *parent = 0);
    ~MainFrame();

    void Designer();//Создание дочерних лэйаутов и виджетов
    void Properties();//Свойства виджетов
    void Layout();//Авто-размещение потомков в главном окне
    void Connector();//Соединение сигналов и слотов
    QByteArray Encoder(QString & str);
    QString Decoder(QByteArray & ba);

    Chat * chat;
    Rsa * rsa;
    int p;
    int q;
    int e;
    int n;
    int eiler;
    //секретный ключ d
    unsigned long int d;


    QVBoxLayout * vbl;
        QToolBar * tb;
            QPushButton * pbNet;
        QHBoxLayout * hbl;
            QTextEdit * te_cod;
            QTextEdit * te_text;
        QLabel * lbinp;
        QTextEdit * te_wtext;
        QPushButton * pbCoding;
        QLabel * lbcod;
//        QTextEdit * te_wcod;
        QPushButton * pbSend;

 public slots:
    void slotNet();
};

#endif // MAINFRAME_H
