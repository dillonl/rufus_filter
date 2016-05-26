#include "gtest/gtest.h"

#include "HashParserTests.hpp"
#include "FastQParserTests.hpp"

//#include "config/DataPaths.h"
//#include "AlignmentParserTests.hpp"
//#include "SparseKmerSetTests.hpp"

GTEST_API_ int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
