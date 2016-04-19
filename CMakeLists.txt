cmake_minimum_required(VERSION 2.8)
project (pyck)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(pyckLibs "")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")

add_subdirectory(packers)
add_subdirectory(shapes)
add_subdirectory(writers)

find_package(OpenMP REQUIRED)
if(OPENMP_FOUND)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_library(cylindricalPacker cylindricalPacker.cpp)
list(APPEND pyckLibs "cylindricalPacker")
add_library(ellipsoidalPacker ellipsoidalPacker.cpp)
list(APPEND pyckLibs "ellipsoidalPacker")
add_library(pack pack.cpp)
list(APPEND pyckLibs "pack")
add_library(model model.cpp)
list(APPEND pyckLibs "model")
add_library(shape shape.cpp)
list(APPEND pyckLibs "shape")
add_library(boundingBox boundingBox.cpp)
list(APPEND pyckLibs "boundingBox")
add_library(packer packer.cpp)
list(APPEND pyckLibs "packer")
add_library(writer writer.cpp)
list(APPEND pyckLibs "writer")
add_library(intField intField.cpp)
list(APPEND pyckLibs "intField")
add_library(doubleField doubleField.cpp)
list(APPEND pyckLibs "doubleField")

target_link_libraries(pack shape boundingBox packer cylindricalPacker ellipsoidalPacker)
target_link_libraries(boundingBox shape)
target_link_libraries(shape boundingBox)
target_link_libraries(writer intField doubleField)
target_link_libraries(model pack writer)


#add_executable(pyck pyck.cpp)

#target_link_libraries(pyck pack shape packer writer model)

# Do this for each new packer
#target_link_libraries(pyck fccPacker)
#target_link_libraries(pyck hcpPacker)
#target_link_libraries(pyck bccPacker)
#target_link_libraries(pyck cubicPacker)

# Do this for each new shape
#target_link_libraries(pyck cuboid)
#target_link_libraries(pyck sphere)
#target_link_libraries(pyck cylinder)

# Do this for each new writer
#target_link_libraries(pyck sparkWriter)


add_subdirectory(swig)
