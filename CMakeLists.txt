# =================================
# RUFUS
#
# RUFUS/CMakeLists.tx
# =================================


#Set up min CMake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#Set project name
PROJECT(RUFUS_FILTER)

SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "1")
SET(VERSION_PATCH "0")
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

IF("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
  MESSAGE(SEND_ERROR "In-source builds are not allowed, please build this in the bin directory!")
ENDIF("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")

#set(CMAKE_BUILD_TYPE Debug) # uncomment this when you need a debug build
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
SET(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -O3")

INCLUDE_DIRECTORIES(src)

# add subfolders
ADD_SUBDIRECTORY(cmakefiles)
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(tools)
ADD_SUBDIRECTORY(tests)
