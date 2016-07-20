import sys
sys.path.insert(0, '/f/ranjan/packing/pyck/bin'); # Set this to the path where pyck is compiled
import pyck
import pyck_utils # Utility functions for creating simulation parameters
from operator import add
def sum(XX, YY):
	return map (add, XX,YY) 

PI = 3.14159265359;
L = [0.06,0.06,0]
r = 0.0002;
centre_int =[0.03, 0.03, 0]
radius = 0.026838; #0.02692;
dim = 2;
smoothingKernelFunc = 1;
material = pyck_utils.chromite;
# Create a packer, see packers directory for options
#cubic = pyck.Hcp2dPacker(L,r);
cubic = pyck.CubicPacker(L,r);
pack = pyck.StructuredPack(cubic); # do not create the cubic packer in this function call as it will be destroyed, blame SWIG developers

CenterPt = pack.GetClosestParticlePosition(centre_int);
center = [CenterPt[0]+r/2, CenterPt[1]+r/2,0]; #CenterPt;#

print center

import numpy as np
import math
pos=[]
states=[]
JPNbr =[]
JdCosine=[]
jcount1=0;

# jx1 = np.arange(center[0]-radius-10*r,center[1]+radius+10*r,r);
# theta1 = 0*PI/180;
# cos = math.cos(theta1);
# sin = math.sin(theta1);
# jcount1 =0;
# for i in range(len(jx1)):
# 	jy1=center[1];
# 	jxx1= cos*(jx1[i]-center[0]) - sin*(jy1-jy1)+center[0];
# 	jyy1= sin*(jx1[i]-center[0]) + cos*(jy1-jy1)+jy1;
# 	#jx1[i];
# 	if(((jxx1-center[0])*(jxx1-center[0])+(jyy1-center[1])*(jyy1-center[1]))<=((radius+r/5)*(radius+r/5))):
# 		pos.append(float(jxx1))
# 		pos.append(float(jyy1))
# 		pos.append(float(0))
# 		states.append(int(7));
# 		jcount1 +=1;


# jx2 = np.arange(center[0]-radius-10*r,center[1]+radius+10*r,r);
jx2 = np.arange(0,L[0],r);
theta2 = 0*PI/180;
cos = math.cos(theta2);
sin = math.sin(theta2);
jcount2 =0;
for i in range(len(jx2)):
	jy2=center[1]+40*r;
	jxx2= cos*(jx2[i]-center[0]) - sin*(jy2-jy2)+center[0];
	jyy2= sin*(jx2[i]-center[0]) + cos*(jy2-jy2)+jy2;
	#jx1[i];
	if(((jxx2-center[0])*(jxx2-center[0])+(jyy2-center[1])*(jyy2-center[1]))<=((radius+r/5)*(radius+r/5))):
		pos.append(float(jxx2))
		pos.append(float(jyy2))
		pos.append(float(0))
		states.append(int(8));
		jcount2 +=1;


jx3 = np.arange(0,L[0],r); #np.arange(center[0]-radius-10*r,center[1]+radius+10*r,r);
theta3 = 0*PI/180 ;
cos = math.cos(theta3);
sin = math.sin(theta3);
jcount3 =0;
for i in range(len(jx3)):
	jy3=center[1]-40*r;
	jxx3= cos*(jx3[i]-center[0]) - sin*(jy3-jy3)+center[0];
	jyy3= sin*(jx3[i]-center[0]) + cos*(jy3-jy3)+jy3;
	#jx1[i];
	if(((jxx3-center[0])*(jxx3-center[0])+(jyy3-center[1])*(jyy3-center[1]))<=((radius+r/5)*(radius+r/5))):
		pos.append(float(jxx3))
		pos.append(float(jyy3))
		pos.append(float(0))
		states.append(int(9));
		jcount3 +=1;


jx4 = np.arange(0,L[0],r); #np.arange(center[0]-radius-10*r,center[1]+radius+10*r,r);
theta4 = 0*PI/180;
cos = math.cos(theta4);
sin = math.sin(theta4);
jcount4 =0;
for i in range(len(jx4)):
	jy4=center[1]+80*r;
	jxx4= cos*(jx4[i]-center[0]) - sin*(jy4-jy4)+center[0];
	jyy4= sin*(jx4[i]-center[0]) + cos*(jy4-jy4)+jy4;
	#jx1[i];
	if(((jxx4-center[0])*(jxx4-center[0])+(jyy4-center[1])*(jyy4-center[1]))<=((radius+r/5)*(radius+r/5))):
		pos.append(float(jxx4))
		pos.append(float(jyy4))
		pos.append(float(0))
		states.append(int(10));
		jcount4 +=1;


jx5 = np.arange(0,L[0],r);#np.arange(center[0]-radius-10*r,center[1]+radius+10*r,r);
theta5 = 0*PI/180;
cos = math.cos(theta5);
sin = math.sin(theta5);
jcount5 =0;
for i in range(len(jx5)):
	jy5=center[1]-80*r;
	jxx5= cos*(jx5[i]-center[0]) - sin*(jy5-jy5)+center[0];
	jyy5= sin*(jx5[i]-center[0]) + cos*(jy5-jy5)+jy5;
	#jx1[i];
	if(((jxx5-center[0])*(jxx5-center[0])+(jyy5-center[1])*(jyy5-center[1]))<=((radius+r/5)*(radius+r/5))):
		pos.append(float(jxx5))
		pos.append(float(jyy5))
		pos.append(float(0))
		states.append(int(11));
		jcount5 +=1;






#
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
#solid = pyck.Cuboid(1,[5*r,5*r,0],[0.054+5*r,0.135+5*r,0])
solid = pyck.Sphere(1,center,radius)
lowerplaten = pyck.Cuboid(2,[center[0]-7.5*r, center[1]-radius-10*r,0], [center[0]+7.5*r, center[1]-radius,0])
upperplaten = pyck.Cuboid(3,[center[0]-7.5*r, center[1]+radius,0], [center[0]+7.5*r, center[1]+radius+10*r,0])

# Map the shapes and generate the pack
pack.AddShape(solid);
pack.AddShape(lowerplaten);
pack.AddShape(upperplaten);

pack.Process();

# Create a new model from the pack
model = pyck.Model(pack);
# jmodel = pyck.Model(jpack);
model.AddPack(pos, states, jcount1+jcount2+jcount3+jcount4+jcount5,dim);

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
model.SetIntField(stateField,8,6);
model.SetIntField(stateField,9,6);
model.SetIntField(stateField,10,6);
model.SetIntField(stateField,11,6);



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
model.SetDoubleField(densityField,8,2500);
model.SetDoubleField(densityField,9,2500);
model.SetDoubleField(densityField,10,2500);
model.SetDoubleField(densityField,11,2500);


velocityField = model.CreateDoubleField("Velocity",3);
# model.SetDoubleField(velocityField,7,[2.0,0,0]);

JontPointNumberField = model.CreateIntField("JPNbr",1);
for i in range(1, 4):
    model.SetIntField(JontPointNumberField,i,-1000);
# model.SetIntField(JontPointNumberField,7,0);
model.SetIntField(JontPointNumberField,8,0);
model.SetIntField(JontPointNumberField,9,1);
model.SetIntField(JontPointNumberField,10,2);
model.SetIntField(JontPointNumberField,11,3);


JdcosField = model.CreateDoubleField("JdCosine",3);
for i in range(1, 4):
    model.SetDoubleField(JdcosField,i,[-1000,-1000,-1000]);
# model.SetDoubleField(JdcosField,7,[math.cos(theta1),math.sin(theta1),0]);
model.SetDoubleField(JdcosField,8,[math.cos(theta2),math.sin(theta2),0]);
model.SetDoubleField(JdcosField,9,[-math.cos(theta3),math.sin(theta3),0]);
model.SetDoubleField(JdcosField,10,[math.cos(theta4),math.sin(theta4),0]);
model.SetDoubleField(JdcosField,11,[-math.cos(theta5),math.sin(theta5),0]);


pyck_utils.SetJointParameters(model,L,r,material,smoothingKernelFunc);
pyck_utils.SetGeometricParameters(model,L,r,smoothingKernelFunc);
model.SetParameter("Mass","%e" % (0.0001) ); #86.0959926801380e-006
# model.SetParameter("Mass","3.850204950429613e-04 2.500133084694554e-04")
writer = pyck.SparkWriter();
numParticles=pack.GetNumParticles();
# Write the VTP file
#model.Serialize("HFInsituCubic.vtp",writer);
model.Serialize("Brazilian_Cubic4joint0CentreSym_"+str(numParticles)+".vtp",writer);

