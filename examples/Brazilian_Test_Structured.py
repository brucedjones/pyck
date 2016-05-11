import sys
sys.path.insert(0, '~/Downloads/repositories/pyck/bin'); # Set this to the path where pyck is compiled
import pyck
import pyck_utils # Utility functions for creating simulation parameters
import math
# ParticleType {Undefined=0, Liquid=1, Boundary=2, Floating=3, Moving=4, Solid =5};
# SmoothingKernelFunc {Undefined=0, Cubic kernel function=1, Gaussian kernel function=2, Quintic kernel function=3, Quadratic kernel function=4};

# Geometry 
r = 0.053/2;
h = 0.03;
length_platens = r/4;
height_platens = r/4;
penetration_in_sample = r/8;
domain = [2*r+4*r/4,2*r+4*r/4,0.0];
center_init = [domain[0]/2,domain[1]/2,0.0];

# Material Properties
smoothingKernelFunc = 1;
material = pyck_utils.chromite;
appliedstressYY = -40000000.0;
ramptime = 10000;

numParticles = 0;

while (numParticles < 50000):
	# Create a packer, see packers directory for options
	# cubic = pyck.CubicPacker(domain,h);
	# cubic = pyck.BccPacker(domain,h);
	# cubic = pyck.FccPacker(domain,h);
	# cubic = pyck.HcpPacker(domain,h);
	cubic = pyck.Hcp2dPacker(domain,h);
	pack = pyck.StructuredPack(cubic);
	center = pack.GetClosestParticlePosition(center_init);
	sphere = pyck.Sphere(1,center,r);
	
	upper_platen = pyck.Cuboid(2,[-length_platens/2 + center[0],r+center[1]-penetration_in_sample,-1],[length_platens/2 + center[0],r+center[1]+height_platens-penetration_in_sample,1]);
	lower_platen = pyck.Cuboid(3,[-length_platens/2 + center[0],-r+center[1]+penetration_in_sample,-1],[length_platens/2 + center[0],-r+center[1]-height_platens+penetration_in_sample,1]);
	
	# Map the shapes and generate the pack
	pack.AddShape(upper_platen);
	pack.AddShape(lower_platen);
	pack.AddShape(sphere);
	pack.Process();
	
	numParticles = pack.GetNumParticles();
	hincrement = 0.000001;
	h = h - hincrement;


# Create a new model from the pack
model = pyck.Model(pack);
dim = 2;
h =h + hincrement;
stateField = model.CreateIntField("State",1);
model.SetIntField(stateField,1,5);
model.SetIntField(stateField,2,4);
model.SetIntField(stateField,3,4);
velocityField = model.CreateDoubleField("Velocity",3);
model.SetDoubleField(velocityField,1,[0.0,0.0,0.0]);
model.SetDoubleField(velocityField,2,[0.0,0.0,0.0]);
model.SetDoubleField(velocityField,3,[0.0,0.0,0.0]);
densityField = model.CreateDoubleField("Density",1);
model.SetDoubleField(densityField,1,material["density"]);
model.SetDoubleField(densityField,2,material["density"]);
model.SetDoubleField(densityField,3,material["density"]);

mass = ( material["density"]*(math.pi*1.0*(r)*(r))    ) / float(pack.GetNumParticlesByState(1));
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
# Create a file writer, in this case VTP according to spark format
writer = pyck.SparkWriter();

# Write the VTP file
model.Serialize("Brazilian_Test_"+str(dim)+"D_R_"+str(r)+"_h_"+str(h)+"_"+str(numParticles)+".vtp",writer);
