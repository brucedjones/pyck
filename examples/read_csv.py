import sys
sys.path.insert(0, '~/Downloads/repositories/pyck/bin'); # Set this to the path where pyck is compiled
import pyck
import pyck_utils # Utility functions for creating simulation parameters
import math
import csv

# ParticleType {Undefined=0, Liquid=1, Boundary=2, Floating=3, Moving=4, Solid =5};
# Geometry (from the original Python script)
r = 0.053/2;
domain = [2*r+4*r/4,2*r+4*r/4,0.0];
h = 0.0002059999999206506; # the one output at the end of the original Python script
smoothingKernelFunc = 3;
speedsound = 1466.312;
density = 1540;
youngmodulus = 5.96*pow(10.0,9.0);
poissonratio = 0.2;
shearmodulus = 2.483333*pow(10.0,9.0);
bulkmodulus = 3.31111*pow(10.0,9.0);
yieldtensilestrength = 3.2*pow(10.0,6.0);
kdamage = 5392570000000000000000000000000000000;
mdamage = 9.0;
cohesion = 5203840.0;
cohnpt1 = 2601920.0;
cohnpt2 = 0.0;
plasstrpt1 = 0.05;
plasstrpt2 = 0.1;
frictionangle = 55.818340999999997;
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
print(kernelSum);
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
model.SetDoubleField(densityField,5,density);
model.SetDoubleField(densityField,4,density);
model.SetDoubleField(densityField,4,density);

pyck_utils.SetBrazilianTestParameters(model,domain,h,smoothingKernelFunc,speedsound, density,youngmodulus,poissonratio, shearmodulus, bulkmodulus, yieldtensilestrength, kdamage, mdamage, cohesion, cohnpt1,cohnpt2,plasstrpt1,plasstrpt2,frictionangle,appliedstressYY,ramptime);
model.SetParameter("Mass","%e" % (density / kernelSum) );
model.SetParameter("DTime","%e" % (1.0e-8));
model.SetParameter("MovingBoundaryShiftX","%e" % (0.0));
model.SetParameter("MovingBoundaryShiftY","%e" % (-1.0));
model.SetParameter("MovingBoundaryShiftZ","%e" % (0.0));

writer = pyck.SparkWriter();
print("dx = "+str(h));
model.Serialize("Brazilian_Test_"+str(dim)+"D_R_"+str(r)+"_h_"+str(h)+"_"+str(numParticles)+"_relaxed.vtp",writer);
