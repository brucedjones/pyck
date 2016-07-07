import sys
sys.path.insert(0, '/f/ranjan/packing/pyck/bin'); # Set this to the path where pyck is compiled
import pyck
import pyck_utils # Utility functions for creating simulation parameters
from operator import add
def sum(XX, YY):
	return map (add, XX,YY)


Lsample = [0.054,0.135,0.0]
PI = 3.14159265359;
L = [0.1,0.2,0]
r = 0.002;
dim = 2;
smoothingKernelFunc = 1;
material = pyck_utils.chromite;
# Create a packer, see packers directory for options
cubic = pyck.Hcp2dPacker(L,r);
pack = pyck.StructuredPack(cubic); # do not create the cubic packer in this function call as it will be destroyed, blame SWIG developers

import numpy as np
import math

pos=[];
states=[];
JPNbr =[];
JdCosine=[];

jcount1=0;
theta1 = 60*PI/180;
percentage1 = 0.3;
cos = math.cos(theta1);
sin = math.sin(theta1);
tan = math.tan(theta1);
P1 = [5*r,percentage1*Lsample[1],0.0];
P2 = [Lsample[0]+5*r,Lsample[0]*tan+percentage1*Lsample[1],0.0];

jx1 = np.arange(P1[0],P2[0],r*cos);
jy1 = np.arange(P1[1],P2[1],r*sin);


for i in range(len(jx1)):
	if( (jx1[i] >= 5*r) & (jx1[i] <= (Lsample[0]+5*r)) & (jy1[i] >= 5*r) & (jy1[i] <= (Lsample[1]+5*r)) ):
		pos.append(float(jx1[i]))
		pos.append(float(jy1[i]))
		pos.append(float(0))
		states.append(int(7));
		jcount1 +=1;


jcount2=0;
theta2 = -45*PI/180;
percentage2 = 0.6;
cos = math.cos(theta2);
sin = math.sin(theta2);
tan = math.tan(theta2);
P1 = [5*r,percentage2*Lsample[1],0.0];
P2 = [Lsample[0]+5*r,Lsample[0]*tan+percentage2*Lsample[1],0.0];

jx2 = np.arange(P1[0],P2[0],r*cos);
jy2 = np.arange(P1[1],P2[1],r*sin);

for i in range(len(jx2)):
	if( (jx2[i] >= 5*r) & (jx2[i] <= (Lsample[0]+5*r)) & (jy2[i] >= 5*r) & (jy2[i] <= (Lsample[1]+5*r))):
		pos.append(float(jx2[i]))
		pos.append(float(jy2[i]))
		pos.append(float(0))
		states.append(int(8));
		jcount2 +=1;

lowerplaten = pyck.Cuboid(2,[r/2,r/2,0], [Lsample[0]+10*r,5*r,0])
upperplaten = pyck.Cuboid(3,[r/2,Lsample[1]+5*r,0],[Lsample[0]+10*r,Lsample[1]+10*r,0])
solid = pyck.Cuboid(1,[5*r,5*r,0],[Lsample[0]+5*r,Lsample[1]+5*r,0])

# Map the shapes and generate the pack
pack.AddShape(solid);
pack.AddShape(lowerplaten);
pack.AddShape(upperplaten);

pack.Process();

# Create a new model from the pack
model = pyck.Model(pack);

model.AddPack(pos, states, jcount1+jcount2,dim);

stateField = model.CreateIntField("State",1);

model.SetIntField(stateField,1,5);
model.SetIntField(stateField,2,4);
model.SetIntField(stateField,3,4);
model.SetIntField(stateField,7,6);
model.SetIntField(stateField,8,6);

densityField = model.CreateDoubleField("Density",1);

model.SetDoubleField(densityField,1,material["density"]);
model.SetDoubleField(densityField,2,material["density"]);
model.SetDoubleField(densityField,3,material["density"]);
model.SetDoubleField(densityField,7,material["density"]);
model.SetDoubleField(densityField,8,material["density"]);

velocityField = model.CreateDoubleField("Velocity",3);


JointPointNumberField = model.CreateIntField("JPNbr",1);
for i in range(1, 4):
    model.SetIntField(JointPointNumberField,i,-1000);

model.SetIntField(JointPointNumberField,7,0);
model.SetIntField(JointPointNumberField,8,1);

JdcosField = model.CreateDoubleField("JdCosine",3);
for i in range(1, 4):
    model.SetDoubleField(JdcosField,i,[-1000,-1000,-1000]);

model.SetDoubleField(JdcosField,7,[math.cos(theta1),math.sin(theta1),0]);
model.SetDoubleField(JdcosField,8,[math.cos(theta2),math.sin(theta2),0]);


mass = ( material["density"]*(Lsample[0]*Lsample[1])) / float(pack.GetNumParticlesByState(1));
pyck_utils.SetJointParameters(model,L,r,material,smoothingKernelFunc);
model.SetParameter("IsJoint","true");
model.SetParameter("NumJoints","%d" % (2) );
model.SetParameter("Mass","%e" % (mass) );
model.SetParameter("JKnn","%e" % (100.0e+09) );
model.SetParameter("JKtt","%e" % (100.0e+09) );
model.SetParameter("IParticleCheck","%e" % (-100) );
model.SetParameter("JCohesion","%e" % (2.25e5) );
model.SetParameter("JFrictionAngle","%e" % (20.0) );
model.SetParameter("MovingBoundaryShiftX","%e" % (0.0));
model.SetParameter("MovingBoundaryShiftY","%e" % (-1.0));
model.SetParameter("MovingBoundaryShiftZ","%e" % (0.0));

writer = pyck.SparkWriter();
numParticles=pack.GetNumParticles();

model.Serialize("UCS_pyck_joint_"+str(numParticles)+".vtp",writer);

