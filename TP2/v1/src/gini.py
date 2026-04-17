import ctypes
import os

base_dir = os.path.dirname(__file__)
lib_path = os.path.join(base_dir, "../c/libgini.so")

libgini = ctypes.CDLL(lib_path)

libgini.procesar_gini.argtypes = [ctypes.c_float]
libgini.procesar_gini.restype = ctypes.c_int

# Wrapper
def procesar_gini(valor):
    return libgini.procesar_gini(valor)