cmake_minimum_required(VERSION 3.5)

project(NeuronetMaster LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(MSVC_BUILDSYSTEM MSVC AND NOT ${CMAKE_MAKE_PROGRAM} STREQUAL "nmake")
#if(MSVC_BUILDSYSTEM)
#    set(INSTALLER_DIR ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>)
#else()
#    set(INSTALLER_DIR ${CMAKE_CURRENT_BINARY_DIR})
#endif()

INCLUDE_DIRECTORIES(
    $ENV{PYTHON37}/include
    E:/tools/opencv/build/include
    )

#LINK_DIRECTORIES($ENV{PYTHON37}/libs)
# PTH to LIB of python for neuronet
link_libraries(C:/Users/qwert/AppData/Local/Programs/Python/Python37/libs/python37.lib)



link_libraries(C:/Users/qwert/AppData/Local/Programs/Python/Python37/libs/python37_d.lib)

find_package(Qt5 REQUIRED Core Gui Network)

find_package(OpenCV REQUIRED)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/utils
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(NeuronetMaster
  main.cpp
  src/NeuronetMaster.cpp
  src/CommunicationMaster.cpp
  include/CommunicationMaster.h
  include/NeuronetMaster.h
)

target_link_libraries(NeuronetMaster Qt5::Core)
target_link_libraries(NeuronetMaster Qt5::Gui)
target_link_libraries(NeuronetMaster Qt5::Network)
