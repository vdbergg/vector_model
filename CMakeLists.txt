cmake_minimum_required(VERSION 3.12)
project(vector_model)

set(CMAKE_CXX_STANDARD 17)

add_executable(vector_model indexer/indexer.cpp vector_model/vector_model.cpp main.cpp indexer/indexer.h vector_model/vector_model.h wand/Wand.cpp wand/MinHeap.cpp)