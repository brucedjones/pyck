import sys
sys.path.insert(0, '/f/bruce/pyck/bin'); # Set this to the path where pyck is compiled
import pyck
import pyck_utils # Utility functions for creating simulation parameters

# Create a packer, see packers directory for options
cubic = pyck.CubicPacker([10.0,10.0,10.0],0.1);
pack = pyck.Pack(cubic); # do not create the cubic packer in this function call as it will be destroyed, blame SWIG developers

# Create some shapes, see shapes directory for options and reference
# First argument is always a tag for these particles
# Mapping operations are applied sequentially
cube = pyck.Cuboid(1,[2,2,2],[6,6,6]);
sphere = pyck.Sphere(2,[2,2,2],5);

# Map the shapes and generate the pack
pack.AddShape(cube); # As with creating the cubic packer, do not create the shapes within the function call here
pack.AddShape(sphere);
pack.Process();

# Create a new model from the pack
model = pyck.Model(pack);

# Create a new field of n-dimensional integers
# Arguments are CreateIntField(label,dimensions)
# label - label for this field in the vtp file
# dimensions - dimensionality of this field, doesnt have to correspond to model dimensions
# Create field of doubles in the same way with CreateDoubleField
stateField = model.CreateIntField("State",1);

# Arguments are SetIntField(field,tag,value(s))
# field - returned from CreateIntField
# tag - tag applied to particles during shape Mapping
# value(s) - singular value or array of values [v1, v2,...vn] to set of particles with a matching tag
model.SetIntField(stateField,1,10);
model.SetIntField(stateField,2,20);

# Set simulation parameters to the VTP filename
# SetGeometricParameters computes geometric simulation parameters from pack parameters
pyck_utils.SetGeometricParameters(model,L,r);
# Arguments are SetParameter(Label,Value)
model.SetParameter("ParticlesPerCell","100");
model.SetParameter("MaxSteps","10000");
model.SetParameter("Mass","1");
model.SetParameter("Epsilon","0.5");
model.SetParameter("ViscEtq","test");
model.SetParameter("ViscAlpha","test");
model.SetParameter("ViscBeta","test");
model.SetParameter("DTime","test");
model.SetParameter("SpeedSound","test");
model.SetParameter("initialDensity","test");
model.SetParameter("SmoothingKernelFunc","test");
model.SetParameter("Dim","test");
model.SetParameter("AlgorithmSPH","test");
model.SetParameter("BoundaryUpdateStep","1");
model.SetParameter("limitBoundaryDensity","test");
model.SetParameter("IsExternalForce","test");
model.SetParameter("IsAverageVelocity","test");
model.SetParameter("IsVisc","test");
model.SetParameter("IsViscArtificial","test");
model.SetParameter("IsNoSlip","test");
model.SetParameter("IsSurfaceTension","test");
model.SetParameter("IsDeltaSPH","test");
model.SetParameter("delta","test");
model.SetParameter("GravityX","test");
model.SetParameter("GravityY","test");
model.SetParameter("GravityZ","test");
model.SetParameter("IsPeriodicBoundaryX","test");
model.SetParameter("IsPeriodicBoundaryY","test");
model.SetParameter("IsPeriodicBoundaryZ","test");
model.SetParameter("IsLaminarVisc","test");
model.SetParameter("IsSpsVisc","test");
model.SetParameter("EOS","2");
model.SetParameter("MonaghanB","test");
model.SetParameter("MonaghanGamma","test");
model.SetParameter("DensityFunction","test");
model.SetParameter("IsRepulsiveForceBC","test");
model.SetParameter("IsShepard","test");
model.SetParameter("ShepardStep","test");
model.SetParameter("Viscosity","test");
model.SetParameter("MovingBoundaryAmplitudeX","test");
model.SetParameter("MovingBoundaryAmplitudeY","test");
model.SetParameter("MovingBoundaryAmplitudeZ","test");
model.SetParameter("MovingBoundaryFrequencyX","test");
model.SetParameter("MovingBoundaryFrequencyY","test");
model.SetParameter("MovingBoundaryFrequencyZ","test");
model.SetParameter("MovingBoundaryPhaseX","test");
model.SetParameter("MovingBoundaryPhaseY","test");
model.SetParameter("MovingBoundaryPhaseZ","test");
model.SetParameter("MovingBoundaryShiftX","test");
model.SetParameter("MovingBoundaryShiftY","test");
model.SetParameter("MovingBoundaryShiftZ","test");
model.SetParameter("ShearModulus","test");
model.SetParameter("BulkModulus","test");
model.SetParameter("PoissonRatio","test");
model.SetParameter("YoungModulus","test");
model.SetParameter("deltaRmat","%f" % (1e-12 * 1.667e-05));
model.SetParameter("yieldTensileStrength","test");
model.SetParameter("KDamage","test");
model.SetParameter("MDamage","test");
model.SetParameter("IsSolids","test");
model.SetParameter("IsDamage","test");
model.SetParameter("IsPlasticityCorr","test");
model.SetParameter("IsTensileInstCorr","test");
model.SetParameter("IsFlags","test");
model.SetParameter("IsReverseMoving","test");
model.SetParameter("IsDensityBound","test");
model.SetParameter("IsAssociatedFlowRule","test");
model.SetParameter("IsDPbased","test");
model.SetParameter("IsDamping","test");
model.SetParameter("IsAlternateViscArtificial","test");
model.SetParameter("ViscAlphamin","test");
model.SetParameter("ViscAlphamax","test");
model.SetParameter("IsContactForce","test");
model.SetParameter("IsForcedBoundaries","test");
model.SetParameter("IsStressedBoundaries","test");
model.SetParameter("IsPlaneStress","test");
model.SetParameter("IsPlaneStrain","test");
model.SetParameter("IsPlaneStrain2PlaneStress","test");
model.SetParameter("IsElastoPlasticDamage","test");
model.SetParameter("IsDruckerPragerPlasticity","test");
model.SetParameter("DPcohesionSoftening","test");
model.SetParameter("DPYieldsurface","test");
model.SetParameter("IsDPApexCriterion","test");
model.SetParameter("IsDPTensileCrackingCriterion","test");
model.SetParameter("BoundaryNormalTolerance","test");
model.SetParameter("RankineCriticalStress","test");
model.SetParameter("StVenantCriticalStrain","test");
model.SetParameter("Cohesion","test");
model.SetParameter("FrictionAngle","test");
model.SetParameter("DilatancyAngle","test");
model.SetParameter("YieldShearStrength","test");
model.SetParameter("YieldCompressiveStrength","test");
model.SetParameter("YieldBiaxialCompressiveStrength","test");
model.SetParameter("CohnPt1","test");
model.SetParameter("CohnPt2","test");
model.SetParameter("PlastStrainPt1","test");
model.SetParameter("PlastStrainPt2","test");
model.SetParameter("EpsilonRmat","0.1");
model.SetParameter("Cg","test");
model.SetParameter("PlasticityModel","test");
model.SetParameter("DamageModel","test");
model.SetParameter("DampingCoef","0.02");
model.SetParameter("IsImposedDisplacement","test");
model.SetParameter("Impdx","test");
model.SetParameter("Impdy","test");
model.SetParameter("Impdz","test");
model.SetParameter("IsFloatingObjectRotation","test");
model.SetParameter("FloatingObjectAppliedFx","test");
model.SetParameter("FloatingObjectAppliedFy","test");
model.SetParameter("FloatingObjectAppliedFz","test");
model.SetParameter("FloatingObjectAppliedForceRampTime","test");
model.SetParameter("IsFloatingObjectMotionX","test");
model.SetParameter("IsFloatingObjectMotionY","test");
model.SetParameter("IsFloatingObjectMotionZ","test");
model.SetParameter("Movfx","test");
model.SetParameter("Movfy","test");
model.SetParameter("Movfz","test");
model.SetParameter("Movsxx","test");
model.SetParameter("Movsxy","test");
model.SetParameter("Movsyy","test");
model.SetParameter("Movsyz","test");
model.SetParameter("Movsxz","test");
model.SetParameter("Movszz","test");
model.SetParameter("BoundariesRampTime","test");
model.SetParameter("Cracksxx","test");
model.SetParameter("Cracksxy","test");
model.SetParameter("Cracksyy","test");
model.SetParameter("Cracksyz","test");
model.SetParameter("Cracksxz","test");
model.SetParameter("Crackszz","test");
model.SetParameter("CrackLength","test");
model.SetParameter("CrackThickness","test");
model.SetParameter("CrackX","test");
model.SetParameter("CrackY","test");
model.SetParameter("CrackZ","test");
model.SetParameter("ReverseMovingX","test");
model.SetParameter("ReverseMovingY","test");
model.SetParameter("ReverseMovingZ","test");
model.SetParameter("IsCrack","test");
model.SetParameter("IsFloatingObject","test");
model.SetParameter("IsBoundaryForce","test");
model.SetParameter("BoundaryForceMinLimit","test");
model.SetParameter("BoundaryForceMaxLimit","test");
model.SetParameter("IntegrationScheme","1");
model.SetParameter("VerletStep","40");

# Create a file writer, in this case VTP according to spark format
writer = pyck.SparkWriter();

# Write the VTP file
model.Serialize("pyck_test.vtp",writer);
