import math

def AddGeometricParameters(model,L,r):
    smoothingLength = 1.3*r*2;
    Kappa = 2.0;
    KappaH = smoothingLength*Kappa;
    model.AddParameter("GridSizeX","%d" % math.floor(L[0]/KappaH));
    model.AddParameter("GridSizeY","%d" % math.floor(L[1]/KappaH));
    model.AddParameter("GridSizeZ","%d" % math.floor(L[2]/KappaH));
    model.AddParameter("Lx","%f" % L[0]);
    model.AddParameter("Ly","%f" % L[1]);
    model.AddParameter("Lz","%f" % L[2]);
    model.AddParameter("SmoothingLength","%f" % (1.3*r*2));
    model.AddParameter("InitialParticleSeparation","%f" % (r*2));
