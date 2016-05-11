import sys
sys.path.insert(0, '~/Downloads/repositories/pyck/bin'); # Set this to the path where pyck is compiled
import pyck
import pyck_utils # Utility functions for creating simulation parameters
import math

# ParticleType {Undefined=0, Liquid=1, Boundary=2, Floating=3, Moving=4, Solid =5};

# Geometry 
r = 0.053/2;
h = 0.03;
length_platens = r/4;
height_platens = r/4;
penetration_in_sample = r/8;
domain = [2*r+4*r/4,2*r+4*r/4,0.0];
center = [domain[0]/2,domain[1]/2,0.0];

# Material Properties
smoothingKernelFunc = 2;
material = pyck_utils.dummy;
numParticlesModel = 0;


while (numParticlesModel < 50000):
	# Create a packer, see packers directory for options
	pack = pyck.CylindricalPacker(center, domain[0]*math.sqrt(2)/2, 1.0, h, 0);
	
	boundary_particles = pyck.Sphere(4,center,r+r/4+6*h);
	sphere = pyck.Sphere(1,center,r);
	
	upper_platen = pyck.Cuboid(2,[-length_platens/2 + center[0],r+center[1]-penetration_in_sample,-1],[length_platens/2 + center[0],r+center[1]+height_platens-penetration_in_sample,1]);
	lower_platen = pyck.Cuboid(3,[-length_platens/2 + center[0],-r+center[1]+penetration_in_sample,-1],[length_platens/2 + center[0],-r+center[1]-height_platens+penetration_in_sample,1]);
	
	# Map the shapes and generate the pack
	pack.AddShape(boundary_particles);
	pack.AddShape(upper_platen);
	pack.AddShape(lower_platen);
	pack.AddShape(sphere);
	pack.Process();
	
	numParticlesModel = pack.getNumParticlesByState(1)+pack.getNumParticlesByState(2)+pack.getNumParticlesByState(3);
	print(str(numParticlesModel));
	hincrement = 0.000001;
	h = h - hincrement;


numParticles = pack.getNumParticles();
dim = pack.getDim();
h = h+hincrement;
model = pyck.Model(pack);

stateField = model.CreateIntField("State",1);
model.SetIntField(stateField,1,5);
model.SetIntField(stateField,2,4);
model.SetIntField(stateField,3,4);
model.SetIntField(stateField,4,2);
velocityField = model.CreateDoubleField("Velocity",3);
model.SetDoubleField(velocityField,1,[0.0,0.0,0.0]);
model.SetDoubleField(velocityField,2,[0.0,0.0,0.0]);
model.SetDoubleField(velocityField,3,[0.0,0.0,0.0]);
model.SetDoubleField(velocityField,4,[0.0,0.0,0.0]);

densityField = model.CreateDoubleField("Density",1);
model.SetDoubleField(densityField,1,material["density"]);
model.SetDoubleField(densityField,2,material["density"]);
model.SetDoubleField(densityField,3,material["density"]);
model.SetDoubleField(densityField,4,material["density"]);

pressure_0 = 15000;
density_0 = material["density"];
volume_0 = (((math.pi*1.0*(r)*(r))    ) / float(pack.getNumParticlesByState(1)));
beta = 2*pressure_0 / density_0;
damping_coef = 0.5;
dt = math.pow(volume_0,1/dim) / math.sqrt(beta);

pyck_utils.SetParticlePackingParameters(model,domain,h,material,smoothingKernelFunc);
model.SetParameter("Mass","%e" % (material["density"]*volume_0) );
model.SetParameter("DTime","%e" % (dt));
model.SetParameter("InitialPressure","%e" % (pressure_0));
model.SetParameter("IsAverageVelocity","false");
# model.SetParameter("ToleranceNormal","%e" % (-1.0));
# model.SetParameter("ToleranceKineticEnergy","%e" % (0.00001));
model.SetParameter("DampingCoef","%e" % (damping_coef));

writer = pyck.SparkWriter();
print("Dimension = "+str(pack.getDim()));
print("DampingCoef = "+str(damping_coef));
print("DTime = "+str(dt));
model.Serialize("Brazilian_Test_"+str(dim)+"D_R_"+str(r)+"_h_"+str(h)+"_"+str(numParticles)+".vtp",writer);
