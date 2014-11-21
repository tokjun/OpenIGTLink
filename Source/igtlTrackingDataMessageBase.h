/*=========================================================================

  Program:   The OpenIGTLink Library
  Language:  C++
  Web page:  http://openigtlink.org/

  Copyright (c) Insight Software Consortium. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __igtlTrackingDataMessageBase_h
#define __igtlTrackingDataMessageBase_h

#include <vector>
#include <string>

#include "igtlObject.h"
#include "igtlMath.h"
#include "igtlMessageBase.h"
#include "igtlTypes.h"


namespace igtl
{

class IGTLCommon_EXPORT TrackingDataElementBase: public Object
{
public:
  typedef TrackingDataElementBase        Self;
  typedef Object                         Superclass;
  typedef SmartPointer<Self>             Pointer;
  typedef SmartPointer<const Self>       ConstPointer;

  igtlTypeMacro(igtl::TrackingDataElementBase, igtl::Object);
  igtlNewMacro(igtl::TrackingDataElementBase);

  /// Tracking data type. 
  ///  TYPE_TRACKER:  Tracker
  ///  TYPE_6D:       6D instrument: (regular instrument)
  ///  TYPE_3D:       3D instrument (only tip of the instrument defined)
  ///  TYPE_5D:       5D instrument (tip and handle are defined, but not the normal vector)
  enum {
    TYPE_TRACKER  = 1,
    TYPE_6D       = 2,
    TYPE_3D       = 3,
    TYPE_5D       = 4,
  };

public:

  /// Sets the name of the instrument/tracker.
  int          SetName(const char* name);

  /// Gets the name of the instrument/tracker.
  const char*  GetName()                            { return this->m_Name.c_str(); };

  /// Sets the type of the instrument/tracker.
  int          SetType(igtlUint8 type);

  /// Gets the type of the instrument/tracker.
  igtlUint8    GetType()                            { return this->m_Type; };

  /// Sets the position by 3-element array of x, y, and z coordinates.
  virtual void SetPosition(float p[3]) {};

  /// Gets the position. The function substitutes 3-element array of x, y and z coordinates in 'p'.
  virtual void GetPosition(float p[3]) {};

  /// Sets the position by x, y, and z coordinates.
  virtual void SetPosition(float px, float py, float pz) {};

  /// Gets the position. The function substitutes the xyz coordinates in 'px', 'py', and 'pz'.
  virtual void GetPosition(float* px, float* py, float* pz) {};

  /// Sets the 4-by-4 transformation matrix.
  virtual void SetMatrix(Matrix4x4& mat) {};

  /// Gets the 4-by-4 transformation matrix. 
  virtual void GetMatrix(Matrix4x4& mat) {};

  /// Sets the quaternion by 4-element array.
  virtual void SetQuaternion(float q[4]) {};

  /// Gets the quaternion. The function substitutes the array of elements of the quaternion in 'q'.
  virtual void GetQuaternion(float q[4]) {};

  /// Sets the quaternion by elements of the quaternion (x, y, z and w).
  virtual void SetQuaternion(float qx, float qy, float qz, float w) {};

  /// Gets the quaternion. The function substitutes the elements of the quaternion in 'qx', 'qy', 'qz' and 'qw'.
  virtual void GetQuaternion(float* qx, float* qy, float* qz, float* w) {};

  virtual void Identity() {};

protected:
  TrackingDataElementBase();
  ~TrackingDataElementBase();

protected:

  /// Name / description (< 20 bytes
  std::string   m_Name;

  /// Tracking data type (TYPE_TRACKER, TYPE_6D, TYPE_3D, TYPE_5D)
  igtlUint8     m_Type;

};


/// A base class for the STT_TDATA/STT_QTDATA message type.
class IGTLCommon_EXPORT StartTrackingDataMessageBase: public MessageBase
{

public:
  typedef StartTrackingDataMessageBase   Self;
  typedef MessageBase                    Superclass;
  typedef SmartPointer<Self>             Pointer;
  typedef SmartPointer<const Self>       ConstPointer;

  igtlTypeMacro(igtl::StartTrackingDataMessageBase, igtl::MessageBase);
  igtlNewMacro(igtl::StartTrackingDataMessageBase);

public:
  /// Sets the time resolution for streaming of TDATA/QTDATA messages
  virtual void      SetResolution(igtlInt32 res)  { this->m_Resolution = res; }; // ms

  /// Gets the time resolution for streaming of TDATA/QTDATA messages
  virtual igtlInt32 GetResolution()               { return this->m_Resolution; };

  /// Sets the name of the coordinate system. The name must be defined by the user.
  virtual int       SetCoordinateName(const char* name);

  /// Gets the name of the coordinate system.
  virtual const char* GetCoordinateName()         { return this->m_CoordinateName.c_str(); };

protected:
  StartTrackingDataMessageBase();
  ~StartTrackingDataMessageBase();

protected:
  virtual int  GetBodyPackSize();
  virtual int  PackBody();
  virtual int  UnpackBody();

protected:

  /// Minimum time between two frames (ms). Use 0 for as fast as possible.
  igtlInt32     m_Resolution;

  /// Name of the coordinate system.
  std::string   m_CoordinateName;

};


/// A class for the STP_TDATA message type.
class IGTLCommon_EXPORT StopTrackingDataMessageBase: public MessageBase
{
public:
  typedef StopTrackingDataMessageBase    Self;
  typedef MessageBase                    Superclass;
  typedef SmartPointer<Self>             Pointer;
  typedef SmartPointer<const Self>       ConstPointer;

  igtlTypeMacro(igtl::StopTrackingDataMessageBase, igtl::MessageBase);
  igtlNewMacro(igtl::StopTrackingDataMessageBase);

protected:
  StopTrackingDataMessageBase() : MessageBase() { };
  ~StopTrackingDataMessageBase() {};

protected:
  virtual int  GetBodyPackSize() { return 0; };
  virtual int  PackBody()        { AllocatePack(); return 1; };
  virtual int  UnpackBody()      { return 1; };

};


/// A base class for the RTS_TDATA/RTS_TDATA message type.
class IGTLCommon_EXPORT RTSTrackingDataMessageBase: public MessageBase
{
public:
  typedef RTSTrackingDataMessageBase     Self;
  typedef MessageBase                    Superclass;
  typedef SmartPointer<Self>             Pointer;
  typedef SmartPointer<const Self>       ConstPointer;

  /// Status type
  enum {
    STATUS_SUCCESS = 0,
    STATUS_ERROR = 1
  };

  igtlTypeMacro(igtl::RTSTrackingDataMessageBase, igtl::MessageBase);
  igtlNewMacro(igtl::RTSTrackingDataMessageBase);

  /// Sets the status. 'status' must be either STATUS_SUCCESS or STATUS_ERROR.
  virtual void  SetStatus(igtlUint8 status){ this->m_Status = status; }

  /// Gets the status. The function returns either STATUS_SUCCESS or STATUS_ERROR.
  virtual igtlUint8  GetStatus()                { return this->m_Status; };

protected:
  RTSTrackingDataMessageBase() : MessageBase(), m_Status(0) { };
  ~RTSTrackingDataMessageBase() {};

  /// A variable to store the status.
  igtlUint8 m_Status;

protected:
  virtual int  GetBodyPackSize();
  virtual int  PackBody();
  virtual int  UnpackBody();

};


/// The TDATA/QTDATA message type is intended for transferring 3D positions of
/// surgical tools, markers etc. Those positions are often measured by optical,
/// electromagnetic or other type of 3D position sensor continuously and transferred
/// as series of messages.
/// Since it is important for software that receives TDATA to control data flow,
/// STT_TDATA/STT_QTDATA query data type has interval field to control the frame
/// rate of consecutive messages.

class IGTLCommon_EXPORT TrackingDataMessageBase: public MessageBase
{
public:
  typedef TrackingDataMessageBase        Self;
  typedef MessageBase                    Superclass;
  typedef SmartPointer<Self>             Pointer;
  typedef SmartPointer<const Self>       ConstPointer;

  igtlTypeMacro(igtl::TrackingDataMessageBase, igtl::MessageBase);
  igtlNewMacro(igtl::TrackingDataMessageBase);

protected:
  TrackingDataMessageBase();
  ~TrackingDataMessageBase();
  
protected:

  virtual int  GetBodyPackSize() { return 0; };
  virtual int  PackBody()        { return 0; };
  virtual int  UnpackBody()      { return 0; };

  /// The list of trakcing data elements.  
  std::vector<TrackingDataElementBase::Pointer> m_TrackingDataList;
  
protected:

  /// Adds tracking data element.
  int  AddTrackingDataElementBase(TrackingDataElementBase * elem);

  /// Clears the all tracking data element in the list.
  void ClearTrackingDataElementBase();

  /// Gets the number of tracking data elements in the list.
  int  GetNumberOfTrackingDataElementBase();
  
  /// Gets the tracking data element specified by 'index'.
  TrackingDataElementBase* GetTrackingDataElementBase(int index);

};


} // namespace igtl

#endif // _igtlTrackingDataMessageBase_h



