%module OpenIGTLink
%include <windows.i>
%include "std_string.i"

%begin %{
#ifdef _MSC_VER
#define SWIG_PYTHON_INTERPRETER_NO_DEBUG
#endif
%}


#define IGTLCommon_EXPORT __declspec(dllexport)

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
#include "igtlQueryMessage.h"
#include "igtlCommandMessage.h"
%}

%include "igtlMacro.h"
%include "igtlUnit.h"
%include "igtlMath.h"
%include "igtlTypes.h"

%import "igtlSmartPointer.h"
%include "igtlSmartPointer.h"

%import "igtlObject.h"
//%import "igtlLightObject.h"
//%import "igtlSimpleFastMutexLock.h"
//%import "igtlMessageFactory.h"

//%typedef float Matrix4x4[4][4];
//%typedef float igtlFloat32;
//%typedef double igtlFloat64;

//// Classes to be wrapped:
%include "igtlObject.h"
%include "igtlLightObject.h"
%include "igtlSmartPointer.h"
%include "igtlSimpleFastMutexLock.h"
%include "igtlMessageFactory.h"

%include "igtlSocket.h"
%include "igtlClientSocket.h"
%include "igtlServerSocket.h"
%include "igtlMessageHeader.h"
%include "igtlMessageBase.h"

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
