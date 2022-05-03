CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
SET(CMAKE_CXX_STANDARD 14)

project(grootc)

find_package(LLVM REQUIRED CONFIG)

add_executable(grootc main.cpp)

llvm_map_components_to_libnames(LLVM_LIBS core native orcjit support)

target_link_libraries(grootc PRIVATE ${LLVM_LIBS})

