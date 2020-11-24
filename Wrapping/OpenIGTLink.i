%module openigtlink
%include <windows.i>
%include "std_string.i"

// Define array typesf
%include "carrays.i"

%array_class(float, floatArray);
%array_class(int, intArray);
%array_class(char, charArray);

%{
  #include <cstring>

  // Copy a byte array from a Python Bytes object to a C++ void* pointer.
  // Note that the first two parameters are 'typemaped' (see %typemap(in) below)
  // From a python script, the fuction is called as:
  //
  // >>> import openigtlink as igtl
  // >>> igtl.copyBytesToPointer(im, ptr)
  //
  void copyBytesToPointer(char* bytes, int array_length, void* dst_ptr) {
    std::memcpy(dst_ptr, bytes, array_length);
  }

  // This utility function allows to offset the given pointer.
  // Example: The following code copies pixels from array of images slice by slice.
  //
  // >>> import openigtlink as igtl
  // >>> offset = 0
  // >>> for i in range(nSlices):
  // >>>   igtl.copyBytesToPointer(image[i], igtl.offsetPointer(imageMsg.GetScalarPointer(), offset))
  // >>>   offset = offset + len(image[i])
  //
  void* offsetPointer(void* ptr, int offset) {
    char * ptrc = (char*) ptr;
    return (void*) (ptrc + offset);
  }
%}


// Typemap for copyBytesToPointer()
%typemap(in) (char *bytes, int array_length) {
  Py_ssize_t len;
  PyBytes_AsStringAndSize($input, &$1, &len);
  $2 = (int)len;
}


// Covert from Python flaot[][] to C++ igtl::Matrix4x4 &
// Functions that take an igtl::Matrix4x4 reference can be directly called with a 2D Python array.

%typemap(in) igtl::Matrix4x4 & {

  igtl::Matrix4x4 temp;
  
  int i,j;
  if (!PySequence_Check($input)) {
    PyErr_SetString(PyExc_ValueError,"Expected a sequence");
    return NULL;
  }
  if (PySequence_Length($input) != 4) {
    PyErr_SetString(PyExc_ValueError,"Size mismatch. Expected 4 elements");
    return NULL;
  }

  for (i = 0; i < 4; i++) {
    PyObject *olist = PySequence_GetItem($input,i);
    if (!PySequence_Check(olist)) {
      PyErr_SetString(PyExc_ValueError,"Expected a sequence");
      return NULL;
    }
    if (PySequence_Length(olist) != 4) {
      PyErr_SetString(PyExc_ValueError,"Size mismatch. Expected 4 elements");
      return NULL;
    }

    for (j = 0; j < 4; j++) {
      PyObject *o = PySequence_GetItem(olist,j);
      if (PyNumber_Check(o)) {
        temp[i][j] = (float) PyFloat_AsDouble(o);
      } else {
        PyErr_SetString(PyExc_ValueError,"Sequence elements must be numbers");
        return NULL;
      }
    }
  }

  $1 = &temp;
}


void copyBytesToPointer(char* bytes, int array_length, void* dst_ptr);
void* offsetPointer(void* ptr, int offset);


%begin %{
#ifdef _MSC_VER
#define SWIG_PYTHON_INTERPRETER_NO_DEBUG
#endif
%}

%{
#define SWIG_FILE_WITH_INIT

#pragma comment(lib, "Ws2_32.lib")
#include "igtlWin32Header.h"
#include "igtlUnit.h"
#include "igtlMath.h"
#include "igtlTypes.h"
#include "igtlMacro.h"
#include "igtlSmartPointer.h"
#include "igtlLightObject.h"
#include "igtlObject.h"
#include "igtlSmartPointer.h"
#include "igtlSimpleFastMutexLock.h"
#include "igtlMessageFactory.h"
#include "igtlSocket.h"
#include "igtlClientSocket.h"
#include "igtlServerSocket.h"
#include "igtlMessageHeader.h"
#include "igtlMessageBase.h"
#include "igtlCapabilityMessage.h"
#include "igtlImageMessage.h"
#include "igtlImageMessage2.h"
#include "igtlPositionMessage.h"
#include "igtlTransformMessage.h"
#include "igtlStatusMessage.h"
#include "igtlBindMessage.h"
#include "igtlColorTableMessage.h"
#include "igtlImageMetaMessage.h"
#include "igtlLabelMetaMessage.h"
#include "igtlNDArrayMessage.h"
#include "igtlPointMessage.h"
//#include "igtlPolyDataMessage.h"
#include "igtlQuaternionTrackingDataMessage.h"
#include "igtlSensorMessage.h"
#include "igtlStringMessage.h"
#include "igtlTrackingDataMessage.h"
#include "igtlTrajectoryMessage.h"
//#include "igtlQueryMessage.h"
#include "igtlCommandMessage.h"
%}

// Common header files
%include "igtlMacro.h"
%include "igtlWin32Header.h"

%import "igtlSmartPointer.h"
%import "igtlObject.h"
%import "igtlObjectFactory.h"
%import "igtlLightObject.h"
%import "igtlMessageFactory.h"

// Socket
%template(SocketPointer) igtl::SmartPointer<igtl::Socket>;
%template(ClientSocketPointer) igtl::SmartPointer<igtl::ClientSocket>;
%template(ServerSocketPointer) igtl::SmartPointer<igtl::ServerSocket>;

// // Message Base
%template(MessageHeaderPointer) igtl::SmartPointer<igtl::MessageHeader>;
%template(MessageBasePointer) igtl::SmartPointer<igtl::MessageBase>;

// CapabilityMessage
%template(CapabilityMessagePointer) igtl::SmartPointer<igtl::CapabilityMessage>;
%template(ImageMessagePointer) igtl::SmartPointer<igtl::ImageMessage>;
%template(ImageMessage2Pointer) igtl::SmartPointer<igtl::ImageMessage2>;

// ImageMessage
%template(GetImageMessagePointer) igtl::SmartPointer<igtl::GetImageMessage>;
%template(GetImageMessage2Pointer) igtl::SmartPointer<igtl::GetImageMessage2>;
%template(StopImagePointer) igtl::SmartPointer<igtl::StopImageMessage>;

// PositionMessage
%template(PositionMessagePointer) igtl::SmartPointer<igtl::PositionMessage>;

// TransformMessage
%template(TransformMessagePointer) igtl::SmartPointer<igtl::TransformMessage>;
%template(GetTransformMessagePointer) igtl::SmartPointer<igtl::GetTransformMessage>;

// StatusMessage
%template(StatusMessagePointer) igtl::SmartPointer<igtl::StatusMessage>;
%template(GetStatusMessagePointer) igtl::SmartPointer<igtl::GetStatusMessage>;

// BindMessage
%template(BindMessagePointer) igtl::SmartPointer<igtl::BindMessage>;
%template(BindMessageBasePointer) igtl::SmartPointer<igtl::BindMessageBase>;
%template(GetBindMessagePointer) igtl::SmartPointer<igtl::GetBindMessage>;

// ColorTableMessage
%template(ColorTableMessagePointer) igtl::SmartPointer<igtl::ColorTableMessage>;
%template(GetColorTableMessagePointer) igtl::SmartPointer<igtl::GetColorTableMessage>;

// ImageMetaMessage
%template(ImageMetaMessagePointer) igtl::SmartPointer<igtl::ImageMetaMessage>;
%template(GetImageMetaMessagePointer) igtl::SmartPointer<igtl::GetImageMetaMessage>;
%template(ImageMetaElementPointer) igtl::SmartPointer<igtl::ImageMetaElement>;

// LabelMetaMessage
%template(LabelMetaMessagePointer) igtl::SmartPointer<igtl::LabelMetaMessage>;
%template(GetLabelMetaMessagePointer) igtl::SmartPointer<igtl::GetLabelMetaMessage>;
%template(LabelMetaElementPointer) igtl::SmartPointer<igtl::LabelMetaElement>;

// NDArrayMessage
%template(NDArrayMessagePointer) igtl::SmartPointer<igtl::NDArrayMessage>;

// PointMessage
%template(PointMessagePointer) igtl::SmartPointer<igtl::PointMessage>;
%template(GetPointMessagePointer) igtl::SmartPointer<igtl::GetPointMessage>;
%template(PointElementPointer) igtl::SmartPointer<igtl::PointElement>;

// QuaternionTrackingDataMessage
%template(QuaternionTrackingDataMessagePointer) igtl::SmartPointer<igtl::QuaternionTrackingDataMessage>;
%template(QuaternionTrackingDataElementPointer) igtl::SmartPointer<igtl::QuaternionTrackingDataElement>;
%template(StartQuaternionTrackingDataMessagePointer) igtl::SmartPointer<igtl::StartQuaternionTrackingDataMessage>;
%template(StopQuaternionTrackingDataMessagePointer) igtl::SmartPointer<igtl::StopQuaternionTrackingDataMessage>;
%template(RTSQuaternionTrackingDataMessagePointer) igtl::SmartPointer<igtl::RTSQuaternionTrackingDataMessage>;

// TrackingDataMessage
%template(TrackingDataMessagePointer) igtl::SmartPointer<igtl::TrackingDataMessage>;
%template(TrackingDataElementPointer) igtl::SmartPointer<igtl::TrackingDataElement>;
%template(StartTrackingDataMessagePointer) igtl::SmartPointer<igtl::StartTrackingDataMessage>;
%template(StopTrackingDataMessagePointer) igtl::SmartPointer<igtl::StopTrackingDataMessage>;
%template(RTSTrackingDataMessagePointer) igtl::SmartPointer<igtl::RTSTrackingDataMessage>;

// SensorMessage
%template(SensorMessagePointer) igtl::SmartPointer<igtl::SensorMessage>;

// StringMessage
%template(StringMessagePointer) igtl::SmartPointer<igtl::StringMessage>;

// TrajectoryMessage
%template(TrajectoryMessagePointer) igtl::SmartPointer<igtl::TrajectoryMessage>;
%template(GetTrajectoryMessagePointer) igtl::SmartPointer<igtl::GetTrajectoryMessage>;
%template(TrajectoryElementPointer) igtl::SmartPointer<igtl::TrajectoryElement>;

// QueryMessage
// TODO: QueryMessage is commented out for now because it causes ImportError
//%template(QueryMessagePointer) igtl::SmartPointer<igtl::QueryMessage>;

// CommandMessage
%template(CommandMessagePointer) igtl::SmartPointer<igtl::CommandMessage>;
%template(RTSCommandMessagePointer) igtl::SmartPointer<igtl::RTSCommandMessage>;

//// Classes to be wrapped:
%include "igtlLightObject.h"
%include "igtlObject.h"
%include "igtlTimeStamp.h"
%include "igtlUnit.h"
%include "igtlMath.h"
%include "igtlTypes.h"

%include "igtlMessageHeader.h"
%include "igtlMessageBase.h"

%include "igtlSocket.h"
%include "igtlClientSocket.h"
%include "igtlServerSocket.h"

%include "igtlCapabilityMessage.h"
%include "igtlImageMessage.h"
%include "igtlImageMessage2.h"
%include "igtlPositionMessage.h"
%include "igtlTransformMessage.h"
%include "igtlStatusMessage.h"

%include "igtlBindMessage.h"
%include "igtlColorTableMessage.h"
%include "igtlImageMetaMessage.h"
%include "igtlLabelMetaMessage.h"
%include "igtlNDArrayMessage.h"
%include "igtlPointMessage.h"
 //%include "igtlPolyDataMessage.h"
%include "igtlQuaternionTrackingDataMessage.h"
%include "igtlSensorMessage.h"
%include "igtlStringMessage.h"
%include "igtlTrackingDataMessage.h"
%include "igtlTrajectoryMessage.h"
 //%include "igtlQueryMessage.h"
%include "igtlCommandMessage.h"
