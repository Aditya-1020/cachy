#include "cache.hpp"
#include <iostream>
#include <cmath>

Cache::Cache(size_t size_kb, size_t line_size) : hits(0), misses(0) {
    size_t cache_size = size_kb * BYTES_PER_KB;
    if (line_size == 0 || cache_size % line_size != 0) { throw std::invalid_argument("Invalid cache config");}

    size_t num_lines = cache_size / line_size;

    offset_bits = log2(line_size);
    index_bits = log2(num_lines);

    lines.resize(num_lines); // hold exactly num_lines elements
    for (auto &line : lines) {
        line.valid = false;
        line.tag = 0;
    }   
}

bool Cache::access(u32 address) {
    // extract index, tag from addr
    u32 index = get_index(address);
    u32 tag = get_tag(address);

    static int count = 0;
    if (count++ < 10) {
        std::cout << "Addr: 0x" << std::hex << address
                << " Index: " << index << " Tag: 0x" << tag << std::dec << std::endl;
    }

    if (lines[index].valid && lines[index].tag == tag) {
        hits++;
        return true;
    } else {
        misses++;
        lines[index].valid = true;
        lines[index].tag = tag;
        return false;
    }
}

void Cache::print_stats() {
    u32 total = hits + misses;
    u32 hit_rate = (total > 0) ? static_cast<u32>((static_cast<u64>(hits) * 100ULL) / total) : 0;
    std::cout << "Hits: " << hits << std::endl;
    std::cout << "Misses: : " << misses << std::endl;
    std::cout << "Hit Rate: : " << hit_rate << "%" << std::endl;
}
