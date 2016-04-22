set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")

add_library(packer packer.cpp)
list(APPEND pyckLibs "packer")

add_library(structuredPack structuredPack.cpp)
target_link_libraries(structuredPack pack shape boundingBox packer)
list(APPEND pyckLibs "structuredPack")

add_library(cylindricalPacker cylindricalPacker.cpp)
target_link_libraries(cylindricalPacker pack shape)
list(APPEND pyckLibs "cylindricalPacker")

add_library(ellipsoidalPacker ellipsoidalPacker.cpp)
target_link_libraries(ellipsoidalPacker pack shape)
list(APPEND pyckLibs "ellipsoidalPacker")

add_subdirectory(packers)

set(pyckLibs "${pyckLibs}" PARENT_SCOPE)
