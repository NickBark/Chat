#include "chat.h"
#include  "mainframe.h"

Chat::Chat(QFrame *parent) :
    QFrame(parent)
{
    setFixedSize(350,200);
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

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost, 1111 );//адрес и порт получения данных
     connect(udpSocket, SIGNAL(readyRead()),this, SLOT(ReadingData()));
    connect(pbSet,SIGNAL(clicked()),this,SLOT(btSet()));

    le_myip->setText("127.0.0.1");
    le_myport->setText("1111");
    le_ip->setText("127.0.0.1");
    le_port->setText("1111");
}

void Chat::ReadingData()
{
    //Адрес и Порт, от кого получаем получаем
    QHostAddress senderIP;
    quint16 senderPort;

    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());//узнаем оазмер ждущей обработки датаграммы

        udpSocket->readDatagram(datagram.data(), datagram.size(), &senderIP, &senderPort);//читаем данные
        mf->te_cod->append(QString("Принял код: "+datagram));//Вывсодим принятое сообщение в текстовый виджет

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
    mf->te_wtext->clear();
}

void Chat::btSet()
{
    disconnect(udpSocket,SIGNAL(readyRead()),this,0);
    delete udpSocket;
    QHostAddress myip;
    quint16 myport;
    myip.setAddress(le_myip->text());
    myport = le_myport->text().toUShort();

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(myip, myport );//Адрес и порт своего приемного сокета
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(ReadingData()));
    hide();
}
