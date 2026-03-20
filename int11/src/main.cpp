/**
 * ================= Exercise 4 =================
 * Write a command line program in C++ with this syntax: 
 *  write_int11 <filein.txt> <fileout.bin>  
 * 
 * The first parameter is the name of a text file that contains base 10 integers from -1000 to 1000 separated 
 * by whitespace. The program must create a new file, with the name passed as the second parameter, with 
 * the same numbers saved as 11-bit binary in 2’s complement. The bits are inserted in the file from the 
 * most significant to the least significant. The last byte of the file, if incomplete, is filled with bits equal to 
 * 0. Since the incomplete byte will have at most 7 padding bits, there’s no risk of interpreting padding as 
 * another value. 
 * 
 * ================= Exercise 5 =================
 * Write a command line program in C ++ with this syntax: 
 *  read_int11 <filein.bin> <fileout.txt>  
 * 
 * The first parameter is the name of a binary file that contains 11-bit numbers in 2’s complement, with the 
 * bits sorted from most significant to least significant. The program must create a new file, with the name 
 * passed as the second parameter, with the same numbers saved in decimal text format separated by a new 
 * line. Ignore any excess bits in the last byte.
 */

#include <iostream>
#include <fstream>
#include <vector>

struct int11_t{
    int16_t value;

    int11_t() : value(0){}  // default constructor

    int11_t(int v){
        if (v < -1024 || v > 1023)
            throw std::out_of_range("int11_t: value out of range");
        value = static_cast<int16_t>(v & 0x7FF);    // store only 11 meaningful bits
        if(value & 0x400) value |= 0xF800;  // of 11th bit (0x400) is 1 add 1 to bits from 11 to 15 (0xF800)
    }

    operator int() const {return value;}
};

template<typename T>
std::istream& raw_read(std::istream& is, T& val, size_t size = sizeof(T)){
    return is.read(reinterpret_cast<char*>(&val), size);
}

template<typename T>
std::ostream& raw_write(std::ostream& os, T& val, size_t size = sizeof(T)){
    return os.write(reinterpret_cast<const char*>(&val), size);
}

int write_int11(const char* infile, const char* outfile){
    std::ifstream in(infile);
    if (!in){
        std::cerr << "Unable to open input file!!" << std::endl;
        exit(1);
    }

    std::ofstream out(outfile, std::ios::binary);
    if (!out){
        std::cerr << "Unable to open output file!!" << std::endl;
        exit(1);
    }

    std::vector<int11_t> v;
    int n;
    while(in >> n){
        v.push_back(int11_t(n));
    }

    uint8_t buffer = 0;
    int bit_count = 0;
    for(const auto& num : v){
        int11_t n = num;
        for(int i = 10; i >= 0; --i){
            buffer <<= 1;   // move the buffer to the left to make room for the next bit
            buffer |= (n.value >> i) & 1;
            bit_count++;
            if(bit_count == 8){
                out.put(buffer);
                buffer = 0;
                bit_count = 0;
            }
        }
    }
    if(bit_count > 0){
        buffer <<= (8 - bit_count); // shift the remaining bits to the left and fill with 0s
        out.put(buffer);
    }

    return 0;
}

int read_int11(const char* infile, const char* outfile) 
{
    std::ifstream in(infile, std::ios::binary);
    if (!in){
        std::cerr << "Unable to open input file!!" << std::endl;
        exit(1);
    }

    std::ofstream out(outfile);
    if (!out){
        std::cerr << "Unable to open output file!!" << std::endl;
        exit(1);
    }

    uint8_t buffer = 0;
    int bit_count = 0;
    int16_t value = 0;
    while(in.read(reinterpret_cast<char*>(&buffer), 1)) {
        for(int i = 7; i >= 0; --i) {
            value = (value << 1) | (buffer >> i) & 1;  // accumulate into the persistent value
            // ========================================================================================= //
            // is the same as (value << 1) | ((buffer >> i) & 1); sice & have higher precedence than |   //
            // ========================================================================================= //
            bit_count++;
            if(bit_count == 11) {
                if(value & 0x400) value |= 0xF800;
                out << static_cast<int>(value) << "\n";
                bit_count = 0;
                value = 0;               // reset for the next number
            }
        }
    }

    return 0;
}

int main (int argc, char* argv[])
{
    if(argc != 3){
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    write_int11(argv[1], argv[2]);

    read_int11(argv[2], argv[1]);

    return 0;
}