Python Wrapping
===============

Installation
------------

To generate a Python package, turn the USE_SWIG_PYTHON option ON from the CMake
GUI or cmake command. The option is only tested with BUILD_SHARED_LIBS=ON.

Once the build process is completed successfully, the package can be installed
using setup.py. To run setup.py, make sure to install setuptools in the python
via pip: 

~~~~
pip install -U pip setuptools
~~~~

setup.py can be executed as a Makefile option. In the build directory, run:

~~~~
make install-python
~~~~

If you have multiple python interpreters in the system (e.g., python2 and python3),
and want to force to install the library in python3, you can run:

~~~~
make install-python3
~~~~

After the installation, you can load the openigtlink library from python as:

~~~~
import openigtlink
~~~~


