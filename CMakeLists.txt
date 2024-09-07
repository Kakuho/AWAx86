cmake_minimum_required(VERSION 3.1...3.29)

project(awax86 VERSION 1.0 
               LANGUAGES CXX)

# main 

include_directories(src)

set(CXX_SRCS 
      src/lexer.hpp
      src/awatismconverter.hpp  src/awatismconverter.cpp
      src/awassembler.hpp       src/awassembler.cpp
      src/lexer.hpp             src/lexer.cpp
      src/x86codegen.hpp        src/x86codegen.cpp
      src/pipeline.hpp          src/pipeline.cpp
)

add_executable(awax86 src/main.cpp ${CXX_SRCS})

target_compile_options(awax86 PRIVATE -g -std=c++20)

# unit tests

find_package(Catch2 3 REQUIRED)

set(TEST_SRCS 
      tests/awasm/awassembler.cpp
      tests/lexer/lexer.cpp
      tests/codegen/controlflow.cpp
      tests/utils/bubblering.cpp

      tests/codegen/pilemanip/blow.cpp
      tests/codegen/pilemanip/pop.cpp
      tests/codegen/pilemanip/duplicate.cpp

   )

add_executable(tests ${TEST_SRCS} ${CXX_SRCS})

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

target_compile_options(tests PRIVATE -g -std=c++20)

#add_custom_command(TARGET tests POST_BUILD COMMAND tests)
