%module openigtlink
%include <windows.i>
%include "std_string.i"

%begin %{
#ifdef _MSC_VER
#define SWIG_PYTHON_INTERPRETER_NO_DEBUG
#endif
%}


#define IGTLCommon_EXPORT __declspec(dllexport)
#define IGTL_EXPORT __declspec(dllexport)

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

%include "igtlMacro.h"

%import "igtlSmartPointer.h"
%import "igtlObject.h"
%import "igtlObjectFactory.h"
%import "igtlMessageHeader.h"
%import "igtlMessageBase.h"

%import "igtlLightObject.h"
%import "igtlMessageFactory.h"

// Socket
%template(SocketPointer) igtl::SmartPointer<igtl::Socket>;
%template(ClientSocketPointer) igtl::SmartPointer<igtl::ClientSocket>;
%template(ServerSocketPointer) igtl::SmartPointer<igtl::ServerSocket>;

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
// TODO: Adding QueryMessage causes ImportError
//%template(QueryMessagePointer) igtl::SmartPointer<igtl::QueryMessage>;

// CommandMessage
%template(CommandMessagePointer) igtl::SmartPointer<igtl::CommandMessage>;
%template(RTSCommandMessagePointer) igtl::SmartPointer<igtl::RTSCommandMessage>;

//// Classes to be wrapped:
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
