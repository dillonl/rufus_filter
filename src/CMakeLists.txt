#set(CMAKE_BUILD_TYPE Debug) # uncomment this when you need a debug build
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
SET(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -O3")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") # clang Doesnt use pthread
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}
	${CXXOPTS_INCLUDE}
)

set(RUFUS_UTIL_SOURCES
  util/commandline_parser.cpp
  )

add_library(rufus_src_lib
  ${RUFUS_UTIL_SOURCES}
  )

SET(RUFUS_SRC_LIB rufus_src_lib CACHE STRING "THE SOURCE LIBRARY") #add rufus_src and rufus_utils to the list of core libs
