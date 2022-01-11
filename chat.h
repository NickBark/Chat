#ifndef CHAT_H
#define CHAT_H

#include "dependence_qt.h"

class MainFrame;
class Chat : public QFrame
{
    Q_OBJECT
public:
    explicit Chat(QFrame *parent = 0);
    MainFrame * mf;

    QVBoxLayout * vbl;
    QLabel * lb_myip;
    QLineEdit * le_myip;
    QLabel * lb_myport;
    QLineEdit * le_myport;
    QLabel * lb_ip;
    QLineEdit * le_ip;
    QLabel * lb_port;
    QLineEdit * le_port;
    QPushButton * pbSet;

    QUdpSocket * udpSocket;

signals:

public slots:
    void ReadingData();
    void btSendingData();
    void btSet();

};

#endif // CHAT_H
