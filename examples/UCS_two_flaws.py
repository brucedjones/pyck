import sys
sys.path.insert(0, '/f/ranjan/packing/pyck/bin'); # Set this to the path where pyck is compiled
import numpy as np
import math
import pyck
import pyck_utils # Utility functions for creating simulation parameters
from operator import add
def sum(XX, YY):
	return map (add, XX,YY)

PI = 3.14159265359;

Flaw_Width = 1.27e-3; # 1.27mm
Flaw_Length = 1.27e-2; # 1.27cm

x1 = np.array([-Flaw_Length/2,Flaw_Width/2]);
x2 = np.array([-Flaw_Length/2,-Flaw_Width/2]);
x3 = np.array([Flaw_Length/2,Flaw_Width/2]);

y1 = np.array([Flaw_Length/2,-Flaw_Width/2]);
y2 = np.array([Flaw_Length/2,Flaw_Width/2]);
y3 = np.array([-Flaw_Length/2,-Flaw_Width/2]);

theta = 30 * (PI/180);

rot = np.array( ((math.cos(theta),-math.sin(theta)), (math.sin(theta), math.cos(theta))) );

#newt1
newx1 = rot.dot(x1);
newx2 = rot.dot(x2);
newx3 = rot.dot(x3);

#newt2
newy1 = rot.dot(y1);
newy2 = rot.dot(y2);
newy3 = rot.dot(y3);

#beta angle
theta2 = 60 * (PI/180);
rot2 = np.array( ((math.cos(theta2),-math.sin(theta2)), (math.sin(theta2), math.cos(theta2))) );
coef = 2.0;
Separation_length = np.array([coef*Flaw_Length/2,0.0]);
Distance = rot.dot(Separation_length);
newDist = ((newx3 + newy1) / 2) + rot2.dot(Distance);

translationVector = newDist - ((newx1 + newy3) / 2);

#newt1
new2x1 = newx1 + translationVector;
new2x2 = newx2 + translationVector;
new2x3 = newx3 + translationVector;

#newt2
new2y1 = newy1 + translationVector;
new2y2 = newy2 + translationVector;
new2y3 = newy3 + translationVector;

center = ((((newx3 + newy1) / 2)) + (((new2x1 + new2y3) / 2)))/2;

newx1 = newx1 - center;
newx2 = newx2 - center;
newx3 = newx3 - center;
newy1 = newy1 - center;
newy2 = newy2 - center;
newy3 = newy3 - center;

new2x1 = new2x1 - center;
new2x2 = new2x2 - center;
new2x3 = new2x3 - center;
new2y1 = new2y1 - center;
new2y2 = new2y2 - center;
new2y3 = new2y3 - center;




Lsample = [0.0762,0.1524,0.0]

L = [Lsample[0]*2.0,Lsample[1]*2.0,0]
r = 0.08;
dim = 2;
smoothingKernelFunc = 1;
material = pyck_utils.chromite;
numParticles = 0;

while (numParticles < 50000):
	# Create a packer, see packers directory for options
	cubic = pyck.Hcp2dPacker(L,r);
	pack = pyck.StructuredPack(cubic); # do not create the cubic packer in this function call as it will be destroyed, blame SWIG developers
	
	lowerplaten = pyck.Cuboid(2,[r/2,r/2,0], [Lsample[0]+10*r,5*r,0])
	upperplaten = pyck.Cuboid(3,[r/2,Lsample[1]+5*r,0],[Lsample[0]+10*r,Lsample[1]+10*r-r/2,0])
	solid = pyck.Cuboid(1,[5*r,5*r,0],[Lsample[0]+5*r,Lsample[1]+5*r,0])

	center_sample = [5*r+Lsample[0]/2,5*r+Lsample[1]/2,0]

	left_uphalf_flaw = pyck.TriPrism(0,[newx1[0]+center_sample[0],newx1[1]+center_sample[1],0.0],[newx2[0]+center_sample[0],newx2[1]+center_sample[1],0.0],[newx3[0]+center_sample[0],newx3[1]+center_sample[1],0.0],0.0)
	left_lowhalf_flaw = pyck.TriPrism(0,[newy1[0]+center_sample[0],newy1[1]+center_sample[1],0.0],[newy2[0]+center_sample[0],newy2[1]+center_sample[1],0.0],[newy3[0]+center_sample[0],newy3[1]+center_sample[1],0.0],0.0)
	right_uphalf_flaw = pyck.TriPrism(0,[new2x1[0]+center_sample[0],new2x1[1]+center_sample[1],0.0],[new2x2[0]+center_sample[0],new2x2[1]+center_sample[1],0.0],[new2x3[0]+center_sample[0],new2x3[1]+center_sample[1],0.0],0.0)
	right_lowhalf_flaw = pyck.TriPrism(0,[new2y1[0]+center_sample[0],new2y1[1]+center_sample[1],0.0],[new2y2[0]+center_sample[0],new2y2[1]+center_sample[1],0.0],[new2y3[0]+center_sample[0],new2y3[1]+center_sample[1],0.0],0.0)


	# Map the shapes and generate the pack
	pack.AddShape(solid);
	pack.AddShape(lowerplaten);
	pack.AddShape(upperplaten);
	pack.AddShape(left_uphalf_flaw);
	pack.AddShape(left_lowhalf_flaw);
	pack.AddShape(right_uphalf_flaw);
	pack.AddShape(right_lowhalf_flaw);
	
	pack.Process();
	numParticles = pack.GetNumParticles();
	hincrement = 0.00001;
	r = r - hincrement;


# Create a new model from the pack
model = pyck.Model(pack);


stateField = model.CreateIntField("State",1);

model.SetIntField(stateField,1,5);
model.SetIntField(stateField,2,4);
model.SetIntField(stateField,3,4);


densityField = model.CreateDoubleField("Density",1);

model.SetDoubleField(densityField,1,material["density"]);
model.SetDoubleField(densityField,2,material["density"]);
model.SetDoubleField(densityField,3,material["density"]);

velocityField = model.CreateDoubleField("Velocity",3);

appliedstressYY = -100000000.0;
ramptime = 10000;
mass = ( material["density"]*(Lsample[0]*Lsample[1])) / float(pack.GetNumParticlesByState(1));
pyck_utils.SetBrazilianTestParameters(model,L,r,material);
model.SetParameter("Mass","%e" % (mass) );
model.SetParameter("MovingBoundaryShiftX","%e" % (0.0));
model.SetParameter("MovingBoundaryShiftY","%e" % (-1.0));
model.SetParameter("MovingBoundaryShiftZ","%e" % (0.0));
model.SetParameter("MaxSteps","10000");
model.SetParameter("Movsyy","%e" % (appliedstressYY));
model.SetParameter("BoundariesRampTime","%d" % (ramptime));
model.SetParameter("IsStressedBoundaries","true");
pyck_utils.SetDamageParameters(model,mass,material);

writer = pyck.SparkWriter();
numParticles=pack.GetNumParticles();

model.Serialize("UCS_TwoFlaws_"+str(numParticles)+"_"+str(int(coef))+"a"+str(int(theta*180/PI))+str(int(theta2*180/PI))+".vtp",writer);