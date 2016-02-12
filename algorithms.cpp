#include "algorithms.h"

algorithms::algorithms()
{
    //set up the seed for the random number generator
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}


bool algorithms::isPrime( int number )
{
    if ( ( (!(number & 1)) && number != 2 ) ||
         (number < 2) || (number % 3 == 0 && number != 3) )
        return false;

    for( int k = 1; 36*k*k-12*k < number;++k)
    {
        if ( (number % (6*k+1) == 0) || (number % (6*k-1) == 0) )
            return false;
    }
    return true;
}

QList<int> algorithms::IDHopping(int N, int M, int ID, int nChannels)
{
    //-----Step 1: first find the larger number between N and M
    int maxNum = 0;
    if(N > M)
    {
        maxNum = N;
    } else {
        maxNum = M;
    }

    //-----Step 2: find the smallest prime P such that P > max{N,M}
    int primeNum = 0;
    while(true)
    {
        maxNum++;
        if(isPrime(maxNum))
        {
            primeNum = maxNum;
            break;
        }
    }

    //-----Step 3: define the total time
    int totalT = 2 * N * primeNum;

    //-----Step 4: generate the sequence
    QList<int> resultSequence;
    int t = 0;
    while(true)
    {
        int t2 = t % totalT;
        int x = t2/(2*primeNum);
        int y = t2 % (2*primeNum);
        int z = ((x+y*ID) % primeNum) + 1;
        int z2 = ((z-1) % nChannels) + 1;
        resultSequence.push_back(z2);
        t++;
        if(t == totalT)
        {
            break;
        }
    }

    return resultSequence;
}

QList<int> algorithms::IDScale(int ID, int N, int M) {

    //-----Step 1: define variable
    int l = (int)(log(M)/log(N)) + 1;
    int i = 1;
    int cur = ID;

    QList<int> result;

    //-----Step 2: get the scale sequence
    while(i <= l)
    {
        int d = cur%N + 1;
        cur = (int)(cur/N);
        i++;
        result.push_back(d);
    }
    return result;
}

QList<int> algorithms::MultiStepHopping(int ID, int N,
                                        int M, int n){

    //-----Step 1: find the smallest prime P such that P > N
    int P = 0; // define the prime number
    int tempN = N;
    while(true){
        tempN++;
        if(isPrime(tempN))
        {
            P = tempN;
            break;
        }
    }

    //-----Step 2: define the variable
    int l = (int)(log(M)/log(N)) + 1;
    int T = 2 * N * P;
    int t = 0;
    int z = 0;
    QList<int> dx = IDScale(ID,N,M);
    QList<int> result;

    //-----Step 3: get the sequence
    while(true){
        if(t < T)
        {
            z = (int)(t/(2*P)) + 1;
        } else {
            int t1 = (t-T)%(2*l*T);
            int x = (int)(t1/(2*T))+1;
            int y = t1%(2*T);
            int y1 = y%(2*P);
            int y2 = ((int)(y/(2*P)))%N+1;
            z = (y2+y1*dx.at(x-1)-1)%P+1;
        }
        int z1 = (z-1)%n + 1;
        result.push_back(z1);
        t++;
        if(t >= 2*l*T)
        {
            break;
        }
    }
    return result;
}

QList<int> algorithms::ModifiedModuleClock(int n){

    //-----Step 1: generate a random number range from [0,n)
    int j = randInt(0,n,false);
    int r = randInt(1,n,false);
    int p = randP(n,2*n);
    int t = 0;
    QList<int> result;

    //-----Step 2: generate the sequence
    while(true){

        if(t > 2 * p * p) break;

        j = (j + r) % p;
        if(j < n){
            result.push_back(j);
        } else {
            result.push_back(randInt(0,n,false));
        }

        t++;
    }

    return result;
}

int algorithms::randInt(int low, int high, bool equal) {
    if(equal){

        // Random number between low and high, include high bound
        return qrand() % ((high + 1) - low) + low;

    } else {

        // Random number between low and high, exclude high bound
        return qrand() % (high- low) + low;

    }
}

int algorithms::randP(int low, int high){

    int r = randInt(low,high,true);
    int resultP = 0;
    bool finded = false;

    for(int i = r; i <= high; i++){

        if(isPrime(i)){

            finded = true;
            resultP = i;

        }

    }
    if(!finded){

        for(int i = r; i >= low; i--){

            if(isPrime(i)){

                resultP = i;

            }
        }
    }

    return resultP;
}
