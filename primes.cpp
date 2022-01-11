#include "primes.h"

Primes::Primes(QWidget *parent) :
    QWidget(parent)
{
}

void Primes::getprimes(int &p,int &q)
{
    int i=0;
    int j=0;

    while(i==j)
    {
        qsrand(time(0));
        i = qrand()%35;//Случайное число от 0 до 35
        j = qrand()%35;//Случайное число от 0 до 35
    }
    p = pqnum[i];
    q = pqnum[j];
}
