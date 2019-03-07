%module pyck

%include doc.i

%typemap(in) PyObject *PyFunc {
  if (!PyCallable_Check($input)) {
      PyErr_SetString(PyExc_TypeError, "Need a callable object!");
      return NULL;
  }
  $1 = $input;
}

%include "std_vector.i"
%template(vectord) std::vector<double>;
%template(vectordd) std::vector< std::vector<double> >;
%template(vectori) std::vector<int>;
%template(vectorii) std::vector< std::vector<int> >;

%include pack/cylindricalPacker.i
%include pack/ellipsoidalPacker.i
%include pack/structuredPack.i

// Add an interface file for each new packer, see existing packers for reference
%include pack/packers/cubicPacker.i
%include pack/packers/fccPacker.i
%include pack/packers/bccPacker.i
%include pack/packers/hcpPacker.i
%include pack/packers/hcp2dPacker.i

// Add an interface file for each new shape, see existing shapes for reference
%include shapes/cuboid.i
%include shapes/cylinder.i
%include shapes/sphere.i
%include shapes/triprism.i
%include shapes/stlShape.i
%include shapes/pyShape.i
%include shapes/compositeShape.i
%include shapes/convexhull2D.i

%include model.i

// Add an interface file for each new writer, see existing writers for reference
%include writers/sparkWriter.i
%include writers/asciiWriter.i
%include writers/verditeWriter.i
%include writers/binaryWriter.i
