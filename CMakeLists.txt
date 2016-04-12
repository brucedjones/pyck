cmake_minimum_required(VERSION 2.8)
project (pyck)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(packers)
add_subdirectory(shapes)

find_package(OpenMP)

add_library(domain domain.cpp)
add_library(shape shape.cpp)
add_library(boundingBox boundingBox.cpp)
add_library(packer packer.cpp)

target_link_libraries(domain shape boundingBox packer)
target_link_libraries(boundingBox shape)
target_link_libraries(shape boundingBox)

add_executable(pyck pyck.cpp)

target_link_libraries(pyck domain shape packer)

# Do this for each new packer
target_link_libraries(pyck fccPacker)

# Do this for each new shape
target_link_libraries(pyck cuboid)
target_link_libraries(pyck sphere)
target_link_libraries(pyck cylinder)
