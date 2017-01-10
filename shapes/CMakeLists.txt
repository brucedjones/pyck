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

add_library(stlShape stlShape.cpp)
target_link_libraries(stlShape shape boundingBox)
list(APPEND pyckLibs "stlShape")

FIND_PACKAGE(PythonLibs)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
add_library(pyShape pyShape.cpp)
target_link_libraries(pyShape shape boundingBox)
list(APPEND pyckLibs "pyShape")

add_library(compositeShape compositeShape.cpp)
target_link_libraries(compositeShape shape boundingBox)
list(APPEND pyckLibs "compositeShape")

add_library(convexhull2D convexhull2D.cpp)
target_link_libraries(convexhull2D shape boundingBox)
list(APPEND pyckLibs "convexhull2D")

set(pyckLibs "${pyckLibs}" PARENT_SCOPE)
