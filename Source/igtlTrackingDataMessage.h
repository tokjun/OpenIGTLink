/*=========================================================================

  Program:   The OpenIGTLink Library
  Language:  C++
  Web page:  http://openigtlink.org/

  Copyright (c) Insight Software Consortium. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __igtlTrackingDataMessage_h
#define __igtlTrackingDataMessage_h

#include <vector>
#include <string>

#include "igtlObject.h"
#include "igtlMath.h"
#include "igtlMessageBase.h"
#include "igtlTrackingDataMessageBase.h"
#include "igtlTypes.h"


namespace igtl
{

class IGTLCommon_EXPORT TrackingDataElement: public TrackingDataElementBase
{
public:
  typedef TrackingDataElement            Self;
  typedef TrackingDataElementBase        Superclass;
  typedef SmartPointer<Self>             Pointer;
  typedef SmartPointer<const Self>       ConstPointer;

  igtlTypeMacro(igtl::TrackingDataElement, igtl::TrackingDataElementBase);
  igtlNewMacro(igtl::TrackingDataElement);

public:

  /// Sets the position by 3-element array of x, y, and z coordinates.
  virtual void SetPosition(float p[3]);

  /// Gets the position. The function substitutes 3-element array of x, y and z coordinates in 'p'.
  virtual void GetPosition(float p[3]);

  /// Sets the position by x, y, and z coordinates.
  virtual void SetPosition(float px, float py, float pz);

  /// Gets the position. The function substitutes the xyz coordinates in 'px', 'py', and 'pz'.
  virtual void GetPosition(float* px, float* py, float* pz);

  /// Sets the 4-by-4 transformation matrix.
  virtual void SetMatrix(Matrix4x4& mat);

  /// Gets the 4-by-4 transformation matrix. 
  virtual void GetMatrix(Matrix4x4& mat);

  /// Sets the quaternion by 4-element array.
  virtual void SetQuaternion(float q[4]);

  /// Gets the quaternion. The function substitutes the array of elements of the quaternion in 'q'.
  virtual void GetQuaternion(float q[4]);

  /// Sets the quaternion by elements of the quaternion (x, y, z and w).
  virtual void SetQuaternion(float qx, float qy, float qz, float w);

  /// Gets the quaternion. The function substitutes the elements of the quaternion in 'qx', 'qy', 'qz' and 'qw'.
  virtual void GetQuaternion(float* qx, float* qy, float* qz, float* w);

  /// Inialize the rotation / translation
  virtual void Identity();

protected:
 TrackingDataElement() : TrackingDataElementBase() {};
  ~TrackingDataElement() {};

protected:

  /// Transform matrix
  Matrix4x4     m_Matrix;
};


/// A class for the STT_TDATA message type.
class IGTLCommon_EXPORT StartTrackingDataMessage: public StartTrackingDataMessageBase
{

public:
  typedef StartTrackingDataMessage       Self;
  typedef StartTrackingDataMessageBase   Superclass;
  typedef SmartPointer<Self>             Pointer;
  typedef SmartPointer<const Self>       ConstPointer;

  igtlTypeMacro(igtl::StartTrackingDataMessage, igtl::StartTrackingDataMessageBase);
  igtlNewMacro(igtl::StartTrackingDataMessage);

protected:
  StartTrackingDataMessage() : StartTrackingDataMessageBase() { this->m_DefaultBodyType = "STT_TDATA"; };
  ~StartTrackingDataMessage() {};

};


/// A class for the STP_TDATA message type.
class IGTLCommon_EXPORT StopTrackingDataMessage: public StopTrackingDataMessageBase
{
public:
  typedef StopTrackingDataMessage        Self;
  typedef StopTrackingDataMessageBase    Superclass;
  typedef SmartPointer<Self>             Pointer;
  typedef SmartPointer<const Self>       ConstPointer;

  igtlTypeMacro(igtl::StopTrackingDataMessage, igtl::StopTrackingDataMessageBase);
  igtlNewMacro(igtl::StopTrackingDataMessage);

protected:
  StopTrackingDataMessage() : StopTrackingDataMessageBase() { this->m_DefaultBodyType  = "STP_TDATA"; };
  ~StopTrackingDataMessage() {};

};


/// A class for the RTS_TDATA message type.
class IGTLCommon_EXPORT RTSTrackingDataMessage: public RTSTrackingDataMessageBase
{
public:
  typedef RTSTrackingDataMessage         Self;
  typedef RTSTrackingDataMessageBase     Superclass;
  typedef SmartPointer<Self>             Pointer;
  typedef SmartPointer<const Self>       ConstPointer;

  igtlTypeMacro(igtl::RTSTrackingDataMessage, igtl::RTSTrackingDataMessageBase);
  igtlNewMacro(igtl::RTSTrackingDataMessage);

protected:
  RTSTrackingDataMessage() : RTSTrackingDataMessageBase() { this->m_DefaultBodyType  = "RTS_TDATA"; };
  ~RTSTrackingDataMessage() {};

};


/// The TDATA message type is intended for transferring 3D positions of surgical tools,
/// markers etc. Those positions are often measured by optical, electromagnetic or other
/// type of 3D position sensor continuously and transferred as series of messages.
/// Since it is important for software that receives TDATA to control data flow,
/// STT_TDATA query data type has interval field to control the frame rate of consecutive messages.
class IGTLCommon_EXPORT TrackingDataMessage: public TrackingDataMessageBase
{
public:
  typedef TrackingDataMessage            Self;
  typedef MessageBase                    Superclass;
  typedef SmartPointer<Self>             Pointer;
  typedef SmartPointer<const Self>       ConstPointer;

  igtlTypeMacro(igtl::TrackingDataMessage, igtl::TrackingDataMessageBase);
  igtlNewMacro(igtl::TrackingDataMessage);


public:

  /// Adds tracking data element.
  virtual int  AddTrackingDataElement(TrackingDataElement::Pointer& elem);

  /// Clears the all tracking data element in the list.
  virtual void ClearTrackingDataElements();

  /// Gets the number of tracking data elements in the list.
  virtual int  GetNumberOfTrackingDataElements();

  /// Gets the tracking data element specified by 'index'.
  virtual void GetTrackingDataElement(int index, TrackingDataElement::Pointer& elem);

protected:
  TrackingDataMessage() : TrackingDataMessageBase() { this->m_DefaultBodyType = "TDATA"; };
  ~TrackingDataMessage() {};
  
protected:

  virtual int  GetBodyPackSize();
  virtual int  PackBody();
  virtual int  UnpackBody();

};


} // namespace igtl

#endif // _igtlTrackingDataMessage_h



