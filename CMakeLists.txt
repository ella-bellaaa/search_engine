cmake_minimum_required(VERSION 3.15)
project(FinalProjExamples)

# filesystem.h require C++17
set(CMAKE_CXX_STANDARD 17)

file(COPY sample_data/ DESTINATION sample_data/)

# show compiler output and enable warnings
set(CMAKE_VERBOSE_MAKEFILE ON)
#add_compile_options(-Wall -Wextra -pedantic)

#set (CMAKE_CXX_FLAGS_DEBUG -O3)
#set (CMAKE_CXX_FLAGS_RELEASE -O3)
add_executable(rapidJSONExample rapidJSONExample.cpp AvlTree.h DocumentProcessor.cpp DocumentProcessor.h userInterface.cpp userInterface.h indexHandler.cpp indexHandler.h doc.cpp doc.h porter2_stemmer.cpp porter2_stemmer.h test.cpp)

# this makes sure we also link rapidjson
target_include_directories(rapidJSONExample PRIVATE rapidjson/)

set(CMAKE_VERBOSE_MAKEFILE OFF)
