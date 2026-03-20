/**
 * The first parameter is the name of a binary file containing 32-bit numbers 2’s complement, in little 
 * endian. The program must create a new file, with the name passed as the second parameter, with the same 
 * numbers saved in decimal text format separated by a new line.
 * 
 * input: read_int32 <filein.bin> <fileout.txt>  
 */

#include <iostream>
#include <fstream>

std::istream& raw_read(std::istream& is, int32_t& val){
    return is.read(reinterpret_cast<char *> (&val), sizeof(int32_t));
}

int main(int argc, char* argv[]){

    if(argc != 3){
        std::cerr << "Wrong number of params!!" << std::endl << std::endl;
        return 1;
    }

    std::ifstream infile(argv[1], std::ios::binary);
    if(!infile){
        std::cerr << "Unable to open file " << argv[1] << std::endl << std::endl;
        return 1;
    }else{
        std::cout << "Input file "<< argv[1] <<" opened successfully!!" << std::endl << std::endl;
    }

    std::ofstream outfile(argv[2]);
    if(!outfile){
        std::cerr << "Unable to open file " << argv[2] << std::endl << std::endl;
        return 1;
    }else{
        std::cout << "Output file "<< argv[2] <<" opened successfully!!" << std::endl << std::endl;
    }

    int32_t n;
    while(raw_read(infile, n)){
        outfile << n << std::endl;
        std::cout << "Read value: " << n << std::endl;
    }



    return 0;
}