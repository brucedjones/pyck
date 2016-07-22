import sys
sys.path.insert(0, '/f/ranjan/packing/pyck/bin'); # Set this to the path where pyck is compiled
import pyck
import pyck_utils # Utility functions for creating simulation parameters
from operator import add
def sum(XX, YY):
	return map (add, XX,YY)


Lsample = [1.0,1.0,0.0]
PI = 3.14159265359;
L = [Lsample[0]*2.0,Lsample[1]*2.0,Lsample[2]*2.0]
r = 0.08;
dim = 2;
smoothingKernelFunc = 1;
material = pyck_utils.chromite;

numParticles = 0;

while (numParticles < 1000):
	# Create a packer, see packers directory for options
	cubic = pyck.CubicPacker(L,r);
	pack = pyck.StructuredPack(cubic); # do not create the cubic packer in this function call as it will be destroyed, blame SWIG developers

	# solid = pyck.Cuboid(1,[Lsample[0]/2,Lsample[1]/2,Lsample[2]/2],[Lsample[0]+Lsample[0]/2,Lsample[1]+Lsample[1]/2,Lsample[2]+Lsample[2]/2])
	solid = pyck.Cuboid(1,[Lsample[0]/2,Lsample[1]/2,Lsample[2]/2],[Lsample[0]+Lsample[0]/2,Lsample[1]+Lsample[1]/2,0.0])
	
	# Map the shapes and generate the pack
	pack.AddShape(solid);
	
	pack.Process();
	numParticles = pack.GetNumParticles();
	hincrement = 0.00001;
	r = r - hincrement;


# Create a new model from the pack
model = pyck.Model(pack);


stateField = model.CreateIntField("State",1);

model.SetIntField(stateField,1,5);


densityField = model.CreateDoubleField("Density",1);

model.SetDoubleField(densityField,1,material["density"]);
model.SetDoubleField(densityField,2,material["density"]);
model.SetDoubleField(densityField,3,material["density"]);

velocityField = model.CreateDoubleField("Velocity",3);


# mass = ( material["density"]*(Lsample[0]*Lsample[1]*Lsample[2])) / float(pack.GetNumParticlesByState(1));
mass = ( material["density"]*(Lsample[0]*Lsample[1])) / float(pack.GetNumParticlesByState(1));
pyck_utils.SetBrazilianTestParameters(model,L,r,material);
model.SetParameter("Mass","%e" % (mass) );
model.SetParameter("IsCrack","true");
model.SetParameter("IsFlags","true");
model.SetParameter("Cracksxx","0");
model.SetParameter("Cracksxy","0");
model.SetParameter("Crackszz","0");
model.SetParameter("Cracksyz","0");
model.SetParameter("Cracksxz","0");
model.SetParameter("Cracksyy","-30000000");
model.SetParameter("BoundariesRampTime","500");
model.SetParameter("CrackLength","0.2");
model.SetParameter("CrackThickness","0.03");
model.SetParameter("CrackX","1.0");
model.SetParameter("CrackY","1.0");
model.SetParameter("CrackZ","0.0");
model.SetParameter("IsElastoPlasticDamage","true");
model.SetParameter("IsDruckerPragerPlasticity","true");
model.SetParameter("MaxSteps","500");
pyck_utils.SetDamageParameters(model,mass,material);

writer = pyck.SparkWriter();
numParticles=pack.GetNumParticles();

model.Serialize("TestPennyShape3D_"+str(numParticles)+".vtp",writer);

