#include "chat.h"
#include  "mainframe.h"

Chat::Chat(QFrame *parent) :
    QFrame(parent)
{
    setFixedSize(350,250);
    setWindowTitle("Параметры сети");

    vbl = new  QVBoxLayout(this);
    setLayout(vbl);

    lb_myip = new QLabel("Мой IP:",this);
    le_myip = new QLineEdit(this);
    lb_myport = new QLabel("Мой порт:",this);
    le_myport = new QLineEdit(this);
    lb_ip = new QLabel("IP-адрес собеседника:");
    le_ip = new QLineEdit(this);
    lb_port = new QLabel("Порт собеседника:");
    le_port = new QLineEdit(this);

    pbSet  = new QPushButton("Применить",this);
    pbSet->setFixedWidth(100);

    vbl->addWidget(lb_myip);
    vbl->addWidget(le_myip);
    vbl->addWidget(lb_myport);
    vbl->addWidget(le_myport);
    vbl->addWidget(lb_ip);
    vbl->addWidget(le_ip);
    vbl->addWidget(lb_port);
    vbl->addWidget(le_port);
    vbl->addWidget(pbSet);

    mytimer = new QTimer(this);
    mytimer->setInterval(2000);

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost, 1111 );//адрес и порт получения данных
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(ReadingData()));
    connect(pbSet,SIGNAL(clicked()),this,SLOT(btSet()));

    le_myip->setText("192.168.1.33");
    le_myport->setText("1111");
    le_ip->setText("192.168.1.33");
    le_port->setText("1111");
}

void Chat::ReadingData()
{
    //Адрес и Порт, от кого получаем
    QHostAddress senderIP;
    quint16 senderPort;

    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());//узнаем оазмер ждущей обработки датаграммы

        udpSocket->readDatagram(datagram.data(), datagram.size(), &senderIP, &senderPort);//читаем данные
        QString inputData = datagram;
        QStringList inputList;
        inputList = inputData.split(" ",QString::SkipEmptyParts);
        if((inputList[0] == "<begin_broadcast>") && (senderIP != myip))
        {
            QString tmp = QString(datagram);
            qDebug()<<"HIS KEY"<<tmp;
            QStringList list;
            list = tmp.split(" ",QString::SkipEmptyParts);
            QString his_e = list[1];
            QString his_n = list[2];
            mf->his_e = his_e.toInt();
            mf->his_n = his_n.toInt();
            qDebug()<<"!!!!!!!!!!!!!!!"<<mf->his_e<<" "<<mf->his_n;
            break;
        }
        else if(senderIP == myip)
            break;

        mf->te_cod->append(QString("Принял код: "+datagram));//Выводим принятое сообщение в текстовый виджет

        QString str = mf->Decoder(datagram);
        mf->te_cod->append("Декодер: " + str);
    }
}

void Chat::btSendingData()
{
    QString message = mf->te_wtext->toPlainText();
    QByteArray ba = mf->Encoder(message);
    QHostAddress address;
    quint16 port;
    //Адрес и порт, по которому посылаем
    address.setAddress(le_ip->text());
    port = le_port->text().toUShort();
    udpSocket->writeDatagram(ba, address, port);
    mf->te_text->append("Послал: "+message );
    mf->te_text->append("Шифр: "+ba);
    mf->te_wtext->clear();
}

void Chat::btSet()
{
    disconnect(udpSocket,SIGNAL(readyRead()),this,0);
    disconnect(mytimer,SIGNAL(timeout()),this,0);
    delete udpSocket;
    myip.clear();
    myport = 0;
    myip.setAddress(le_myip->text());
    myport = le_myport->text().toUShort();

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(myip, myport );//Адрес и порт своего приемного сокета
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(ReadingData()));
    //широковещательная рассылка ----->
    broadcast_port = myport;
    QString str;
    str = le_myip->text();
    int pos = str.lastIndexOf(QChar('.'));
    str = str.left(pos);
    str.push_back(".255");
    broadcast_address.setAddress(str);

    broadcastSocket = new QUdpSocket(this);
    broadcastSocket->bind(broadcast_address, broadcast_port);
    mytimer->start();
    connect(mytimer,SIGNAL(timeout()),this,SLOT(slotBroadcast()));

    mf->te_text->clear();
    mf->te_cod->clear();
    hide();
}

void Chat::slotBroadcast()
{
    qDebug()<<"Идёт широковещательная рассылка !";
    QByteArray broadcastData;
    broadcastData = "<begin_broadcast> ";
    broadcastData += QByteArray::number(mf->e);
    broadcastData += " ";
    broadcastData += QByteArray::number(mf->n);
    broadcastSocket->writeDatagram(broadcastData,broadcast_address,broadcast_port);
    qDebug()<<broadcastData;
}
