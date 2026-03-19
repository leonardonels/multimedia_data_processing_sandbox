#include <iostream>
#include <fstream>
#include <map>


/**
 * The program takes a binary file as input and for each byte (interpreted as an unsigned 8-bit integer) it 
 * counts its occurrences. The output is a text file consisting of one line for each different byte found in the 
 * input file with the following format:
 * 
 * <byte><tab><occurrences><new line>
 * 
 * The byte is represented with its two-digit hexadecimal value, occurrences in base ten. The rows are sorted 
 * by byte value, from the smallest to the largest.
 * 
 * input: frequencies <input file> <output file>
 */

 int main(int argc, char* argv[]){

    /**
     * 1. Check for input correctness
     * 2. Open the input in binary mode
     * 3. Save each byte in a map that increases counter for each occurrance
     * 4. Open the output file in writing
     * 5. Write each elem from map as requested 
     */

    if (argc != 3){
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
    }

    std::ifstream infile(argv[1], std::ios::binary);
    if (!infile){
        std::cerr << "Error: Could not open input file " << argv[1] << std::endl;
        return 1;
    }

    std::map<unsigned char, size_t> byte_counts;
    unsigned char byte;
    while (infile.read(reinterpret_cast<char*>(&byte), sizeof(byte))){
        byte_counts[byte]++;
    }

    std::ofstream outfile(argv[2]);
    if (!outfile){
        std::cerr << "Error: Could not open output file " << argv[2] << std::endl;
        return 1;
    }

    for (const auto& [byte, count] : byte_counts){
        outfile << std::hex << static_cast<int>(byte) << "\t" << count << std::endl;
    }

    return 0;
 }