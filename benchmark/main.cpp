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

    auto start = std::chrono::high_resolution_clock::now();

	rana::parser parser;
	rana::value result;
    
    for(int i = 0; i < 1000; i++)
    {
		parser.parse_string(file_string, result);
    }
    
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
    std::cout << elapsed.count() * 1.0 / std::chrono::high_resolution_clock::period::den << std::endl;
}

int main()
{
    benchmark();
	int a = 0;
	std::cin >> a;
    return 0;
}
