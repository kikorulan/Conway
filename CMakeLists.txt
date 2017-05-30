#/*============================================================================
#
#  MYPROJECT: A software package for whatever.
#
#  Copyright (c) University College London (UCL). All rights reserved.
#
#  This software is distributed WITHOUT ANY WARRANTY; without even
#  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#  PURPOSE.
#
#  See LICENSE.txt in the top level directory for details.
#
#============================================================================*/

######################################################################
# Set the minimum CMake version.
######################################################################
set(MYPROJECT_CMAKE_MINIMUM_REQUIRED_VERSION 2.8)
cmake_minimum_required(VERSION ${MYPROJECT_CMAKE_MINIMUM_REQUIRED_VERSION})

##################################################################################
# Set some CMake Policies.
# See http://cmake.org/cmake/help/cmake-2-8-docs.html#section_Policies for details
##################################################################################
set(project_policies )
foreach(policy ${project_policies})
  if(POLICY ${policy})
    cmake_policy(SET ${policy} NEW)
  endif()
endforeach()


######################################################################
# Setting supported build types. Should ONLY be Release or Debug.
######################################################################
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Valid options are Release or Debug" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Release" "Debug")
endif()

if (NOT (CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "Debug"))
  message(FATAL_ERROR "Build type \"${CMAKE_BUILD_TYPE}\" is not supported.")
endif()

######################################################################
# Make sure Git is available.
######################################################################
find_package(Git REQUIRED)

######################################################################
# Setup the path to load CMake macros, and extra CMake files.
######################################################################
set(CMAKE_MODULE_PATH
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/CMake
    ${CMAKE_MODULE_PATH}
   )
   
######################################################################
# Choose C++ standard
######################################################################
set(MYPROJECT_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS 0)
set(CMAKE_CXX_STANDARD ${MYPROJECT_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED 1)

add_compile_options(-std=c++11)

##############################################################################
# Build options.
##############################################################################
option(BUILD_TESTING "Build Unit tests." ON)

######################################################################
# Add Mandatory Requirements
######################################################################
set(ALL_THIRD_PARTY_LIBRARIES)
set(CONWAY_LIBRARY conwayGL)
set(ADDITIONAL_SEARCH_PATHS ${CMAKE_BINARY_DIR}/bin/${VS_BUILD_TYPE})


######################################################################
# MPI
######################################################################

find_package(MPI REQUIRED)
list(APPEND ALL_THIRD_PARTY_LIBRARIES ${MPI_C_LIBRARIES} ${MPI_CXX_LIBRARIES})
include_directories(${MPI_C_INCLUDE_PATH})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MPI_C_COMPILE_FLAGS}")


######################################################################
# Boost
######################################################################

# Example of:
#   (1) Standard, widely used library
#   (2) Mostly header library, some compiled libraries
#   (3) Your CMake probably has a standard FindBoost.cmake in its distribution,
#       so Boost is probably found by CMake's own FindBoost.cmake.

set(BOOST_LIBRARYDIR "/usr/lib/x86_64-linux-gnu")
set(BOOST_INCLUDEDIR "/usr/include/boost")
set(Boost_DEBUG ON)
set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_NO_BOOST_CMAKE ON)
if(BUILD_SHARED_LIBS)
  set(Boost_USE_STATIC_LIBS OFF)
  set(Boost_USE_STATIC_RUNTIME OFF)
else()
  set(Boost_USE_STATIC_LIBS ON)
  set(Boost_USE_STATIC_RUNTIME ON) 
endif()
#find_package(Boost 1.56 EXACT COMPONENTS filesystem system date_time regex REQUIRED)
find_package(Boost COMPONENTS mpi REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

list(APPEND ALL_THIRD_PARTY_LIBRARIES ${Boost_LIBRARIES})
add_definitions(-DBUILD_Boost)
set(ADDITIONAL_SEARCH_PATHS "${BOOST_ROOT}/bin;${ADDITIONAL_SEARCH_PATHS}")


######################################################################
# Add code folders.
######################################################################
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
foreach(type LIBRARY RUNTIME ARCHIVE)
  set(output_dir ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_${type}_OUTPUT_DIRECTORY ${output_dir} CACHE INTERNAL "Single output directory for building all libraries.")
  mark_as_advanced(CMAKE_${type}_OUTPUT_DIRECTORY)
endforeach()
include_directories(${CMAKE_SOURCE_DIR}/Code/Lib)
add_subdirectory(Code)
