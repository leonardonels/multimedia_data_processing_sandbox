#include <iostream>     // for std::cerr and std::endl
#include <fstream>      // for std::ifstream and std::ofstream
#include <vector>       // for std::vector
#include <algorithm>    // for std::sort



/**
 * The first parameter is the name of a text file that contains text formatted base 10 numbers representable as 
 * 32 bits signed integers, separated by whitespace. The program must create a new file, with the name 
 * passed as the second parameter, with the same numbers sorted from the smallest to the largest, each 
 * followed by <new line>. 
 * 
 * input: sort_int <filein.txt> <fileout.txt>
 */
int main(int argc, char* argv[])
{
    /**
     * 1. Check if the correct number of arguments is provided
     * 2. Open the input file for reading
     * 3. Read integers from the input file and store them in a vector
     * 4. Sort the vector of integers
     * 5. Open the output file for writing
     * 6. Write the sorted integers to the output file, each followed by a new line
     */

    if(argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    std::ifstream infile(argv[1]);
    if(!infile) {
        std::cerr << "Error: Could not open input file " << argv[1] << std::endl;
        return 1;
    }

    std::vector<int> numbers;
    int n;
    while(infile >> n) {
        numbers.push_back(n);
    }

    std::sort(numbers.begin(), numbers.end());

    std::ofstream outfile(argv[2]);
    if(!outfile) {
        std::cerr << "Error: Could not open output file " << argv[2] << std::endl;
        return 1;
    }

    for(const auto& num : numbers) {
        outfile << num << std::endl;
    }

    return 0;
}