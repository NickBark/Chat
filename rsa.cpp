#include "rsa.h"

Rsa::Rsa(QFrame *parent) :
    QFrame(parent)
{
}

//Возвращает секретный вторичный ключ для декодирования
//e - первичный открытый ключ
//eiler = (p-1)*(q-1)
unsigned int Rsa::PrivateKey(int e, int eiler)
{
    int d = 1;
//    while ( (d*e)%eiler != 1 );
//    {
//        if ( (d*e)%eiler == 1 ) break;
//        d++;
//    }
    do
    {
      if ( (d*e)%eiler == 1 ) break;
      else d++;
    }
    while (d<65500);


    return d;
}

//Возвращает (x^y)%N
int Rsa::modexp(int x, unsigned long int y, int N)
{
  if (y == 0) return 1;
  int z = modexp(x, y / 2, N);
  if (y % 2 == 0)
    return (z*z) % N;
  else
    return (x*z*z) % N;
}
