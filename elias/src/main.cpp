/**
 * Write a command line program in C++ with this syntax: 
 * 
 * input: elias [c|d] <filein> <fileout>  
 * 
 * The first parameter can be either “c” or “d”, for compression or decompression.  When the “c” option is specified, the program opens the specified input file as text (the name is provided 
 * as the second command line parameter) and reads signed base 10 integers separated by whitespace. The 
 * program must then map each value to the range [1,+∞] using the following correspondence (0, −1, 1, −2, 
 * 2, −3, 3, −4, 4, ...) to (1, 2, 3, 4, 5, 6, 7, 8, 9, ...), i.e. negative numbers are mapped to even values, while 
 * non negative ones are mapped to odd numbers. The mapped numbers are then encoded with Elias γ code.
 * 
 * The output file is created in binary mode, with the name passed as the third parameter, and each number 
 * is saved with the number of bits specified by the encoding. The last byte is padded with 0, so that it 
 * cannot be read as a valid number.  
 * When the “d” option is specified, the data is decoded from binary to text. The program must create a new 
 * file, with the name passed as the third parameter, with the same numbers saved in decimal text format, 
 * each followed by a new line. 
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <bitset>

using namespace std;

template<typename T>
int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

int binary_length(int32_t n){
    return n==0 ? 1 : (int)log2(n) + 1;
    /**
     * or with __builtin_clz() which counts the number of leading zeros in the binary representation of an integer:
     * return n == 0 ? 1 : 32 - __builtin_clz(n);
     * Note: __builtin_clz() is a GCC built-in function and may not be available in all compilers. It also assumes that the input is a 32-bit integer.
     */
}

int encode(char* infile, char* outfile){
    ifstream in(infile);
    if(!in){
        exit(1);
    }

    ofstream out(outfile, ios::binary);
    if(!out){
        exit(1);
    }

    vector<int32_t> v;
    int32_t n;
    while(in >> n) v.push_back(2 * abs(n) + (1 + sign<int32_t>(n)) / 2 + (n == 0 ? 1 : 0));

    /* elias coding */
    int64_t buffer = 0;
    int bit_count = 0;
    for(const int32_t num : v){
        int len = 2 * (binary_length(num) - 1) + 1;
        buffer <<= len;
        bit_count += len;
        buffer |= num;
        while(bit_count >= 8){
            int64_t out_buffer = buffer;
            out_buffer >>= bit_count - 8;
            out.put(static_cast<int8_t>(out_buffer & 0xFF));
            bit_count -= 8;
        }
    }
    if(bit_count > 0){
        buffer <<= (8 - bit_count); // shift the remaining bits to the left and fill with 0s
        out.put(buffer & 0xFF);
    }
    
    return 0;
}

int decode(char* infile, char* outfile){
    ifstream in(infile, ios::binary);
    if(!in){
        exit(1);
    }

    ofstream out(outfile);
    if(!out){
        exit(1);
    }

    int32_t out_buffer = 0;
    char buffer = 0;
    size_t prefix_len = 0;
    size_t num = 0;
    size_t len = 0;
    while(in.read(&buffer, sizeof(int8_t))){
        unsigned char u_buffer = static_cast<unsigned char>(buffer);
        for(size_t i = 0; i < 8; i++){
            if(len == 0){
                // looking for prefix
                if((u_buffer >> (7 - i) & 0x01) != 0x01){
                    prefix_len++;
                    continue;
                }else{
                    // prefix len found
                    len = prefix_len + 1;
                }
            }
            // len != 0
            out_buffer <<= 1;
            out_buffer |= (u_buffer >> (7 - i)) & 0x01;
            len--;

            if(len == 0){
                // reverse mapping
                int val = 0;
                if((int)out_buffer%2!=0){
                    val = ((int)out_buffer - 1) / 2;
                }else{
                    val = (int)out_buffer / (-2);
                }
                out << val << '\n';
                out_buffer = prefix_len = len = 0;
            }
        }
    }

    return 0;
}

int main(int argc, char* argv[]){
    if(argc != 3){
        exit(1);
    }

    encode(argv[1], argv[2]);

    decode(argv[2], argv[1]);

    return 0;
}