import sys
sys.path.insert(0, '/f/bruce/pyck/bin'); # Set this to the path where pyck is compiled
import pyck

# Create a packer, see packers directory for options
cubic = pyck.CubicPacker([10.0,10.0,10.0],0.1);
pack = pyck.Pack(cubic); # do not create the cubic packer in this function call as it will be destroyed, blame SWIG developers

# Create some shapes, see shapes directory for options and reference
# First argument is always a tag for these particles
# Mapping operations are applied sequentially
cube = pyck.Cuboid(1,[2,2,2],[6,6,6]);
sphere = pyck.Sphere(2,[2,2,2],5);

# Map the shapes and generate the pack
pack.AddShape(cube); # As with creating the cubic packer, do not create the shapes within the function call here
pack.AddShape(sphere);
pack.Process();

# Create a new model from the pack
model = pyck.Model(pack);

# Create a new field of n-dimensional integers
# Arguments are CreateIntField(label,dimensions)
# label - label for this field in the vtp file
# dimensions - dimensionality of this field, doesnt have to correspond to model dimensions
# Create field of doubles in the same way with CreateDoubleField
stateField = model.CreateIntField("State",1);

# Arguments are SetIntField(field,tag,value(s))
# field - returned from CreateIntField
# tag - tag applied to particles during shape Mapping
# value(s) - singular value or array of values [v1, v2,...vn] to set of particles with a matching tag
model.SetIntField(stateField,1,10);
model.SetIntField(stateField,2,20);

# Add simulation parameters to the VTP filename
# Arguments are AddParameter(Label,Value)
model.AddParameter("TestParam","test");

# Create a file writer, in this case VTP according to spark format
writer = pyck.SparkWriter();

# Write the VTP file
model.Serialize("pyck_test.vtp",writer);