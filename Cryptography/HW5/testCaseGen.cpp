#include <vector>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <math.h>

long long GCD(long long p, long long q){
    if(q == 0){
        return p;
    }

    long long r = p % q;
    return GCD(q, r);
}

long long modExp(long long num, long long power, long long mod){
    if(power == 0) return 1;
    if(power == 1) return num % mod;
    if(power % 2 == 0){
        long long q = modExp(num, power/2LL, mod);
        return (q * q) % mod;
    }
    return (num * modExp(num, power - 1LL, mod)) % mod;
}

bool isPrimitiveRoot(long long p, long long g){

    std::vector<long long> factors;
    for(long long i = 2; i * i < 50; i++){
        if((p - 1) % i == 0){
            factors.push_back(i);
            factors.push_back(p / i);
        }
    }

    long long numFactors = factors.size();

    for(int i = 0; i < numFactors; i++){
        if(modExp(g, (p - 1LL) / factors.at(i), p) == 1){
            return false;
        }
    }
    return true;
}

int main(){
    long long p;
    int n;

    std::cin >> p >> n;

    // long long val = 1;
    // for(long long i = 2; i < p - 1; i++){
    //     if(isPrimitiveRoot(p, i) == true){
    //         val = i;
    //         break;
    //     }
    // }


    // std::vector<long long> relPrimes;
    // std::vector<long long> notRelPrime;

    // for(long long i = 1; i < p - 1; i++){
    //     if(GCD(p - 1, i) == 1){
    //         relPrimes.push_back(i);
    //     }
    //     else {
    //         notRelPrime.push_back(i);
    //     }
    // }
    // long long size = relPrimes.size();
    // long long size2 = notRelPrime.size();

    std::cout << n << std::endl;

    srand(time(NULL));
    // long long *primRoots = (long long*)malloc(sizeof(long long) * size);
    // srand(time(NULL));
    for(int i = 0; i < n; i++){
        long long k = rand() * pow(10, 5) + rand();
        //long long k = rand() % 1523;
        std::cout << p << " " << k << std::endl;
    }

    // free(primRoots);
}

