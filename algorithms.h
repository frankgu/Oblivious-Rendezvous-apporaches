#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <math.h>
#include <QtCore>

class algorithms
{
public:
    algorithms();
    //generate the sequence for rendzvous
    QList<int> IDHopping(int N, int M, int ID, int nChannels);
    QList<int> MultiStepHopping(int ID, int N, int M, int n);
    QList<int> ModifiedModuleClock(int n);
private:
    bool isPrime(int number);   //check if a number is a prime
    QList<int> IDScale(int ID, int N, int M);
    int randInt(int low, int high, bool equal);
    int randP(int low, int high);
};

#endif // ALGORITHMS_H
