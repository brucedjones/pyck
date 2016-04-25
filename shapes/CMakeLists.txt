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

add_library(triprism triprism.cpp)
target_link_libraries(triprism shape boundingBox)
list(APPEND pyckLibs "triprism")

set(pyckLibs "${pyckLibs}" PARENT_SCOPE)
