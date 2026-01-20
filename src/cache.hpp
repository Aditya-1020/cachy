#pragma once

#include <vector>
#include <cstdint>

using u32 = uint32_t;
using u64 = uint64_t;
using addr_t = u64;

static constexpr size_t BYTES_PER_KB = 1024;
static constexpr size_t BYTES_PER_MB = BYTES_PER_KB * BYTES_PER_KB;


struct CacheLine {
    bool valid{false};
    addr_t tag{0};
    u64 meta{0}; // Later: uint8: RRIP, uint16 for LRU
};

class Cache {
private:
    size_t num_sets;
    size_t associativity;
    size_t line_size;
    
    size_t offset_bits;
    size_t index_bits;

    size_t hits{0};
    size_t misses{0};

    std::vector<std::vector<CacheLine>> sets;

public:
    Cache(size_t size_KB, size_t line_size, size_t associativity);
    bool access(addr_t address);
    void print_stats();
};
