#include "commandline_parser.h"

namespace rufus
{
	CommandlineParser::CommandlineParser(int argc, char** argv) :
		m_options("Rufus.Filter", "Filters through kmers and finds the good ones")
	{
	}



	CommandlineParser::~CommandlineParser()
	{
	}

	bool CommandlineParser::parseOptions(int argc, char** argv)
	{
		bool success = true;
		this->m_options.add_options()
			("h,hash", "Path to kmer hash file", cxxopts::value< std::string >(this->m_hash_path))
			("s,window_size", "Size of kmer Window", cxxopts::value< uint32_t >(this->m_window_size))
			("t,window_threshold", "Threshold of matching kmers within window size", cxxopts::value< uint32_t >(this->m_window_threshold))
			("q,quality_threshold", "Threshold of kmer base quality", cxxopts::value< uint32_t >(this->m_quality_threshold))
			("help", "Print Help")
			;

		this->m_options.parse(argc, argv);

		if (this->m_options.count("help")) { std::cout << this->m_options.help() << std::endl; }
		if (this->m_options.count("k") == 0 ||
			this->m_options.count("s") == 0 ||
			this->m_options.count("t") == 0 ||
			this->m_options.count("q") == 0)
		{
			std::cout << "Usage: rufus_filter [option] <argument>" << std::endl;
			success = false;
		}
		if (this->m_options.count("h") == 0) { std::cout << "\t[-k] Kmer hash file must be specified" << std::endl; }
		if (this->m_options.count("s") == 0) { std::cout << "\t[-s] Window size must be specified" << std::endl; }
		if (this->m_options.count("t") == 0) { std::cout << "\t[-t] Window threshold must be specified" << std::endl; }
		if (this->m_options.count("q") == 0) { std::cout << "\t[-q] Quality threshold must be specified" << std::endl; }
		return success;
	}

	std::string CommandlineParser::getHashPath()
	{
		return this->m_hash_path;
	}

	uint32_t CommandlineParser::getWindowSize()
	{
		return this->m_window_size;
	}

	uint32_t CommandlineParser::getWindowThreshold()
	{
		return this->m_window_threshold;
	}

	uint32_t CommandlineParser::getQualityThreshold()
	{
		return this->m_quality_threshold;
	}

	/*
	std::iostream CommandlineParser::getOutStream()
	{
	}
	*/

}
