import pyck


domain = [1.0, 1.0, 1.0]
h = 0.01
smoothingKernelFunc = 2
speedsound = 1
density = 1
shearmodulus = 1
bulkmodulus = 1
material = pyck_utils.chromite
# Create a packer, see packers directory for options
Hcp = pyck.HcpPacker(domain, h)
pack = pyck.StructuredPack(Hcp)


def pythonShape(x, y, z):
    dx = x - 1.0
    dy = y - 1.0
    dz = z - 1.0
    r = 0.3
    if(dx * dx + dy * dy + dz * dz < r * r):
        return True
    return False

pyShape = pyck.PyShape(1, [0.7, 0.7, 0.7], [1.0, 1.0, 1.0], pythonShape)

cube = pyck.Cuboid(2, [0.2, 0.2, 0.2], [0.6, 0.6, 0.6])

# Map the shapes and generate the pack
pack.AddShape(pyShape)
pack.AddShape(cube)
pack.Process()

# Create a new model from the pack
model = pyck.Model(pack)

# Create a new field of n-dimensional integers
# Arguments are CreateIntField(label,dimensions)
# label - label for this field in the vtp file
# dimensions - dimensionality of this field, doesnt have to correspond to model dimensions
# Create field of doubles in the same way with CreateDoubleField
stateField = model.CreateIntField("State", 1)

# Arguments are SetIntField(field,tag,value(s))
# field - returned from CreateIntField
# tag - tag applied to particles during shape Mapping
# value(s) - singular value or array of values [v1, v2,...vn] to set of
# particles with a matching tag
model.SetIntField(stateField, 1, 10)
model.SetIntField(stateField, 2, 20)

# Overwrite some parameters
# Arguments are SetParameter(Label,Value)
model.SetParameter("MaxSteps", "100")
model.SetParameter("Mass", "0.5")

# Or use a python dictionary to overwrite parameters
parameters = pyck.Parameters({'ViscAlpha': '0.1', 'ViscBeta': '0.2'})
model.SetParameters(parameters)

# Create a file writer, in this case VTP according to spark format
writer = pyck.SparkWriter()

# Write the VTP file
model.Serialize("pyShape.vtp", writer)
