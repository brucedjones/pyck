set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")

# Do this for each new packer
add_library(fccPacker fccPacker.cpp)
target_link_libraries(fccPacker packer)
list(APPEND pyckLibs "fccPacker")

add_library(hcpPacker hcpPacker.cpp)
target_link_libraries(hcpPacker packer)
list(APPEND pyckLibs "hcpPacker")

add_library(hcp2dPacker hcp2dPacker.cpp)
target_link_libraries(hcp2dPacker packer)
list(APPEND pyckLibs "hcp2dPacker")

add_library(bccPacker bccPacker.cpp)
target_link_libraries(bccPacker packer)
list(APPEND pyckLibs "bccPacker")

add_library(cubicPacker cubicPacker.cpp)
target_link_libraries(cubicPacker packer)
list(APPEND pyckLibs "cubicPacker")

set(pyckLibs "${pyckLibs}" PARENT_SCOPE)
