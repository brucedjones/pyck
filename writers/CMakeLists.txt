# Do this for each new writer
add_library(sparkWriter sparkWriter.cpp)
target_link_libraries(sparkWriter writer)
