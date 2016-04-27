import sys
sys.path.insert(0, '~/Downloads/repositories/pyck/bin'); # Set this to the path where pyck is compiled
import pyck
import pyck_utils # Utility functions for creating simulation parameters
import math

# ParticleType {Undefined=0, Liquid=1, Boundary=2, Floating=3, Moving=4, Solid =5};

# Geometry 
domain = [1.0,1.0,0.0];
center = [0.5,0.5,0.0];
r = 0.053/2;
# r = 0.1;
h = 0.001;
length_platens = r/4;
height_platens = r/4;
penetration_in_sample = r/8;

# Material Properties
smoothingKernelFunc = 2;
speedsound = 1.0;
density = 1.0;
shearmodulus = 1.0;
bulkmodulus = 1.0;
numParticles = 0;






# while (numParticles < 5000):
# Create a packer, see packers directory for options
pack = pyck.CylindricalPacker(center, domain[0]*math.sqrt(2)/2, 1.0, h, 0);

sphere = pyck.Sphere(1,center,r);

upper_platen = pyck.Cuboid(2,[-length_platens/2 + center[0],r+center[1]-penetration_in_sample,-1],[length_platens/2 + center[0],r+center[1]+height_platens-penetration_in_sample,1]);
lower_platen = pyck.Cuboid(3,[-length_platens/2 + center[0],-r+center[1]+penetration_in_sample,-1],[length_platens/2 + center[0],-r+center[1]-height_platens+penetration_in_sample,1]);

# Map the shapes and generate the pack
pack.AddShape(upper_platen);
pack.AddShape(lower_platen);
pack.AddShape(sphere);
pack.Process();

numParticles = pack.getNumParticles();
print(str(numParticles));
	# h = h - 0.000001;



# pack = pyck.CylindricalPacker(center, r-5*h, ratio_ellipse, h, 5);
# pack.updateStates(center, r + 0.0001, ratio_ellipse, 2);
# positions = pack.getPositions();
# states = pack.getStates();
numParticles = pack.getNumParticles();
dim = pack.getDim();

model = pyck.Model(pack);

stateField = model.CreateIntField("State",1);
model.SetIntField(stateField,1,5);
model.SetIntField(stateField,2,4);
model.SetIntField(stateField,3,4);

velocityField = model.CreateDoubleField("Velocity",3);
model.SetDoubleField(velocityField,5,[0.0,0.0,0.0]);
# model.SetDoubleField(velocityField,2,[0.0,0.0,0.0]);

densityField = model.CreateDoubleField("Density",1);
model.SetDoubleField(densityField,5,1);
# model.SetDoubleField(densityField,2,1);

pyck_utils.SetDefaultParameters(model,domain,h,smoothingKernelFunc,speedsound, density, shearmodulus, bulkmodulus);
model.SetParameter("Mass","%f" % (density*((math.pi*1.0*r*r)/float(numParticles))));
model.SetParameter("DTime","%f" % (0.00001));

writer = pyck.SparkWriter();

model.Serialize("Brazilian_Test_"+str(dim)+"D_R_"+str(r)+"_"+str(numParticles)+".vtp",writer);
