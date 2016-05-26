#include <iostream>

#include "util/commandline_parser.h"

#include "parser/HashParser.hpp"

int main(int argc, char** argv)
{
	rufus::CommandlineParser commandlineParser(argc, argv);
	if (!commandlineParser.parseOptions(argc, argv))
	{
		return 0;
	}

	auto kmerHashes = rufus::HashParser::ParseFile(commandlineParser.getHashPath());

	return 0;
}
