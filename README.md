# Build
## Prerequisites:
Cmake, Python, Swig, Visual Studio, zlib

## Linux
1. Navigate to the source directory in a terminal then execute,
2. ```./makedoc```
3. ```cmake . ```
4. ```make```
5. Build files with be placed in bin/

Note: The 'makedoc' script builds documentation and should be carried out prior to building to ensure python docstrings are up-to-date.

## Mac
If Swig is installed using MacPorts, install Python 3.x in order to compile and run pyck. Otherwise, instructions are identical to linux.

## Windows

1. Set the following environment variables, Example using Python 2.1.1:

    PYTHON_INCLUDE: D:\python21\include
    
    PYTHON_LIB: D:\python21\libs\python21.lib

2. Open CMake-gui and set source and build directories, hit configure.

3. CMake will not automatically find swigwin, so set the SWIG_EXECUTEABLE variable to the location of the swigwin executeable.

4. Repeatedly press configure until no more configuration is required, then click generate.

5. Navigate to the build directory and open the pyck.sln file with visual studio.

6. Set the build mode to Release, then build.

7. Built files will be placed in the source_directory/bin. Note: currently _pyck.pyd is placed in an incorrect directory, you will find it in bin/Release, copy it to bin/

8. To run the examples set the path on line 2 to the directory where pyck was built.

Build and run errors: Assuming CMake worked correctly, the most likely error is that you are attempting to build for 32bit against 64bit libs or vice versa.

# Using Pyck
## Importing pyck

The following lines should be placed at the beginning of any python script which uses pyck,

```python
import sys
sys.path.insert(0, '/path/to/src/bin'); # Set this to the path where pyck is compiled
import pyck       # Pyck library
import pyck_utils # Utility functions for creating simulation parameters
```

## Functionality Reference
Pyck functionality is all written in C++ and exposed in python via Swig bindings. All non-abstract classes in the C++ code are exposed in the python library. Inspect the doxygen documentation or source header files to determine functionality and correct arguments. Example scripts are given in the examples/ directory.

# Pyck Development
## Pack
Classes derived from pack should populate the positions and states arrays, set the numParticles variable, and set the dim variable (indicated dimensionality of the problem)

Classes derived from pack are also required to implement the MapShape function. This function must iterate over all particles and determine whether they are inside or outside of the shape. See the ellipsoidal or cylindrical packers for a general implementation based on position and state arrays.

## Shapes
All shapes are derived from the Shape class. Shapes should set a bounding box in the model (Cartesian) coordinate system. Shapes must also implement the IsInside method which takes a single length 3 array of doubles indicating a particles xyz coordinates.

## Writers
Writers are derived from the Writer class and must implement the Write(fname, positions, intFields, doubleFields, dim, numParticles) method. The purpose of this method is to take the packed model from Pyck and write it to a file. If a new output format is required, create a new writer.
