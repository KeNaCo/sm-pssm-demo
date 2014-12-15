cmake_minimum_required(VERSION 2.8)
project(sm-pssm-demo)

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${sm-pssm-demo_SOURCE_DIR}/cmake")
# Set an output directory for our binaries
set(BUILD_DIR ${sm-pssm-demo_SOURCE_DIR}/build)

# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11 -pthread -lboost_thread -lboost_log_setup -lboost_log")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

# Look up SDL2 and add the include directory to our include path
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

# Look up BOOST
#set(Boost_USE_STATIC_LIBS ON) #if we want link static TODO prepinac
add_definitions(-DBOOST_LOG_DYN_LINK)
find_package(Boost COMPONENTS system log REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

#Look up glbinding
find_package(glbinding REQUIRED)
include_directories(${glbinding_INCLUDE_DIR})

#Look up assimp
find_package (assimp REQUIRED)
include_directories(${assimp_INCLUDE_DIR})

#Look up glm
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIR})

# Look in src to build binaries
add_subdirectory(src)
