#ifndef SRC_PARSERS_ALIGNMENTPARSER_H
#define SRC_PARSERS_ALIGNMENTPARSER_H

#include "util/types.h"
#include "util/noncopyable.hpp"


#include <memory>
#include <iostream>
#include <bitset>
#include <unordered_map>

namespace rufus
{

	class AlignmentParser : private noncopyable
	{
	public:
		static inline bool ParseAlignment2(const char* sequence, const char* quality, uint32_t qualityThreshold, size_t kmerIterations, std::vector< InternalKmer >& kmers)
		{
			bool validKmer = true;
			uint16_t lowQualityIndices[256];
			uint16_t lowQualityIndicesSize = 0;
			for (auto i = 0; i < kmerIterations; ++i)
			{
				if (quality[i] < qualityThreshold)
				{
					lowQualityIndices[lowQualityIndicesSize] = i;
					++lowQualityIndicesSize;
				}
			}
			size_t currentKmerPosition = 0;
			uint16_t currentLowQualityIndex = 0;
			uint16_t nextLowQualityPosition = (lowQualityIndicesSize > 0) ? lowQualityIndices[currentLowQualityIndex++] : std::numeric_limits< uint16_t >::max();
			std::cout << sequence << std::endl;
			for (auto j = 0; j < kmerIterations; ++j)
			{
				// std::cout << nextLowQualityPosition << " " << j << std::endl;
				// if (nextLowQualityPosition <= (j + KMER_SIZE) && j >= nextLowQualityPosition) // if there is a low quality base the current kmer the skip past the low quality base
				if (false)
				{
					j = nextLowQualityPosition;
					++currentLowQualityIndex;
					nextLowQualityPosition = (currentLowQualityIndex < lowQualityIndicesSize) ? lowQualityIndices[currentLowQualityIndex] :  std::numeric_limits< uint16_t >::max();
				}
				else // create the kmer from the sequence
				{
					InternalKmer tmp;
					kmers[currentKmerPosition] = 0;
					// validKmer &= unroller(j, uint_< KMER_SIZE - 1 >(),  sequence, kmers[currentKmerPosition]);
					validKmer &= unroller(j, uint_< KMER_SIZE - 1 >(),  sequence, tmp);
					++currentKmerPosition;
					// std::cout << std::bitset< 64 >(kmers[currentKmerPosition]) << std::endl;
					std::cout << std::string(sequence + j, KMER_SIZE) << std::endl;
					std::cout << std::bitset< 64 >(tmp) << std::endl << std::endl;
				}
			}
			kmers.resize(currentKmerPosition);
			std::cout << kmers.size() << " " << kmers.capacity() << std::endl;
			return validKmer;
		}

		static inline bool ParseAlignment(const char* alignment, size_t kmerIterations, std::vector< InternalKmer >& kmers)
		{
			bool validKmer = true;
			for (auto i = 0; i < kmerIterations; ++i)
			{
				kmers[i] = 0;
				validKmer &= unroller(i, uint_< KMER_SIZE - 1 >(),  alignment, kmers[i]);
			}
			kmers.resize(kmerIterations);
			return validKmer;
		}

		static inline void ParseInternalKmer(const char* kmer, InternalKmer& iKmer)
		{
			unroller(0, uint_< KMER_SIZE - 1 >(),  kmer, iKmer);
		}

		static inline InternalKmer ReverseComplement(InternalKmer kmer)
		{
			InternalKmer cKmer = ComplimentConst ^ kmer;
			InternalKmer rKmer = 0;
			unrollerReverse(uint_< KMER_SIZE >(),  cKmer, rKmer);
			return rKmer;
		}

		static inline InternalKmer Compliment(InternalKmer kmer)
		{
			return ComplimentConst ^ kmer;
		}

		static inline InternalKmer SwapCG(InternalKmer kmer)
		{
			std::cout << std::bitset< 64 >((SwapMask2 & kmer)) << std::endl;
			return (((kmer >> 0x1) ^ kmer) & SwapMask1) | (SwapMask2 & kmer);
		}

	private:
		static const InternalKmer ShiftByOne = 1; // these need to the same as InternalKmer
		static const InternalKmer ShiftByThree = 3;
		static const InternalKmer ComplimentConst = KMER_MASK & 12297829382473034410U;
        static const InternalKmer SwapMask1 = 6148914691236517205U;  // 0101010101010101010101010101010101010101010101010101010101010101
		static const InternalKmer SwapMask2 = 12297829382473034410U; // 1010101010101010101010101010101010101010101010101010101010101010
		static const InternalKmer TotalBits = KMER_SIZE * 2;

		AlignmentParser() = delete;
		~AlignmentParser() = delete;

		template <InternalKmer N> struct uint_{ };

		template <InternalKmer N>
		static inline void unrollerReverse(uint_<N>, InternalKmer sourceKmer, InternalKmer& internalKmer)
		{
			unrollerReverse(uint_<N-1>(), sourceKmer, internalKmer);
			reverse(sourceKmer, internalKmer, N);
		}

		static inline void unrollerReverse(uint_<0>, InternalKmer sourceKmer, InternalKmer& internalKmer)
		{
			reverse(sourceKmer, internalKmer, 0);
		}

		static inline void reverse(InternalKmer sourceKmer, InternalKmer& kmer, InternalKmer kmerBitOffset)
		{
			InternalKmer bitOffset = (kmerBitOffset* 2);
			int shifter = (((-1) * bitOffset) + TotalBits);
			kmer |= (((sourceKmer >> (bitOffset - 2)) & 0x3) << shifter);
		}

		template <InternalKmer N, typename IterT>
		static inline bool unroller(const IterT& iter, uint_<N>, const char* sequence, InternalKmer& internalKmer)
		{
			unroller(iter, uint_<N-1>(), sequence, internalKmer);
			return parse(sequence, internalKmer, N, iter);
		}

		template <typename IterT>
		static inline bool unroller(const IterT& iter, uint_<0>, const char* sequence, InternalKmer& internalKmer)
		{
			return parse(sequence, internalKmer, 0, iter);
		}

		static inline bool parse(const char* alignmentCharacter, InternalKmer& kmer, InternalKmer kmerBitOffset, uint64_t counter)
		{
			InternalKmer shifter = (kmerBitOffset * 2);
			if ((alignmentCharacter[kmerBitOffset + counter]) & (1 >> (3))) { return false; } // if this is a non basepair char
			kmer |= (((alignmentCharacter[kmerBitOffset + counter] >> ShiftByOne) & 0x3) & ShiftByThree) << shifter;
			return true;
		}

	};
}

#endif //SRC_PARSERS_ALIGNMENTPARSER_H
