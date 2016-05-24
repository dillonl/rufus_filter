# =================================
# rufus_filter
#
# tools/CMakeLists.txt
# =================================

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

# set header and source files
set(RUFUS_TOOLS_SOURCES
	rufus_filter.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") # clang Doesnt use pthread
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

#set(CMAKE_BUILD_TYPE Debug) # uncomment this when you need a debug build

#create binary
add_executable(rufus_filter
  ${RUFUS_TOOLS_SOURCES}
)
