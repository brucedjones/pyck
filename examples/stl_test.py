import sys
sys.path.insert(0, '/f/bruce/pyck/bin'); # Set this to the path where pyck is compiled
import pyck
import pyck_utils # Utility functions for creating simulation parameters
import math


domain = [100.0,100.0,500.0];
h = domain[0]/100;
smoothingKernelFunc = 2;
speedsound = 1;
density = 1;
shearmodulus = 1;
bulkmodulus = 1;
material = pyck_utils.chromite;
# Create a packer, see packers directory for options
Hcp = pyck.HcpPacker(domain,h);
pack = pyck.StructuredPack(Hcp)

tibia_min = [154.2328,204.0634,-853.9525]; # Read from the tibia STL file
tibia_max = [226.9384,268.8318,-468.3400];
tibia_len = [tibia_max[0]-tibia_min[0],tibia_max[1]-tibia_min[1],tibia_max[2]-tibia_min[2]];
tibia_center = [tibia_min[0] + tibia_len[0]/2,tibia_min[1] + tibia_len[1]/2,tibia_min[2] + tibia_len[2]/2];
tibia_scale = 1;
tibia_len[0] = tibia_len[0]*tibia_scale;
tibia_len[1] = tibia_len[1]*tibia_scale;
tibia_len[2] = tibia_len[2]*tibia_scale;

tibia_dcenter = [domain[0]/2,domain[1]/2, domain[2]/2];
tibia_translation = [tibia_dcenter[0]-tibia_center[0],tibia_dcenter[1]-tibia_center[1],tibia_dcenter[2]-tibia_center[2]];


stlShape = pyck.StlShape(1,'tibia_low.stl',tibia_translation);

#cube = pyck.Cuboid(2,[0.2,0.2,0.2],[0.6,0.6,0.6]);

# Map the shapes and generate the pack
pack.AddShape(stlShape);
#pack.AddShape(cube);
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

# Set default simulation parameters for the VTP file
# SetDefaultParameters computes geometric simulation parameters from pack parameters

pyck_utils.SetBrazilianTestParameters(model,domain,h,material);

# Overwrite some parameters
# Arguments are SetParameter(Label,Value)
model.SetParameter("MaxSteps","100");
model.SetParameter("Mass","0.5");

# Or use a python dictionary to overwrite parameters
parameters = pyck.Parameters({'ViscAlpha':'0.1','ViscBeta':'0.2'});
model.SetParameters(parameters);

# Create a file writer, in this case VTP according to spark format
writer = pyck.SparkWriter();

# Write the VTP file
model.Serialize("tibia.vtp",writer);
