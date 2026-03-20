/**
 * The first parameter is the name of a text file that contains signed base 10 integers from -1000 to 1000 
 * separated by whitespace. The program must create a new file, with the name passed as the second 
 * parameter, with the same numbers saved as 32-bit binary little endian numbers in 2's complement.
 * 
 * input: write_int32 <filein.txt> <fileout.bin>
 */

#include <iostream>
#include <fstream>

std::ostream& raw_write(std::ostream& os, const int32_t& val){
    return os.write(reinterpret_cast<const char*> (&val), sizeof(int32_t));
}

int main(int argc, char* argv[]){

    /**
     * 1. check for params
     * 2. open input file
     * 3. open output file
     * 4. read values and write them down as requested 
     */

    if (argc != 3){
        std::cerr << "Wrong number of params!!" << std::endl;
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile){
        std::cerr << "Unable to open input file!!" << std::endl;
        return 1;
    }else{
        std::cout << "Input file "<< argv[1] <<" opened successfully!!" << std::endl;
    }

    std::ofstream outfile(argv[2], std::ios::binary);
    if (!outfile){
        std::cerr << "Unable to open output file!!" << std::endl;
        return 1;
    }else{
        std::cout << "Output file "<< argv[2] <<" opened successfully!!" << std::endl;
    }

    int32_t n;
    while (infile >> n)
    {
        raw_write(outfile, n);
        std::cout << "Written value: " << n << std::endl;
    }
    
   return 0;
}