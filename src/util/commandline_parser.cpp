#include "commandline_parser.h"

namespace rufus
{
	CommandlineParser::CommandlineParser(int argc, char** argv) :
		m_options("Rufus.Filter", "Filters through kmers and finds the good ones"),
		m_thread_count(2)
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
			("w,window_size", "Size of kmer Window", cxxopts::value< uint32_t >(this->m_window_size))
			("c,window_threshold", "Threshold of matching kmers within window size", cxxopts::value< uint32_t >(this->m_window_threshold))
			("q,quality_threshold", "Threshold of kmer base quality", cxxopts::value< uint32_t >(this->m_quality_threshold))
			("t,thread_count", "Thread Count [optional -- default 2]", cxxopts::value< uint32_t >(this->m_thread_count))
			("f,fastq_file", "Input FastQ File [optional -- default stdin]", cxxopts::value< std::string >(this->m_fastq_path))
			("help", "Print Help")
			;

		this->m_options.parse(argc, argv);

		if (this->m_options.count("help")) { std::cout << this->m_options.help() << std::endl; }

		if (!this->m_options.count("h") ||
			!this->m_options.count("w") ||
			!this->m_options.count("c") ||
			!this->m_options.count("q"))
		{
			std::cout << "Usage: rufus_filter [option] <argument>" << std::endl;
			success = false;
		}
		if (this->m_options.count("h") == 0) { std::cout << "\t[-h] Kmer hash file must be specified" << std::endl; }
		if (this->m_options.count("w") == 0) { std::cout << "\t[-w] Window size must be specified" << std::endl; }
		if (this->m_options.count("c") == 0) { std::cout << "\t[-c] Window threshold must be specified" << std::endl; }
		if (this->m_options.count("q") == 0) { std::cout << "\t[-q] Quality threshold must be specified" << std::endl; }
		return success;
	}

	std::string CommandlineParser::getHashPath()
	{
		return this->m_hash_path;
	}

	std::string CommandlineParser::getFastQPath()
	{
		return this->m_fastq_path;
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

	uint32_t CommandlineParser::getThreadCount()
	{
		return this->m_thread_count;
	}

}
