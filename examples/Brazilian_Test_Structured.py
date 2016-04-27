import sys
sys.path.insert(0, '~/Downloads/repositories/pyck/bin'); # Set this to the path where pyck is compiled
import pyck
import pyck_utils # Utility functions for creating simulation parameters

# ParticleType {Undefined=0, Liquid=1, Boundary=2, Floating=3, Moving=4, Solid =5};

# Geometry 
r = 0.053/2;
h = 0.1;
length_platens = r/4;
height_platens = r/4;
penetration_in_sample = r/8;
domain = [2*r+4*r/4,2*r+4*r/4,0.0];
center = [domain[0]/2,domain[1]/2,0.0];

# Material Properties
smoothingKernelFunc = 2;
speedsound = 1.0;
density = 1.0;
shearmodulus = 1.0;
bulkmodulus = 1.0;
numParticles = 0;

while (numParticles < 50000):
	# Create a packer, see packers directory for options
	# cubic = pyck.CubicPacker(domain,h);
	cubic = pyck.BccPacker(domain,h);
	# cubic = pyck.FccPacker(domain,h);
	# cubic = pyck.HcpPacker(domain,h);
	pack = pyck.StructuredPack(cubic);
	
	sphere = pyck.Sphere(1,center,r);
	
	upper_platen = pyck.Cuboid(2,[-length_platens/2 + center[0],r+center[1]-penetration_in_sample,-1],[length_platens/2 + center[0],r+center[1]+height_platens-penetration_in_sample,1]);
	lower_platen = pyck.Cuboid(3,[-length_platens/2 + center[0],-r+center[1]+penetration_in_sample,-1],[length_platens/2 + center[0],-r+center[1]-height_platens+penetration_in_sample,1]);
	
	# Map the shapes and generate the pack
	pack.AddShape(upper_platen);
	pack.AddShape(lower_platen);
	pack.AddShape(sphere);
	pack.Process();
	
	numParticles = pack.getNumParticles();
	hincrement = 0.000001;
	h = h - hincrement;


# Create a new model from the pack
model = pyck.Model(pack);

stateField = model.CreateIntField("State",1);

model.SetIntField(stateField,1,5);
model.SetIntField(stateField,2,4);
model.SetIntField(stateField,3,4);

# Set default simulation parameters for the VTP file
# SetDefaultParameters computes geometric simulation parameters from pack parameters
pyck_utils.SetParticlePackingParameters(model,domain,h,smoothingKernelFunc,speedsound, density, shearmodulus, bulkmodulus);
# Overwrite some parameters
# Arguments are SetParameter(Label,Value)
model.SetParameter("MaxSteps","100");
model.SetParameter("Mass","0.5");

# Or use a python dictionary to overwrite parameters
parameters = pyck.Parameters({'ViscAlpha':'0.1','ViscBeta':'0.2'});
model.SetParameters(parameters);

# Create a file writer, in this case VTP according to spark format
writer = pyck.SparkWriter();

# Write the VTP file
print("dx = "+str(h));
model.Serialize("Brazilian_Test_"+str(numParticles)+".vtp",writer);
