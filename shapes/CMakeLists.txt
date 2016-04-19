set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")

# Do this for each new shape
add_library(cuboid cuboid.cpp)
target_link_libraries(cuboid shape boundingBox)
list(APPEND pyckLibs "cuboid")

add_library(sphere sphere.cpp)
target_link_libraries(sphere shape boundingBox)
list(APPEND pyckLibs "sphere")

add_library(cylinder cylinder.cpp)
target_link_libraries(cylinder shape boundingBox)
list(APPEND pyckLibs "cylinder")

set(pyckLibs "${pyckLibs}" PARENT_SCOPE)
