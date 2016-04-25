Prerequisites:
Cmake, Python, Swig, Visual Studio, zlib

Building on Windows
Download and install prerequisites.

Set the following environment variables, Example using Python 2.1.1:
PYTHON_INCLUDE: D:\python21\include
PYTHON_LIB: D:\python21\libs\python21.lib

Open CMake-gui
Set source and build directories and hit configure.

Cmake will not automatically find swigwin, so set the SWIG_EXECUTEABLE to the location of the swigwin executeable.

Press configure until no more ocnfiguration is required, then click generate.

Navigate to the build directory and open the pyck.sln file with visual studio.

Set the build mode to Release, then build.

Built files will be placed in the source_directory/bin. Note: currently _pyck.pyd is placed in an incorrect directory, you will find it in bin/Release, copy it to bin/

Build and run errors: Assuming CMake worked correctly, the most likely error is that you are attempting to build for 32bit against 64bit libs or vice versa.

To run the examples set the path on line 2 to the directory where pyck was built.