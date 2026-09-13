#include <iostream>
#include <cstdint>
#include <iomanip>
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

struct vec2i {
    int x;
    int y;
};

int erpolate(vec2i cur, vec2i snk, double exp = 1){
    //cur = current coordinate; snk = (closest) sink coordinate
    //exp defines how "curved" the thing is

    double dist = sqrt(pow(snk.x + cur.x, 2) + pow(snk.y + cur.y, 2));
    std::cout << dist << std::endl;
    return 0; // supppress warning 
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

    
    int glutton[29][29] = {};
    
    std::cout << pow2(1) << std::endl;
    std::cout << pow2(20) << std::endl;
    

}


