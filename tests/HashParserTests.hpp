#ifndef RUFUS_FILTER_HASHFILTERTESTS_HPP
#define RUFUS_FILTER_HASHFILTERTESTS_HPP

#include "parser/AlignmentParser.hpp"
#include "parser/HashParser.hpp"

#include <string>
#include <bitset>

namespace
{
	int loop = 100000000;
	std::string testString = "226347515391\t0\t1\tTTTTGTTTATGGTATCAGTAAAAAA\n343423323903\t0\t1\tTTTTCTAAAACCGGTTTTAGAAAAA\n3422229348607\t0\t1\tTTTTAAATTAATATATATGATAAAA\n9561171458431\t0\t1\tTTTGGCTGCCTACACACATCACAAA\n4247713304959\t0\t1\tTTTGGAGGGATGTTTTATGTTAAAA\n4091493075583\t0\t1\tTTTGCCATGTTTTTGCACTCTAAAA\n11218455969919\t0\t1\tTTTGAAAGGGGAAAAAAGTACCAAA\n1260484543\t0\t1\tTTTCTGTGGACATCAGAAAAAAAAA";
	TEST(FilterHashTests, FindTest)
	{
		// for (uint32_t i = 0; i < 100000000; ++i)
		{
			std::cout << "TTTTGTTTATGGTATCAGTAAAAAA" << std::endl;
			std::cout << "TTTTTTACTGATACCATAAACAAAA" << std::endl;
			const char* endlinePosition = nullptr;
			auto kmer = rufus::HashParser::ParseLine(testString.c_str(), endlinePosition);
			auto rKmer = rufus::AlignmentParser::ReverseComplement(kmer);
			auto sKmer = rufus::AlignmentParser::SwapCG(kmer);
			std::cout << std::bitset< 64 >(kmer) << std::endl;
			// std::cout << std::bitset< 64 >(rKmer) << std::endl;
			std::cout << std::bitset< 64 >(sKmer) << std::endl;
		}
	}

	TEST(FilterHashTests, FindTest2)
	{
		std::string filepath = "/uufs/chpc.utah.edu/common/home/ucgdlustre/u0991464/SimonsTryAgain/14590/SSC12411.proband.k25_m0_c7.HashList";

		auto kmerSet = rufus::HashParser::ParseFile(filepath);
		std::cout << kmerSet.size() << std::endl;
	}
}

#endif //RUFUS_FILTER_HASHFILTERTESTS_HPP
