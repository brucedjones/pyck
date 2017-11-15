cmake_minimum_required(VERSION 2.8)
project (pyck)

FIND_PACKAGE(PythonLibs)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

set(pyckLibs "")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_subdirectory(pack)
add_subdirectory(shapes)
add_subdirectory(writers)

find_package(OpenMP REQUIRED)
if(OPENMP_FOUND)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_library(pack pack.cpp)
list(APPEND pyckLibs "pack")
add_library(model model.cpp)
list(APPEND pyckLibs "model")
add_library(shape shape.cpp)
list(APPEND pyckLibs "shape")
add_library(boundingBox boundingBox.cpp)
list(APPEND pyckLibs "boundingBox")
add_library(writer writer.cpp)
list(APPEND pyckLibs "writer")
add_library(intField intField.cpp)
list(APPEND pyckLibs "intField")
add_library(doubleField doubleField.cpp)
list(APPEND pyckLibs "doubleField")

# Utility libraries
add_library(progressBar progressBar.cpp)

target_link_libraries(pack shape)
target_link_libraries(boundingBox shape)
target_link_libraries(shape boundingBox)
target_link_libraries(writer intField doubleField)
target_link_libraries(model pack writer)


#add_executable(pyckcpp pyck.cpp)

#target_link_libraries(pyckcpp pack shape packer writer model cylindricalPacker ellipsoidalPacker)

# Do this for each new packer
#target_link_libraries(pyckcpp fccPacker)
#target_link_libraries(pyckcpp hcpPacker)
#target_link_libraries(pyckcpp bccPacker)
#target_link_libraries(pyckcpp cubicPacker)

# Do this for each new shape
#target_link_libraries(pyckcpp cuboid)
#target_link_libraries(pyckcpp sphere)
#target_link_libraries(pyckcpp cylinder)
#target_link_libraries(pyckcpp triprism)

# Do this for each new writer
#target_link_libraries(pyckcpp ${pyckLibs})

set(CPACK_PACKAGE_VERSION "0.0.1")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_VENDOR "MIT Geonumerics")

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.txt")

option(USE_WIX_TOOLSET "Use WIX" true)

if (WIN32)
    if (USE_WIX_TOOLSET)
        set(CPACK_GENERATOR "WIX") # this need WiX Tooset installed and a path to candle.exe
        set(CPACK_WIX_TEMPLATE "${CMAKE_CURRENT_SOURCE_DIR}/install/windows/pyck.template.in")
        SET(CPACK_WIX_PRODUCT_GUID 7EC919B7-6484-49BF-8803-614CEBB4154A)
        SET(CPACK_WIX_UPGRADE_GUID 7EC919B7-6484-49BF-8803-614CEBB4154A)
        # SET(CPACK_WIX_PRODUCT_ICON ../rsc/app.ico)
        SET(CPACK_WIX_UI_BANNER  "${CMAKE_CURRENT_SOURCE_DIR}/install/windows/banner_493x58.bmp")
        SET(CPACK_WIX_UI_DIALOG  "${CMAKE_CURRENT_SOURCE_DIR}/install/windows/dialog_493x312.bmp")
    else ()
        set(CPACK_GENERATOR "NSIS") # this needs NSIS installed, and available
    endif ()
    set(CPACK_SOURCE_GENERATOR "ZIP")
    set(INSTALL_DEST .)
elseif ( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
    set(INSTALL_DEST /Applications/pyck.app/Contents/MacOS/)
    set(CPACK_GENERATOR "PackageMake")
else ()
  set(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "/usr/local")
  set(INSTALL_DEST local/pyck)
  # install(TARGETS solver DESTINATION ${INSTALL_DEST})
  install(FILES ${CMAKE_SOURCE_DIR}/install/unix/set_pyck_env.sh DESTINATION ${INSTALL_DEST})
    
  option(BUILD_RPM "Builds an RPM instead of a DEB" OFF)
  if(BUILD_RPM)
    set(CPACK_RPM_PACKAGE_AUTOREQ OFF) # should probably use CPACK_RPM_PACKAGE_CONFLICTS instead
    set(CPACK_GENERATOR "RPM")
  else()
    set(CPACK_GENERATOR "DEB")
    set(CPACK_SOURCE_GENERATOR "TGZ")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Bruce Jones") #required
  endif()
endif ()

# INSTALL(TARGETS ${SWIG_MODULE_swig_test_REAL_NAME} DESTINATION test)
install(FILES ${CMAKE_BINARY_DIR}/swig/pyck.py DESTINATION ${INSTALL_DEST})
install(FILES ${ZLIB_LIBRARY_RELEASE} DESTINATION ${INSTALL_DEST})

add_subdirectory(swig)

include(CPack)
