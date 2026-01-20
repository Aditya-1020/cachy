#include "cache.hpp"
#include <iostream>
#include <cmath>
#include <cassert>

Cache::Cache(size_t size_KB, size_t line_size, size_t associativity) : associativity(associativity), line_size(line_size) {

    assert(size_KB > 0);
    assert(line_size > 0);
    assert(associativity > 0);

    size_t cache_bytes = size_KB * BYTES_PER_KB;

    assert(cache_bytes % (line_size * associativity) == 0);

    num_sets = cache_bytes / (line_size * associativity);

    assert((line_size & (line_size - 1)) == 0);
    assert((num_sets & (num_sets - 1)) == 0);

    offset_bits = static_cast<size_t>(std::log2(line_size));
    index_bits = static_cast<size_t>(std::log2(num_sets));

    sets.resize(num_sets);
    for (auto &set : sets) {
        set.resize(associativity);
    }
}

bool Cache::access(addr_t address) {
    // extract index, tag from addr
    addr_t index = (address >> offset_bits) & ((1ULL << index_bits) - 1);
    addr_t tag = address >> (offset_bits + index_bits);

    assert(index < num_sets);

    auto &set = sets[index];

    for (auto &line : set) {
        if (line.valid && line.tag == tag) {
            hits++;
            return true;
        }
    }

    // handle miss
    misses++;
    int victim = -1;

    for (size_t i{0}; i < set.size(); i++){
        if (!set[i].valid) {
            victim = i;
            break;
        }
    }

    if (victim == -1) {
        victim = 0;
    }

    set[victim].valid = true;
    set[victim].tag = tag;

    return false;

}

void Cache::print_stats() {
    u32 total = hits + misses;
    u32 hit_rate = (total > 0) ? static_cast<u32>((static_cast<u64>(hits) * 100ULL) / total) : 0;
    std::cout << "Hits: " << hits << std::endl;
    std::cout << "Misses: : " << misses << std::endl;
    std::cout << "Hit Rate: : " << hit_rate << "%" << std::endl;
}
