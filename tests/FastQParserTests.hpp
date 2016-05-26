#ifndef RUFUS_FILTER_FASTQTESTS_HPP
#define RUFUS_FILTER_FASTQTESTS_HPP

#include "parser/FastQParser.hpp"

#include <sstream>
#include <string>
#include <bitset>

namespace
{
	std::string fastQString = "@E00121:21:H06AJALXX:2:1107:25806:32865/1\nCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCAACCCTAACCCCAACCCTAACCCTAACCCTAACCCTAACCCC\n+\n>@==?>>@?>=>>?>====?>===>?>====?>====?>====?>====?>====?>====?=====?>=====;:=>>?=>>=>??=>==??>=>=?=>>;;=><:9=<>3>>/<<,>9-/?*--/<;,5</+?,=</8?,.=/9>+99/\n@E00121:21:H06AJALXX:2:1107:3517:24462/1\nCTAACCCTAAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCAACCCTAACCCAAACCCTAACCCAACCCAAAACCTAACCAC\n+\n>@==??>@?><>==@>====?<>=>=?>:====>===;=><=;=/>====?>====?>====?>====?=====?;=>>=??>>>;==>>=>=?:>=<@?/3;>/?>>:;<>:>./8>>-4/?-:;</==;.?-/7??6/:/,@/=/+;0-\n@E00121:21:H06AJALXX:2:1112:15890:22089/1\nCTAACCCTAACCCTAACCCTAACCCTAAGCTCGGCAGTGAACACGTCTGAACTCCAGACACTGATCATAACCTCGTCTCTCACCCTCTGCTTGAAAATAAACATAACCCTAACCCTAACCCTAACCCTAACGTTAACGCTAACCTTAGCAC\n+\n>@==?>>@?>===?>=>==?>=>==?>=7)/.3*,/*.1./=<,%8=/*.=,/==6>.=>=/*.-=/>-=+=/.8..;.-./,>.@./*?/>)>,<,2?>/*/8->:-=@?>7><>?/,9-=<-:9./,=+%.4-?<%,/4;,./=>),0-\n@E00121:21:H06AJALXX:2:1117:5202:1678/1\nCTAACCCTAACCCTAACCCTAACCCTAACCCTTAACCCTAACCCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACC\n+\n>@==?>>@?>===?>====?>====?=====?=>====?>=====?>====?><===?>/====;9===;9<==;/8<:==@;<>>>;;9>>;.3/:<>/8-=>>;8.=>9?<>>>->:=>?>??>??6<:??>/-6??@/@@@6?>,;-;\n@E00121:21:H06AJALXX:2:1203:16895:50129/1\nCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTACCCTTACCCTTACCCTAACCCTTACCCTTACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTAACCCAACCCTAACCCTAACCCTAACCCTAACCCTAACCCTA";

	TEST(FastQTests, FindTest)
	{
		std::stringstream ss;
		ss.str(fastQString.c_str());
		rufus::FastQParser fqparser(&ss, &std::cout);
		fqparser.parse();
	}

	TEST(FastQTests, FindTest2)
	{
		std::string filepath = "/uufs/chpc.utah.edu/common/home/ucgdlustre/u0991464/SimonsTryAgain/14590/SSC12411.proband.k25_m0_c7.HashList";
		auto kmerSet = rufus::HashParser::ParseFile(filepath);
	}
}

#endif //RUFUS_FILTER_FASTQTESTS_HPP
