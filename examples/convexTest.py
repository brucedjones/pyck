import pyck

L = [1, 1, 0]
r = 0.002
dim = 2
smoothingKernelFunc = 1

cubic = pyck.Hcp2dPacker(L, r)
# do not create the cubic packer in this function call as it will be
# destroyed, blame SWIG developers
pack = pyck.StructuredPack(cubic)


cube = pyck.Cuboid(1, [0, 0, 0], [1, 1, 0])
convexh = pyck.ConvexHull2D(2, [[0.1, 0.2, 0], [0.8, 0.2, 0], [0.3, 0.8, 0]])

pack.AddShape(cube)
pack.AddShape(convexh)

# Map the shapes and generate the pack
pack.Process()

# Create a new model from the pack
model = pyck.Model(pack)

# Create a new field of n-dimensional integers
# Arguments are CreateIntField(label,dimensions)
# label - label for this field in the vtp file
# dimensions - dimensionality of this field, doesnt have to correspond to model dimensions
# Create field of doubles in the same way with CreateDoubleField
stateField = model.CreateIntField("State", 1)
# for i in range(1, 17):
# 	model.SetIntField(stateField,i,5);

model.SetIntField(stateField, 1, 0)
model.SetIntField(stateField, 2, 1)


writer = pyck.SparkWriter()
numParticles = pack.GetNumParticles()
# Write the VTP file
# model.Serialize("HFInsituCubic.vtp",writer);
model.Serialize("ConvexHull_Test_" + str(numParticles) + ".vtp", writer)
