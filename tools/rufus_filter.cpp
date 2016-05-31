#include <iostream>
#include <fstream>

#include "util/commandline_parser.h"

#include "parser/HashParser.hpp"
#include "parser/FastQParser.hpp"

bool fileExists(const std::string& name)
{
	std::ifstream f(name.c_str());
	return f.good();
}

int main(int argc, char** argv)
{
	rufus::CommandlineParser commandlineParser(argc, argv);
	if (!commandlineParser.parseOptions(argc, argv))
	{
		return 0;
	}
	std::string hashFilePath = commandlineParser.getHashPath();
	std::string fastQFilePath = commandlineParser.getFastQPath();

	if (!fileExists(hashFilePath))
	{
		std::cout << "Hash file not found. Please check the path and try again";
		return 1;
	}

	if (!fastQFilePath.empty() && !fileExists(fastQFilePath))
	{
		std::cout << "FastQ file not found. Please check the path and try again";
		return 1;
	}

	auto kmerHashes = rufus::HashParser::ParseFile(commandlineParser.getHashPath());

	std::istream* fastQStream;
	if (commandlineParser.getFastQPath().empty())
	{
		fastQStream = &std::cin;
	}
	else
	{
		fastQStream = new std::ifstream(fastQFilePath.c_str());
	}
	rufus::FastQParser fqparser(fastQStream, &std::cout, kmerHashes, commandlineParser.getWindowSize(), commandlineParser.getWindowThreshold(), commandlineParser.getQualityThreshold(), commandlineParser.getThreadCount());
	fqparser.parse();

	return 0;
}
