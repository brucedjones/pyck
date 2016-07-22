import sys
sys.path.insert(0, '~/Downloads/repositories/pyck/bin'); # Set this to the path where pyck is compiled
import pyck
import pyck_utils # Utility functions for creating simulation parameters
import math
# ParticleType {Undefined=0, Liquid=1, Boundary=2, Floating=3, Moving=4, Solid =5};
# SmoothingKernelFunc {Undefined=0, Cubic kernel function=1, Gaussian kernel function=2, Quintic kernel function=3, Quadratic kernel function=4};

# Geometry 
Beam_Length = 1.0;
Beam_Width = 0.1;
Beam_Depth = 0.1;
Boundary_Length = 0.05;
h = 0.08;

domain = [2.0*Beam_Length,2.0*Beam_Width,2.0*Beam_Depth];
center_init = [domain[0]/2,domain[1]/2,domain[2]/2];

# Material Properties
smoothingKernelFunc = 1;
material = pyck_utils.chromite;
appliedstressYY = -40000000.0;
ramptime = 10000;

numParticles = 0;

while (numParticles < 100):
	# Create a packer, see packers directory for options
	cubic = pyck.CubicPacker(domain,h);
	# cubic = pyck.BccPacker(domain,h);
	# cubic = pyck.FccPacker(domain,h);
	# cubic = pyck.HcpPacker(domain,h);
	# cubic = pyck.Hcp2dPacker(domain,h);
	pack = pyck.StructuredPack(cubic);
	center = pack.GetClosestParticlePosition(center_init);
	# center = center_init;
	
	beam = pyck.Cuboid(1,[Boundary_Length,Beam_Width/2.0,Beam_Depth/2.0],[Boundary_Length+Beam_Length,Beam_Width+Beam_Width/2.0,Beam_Depth+Beam_Depth/2.0]);
	

	boundary = pyck.Cuboid(2,[0.0,Beam_Width/2.0,Beam_Depth/2.0],[Boundary_Length,Beam_Width+Beam_Width/2.0,Beam_Depth+Beam_Depth/2.0]);
	
	# Map the shapes and generate the pack
	pack.AddShape(boundary);
	pack.AddShape(beam);
	pack.Process();
	
	numParticles = pack.GetNumParticles();
	hincrement = 0.00001;
	h = h - hincrement;


# Create a new model from the pack
model = pyck.Model(pack);
dim = 2;
h =h + hincrement;
stateField = model.CreateIntField("State",1);
model.SetIntField(stateField,1,5);
model.SetIntField(stateField,2,2);
velocityField = model.CreateDoubleField("Velocity",3);
model.SetDoubleField(velocityField,1,[0.0,0.0,0.0]);
model.SetDoubleField(velocityField,2,[0.0,0.0,0.0]);
densityField = model.CreateDoubleField("Density",1);
model.SetDoubleField(densityField,1,material["density"]);
model.SetDoubleField(densityField,2,material["density"]);
print("Center = "+str(center[0])+str(center[1])+str(center[2]));
mass = ( material["density"]*(Beam_Length*Beam_Depth*Beam_Width)    ) / float(pack.GetNumParticlesByState(1));
pyck_utils.SetBrazilianTestParameters(model,domain,h,material);
model.SetParameter("Mass","%e" % (mass) );
#model.SetParameter("DTime","%e" % (1.0e-8));
model.SetParameter("MovingBoundaryShiftX","%e" % (0.0));
model.SetParameter("MovingBoundaryShiftY","%e" % (0.0));
model.SetParameter("MovingBoundaryShiftZ","%e" % (0.0));
model.SetParameter("MaxSteps","%d" % (1000));
model.SetParameter("CohnPt2","10.0");
model.SetParameter("GravityZ","-9.81");
model.SetParameter("IsDamping","true");
model.SetParameter("IsFlags","true");
model.SetParameter("IsElastoPlasticDamage","false");
model.SetParameter("IsDruckerPragerPlasticity","false");
model.SetParameter("BoundariesRampTime","500");
model.SetParameter("MaxSteps","1000");

pyck_utils.SetDamageParameters(model,mass,material);
# Create a file writer, in this case VTP according to spark format
writer = pyck.SparkWriter();

# Write the VTP file
model.Serialize("TestBeam_Bending_"+str(dim)+"_h_"+str(h)+"_"+str(numParticles)+".vtp",writer);
