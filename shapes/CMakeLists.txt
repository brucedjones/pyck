# Do this for each new shape
add_library(cuboid cuboid.cpp)
target_link_libraries(cuboid shape boundingBox)
