# Setup file for Rt's Python interface.  This will build and
# install Rt as a Python extension module.
#
# SWIG should've been used to create Rt_wrap.cxx before invoking
# this script.  swig -c++ -python Rt.i
#
# Brian Hammond <RtDev@BrianHammond.com>
# $Id$

from distutils.core import setup, Extension
import glob, os

# TODO 
# Ensure that Rt_wrap.cxx exists first

# Create source file list (up a dir).  Include the SWIG
# generated wrapper as well.

srcfiles = glob.glob('*.cpp')
srcfiles.append('Rt_wrap.cxx')
srcfiles.remove('main.cpp')        # Not a standalone, thanks.

# Define our extension module "Rt"
# Note: this must be able to find libPNG headers and library so
# update as needed.

rtmod = Extension(
  '_Rt', srcfiles, 
  define_macros=[
    ('DBL_REAL', 1),       # Use double precision floating point
  ],
  extra_compile_args=[
    '-ffast-math'          # Ok to use fast math
  ],
  include_dirs=[
    '../include'        # Rt includes
  ],
  library_dirs=[
  ],
  libraries=[
    'stdc++',              # C++ 
    'm',                   # math
    'z',                   # zlib
    'png'                  # libpng
  ]
)

setup(name="Rt",
  version="0.1.0",
  description="A simple raytracer",
  author="Brian Hammond",
  author_email="RtDev@BrianHammond.com",
  url="http://brianhammond.com/Rt",
  ext_modules=[rtmod],
  py_modules=["Rt"])

