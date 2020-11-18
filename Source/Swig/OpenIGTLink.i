%module OpenIGTLink
%include <windows.i>
%include "std_string.i"

%begin %{
#ifdef _MSC_VER
#define SWIG_PYTHON_INTERPRETER_NO_DEBUG
#endif
%}


#define IGTLCommon_EXPORT __declspec(dllexport)
#define IGTL_EXPORT __declspec(dllexport)
//#define igtl_export __declspec(dllexport)

////#define SmartPointer igtl::SmartPointer
//
//#define igtlNewMacro(x) \
//static Pointer New(void) \
//{ \
//  Pointer smartPtr = ::igtl::ObjectFactory<x>::Create(); \
//  if(smartPtr.GetPointer() == NULL) \
//    { \
//    smartPtr = new x; \
//    } \
//  smartPtr->UnRegister(); \
//  return smartPtr; \
//} \
//virtual ::igtl::LightObject::Pointer CreateAnother(void) const \
//{ \
//  return x::New().GetPointer(); \
//} \
//
//#define igtlTypeMacro(thisClass,superclass) \
//    virtual const char *GetNameOfClass() const \
//        {return #thisClass;}


%{
#define SWIG_FILE_WITH_INIT

//#pragma comment(lib, "Ws2_32.lib")
//#include "igtlWin32Header.h"

typedef float Matrix4x4[4][4];
typedef float igtlFloat32;

#include "igtlSocket.h"
#include <iostream>
#include "igtlSimpleFastMutexLock.h"
#include "igtlSmartPointer.h"
#include "igtlObject.h"
#include "igtlLightObject.h"
#include "igtlMessageBase.h"
#include "igtlMessageFactory.h"

#include "igtlSocket.h"
#include "igtlServerSocket.h"
#include "igtlClientSocket.h"
#include "igtlTransformMessage.h"
#include "igtlStringMessage.h"
#include "igtlStatusMessage.h"
#include "igtlPointMessage.h"
#include "igtlImageMessage.h"
#include "igtlImageMessage2.h"
#include "igtlPolyDataMessage.h"
#include "igtlPositionMessage.h"

#include "igtlBindMessage.h"
#include "igtlTrajectoryMessage.h"
#include "igtlSensorMessage.h"
#include "igtlQueryMessage.h"
#include "igtlNDArrayMessage.h"
#include "igtlTrackingDataMessage.h"
#include "igtlQuaternionTrackingDataMessage.h"
#include "igtlLabelMetaMessage.h"
#include "igtlImageMetaMessage.h"
#include "igtlCapabilityMessage.h"
#include "igtlColorTableMessage.h"
#include "igtlCommandMessage.h"

%}

%typedef float Matrix4x4[4][4];
%typedef float igtlFloat32;
%typedef double igtlFloat64;

%import "igtlSmartPointer.h"
%import "igtlLightObject.h"
%import "igtlObject.h"

%template(ClientSocketPointer) igtl::SmartPointer<igtl::ClientSocket>;
%template(ServerSocketPointer) igtl::SmartPointer<igtl::ServerSocket>;
%template(PointElementPointer) igtl::SmartPointer<igtl::PointElement>;
%template(PointMessagePointer) igtl::SmartPointer<igtl::PointMessage>;
%template(TransformMessagePointer) igtl::SmartPointer<igtl::TransformMessage>;
%template(StringMessagePointer) igtl::SmartPointer<igtl::StringMessage>;
%template(StatusMessagePointer) igtl::SmartPointer<igtl::StatusMessage>;
%template(ImageMessagePointer) igtl::SmartPointer<igtl::ImageMessage>;
%template(ImageMessage2Pointer) igtl::SmartPointer<igtl::ImageMessage2>;
%template(StopImagePointer) igtl::SmartPointer<igtl::StopImageMessage>;
%template(BindMessageBasePointer) igtl::SmartPointer<igtl::BindMessageBase>;
%template(BindMessagePointer) igtl::SmartPointer<igtl::BindMessage>;
%template(TrajectoryElementPointer) igtl::SmartPointer<igtl::TrajectoryElement>;
%template(TrajectoryMessagePointer) igtl::SmartPointer<igtl::TrajectoryMessage>;
%template(NDArrayMessagePointer) igtl::SmartPointer<igtl::NDArrayMessage>;
%template(TrackingDataElementPointer) igtl::SmartPointer<igtl::TrackingDataElement>;
%template(StartTrackingDataMessagePointer) igtl::SmartPointer<igtl::StartTrackingDataMessage>;
%template(StopTrackingDataMessagePointer) igtl::SmartPointer<igtl::StopTrackingDataMessage>;
%template(RTSTrackingDataMessagePointer) igtl::SmartPointer<igtl::RTSTrackingDataMessage>;
%template(TrackingDataMessagePointer) igtl::SmartPointer<igtl::TrackingDataMessage>;
%template(QuaternionTrackingDataElementPointer) igtl::SmartPointer<igtl::QuaternionTrackingDataElement>;
%template(StartQuaternionTrackingDataMessagePointer) igtl::SmartPointer<igtl::StartQuaternionTrackingDataMessage>;
%template(StopQuaternionTrackingDataMessagePointer) igtl::SmartPointer<igtl::StopQuaternionTrackingDataMessage>;
%template(RTSQuaternionTrackingDataMessagePointer) igtl::SmartPointer<igtl::RTSQuaternionTrackingDataMessage>;
%template(QuaternionTrackingDataMessagePointer) igtl::SmartPointer<igtl::QuaternionTrackingDataMessage>;
%template(LabelMetaElementPointer) igtl::SmartPointer<igtl::LabelMetaElement>;
%template(LabelMetaMessagePointer) igtl::SmartPointer<igtl::LabelMetaMessage>;
%template(ImageMetaElementPointer) igtl::SmartPointer<igtl::ImageMetaElement>;
%template(ImageMetaMessagePointer) igtl::SmartPointer<igtl::ImageMetaMessage>;
%template(CapabilityMessagePointer) igtl::SmartPointer<igtl::CapabilityMessage>;
%template(ColorTableMessagePointer) igtl::SmartPointer<igtl::ColorTableMessage>;
%template(CommandMessagePointer) igtl::SmartPointer<igtl::CommandMessage>;
%template(RTSCommandMessagePointer) igtl::SmartPointer<igtl::RTSCommandMessage>;

%template(GetPointMessagePointer) igtl::SmartPointer<igtl::GetPointMessage>;
%template(GetTransformMessagePointer) igtl::SmartPointer<igtl::GetTransformMessage>;
%template(GetStatusMessagePointer) igtl::SmartPointer<igtl::GetStatusMessage>;
%template(GetImageMessagePointer) igtl::SmartPointer<igtl::GetImageMessage>;
%template(GetImageMessage2Pointer) igtl::SmartPointer<igtl::GetImageMessage2>;
%template(GetBindMessagePointer) igtl::SmartPointer<igtl::GetBindMessage>;
%template(GetTrajectoryMessagePointer) igtl::SmartPointer<igtl::GetTrajectoryMessage>;
%template(GetLabelMetaMessagePointer) igtl::SmartPointer<igtl::GetLabelMetaMessage>;
%template(GetImageMetaMessagePointer) igtl::SmartPointer<igtl::GetImageMetaMessage>;
%template(GetColorTableMessagePointer) igtl::SmartPointer<igtl::GetColorTableMessage>;

