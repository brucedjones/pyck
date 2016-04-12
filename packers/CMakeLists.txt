# Do this for each new packer
add_library(fccPacker fccPacker.cpp)
target_link_libraries(fccPacker packer)

add_library(hcpPacker hcpPacker.cpp)
target_link_libraries(hcpPacker packer)
