import math

# MATERIAL LIBRARY
# Gypsum
gypsum = {};
gypsum["speedsound"] = 1466.312;
gypsum["density"] = 1540;
gypsum["youngmodulus"] = 5.96*pow(10.0,9.0);
gypsum["poissonratio"] = 0.2;
gypsum["shearmodulus"] = 2.483333*pow(10.0,9.0);
gypsum["bulkmodulus"] = 3.31111*pow(10.0,9.0);
gypsum["yieldtensilestrength"] = 3.2*pow(10.0,6.0);
gypsum["kdamage"] = 5392570000000000000000000000000000000;
gypsum["mdamage"] = 9.0;
gypsum["cohesion"] = 5203840.0;
gypsum["cohnpt1"] = 2601920.0;
gypsum["cohnpt2"] = 0.0;
gypsum["plasstrpt1"] = 0.05;
gypsum["plasstrpt2"] = 0.1;
gypsum["frictionangle"] = 55.818340999999997;

# Chromite
chromite = {};
chromite["speedsound"] = 2886.5203966;
chromite["density"] = 2500;
chromite["youngmodulus"] = 50.0*pow(10.0,9.0);
chromite["poissonratio"] = 0.1;
chromite["shearmodulus"] = 22.73*pow(10.0,9.0);
chromite["bulkmodulus"] = 20.83*pow(10.0,9.0);
chromite["yieldtensilestrength"] = 16.52*pow(10.0,6.0);
chromite["kdamage"] = 1.59*pow(10.0,38.0);
chromite["mdamage"] = 9.5;
chromite["cohesion"] = 34.94*pow(10.0,6.0);
chromite["cohnpt1"] = 5.8233*pow(10.0,6.0);
chromite["cohnpt2"] = 0.3494*pow(10.0,6.0);
chromite["plasstrpt1"] = 0.1;
chromite["plasstrpt2"] = 0.5;
chromite["frictionangle"] = 51.48;

# Particle Packing Dummy Material
dummy = {};
dummy["speedsound"] = 1.0;
dummy["density"] = 1.0;
dummy["youngmodulus"] = 1.0;
dummy["poissonratio"] = 1.0;
dummy["shearmodulus"] = 1.0;
dummy["bulkmodulus"] = 1.0;
dummy["yieldtensilestrength"] = 1.0;
dummy["kdamage"] = 1.0;
dummy["mdamage"] = 1.0;
dummy["cohesion"] = 1.0;
dummy["cohnpt1"] = 1.0;
dummy["cohnpt2"] = 1.0;
dummy["plasstrpt1"] = 1.0;
dummy["plasstrpt2"] = 1.0;
dummy["frictionangle"] = 1.0;
# END OF MATERIAL LIBRARY


def SetGeometricParameters(model,L,r,smoothingKernelFunc=3):
    smoothingLength = 1.3*r;
    
    if smoothingKernelFunc != 3:
        Kappa = 2.0;
    else:
        Kappa = 3.0;

    KappaH = smoothingLength*Kappa;
    
    if L[0]==0:
            L[0] = KappaH;
    if L[1]==0:
            L[1] = KappaH;
    if L[2]==0:
            L[2] = KappaH;

    model.SetParameter("Lx","%e" % L[0]);
    model.SetParameter("Ly","%e" % L[1]);
    model.SetParameter("Lz","%e" % L[2]);
    model.SetParameter("GridSizeX","%d" % math.floor(L[0]/KappaH));
    model.SetParameter("GridSizeY","%d" % math.floor(L[1]/KappaH));
    model.SetParameter("GridSizeZ","%d" % math.floor(L[2]/KappaH));
    print("InitialSeparation = "+str(r));
    print("SmoothingLength = "+str(smoothingLength));
    print("KappaH = "+str(KappaH));
    print("Lx = "+str(L[0]));
    print("Ly = "+str(L[1]));
    print("Lz = "+str(L[2]));
    print("Gx = "+str(math.floor(L[0]/KappaH)));
    print("Gy = "+str(math.floor(L[1]/KappaH)));
    print("Gz = "+str(math.floor(L[2]/KappaH)));
    model.SetParameter("KappaH","%e" % KappaH);
    model.SetParameter("SmoothingLength","%e" % (1.3*r));
    model.SetParameter("InitialParticleSeparation","%e" % (r));

def SetGeometricPackingParameters(model,L,r,smoothingKernelFunc=3):
    smoothingLength = 1.3*r*2;
    
    if smoothingKernelFunc != 3:
        Kappa = 2.0;
    else:
        Kappa = 3.0;

    KappaH = smoothingLength*Kappa;
    
    if L[0]==0:
            L[0] = KappaH;
    if L[1]==0:
            L[1] = KappaH;
    if L[2]==0:
            L[2] = KappaH;

    model.SetParameter("Lx","%e" % L[0]);
    model.SetParameter("Ly","%e" % L[1]);
    model.SetParameter("Lz","%e" % L[2]);
    model.SetParameter("GridSizeX","%d" % math.floor(L[0]/KappaH));
    model.SetParameter("GridSizeY","%d" % math.floor(L[1]/KappaH));
    model.SetParameter("GridSizeZ","%d" % math.floor(L[2]/KappaH));
    print("InitialSeparation = "+str(r));
    print("PackingSmoothingLength = "+str(smoothingLength));
    print("SmoothingLength = "+str(1.3*r));
    print("KappaH = "+str(KappaH));
    print("Lx = "+str(L[0]));
    print("Ly = "+str(L[1]));
    print("Lz = "+str(L[2]));
    print("Gx = "+str(math.floor(L[0]/KappaH)));
    print("Gy = "+str(math.floor(L[1]/KappaH)));
    print("Gz = "+str(math.floor(L[2]/KappaH)));
    model.SetParameter("KappaH","%e" % KappaH);
    model.SetParameter("SmoothingLength","%e" % (1.3*r));
    model.SetParameter("InitialParticleSeparation","%e" % (r));    

def SetDamageParameters(model,mass,material):
    speedsound = material["speedsound"];
    density = material["density"];
    youngmodulus = material["youngmodulus"];
    poissonratio = material["poissonratio"];
    shearmodulus = material["shearmodulus"];
    bulkmodulus = material["bulkmodulus"];
    cohesion = material["cohesion"];
    frictionangle = (math.pi / 180.0)*material["frictionangle"];
    cg = 0.4*speedsound;
    tensilestrength =  (2.0 * cohesion * math.cos(frictionangle)) / (1 + math.sin(frictionangle)); 
    b = 0.25;
    m = 3.0* ((1.0/b) -1.0);
    t1 = ((m+1.0)*(m+2.0)) / (8.0 * (22.0/7.0) * cg*cg*cg);
    t2 = math.pow((m+3.0)/(m+4.0),m+4.0);
    temp = math.pow((bulkmodulus + (4.0/3.0)*shearmodulus)/tensilestrength,m) * (density)/(mass*t1*t2);
    rate = math.log10(math.pow(temp,(1/(m+3.0)))*(tensilestrength/bulkmodulus));
    A = tensilestrength / math.pow(10.0,rate);
    t3 = math.pow(bulkmodulus/A,(m+3));
    k = t1*t2*t3;
    print('k %15e' % k);
    print('m %15e' % m);
    model.SetParameter("KDamage","%e" % (k));
    model.SetParameter("MDamage","%e" % (m));

def SetDefaultParameters(model,L,r, material,smoothingKernelFunc=3):

    speedsound = material["speedsound"];
    density = material["density"];
    youngmodulus = material["youngmodulus"];
    poissonratio = material["poissonratio"];
    shearmodulus = material["shearmodulus"];
    bulkmodulus = material["bulkmodulus"];
    yieldtensilestrength = material["yieldtensilestrength"];
    kdamage = material["kdamage"];
    mdamage = material["mdamage"];
    cohesion = material["cohesion"];
    cohnpt1 = material["cohnpt1"];
    cohnpt2 = material["cohnpt2"];
    plasstrpt1 = material["plasstrpt1"];
    plasstrpt2 = material["plasstrpt2"];
    frictionangle = material["frictionangle"];

    model.SetParameter("SmoothingKernelFunc","%d" % smoothingKernelFunc);

    if L[2]==0:
            dim = 2;
    else:
            dim = 3;            

    SetGeometricParameters(model,L,r,smoothingKernelFunc);
    model.SetParameter("ParticlesPerCell","100");
    model.SetParameter("MaxSteps","10000");
    model.SetParameter("Mass","1");
    model.SetParameter("Epsilon","0.5");
    model.SetParameter("ViscEtq","0.1");
    model.SetParameter("ViscAlpha","1.0");
    model.SetParameter("ViscBeta","2.0");
    model.SetParameter("DTime","%e" % (0.4*((1.3*r)/speedsound)));
    model.SetParameter("SpeedSound","%e" % speedsound);
    model.SetParameter("InitialDensity","%e" % density);
    model.SetParameter("SmoothingKernelFunc","%d" % smoothingKernelFunc);
    model.SetParameter("Dim","%d" % dim);
    model.SetParameter("AlgorithmSPH","2");
    model.SetParameter("BoundaryUpdateStep","1");
    model.SetParameter("isBoundaryDensityLowLimit","false");
    model.SetParameter("IsExternalForce","false");
    model.SetParameter("IsAverageVelocity","true");
    model.SetParameter("IsVisc","false");
    model.SetParameter("IsViscArtificial","false");
    model.SetParameter("IsNoSlip","false");
    model.SetParameter("IsSurfaceTension","false");
    model.SetParameter("IsDeltaSPH","false");
    model.SetParameter("delta","0.1");
    model.SetParameter("GravityX","0.0");
    model.SetParameter("GravityY","0.0");
    model.SetParameter("GravityZ","0.0");
    model.SetParameter("IsPeriodicBoundaryX","false");
    model.SetParameter("IsPeriodicBoundaryY","false");
    model.SetParameter("IsPeriodicBoundaryZ","false");
    model.SetParameter("IsLaminarVisc","false");
    model.SetParameter("IsSpsVisc","false");
    model.SetParameter("EOS","2");
    model.SetParameter("MonaghanB","");
    model.SetParameter("MonaghanGamma","");
    model.SetParameter("DensityFunction","");
    model.SetParameter("IsRepulsiveForceBC","false");
    model.SetParameter("IsShepard","false");
    model.SetParameter("ShepardStep","");
    model.SetParameter("Viscosity","");
    model.SetParameter("MovingBoundaryAmplitudeX","");
    model.SetParameter("MovingBoundaryAmplitudeY","");
    model.SetParameter("MovingBoundaryAmplitudeZ","");
    model.SetParameter("MovingBoundaryFrequencyX","");
    model.SetParameter("MovingBoundaryFrequencyY","");
    model.SetParameter("MovingBoundaryFrequencyZ","");
    model.SetParameter("MovingBoundaryPhaseX","");
    model.SetParameter("MovingBoundaryPhaseY","");
    model.SetParameter("MovingBoundaryPhaseZ","");
    model.SetParameter("MovingBoundaryShiftX","");
    model.SetParameter("MovingBoundaryShiftY","");
    model.SetParameter("MovingBoundaryShiftZ","");
    model.SetParameter("ShearModulus","%e" % shearmodulus);
    model.SetParameter("BulkModulus","%e" % bulkmodulus);
    model.SetParameter("PoissonRatio","");
    model.SetParameter("YoungModulus","");
    model.SetParameter("deltaRmat","%e" % (1e-12 * 1.667e-05));
    model.SetParameter("yieldTensileStrength","");
    model.SetParameter("KDamage","");
    model.SetParameter("MDamage","");
    model.SetParameter("IsSolids","true");
    model.SetParameter("IsDamage","false");
    model.SetParameter("IsPlasticityCorr","false");
    model.SetParameter("IsTensileInstCorr","false");
    model.SetParameter("IsFlags","false");
    model.SetParameter("IsReverseMoving","false");
    model.SetParameter("IsDensityBound","false");
    model.SetParameter("IsAssociatedFlowRule","false");
    model.SetParameter("IsDPbased","false");
    model.SetParameter("IsDamping","true");
    model.SetParameter("IsAlternateViscArtificial","false");
    model.SetParameter("ViscAlphamin","1.0");
    model.SetParameter("ViscAlphamax","2.5");
    model.SetParameter("IsContactForce","false");
    model.SetParameter("IsForcedBoundaries","false");
    model.SetParameter("IsStressedBoundaries","false");
    model.SetParameter("IsPlaneStress","false");
    model.SetParameter("IsPlaneStrain","false");
    model.SetParameter("IsPlaneStrain2PlaneStress","false");
    model.SetParameter("IsElastoPlasticDamage","false");
    model.SetParameter("IsDruckerPragerPlasticity","false");
    model.SetParameter("DPcohesionSoftening","1");
    model.SetParameter("DPYieldsurface","1");
    model.SetParameter("IsDPApexCriterion","false");
    model.SetParameter("IsDPTensileCrackingCriterion","false");
    model.SetParameter("BoundaryNormalTolerance","0.3");
    model.SetParameter("RankineCriticalStress","");
    model.SetParameter("StVenantCriticalStrain","");
    model.SetParameter("Cohesion","");
    model.SetParameter("FrictionAngle","");
    model.SetParameter("DilatancyAngle","");
    model.SetParameter("YieldShearStrength","");
    model.SetParameter("YieldCompressiveStrength","");
    model.SetParameter("YieldBiaxialCompressiveStrength","");
    model.SetParameter("CohnPt1","");
    model.SetParameter("CohnPt2","");
    model.SetParameter("PlastStrainPt1","");
    model.SetParameter("PlastStrainPt2","");
    model.SetParameter("EpsilonRmat","0.1");
    model.SetParameter("FluidPrefix","fluid");
    model.SetParameter("BoundaryPrefix","boundary");
    model.SetParameter("SolidPrefix","solid");
    model.SetParameter("VisualizationExt",".vtp");
    model.SetParameter("VisualizationDir","./output");
    model.SetParameter("StepsPerSnapshot","1000");
    model.SetParameter("CurrentStep","0");
    model.SetParameter("StepsPerFrame","100");
    model.SetParameter("CheckpointPrefix","checkpoint");
    model.SetParameter("CheckpointExt",".vtp");
    model.SetParameter("CheckpointDir","./checkpoint");
    model.SetParameter("OutputFormat","binary");
    model.SetParameter("Cg","%e" % (0.4*speedsound));
    model.SetParameter("PlasticityModel","2");
    model.SetParameter("DamageModel","1");
    model.SetParameter("DampingCoef","0.05");
    model.SetParameter("IsImposedDisplacement","false");
    model.SetParameter("Impdx","");
    model.SetParameter("Impdy","");
    model.SetParameter("Impdz","");
    model.SetParameter("IsFloatingObjectRotation","false");
    model.SetParameter("FloatingObjectAppliedFx","false");
    model.SetParameter("FloatingObjectAppliedFy","false");
    model.SetParameter("FloatingObjectAppliedFz","false");
    model.SetParameter("FloatingObjectAppliedForceRampTime","1");
    model.SetParameter("IsFloatingObjectMotionX","false");
    model.SetParameter("IsFloatingObjectMotionY","false");
    model.SetParameter("IsFloatingObjectMotionZ","false");
    model.SetParameter("Movfx","");
    model.SetParameter("Movfy","");
    model.SetParameter("Movfz","");
    model.SetParameter("Movsxx","");
    model.SetParameter("Movsxy","");
    model.SetParameter("Movsyy","");
    model.SetParameter("Movsyz","");
    model.SetParameter("Movsxz","");
    model.SetParameter("Movszz","");
    model.SetParameter("BoundariesRampTime","1");
    model.SetParameter("Cracksxx","");
    model.SetParameter("Cracksxy","");
    model.SetParameter("Cracksyy","");
    model.SetParameter("Cracksyz","");
    model.SetParameter("Cracksxz","");
    model.SetParameter("Crackszz","");
    model.SetParameter("CrackLength","");
    model.SetParameter("CrackThickness","");
    model.SetParameter("CrackX","");
    model.SetParameter("CrackY","");
    model.SetParameter("CrackZ","");
    model.SetParameter("ReverseMovingX","false");
    model.SetParameter("ReverseMovingY","false");
    model.SetParameter("ReverseMovingZ","false");
    model.SetParameter("IsCrack","false");
    model.SetParameter("IsFloatingObject","false");
    model.SetParameter("IsBoundaryForce","false");
    model.SetParameter("BoundaryForceMinLimit","");
    model.SetParameter("BoundaryForceMaxLimit","");
    model.SetParameter("IntegrationScheme","1");
    model.SetParameter("VerletStep","40");
def SetParticlePackingParameters(model,L,r,material,smoothingKernelFunc=3):
    model.SetParameter("SmoothingKernelFunc","%d" % smoothingKernelFunc);
    speedsound = material["speedsound"];
    density = material["density"];
    youngmodulus = material["youngmodulus"];
    poissonratio = material["poissonratio"];
    shearmodulus = material["shearmodulus"];
    bulkmodulus = material["bulkmodulus"];
    if L[2]==0:
            dim = 2;
    else:
            dim = 3;            

    SetGeometricPackingParameters(model,L,r,smoothingKernelFunc);
    model.SetParameter("ParticlesPerCell","100");
    model.SetParameter("MaxSteps","10000");
    model.SetParameter("Mass","1");
    model.SetParameter("Epsilon","0.5");
    model.SetParameter("ViscEtq","0.1");
    model.SetParameter("ViscAlpha","1.0");
    model.SetParameter("ViscBeta","2.0");
    model.SetParameter("DTime","%e" % (0.4*((1.3*r)/speedsound)));
    model.SetParameter("SpeedSound","%e" % speedsound);
    model.SetParameter("InitialDensity","%e" % density);
    model.SetParameter("SmoothingKernelFunc","%d" % smoothingKernelFunc);
    model.SetParameter("Dim","%d" % dim);
    model.SetParameter("AlgorithmSPH","2");
    model.SetParameter("BoundaryUpdateStep","1");
    model.SetParameter("isBoundaryDensityLowLimit","false");
    model.SetParameter("IsExternalForce","false");
    model.SetParameter("IsAverageVelocity","true");
    model.SetParameter("IsVisc","false");
    model.SetParameter("IsViscArtificial","false");
    model.SetParameter("IsNoSlip","false");
    model.SetParameter("IsSurfaceTension","false");
    model.SetParameter("IsDeltaSPH","false");
    model.SetParameter("delta","0.1");
    model.SetParameter("GravityX","0.0");
    model.SetParameter("GravityY","0.0");
    model.SetParameter("GravityZ","0.0");
    model.SetParameter("IsPeriodicBoundaryX","false");
    model.SetParameter("IsPeriodicBoundaryY","false");
    model.SetParameter("IsPeriodicBoundaryZ","false");
    model.SetParameter("IsLaminarVisc","false");
    model.SetParameter("IsSpsVisc","false");
    model.SetParameter("EOS","2");
    model.SetParameter("MonaghanB","");
    model.SetParameter("MonaghanGamma","");
    model.SetParameter("DensityFunction","");
    model.SetParameter("IsRepulsiveForceBC","false");
    model.SetParameter("IsShepard","false");
    model.SetParameter("ShepardStep","");
    model.SetParameter("Viscosity","");
    model.SetParameter("MovingBoundaryAmplitudeX","");
    model.SetParameter("MovingBoundaryAmplitudeY","");
    model.SetParameter("MovingBoundaryAmplitudeZ","");
    model.SetParameter("MovingBoundaryFrequencyX","");
    model.SetParameter("MovingBoundaryFrequencyY","");
    model.SetParameter("MovingBoundaryFrequencyZ","");
    model.SetParameter("MovingBoundaryPhaseX","");
    model.SetParameter("MovingBoundaryPhaseY","");
    model.SetParameter("MovingBoundaryPhaseZ","");
    model.SetParameter("MovingBoundaryShiftX","");
    model.SetParameter("MovingBoundaryShiftY","");
    model.SetParameter("MovingBoundaryShiftZ","");
    model.SetParameter("ShearModulus","%e" % shearmodulus);
    model.SetParameter("BulkModulus","%e" % bulkmodulus);
    model.SetParameter("PoissonRatio","");
    model.SetParameter("YoungModulus","");
    model.SetParameter("deltaRmat","%e" % (1e-12 * 1.667e-05));
    model.SetParameter("yieldTensileStrength","");
    model.SetParameter("KDamage","");
    model.SetParameter("MDamage","");
    model.SetParameter("IsSolids","true");
    model.SetParameter("IsDamage","false");
    model.SetParameter("IsPlasticityCorr","false");
    model.SetParameter("IsTensileInstCorr","false");
    model.SetParameter("IsFlags","false");
    model.SetParameter("IsReverseMoving","false");
    model.SetParameter("IsDensityBound","false");
    model.SetParameter("IsAssociatedFlowRule","false");
    model.SetParameter("IsDPbased","false");
    model.SetParameter("IsDamping","true");
    model.SetParameter("IsAlternateViscArtificial","false");
    model.SetParameter("ViscAlphamin","1.0");
    model.SetParameter("ViscAlphamax","2.5");
    model.SetParameter("IsContactForce","false");
    model.SetParameter("IsForcedBoundaries","false");
    model.SetParameter("IsStressedBoundaries","false");
    model.SetParameter("IsPlaneStress","false");
    model.SetParameter("IsPlaneStrain","false");
    model.SetParameter("IsPlaneStrain2PlaneStress","false");
    model.SetParameter("IsElastoPlasticDamage","false");
    model.SetParameter("IsDruckerPragerPlasticity","false");
    model.SetParameter("DPcohesionSoftening","1");
    model.SetParameter("DPYieldsurface","1");
    model.SetParameter("IsDPApexCriterion","false");
    model.SetParameter("IsDPTensileCrackingCriterion","false");
    model.SetParameter("BoundaryNormalTolerance","0.3");
    model.SetParameter("RankineCriticalStress","");
    model.SetParameter("StVenantCriticalStrain","");
    model.SetParameter("Cohesion","");
    model.SetParameter("FrictionAngle","");
    model.SetParameter("DilatancyAngle","");
    model.SetParameter("YieldShearStrength","");
    model.SetParameter("YieldCompressiveStrength","");
    model.SetParameter("YieldBiaxialCompressiveStrength","");
    model.SetParameter("CohnPt1","");
    model.SetParameter("CohnPt2","");
    model.SetParameter("PlastStrainPt1","");
    model.SetParameter("PlastStrainPt2","");
    model.SetParameter("EpsilonRmat","0.1");
    model.SetParameter("FluidPrefix","fluid");
    model.SetParameter("BoundaryPrefix","boundary");
    model.SetParameter("SolidPrefix","solid");
    model.SetParameter("VisualizationExt",".vtp");
    model.SetParameter("VisualizationDir","./output");
    model.SetParameter("StepsPerSnapshot","1000");
    model.SetParameter("CurrentStep","0");
    model.SetParameter("StepsPerFrame","100");
    model.SetParameter("CheckpointPrefix","checkpoint");
    model.SetParameter("CheckpointExt",".vtp");
    model.SetParameter("CheckpointDir","./checkpoint");
    model.SetParameter("OutputFormat","binary");
    model.SetParameter("Cg","%e" % (0.4*speedsound));
    model.SetParameter("PlasticityModel","2");
    model.SetParameter("DamageModel","1");
    model.SetParameter("DampingCoef","0.5");
    model.SetParameter("InitialPressure","15000");
    model.SetParameter("ToleranceNormal","-1");
    model.SetParameter("ToleranceKineticEnergy","0.000001");
    model.SetParameter("IsImposedDisplacement","false");
    model.SetParameter("Impdx","");
    model.SetParameter("Impdy","");
    model.SetParameter("Impdz","");
    model.SetParameter("IsFloatingObjectRotation","false");
    model.SetParameter("FloatingObjectAppliedFx","false");
    model.SetParameter("FloatingObjectAppliedFy","false");
    model.SetParameter("FloatingObjectAppliedFz","false");
    model.SetParameter("FloatingObjectAppliedForceRampTime","1");
    model.SetParameter("IsFloatingObjectMotionX","false");
    model.SetParameter("IsFloatingObjectMotionY","false");
    model.SetParameter("IsFloatingObjectMotionZ","false");
    model.SetParameter("Movfx","");
    model.SetParameter("Movfy","");
    model.SetParameter("Movfz","");
    model.SetParameter("Movsxx","");
    model.SetParameter("Movsxy","");
    model.SetParameter("Movsyy","");
    model.SetParameter("Movsyz","");
    model.SetParameter("Movsxz","");
    model.SetParameter("Movszz","");
    model.SetParameter("BoundariesRampTime","1");
    model.SetParameter("Cracksxx","");
    model.SetParameter("Cracksxy","");
    model.SetParameter("Cracksyy","");
    model.SetParameter("Cracksyz","");
    model.SetParameter("Cracksxz","");
    model.SetParameter("Crackszz","");
    model.SetParameter("CrackLength","");
    model.SetParameter("CrackThickness","");
    model.SetParameter("CrackX","");
    model.SetParameter("CrackY","");
    model.SetParameter("CrackZ","");
    model.SetParameter("ReverseMovingX","false");
    model.SetParameter("ReverseMovingY","false");
    model.SetParameter("ReverseMovingZ","false");
    model.SetParameter("IsCrack","false");
    model.SetParameter("IsFloatingObject","false");
    model.SetParameter("IsBoundaryForce","false");
    model.SetParameter("BoundaryForceMinLimit","");
    model.SetParameter("BoundaryForceMaxLimit","");
    model.SetParameter("IntegrationScheme","1");
    model.SetParameter("VerletStep","40");
def SetBrazilianTestParameters(model,L,r,material,smoothingKernelFunc=3):
    model.SetParameter("SmoothingKernelFunc","%d" % smoothingKernelFunc);
    speedsound = material["speedsound"];
    density = material["density"];
    youngmodulus = material["youngmodulus"];
    poissonratio = material["poissonratio"];
    shearmodulus = material["shearmodulus"];
    bulkmodulus = material["bulkmodulus"];
    yieldtensilestrength = material["yieldtensilestrength"];
    kdamage = material["kdamage"];
    mdamage = material["mdamage"];
    cohesion = material["cohesion"];
    cohnpt1 = material["cohnpt1"];
    cohnpt2 = material["cohnpt2"];
    plasstrpt1 = material["plasstrpt1"];
    plasstrpt2 = material["plasstrpt2"];
    frictionangle = material["frictionangle"];
    if L[2]==0:
        dim = 2;
    else:
        dim = 3;            
                    
    SetGeometricParameters(model,L,r,smoothingKernelFunc);
    model.SetParameter("ParticlesPerCell","100");
    model.SetParameter("MaxSteps","40000");
    model.SetParameter("Mass","1");
    model.SetParameter("Epsilon","0.5");
    model.SetParameter("ViscEtq","0.1");
    model.SetParameter("ViscAlpha","1.0");
    model.SetParameter("ViscBeta","2.0");
    model.SetParameter("DTime","%e" % (0.4*((1.3*r)/speedsound)));
    model.SetParameter("SpeedSound","%e" % speedsound);
    model.SetParameter("InitialDensity","%e" % density);
    model.SetParameter("SmoothingKernelFunc","%d" % smoothingKernelFunc);
    model.SetParameter("Dim","%d" % dim);
    model.SetParameter("AlgorithmSPH","2");
    model.SetParameter("BoundaryUpdateStep","1");
    model.SetParameter("isBoundaryDensityLowLimit","false");
    model.SetParameter("IsExternalForce","false");
    model.SetParameter("IsAverageVelocity","true");
    model.SetParameter("IsVisc","false");
    model.SetParameter("Visc","false");
    model.SetParameter("IsViscArtificial","true");
    model.SetParameter("IsNoSlip","false");
    model.SetParameter("IsSurfaceTension","false");
    model.SetParameter("IsDeltaSPH","false");
    model.SetParameter("delta","0.1");
    model.SetParameter("GravityX","0.0");
    model.SetParameter("GravityY","0.0");
    model.SetParameter("GravityZ","0.0");
    model.SetParameter("IsPeriodicBoundaryX","false");
    model.SetParameter("IsPeriodicBoundaryY","false");
    model.SetParameter("IsPeriodicBoundaryZ","false");
    model.SetParameter("IsLaminarVisc","false");
    model.SetParameter("IsSpsVisc","false");
    model.SetParameter("EOS","1");
    model.SetParameter("MonaghanB","");
    model.SetParameter("MonaghanGamma","");
    model.SetParameter("DensityFunction","");
    model.SetParameter("IsRepulsiveForceBC","false");
    model.SetParameter("IsShepard","false");
    model.SetParameter("ShepardStep","");
    model.SetParameter("Viscosity","");
    model.SetParameter("MovingBoundaryAmplitudeX","");
    model.SetParameter("MovingBoundaryAmplitudeY","");
    model.SetParameter("MovingBoundaryAmplitudeZ","");
    model.SetParameter("MovingBoundaryFrequencyX","");
    model.SetParameter("MovingBoundaryFrequencyY","");
    model.SetParameter("MovingBoundaryFrequencyZ","");
    model.SetParameter("MovingBoundaryPhaseX","");
    model.SetParameter("MovingBoundaryPhaseY","");
    model.SetParameter("MovingBoundaryPhaseZ","");
    model.SetParameter("MovingBoundaryShiftX","");
    model.SetParameter("MovingBoundaryShiftY","");
    model.SetParameter("MovingBoundaryShiftZ","");
    model.SetParameter("ShearModulus","%e" % shearmodulus);
    model.SetParameter("BulkModulus","%e" % bulkmodulus);
    model.SetParameter("PoissonRatio","%e" % poissonratio);
    model.SetParameter("YoungModulus","%e" % youngmodulus);
    model.SetParameter("deltaRmat","%e" % (1e-12 * 1.667e-05));
    model.SetParameter("yieldTensileStrength","%e" % yieldtensilestrength);
    model.SetParameter("KDamage","%e" % kdamage);
    model.SetParameter("MDamage","%e" % mdamage);
    model.SetParameter("IsSolids","true");
    model.SetParameter("IsDamage","false");
    model.SetParameter("IsPlasticityCorr","false");
    model.SetParameter("IsTensileInstCorr","true");
    model.SetParameter("IsFlags","false");
    model.SetParameter("IsReverseMoving","true");
    model.SetParameter("IsDensityBound","false");
    model.SetParameter("IsAssociatedFlowRule","true");
    model.SetParameter("IsDPbased","true");
    model.SetParameter("IsDamping","false");
    model.SetParameter("IsAlternateViscArtificial","true");
    model.SetParameter("ViscAlphamin","1.0");
    model.SetParameter("ViscAlphamax","2.5");
    model.SetParameter("IsContactForce","false");
    model.SetParameter("IsForcedBoundaries","false");
    model.SetParameter("IsStressedBoundaries","false");
    model.SetParameter("IsPlaneStress","false");
    model.SetParameter("IsPlaneStrain","true");
    model.SetParameter("IsPlaneStrain2PlaneStress","true");
    model.SetParameter("IsElastoPlasticDamage","true");
    model.SetParameter("IsDruckerPragerPlasticity","true");
    model.SetParameter("DPcohesionSoftening","1");
    model.SetParameter("DPYieldsurface","1");
    model.SetParameter("IsDPApexCriterion","true");
    model.SetParameter("IsDPTensileCrackingCriterion","false");
    model.SetParameter("BoundaryNormalTolerance","0.02");
    model.SetParameter("DensityTolerance","0.3");
    model.SetParameter("RankineCriticalStress","");
    model.SetParameter("StVenantCriticalStrain","");
    model.SetParameter("Cohesion","%e" % cohesion);
    model.SetParameter("FrictionAngle","%e" % frictionangle);
    model.SetParameter("DilatancyAngle","%e" % (frictionangle/10.0));
    model.SetParameter("YieldShearStrength","");
    model.SetParameter("YieldCompressiveStrength","");
    model.SetParameter("YieldBiaxialCompressiveStrength","");
    model.SetParameter("CohnPt1","%e" % cohnpt1);
    model.SetParameter("CohnPt2","%e" % cohnpt2);
    model.SetParameter("PlastStrainPt1","%e" % plasstrpt1);
    model.SetParameter("PlastStrainPt2","%e" % plasstrpt2);
    model.SetParameter("EpsilonRmat","0.1");
    model.SetParameter("FluidPrefix","fluid");
    model.SetParameter("BoundaryPrefix","boundary");
    model.SetParameter("SolidPrefix","solid");
    model.SetParameter("VisualizationExt",".vtp");
    model.SetParameter("VisualizationDir","./output");
    model.SetParameter("StepsPerSnapshot","1000");
    model.SetParameter("CurrentStep","0");
    model.SetParameter("StepsPerFrame","100");
    model.SetParameter("CheckpointPrefix","checkpoint");
    model.SetParameter("CheckpointExt",".vtp");
    model.SetParameter("CheckpointDir","./checkpoint");
    model.SetParameter("OutputFormat","binary");
    model.SetParameter("Cg","%e" % (0.4*speedsound));
    model.SetParameter("PlasticityModel","2");
    model.SetParameter("DamageModel","1");
    model.SetParameter("DampingCoef","0.02");
    model.SetParameter("IsImposedDisplacement","false");
    model.SetParameter("Impdx","");
    model.SetParameter("Impdy","");
    model.SetParameter("Impdz","");
    model.SetParameter("IsFloatingObjectRotation","true");
    model.SetParameter("FloatingObjectAppliedFx","0");
    model.SetParameter("FloatingObjectAppliedFy","0");
    model.SetParameter("FloatingObjectAppliedFz","0");
    model.SetParameter("FloatingObjectVelocity","0.0000000000 0.0000000000 0.0000000000");
    model.SetParameter("FloatingObjectCenterOfMass","0.0000000000 0.0000000000 0.0000000000");
    model.SetParameter("FloatingObjectAppliedForceRampTime","1");
    model.SetParameter("FloatingObjectRotationMatrix","1.0 0.0 0.0 0.0 1.0 0.0 0.0 0.0 1.0");
    model.SetParameter("FloatingObjectMomentOfInertia","0.0000000000 0.0 0.0 0.0 0.0000000000 0.0 0.0 0.0 0.0000000000");
    model.SetParameter("FloatingObjectRotationMatrix","0.0 0.0 0.0");
    model.SetParameter("FloatingObjectAngularVelocity","0.0 0.0 0.0");
    model.SetParameter("IsFloatingObjectMotionX","true");
    model.SetParameter("IsFloatingObjectMotionY","true");
    model.SetParameter("IsFloatingObjectMotionZ","true");
    model.SetParameter("FloatingObjectMass","0");
    model.SetParameter("Movfx","0");
    model.SetParameter("Movfy","0");
    model.SetParameter("Movfz","0");
    model.SetParameter("Movsxx","0");
    model.SetParameter("Movsxy","0");
    model.SetParameter("Movsyy","0");
    model.SetParameter("Movsyz","0");
    model.SetParameter("Movsxz","0");
    model.SetParameter("Movszz","0");
    model.SetParameter("BoundariesRampTime","0");
    model.SetParameter("Cracksxx","0");
    model.SetParameter("Cracksxy","0");
    model.SetParameter("Cracksyy","0");
    model.SetParameter("Cracksyz","0");
    model.SetParameter("Cracksxz","0");
    model.SetParameter("Crackszz","0");
    model.SetParameter("CrackLength","0.2");
    model.SetParameter("CrackThickness","0.01");
    model.SetParameter("CrackX","2.6");
    model.SetParameter("CrackY","2.6");
    model.SetParameter("CrackZ","2.6");
    model.SetParameter("ReverseMovingX","false");
    model.SetParameter("ReverseMovingY","true");
    model.SetParameter("ReverseMovingZ","false");
    model.SetParameter("IsCrack","false");
    model.SetParameter("IsFloatingObject","false");
    model.SetParameter("IsBoundaryForce","false");
    model.SetParameter("BoundaryForceMinLimit","");
    model.SetParameter("BoundaryForceMaxLimit","");
    model.SetParameter("IntegrationScheme","1");
    model.SetParameter("VerletStep","40");
