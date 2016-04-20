set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")

# Do this for each new writer
add_library(sparkWriter sparkWriter.cpp)
target_link_libraries(sparkWriter writer)

# Section below is only required for SparkWriter
find_package( ZLIB REQUIRED )
add_library(base64 base64.cpp)
target_link_libraries(sparkWriter base64)
if ( ZLIB_FOUND )
    include_directories( ${ZLIB_INCLUDE_DIRS} )
    target_link_libraries( sparkWriter ${ZLIB_LIBRARIES} )
endif( ZLIB_FOUND )
list(APPEND pyckLibs "sparkWriter")

set(pyckLibs "${pyckLibs}" PARENT_SCOPE)