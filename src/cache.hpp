#pragma once

#include <vector>
#include <cstdint>

typedef uint32_t u32;
typedef uint64_t u64;

struct CacheLine {
    bool valid;
    u32 tag;
};

class Cache {
private:
    std::vector<CacheLine> lines;
    size_t num_sets;
    size_t offset_bits;
    size_t index_bits;

    u32 hits;  
    u32 misses;

    static constexpr size_t BYTES_PER_KB = 1024;
    static constexpr size_t BYTES_PER_MB = BYTES_PER_KB * BYTES_PER_KB;

    u32 get_index(u32 address) const {
        return (address >> offset_bits) & ((1UL << index_bits) - 1);
    }

    u32 get_tag(u32 address) const {
        return address >> (offset_bits + index_bits);
    }


public:
    Cache(size_t size_kb, size_t line_size);
    bool access(u32 address);
    void print_stats();
};
