# Do this for each new shape
add_library(cuboid cuboid.cpp)
target_link_libraries(cuboid shape boundingBox)
add_library(sphere sphere.cpp)
target_link_libraries(sphere shape boundingBox)
add_library(cylinder cylinder.cpp)
target_link_libraries(cylinder shape boundingBox)
