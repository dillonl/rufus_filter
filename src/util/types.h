#ifndef TYPES_UTILS_TYPES_H
#define TYPES_UTILS_TYPES_H

#include <cstdint>
#include <limits>

namespace rufus
{
	typedef uint64_t InternalKmer;
	typedef uint32_t position;

#define KMER_SIZE 25ULL
#define KMER_SHIFTER_SIZE (KMER_SIZE * 2)
#define KMER_COUNT_INC 1ULL
#define KMER_MASK std::numeric_limits< InternalKmer >::max() >> ((sizeof(InternalKmer) * 8) - KMER_SHIFTER_SIZE)
}

#endif //SRC_UTILS_TYPES_H
