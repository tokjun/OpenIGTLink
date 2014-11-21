/*=========================================================================

  Program:   The OpenIGTLink Library
  Language:  C++
  Web page:  http://openigtlink.org/

  Copyright (c) Insight Software Consortium. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "igtlTrackingDataMessage.h"
#include "igtlMath.h"

#include "igtl_header.h"
#include "igtl_tdata.h"

// Disable warning C4996 (strncpy() may be unsafe) in Windows. 
#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <vector>

namespace igtl {


//----------------------------------------------------------------------
// igtl::TrackingDataElement class

void TrackingDataElement::SetPosition(float p[3])
{
  this->m_Matrix[0][3] = p[0];
  this->m_Matrix[1][3] = p[1];
  this->m_Matrix[2][3] = p[2];
}


void TrackingDataElement::GetPosition(float p[3])
{
  p[0] = this->m_Matrix[0][3];
  p[1] = this->m_Matrix[1][3];
  p[2] = this->m_Matrix[2][3];
}


void TrackingDataElement::SetPosition(float px, float py, float pz)
{
  this->m_Matrix[0][3] = px;
  this->m_Matrix[1][3] = py;
  this->m_Matrix[2][3] = pz;
}


void TrackingDataElement::GetPosition(float* px, float* py, float* pz)
{
  *px = this->m_Matrix[0][3];
  *py = this->m_Matrix[1][3];
  *pz = this->m_Matrix[2][3];
}


void TrackingDataElement::SetMatrix(Matrix4x4& mat)
{
  m_Matrix[0][0] = mat[0][0];
  m_Matrix[1][0] = mat[1][0];
  m_Matrix[2][0] = mat[2][0];
  m_Matrix[3][0] = mat[3][0];

  m_Matrix[0][1] = mat[0][1];
  m_Matrix[1][1] = mat[1][1];
  m_Matrix[2][1] = mat[2][1];
  m_Matrix[3][1] = mat[3][1];

  m_Matrix[0][2] = mat[0][2];
  m_Matrix[1][2] = mat[1][2];
  m_Matrix[2][2] = mat[2][2];
  m_Matrix[3][2] = mat[3][2];

  m_Matrix[0][3] = mat[0][3];
  m_Matrix[1][3] = mat[1][3];
  m_Matrix[2][3] = mat[2][3];
  m_Matrix[3][3] = mat[3][3];
}


void TrackingDataElement::GetMatrix(Matrix4x4& mat)
{
  mat[0][0] = m_Matrix[0][0];
  mat[1][0] = m_Matrix[1][0];
  mat[2][0] = m_Matrix[2][0];
  mat[3][0] = m_Matrix[3][0];

  mat[0][1] = m_Matrix[0][1];
  mat[1][1] = m_Matrix[1][1];
  mat[2][1] = m_Matrix[2][1];
  mat[3][1] = m_Matrix[3][1];

  mat[0][2] = m_Matrix[0][2];
  mat[1][2] = m_Matrix[1][2];
  mat[2][2] = m_Matrix[2][2];
  mat[3][2] = m_Matrix[3][2];

  mat[0][3] = m_Matrix[0][3];
  mat[1][3] = m_Matrix[1][3];
  mat[2][3] = m_Matrix[2][3];
  mat[3][3] = m_Matrix[3][3];
}


void TrackingDataElement::SetQuaternion(float q[4])
{
  float t[4];

  // Store translation part
  t[0] = m_Matrix[0][3];
  t[1] = m_Matrix[1][3];
  t[2] = m_Matrix[2][3];
  t[3] = m_Matrix[3][3];

  igtl::QuaternionToMatrix(q, m_Matrix);

  // Load translation part
  m_Matrix[0][3] = t[0];
  m_Matrix[1][3] = t[1];
  m_Matrix[2][3] = t[2];
  m_Matrix[3][3] = t[3];
}


void TrackingDataElement::GetQuaternion(float q[4])
{
  igtl::MatrixToQuaternion(m_Matrix, q);
}


void TrackingDataElement::SetQuaternion(float qx, float qy, float qz, float w)
{
  float q[4];

  q[0] = qx;
  q[1] = qy;
  q[2] = qz;
  q[3] = w;
  SetQuaternion(q);
}


void TrackingDataElement::GetQuaternion(float* qx, float* qy, float* qz, float* w)
{
  float q[4];

  igtl::MatrixToQuaternion(m_Matrix, q);
  *qx = q[0];
  *qy = q[1];
  *qz = q[2];
  *w  = q[3];
}


void TrackingDataElement::Identity()
{
  IdentityMatrix(this->m_Matrix);
}


//----------------------------------------------------------------------
// igtl::TrackingDataMessage class


int TrackingDataMessage::AddTrackingDataElement(TrackingDataElement::Pointer& elem)
{
  return this->AddTrackingDataElementBase(elem); 
}
  

void TrackingDataMessage::ClearTrackingDataElements()
{
  this->ClearTrackingDataElementBase(); 
}
  

int TrackingDataMessage::GetNumberOfTrackingDataElements()
{ 
  return this->GetNumberOfTrackingDataElementBase(); 
}

  
void TrackingDataMessage::GetTrackingDataElement(int index, TrackingDataElement::Pointer& elem)
{ 
  elem = dynamic_cast<TrackingDataElement*>(this->GetTrackingDataElementBase(index));
}


int TrackingDataMessage::GetBodyPackSize()
{
  // The body size sum of the header size and status message size.
  return IGTL_TDATA_ELEMENT_SIZE * this->m_TrackingDataList.size();
}


int TrackingDataMessage::PackBody()
{
  // allocate pack
  AllocatePack();
  
  igtl_tdata_element* element;
  element = (igtl_tdata_element*)this->m_Body;
  std::vector<TrackingDataElementBase::Pointer>::iterator iter;

  for (iter = this->m_TrackingDataList.begin(); iter != this->m_TrackingDataList.end(); iter ++)
    {
    strncpy((char*)element->name, (*iter)->GetName(), IGTL_TDATA_LEN_NAME);
    element->type = (*iter)->GetType();

    Matrix4x4 matrix;
    (*iter)->GetMatrix(matrix);
    for (int i = 0; i < 3; i ++)
      {
      element->transform[i]   = matrix[i][0];
      element->transform[i+3] = matrix[i][1];
      element->transform[i+6] = matrix[i][2];
      element->transform[i+9] = matrix[i][3];
      }
    element ++;
    }
  
  igtl_tdata_convert_byte_order((igtl_tdata_element*)this->m_Body, this->m_TrackingDataList.size());
  
  return 1;
}


int TrackingDataMessage::UnpackBody()
{

  this->m_TrackingDataList.clear();

  igtl_tdata_element* element = (igtl_tdata_element*) this->m_Body;
  int nElement = igtl_tdata_get_data_n(this->m_BodySizeToRead);

  igtl_tdata_convert_byte_order(element, nElement);
  
  char strbuf[128];
  for (int i = 0; i < nElement; i ++)
    {
    TrackingDataElement::Pointer elemClass = TrackingDataElement::New();

    // Add '\n' at the end of each string
    // (neccesary for a case, where a string reaches the maximum length.)
    strbuf[IGTL_TDATA_LEN_NAME] = '\n';
    strncpy(strbuf, (char*)element->name, IGTL_TDATA_LEN_NAME);
    elemClass->SetName((const char*)strbuf);
    elemClass->SetType(element->type);

    Matrix4x4 matrix;
    IdentityMatrix(matrix);
    for (int j = 0; j < 3; j ++)
      {
      matrix[j][0] = element->transform[j];
      matrix[j][1] = element->transform[j+3];
      matrix[j][2] = element->transform[j+6];
      matrix[j][3] = element->transform[j+9];
      }
    elemClass->SetMatrix(matrix);

    this->m_TrackingDataList.push_back(dynamic_cast<TrackingDataElement *>(elemClass.GetPointer()));

    element ++;
    }

  return 1;
}

} // namespace igtl





