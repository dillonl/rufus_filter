#ifndef SRC_PARSER_FASTQPARSER_HPP
#define SRC_PARSER_FASTQPARSER_HPP

#include "util/noncopyable.hpp"

namespace rufus
{
	class FastQParser : noncopyable
	{
	public:
		FastQParser(std::istream* in, std::ostream* out, std::unordered_set< InternalKmer >& kmers, uint32_t windowSize, uint32_t windowThreshold, uint32_t qualityThreshold) :
			m_in(in),
			m_out(out),
			m_kmers(kmers),
			m_window_size(windowSize),
			m_window_threshold(windowThreshold),
			m_quality_threshold(qualityThreshold)
		{
		}

		~FastQParser()
		{
		}

		void parse()
		{
			std::string infoLine;
			std::string seqLine;
			std::string plusLine;
			std::string qualLine;

			std::vector< InternalKmer > kmers;
			kmers.reserve(256);

			while (std::getline(*m_in, infoLine) &&
				   std::getline(*m_in, seqLine) &&
				   std::getline(*m_in, plusLine) &&
				   std::getline(*m_in, qualLine))
			{
				uint32_t kmerIterations = seqLine.size() - KMER_SIZE;
				if (AlignmentParser::ParseAlignment(seqLine.c_str(), kmerIterations, kmers));;
				{
					processAlignment(kmers, infoLine, seqLine, plusLine, qualLine);
				}
			}
		}

	private:

		void processAlignment(const std::vector< InternalKmer >& kmers, const std::string& infoLine, const std::string& sequence, const std::string& plusLine, const std::string& quality)
		{
			std::vector< bool > keepKmerPositions(kmers.size(), false);
			uint16_t lowQualityIndices[256];
			uint16_t lowQualityIndicesSize = 0;
			uint32_t currentLowQualityIndex = 0;
			setLowQualityIndices(quality.c_str(), quality.size(), lowQualityIndices, lowQualityIndicesSize);
			uint16_t nextLowQualityPosition = (lowQualityIndicesSize > currentLowQualityIndex) ? lowQualityIndices[currentLowQualityIndex] : std::numeric_limits< uint16_t >::max();
			auto kmerLength = kmers.size();

			bool kmerThresholdMet = false;
			uint32_t currentWindowCount = 0;
			for (auto i = 0; i < kmerLength; ++i)
			{
				if ((i + KMER_SIZE) >= nextLowQualityPosition)
				{
					// here we subtract out all the windowCounts within the current window, we do this because we are skipping forward
					for (uint32_t j = i; j < (nextLowQualityPosition + 1); ++j)
					{
						if (keepKmerPositions[j]) { currentWindowCount = (currentWindowCount <= 1) ? 0 : currentWindowCount - 1; }
					}
					i = nextLowQualityPosition + 1;
					++currentLowQualityIndex;
					nextLowQualityPosition = (lowQualityIndicesSize > currentLowQualityIndex) ? lowQualityIndices[currentLowQualityIndex] : std::numeric_limits< uint16_t >::max();
					continue;
				}
				//decrement window count
				auto kmer = kmers[i];
				auto rKmer = rufus::AlignmentParser::ReverseComplement(kmer);
				bool keep = (kmer < rKmer) ? (this->m_kmers.count(kmer) > 0) : (this->m_kmers.count(rKmer) > 0);
				if (keep)
				{
					keepKmerPositions[i] = true;
					++currentWindowCount;
					// when there are enough found kmers then we want to exit this loop
					if (currentWindowCount >= this->m_window_threshold)
					{
						kmerThresholdMet = true;
						break;
					}
				}
				if (i > this->m_window_size && keepKmerPositions[i - (this->m_window_size - 1)])
				{
					currentWindowCount = (currentWindowCount <= 1) ? 0 : currentWindowCount - 1;
				}
			}

			if (kmerThresholdMet)
			{
				std::cout << infoLine << std::endl;
				std::cout << sequence << std::endl;
				std::cout << plusLine << std::endl;
				std::cout << quality << std::endl;
			}
		}

		inline void setLowQualityIndices(const char* quality, size_t qualityLength, uint16_t* lowQualityIndices, uint16_t& lowQualityIndicesSize)
		{
			for (auto i = 0; i < qualityLength; ++i)
			{
				if (quality[i] < this->m_quality_threshold)
				{
					lowQualityIndices[lowQualityIndicesSize] = i;
					++lowQualityIndicesSize;
				}
			}
		}

		std::istream* m_in;
		std::ostream* m_out;

		std::unordered_set< InternalKmer > m_kmers;
		uint32_t m_window_size;
		uint32_t m_window_threshold;
		uint32_t m_quality_threshold;
	};
}

#endif //SRC_PARSER_FASTQPARSER_HPP
