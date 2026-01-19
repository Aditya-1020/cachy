#include "cache.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <trace_file>" << std::endl;
        return 1;
    }

    Cache cache(32, 64);

    std::ifstream trace(argv[1]);
    if (!trace) {
        std::cerr << "Cannot open trace file" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(trace, line)) {
        u32 address = std::stoull(line, nullptr, 16);
        cache.access(address);
    }

    cache.print_stats();
    return 0;
}