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


Examples
========

The following code pushes a linear transformation matrix to an OpenIGTLink server:

~~~~
import openigtlink as igtl

transMsg = igtl.TransformMessage.New()
transMsg.SetDeviceName("Tracker")

# Create a 2D array
trans = [[1.0, 0.0, 0.0, 0.0], [0.0, 1.0, 0.0, 0.0], [0.0, 0.0, 1.0, 0.0], [0.0, 0.0, 0.0, 1.0]]

# Change X, Y, and Z coordinates
trans[0][3] = 10.0
trans[1][3] = 20.0
trans[2][3] = 30.0

transMsg.Pack();

c = igtl.ClientSocket.New()
c.ConnectToServer('localhost', 18944)
c.Send(transMsg.GetPackPointer(), transMsg.GetPackSize())
c.CloseSocket()
~~~~

The following code pushes a pixel patter to the server:

~~~~
import openigtlink as igtl

imageMsg = igtl.ImageMessage.New()
imageMsg.SetDimensions(64, 64, 1)
imageMsg.SetSpacing(1.0, 1.0, 5)
imageMsg.SetScalarTypeToInt8()
imageMsg.SetDeviceName('Test2')
imageMsg.SetNumComponents(1)
imageMsg.SetEndian(2)
imageMsg.AllocateScalars()

# Generate a 64x64 pixel matrix
b = [0.0] * 64*64
for i in range(64*64):
    b[i] = i % 256

im = bytes(b)

# Copy the pixel matrix to the imageMsg
igtl.copyBytesToPointer(im, igtl.offsetPointer(imageMsg.GetScalarPointer(), 0))

# Create a transform as a 2D array
trans = [[1.0, 0.0, 0.0, 0.0], [0.0, 1.0, 0.0, 0.0], [0.0, 0.0, 1.0, 0.0], [0.0, 0.0, 0.0, 1.0]]

trans[0][3] = 10.0
trans[1][3] = 20.0
trans[2][3] = 30.0

imageMsg.SetMatrix(trans)

imageMsg.Pack()

c = igtl.ClientSocket.New()
c.ConnectToServer('localhost', 18944)
c.Send(imageMsg.GetPackPointer(), imageMsg.GetPackSize())
c.CloseSocket()
~~~~

Please note that Python wrappered functions cannot return values using a 2D array referenced as an argument.
Instead, those functions return a 2D array. However, the functions still require a reference to a 2D array,
and the user must prepare a dummy array to call it. For example:

~~~~
dummy = [[0.0, 0.0, 0.0, 0.0], [0.0, 0.0, 0.0, 0.0], [0.0, 0.0, 0.0, 0.0], [0.0, 0.0, 0.0, 0.0]]
a = transMsg.GetMatrix(dummy)
~~~~





