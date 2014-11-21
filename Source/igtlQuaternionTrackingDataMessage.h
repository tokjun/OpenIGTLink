/*=========================================================================

  Program:   The OpenIGTLink Library
  Language:  C++
  Web page:  http://openigtlink.org/

  Copyright (c) Insight Software Consortium. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __igtlQuaternionTrackingDataMessage_h
#define __igtlQuaternionTrackingDataMessage_h

#include <vector>
#include <string>

#include "igtlObject.h"
#include "igtlMath.h"
#include "igtlMessageBase.h"
#include "igtlTrackingDataMessageBase.h"
#include "igtlTypes.h"


namespace igtl
{

/// A class to manage tracking data as a quaternion used in the QTDATA message type.
/// A QuaternionTrackingDataElement class instance holds tracking data for 1 tracking device.
class IGTLCommon_EXPORT QuaternionTrackingDataElement: public TrackingDataElementBase
{

public:
  typedef QuaternionTrackingDataElement  Self;
  typedef TrackingDataElementBase        Superclass;
  typedef SmartPointer<Self>             Pointer;
  typedef SmartPointer<const Self>       ConstPointer;

  igtlTypeMacro(igtl::QuaternionTrackingDataElement, igtl::TrackingDataElementBase);
  igtlNewMacro(igtl::QuaternionTrackingDataElement);

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
  QuaternionTrackingDataElement() : TrackingDataElementBase() {};
  ~QuaternionTrackingDataElement() {};

protected:

  /// position (x, y, z)
  igtlFloat32   m_position[3];

  /// orientation as quaternion (qx, qy, qz, w)
  igtlFloat32   m_quaternion[4];
};


/// A class for the STT_QTDATA message type.
class IGTLCommon_EXPORT StartQuaternionTrackingDataMessage: public StartTrackingDataMessageBase
{

public:
  typedef StartQuaternionTrackingDataMessage  Self;
  typedef StartTrackingDataMessageBase        Superclass;
  typedef SmartPointer<Self>                  Pointer;
  typedef SmartPointer<const Self>            ConstPointer;

  igtlTypeMacro(igtl::StartQuaternionTrackingDataMessage, igtl::StartTrackingDataMessageBase);
  igtlNewMacro(igtl::StartQuaternionTrackingDataMessage);

protected:
  StartQuaternionTrackingDataMessage() : StartTrackingDataMessageBase() { this->m_DefaultBodyType = "STT_QTDATA"; };
  ~StartQuaternionTrackingDataMessage() {};

};


class IGTLCommon_EXPORT StopQuaternionTrackingDataMessage: public StopTrackingDataMessageBase
{
public:
  typedef StopQuaternionTrackingDataMessage  Self;
  typedef StopTrackingDataMessageBase        Superclass;
  typedef SmartPointer<Self>                 Pointer;
  typedef SmartPointer<const Self>           ConstPointer;

  igtlTypeMacro(igtl::StopQuaternionTrackingDataMessage, igtl::StopTrackingDataMessageBase);
  igtlNewMacro(igtl::StopQuaternionTrackingDataMessage);

protected:
  StopQuaternionTrackingDataMessage() : StopTrackingDataMessageBase() { this->m_DefaultBodyType  = "STP_QTDATA"; };
  ~StopQuaternionTrackingDataMessage() {};

};


/// A class for the RTS_QTDATA message type.
class IGTLCommon_EXPORT RTSQuaternionTrackingDataMessage: public RTSTrackingDataMessageBase
{
public:
  typedef RTSQuaternionTrackingDataMessage  Self;
  typedef RTSTrackingDataMessageBase        Superclass;
  typedef SmartPointer<Self>                Pointer;
  typedef SmartPointer<const Self>          ConstPointer;

  igtlTypeMacro(igtl::RTSQuaternionTrackingDataMessage, igtl::RTSTrackingDataMessageBase);
  igtlNewMacro(igtl::RTSQuaternionTrackingDataMessage);

protected:
  RTSQuaternionTrackingDataMessage() : RTSTrackingDataMessageBase() { this->m_DefaultBodyType  = "RTS_QTDATA"; };
  ~RTSQuaternionTrackingDataMessage() {};

};


/// The QTDATA message type is intended for transferring 3D positions of surgical tools,
/// markers etc. Its role is almost identical to TDATA, except that QTDATA describes
/// orientation by using quaternion.
class IGTLCommon_EXPORT QuaternionTrackingDataMessage: public TrackingDataMessageBase
{
public:
  typedef QuaternionTrackingDataMessage  Self;
  typedef TrackingDataMessageBase        Superclass;
  typedef SmartPointer<Self>             Pointer;
  typedef SmartPointer<const Self>       ConstPointer;

  igtlTypeMacro(igtl::QuaternionTrackingDataMessage, igtl::TrackingDataMessageBase);
  igtlNewMacro(igtl::QuaternionTrackingDataMessage);

public:

  /// Adds tracking data element.
  int  AddQuaternionTrackingDataElement(QuaternionTrackingDataElement::Pointer& elem);

  /// Clears the all tracking data element in the list.
  void ClearQuaternionTrackingDataElements();

  /// Gets the number of tracking data elements in the list.
  int  GetNumberOfQuaternionTrackingDataElements();

  /// Gets the tracking data element specified by 'index'.
  void GetQuaternionTrackingDataElement(int index, QuaternionTrackingDataElement::Pointer& elem);


protected:
  QuaternionTrackingDataMessage() : TrackingDataMessageBase() { this->m_DefaultBodyType = "TDATA"; };
  ~QuaternionTrackingDataMessage() {};
  
protected:

  virtual int  GetBodyPackSize();
  virtual int  PackBody();
  virtual int  UnpackBody();
  
};


} // namespace igtl

#endif // _igtlQuaternionTrackingDataMessage_h



