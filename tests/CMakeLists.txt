# =================================
# rufus - test
#
# text/CMakeLists.txt
# =================================

#configure_file (
#  "${CMAKE_CURRENT_SOURCE_DIR}/config/DataPaths.h.in"
#  "${CMAKE_CURRENT_SOURCE_DIR}/config/DataPaths.h"
#)

# set header and source files
set(RUFUS_TEST_SOURCES
  gtest_main.cpp
)

# Where Google Test's .h files can be found.
include_directories(
  ${CMAKE_SOURCE_DIR}
  ${GTEST_INCLUDE}
  ${GTEST_INCLUDE}/include
)
set(Boost_USE_MULTITHREADED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") # clang Doesnt use pthread
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()
#set(CMAKE_BUILD_TYPE Debug)


#create binary
add_executable(rufus_filter_tests
  ${RUFUS_TEST_SOURCES}
)

add_dependencies(rufus_filter_tests ${GTEST_PROJECT})

target_link_libraries(rufus_filter_tests
	${GTEST_LIB}
)
