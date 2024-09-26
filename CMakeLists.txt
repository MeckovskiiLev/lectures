cmake_minimum_required(VERSION 3.5.0)
project(labwork1 VERSION 0.1.0 LANGUAGES C CXX)

SET(CMAKE_CXX_STANDARD 23)

add_executable(AnalyzeLog main.cpp output_directory_arguments.cpp input_check.cpp print_check.cpp time_from.cpp window_check.cpp stats_check.cpp)

