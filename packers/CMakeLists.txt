# Do this for each new packer
add_library(fccPacker fccPacker.cpp)
target_link_libraries(fccPacker packer)
