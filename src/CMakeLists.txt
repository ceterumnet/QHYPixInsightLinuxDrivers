cmake_minimum_required (VERSION 2.8.1)
cmake_policy(SET CMP0015 NEW)

project(QHYPixInsightLinuxDrivers)

set(PIXINSIGHT64 ${CMAKE_CURRENT_SOURCE_DIR}/../../PixInsight/bin CACHE PATH "PixInsight 64bit bin")
set(PCL_SDK_HOME  ${CMAKE_CURRENT_SOURCE_DIR}/../../PCL CACHE PATH "PixInsight SDK")
set(IMAGE_ACQ_HOME ${CMAKE_CURRENT_SOURCE_DIR}/../../ImageAcquisition/src CACHE PATH "ImageAcquisition Root Src Dir")
set(QHY_HOME ${CMAKE_CURRENT_SOURCE_DIR}/../../QHYCCD_Linux CACHE PATH "ImageAcquisition Root Src Dir")

set(CMAKE_USER_MAKE_RULES_OVERRIDE
  ${CMAKE_CURRENT_SOURCE_DIR}/c_flag_overrides.cmake)
set(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX
  ${CMAKE_CURRENT_SOURCE_DIR}/cxx_flag_overrides.cmake)

include_directories(${PCL_SDK_HOME}/include)
include_directories(${IMAGE_ACQ_HOME})
include_directories(${QHY_HOME}/src)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB all_SOURCES "*.cpp" "*.c")
file(GLOB all_HEADERS "*.hpp" "*.h")

source_group("headers" FILES ${all_HEADERS})

add_subdirectory("qhy5_ii")
add_subdirectory("qhy5_ii_raw")