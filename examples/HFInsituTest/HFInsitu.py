import sys
sys.path.insert(0, '/f/pkpan/pyck/bin'); # Set this to the path where pyck is compiled
import pyck
import pyck_utils # Utility functions for creating simulation parameters
from operator import add
def sum(XX, YY):
	return map (add, XX,YY) 

L = [0.197,0.104,0.0]
r = 0.00050401797432575294;#0.0005;
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

center = pack.GetClosestParticlePosition([0.05,0.052,0]);
shiftX = center[0] - 0.05;
shiftY = center[1] - 0.052;
shiftZ = center[2] - 0;
CoShift=[shiftX, -r/2, shiftZ]

print "ShitX %r ShitY %r ShiftZ %r: " %(shiftX, CoShift[1], shiftZ)
bottomFluidChannel     = pyck.Cuboid(1,sum([0,0.048,0],CoShift),sum([0.045,0.050,0],CoShift));
topFluidChannel        = pyck.Cuboid(3,sum([0,0.054,0],CoShift),sum([0.045,0.056,0],CoShift));
fluid                  = pyck.Cuboid(2,sum([0,0.050,0],CoShift),sum([0.035,0.054,0],CoShift));
leftTopSolidBd         = pyck.Cuboid(4,sum([0.043,0.056,0],CoShift),sum([0.045,0.104,0],CoShift));
leftBottomSolidBd      = pyck.Cuboid(5,sum([0.043,0,0],CoShift),sum([0.045,0.048,0],CoShift));
solid                  = pyck.Cuboid(6,sum([0.045,0.002,0],CoShift),sum([0.195,0.102,0],CoShift));
waveMaker              = pyck.Cuboid(7,sum([0,0.05,0],CoShift),sum([0.002,0.054,0],CoShift));
solidTop               = pyck.Cuboid(8,sum([0.045,0.1000,0],CoShift),sum([0.1935,0.102,0],CoShift));
solidRightTop          = pyck.Cuboid(9,sum([0.1935,0.1000,0],CoShift),sum([0.195,0.102,0],CoShift));
solidRightBottom       = pyck.Cuboid(10,sum([0.1935,0.002,0],CoShift),sum([0.195,0.0035,0],CoShift));
solidRight             = pyck.Cuboid(11,sum([0.1935,0.0035,0],CoShift),sum([0.195,0.1005,0],CoShift));
solidBottom            = pyck.Cuboid(12,sum([0.045,0.002,0],CoShift),sum([0.1935,0.0035+r,0],CoShift));
notch                  = pyck.TriPrism(0,sum([0.045,0.050,0],CoShift),sum([0.05,0.052,0],CoShift),sum([0.045,0.054,0],CoShift),0);

# Map the shapes and generate the pack
pack.AddShape(fluid);
pack.AddShape(solid);
pack.AddShape(notch);
pack.AddShape(waveMaker);
pack.AddShape(bottomFluidChannel); # As with creating the cubic packer, do not create the shapes within the function call here
pack.AddShape(topFluidChannel);
pack.AddShape(solidTop);
pack.AddShape(solidBottom);
pack.AddShape(solidRight);
pack.AddShape(solidRightBottom);
pack.AddShape(solidRightTop);
pack.AddShape(leftTopSolidBd);
pack.AddShape(leftBottomSolidBd);


pack.Process();

# Create a new model from the pack
model = pyck.Model(pack);

# Create a new field of n-dimensional integers
# Arguments are CreateIntField(label,dimensions)
# label - label for this field in the vtp file
# dimensions - dimensionality of this field, doesnt have to correspond to model dimensions
# Create field of doubles in the same way with CreateDoubleField
stateField = model.CreateIntField("State",1);
for i in range(1, 13):
    model.SetIntField(stateField,i,5);
model.SetIntField(stateField,1,2);
model.SetIntField(stateField,2,1);
model.SetIntField(stateField,3,2);
model.SetIntField(stateField,4,2);
model.SetIntField(stateField,5,2);
model.SetIntField(stateField,7,6);



phaseField = model.CreateIntField("Phase",1);
for i in range(1, 7):
    model.SetIntField(phaseField,i,0);
model.SetIntField(phaseField,2,1);   
model.SetIntField(phaseField,7,1);

boundaryIndexField = model.CreateIntField("BoundaryIndex",1);
model.SetIntField(boundaryIndexField,1,5);
model.SetIntField(boundaryIndexField,3,5);
model.SetIntField(boundaryIndexField,4,5);
model.SetIntField(boundaryIndexField,5,5);
model.SetIntField(boundaryIndexField,8,8);
model.SetIntField(boundaryIndexField,9,10);
model.SetIntField(boundaryIndexField,10,10);
model.SetIntField(boundaryIndexField,11,9);
model.SetIntField(boundaryIndexField,12,7);

densityField = model.CreateDoubleField("Density",1);
for i in range(1, 13):
    model.SetDoubleField(densityField,i,1540);
#model.SetIntField(densityField,6,1540);
model.SetDoubleField(densityField,2,1000);   
model.SetDoubleField(densityField,7,1000);

velocityField = model.CreateDoubleField("Velocity",3);
# model.SetDoubleField(velocityField,7,[2.0,0,0]);

pyck_utils.SetHydroFracturingParameters(model,L,r);
model.SetParameter("Mass","0.00033681832187097428 0.00021871319602011316")
model.SetParameter("DTime", 9e-08);

writer = pyck.SparkWriter();
numParticles=pack.GetNumParticles();
# Write the VTP file
#model.Serialize("HFInsituCubic.vtp",writer);
model.Serialize("HFInsituCubic_"+str(numParticles)+".vtp",writer);

