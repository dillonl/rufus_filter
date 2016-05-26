#ifndef RUFUS_FILTER_FILTERTESTS_HPP
#define RUFUS_FILTER_FILTERTESTS_HPP

#include <string>

namespace
{
	int loop = 100000000;
	std::string testString = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aliquam ac justo id enim egestas faucibus in eget odio. In vitae nunc ut ligula maximus amet.";
	TEST(FilterTests, FindTest)
	{
		for (int i = 0; i < loop; ++i)
		{
			size_t pos = testString.find(' ', 0);
			int count = 0;
			while (pos != std::string::npos)
			{
				pos = testString.find(' ', pos+1);
				++count;
			}
		}
	}

	TEST(FilterTests, LoopTest)
	{
		int count = 0;
		const char* tmp;
		for (int i = 0; i < loop; ++i)
		{
			tmp = testString.c_str();
			while (*tmp)
			{
				if (*tmp == ' ')
				{
					++count;
				}
				++tmp;
			}
		}
	}
}

#endif //RUFUS_FILTER_FILTERTESTS_HPP
