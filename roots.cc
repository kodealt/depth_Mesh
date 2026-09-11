#include <cstring> // i aint rewriting memcpy

constexpr uint64_t E = 0x4005BF0A8B145769; //euler's number
constexpr double LN2 = 0.6931471805599453;
#define EXP_MASK 0x7FF
double pow2(int k){
    
    double x = 1.0;

    uint64_t bits;
    std::memcpy(&bits, &x, sizeof(x));

    uint64_t exponent = (bits >> 52) & EXP_MASK; // 52 moves exponent all the way down to LSB
    exponent += k;

    bits = (bits & ~(uint64_t(EXP_MASK) << 52)) | (exponent << 52);

    std::memcpy(&x, &bits, sizeof(x));
        
    return x;

}

double exp(double n){ // e^n; taylor expantion
    
    // n = k * ln(2) + r
    //          -> r = k*ln(2) - n
    // e^n = e^(k*ln(2)) + e^r
    // e^n = 2^k + e^r
    //

    int k = int(n/LN2 + 0.5);
    double r = n - k * LN2;

    // 5th degree taylor series expantion, horner's method
    double res = 1 + r * ( 1 + r * (0.5 + r * (0.166666667 + r * (0.0416666667 + r * 0.00833333333 ))));

    return res * pow2(k);
}


double ln(double n){

}

double pow(float n, float p){

}
