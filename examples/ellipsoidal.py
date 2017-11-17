import pyck
import math

domain = [1.0, 1.0, 0.0]
center = [0.5, 0.5, 0.0]
r = 0.2
h = 0.005
ratio_ellipse = 0.6
smoothingKernelFunc = 2
speedsound = 1.0
density = 1.0
shearmodulus = 1.0
bulkmodulus = 1.0
pack = pyck.EllipsoidalPacker(center, r, ratio_ellipse, h, 5)
pack.updateStates(center, r, h, r - 5 * h, ratio_ellipse, 2)
positions = pack.getPositions()
states = pack.getStates()
numParticles = pack.GetNumParticles()
dim = pack.getDim()
model = pyck.Model(positions, states, numParticles, dim)

stateField = model.CreateIntField("State", 1)
model.SetIntField(stateField, 5, 5)
model.SetIntField(stateField, 2, 2)

velocityField = model.CreateDoubleField("Velocity", 3)
model.SetDoubleField(velocityField, 5, [0.0, 0.0, 0.0])
model.SetDoubleField(velocityField, 2, [0.0, 0.0, 0.0])

densityField = model.CreateDoubleField("Density", 1)
model.SetDoubleField(densityField, 5, 1)
model.SetDoubleField(densityField, 2, 1)

model.SetParameter("Mass", "%f" % (
    density * ((math.pi * ratio_ellipse * r * r) / float(numParticles))))
model.SetParameter("DTime", "%f" % (0.00001))

writer = pyck.SparkWriter()

model.Serialize("Ellipsoidal_" + str(dim) + "D_R_" + str(r) + "_Ratio_" +
                str(ratio_ellipse) + "_" + str(numParticles) + ".vtp", writer)
