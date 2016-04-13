cmake_minimum_required(VERSION 2.8)
project (pyck)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(packers)
add_subdirectory(shapes)

find_package(OpenMP REQUIRED)
if(OPENMP_FOUND)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

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
target_link_libraries(pyck hcpPacker)
target_link_libraries(pyck bccPacker)
target_link_libraries(pyck cubicPacker)

# Do this for each new shape
target_link_libraries(pyck cuboid)
target_link_libraries(pyck sphere)
target_link_libraries(pyck cylinder)
