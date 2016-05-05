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

# Getting started
## Importing pyck

In order to use pyck you must import the compiled library. If your python script is in the same directory as your compiled pyck module, then you can simply use,

```python
import pyck
```

To run a script in a different directory add the correct path manually within the script before importing pyck.

```python
import sys
sys.path.insert(0, '/path/to/src/bin'); # Set this to the path where pyck is compiled
import pyck       # Pyck library
```

## Creating a domain
To create a domain to packed with a structured packing configuration a packer must first be defined reflecting the desired packing configuration. Options are as follows,

```python
cubic               = pyck.CubicPacker([Lx,Ly,Lz],radius);
faceCenteredCubic   = pyck.FccPacker([Lx,Ly,Lz],radius);
bodyCenteredCubic   = pyck.BccPacker([Lx,Ly,Lz],radius);
hexagonalClosePack  = pyck.HcpPacker([Lx,Ly,Lz],radius);
```

In which `Lx`, `Ly`, and `Lz`, are the domain lengths in the x, y, and z directions respectively. `radius` is the radius of particles to be packed (Half the minimum separation distance). To pack a 2D domain, simply set `Lz` to 0. Note: the only packing configurations that make sense in 2D are Cubic and Hexagonal Close Packing.

With a packer defined, the domain is initialized with the following,

```python
pack = pyck.StructuredPack(cubic);
```

Take care to create the packer separately to the StructuredPack object. If the Packer is dynamically created within the constructor argument of structed pack (eg. `StructuredPack(pyck.CubicPacker([Lx,Ly,Lz],radius)`) pyck will crash. This is because the python garbage collects the CubicPacker as soon as the StructuredPack constructor returns.

## Packing shapes

All shapes within pyck are specified in two ways, their geometric properties, and an integer `tag` which is applied to all particles packed within that shape. The shapes `tag` is always the first argument in the constructor of a shape. Examples are given here for cuboids and spheres, for reference on other shapes see the doxygen documentation or the shape classes in the shapes/ directory.


### Cuboid

The geometry of a cuboid is defined by a lower-left point, `p1`, and an upper-right point `p2`.

```python
cube = pyck.Cuboid(tag,[p1x,p1y,p1z],[p2x,p2y,p2z]);
```

### Sphere

The geometry of a sphere is defined by a centroid, `p1`, and a `radius`.

```Sphere
sphere = pyck.Spheretag,[p1x,p2x,p3x],radius);
```

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

Parameters are often reused between models. It may be convenient to set up a python function for yourself that sets sensible defaults for all model parameters first using the syntax shown. Once defaults have been set, they can be over-written by simply called `model.SetParameter('key','value')` using the key you wish to over-write.

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