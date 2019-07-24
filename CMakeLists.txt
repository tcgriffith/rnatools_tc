# Specify the minimum version for CMake
project(rnatools_tc)
cmake_minimum_required(VERSION 2.8) 

# Project's name



set(CMAKE_BINARY_DIR ${CMAKE_HOME_DIRECTORY}/bin)
set(CMAKE_SOURCE_DIR ${CMAKE_HOME_DIRECTORY}/src)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_HOME_DIRECTORY}/include)




set(SRCPDB 
    ${CMAKE_SOURCE_DIR}/PDB.cc  
    ${CMAKE_SOURCE_DIR}/pdb_utils.cc 
    )



# executables

# add_executable(tester ${SRCPDB} ${CMAKE_SOURCE_DIR}/dfire_PDB.cc ${CMAKE_SOURCE_DIR}/tester.cc)

add_executable(getseq ${SRCPDB} ${CMAKE_SOURCE_DIR}/getseq.cc)

add_executable(getcontacts  ${SRCPDB} ${CMAKE_SOURCE_DIR}/getcontacts.cc)

