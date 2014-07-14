#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>

#include "rana.hpp"

void benchmark()
{
    std::chrono::high_resolution_clock clock;
    auto start = clock.now();

    std::fstream file("../benchmark/data/sample.json");
    std::stringstream ss;
    ss << file.rdbuf();
    std::string file_string = ss.str();
    rana::parser parser;
    rana::value result;
    
    for(int i = 0; i < 1000; i++)
    {
        parser.set_buffer(file_string.data(), file_string.length());
        parser.parse_next(result);
    }
    
    auto elapsed = clock.now() - start;
    std::cout << elapsed.count() / 1000000000.0 << std::endl;
}

int main()
{
    benchmark();
    return 0;
}
