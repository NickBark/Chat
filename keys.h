#ifndef KEYS_H
#define KEYS_H

#include "dependence_qt.h"

class MainFrame;
class Keys : public QFrame
{
    Q_OBJECT
public:
    explicit Keys(QFrame *parent = 0);
    MainFrame * mfk;

    QVBoxLayout * vbl;
    QLabel * open_key;
    QLabel * open_key_val;
    QLabel * close_key;
    QLabel * close_key_val;

    QString open;
    QString close;
signals:

public slots:
    void slotShowKeys();
};

#endif // KEYS_H
