import sys
sys.path.insert(0, '/mnt/c/ubuntu/packing/git_pyck/pyck/bin'); # Set this to the path where pyck is compiled
import pyck
import FS_hole_utils # Utility functions for creating simulation parameters
from operator import add
def sum(XX, YY):
	return map (add, XX,YY) 

L = [1,1,0.0]
r = 0.002;
dim = 2;

# Create a packer, see packers directory for options
# cubic = pyck.CubicPacker(L,r);
cubic = pyck.Hcp2dPacker(L,r);
pack = pyck.StructuredPack(cubic); # do not create the cubic packer in this function call as it will be destroyed, blame SWIG developers

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

center = [0.501,0.500563,0.0];#pack.GetClosestParticlePosition([0.501,0.501,0]);#
# shiftX = center[0] - 0.05;
# shiftY = center[1] - 0.052;
# shiftZ = center[2] - 0;
CoShift=[0 , 0 , 0];
print center

#print "ShitX %r ShitY %r ShiftZ %r: " %(shiftX, CoShift[1], shiftZ)
solid     = pyck.Cuboid(1, [0, 0, 0] , [1, 1, 0]);
fluid     = pyck.Sphere(2, center, 0.0195);
solidTop  = pyck.Cuboid(3, [0, 1-4*r, 0], [1, 1, 0]);
solidBottome = pyck.Cuboid(4, [0, 0, 0], [1, 4*r, 0]);
solidLeft = pyck.Cuboid(5, [0, 0, 0], [4*r, 1, 0]);
solidRight = pyck.Cuboid(6, [1-4*r, 0, 0], [1, 1, 0]);
solidTR = pyck.Cuboid(7, [1-4*r, 1-4*r, 0], [1, 1, 0]);
solidBR = pyck.Cuboid(8, [1-4*r,0,0], [1, 4*r, 0]);
solidTL = pyck.Cuboid(9, [0, 1-4*r, 0], [4*r, 1, 0]);	
solidBL = pyck.Cuboid(10, [0, 0, 0], [4*r, 4*r, 0]);

# Map the shapes and generate the pack
pack.AddShape(solid);
pack.AddShape(fluid);
pack.AddShape(solidTop);
pack.AddShape(solidBottome);
pack.AddShape(solidLeft);
pack.AddShape(solidRight);
pack.AddShape(solidTR);
pack.AddShape(solidBR);
pack.AddShape(solidTL);
pack.AddShape(solidBL);

pack.Process();

# Create a new model from the pack
model = pyck.Model(pack);

# Create a new field of n-dimensional integers
# Arguments are CreateIntField(label,dimensions)
# label - label for this field in the vtp file
# dimensions - dimensionality of this field, doesnt have to correspond to model dimensions
# Create field of doubles in the same way with CreateDoubleField
stateField = model.CreateIntField("State",1);
for i in range(1, 11):
    model.SetIntField(stateField,i,5);
model.SetIntField(stateField,2,1);

phaseField = model.CreateIntField("Phase",1);
for i in range(1, 11):
    model.SetIntField(phaseField,i,0);
model.SetIntField(phaseField,2,1);   

boundaryIndexField = model.CreateIntField("BoundaryIndex",1);
for i in range(1, 11):
    model.SetIntField(boundaryIndexField,i,1);
model.SetIntField(boundaryIndexField,3,2); # top
model.SetIntField(boundaryIndexField,4,2); # bottom
model.SetIntField(boundaryIndexField,5,3); # left
model.SetIntField(boundaryIndexField,6,3); # right
model.SetIntField(boundaryIndexField,7,4); # TR
model.SetIntField(boundaryIndexField,8,4); # BR
model.SetIntField(boundaryIndexField,9,4); # TL
model.SetIntField(boundaryIndexField,10,4); #BL

densityField = model.CreateDoubleField("Density",1);
for i in range(1, 11):
    model.SetDoubleField(densityField,i,1540);
model.SetDoubleField(densityField,2,1000);

velocityField = model.CreateDoubleField("Velocity",3);
# model.SetDoubleField(velocityField,7,[2.0,0,0]);

FS_hole_utils.Set_HFhole_Parameters(model,L,r);

mass = 0.005303513149097;
model.SetParameter("Mass", "%e %e" % (mass, mass/1.54));

material = FS_hole_utils.gypsum;
FS_hole_utils.SetDamageParameters(model,mass,material);
speedsound = material["speedsound"];
model.SetParameter("DTime", "%e" % (0.2*r/speedsound));

writer = pyck.SparkWriter();
numParticles=pack.GetNumParticles();
# Write the VTP file
#model.Serialize("HFInsituCubic.vtp",writer);
model.Serialize("FS_hole_"+str(numParticles)+".vtp",writer);

