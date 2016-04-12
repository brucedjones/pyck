#!/usr/bin/python

from lxml import etree
import zlib
import struct
import base64
import math
import sys  
import os.path

class ParticleType:
    Undefined, Liquid, Boundary, Floating, Moving, Solid, Joint = range(7)
    name = ['Undefined','Liquid','Boundary','Floating','Moving','Solid','Joint']



def convert_input(particles_filename, parameters_filename, output_filename):
    parameters = read_sim_parameters(parameters_filename)
    particles = read_particles(particles_filename, parameters)
    generate_vtp(particles, parameters, output_filename)


def read_particles(filename, simparams ):
    root = etree.parse(filename).getroot()
     
    # read simulation parameters from particle file
    simparams.update({
        'KappaH': 0.04804, #float(root.find('KappaH').text),
        'Mass': 0.72140917, #float(root.find('TheCells/item/value/Cell/_Particles/Particle/Mass').text),
        'GridSizeX' : int(root.find('NX').text),
        'GridSizeY' : int(root.find('NY').text),
        'GridSizeZ' : int(root.find('NZ').text)
        #         'GridSizeX' : int(4),
        # 'GridSizeY' : int(4),
        # 'GridSizeZ' : int(4)
    })

    # Update Lx, Ly, and Lz to be an integer multiple of KappaH
    simparams['Lx'] = simparams['KappaH'] * simparams['GridSizeX']
    simparams['Ly'] = simparams['KappaH'] * simparams['GridSizeY']
    simparams['Lz'] = simparams['KappaH'] * simparams['GridSizeZ']

    # xc = open("data.txt", "r") #Read Joint file X and Y coordinate
    # Jxc = [ map(float,line.split('\t')) for line in xc ]
    # xc.close()
    fxc = open("packing.txt", "r") #Read Joint file X and Y coordinate
    cord = [ map(float,line.split(',')) for line in fxc ]
    fxc.close()

    # simparams['GridSizeX'] = int(6)
    # simparams['GridSizeY'] = int(6)
    # simparams['GridSizeZ'] = int(6)

    # simparams['movingShiftX'] = float(root.find('VxC').text)
    # simparams['movingShiftY'] = float(root.find('VzC').text)
    # simparams['movingShiftZ'] = float(root.find('VyC').text)
     
    particles = []
    cells = root.find('TheCells').getchildren()
     # Loop through cells
    for c in cells:
        parts = c.find('value/Cell/_Particles').getchildren()
        
        # For each particle in the current cell
        # for p in parts:
        #      current_particle = {}
            
            # current_particle['Position'] = [float(p.find('_Position/X').text)-simparams['MinX'], float(p.find('_Position/Y').text)-simparams['MinY'], float(p.find('_Position/Z').text) -simparams['MinZ']]
            # current_particle['Velocity'] = [float(p.find('_Velocity/X').text), float(p.find('_Velocity/Y').text), float(p.find('_Velocity/Z').text)]
            # current_particle['Density']  = float(p.find('_Density').text)
            # current_particle['JointNum'] = int(-1)
            # if (int(p.find('State').text) == 1):
            #     current_particle['State'] = ParticleType.Solid
            # if (int(p.find('State').text) == 2 and int(p.find('BoundaryType').text) == 0):
            #     current_particle['State'] = ParticleType.Boundary
            # if (int(p.find('State').text) == 2 and int(p.find('BoundaryType').text) == 1):
            #     current_particle['State'] = ParticleType.Moving
            # if (int(p.find('State').text) == 2 and int(p.find('BoundaryType').text) == 2):
            #     current_particle['State'] = ParticleType.Floating          
             # particles.append(current_particle)

    #print range(len(cord))
    for c in range(len(cord)):
        current_particle = {}
            
        current_particle['Position'] = [cord[c][0]-simparams['MinX'],cord[c][1]-simparams['MinY'],cord[c][2]-simparams['MinY']]
        current_particle['Velocity'] = [0.0, 0.0, 0.0]
        current_particle['Density']  = 2500.0
            #current_particle['JointNum'] = int(-1)
        if ((int(cord[c][3])) == 1):
            current_particle['State'] = ParticleType.Solid
        if ((int(cord[c][3])) == 2):
            current_particle['State'] = ParticleType.Moving 
        particles.append(current_particle)

    # cells = root.find('TheCells').getchildren()
    
    # # Loop through cells
    # for c in cells:
    #     parts = c.find('value/Cell/_Particles').getchildren()
        
    #     # For each particle in the current cell
    #     for p in parts:
    #         current_particle = {}
            
    #         current_particle['Position'] = [float(p.find('_Position/X').text)-simparams['MinX'], float(p.find('_Position/Y').text)-simparams['MinY'], float(p.find('_Position/Z').text) -simparams['MinZ']]
    #         current_particle['Velocity'] = [float(p.find('_Velocity/X').text), float(p.find('_Velocity/Y').text), float(p.find('_Velocity/Z').text)]
    #         current_particle['Density']  = float(p.find('_Density').text)
    #         current_particle['JointNum'] = int(-1)
    #         if (int(p.find('State').text) == 1):
    #             current_particle['State'] = ParticleType.Solid
    #         if (int(p.find('State').text) == 2 and int(p.find('BoundaryType').text) == 0):
    #             current_particle['State'] = ParticleType.Boundary
    #         if (int(p.find('State').text) == 2 and int(p.find('BoundaryType').text) == 1):
    #             current_particle['State'] = ParticleType.Moving
    #         if (int(p.find('State').text) == 2 and int(p.find('BoundaryType').text) == 2):
    #             current_particle['State'] = ParticleType.Floating          
    #         particles.append(current_particle)

    # for c in range(len(Jxc)):

    #     current_particle = {}       
    #     current_particle['Position'] = [Jxc[c][0]-simparams['MinX'],Jxc[c][1]-simparams['MinY'],Jxc[c][2]-simparams['MinZ']]
    #     current_particle['JointNum'] = int(Jxc[c][3])
    #     current_particle['Jcosine'] = [Jxc[c][4], Jxc[c][5], Jxc[c][6]]
    #     current_particle['Velocity'] = [0.0,0.0,0.0]
    #     current_particle['Density']  = 2500.0
    #     current_particle['State'] = ParticleType.Joint

    #     particles.append(current_particle)


    # remove unused parameters
    del simparams['MinX']
    del simparams['MinY']
    del simparams['MinZ']
    
    return particles


def read_sim_parameters(filename):
    root = etree.parse(filename).getroot()
    simparams = {
        'Lx'                        : float(root.find('MaxX').text)-float(root.find('MinX').text),
        'Ly'                        : float(root.find('MaxY').text)-float(root.find('MinY').text),
        'Lz'                        : float(root.find('MaxZ').text)-float(root.find('MinZ').text),
        'ParticlesPerCell'          : 800,
        'InitialDensity'            : float(root.find('PhaseInitialDensities/item/value/double').text),
        'SmoothingLength'           : 0.0241,#float(root.find('HashTableH').text),
        'EOS'                       : 1,
        'SpeedSound'                : float(root.find('PhaseEOSs/item/value/EOS/C').text),
        'SmoothingKernelFunc'       : int(root.find('SmoothingKernelFunc').text),
        'Dim'                       : int(root.find('Dim').text),
        'AlgorithmSPH'              : int(root.find('AlgorithmSPH').text),
        'IsExternalForce'           : (root.find('ExternalForce').text.lower() == 'true'),
        'IsAverageVelocity'         : (root.find('AverageVelocity').text.lower() == 'true'),
        'Epsilon'                   : float(root.find('Epsilon').text),
        'IsNoSlip'                  : (root.find('NoSlipBoundaries').text.lower() == 'true'),
        'Visc'                      : (root.find('Visc').text.lower() == 'true'),
        'IsViscArtificial'          : (root.find('ViscArtificial').text.lower() == 'true'),
        'ViscEtq'                   : float(root.find('ViscEtq').text),
        'ViscAlpha'                 : float(root.find('ViscAlpha').text),
        'ViscBeta'                  : float(root.find('ViscBeta').text),
        'DensityTolerance'          : 0.30,
        'DTime'                     : float(root.find('DTime').text),
        'CurrentStep'               : 0,
        'MaxSteps'                  : int(root.find('MaxSteps').text),
        'StepsPerFrame'             : int(root.find('SaveStep').text),
        'FluidPrefix'               : "fluid",
        'BoundaryPrefix'            : "boundary",
		'SolidPrefix'            	: "solid",
        'VisualizationExt'          : ".vtp",
        'VisualizationDir'          : "./output",
        'StepsPerSnapshot'          : int(root.find('SaveStep').text)*10,
        'CheckpointPrefix'          : "checkpoint",
        'CheckpointExt'             : ".vtp",
        'CheckpointDir'             : "./checkpoint",
        'OutputFormat'              : "binary",
		'InitialSeparation'         : 0.02,# float(root.find('HashTableH').text) / float(root.find('HScale').text),
		'FloatingObjectMomentOfInertia': "%.10f 0.0 0.0 0.0 %.10f 0.0 0.0 0.0 %.10f" % \
        (float(root.find('FtIx').text), 
         float(root.find('FtIy').text), 
         float(root.find('FtIz').text)),
		'FloatingObjectRotationMatrix' : "1.0 0.0 0.0 0.0 1.0 0.0 0.0 0.0 1.0",
		'FloatingObjectDisplacement'   : "0.0 0.0 0.0",
		'FloatingObjectAngularVelocity': "0.0 0.0 0.0",
		'FloatingObjectVelocity'       : "%.10f %.10f %.10f"%(float(root.find('VxC').text), float(root.find('VyC').text), float(root.find('VzC').text)),
		'FloatingObjectCenterOfMass'   : "%.10f %.10f %.10f"%(float(root.find('FtCenterX').text), float(root.find('FtCenterY').text), float(root.find('FtCenterZ').text)),
		'FloatingObjectMass'           : float(root.find('FtMass').text) ,
        'MinX'                      : float(root.find('MinX').text),
        'MinY'                      : float(root.find('MinY').text),
        'MinZ'                      : float(root.find('MinZ').text),
        'MovingBoundaryShiftX'      : float(root.find('VxC').text),
        'MovingBoundaryShiftY'      : float(root.find('VyC').text),
        'MovingBoundaryShiftZ'      : float(root.find('VzC').text)
    }
    return simparams






###############################################################
################### VTP Format Functions ######################
###############################################################

def xml_add_simulation_parameters(sim_params, xmlVTKRoot):
    xmlparams = etree.Element('SimulationParameters')
    for p in sim_params:
        e = etree.Element(p)
        if isinstance(sim_params[p], float):
            e.text = "%.17g" % sim_params[p]
        else:
            e.text = str(sim_params[p])
        # e.text = str(sim_params[p])
        xmlparams.append(e)
    xmlVTKRoot.append(xmlparams)

def xml_add_data_array(particleData, arrayName ,elemtype, xmlRoot):
    n = len(particleData)
    if isinstance(particleData[0][arrayName], list):
        dim = len(particleData[0][arrayName])
    else:
        dim = 1
    if elemtype=='int':
        t = 4
    else:
        t = 8

    arraySize = dim*n*t;
    compData  = pack_array(particleData, elemtype, arrayName)
    b64Data = base64.b64encode(compData)

    header = [1, arraySize, arraySize, len(compData)]
    b64Header = base64.b64encode(struct.pack('4i', *header))

    b64All = b64Header + b64Data

    xmlarray = etree.Element('DataArray')
    if elemtype=='int':
        xmlarray.set('type', 'Int32')
    else:
        xmlarray.set('type', 'Float64')
    xmlarray.set('NumberOfComponents', str(dim))
    xmlarray.set('format', 'binary')
    xmlarray.set('Name', arrayName)

    xmlarray.text = b64All

    xmlRoot.append(xmlarray);


def xml_add_particlesa(particleData, xmlVTKRoot):
    polydata = etree.Element('PolyData')

    piece = etree.Element('Piece')
    piece.set("NumberOfPoints", str(len(particleData)))
    piece.set("NumberOfVerts",  '0')
    piece.set("NumberOfLines",  '0')
    piece.set("NumberOfStrips", '0')
    piece.set("NumberOfPolys",  '0')

    # Position
    points = etree.Element('Points')
    xml_add_data_array( particleData, 'Position', 'double', points)
    piece.append(points)


    # Properties
    pointData = etree.Element('PointData')
     
    xml_add_data_array(particleData, 'Density',  'double', pointData)
    xml_add_data_array(particleData, 'Velocity', 'double', pointData)
    xml_add_data_array(particleData, 'State',    'int',    pointData)

    piece.append(pointData)
    polydata.append(piece)
    xmlVTKRoot.append(polydata)

def pack_array(particleData, elemtype, arrayName):
    if isinstance(particleData[0][arrayName], list):
        arrayValue = list(val for particle in particleData for val in particle[arrayName])
    else:
        arrayValue = list(particle[arrayName] for particle in particleData)
    if (elemtype == 'int'):
        arrayBytes = struct.pack('%si' % len(arrayValue), *arrayValue)
    else:
        arrayBytes = struct.pack('%sd' % len(arrayValue), *arrayValue)
    return zlib.compress(arrayBytes)

def generate_vtp(particles, parameters, filename_prefix):
    root = etree.Element('VTKFile')
    root.set("type", "PolyData")
    root.set("byte_order", "LittleEndian")
    root.set("compressor", "vtkZLibDataCompressor")
    xml_add_simulation_parameters(parameters, root)
    xml_add_particlesa(particles, root)
    filename = "%s_%d.vtp"%(filename_prefix, len(particles))
    root.getroottree().write(filename, pretty_print=True, encoding="UTF-8", xml_declaration=True)
    print "Generated %d particles in file: %s" % (len(particles), filename)

###############################################################
###############################################################
###############################################################


# Check if input filenames are provided
if len(sys.argv) < 3:
    print '-- Input Converter: C# XML to Spark VTP --'
    print 'Usage:'
    print '  %s particles_file parameters_file [output_file]' % sys.argv[0].replace('./', '')
    print ''
    exit(0)

particles_file  = sys.argv[1]
parameters_file = sys.argv[2]

if not os.path.isfile(particles_file):
    print "[Error] Particles file '%s' cannot be read." % particles_file
    exit(1)
if not os.path.isfile(parameters_file):
    print "[Error] Parameters file '%s' cannot be read." % parameters_file
    exit(1)


vtp_file = os.path.splitext(particles_file)[0]
if len(sys.argv) == 4:
    vtp_file = os.path.splitext(sys.argv[3])[0]

convert_input(particles_file, parameters_file, vtp_file)

import os
import sys    
import termios
import fcntl

def getch():
  fd = sys.stdin.fileno()

  oldterm = termios.tcgetattr(fd)
  newattr = termios.tcgetattr(fd)
  newattr[3] = newattr[3] & ~termios.ICANON & ~termios.ECHO
  termios.tcsetattr(fd, termios.TCSANOW, newattr)

  oldflags = fcntl.fcntl(fd, fcntl.F_GETFL)
  fcntl.fcntl(fd, fcntl.F_SETFL, oldflags | os.O_NONBLOCK)

  try:        
    while 1:            
      try:
        c = sys.stdin.read(1)
        break
      except IOError: pass
  finally:
    termios.tcsetattr(fd, termios.TCSAFLUSH, oldterm)
    fcntl.fcntl(fd, fcntl.F_SETFL, oldflags)
  return c