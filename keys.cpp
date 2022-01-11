#include "keys.h"
#include "mainframe.h"

Keys::Keys(QFrame *parent) :
    QFrame(parent)
{
    setFixedSize(300,200);
    setWindowTitle("Мои Ключи");

    vbl = new  QVBoxLayout(this);
    setLayout(vbl);
}

void Keys::slotShowKeys()
{
    open = QString::number(mfk->e);
    open += " ";
    open += QString::number(mfk->n);

    close = QString::number(mfk->d);
    close += " ";
    close += QString::number(mfk->n);

    open_key = new QLabel("Мой открытый ключ: ",this);
    open_key_val = new QLabel(open,this);
    close_key = new QLabel("Мой закрытый ключ: ",this);
    close_key_val = new QLabel(close,this);

    vbl->addWidget(open_key);
    vbl->addWidget(open_key_val);
    vbl->addWidget(close_key);
    vbl->addWidget(close_key_val);
}
