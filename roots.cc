constexpr uint64_t e_bits = 0x4005BF0A8B145769; //euler's number

constexpr double ln2 = 0.6931471805599453;

double exp(double n, int p = 10){ // e^n; taylor expantion
    
    // n = k * ln(2) + r 
    // e^n = e^(k*ln(2)) + e^r
    // e^n = 2^k + e^r
    //

    double res = 1;
    double k = 1;
    for (int i = 1; i<=p; i++){
        k *= n/i;
        res += k;
    }
    return res;
}



double ln(double n){

}

double pow(float n, float p){

}
