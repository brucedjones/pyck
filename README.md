# About
Pyck is a preprocessing utillity developed by [MIT Geonumerics](http://geonumerics.mit.edu). Pyck has a python frontend, with a C++ backend, where all packing operations are parallelized using OpenMP. Designed to be method and code agnostic, Pyck is written in a general way such that it would be suitable for any any typical particle method (SPH, DEM, etc).

Pyck is licensed under the MIT license

# Build
## Prerequisites:
* [zlib](https://github.com/madler/zlib)
* [swig](http://www.swig.org/)
* [CUDA](https://developer.nvidia.com/cuda-downloads)
* [cmake](https://cmake.org/)
* [Python](http://www.python.org)
* Visual Studio (Windows only)

## Linux
1. Clone the repository
2. Create a build repository, eg. pyck-build
2. ```./path/to/src/makedoc```
3. Navigate to build directory
3. ```cmake /path/to/src ```
4. ```make```
5. To run either,
    * Add build_directory/swig to PATH
    * Copy the contents of build_directory/swig the directory where you want to run your script
    * Add build_directory/swig to path in your script (See below)
6. If using pyck utils either copy it to the pyck binary folder or to the same folder as your script
    
Note: The 'makedoc' script builds documentation and should be carried out prior to building to ensure python docstrings are up-to-date.

## Mac
Instructions are similar to Linux but :
1. CMake uses the default Apple’s C/C++ compiler clang to compile pyck but it does not support OpenMP.
	* It is needed to manually modify the CMake script by entering ```ccmake .``` and to perform the following changes (assuming the gcc version installed is gcc 4.9) :
		* CMAKE_C_COMPILER = gcc-mp-4.9
		* CMAKE_CXX_COMPILER = g++-mp-4.9
2. Swig should be installed either using MacPorts or Homebrew.
	* For Macports, the following packages are need : ```swig```, ```swig-python```
3. If Swig is installed using MacPorts, install Python 3.x in order to compile and run pyck.

## Windows

In the steps that follow, ensure that the cmake generator is set for your desired version of visual studio, and is the same for both zlib and pyrite. For example "Visual Studio 14 2015 Win64".

### Build zlib

1. Download [source](https://github.com/madler/zlib)
2. Create zlib-build directory
3. Open cmake-gui
4. Select source directory and zlib-build directory
5. Click configure until configuration done
6. Click generate
7. Open zlib.sln in visual studio
8. Select "Release" build and build
9. Built lib will be in zlib-build/Release
10. Copy zlib-build/zconf.h into source directory
11. zlib include directory will be the source directory

### Build pyck

1. Open CMake-gui and set source and build directories (These should be separate directories), hit configure.

2. Click configure, cmake will require information for SWIG_EXECUTEABLE, ZLIB_INCLUDE_DIR, ZLIB_LIBRARY_RELEASE (zlib.lib)
    * You may need to click configure a number of times, adding this information as you go. You may also need to check the "Advanced" box in cmake-gui

3. Generate

4. Open build_directory/pyck.sln

5. Set the build mode to Release, then build.

6. Built files will be+ placed in build_directory/swig/Release/. Note: currently pyck.py is placed in build_directory/swig/ and should be copied in to build_directory/swig/Release/

7. To run either,
    * Add build_directory/swig/Release/ to PATH
    * Copy these files in to the directory where you want to run your script
    * Add the build directory to path in your script (See below)

Build and run errors: Assuming CMake worked correctly, the most likely error is that you are attempting to build for 32bit against 64bit libs or vice versa.

# Getting started
## Importing pyck

In order to use pyck you must import the compiled library. If your python script is in the same directory as your compiled pyck module, then you can simply use,

```python
import pyck
```

To run a script in a different directory  you need to add pyck to your python path. This can be done in two ways, noting that pycks python interface is actually compiled in to the swig/ subdirectory.

Option 1 (Preferred), add the path to pyck to the PYTHONPATH environment variable,

```bash
$ export PYTHONPATH=${PYTHONPATH}:/path/to/pyck/swig
```

Option 2, add the path to pyck within the script before importing pyck.

```python
import sys
sys.path.insert(0, '/path/to/pyck/swig'); # Set this to the path where pyck is compiled
import pyck       # Pyck library
```

## Creating a domain
### Packers
To create a domain to packed with a structured packing configuration a packer must first be defined reflecting the desired packing configuration. Options are as follows,

```python
cubic                 = pyck.CubicPacker([Lx,Ly,Lz],minSeparation);
faceCenteredCubic     = pyck.FccPacker([Lx,Ly,Lz],minSeparation);
bodyCenteredCubic     = pyck.BccPacker([Lx,Ly,Lz],minSeparation);
hexagonalClosePack    = pyck.HcpPacker([Lx,Ly,Lz],minSeparation);
hexagonalClosePack2d  = pyck.Hcp2dPacker([Lx,Ly,0],minSeparation);
```

In which `Lx`, `Ly`, and `Lz`, are the domain lengths in the x, y, and z directions respectively. `minSeparation` is the minimum separation distance between particles. To pack a 2D domain, simply set `Lz` to 0. Note: the only packing configurations that make sense in 2D are Cubic and Hexagonal Close Packing.

With a packer defined, the domain is initialized with the following,

```python
pack = pyck.StructuredPack(cubic);
```

Take care to create the packer separately to the StructuredPack object. If the Packer is dynamically created within the constructor argument of structed pack (eg. `StructuredPack(pyck.CubicPacker([Lx,Ly,Lz],radius)`) pyck will crash. This is because the python garbage collects the CubicPacker as soon as the StructuredPack constructor returns.

#### Particle Volume
Packers can be used to compute an approximate particle volume, for example,

```python
particleVolume = cubic.GetParticleVolume();
```

This approximation is computed as the domain volume / number of particles.

#### Rotating the pack
Packers which use a hexagonal packing configuration can have their orientation rotated. To rotate the pack 90 degrees add a boolean `True` flag as the last option to the packer construction. For example,

```python
hexagonalClosePack = pyck.HcpPacker([Lx,Ly,Lz],minSeparation,True);
```

#### Offsetting the domain
By default pyck will pack a domain from 0 to L in each direction, so the lower left corner of the domain will always be (0,0,0). In some cases it is desireable to move the domain by some amount. To do this an offset vector may be specified in the packer constructor such as,

```python
cubic = pyck.CubicPacker([Lx,Ly,Lz],minSeparation,[Ox,Oy,Oz]);
```
The offset vector is always the last argument in the packer constructor. If using the offset vector with a packer which supports packing rotation, such as HcpPacker, the optional boolean flag is now manadatory and must be set as either `True` or `False` for the offset to be correctly applied. For instance,

```python
hexagonalClosePack = pyck.HcpPacker([Lx,Ly,Lz],minSeparation,False,[Ox,Oy,Oz]);
```

#### Periodic Domains
All packers pack in a periodic fashion. That is, if the domain is fully filled with particles, the domain boundaries will be periodic. However to ensure periodicity in a model, the domain extent must be correctly specified so that the distance between particles accross the boundary is correct. For a packer created for a domain of size, `L`, the periodic domain size, `Lp` is returned by the `GetPeriodicExtent()` function so that,

```python
hexagonalClosePack  = pyck.HcpPacker(L,minSeparation);
Lp = hexagonalClosePack.GetPeriodicExtent();
```
Where `Lp` is a vector of length 3.

## Packing shapes

All shapes within pyck are specified in two ways, their geometric properties, and an integer `tag` which is applied to all particles packed within that shape. The shapes `tag` is always the first argument in the constructor of a shape. Examples are given here for cuboids, spheres, StlShape, and PyShape, for reference on other shapes see the doxygen documentation or the shape classes in the shapes/ directory.


### Cuboid

The geometry of a cuboid is defined by a lower-left point, `p1`, and an upper-right point `p2`.

```python
cube = pyck.Cuboid(tag,[p1x,p1y,p1z],[p2x,p2y,p2z]);
```

### Sphere

The geometry of a sphere is defined by a centroid, `p1`, and a `radius`.

```python
sphere = pyck.Sphere(tag,[p1x,p2x,p3x],radius);
```
### Convex hull in 2D

The geometry of a convex polygon is defined by n-number (n>2) of vertices in either clockwise or counter-clockwise order (both work).

```python
convexh = pyck.ConvexHull2D(tag,[[p1x,p1y,p1z],[p2x,p2y,p2z],.....,[pnx,pny,pnz]]);
```

### StlShape

Using an StlShape, it is possible to pack CAD geometries with pyck. An StlShape packs a boundary surface mesh and determines if a particle is within the CAD geometry by applying the boundary intersection counting technique. This technique is very robust with regard to the quality of the mesh, and will work for both convex and concave shapes. For best results ensure that there is no duplication of facets, and that the boundary surface mesh is watertight.

An StlShape is defined as,

```python
stlShape = pyck.StlShape(tag,filename,translation,scale,rotation_axis,rotation_angle);
```

Where,

* `filename` (required) The STL filename
* `translation` (optional) Length 3 vector specifying a translation to move the STL file
* `scale` (optional) Scalar used to scale the geometry
* `rotation_axis` (optional) Length 3 vector specifying the axis of rotation about which to rotate the geometry
* `rotation_angle` (optional, rquired if rotation_axis specified) Angle in radians by which the geometry is rotated about the rotation axis

### PyShape

PyShape is a shape which is defined by a python callback function. PyShape is used as follows.

```python
pyshape = pyck.PyShape(tag,[p1x,p1y,p1z],[p2x,p2y,p2z],isInside);
```

Where the `p1` and `p2` arrays are the coordinates of points defining a bounding box in which particles may be inside the shape. `isInside` is a python function used to determine whether a given particle is inside the shape, and must be defined by the user. An example is given here for a sphere.

```python
def isInside(x,y,z):
    dx = x-1.0;
    dy = y-1.0;
    dz = z-1.0;
    r = 0.3;
    if(dx*dx+dy*dy+dz*dz<r*r):
        return True
    return False
```

The isInside callback takes three arguments, `x`, `y`, and `z`, which are the coordinates of a particle. This example specifies a sphere centered at coordinates (1.0,1.0,1.0) with a radius of 0.3. If a particle is inside this sphere the function returns true, if it is outside the function returns false.

Unfortunately, due to the way in which python-c++ interoperability works, python callbacks can only be run in serial. If you find that you need a new shape and PyShape is too slow for your application, consider implementing it as a native c++ class instead.

### CompositeShape
A CompositeShape performs the Inside/Outside checking on a list of shapes to determine if a point is inside the CompositeShape. A point will be inside the CompositeShape if it is inside all shapes in this list.

A CompositeShape is defined as,

```python
compositeShape = pyck.CompositeShape(tag,[shapes1, shape2,...]);
```

Note that the tag assigned to a CompositeShape overrides the tage assigned to shapes in the list.

### Inverted shapes
All shapes have an optional final argument which will invert the shape. This inversion dictates that particles *outside* the shape are mapped, rather than the default case where particles *inside* the shape are mapped. The optional argument defaults to `False`, set it to `True` to invert the shape. For example,

```python
sphere = pyck.Sphere(tag,[p1x,p2x,p3x],radius, True);
```

This will map all particles in the domain that are outside the sphere.

### Adding and processing
Once shapes have been created they are added to the pack as,

```python
pack.AddShape(cube);
pack.AddShape(sphere);
```

At this point the shapes have only been registered with the pyck, and no packing has occured. Packing is then carried out with,

```python
pack.Process();
```

Shapes are processed in the order they are added to the pack. Pyck will iterate over all particles within a shape, and assign them the `tag` corresponding to the shape being processed.

When processing multiple shapes it is possible for a particle to exist within two shapes. In this case, the particle is tagged according to the last shape added to the pack in which the particle lies. Therefore in the example given above, if a particle lies within both the sphere and the cube, it will be given the tag of the sphere since the sphere was added after the cube.

### Void space

Particles may be removed from the pack by adding a shape with a tag of 0 to the pack. Take care that the specific order of tagging is still strictly maintained, so if a particle is tagged as 0, but the next shape in the queue tags it with a non-zero value, the final state of the particle will be the non-zero value.

## Creating a model

Once shapes are packed and `pack.Process()` has been called, we are ready to create a model from our pack.

```python
model = pyck.Model(pack);
```

It is possible to create a model that is a composite of multiple packs.

```python
model.AddPack(pack);
```

It is also possible to create a model from particles specified by python objects.

```python
model = pyck.Model([p1x,p1y,p1z,p2x,p2y,p2z,...pnx,pny,pnz], [tag1,tag2,...tagn],n,dim);
model = pyck.AddPack([p1x,p1y,p1z,p2x,p2y,p2z,...pnx,pny,pnz], [tag1,tag2,...tagn],n,dim);
```

Where the first article is an array of particle positions, the second is an array of tags, `n` is the number of particles in this pack, and `dim` is the dimensionality of the pack. Note, even if your pack is 1D or 2D, particles still have to be specified with a Y and Z coordinate (even if it is zero).

### Model parameters

Model parameters are specified as key-value pairs, or as a python dictionary.

```python
model.SetParameter('key','value');
model.SetParameters({'key1':'value1','key2':'value2'});
```

Parameters are often reused between models. It may be convenient to set up a python function for yourself that sets sensible defaults for all model parameters first using the syntax shown. Once defaults have been set, they can be over-written by calling `model.SetParameter('key','value')` using the key you wish to over-write.

### Fields
In pyck, a field is an n-dimensional property attached to every particle, and may be either an Int or Double field. Where in this case Integer and Double refer to the c++ datatype used to represent the field.

Fields are created by,

```python
someIntField = model.CreateIntField(name,dim);
someDoubleField = model.CreateDoubleField(name,dim);
```

In which name is a string specifying the name of the field. `dim` is the dimensionality of the property, typically 1 for scalar properties, 2/3 for vector properties, and 9 for tensor properties. All fields are initialized with zero.

Values for each field are applied to particles by,

```python
model.SetIntField(someIntField,tag,value);
model.SetDoubleField(someDoubleField,tag,value);
```

Where the first argument is the handle to the field created with the CreateField functions, `tag` corresponds to the particle tags applied during shape mapping, and `value` is the value of the property to be applied. For non-scalar values, an array may be specified.

#### Field callbacks
A common requirement is for the value of a field to vary with position. To do this with pyck we use a python callback such as,

```python
def fieldCallback(x, y, z):
    return [x/10, y*50, 0]
```

The callback is then applied with `model.SetIntField(someIntField,tag,fieldCallback);` or`model.SetDoubleField(someDoubleField,tag,fieldCallback);`. When using field callbacks, the callback must always take 3 arguments which indicate the x y and z positions, for a 2D pack z will be zero but is still required. The callback should return either single value or a vector of values, when the number of values returned is equal to the dimensionality of the field being set.
 
## Writing the output file

Once all parameters and field have been specified, the model is now ready to be written to a file. Currently only one format is supported, which is the format used within MIT Geonumerics, for other formats a new class deriving from the abstract writer class must be implemented. See sparkWriter.h/cpp for reference.

First a writer must be created, this is then passed to the models serialize function along with the desired filename.

```python
writer = pyck.SparkWriter();
model.Serialize(filename,writer);
```
##
Further examples demonstrating the use of pyck may be found in the examples/ directory.

## Functionality Reference
Pyck functionality is all written in C++ and exposed in python via Swig bindings. All non-abstract classes in the C++ code are exposed in the python library. Inspect the doxygen documentation or source header files to determine functionality and correct arguments. Example scripts are given in the examples/ directory.

# Pyck Utils
pyck_utils.py contains helper functions primarily used to set sensible default paramters for SPH code used at MIT Geonumerics.

# Pyck Development
## Pack
Classes derived from pack should populate the positions and states arrays, set the numParticles variable, and set the dim variable (indicated dimensionality of the problem)

Classes derived from pack are also required to implement the MapShape function. This function must iterate over all particles and determine whether they are inside or outside of the shape. See the ellipsoidal or cylindrical packers for a general implementation based on position and state arrays.

## Shapes
All shapes are derived from the Shape class. Shape constructors should set a bounding box in the model (Cartesian) coordinate system. Shapes must also implement the IsInside method which takes a single length 3 array of doubles indicating a particles xyz coordinates.

## Writers
Writers are derived from the Writer class and must implement the Write(fname, positions, intFields, doubleFields, dim, numParticles) method. The purpose of this method is to take the packed model from Pyck and write it to a file. If a new output format is required, create a new writer.
