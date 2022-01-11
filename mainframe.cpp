#include "mainframe.h"
#include "chat.h"
#include "rsa.h"

MainFrame::MainFrame(QFrame *parent)
    : QFrame(parent)
{
    setMinimumSize(600,600);
    move(20,40);
    vbl = new  QVBoxLayout(this);
    setLayout(vbl);

    chat = new Chat();
    chat->mf = this;
    rsa = new Rsa(this);

    Designer();
    Properties();
    Layout();
    Connector();

    //RSA param
    p = 13;
    q = 17;
    e = 7;
    n = 221;
//    eiler = (p-1)*(q-1);
//    секретный ключ d
//    d = rsa->PrivateKey(e, eiler);
    d = 55;
 }

MainFrame::~MainFrame()
{

}

void MainFrame::Designer()
{
         tb = new QToolBar(this);
            pbNet = new QPushButton(" Сеть ",this);
         hbl = new QHBoxLayout(this);
             te_cod = new QTextEdit(this);
             te_text = new QTextEdit(this);
         lbinp = new QLabel("Ввод:", this);
         te_wtext = new QTextEdit(this);

//         pbCoding = new QPushButton("Кодировать",this);
//         lbcod = new QLabel("Код:", this);lbcod->hide;
//         te_wcod = new QTextEdit(this);te_wcod->hide;

         pbSend = new QPushButton(" Послать ", this);
}


void MainFrame::Layout()
{
    vbl->addWidget(tb);
        tb->addWidget(pbNet);
    vbl->addLayout(hbl);
        hbl->addWidget(te_text);
        hbl->addWidget(te_cod);
    vbl->addWidget(lbinp);
    vbl->addWidget(te_wtext);


//    vbl->addWidget(pbCoding);
//    vbl->addWidget(lbcod);
//    vbl->addWidget(te_wcod);

    vbl->addWidget(pbSend);
}

void MainFrame::Properties()
{
    tb->setFixedHeight(25);
    te_wtext->setFixedHeight(40);
//    te_wcod->setFixedHeight(40);

    te_text->setReadOnly(true);
    te_cod->setReadOnly(true);
//    te_wcod->setReadOnly(true);

}

void MainFrame::Connector()
{
    connect(pbNet,SIGNAL(clicked()),this,SLOT(slotNet()));
    connect(pbSend,SIGNAL(clicked()),chat,SLOT(btSendingData()));
}

void MainFrame::slotNet()
{
    chat->show();
}

QByteArray MainFrame::Encoder(QString & str)
{
    QDebug deb = qDebug();
    QByteArray ba;
    QByteArray bout;
    ba.append(str);
    int data[1024];
    unsigned char * ch = (unsigned char*)data;

    //Вводим байт-эррэй в массив интов
    deb<<"\n data[]: ";
    for(int i=0;i<ba.size();i++){
        data[i] = ba[i];
        deb<<data[i];
    }
    deb<<"\n ba.size= "<<ba.size()<<"\n";

    //Кодирование - модульная экспонента
    deb<<"\n cod_data[]: ";
    for(int i=0;i<ba.size();i++){
        data[i] = rsa->modexp(data[i],e,n);
        deb<<data[i];
    }
    bout.clear();
    deb<<"\n ch[]: ";
    for(int i=0;i<4*ba.size();i++){
        deb<<ch[i];
    }
    //Создаем выходной байт-эррэй для отправки
    for(int i=0;i<4*ba.size();i++){
        bout.append(ch[i]);
    }
    deb<<"\nbout.size()="<<bout.size();

    deb<<"\n bout: ";
    for(int i=0;i<bout.size();i++)
    {
        deb<<(unsigned char)bout[i];
    }
    return bout;
}

QString MainFrame::Decoder(QByteArray & bx)
{
    QDebug deb = qDebug();
    QByteArray bout;
    int datax[1024];
    unsigned char * chx = (unsigned char*)datax;
    deb<<"\n---ПРИЕМ---!!!---\n";
    //ПРИНИМАЕМ ba[] ПО СЕТИ И
    //Сбрасываем входной байт-эррэй в массив чаров
    deb<<"chx: ";
    for(int i=0;i<bx.size();i++){
        chx[i]=(int)bx[i];
        deb<<(int)chx[i];
    }
    deb<<"\n";

    //Выводм общий с чарами сассив интов
    deb<<"datax: ";
    for(int i=0;i<bx.size()/4;i++){
        deb<<(int)datax[i];
    }
    deb<<"\n";

    //Проводим декодирование
    deb<<"datax-1000: ";
    for(int i=0;i<bx.size()/4;i++){
        datax[i] = rsa->modexp(datax[i],d,n);
        deb<<datax[i];
    }
    deb<<"\n";

    QByteArray by;
    //Вводим декодированный массив интов в байт-эррэй выводим результат
    deb<<"by: ";
    for(int i=0;i<bx.size()/4;i++){
        by.append(datax[i]);
        deb<<by[i];
    }
    deb<<"\n";

    //Выводим строку
    QString str;
    str.append(by);
    return str;
}
