cmake_minimum_required(VERSION 2.8)
project (pyck)

set(pyckLibs "")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")

add_subdirectory(pack)
add_subdirectory(shapes)
add_subdirectory(writers)

find_package(OpenMP REQUIRED)
if(OPENMP_FOUND)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_library(pack pack.cpp)
list(APPEND pyckLibs "pack")
add_library(model model.cpp)
list(APPEND pyckLibs "model")
add_library(shape shape.cpp)
list(APPEND pyckLibs "shape")
add_library(boundingBox boundingBox.cpp)
list(APPEND pyckLibs "boundingBox")
add_library(writer writer.cpp)
list(APPEND pyckLibs "writer")
add_library(intField intField.cpp)
list(APPEND pyckLibs "intField")
add_library(doubleField doubleField.cpp)
list(APPEND pyckLibs "doubleField")

# Utility libraries
add_library(progressBar progressBar.cpp)

target_link_libraries(pack shape)
target_link_libraries(boundingBox shape)
target_link_libraries(shape boundingBox)
target_link_libraries(writer intField doubleField)
target_link_libraries(model pack writer)


#add_executable(pyckcpp pyck.cpp)

#target_link_libraries(pyckcpp pack shape packer writer model cylindricalPacker ellipsoidalPacker)

# Do this for each new packer
#target_link_libraries(pyckcpp fccPacker)
#target_link_libraries(pyckcpp hcpPacker)
#target_link_libraries(pyckcpp bccPacker)
#target_link_libraries(pyckcpp cubicPacker)

# Do this for each new shape
#target_link_libraries(pyckcpp cuboid)
#target_link_libraries(pyckcpp sphere)
#target_link_libraries(pyckcpp cylinder)
#target_link_libraries(pyckcpp triprism)

# Do this for each new writer
#target_link_libraries(pyckcpp ${pyckLibs})


add_subdirectory(swig)
