import sys
sys.path.insert(0, '/f/bruce/pyck/bin');
import pyck

#pack = pyck.EllipsoidalPacker([0.5,0.5,0.5], 0.2, 1, 0.02, 1);
pack = pyck.EllipsoidalPacker([0.5,0.5,0.5], 0.2, 1, 1, 0.02, 1,0.0001);
positions = pack.getPositions();
states = pack.getStates();
numParticles = pack.getNumParticles();
dim = pack.getDim();

model = pyck.Model(positions,states,numParticles,dim);

stateField = model.CreateIntField("State",1);
model.SetIntField(stateField,1,10);

model.SetParameter("TestParam","test");

writer = pyck.SparkWriter();

model.Serialize("pyck_test.vtp",writer);
