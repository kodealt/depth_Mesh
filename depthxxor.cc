#include <iostream>
#include <cstdint>
#include <iomanip>
// #include <cmath>
#include <cstdio>
#include "roots.cc"

char i_buff[16]; // permanent buffer for conversion int => string
 
// int to string: i just realized i dont even need this
char* itos(int raw_num, char (&buffer)[16] = i_buff){ // honestly i only need like what? 11 bytes? to represent max of 2^32 which is 
    int n_DIGIT = 0;
    buffer[15] = '\0'; // last byte must always be a null terminator: reserve
    if (raw_num == 0) { // loop runs only for >0 so terminate early after check
        buffer[14] = '0';
        return &buffer[14];
    }
    bool negative = raw_num < 0;
    uint32_t num = (negative) ? 0u - static_cast<unsigned int>(raw_num) : static_cast<unsigned int>(raw_num); // bro think shit sweet 
                                                                                                              // (it is)

    // read from right to left, and write from right to left 
    // ...such that reversal isnt needed (insert in correct order from the start)
    constexpr uint32_t MAGIC = 0xCCCCCCCD; // round value of 2^35/10
    while (num > 0 && n_DIGIT < 14){ // iterate 14 digits [1E14] or 100s of trillion
        uint32_t quotient = (static_cast<uint64_t>(num) * MAGIC) >> 35; // if i tried to >> 35 on a 32 bit variable...
        uint32_t remainder = num - quotient * 10;

        buffer[14-n_DIGIT] = remainder + '0'; // get digit, and add char 0 as it is conveniently spaced that much
        //num /= 10; // sweet thing about c++ is that it truncates when doing int/int division...
        num = quotient;
        n_DIGIT++;
    }
    if (negative) {
        buffer[14-n_DIGIT] = '-';
        n_DIGIT++;
    };
    return &buffer[15-n_DIGIT]; // return the written bits, and ignore anything leading (be it garbage or previously written)
}

void scrutny(int arr[3][3]){
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            std::cout << arr[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void scrutny(double arr[28][28]){
    for (int i=0; i<28; i++){
        for (int j=0; j<28; j++){
            std::printf("%.2f ", arr[i][j]);
        }
        std::cout << std::endl;
    }
}

struct vec2i {
    int x;
    int y;
};

double eqx2(double x, double k = 0.05){ // e^(k*x^2) -> the normal distribution
    if (x < -1) {
        x = -x;
    }
    if (k > 0){
        k = -k;
    }

    return exp(k * pow((x - 1), 2));
    // return ((int)(exp(k * pow(x, 2))*100)+0.5) / 100.0; // round to 10ths 
}

double erpolate(vec2i cur, vec2i snk, int val, double exp = 1){
    //cur = current coordinate; snk = (closest) sink coordinate
    //exp defines how "curved" the thing is
    double dist = sqrt(pow(((snk.x + 1) * 3) - cur.x, 2) + pow(((snk.y + 1) * 3) - cur.y, 2));
    dist = (int)(dist * 100) / 100.0;
    // std::cout << dist << std::endl;
    // return round(dist);
    // return int(val * eqx2(round(dist))*100+ .5)/100.0;
    return int(val * eqx2(dist)*100+ .5)/100.0;
}

int main(){
    int sinks[3][3] = {};
    for (int i = 0; i<3; i++){
        for (int j = 0; j<3; j++){
            sinks[i][j] = rand()%5 + 2;
        }
    }
    scrutny(sinks);
    std::cout << "\n\n\n\n" << std::flush;

    
    double glutton[28][28] = {0};
    for (int i = 1; i < 27; i++){
        for (int j = 1; j < 27; j++){
            glutton[i][j] = erpolate(vec2i{i, j}, vec2i{i/3, j/3}, sinks[i/9][j/9]);
            // std::cout << i/9 << ","<< j/9 << " ";
        }
    }
  
    std::cout << std::setprecision(17);
    scrutny(glutton);

}

