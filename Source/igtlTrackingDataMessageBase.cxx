/*=========================================================================

  Program:   The OpenIGTLink Library
  Language:  C++
  Web page:  http://openigtlink.org/

  Copyright (c) Insight Software Consortium. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "igtlTrackingDataMessageBase.h"
#include "igtlMath.h"

#include "igtl_header.h"
#include "igtl_tdata.h"

// Disable warning C4996 (strncpy() may be unsafe) in Windows. 
#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <vector>

namespace igtl {


//----------------------------------------------------------------------
// igtl::TrackingDataElementBase class

TrackingDataElementBase::TrackingDataElementBase() : Object()
{
  this->m_Name = "";
  this->m_Type = TYPE_TRACKER;
  this->Identity();
}


TrackingDataElementBase::~TrackingDataElementBase()
{
}


int TrackingDataElementBase::SetName(const char* name)
{
  if (strlen(name) <= IGTL_TDATA_LEN_NAME)
    {
    this->m_Name = name;
    return 1;
    }
  else
    {
    return 0;
    }
}


int TrackingDataElementBase::SetType(igtlUint8 type)
{
  if(type == TYPE_TRACKER ||
     type == TYPE_6D ||
     type == TYPE_3D ||
     type == TYPE_5D)
    {
    this->m_Type = type;
    return type;
    }
  else
    {
    return 0;
    }
}


//----------------------------------------------------------------------
// igtl::StartTrackingDataMessageBase class

StartTrackingDataMessageBase::StartTrackingDataMessageBase():
  MessageBase()
{
  //this->m_DefaultBodyType = "STT_TDATA";
  this->m_Resolution      = 0;
  this->m_CoordinateName  = "";
}


StartTrackingDataMessageBase::~StartTrackingDataMessageBase()
{
}


int StartTrackingDataMessageBase::SetCoordinateName(const char* name)
{

  // NOTE: The maximum length of the coordinate name is same for all
  // child classes (STT_TDATA/STTQTDATA)
  if (strlen(name) <= IGTL_STT_TDATA_LEN_COORDNAME)
    {
    this->m_CoordinateName = name;
    return 1;
    }
  else
    {
    return 0;
    }
}


int StartTrackingDataMessageBase::GetBodyPackSize()
{
  // NOTE: The body pack size is same for all child classes (STT_TDATA/STT_QTDATA)
  return IGTL_STT_TDATA_SIZE;
}


int StartTrackingDataMessageBase::PackBody()
{
  AllocatePack();

  igtl_stt_tdata* stt_tdata = (igtl_stt_tdata*)this->m_Body;

  // NOTE: The body pack size is same for all child classes (STT_TDATA/STT_QTDATA)
  stt_tdata->resolution = this->m_Resolution;
  strncpy(stt_tdata->coord_name, this->m_CoordinateName.c_str(), IGTL_STT_TDATA_LEN_COORDNAME);

  igtl_stt_tdata_convert_byte_order(stt_tdata);

  return 1;
  
}


int StartTrackingDataMessageBase::UnpackBody()
{
  igtl_stt_tdata* stt_tdata = (igtl_stt_tdata*)this->m_Body;
  
  igtl_stt_tdata_convert_byte_order(stt_tdata);

  this->m_Resolution = stt_tdata->resolution;

  // NOTE: The maximum length of the coordinate name is same for all
  // child classes (STT_TDATA/STTQTDATA)
  char strbuf[IGTL_STT_TDATA_LEN_COORDNAME+1];
  strbuf[IGTL_STT_TDATA_LEN_COORDNAME] = '\n';
  strncpy(strbuf, stt_tdata->coord_name, IGTL_STT_TDATA_LEN_COORDNAME);

  this->SetCoordinateName(strbuf);

  return 1;

}


//----------------------------------------------------------------------
// igtl::RTSTrackingDataMessageBase class

int  RTSTrackingDataMessageBase::GetBodyPackSize()
{ 
  return IGTL_RTS_TDATA_SIZE; 
}

int  RTSTrackingDataMessageBase::PackBody()
{
  AllocatePack(); 

  igtl_rts_tdata* rts_tdata = (igtl_rts_tdata*)this->m_Body;

  rts_tdata->status = this->m_Status;

  igtl_rts_tdata_convert_byte_order(rts_tdata);

  return 1; 
}


int  RTSTrackingDataMessageBase::UnpackBody()
{ 
  igtl_rts_tdata* rts_tdata = (igtl_rts_tdata*)this->m_Body;
  
  igtl_rts_tdata_convert_byte_order(rts_tdata);

  this->m_Status= rts_tdata->status;

  return 1; 
}



//----------------------------------------------------------------------
// igtl::TrackingDataMessageBase class

TrackingDataMessageBase::TrackingDataMessageBase():
  MessageBase()
{
  //this->m_DefaultBodyType = "TDATA";
  this->m_TrackingDataList.clear();
}


TrackingDataMessageBase::~TrackingDataMessageBase()
{
}


int TrackingDataMessageBase::AddTrackingDataElementBase(TrackingDataElementBase * elem)
{
  this->m_TrackingDataList.push_back(elem);
  return this->m_TrackingDataList.size();
}


void TrackingDataMessageBase::ClearTrackingDataElementBase()
{
  this->m_TrackingDataList.clear();
}


int TrackingDataMessageBase::GetNumberOfTrackingDataElementBase()
{
  return this->m_TrackingDataList.size();
}


TrackingDataElementBase* TrackingDataMessageBase::GetTrackingDataElementBase(int index)
{
  if (index >= 0 && index < (int)this->m_TrackingDataList.size())
    {
    return this->m_TrackingDataList[index].GetPointer();
    }
  else
    {
    return NULL;
    }
}


} // namespace igtl





