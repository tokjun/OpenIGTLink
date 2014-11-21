/*=========================================================================

  Program:   The OpenIGTLink Library
  Language:  C++
  Web page:  http://openigtlink.org/

  Copyright (c) Insight Software Consortium. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "igtlQuaternionTrackingDataMessage.h"
#include "igtlMath.h"

#include "igtl_header.h"
#include "igtl_qtdata.h"

// Disable warning C4996 (strncpy() may be unsafe) in Windows. 
#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <vector>

namespace igtl {


//----------------------------------------------------------------------
// igtl::QuaternionTrackingDataElement class

void QuaternionTrackingDataElement::SetPosition(float p[3])
{
  this->m_position[0] = p[0];
  this->m_position[1] = p[1];
  this->m_position[2] = p[2];
}


void QuaternionTrackingDataElement::GetPosition(float p[3])
{
  p[0] = this->m_position[0];
  p[1] = this->m_position[1];
  p[2] = this->m_position[2];
}


void QuaternionTrackingDataElement::SetPosition(float px, float py, float pz)
{
  this->m_position[0] = px;
  this->m_position[1] = py;
  this->m_position[2] = pz;
}


void QuaternionTrackingDataElement::GetPosition(float* px, float* py, float* pz)
{
  *px = this->m_position[0];
  *py = this->m_position[1];
  *pz = this->m_position[2];
}


void QuaternionTrackingDataElement::SetMatrix(Matrix4x4& mat)
{
  igtl::MatrixToQuaternion(mat, this->m_quaternion);
  this->m_position[0] = mat[0][3];
  this->m_position[1] = mat[1][3];
  this->m_position[2] = mat[2][3];
}


void QuaternionTrackingDataElement::GetMatrix(Matrix4x4& mat)
{
  igtl::QuaternionToMatrix(this->m_quaternion, mat);

  mat[0][3] = this->m_position[0];
  mat[1][3] = this->m_position[1];
  mat[2][3] = this->m_position[2];
  mat[3][3] = 1;
}


void QuaternionTrackingDataElement::SetQuaternion(float q[4])
{
  this->m_quaternion[0] = q[0];
  this->m_quaternion[1] = q[1];
  this->m_quaternion[2] = q[2];
  this->m_quaternion[3] = q[3];
}


void QuaternionTrackingDataElement::GetQuaternion(float q[4])
{
  q[0] = this->m_quaternion[0];
  q[1] = this->m_quaternion[1];
  q[2] = this->m_quaternion[2];
  q[3] = this->m_quaternion[3];
}


void QuaternionTrackingDataElement::SetQuaternion(float qx, float qy, float qz, float w)
{
  this->m_quaternion[0] = qx;
  this->m_quaternion[1] = qy;
  this->m_quaternion[2] = qz;
  this->m_quaternion[3] = w;
}


void QuaternionTrackingDataElement::GetQuaternion(float* qx, float* qy, float* qz, float* w)
{
  *qx = this->m_quaternion[0];
  *qy = this->m_quaternion[1];
  *qz = this->m_quaternion[2];
  *w  = this->m_quaternion[3];
}


void QuaternionTrackingDataElement::Identity()
{
  this->m_quaternion[0] = 0;
  this->m_quaternion[1] = 0;
  this->m_quaternion[2] = 1;
  this->m_quaternion[3] = 0;

  this->m_position[0] = 0;
  this->m_position[1] = 0;
  this->m_position[2] = 1;
}


//----------------------------------------------------------------------
// igtl::QuaternionTrackingDataMessage class

int QuaternionTrackingDataMessage::AddQuaternionTrackingDataElement(QuaternionTrackingDataElement::Pointer& elem)
{
  return this->AddTrackingDataElementBase(elem); 
}


void QuaternionTrackingDataMessage::ClearQuaternionTrackingDataElements()
{
  this->ClearTrackingDataElementBase(); 
}


int QuaternionTrackingDataMessage::GetNumberOfQuaternionTrackingDataElements()
{
  return this->GetNumberOfTrackingDataElementBase(); 
}


void QuaternionTrackingDataMessage::GetQuaternionTrackingDataElement(int index, QuaternionTrackingDataElement::Pointer& elem)
{
  elem = dynamic_cast<QuaternionTrackingDataElement*>(this->GetTrackingDataElementBase(index));
}


int QuaternionTrackingDataMessage::GetBodyPackSize()
{
  // The body size sum of the header size and status message size.
  return IGTL_QTDATA_ELEMENT_SIZE * this->m_TrackingDataList.size();
}


int QuaternionTrackingDataMessage::PackBody()
{
  // allocate pack
  AllocatePack();
  
  igtl_qtdata_element* element;
  element = (igtl_qtdata_element*)this->m_Body;
  std::vector<TrackingDataElementBase::Pointer>::iterator iter;

  for (iter = this->m_TrackingDataList.begin(); iter != this->m_TrackingDataList.end(); iter ++)
    {
    strncpy((char*)element->name, (*iter)->GetName(), IGTL_QTDATA_LEN_NAME);
    element->type = (*iter)->GetType();

    float p[3];
    (*iter)->GetPosition(p);
    float q[4];
    (*iter)->GetQuaternion(q);

    for (int i = 0; i < 3; i ++)
      {
      element->position[i] = p[i];
      }
    for (int j = 0; j < 4; j ++)
      {
      element->quaternion[j] = q[j];
      }

    element ++;
    }
  
  igtl_qtdata_convert_byte_order((igtl_qtdata_element*)this->m_Body, this->m_TrackingDataList.size());
  
  return 1;
}


int QuaternionTrackingDataMessage::UnpackBody()
{

  this->m_TrackingDataList.clear();

  igtl_qtdata_element* element = (igtl_qtdata_element*) this->m_Body;
  int nElement = igtl_qtdata_get_data_n(this->m_BodySizeToRead);

  igtl_qtdata_convert_byte_order(element, nElement);
  
  char strbuf[128];
  for (int i = 0; i < nElement; i ++)
    {
    QuaternionTrackingDataElement::Pointer elemClass = QuaternionTrackingDataElement::New();

    // Add '\n' at the end of each string
    // (neccesary for a case, where a string reaches the maximum length.)
    strbuf[IGTL_QTDATA_LEN_NAME] = '\n';
    strncpy(strbuf, (char*)element->name, IGTL_QTDATA_LEN_NAME);
    elemClass->SetName((const char*)strbuf);
    elemClass->SetType(element->type);

    float p[3] = {0, 0, 0};
    float q[4] = {0, 0, 0, 1};

    for (int i = 0; i < 3; i ++)
      {
      p[i] = element->position[i];
      }
    for (int j = 0; j < 4; j ++)
      {
      q[j] = element->quaternion[j];
      }

    elemClass->SetPosition(p);
    elemClass->SetQuaternion(q);

    this->m_TrackingDataList.push_back(dynamic_cast<TrackingDataElementBase *>(elemClass.GetPointer()));

    element ++;
    }

  return 1;
}

} // namespace igtl





