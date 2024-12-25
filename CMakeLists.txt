cmake_minimum_required(VERSION 3.5.1)
project(simple_atm_controller)

set(CMAKE_CXX_STANDARD 11)

add_executable(simple_atm_controller bank.cpp atmController.cpp)
