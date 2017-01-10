import sys
sys.path.insert(0, '/mnt/c/ubuntu/packing/git_mod_notch/pyck/bin'); # Set this to the path where pyck is compiled
import pyck
import pyck_utils # Utility functions for creating simulation parameters



from operator import add
def sum(XX, YY):
	return map (add, XX,YY) 
import numpy as np
import math
L = [1,1,0]
r = 0.002;#0.00004;#
dim = 2;
smoothingKernelFunc = 1;

cubic = pyck.Hcp2dPacker(L,r);
pack = pyck.StructuredPack(cubic); # do not create the cubic packer in this function call as it will be destroyed, blame SWIG developers


solid = pyck.Cuboid(1,[0, 0, 0],[1, 1, 0]);
convexh = pyck.ConvexHull2D(2, [[0.1,0.2,0],[0.8,0.2,0],[0.3,0.8,0]]);
#convexh = pyck.Cuboid(2,[0.1, 0.2, 0],[0.8, 0.8, 0]);


pack.AddShape(solid);
pack.AddShape(convexh);

# Map the shapes and generate the pack


pack.Process();

# Create a new model from the pack
model = pyck.Model(pack);

# Create a new field of n-dimensional integers
# Arguments are CreateIntField(label,dimensions)
# label - label for this field in the vtp file
# dimensions - dimensionality of this field, doesnt have to correspond to model dimensions
# Create field of doubles in the same way with CreateDoubleField
stateField = model.CreateIntField("State",1);
# for i in range(1, 17):
# 	model.SetIntField(stateField,i,5);

model.SetIntField(stateField,1,0);
model.SetIntField(stateField,2,1);


writer = pyck.SparkWriter();
numParticles=pack.GetNumParticles();
# Write the VTP file
#model.Serialize("HFInsituCubic.vtp",writer);
model.Serialize("ConvexHull_Test_"+str(numParticles)+".vtp",writer);

