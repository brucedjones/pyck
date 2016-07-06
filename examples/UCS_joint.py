import sys
sys.path.insert(0, '/f/ranjan/packing/pyck/bin'); # Set this to the path where pyck is compiled
import pyck
import pyck_utils # Utility functions for creating simulation parameters
from operator import add
def sum(XX, YY):
	return map (add, XX,YY) 

PI = 3.14159265359;
L = [0.1,0.2,0]
r = 0.001;
dim = 2;
smoothingKernelFunc = 1;
material = pyck_utils.chromite;
# Create a packer, see packers directory for options
cubic = pyck.Hcp2dPacker(L,r);
pack = pyck.StructuredPack(cubic); # do not create the cubic packer in this function call as it will be destroyed, blame SWIG developers

import numpy as np
import math
pos=[]
states=[]
JPNbr =[]
JdCosine=[]

jx1 = np.arange(5*r,0.054+5*r,r);
theta1 = 45*PI/180;


for i in range(len(jx1)):
	jy1=jx1[i];
	pos.append(float(jx1[i]))
	pos.append(float(jy1+30*r))
	pos.append(float(0))
	states.append(int(7));
	# JPNbr.append(int(0));
	# JdCosine.append(float(math.cos(theta1)));
	# JdCosine.append(float(math.sin(theta1)));
	# JdCosine.append(float(0));



# pos=np.add(jx,jy,jz)

#
# Create some shapes, see shapes directory for options and reference
# First argument is always a tag for these particles
# Mapping operations are applied sequentially

# bottomFluidChannel = pyck.Cuboid(1,[0,0.048,0],[0.043,0.050,0]);
# fluid = pyck.Cuboid(2,[0,0.050,0],[0.045,0.054,0]);
# topFluidChannel = pyck.Cuboid(3,[0,0.054,0],[0.043,0.056,0])
# leftTopSolidBd = pyck.Cuboid(4,[0.043,0.054,0],[0.045,0.104,0])
# leftBottomSolidBd = pyck.Cuboid(5,[0.043,0,0],[0.045,0.050,0])
# solid = pyck.Cuboid(6,[0.045,0.002,0],[0.195,0.102,0])
# waveMaker = pyck.Cuboid(7,[0,0.05,0],[0.002,0.054,0])
# solidTop = pyck.Cuboid(8,[0.045,0.1005,0],[0.1935,0.102,0])
# solidRightTop = pyck.Cuboid(9,[0.1935,0.1005,0],[0.195,0.102,0])
# solidRightBottom = pyck.Cuboid(10,[0.1935,0.002,0],[0.195,0.0035,0])
# solidRight = pyck.Cuboid(11,[0.1935,0.0035,0],[0.195,0.1005,0])
# solidBottom = pyck.Cuboid(12,[0.045,0.002,0],[0.1935,0.0035,0])

lowerplaten = pyck.Cuboid(2,[r/2,r/2,0], [0.054+10*r,5*r,0])
upperplaten = pyck.Cuboid(3,[r/2,0.135+5*r,0],[0.054+10*r,0.135+10*r,0])
solid = pyck.Cuboid(1,[5*r,5*r,0],[0.054+5*r,0.135+5*r,0])
# Map the shapes and generate the pack
pack.AddShape(solid);
pack.AddShape(lowerplaten);
pack.AddShape(upperplaten);

pack.Process();

# Create a new model from the pack
model = pyck.Model(pack);
# jmodel = pyck.Model(jpack);
model.AddPack(pos, states, len(jx1),dim);
# Create a new field of n-dimensional integers
# Arguments are CreateIntField(label,dimensions)
# label - label for this field in the vtp file
# dimensions - dimensionality of this field, doesnt have to correspond to model dimensions
# Create field of doubles in the same way with CreateDoubleField
stateField = model.CreateIntField("State",1);

model.SetIntField(stateField,1,5);
model.SetIntField(stateField,2,4);
model.SetIntField(stateField,3,4);
model.SetIntField(stateField,7,6);


# phaseField = model.CreateIntField("Phase",1);
# for i in range(1, 7):
#     model.SetIntField(phaseField,i,0);
# model.SetIntField(phaseField,2,1);   
# model.SetIntField(phaseField,7,1);

# boundaryIndexField = model.CreateIntField("BoundaryIndex",1);
# model.SetIntField(boundaryIndexField,1,5);
# model.SetIntField(boundaryIndexField,3,5);
# model.SetIntField(boundaryIndexField,4,5);
# model.SetIntField(boundaryIndexField,5,5);
# model.SetIntField(boundaryIndexField,8,8);
# model.SetIntField(boundaryIndexField,9,10);
# model.SetIntField(boundaryIndexField,10,10);
# model.SetIntField(boundaryIndexField,11,9);
# model.SetIntField(boundaryIndexField,12,7);

densityField = model.CreateDoubleField("Density",1);
# for i in range(1, 13):
#     model.SetDoubleField(densityField,i,1540);
# #model.SetIntField(densityField,6,1540);
# model.SetDoubleField(densityField,2,1000);   
model.SetDoubleField(densityField,1,2500);
model.SetDoubleField(densityField,2,2500);
model.SetDoubleField(densityField,3,2500);
model.SetDoubleField(densityField,7,2500);

velocityField = model.CreateDoubleField("Velocity",3);
# model.SetDoubleField(velocityField,7,[2.0,0,0]);

JontPointNumberField = model.CreateIntField("JPNbr",1);
for i in range(1, 4):
    model.SetIntField(JontPointNumberField,i,-1000);
model.SetIntField(JontPointNumberField,7,0);

JdcosField = model.CreateDoubleField("JdCosine",3);
for i in range(1, 4):
    model.SetDoubleField(JdcosField,i,[-1000,-1000,-1000]);
model.SetDoubleField(JdcosField,7,[math.cos(theta1),math.sin(theta1),0]);


pyck_utils.SetJointParameters(model,L,r,material,smoothingKernelFunc);
pyck_utils.SetGeometricParameters(model,L,r,smoothingKernelFunc);
model.SetParameter("Mass","%e" % (2.15239981700345e-003) );
# model.SetParameter("Mass","3.850204950429613e-04 2.500133084694554e-04")
writer = pyck.SparkWriter();
numParticles=pack.GetNumParticles();
# Write the VTP file
#model.Serialize("HFInsituCubic.vtp",writer);
model.Serialize("UCS_pyck_joint_"+str(numParticles)+".vtp",writer);

