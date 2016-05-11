%module pyck

%include doc.i

%typemap(in) (double *xyz) {
 int i;
 if (!PySequence_Check($input)) {
   PyErr_SetString(PyExc_ValueError,"Expected a sequence");
   return NULL;
 }

 $1 = (double *) malloc(3*sizeof(double));

 for (i = 0; i < 3; i++) {
   PyObject *s = PyList_GetItem($input,i);
   $1[i] = (double) PyFloat_AsDouble(s);
 }
}

%typemap(freearg) (double *xyz) {
  if ($1) free($1);
}

%typemap(typecheck) (double *xyz) {
   $1 = PySequence_Check($input) ? 1 : 0;
}

%typemap(in) (double *dprop) {
 int i;
 if (!PySequence_Check($input)) {
   $1 = (double *) malloc(sizeof(double));
   PyObject *s = $input;
   $1[0] = (double) PyFloat_AsDouble(s);
 } else {

  long len = PySequence_Length($input);

  $1 = (double *) malloc(len*sizeof(double));

  for (i = 0; i < len; i++) {
    PyObject *s = PyList_GetItem($input,i);
    $1[i] = (double) PyFloat_AsDouble(s);
  }
 }
}

%typemap(freearg) (double *dprop) {
  if ($1) free($1);
}

%typemap(typecheck) (double *dprop) {
   $1 = PySequence_Check($input) ? 1 : 0;
}

%typemap(in) (int *iprop) {
 int i;
 if (!PySequence_Check($input)) {
   $1 = (int *) malloc(sizeof(int));
   PyObject *s = $input;
   $1[0] = (int) PyFloat_AsDouble(s);
 } else {

  long len = PySequence_Length($input);

  $1 = (int *) malloc(len*sizeof(int));

  for (i = 0; i < len; i++) {
    PyObject *s = PyList_GetItem($input,i);
    $1[i] = (int) PyInt_AsLong(s);
  }
 }
}

%typemap(freearg) (int *iprop) {
  if ($1) free($1);
}

%typemap(typecheck) (int *iprop) {
   $1 = PySequence_Check($input) ? 1 : 0;
}

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

%include model.i

// Add an interface file for each new writer, see existing writers for reference
%include writers/sparkWriter.i
