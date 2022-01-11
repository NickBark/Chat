#ifndef PRIMES_H
#define PRIMES_H

#include "dependence_qt.h"

class Primes : public QWidget
{
    Q_OBJECT
public:
    explicit Primes(QWidget *parent = 0);
    const int pqnum[35] ={11,13,17,19,23,
                          29,31,37,41,43,
                          47,53,58,61,67,
                          73,79,83,89,97,
                          101,103,107,109,113,
                          127,131,137,139,149,
                          151,157,163,167,173};
    void getprimes(int &p,int &q);
};

#endif // PRIMES_H
