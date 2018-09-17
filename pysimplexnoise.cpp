#include <Python.h>
#include "numpy/arrayobject.h"
#include "numpy/ufuncobject.h"
#include "numpy/npy_3kcompat.h"
#include "SimplexNoise.h"

static PyObject *simplexnoise1d_c(PyObject *self, PyObject *args) 
{
  PyObject* arg1;
  PyObject* x;
  int ndx;

  if (!PyArg_ParseTuple(args, "O", &arg1))
    return NULL;

  x = PyArray_FROM_OTF(arg1, NPY_FLOAT64, NPY_ARRAY_IN_ARRAY);
  
  ndx = PyArray_NDIM(x);

  npy_intp *sx = PyArray_DIMS(x);

  PyObject* out_array = PyArray_SimpleNew(ndx, sx, NPY_FLOAT64);
  npy_intp *so = PyArray_DIMS(out_array);

  double* data_x = (double*) PyArray_DATA(x);
  double* data_out = (double*) PyArray_DATA(out_array);

  for (int i = 0; i<sx[0]; i++) {
      data_out[i] = SimplexNoise::noise(data_x[i]);
  }
  return out_array;

}

static PyObject *simplexnoise2d_c(PyObject *self, PyObject *args) 
{
  PyObject* arg1;
  PyObject* arg2;
  PyObject* x;
  PyObject* y;
  int nd;

  if (!PyArg_ParseTuple(args, "OO", &arg1, &arg2))
    return NULL;

  x = PyArray_FROM_OTF(arg1, NPY_FLOAT64, NPY_ARRAY_IN_ARRAY);
  y = PyArray_FROM_OTF(arg2, NPY_FLOAT64, NPY_ARRAY_IN_ARRAY);
  
  if (!PyArray_SAMESHAPE(x, y))
    return NULL;

  nd = PyArray_NDIM(x);
  npy_intp *shape = PyArray_DIMS(x);
  npy_intp size = PyArray_SIZE(x);

  PyObject* out_array = PyArray_SimpleNew(nd, shape, NPY_FLOAT64);

  double* data_x = (double*) PyArray_DATA(x);
  double* data_y = (double*) PyArray_DATA(y);
  double* data_out = (double*) PyArray_DATA(out_array);

 for (int i = 0; i<size; i++)
 {
   data_out[i] = SimplexNoise::noise(data_x[i], data_y[i]);
 }
  return out_array;

}

static PyObject *simplexnoise3d_c(PyObject *self, PyObject *args) 
{
  PyObject* arg1;
  PyObject* arg2;
  PyObject* arg3;
  PyObject* x;
  PyObject* y;
  PyObject* z;
  int nd;

  if (!PyArg_ParseTuple(args, "OOO", &arg1, &arg2, &arg3))
    return NULL;

  x = PyArray_FROM_OTF(arg1, NPY_FLOAT64, NPY_ARRAY_IN_ARRAY);
  y = PyArray_FROM_OTF(arg2, NPY_FLOAT64, NPY_ARRAY_IN_ARRAY);
  z = PyArray_FROM_OTF(arg3, NPY_FLOAT64, NPY_ARRAY_IN_ARRAY);
  
  if (!(PyArray_SAMESHAPE(x, y) && PyArray_SAMESHAPE(y, z)))
    return NULL;

  nd = PyArray_NDIM(x);
  npy_intp *shape = PyArray_DIMS(x);
  npy_intp size = PyArray_SIZE(x);

  PyObject* out_array = PyArray_SimpleNew(nd, shape, NPY_FLOAT64);

  double* data_x = (double*) PyArray_DATA(x);
  double* data_y = (double*) PyArray_DATA(y);
  double* data_z = (double*) PyArray_DATA(z);
  double* data_out = (double*) PyArray_DATA(out_array);

 for (int i = 0; i<size; i++)
 {
   data_out[i] = SimplexNoise::noise(data_x[i], data_y[i], data_z[i]);
 }
  return out_array;

}

static PyObject *fractalnoise1d_c(PyObject *self, PyObject *args) 
{
  PyObject* arg1;
  PyObject* x;
  int n_octaves = 0;
  float frequency = 0;
  float amplitude = 0;
  float lacunarity = 0;
  float persistence = 0;
  int nd;

  if (!PyArg_ParseTuple(args, "Oiffff", &arg1, &n_octaves, &frequency, &amplitude, &lacunarity, &persistence))
    return NULL;

  x = PyArray_FROM_OTF(arg1, NPY_FLOAT64, NPY_ARRAY_IN_ARRAY);

  nd = PyArray_NDIM(x);
  npy_intp *shape = PyArray_DIMS(x);
  npy_intp size = PyArray_SIZE(x);

  PyObject* out_array = PyArray_SimpleNew(nd, shape, NPY_FLOAT64);

  double* data_x = (double*) PyArray_DATA(x);
  double* data_out = (double*) PyArray_DATA(out_array);

  SimplexNoise simplexNoise(frequency, amplitude, lacunarity, persistence);

  for (int i = 0; i<size; i++) {
      data_out[i] = simplexNoise.fractal(n_octaves, data_x[i]);
  }
  return out_array;

}


static PyObject *fractalnoise2d_c(PyObject *self, PyObject *args) 
{
  PyObject* arg1;
  PyObject* arg2;
  PyObject* x;
  PyObject* y;
  int n_octaves = 0;
  float frequency = 0;
  float amplitude = 0;
  float lacunarity = 0;
  float persistence = 0;
  int nd;

  if (!PyArg_ParseTuple(args, "OOiffff", &arg1, &arg2, &n_octaves, &frequency, &amplitude, &lacunarity, &persistence))
    return NULL;

  x = PyArray_FROM_OTF(arg1, NPY_FLOAT64, NPY_ARRAY_IN_ARRAY);
  y = PyArray_FROM_OTF(arg2, NPY_FLOAT64, NPY_ARRAY_IN_ARRAY);
  
  if (!PyArray_SAMESHAPE(x, y))
    return NULL;

  nd = PyArray_NDIM(x);
  npy_intp *shape = PyArray_DIMS(x);
  npy_intp size = PyArray_SIZE(x);

  PyObject* out_array = PyArray_SimpleNew(nd, shape, NPY_FLOAT64);

  double* data_x = (double*) PyArray_DATA(x);
  double* data_y = (double*) PyArray_DATA(y);
  double* data_out = (double*) PyArray_DATA(out_array);

  SimplexNoise simplexNoise(frequency, amplitude, lacunarity, persistence);

  for (int i = 0; i<size; i++) {
      data_out[i] = simplexNoise.fractal(n_octaves, data_x[i], data_y[i]);
  }
  return out_array;

}

static PyObject *fractalnoise3d_c(PyObject *self, PyObject *args) 
{
  PyObject* arg1;
  PyObject* arg2;
  PyObject* arg3;
  PyObject* x;
  PyObject* y;
  PyObject* z;
  int n_octaves = 0;
  float frequency = 0;
  float amplitude = 0;
  float lacunarity = 0;
  float persistence = 0;
  int nd;

  if (!PyArg_ParseTuple(args, "OOOiffff", &arg1, &arg2, &arg3, &n_octaves, &frequency, &amplitude, &lacunarity, &persistence))
    return NULL;

  x = PyArray_FROM_OTF(arg1, NPY_FLOAT64, NPY_ARRAY_IN_ARRAY);
  y = PyArray_FROM_OTF(arg2, NPY_FLOAT64, NPY_ARRAY_IN_ARRAY);
  z = PyArray_FROM_OTF(arg3, NPY_FLOAT64, NPY_ARRAY_IN_ARRAY);
  
  if (!(PyArray_SAMESHAPE(x, y) && PyArray_SAMESHAPE(y, z)))
    return NULL;

  nd = PyArray_NDIM(x);
  npy_intp *shape = PyArray_DIMS(x);
  npy_intp size = PyArray_SIZE(x);

  PyObject* out_array = PyArray_SimpleNew(nd, shape, NPY_FLOAT64);

  double* data_x = (double*) PyArray_DATA(x);
  double* data_y = (double*) PyArray_DATA(y);
  double* data_z = (double*) PyArray_DATA(z);
  double* data_out = (double*) PyArray_DATA(out_array);

  SimplexNoise simplexNoise(frequency, amplitude, lacunarity, persistence);

  for (int i = 0; i<size; i++) {
      data_out[i] = simplexNoise.fractal(n_octaves, data_x[i], data_y[i], data_z[i]);
  }
  return out_array;

}


static PyMethodDef pysimplexnoise_methods[] = {
        {
                "simplexnoise1d", simplexnoise1d_c, METH_VARARGS,
                "simplexnoise1d(x)\n1D simplex noise",
        },
        {
                "simplexnoise2d", simplexnoise2d_c, METH_VARARGS,
                "2D simplex noise",
        },
        {
                "simplexnoise3d", simplexnoise3d_c, METH_VARARGS,
                "3D simplex noise",
        },
        {
                "fractalnoise1d", fractalnoise1d_c, METH_VARARGS,
                "1D fractal noise",
        },
        {
                "fractalnoise2d", fractalnoise2d_c, METH_VARARGS,
                "2D fractal noise",
        },
        {
                "fractalnoise3d", fractalnoise3d_c, METH_VARARGS,
                "3D fractal noise",
        },
        {NULL, NULL, 0, NULL}
};


static struct PyModuleDef pysimplexnoise_definition = {
        PyModuleDef_HEAD_INIT,
        "pysimplexnoise",
        "One, two and three dimensional simplex and fractal noise.",
        -1,
        pysimplexnoise_methods
};


PyMODINIT_FUNC PyInit_pysimplexnoise(void) {
    Py_Initialize();
    import_array();
    return PyModule_Create(&pysimplexnoise_definition);  
}