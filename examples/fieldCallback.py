import pyck

L = [10.0, 10.0, 0.0]
r = 0.1

cubic = pyck.CubicPacker(L, r)
pack = pyck.StructuredPack(cubic)

cube = pyck.Cuboid(1, [2, 2, -1], [6, 6, 1])
sphere = pyck.Sphere(2, [2, 2, 2], 5)

pack.AddShape(cube)
pack.AddShape(sphere)
pack.Process()

model = pyck.Model(pack)


# Create an IntField
stateField = model.CreateIntField("State", 1)

# The IntField may be set in the traditional way:
model.SetIntField(stateField, 1, 10)

# Or we can use a callback to determine the value of the
# field as a function of position
# Note that the callback must always take arguments for X Y and Z
# regardless of the dimensionality of the pack


def fieldCallback(x, y, z):
    return x

model.SetIntFieldCallback(stateField, 2, fieldCallback)

# The same can be done with DoubleFields
posField = model.CreateDoubleField("pos", 3)


def fieldCallback2(x, y, z):
    return [x, y, z]
# Here our field is 3D, so we return a 3D value

model.SetDoubleFieldCallback(posField, 2, fieldCallback2)

writer = pyck.SparkWriter()
model.Serialize("hello.vtp", writer)
