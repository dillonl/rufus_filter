#ifndef SRC_UTIL_COMMANDLINE_PARSER_H
#define SRC_UTIL_COMMANDLINE_PARSER_H

#include <cxxopts.hpp>

#include "noncopyable.hpp"

namespace rufus
{
	class CommandlineParser : private noncopyable
	{
	public:
		CommandlineParser(int argc, char** argv);
		~CommandlineParser();

		std::string getHashPath();
		uint32_t getWindowSize();
		uint32_t getWindowThreshold();
		uint32_t getQualityThreshold();
		/* std::iostream getOutStream(); */
		bool parseOptions(int argc, char** argv);
	private:

		cxxopts::Options m_options;

		std::string m_hash_path;
		uint32_t m_window_size;
		uint32_t m_window_threshold;
		uint32_t m_quality_threshold;
	};
}

#endif //SRC_UTIL_COMMANDLINE_PARSER_H
