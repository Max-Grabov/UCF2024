#include <vector>
#include <iostream>

long long modMult(long long x, long long y, long long mod){
    long long q = (mod / x);
    return x * (y % q) - (mod % x) * (y / q) < 0 ? (x * (y % q) - (mod % x) * (y / q) + mod) % mod : (x * (y % q) - (mod % x) * (y / q)) % mod;
}

long long modExp(long long num, long long power, long long mod){

    if(power == 0) return 1;
    if(power == 1) return num % mod;
    if(power % 2 == 0){
        long long q = modExp(num, power/2, mod);
        long long val = modMult(q, q, mod) % mod;

        std::cout << val << std::endl;
        return (val);
    }
    return ((num % mod) * modExp(num, power - 1, mod)) % mod;
}

bool isPrimitiveRoot(long long p, long long g, std::vector<long long> &factors){


    for(long long i = 2; i * i < p - 1; i++){
        if((p - 1) % i == 0){
            factors.push_back(i);
            factors.push_back((p - 1) / i);
        }
    }
    long long numFactors = factors.size();

    for(long long i = 0; i < numFactors; i++){
        if(modExp(g, (p - 1) / factors[i], p) == 1){
            return false;
        }
    }
    return true;
}

int main(){
    int n;
    long long p, g;

    std::vector<long long> factors;

    std::cin >> n;

    for(int i = 0; i < n; i++){
        std::cin >> p >> g;

        if(isPrimitiveRoot(p, g, factors) == true){
            std::cout << 1 << std::endl;
        }
        else {
            std::cout << 0 << std::endl;
        }

        factors.clear();
    }
}