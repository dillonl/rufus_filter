#ifndef SRC_PARSER_FASTQPARSER_HPP
#define SRC_PARSER_FASTQPARSER_HPP

#include "util/noncopyable.hpp"

namespace rufus
{
	class FastQParser : noncopyable
	{
	public:
		FastQParser(std::istream* in, std::ostream* out) :
			m_in(in),
			m_out(out)
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
			kmers.resize(200);

			while (std::getline(*m_in, infoLine) &&
				   std::getline(*m_in, seqLine) &&
				   std::getline(*m_in, plusLine) &&
				   std::getline(*m_in, qualLine))
			{
				uint32_t kmerIterations = seqLine.size() - KMER_SIZE;
				if (AlignmentParser::ParseAlignment(seqLine.c_str(), qualLine.c_str(), 1, kmerIterations, kmers))
				{
					for (auto kmer : kmers)
					{
						std::cout << std::bitset< 64 >(kmer) << std::endl;
					}
				}
			}
		}

	private:

		std::istream* m_in;
		std::ostream* m_out;
	};
}

#endif //SRC_PARSER_FASTQPARSER_HPP
