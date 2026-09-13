#include <cstring> // i aint rewriting memcpy

// constexpr uint64_t E = 0x4005BF0A8B145769; //euler's number
constexpr double LN2 = 0.6931471805599453;
constexpr double SQRT2=1.4142135623730951;
// constexpr double INV_SQRT2 = SQRT2 * 0.5;
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
    // e^n = 2^k * e^r
    //

    int k = int(n/LN2 + 0.5);
    double r = n - k * LN2;

    // 5th degree taylor series expantion, horner's method
    double res = 1 + r * ( 1 + r * (0.5 + r * (0.166666667 + r * (0.0416666667 + r * 0.00833333333 ))));

    return res * pow2(k);
}


double ln(double x){ //lnx sounds so much more fun to say than e^n or even e^x for that matter
    // ehh
    // extract mantisaa?
    // pray on newton and mercator?
    //

    // x = m * 2^k
    // ln(x) = ln(m*2^k)
    // ln(x) = ln(m) + k * ln(2)
    //            |    k -> get same as last time (exp bits)
    //            m -> leftover bits after removing k
    // z = substitute for m for the atanh-style series 

    uint64_t bits;
    std::memcpy(&bits, &x, sizeof(x));

    int k = ((bits >> 52) & EXP_MASK) - 1023; // max exp
    
    bits &= ~(uint64_t(EXP_MASK) << 52); // extract 
    bits |= uint64_t(1023) << 52;       //  the souls 
                                       //   ...the dark souls

    std::memcpy(&x, &bits, sizeof(x));
    if (x > SQRT2){ // reduce range further from [1, 2) to [1, SQRT2)
        x *= 0.5;
        k++; // x * 1/2 * 2 * 2^k
    } 

    // ouuu i can save .001 ms time with hyperbolic trig taylor series (then use it for higher accuracy)
    // then converting it to look like my lnx :teary face:

    // atanh-type taylor series;
    double z = (x - 1)/(x + 1); 
    double z2 = z * z;

    // term: 7
    // 2 * (z + z^3/3 + z^5/5 + z^7/7 + z^9/9 + z^11/11 + z^13/13;)
    double res = 2 * (z + z2 * (0.333333333 + z2 * (0.2 + z2 * (0.142857143 + z2 * (0.111111111 + z2 * (0.0909090909 + z2 * 0.0769230769))))));
    return res + k * LN2;

}

double pow(double a, double b){ // a^b = e^(b*lna)
    return exp(b * ln(a));   //  thank you daddy taylor 
}                           //   (or newton+mercator and BIG daddy euler, more specifically)


double sqrt(double x){
    return pow(x, 0.5);
}
