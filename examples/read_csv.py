import pyck
import math
import csv

# ParticleType {Undefined=0, Liquid=1, Boundary=2, Floating=3, Moving=4, Solid =5};
# SmoothingKernelFunc {Undefined=0, Cubic kernel function=1, Gaussian
# kernel function=2, Quintic kernel function=3, Quadratic kernel
# function=4};

# Geometry (from the original Python script)
r = 0.053 / 2
domain = [2 * r + 4 * r / 4, 2 * r + 4 * r / 4, 0.0]
h = 0.0002069999999206506  # the one output at the end of the original Python script
smoothingKernelFunc = 1
appliedstressYY = -40000000.0
ramptime = 10000

# Reading the csv file
states = []
positions = []
ifile = open('pack.csv', "r")
reader = csv.reader(ifile)
state_col = 2 - 1  # column containing states
posX_col = 29 - 1  # column containing x
posY_col = 30 - 1  # column containing y
posZ_col = 31 - 1  # column containing z
kernelSum_col = 20 - 1  # column containing kernel summation
rownum = 0
numParticles = 0
dim = 2
kernelSum = 0.0
for row in reader:
    if(rownum != 0):
        test = 0
        colnum = 0
        for col in row:
            if(colnum == state_col and int(col) != 2):
                states.append(int(col))
                numParticles += 1
                test = 1
                count = 1
            if(colnum == kernelSum_col and test == 1 and count == 1):
                kernelSum += float(col)
            if(colnum == posX_col and test == 1):
                positions.append(float(col))
            if(colnum == posY_col and test == 1):
                positions.append(float(col))
            if(colnum == posZ_col and test == 1):
                positions.append(float(col))
                if(float(col) != 0.0):
                    dim = 3
            colnum += 1
    rownum += 1

ifile.close()
kernelSum = kernelSum / float(numParticles)

# Creation of the model
model = pyck.Model(positions, states, numParticles, dim)

writer = pyck.SparkWriter()
print("dx = " + str(h))
model.Serialize("read_csv_" + str(dim) + "D_R_" + str(r) + "_h_" +
                str(h) + "_" + str(numParticles) + "_relaxed.vtp", writer)
