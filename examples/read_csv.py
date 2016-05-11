import sys
sys.path.insert(0, '~/Downloads/repositories/pyck/bin'); # Set this to the path where pyck is compiled
import pyck
import pyck_utils # Utility functions for creating simulation parameters
import math
import csv

# ParticleType {Undefined=0, Liquid=1, Boundary=2, Floating=3, Moving=4, Solid =5};
# SmoothingKernelFunc {Undefined=0, Cubic kernel function=1, Gaussian kernel function=2, Quintic kernel function=3, Quadratic kernel function=4};

# Geometry (from the original Python script)
r = 0.053/2;
domain = [2*r+4*r/4,2*r+4*r/4,0.0];
h = 0.0002069999999206506; # the one output at the end of the original Python script
smoothingKernelFunc = 1;
material = pyck_utils.chromite;
appliedstressYY = -40000000.0;
ramptime = 10000;

# Reading the csv file
states = [];
positions = [];
ifile  = open('pack.csv', "r")
reader = csv.reader(ifile)
state_col = 2-1; # column containing states
posX_col = 29-1; # column containing x
posY_col = 30-1; # column containing y
posZ_col = 31-1; # column containing z
kernelSum_col = 20-1; # column containing kernel summation
rownum = 0;
numParticles = 0;
dim = 2;
kernelSum = 0.0;
for row in reader:
	if(rownum != 0):
		test = 0;
		colnum = 0;
		for col in row:
			if(colnum == state_col and int(col) != 2):
				states.append(int(col));
				numParticles += 1;
				test = 1;
				count = 1;
			if(colnum == kernelSum_col and test == 1 and count == 1):
				kernelSum += float(col);		
			if(colnum == posX_col and test == 1):
				positions.append(float(col));
			if(colnum == posY_col and test == 1):
				positions.append(float(col));
			if(colnum == posZ_col and test == 1):
				positions.append(float(col));            	
				if(float(col) != 0.0):
					dim = 3;
			colnum += 1
	rownum += 1

ifile.close()
kernelSum = kernelSum / float(numParticles);

# Creation of the model
model = pyck.Model(positions,states,numParticles,dim);

# Generating the correct model properties and initial conditions
stateField = model.CreateIntField("State",1);
model.SetIntField(stateField,5,5);
model.SetIntField(stateField,4,4);
model.SetIntField(stateField,4,4);
velocityField = model.CreateDoubleField("Velocity",3);
model.SetDoubleField(velocityField,5,[0.0,0.0,0.0]);
model.SetDoubleField(velocityField,4,[0.0,0.0,0.0]);
model.SetDoubleField(velocityField,4,[0.0,0.0,0.0]);

densityField = model.CreateDoubleField("Density",1);
model.SetDoubleField(densityField,5,material["density"]);
model.SetDoubleField(densityField,4,material["density"]);
model.SetDoubleField(densityField,4,material["density"]);

mass = material["density"] / kernelSum;
pyck_utils.SetBrazilianTestParameters(model,domain,h,material);
model.SetParameter("Mass","%e" % (mass) );
model.SetParameter("DTime","%e" % (1.0e-8));
model.SetParameter("MovingBoundaryShiftX","%e" % (0.0));
model.SetParameter("MovingBoundaryShiftY","%e" % (-0.1));
model.SetParameter("MovingBoundaryShiftZ","%e" % (0.0));
model.SetParameter("MaxSteps","%d" % (200000));
model.SetParameter("CohnPt2","10.0");
# model.SetParameter("Movsyy","%e" % (appliedstressYY));
# model.SetParameter("BoundariesRampTime","%d" % (ramptime));
# model.SetParameter("IsStressedBoundaries","false");
pyck_utils.SetDamageParameters(model,mass,material);
writer = pyck.SparkWriter();
print("dx = "+str(h));
model.Serialize("Brazilian_Test_"+str(dim)+"D_R_"+str(r)+"_h_"+str(h)+"_"+str(numParticles)+"_relaxed.vtp",writer);
