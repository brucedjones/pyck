set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")

find_package(OpenMP REQUIRED)
if(OPENMP_FOUND)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_library(packer packer.cpp)
list(APPEND pyckLibs "packer")

add_library(structuredPack structuredPack.cpp)
target_link_libraries(structuredPack pack shape boundingBox packer progressBar)
list(APPEND pyckLibs "structuredPack")

add_library(cylindricalPacker cylindricalPacker.cpp)
target_link_libraries(cylindricalPacker pack shape)
list(APPEND pyckLibs "cylindricalPacker")

add_library(ellipsoidalPacker ellipsoidalPacker.cpp)
target_link_libraries(ellipsoidalPacker pack shape)
list(APPEND pyckLibs "ellipsoidalPacker")

add_subdirectory(packers)

set(pyckLibs "${pyckLibs}" PARENT_SCOPE)
