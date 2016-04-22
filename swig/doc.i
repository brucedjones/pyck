
// File: index.xml

// File: classBccPacker.xml
%feature("docstring") BccPacker "";

%feature("docstring")  BccPacker::BccPacker "BccPacker::BccPacker(double *doubleLenIn, double h)

BccPacker constructor.

Parameters:
-----------

doubleLenIn:  Size of the domain in Cartesian coordinate system

h:  Particle radius ";

%feature("docstring")  BccPacker::~BccPacker "BccPacker::~BccPacker()
";

%feature("docstring")  BccPacker::IDX2Pos "void
BccPacker::IDX2Pos(long i, long j, long k, double *posOut)

Converts an ijk index to Cartesian coordinates

Parameters:
-----------

i:  i index (along X)

j:  j index (along Y)

k:  k index (along Z)

posOut:  Cartesian coordinate output, array of length 3 ";

%feature("docstring")  BccPacker::Pos2IDX "void
BccPacker::Pos2IDX(double *posIn, long *idxOut, bool doFloor)

Converts a Cartesian coordinate to an IJK position

Parameters:
-----------

posIn:  Cartesian coordinate input, array of length 3

idxOut:  ijk coordinate output, array of length 3

doFloor:  Returns the lower-left point in relation to the Cartesian
point if true. Returns the upper-right point if false ";


// File: classBoundingBox.xml
%feature("docstring") BoundingBox "

Stores Lower-left and Upper-right bounding box coordinates in ijk
indexes. This bounding box will be iterated over when mapping a shape.

C++ includes: boundingBox.h ";

%feature("docstring")  BoundingBox::BoundingBox "BoundingBox::BoundingBox(double *p1, double *p2)

BoundingBox Constructor

Parameters:
-----------

p1:  Lower-left corner in cartesian coordinates

p2:  Upper-right corner in cartesian coordinates

domain:  Domain in which this BoundingBox exists ";

%feature("docstring")  BoundingBox::~BoundingBox "BoundingBox::~BoundingBox() ";


// File: classCubicPacker.xml
%feature("docstring") CubicPacker "";

%feature("docstring")  CubicPacker::CubicPacker "CubicPacker::CubicPacker(double *doubleLenIn, double h)

CubicPacker constructor.

Parameters:
-----------

doubleLenIn:  Size of the domain in Cartesian coordinate system

h:  Particle radius ";

%feature("docstring")  CubicPacker::~CubicPacker "CubicPacker::~CubicPacker() ";

%feature("docstring")  CubicPacker::IDX2Pos "void
CubicPacker::IDX2Pos(long i, long j, long k, double *posOut)

Converts an ijk index to Cartesian coordinates

Parameters:
-----------

i:  i index (along X)

j:  j index (along Y)

k:  k index (along Z)

posOut:  Cartesian coordinate output, array of length 3 ";

%feature("docstring")  CubicPacker::Pos2IDX "void
CubicPacker::Pos2IDX(double *posIn, long *idxOut, bool doFloor)

Converts a Cartesian coordinate to an IJK position

Parameters:
-----------

posIn:  Cartesian coordinate input, array of length 3

idxOut:  ijk coordinate output, array of length 3

doFloor:  Returns the lower-left point in relation to the Cartesian
point if true. Returns the upper-right point if false ";


// File: classCuboid.xml
%feature("docstring") Cuboid "";

%feature("docstring")  Cuboid::Cuboid "Cuboid::Cuboid(int state,
double *p1, double *p2)

Cuboid constructor

Parameters:
-----------

state:  State to be applied to particles within this shape. state = 0
will remove particle from output

p1:  Lower-left corner of cuboid in cartesian coordinates

p2:  Upper-right corner of cuboid in cartesian coordinates

domain:  Domain in which this shape will be mapped ";

%feature("docstring")  Cuboid::~Cuboid "Cuboid::~Cuboid() ";

%feature("docstring")  Cuboid::IsInside "bool Cuboid::IsInside(double
*pt)

Check if given coordinate is inside this shape

Parameters:
-----------

pt:  Coordinates to check

True if coordinate is inside shape, false otherwise ";


// File: classCylinder.xml
%feature("docstring") Cylinder "";

%feature("docstring")  Cylinder::Cylinder "Cylinder::Cylinder(int
state, double *c, double r, double *l)

Cylinder constructor

Parameters:
-----------

state:  State to be applied to particles within this shape. state = 0
will remove particle from output

c:  Center of the cylinder in cartesian coordinates

r:  Radius of the cylinder

l:  Length of the cylinder in cartesian coordinates, (0,0,l) or
(0,l,0) or (l,0,0) indicates the direction

domain:  Domain in which this shape will be mapped ";

%feature("docstring")  Cylinder::~Cylinder "Cylinder::~Cylinder() ";

%feature("docstring")  Cylinder::IsInside "bool
Cylinder::IsInside(double *pt)

Check if given coordinate is inside this shape

Parameters:
-----------

pt:  Coordinates to check

True if coordinate is inside shape, false otherwise ";


// File: classCylindricalPacker.xml
%feature("docstring") CylindricalPacker "";

%feature("docstring")  CylindricalPacker::CylindricalPacker "CylindricalPacker::CylindricalPacker(double *c, double r, double
ratio, double h, int state, double num_div=3.0) ";

%feature("docstring")  CylindricalPacker::CylindricalPacker "CylindricalPacker::CylindricalPacker(double *c, double r, double
ratio, double *l, double h, int state, double num_div=3.0) ";

%feature("docstring")  CylindricalPacker::CylindricalPacker "CylindricalPacker::CylindricalPacker(double *c, double r, double
ratioY, double ratioZ, double h, int state, double num_div=3.0) ";

%feature("docstring")  CylindricalPacker::~CylindricalPacker "CylindricalPacker::~CylindricalPacker() ";

%feature("docstring")  CylindricalPacker::getPositions "double *
CylindricalPacker::getPositions() ";

%feature("docstring")  CylindricalPacker::getStates "int *
CylindricalPacker::getStates() ";

%feature("docstring")  CylindricalPacker::getNumParticles "long
CylindricalPacker::getNumParticles() ";

%feature("docstring")  CylindricalPacker::getDim "int
CylindricalPacker::getDim() ";


// File: classDoubleField.xml
%feature("docstring") DoubleField "";

%feature("docstring")  DoubleField::DoubleField "DoubleField::DoubleField(std::string name, long n, int dim) ";

%feature("docstring")  DoubleField::~DoubleField "DoubleField::~DoubleField() ";


// File: classdoxy2swig_1_1Doxy2SWIG.xml
%feature("docstring") doxy2swig::Doxy2SWIG "

Converts Doxygen generated XML files into a file containing docstrings
that can be used by SWIG-1.3.x that have support for
feature(\"docstring\").  Once the data is parsed it is stored in
self.pieces. ";

%feature("docstring")  doxy2swig::Doxy2SWIG::__init__ "def
doxy2swig::Doxy2SWIG::__init__ Initialize the instance given a source
object (file or filename). ";

%feature("docstring")  doxy2swig::Doxy2SWIG::generate "def
doxy2swig::Doxy2SWIG::generate Parses the file set in the
initialization.  The resulting data is stored in `self.pieces`. ";

%feature("docstring")  doxy2swig::Doxy2SWIG::parse "def
doxy2swig::Doxy2SWIG::parse Parse a given node.  This function in turn
calls the `parse_<nodeType>` functions which handle the respective
nodes. ";

%feature("docstring")  doxy2swig::Doxy2SWIG::parse_Document "def
doxy2swig::Doxy2SWIG::parse_Document";

%feature("docstring")  doxy2swig::Doxy2SWIG::parse_Text "def
doxy2swig::Doxy2SWIG::parse_Text";

%feature("docstring")  doxy2swig::Doxy2SWIG::parse_Element "def
doxy2swig::Doxy2SWIG::parse_Element Parse an `ELEMENT_NODE`.  This
calls specific `do_<tagName>` handers for different elements.  If no
handler is available the `generic_parse` method is called.  All
tagNames specified in `self.ignores` are simply ignored. ";

%feature("docstring")  doxy2swig::Doxy2SWIG::add_text "def
doxy2swig::Doxy2SWIG::add_text Adds text corresponding to `value` into
`self.pieces`. ";

%feature("docstring")  doxy2swig::Doxy2SWIG::get_specific_nodes "def
doxy2swig::Doxy2SWIG::get_specific_nodes Given a node and a sequence
of strings in `names`, return a dictionary containing the names as
keys and child `ELEMENT_NODEs`, that have a `tagName` equal to the
name. ";

%feature("docstring")  doxy2swig::Doxy2SWIG::generic_parse "def
doxy2swig::Doxy2SWIG::generic_parse A Generic parser for arbitrary
tags in a node.  Parameters:   - node: A node in the DOM.  - pad:
`int` (default: 0)     If 0 the node data is not padded with newlines.
If 1 it    appends a newline after parsing the childNodes.  If 2 it
pads before and after the nodes are processed.  Defaults to    0. ";

%feature("docstring")  doxy2swig::Doxy2SWIG::space_parse "def
doxy2swig::Doxy2SWIG::space_parse";

%feature("docstring")  doxy2swig::Doxy2SWIG::do_compoundname "def
doxy2swig::Doxy2SWIG::do_compoundname";

%feature("docstring")  doxy2swig::Doxy2SWIG::do_compounddef "def
doxy2swig::Doxy2SWIG::do_compounddef";

%feature("docstring")  doxy2swig::Doxy2SWIG::do_includes "def
doxy2swig::Doxy2SWIG::do_includes";

%feature("docstring")  doxy2swig::Doxy2SWIG::do_parameterlist "def
doxy2swig::Doxy2SWIG::do_parameterlist";

%feature("docstring")  doxy2swig::Doxy2SWIG::do_para "def
doxy2swig::Doxy2SWIG::do_para";

%feature("docstring")  doxy2swig::Doxy2SWIG::do_parametername "def
doxy2swig::Doxy2SWIG::do_parametername";

%feature("docstring")  doxy2swig::Doxy2SWIG::do_parameterdefinition "def doxy2swig::Doxy2SWIG::do_parameterdefinition";

%feature("docstring")  doxy2swig::Doxy2SWIG::do_detaileddescription "def doxy2swig::Doxy2SWIG::do_detaileddescription";

%feature("docstring")  doxy2swig::Doxy2SWIG::do_briefdescription "def
doxy2swig::Doxy2SWIG::do_briefdescription";

%feature("docstring")  doxy2swig::Doxy2SWIG::do_memberdef "def
doxy2swig::Doxy2SWIG::do_memberdef";

%feature("docstring")  doxy2swig::Doxy2SWIG::do_definition "def
doxy2swig::Doxy2SWIG::do_definition";

%feature("docstring")  doxy2swig::Doxy2SWIG::do_sectiondef "def
doxy2swig::Doxy2SWIG::do_sectiondef";

%feature("docstring")  doxy2swig::Doxy2SWIG::do_simplesect "def
doxy2swig::Doxy2SWIG::do_simplesect";

%feature("docstring")  doxy2swig::Doxy2SWIG::do_argsstring "def
doxy2swig::Doxy2SWIG::do_argsstring";

%feature("docstring")  doxy2swig::Doxy2SWIG::do_member "def
doxy2swig::Doxy2SWIG::do_member";

%feature("docstring")  doxy2swig::Doxy2SWIG::do_doxygenindex "def
doxy2swig::Doxy2SWIG::do_doxygenindex";

%feature("docstring")  doxy2swig::Doxy2SWIG::write "def
doxy2swig::Doxy2SWIG::write";

%feature("docstring")  doxy2swig::Doxy2SWIG::clean_pieces "def
doxy2swig::Doxy2SWIG::clean_pieces Cleans the list of strings given as
`pieces`.  It replaces multiple newlines by a maximum of 2 and returns
a new list. It also wraps the paragraphs nicely. ";


// File: classEllipsoidalPacker.xml
%feature("docstring") EllipsoidalPacker "";

%feature("docstring")  EllipsoidalPacker::EllipsoidalPacker "EllipsoidalPacker::EllipsoidalPacker(double *c, double r, double
ratio, double h, int state, double tolerance_angle=0.001, double
tolerance_h=0.55, bool random_startingpoint=true, bool adjust_h=true)
";

%feature("docstring")  EllipsoidalPacker::EllipsoidalPacker "EllipsoidalPacker::EllipsoidalPacker(double *c, double r, double
ratio, double *l, double h, int state, double tolerance_angle=0.001,
double tolerance_h=0.55, bool random_startingpoint=true, bool
adjust_h=true) ";

%feature("docstring")  EllipsoidalPacker::EllipsoidalPacker "EllipsoidalPacker::EllipsoidalPacker(double *c, double r, double
ratioY, double ratioZ, double h, int state, double
tolerance_angle=0.001, double tolerance_h=0.55, bool
random_startingpoint=true, bool adjust_h=true) ";

%feature("docstring")  EllipsoidalPacker::~EllipsoidalPacker "EllipsoidalPacker::~EllipsoidalPacker() ";

%feature("docstring")  EllipsoidalPacker::getPositions "double *
EllipsoidalPacker::getPositions() ";

%feature("docstring")  EllipsoidalPacker::getStates "int *
EllipsoidalPacker::getStates() ";

%feature("docstring")  EllipsoidalPacker::getNumParticles "long
EllipsoidalPacker::getNumParticles() ";

%feature("docstring")  EllipsoidalPacker::getDim "int
EllipsoidalPacker::getDim() ";

%feature("docstring")  EllipsoidalPacker::EllipsoidalPacker "EllipsoidalPacker::EllipsoidalPacker(double h, int state, double *c,
double r, double ratioY, double ratioZ) ";

%feature("docstring")  EllipsoidalPacker::EllipsoidalPacker "EllipsoidalPacker::EllipsoidalPacker(double h, int state, double *c,
double r, double ratio) ";

%feature("docstring")  EllipsoidalPacker::~EllipsoidalPacker "EllipsoidalPacker::~EllipsoidalPacker() ";

%feature("docstring")  EllipsoidalPacker::getPositions "double*
EllipsoidalPacker::getPositions() ";

%feature("docstring")  EllipsoidalPacker::getStates "int*
EllipsoidalPacker::getStates() ";

%feature("docstring")  EllipsoidalPacker::getNumParticles "long
EllipsoidalPacker::getNumParticles() ";

%feature("docstring")  EllipsoidalPacker::getDim "int
EllipsoidalPacker::getDim() ";


// File: classFccPacker.xml
%feature("docstring") FccPacker "";

%feature("docstring")  FccPacker::FccPacker "FccPacker::FccPacker(double *doubleLenIn, double h)

FccPacker constructor.

Parameters:
-----------

doubleLenIn:  Size of the domain in Cartesian coordinate system

h:  Particle radius ";

%feature("docstring")  FccPacker::~FccPacker "FccPacker::~FccPacker()
";

%feature("docstring")  FccPacker::IDX2Pos "void
FccPacker::IDX2Pos(long i, long j, long k, double *posOut)

Converts an ijk index to Cartesian coordinates

Parameters:
-----------

i:  i index (along X)

j:  j index (along Y)

k:  k index (along Z)

posOut:  Cartesian coordinate output, array of length 3 ";

%feature("docstring")  FccPacker::Pos2IDX "void
FccPacker::Pos2IDX(double *posIn, long *idxOut, bool doFloor)

Converts a Cartesian coordinate to an IJK position

Parameters:
-----------

posIn:  Cartesian coordinate input, array of length 3

idxOut:  ijk coordinate output, array of length 3

doFloor:  Returns the lower-left point in relation to the Cartesian
point if true. Returns the upper-right point if false ";


// File: classHcpPacker.xml
%feature("docstring") HcpPacker "";

%feature("docstring")  HcpPacker::HcpPacker "HcpPacker::HcpPacker(double *doubleLenIn, double h)

HcpPacker constructor.

Parameters:
-----------

doubleLenIn:  Size of the domain in Cartesian coordinate system

h:  Particle radius ";

%feature("docstring")  HcpPacker::~HcpPacker "HcpPacker::~HcpPacker()
";

%feature("docstring")  HcpPacker::IDX2Pos "void
HcpPacker::IDX2Pos(long i, long j, long k, double *posOut)

Converts an ijk index to Cartesian coordinates

Parameters:
-----------

i:  i index (along X)

j:  j index (along Y)

k:  k index (along Z)

posOut:  Cartesian coordinate output, array of length 3 ";

%feature("docstring")  HcpPacker::Pos2IDX "void
HcpPacker::Pos2IDX(double *posIn, long *idxOut, bool doFloor)

Converts a Cartesian coordinate to an IJK position

Parameters:
-----------

posIn:  Cartesian coordinate input, array of length 3

idxOut:  ijk coordinate output, array of length 3

doFloor:  Returns the lower-left point in relation to the Cartesian
point if true. Returns the upper-right point if false ";


// File: classIntField.xml
%feature("docstring") IntField "";

%feature("docstring")  IntField::IntField "IntField::IntField(std::string name, long n, int dim) ";

%feature("docstring")  IntField::~IntField "IntField::~IntField() ";


// File: classModel.xml
%feature("docstring") Model "";

%feature("docstring")  Model::Model "Model::Model()

Model Constructor, creates an empty model with no particles ";

%feature("docstring")  Model::Model "Model::Model(Pack *pack)

Model Constructor

Parameters:
-----------

pack:  Packed pack object ";

%feature("docstring")  Model::Model "Model::Model(double *positions,
int *states, long numParticles, int dim)

Model Constructor

Parameters:
-----------

positions:  N x 3 array of positions, third dimension should be 0.0
for 2d

states:  N x 1 array of pack states

numParticles:  Specifies N particles ";

%feature("docstring")  Model::~Model "Model::~Model() ";

%feature("docstring")  Model::AddPack "void Model::AddPack(Pack
*pack)

Append particles from another pack to this model

Parameters:
-----------

pack:  A fully processed pack object ";

%feature("docstring")  Model::AddPack "void Model::AddPack(double
*positions, int *states, long numParticles, int dim)

Append particles to this model

Parameters:
-----------

positions:  Nx3 array of positions (x1,y1,z1,x2,y2,z2,...,xn,yn,zn)

states:  Length N integer array of states

numParticles:  Number of particles to add

dim:  Dimensionality of the pack ";

%feature("docstring")  Model::CreateIntField "int
Model::CreateIntField(std::string name, int dim)

Create a dim dimensional field of integers

Parameters:
-----------

name:  Name of the field

dim:  dimensionality of the field

A Handle to the field so that values may be set ";

%feature("docstring")  Model::CreateDoubleField "int
Model::CreateDoubleField(std::string name, int dim)

Create a dim dimensional field of floats

Parameters:
-----------

name:  Name of the field

dim:  dimensionality of the field

A Handle to the field so that values may be set ";

%feature("docstring")  Model::SetIntField "void
Model::SetIntField(int handle, int state, int *val)

Set the values of an integer field

Parameters:
-----------

handle:  Handle of the field to be set

state:   particle state for which these values will be applioed

val:  Array of length equal to the dimensionality of the field ";

%feature("docstring")  Model::SetDoubleField "void
Model::SetDoubleField(int handle, int state, double *val)

Set the values of an float field

Parameters:
-----------

handle:  Handle of the field to be set

state:   particle state for which these values will be applioed

val:  Array of length equal to the dimensionality of the field ";

%feature("docstring")  Model::SetParameter "void
Model::SetParameter(std::string key, std::string value)

Add a parameter to the domain

Parameters:
-----------

key:  The label for this parameter

value:  The value of this parameter ";

%feature("docstring")  Model::SetParameters "void
Model::SetParameters(std::map< std::string, std::string > &parameters)

Add a parameter to the domain

Parameters:
-----------

parameters:  Map of parameters to add ";

%feature("docstring")  Model::Serialize "void
Model::Serialize(std::string fname, Writer *writer)

Write domain to CSV file

Parameters:
-----------

fname:  Output filename ";


// File: classPack.xml
%feature("docstring") Pack "

The pack to be packed with particles.

C++ includes: pack.h ";

%feature("docstring")  Pack::Pack "Pack::Pack(Packer *packer)

Pack Constructor

Parameters:
-----------

packer:  Determines the relationship between IJK and Cartesian
coordinates. ";

%feature("docstring")  Pack::~Pack "Pack::~Pack() ";

%feature("docstring")  Pack::AddShape "void Pack::AddShape(Shape
*shape)

Add a shape to the Pack

Parameters:
-----------

shape:   Shape to be mapped ";

%feature("docstring")  Pack::Process "void Pack::Process()

Pack all added shapes and generate positions and states ";


// File: classPacker.xml
%feature("docstring") Packer "";

%feature("docstring")  Packer::Packer "Packer::Packer()

Packer constructor. A new constructor should be implemented by the
deriving class which sets the length of the domain in ijk and the
spacing between particles. ";

%feature("docstring")  Packer::~Packer "Packer::~Packer() ";

%feature("docstring")  Packer::IDX2Pos "virtual void
Packer::IDX2Pos(long i, long j, long k, double *posOut)=0

Converts an ijk index to Cartesian coordinates

Parameters:
-----------

i:  i index (along X)

j:  j index (along Y)

k:  k index (along Z)

posOut:  Cartesian coordinate output, array of length 3 ";

%feature("docstring")  Packer::Pos2IDX "virtual void
Packer::Pos2IDX(double *posIn, long *idxOut, bool doFloor)=0

Converts a Cartesian coordinate to an IJK position

Parameters:
-----------

posIn:  Cartesian coordinate input, array of length 3

idxOut:  ijk coordinate output, array of length 3

doFloor:  Returns the lower-left point in relation to the Cartesian
point if true. Returns the upper-right point if false ";


// File: structpart.xml
%feature("docstring") part "";


// File: structparticle.xml
%feature("docstring") particle "";


// File: classShape.xml
%feature("docstring") Shape "

Abstract class defining a shape to be mapped to the domain

C++ includes: shape.h ";

%feature("docstring")  Shape::Shape "Shape::Shape(int state)

Shape base constructor

Parameters:
-----------

state:  The state which will be assigned to particles contained in
this shape. state = 0 will remove any previously assigned particles ";

%feature("docstring")  Shape::~Shape "Shape::~Shape() ";

%feature("docstring")  Shape::IsInside "virtual bool
Shape::IsInside(double *pt)=0

Check if given coordinate is inside this shape

Parameters:
-----------

pt:  Coordinates to check

True if coordinate is inside shape, false otherwise ";


// File: classSparkWriter.xml
%feature("docstring") SparkWriter "";

%feature("docstring")  SparkWriter::SparkWriter "SparkWriter::SparkWriter() ";

%feature("docstring")  SparkWriter::~SparkWriter "SparkWriter::~SparkWriter() ";

%feature("docstring")  SparkWriter::Write "void
SparkWriter::Write(std::string fname, std::map< std::string,
std::string > parameters, double *positions, std::vector< IntField * >
intFields, std::vector< DoubleField * > doubleFields, int dim, long
numParticles) ";


// File: classSphere.xml
%feature("docstring") Sphere "";

%feature("docstring")  Sphere::Sphere "Sphere::Sphere(int state,
double *c, double r)

Sphere constructor

Parameters:
-----------

state:  State to be applied to particles within this shape. state = 0
will remove particle from output

c:  Center of the sphere in cartesian coordinates

r:  Radius of the sphere

domain:  Domain in which this shape will be mapped ";

%feature("docstring")  Sphere::~Sphere "Sphere::~Sphere() ";

%feature("docstring")  Sphere::IsInside "bool Sphere::IsInside(double
*pt)

Check if given coordinate is inside this shape

Parameters:
-----------

pt:  Coordinates to check

True if coordinate is inside shape, false otherwise ";


// File: classWriter.xml
%feature("docstring") Writer "";

%feature("docstring")  Writer::Writer "Writer::Writer() ";

%feature("docstring")  Writer::~Writer "Writer::~Writer() ";

%feature("docstring")  Writer::Write "virtual void
Writer::Write(std::string fname, std::map< std::string, std::string >
parameters, double *positions, std::vector< IntField * > intFields,
std::vector< DoubleField * > doubleFields, int dim, long
numParticles)=0 ";


// File: namespacedoxy2swig.xml
%feature("docstring")  doxy2swig::my_open_read "def
doxy2swig::my_open_read";

%feature("docstring")  doxy2swig::my_open_write "def
doxy2swig::my_open_write";

%feature("docstring")  doxy2swig::main "def doxy2swig::main";


// File: boundingBox_8cpp.xml


// File: boundingBox_8h.xml


// File: cylindricalPacker_8cpp.xml
%feature("docstring")  make_particle "particle make_particle(double
x, double y, double z, int state) ";


// File: cylindricalPacker_8h.xml


// File: doxy2swig_8py.xml


// File: doubleField_8cpp.xml


// File: doubleField_8h.xml


// File: ellipsoidalPacker_8cpp.xml
%feature("docstring")  make_part "part make_part(double x, double y,
double z, int state) ";


// File: ellipsoidalPacker_8h.xml


// File: elliptic__integral__firstform_8cpp.xml
%feature("docstring")  Landen_Transform "static void
Landen_Transform(long double phi, long double parameter, double *K,
double *F) ";

%feature("docstring")  Elliptic_Integral_First_Kind "static void
Elliptic_Integral_First_Kind(long double phi, long double m, double
*K, double *F) ";

%feature("docstring")  Large_Modulus2 "static double
Large_Modulus2(double amplitude, long double k) ";

%feature("docstring")  Legendre_Elliptic_Integral_First_Kind "double
Legendre_Elliptic_Integral_First_Kind(double amplitude, char arg,
double x) ";


// File: elliptic__integral__secondform_8cpp.xml
%feature("docstring")  Landen_Transform "static void
Landen_Transform(long double phi, long double parameter, double *F,
double *Fk, double *E, double *Ek) ";

%feature("docstring")  Elliptic_Integral_Second_Kind "static void
Elliptic_Integral_Second_Kind(long double phi, long double m, double
*Em, double *Em_phi) ";

%feature("docstring")  Large_Modulus "static double
Large_Modulus(double amplitude, long double k) ";

%feature("docstring")  Legendre_Elliptic_Integral_Second_Kind "double
Legendre_Elliptic_Integral_Second_Kind(double amplitude, char arg,
double x) ";


// File: intField_8cpp.xml


// File: intField_8h.xml


// File: model_8cpp.xml


// File: model_8h.xml


// File: old__ellipsoidalPacker_8cpp.xml
%feature("docstring")  make_part "part make_part(double x, double y,
double z, int state) ";

%feature("docstring")  swap "void swap(double &x, double &y) ";

%feature("docstring")  sort "void sort(double &a, double &b, double
&c) ";

%feature("docstring")  calculateEllipse "std::vector<part>
calculateEllipse(double x, double y, double a, double b, double angle,
long stepsA, double h, int state) ";

%feature("docstring")  calculateEllipsoid "std::vector<part>
calculateEllipsoid(double x, double y, double z, double a, double b,
double c, double angle, long stepsA, long stepsB, double h, int state)
";


// File: old__ellipsoidalPacker_8h.xml


// File: pack_8cpp.xml


// File: pack_8h.xml


// File: packer_8cpp.xml


// File: packer_8h.xml


// File: bccPacker_8cpp.xml


// File: bccPacker_8h.xml


// File: cubicPacker_8cpp.xml


// File: cubicPacker_8h.xml


// File: fccPacker_8cpp.xml


// File: fccPacker_8h.xml


// File: hcpPacker_8cpp.xml


// File: hcpPacker_8h.xml


// File: pyck_8cpp.xml
%feature("docstring")  main "int main() ";


// File: pyck_8h.xml


// File: shape_8cpp.xml


// File: shape_8h.xml


// File: cuboid_8cpp.xml


// File: cuboid_8h.xml


// File: cylinder_8cpp.xml


// File: cylinder_8h.xml


// File: sphere_8cpp.xml


// File: sphere_8h.xml


// File: writer_8cpp.xml


// File: writer_8h.xml


// File: base64_8cpp.xml
%feature("docstring")  base64encode "int base64encode(const void
*data_buf, size_t dataLength, char *result, size_t resultSize) ";

%feature("docstring")  base64decode "int base64decode(char *in,
size_t inLen, unsigned char *out, size_t *outLen) ";


// File: base64_8h.xml
%feature("docstring")  base64encode "int base64encode(const void
*data_buf, size_t dataLength, char *result, size_t resultSize) ";

%feature("docstring")  base64decode "int base64decode(char *in,
size_t inLen, unsigned char *out, size_t *outLen) ";


// File: sparkWriter_8cpp.xml


// File: sparkWriter_8h.xml


// File: dir_4699ad3df0ca2385ac6f5b73c70216ce.xml


// File: dir_d02fab7b3197f2d150e34b78c922b345.xml


// File: dir_52ef77e189de5fda808669e8c78dfd40.xml


// File: dir_225cc56f8c787233b05a4a99f07b5250.xml

