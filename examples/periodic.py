import math
import pyck

L = [10.0, 10.0, 0.0]
r = 0.1

# Create a packer, see packers directory for options
cubic = pyck.Hcp2dPacker(L, r)

# Get the periodic extent of the pack
periodicExtent = cubic.GetPeriodicExtent()

# Create a structured pack
pack = pyck.StructuredPack(cubic)

# Create a cube which will pack every particle specified by the packer
cube = pyck.Cuboid(1, [-1, -1, -1], [11, 11, 11])

# Add and process
pack.AddShape(cube)
pack.Process()

# Create a new model from the pack
model = pyck.Model(pack)

# (Over)write the domain size
model.SetParameter("Lx", "%e" % periodicExtent[0])
model.SetParameter("Ly", "%e" % periodicExtent[1])
model.SetParameter("Lz", "%e" % periodicExtent[2])
model.SetParameter("GridSizeX", "%d" % math.floor(periodicExtent[0] / r))
model.SetParameter("GridSizeY", "%d" % math.floor(periodicExtent[1] / r))
model.SetParameter("GridSizeZ", "%d" % math.floor(periodicExtent[2] / r))

writer = pyck.SparkWriter()

# Write the VTP file
model.Serialize("periodic.vtp", writer)

print("Periodic domain size:")
print(periodicExtent)
