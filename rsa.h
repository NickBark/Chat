#ifndef RSA_H
#define RSA_H

#include "dependence_qt.h"

class Rsa : public QFrame
{
    Q_OBJECT
public:
    explicit Rsa(QFrame *parent = 0);
    long unsigned int PrivateKey(int e, int eiler);
    int modexp(int x, unsigned long int y, int N);
signals:

public slots:

};

#endif // RSA_H
