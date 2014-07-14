#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>

#include "rana.hpp"

void benchmark()
{

    std::fstream file("sample.json");
    std::stringstream ss;
    ss << file.rdbuf();
    std::string file_string = ss.str();
    rana::parser parser;
    rana::value result;

    std::chrono::high_resolution_clock clock;
    auto start = clock.now();
    
    for(int i = 0; i < 1000; i++)
    {
        parser.set_buffer(file_string.data(), file_string.length());
        parser.parse_next(result);
    }
    
    auto elapsed = clock.now() - start;
    std::cout << elapsed.count() / 10000000.0 << std::endl;
}

int main()
{
    benchmark();
    return 0;
}
