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

# Add simulation parameters to the VTP filename
# AddGeometricParameters computes geometric simulation parameters from pack parameters
pyck_utils.AddGeometricParameters(model,L,r);
# Arguments are AddParameter(Label,Value)
model.AddParameter("ParticlesPerCell","100");
model.AddParameter("MaxSteps","10000");
model.AddParameter("Mass","1");
model.AddParameter("Epsilon","0.5");
model.AddParameter("ViscEtq","test");
model.AddParameter("ViscAlpha","test");
model.AddParameter("ViscBeta","test");
model.AddParameter("DTime","test");
model.AddParameter("SpeedSound","test");
model.AddParameter("initialDensity","test");
model.AddParameter("SmoothingKernelFunc","test");
model.AddParameter("Dim","test");
model.AddParameter("AlgorithmSPH","test");
model.AddParameter("BoundaryUpdateStep","1");
model.AddParameter("limitBoundaryDensity","test");
model.AddParameter("IsExternalForce","test");
model.AddParameter("IsAverageVelocity","test");
model.AddParameter("IsVisc","test");
model.AddParameter("IsViscArtificial","test");
model.AddParameter("IsNoSlip","test");
model.AddParameter("IsSurfaceTension","test");
model.AddParameter("IsDeltaSPH","test");
model.AddParameter("delta","test");
model.AddParameter("GravityX","test");
model.AddParameter("GravityY","test");
model.AddParameter("GravityZ","test");
model.AddParameter("IsPeriodicBoundaryX","test");
model.AddParameter("IsPeriodicBoundaryY","test");
model.AddParameter("IsPeriodicBoundaryZ","test");
model.AddParameter("IsLaminarVisc","test");
model.AddParameter("IsSpsVisc","test");
model.AddParameter("EOS","2");
model.AddParameter("MonaghanB","test");
model.AddParameter("MonaghanGamma","test");
model.AddParameter("DensityFunction","test");
model.AddParameter("IsRepulsiveForceBC","test");
model.AddParameter("IsShepard","test");
model.AddParameter("ShepardStep","test");
model.AddParameter("Viscosity","test");
model.AddParameter("MovingBoundaryAmplitudeX","test");
model.AddParameter("MovingBoundaryAmplitudeY","test");
model.AddParameter("MovingBoundaryAmplitudeZ","test");
model.AddParameter("MovingBoundaryFrequencyX","test");
model.AddParameter("MovingBoundaryFrequencyY","test");
model.AddParameter("MovingBoundaryFrequencyZ","test");
model.AddParameter("MovingBoundaryPhaseX","test");
model.AddParameter("MovingBoundaryPhaseY","test");
model.AddParameter("MovingBoundaryPhaseZ","test");
model.AddParameter("MovingBoundaryShiftX","test");
model.AddParameter("MovingBoundaryShiftY","test");
model.AddParameter("MovingBoundaryShiftZ","test");
model.AddParameter("ShearModulus","test");
model.AddParameter("BulkModulus","test");
model.AddParameter("PoissonRatio","test");
model.AddParameter("YoungModulus","test");
model.AddParameter("deltaRmat","%f" % (1e-12 * 1.667e-05));
model.AddParameter("yieldTensileStrength","test");
model.AddParameter("KDamage","test");
model.AddParameter("MDamage","test");
model.AddParameter("IsSolids","test");
model.AddParameter("IsDamage","test");
model.AddParameter("IsPlasticityCorr","test");
model.AddParameter("IsTensileInstCorr","test");
model.AddParameter("IsFlags","test");
model.AddParameter("IsReverseMoving","test");
model.AddParameter("IsDensityBound","test");
model.AddParameter("IsAssociatedFlowRule","test");
model.AddParameter("IsDPbased","test");
model.AddParameter("IsDamping","test");
model.AddParameter("IsAlternateViscArtificial","test");
model.AddParameter("ViscAlphamin","test");
model.AddParameter("ViscAlphamax","test");
model.AddParameter("IsContactForce","test");
model.AddParameter("IsForcedBoundaries","test");
model.AddParameter("IsStressedBoundaries","test");
model.AddParameter("IsPlaneStress","test");
model.AddParameter("IsPlaneStrain","test");
model.AddParameter("IsPlaneStrain2PlaneStress","test");
model.AddParameter("IsElastoPlasticDamage","test");
model.AddParameter("IsDruckerPragerPlasticity","test");
model.AddParameter("DPcohesionSoftening","test");
model.AddParameter("DPYieldsurface","test");
model.AddParameter("IsDPApexCriterion","test");
model.AddParameter("IsDPTensileCrackingCriterion","test");
model.AddParameter("BoundaryNormalTolerance","test");
model.AddParameter("RankineCriticalStress","test");
model.AddParameter("StVenantCriticalStrain","test");
model.AddParameter("Cohesion","test");
model.AddParameter("FrictionAngle","test");
model.AddParameter("DilatancyAngle","test");
model.AddParameter("YieldShearStrength","test");
model.AddParameter("YieldCompressiveStrength","test");
model.AddParameter("YieldBiaxialCompressiveStrength","test");
model.AddParameter("CohnPt1","test");
model.AddParameter("CohnPt2","test");
model.AddParameter("PlastStrainPt1","test");
model.AddParameter("PlastStrainPt2","test");
model.AddParameter("EpsilonRmat","0.1");
model.AddParameter("Cg","test");
model.AddParameter("PlasticityModel","test");
model.AddParameter("DamageModel","test");
model.AddParameter("DampingCoef","0.02");
model.AddParameter("IsImposedDisplacement","test");
model.AddParameter("Impdx","test");
model.AddParameter("Impdy","test");
model.AddParameter("Impdz","test");
model.AddParameter("IsFloatingObjectRotation","test");
model.AddParameter("FloatingObjectAppliedFx","test");
model.AddParameter("FloatingObjectAppliedFy","test");
model.AddParameter("FloatingObjectAppliedFz","test");
model.AddParameter("FloatingObjectAppliedForceRampTime","test");
model.AddParameter("IsFloatingObjectMotionX","test");
model.AddParameter("IsFloatingObjectMotionY","test");
model.AddParameter("IsFloatingObjectMotionZ","test");
model.AddParameter("Movfx","test");
model.AddParameter("Movfy","test");
model.AddParameter("Movfz","test");
model.AddParameter("Movsxx","test");
model.AddParameter("Movsxy","test");
model.AddParameter("Movsyy","test");
model.AddParameter("Movsyz","test");
model.AddParameter("Movsxz","test");
model.AddParameter("Movszz","test");
model.AddParameter("BoundariesRampTime","test");
model.AddParameter("Cracksxx","test");
model.AddParameter("Cracksxy","test");
model.AddParameter("Cracksyy","test");
model.AddParameter("Cracksyz","test");
model.AddParameter("Cracksxz","test");
model.AddParameter("Crackszz","test");
model.AddParameter("CrackLength","test");
model.AddParameter("CrackThickness","test");
model.AddParameter("CrackX","test");
model.AddParameter("CrackY","test");
model.AddParameter("CrackZ","test");
model.AddParameter("ReverseMovingX","test");
model.AddParameter("ReverseMovingY","test");
model.AddParameter("ReverseMovingZ","test");
model.AddParameter("IsCrack","test");
model.AddParameter("IsFloatingObject","test");
model.AddParameter("IsBoundaryForce","test");
model.AddParameter("BoundaryForceMinLimit","test");
model.AddParameter("BoundaryForceMaxLimit","test");
model.AddParameter("IntegrationScheme","1");
model.AddParameter("VerletStep","test");

# Create a file writer, in this case VTP according to spark format
writer = pyck.SparkWriter();

# Write the VTP file
model.Serialize("pyck_test.vtp",writer);
