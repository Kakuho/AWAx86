cmake_minimum_required(VERSION 3.1...3.29)

project(awa4x86 VERSION 1.0 
                    LANGUAGES CXX)

# main 

include_directories(src)

set(CXX_SRCS 
      src/lexer.hpp
      src/awatismconverter.hpp
   )

add_executable(awa4x86 src/main.cpp ${CXX_SRCS})

target_compile_features(awa4x86 PUBLIC cxx_std_20)

set_target_properties(awa4x86 PROPERTIES CXX_EXTENSIONS OFF)

target_compile_options(awa4x86 PRIVATE -g -std=c++20)

#add_custom_command(
#    TARGET awa4x86
#    POST_BUILD
#    COMMAND awa4x86
#)
