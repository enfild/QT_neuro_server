cmake_minimum_required(VERSION 3.5)

project(NeuronetMaster LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

INCLUDE_DIRECTORIES(
    $ENV{PYTHON37}/include
    E:/tools/opencv/build/include
    )

LINK_DIRECTORIES($ENV{PYTHON37}/libs)
# PTH to LIB of python for neuronet
link_libraries(C:/Users/qwert/AppData/Local/Programs/Python/Python37/libs/python37.lib)

find_package(Qt5 REQUIRED Core Gui Network)

find_package(OpenCV REQUIRED)

add_executable(NeuronetMaster
  main.cpp
  src/NeuronetMaster.cpp
  src/CommunicationMaster.cpp
  include/CommunicationMaster.h
  include/NeuronetMaster.h
)
#qt5_use_modules(NavigationServerTest Core Network Test)

target_link_libraries(NeuronetMaster Qt5::Core)
target_link_libraries(NeuronetMaster Qt5::Gui)
target_link_libraries(NeuronetMaster Qt5::Network)
