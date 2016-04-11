cmake_minimum_required(VERSION 2.8)
project (pyck)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(OpenMP)

add_library(domain domain.cpp)
add_library(shape shape.cpp)
add_library(boundingBox boundingBox.cpp)
add_library(cuboid cuboid.cpp)
add_library(packer packer.cpp)
add_library(fccPacker fccPacker.cpp)

target_link_libraries(domain shape boundingBox packer)
target_link_libraries(boundingBox shape)
target_link_libraries(shape boundingBox)
target_link_libraries(cuboid shape boundingBox)
target_link_libraries(fccPacker packer)

add_executable(pyck pyck.cpp)

target_link_libraries(pyck domain shape boundingBox cuboid packer fccPacker)
