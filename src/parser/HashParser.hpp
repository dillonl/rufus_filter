#ifndef SRC_PARSER_HASHPARSER_H
#define SRC_PARSER_HASHPARSER_H

#include "util/types.h"
#include "util/noncopyable.hpp"
#include "AlignmentParser.hpp"

#include <unordered_set>
#include <algorithm>

#include <sstream>
#include <fstream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

namespace rufus
{
	class HashParser
	{
	public:
		static inline std::unordered_set< InternalKmer > ParseFile(const std::string& hashFilePath)
		{
			std::unordered_set< InternalKmer > kmerSet;
			readHashFile(hashFilePath.c_str(), kmerSet);
			return kmerSet;
		}

		static inline std::unordered_set< InternalKmer > ParseString(const std::string& hashString)
		{
			std::unordered_set< InternalKmer > kmerSet;

			std::istringstream hashStream(hashString);
			std::string line;

			std::getline(hashStream, line);
			size_t tabLineCount = std::count(line.begin(), line.end(), '\t');
			InternalKmer iKmer = HashParser::ParseHashLine(line.c_str(), tabLineCount);
			kmerSet.emplace(iKmer);

			while (std::getline(hashStream, line))
			{
				InternalKmer iKmer = HashParser::ParseHashLine(line.c_str(), tabLineCount);
				setReverseComplement(line);
				InternalKmer rKmer = HashParser::ParseHashLine(line.c_str(), tabLineCount);
				kmerSet.emplace(iKmer);
				kmerSet.emplace(rKmer);
			}

			return kmerSet;
		}

		static inline InternalKmer ParseLine(const char* bufferPosition, const char*& endLinePosition)
		{
			InternalKmer iKmer = 0;
			uint32_t tabCount = 0;
			const char* kmer = nullptr;
			endLinePosition = bufferPosition;
			while (true)
			{
				++endLinePosition;
				if (*endLinePosition == '\t') { ++tabCount; }
				if (tabCount == 3)
				{
					++endLinePosition;
					kmer = endLinePosition;
					break;
				}
			}
			AlignmentParser::ParseInternalKmer(kmer, iKmer);
			endLinePosition += KMER_SIZE + 1;
			return iKmer;
		}

		static inline InternalKmer ParseHashLine(const char* bufferPosition, size_t tabLineCount)
		{
			InternalKmer iKmer = 0;
			uint32_t tabCount = 0;
			const char* kmer = nullptr;
			const char* endLinePosition = bufferPosition;
			while (true)
			{
				++endLinePosition;
				if (*endLinePosition == '\t') { ++tabCount; }
				if ((tabLineCount < 3 && tabCount == 0) ||
					(tabLineCount == 3 && tabCount == 3))
				{
					++endLinePosition;
					kmer = endLinePosition;
					break;
				}
			}
			AlignmentParser::ParseInternalKmer(kmer, iKmer);
			return iKmer;
		}

	private:
		HashParser() {}
		~HashParser() {}

		static void readHashFile(const char* fname, std::unordered_set< InternalKmer >& kmerSet)
		{
			std::ifstream file(fname);
			std::string line;

			std::getline(file, line);
			size_t tabLineCount = std::count(line.begin(), line.end(), '\t');
			InternalKmer iKmer = HashParser::ParseHashLine(line.c_str(), tabLineCount);
			kmerSet.emplace(iKmer);

			while (std::getline(file, line))
			{
				InternalKmer iKmer = HashParser::ParseHashLine(line.c_str(), tabLineCount);
				setReverseComplement(line);
				InternalKmer rKmer = HashParser::ParseHashLine(line.c_str(), tabLineCount);
				kmerSet.emplace(iKmer);
				kmerSet.emplace(rKmer);
			}
		}

		static void wc(char const *fname, std::unordered_set< InternalKmer >& kmerSet)
		{
			static const auto BUFFER_SIZE = 16*1024;
			int fd = open(fname, O_RDONLY);
			if(fd == -1)
				handle_error("open");

			/* Advise the kernel of our access pattern.  */
			posix_fadvise(fd, 0, 0, 1);  // FDADVICE_SEQUENTIAL

			char buf[BUFFER_SIZE + 1];
			uintmax_t lines = 0;

			while(size_t bytes_read = read(fd, buf, BUFFER_SIZE))
			{
				if(bytes_read == (size_t)-1)
				{
					handle_error("read failed");
				}
				if (!bytes_read)
				{
					break;
				}

				// for(char *p = buf; (p = (char*) memchr(p, '\n', (buf + bytes_read) - p)); ++p)
				const char* nextLine;
				const char* currentLine = buf;
				// while (currentLine)
				for(char *p = buf; (p = (char*) memchr(p, '\n', (buf + bytes_read) - p)); ++p)
				{
					currentLine = p;
					InternalKmer iKmer = HashParser::ParseLine(currentLine, nextLine);
					// kmerSet.emplace(iKmer);
					currentLine = nextLine;
				}
				std::cout << "reading: " << lines++ << std::endl;
			}
		}

		static void setReverseComplement(std::string& line)
		{
			std::unordered_map< char, char > complement({ {'A', 'T'}, {'T', 'A'}, {'C', 'G'}, {'G', 'C'} });
			std::reverse(line.begin(), line.end());
			for (auto i = 0; i < line.size(); ++i) { line[i] = complement[line[i]]; }
		}
	};
}

#endif //SRC_PARSER_HASHPARSER_H
