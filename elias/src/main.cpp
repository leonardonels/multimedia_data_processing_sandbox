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

using namespace std;

template<typename T>
int sign(T val) {
    return (T(0) < val) - (val < T(0));
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
    while(in >> n) v.push_back(2 * abs(n) + (1 + sign<int>(n)) / 2 + (n == 0 ? 1 : 0));

    /* elias coding */
    
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
}

int main(int argc, char* argv[]){
    if(argc != 3){
        exit(1);
    }

    encode(argv[1], argv[2]);

    decode(argv[2], argv[1]);

    return 0;
}