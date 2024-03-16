// Copyright (c) 2024 Krispin Davies
// SPDX-License-Identifier: BSD-3-Clause

#ifndef KOS_CONTROLLER_H_
#define KOS_CONTROLLER_H_

#include <freeglut.h>

#include <cmath>
#include <iostream>

#include "kMath.h"

namespace KOS
{

// Typedefs for easily changing the representation of interger and decimal
// values used by kMath.
typedef double KOS_DEC;  // Decimal

static const double ERROR_BOUND_95_PCT = 0.05;

enum Module_Identifier
{
  e_Message_Hub,
  e_Hardware,
  e_Situational,
  e_Motion
};

// Thrown error class declarations.
class Misuse_Error
{
};  // KOS
class Range_Error
{
};  // KOS

// Classes Defined Herein
struct KOS_Cricket_Struct;
struct KOS_Message_Struct;
class KOS_Message_Hub;
class KOS_Hub_Inbox;
class KOS_Hardware;
class KOS_Hardware_Inbox;
class KOS_Situational;
class KOS_Situational_Inbox;
class KOS_Motion;
class KOS_Motion_Inbox;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// General Data Structures
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct KOS_Cricket_Struct
{
  double BDY_pos_x, BDY_pos_y, BDY_pos_z;
  double BDY_yaw, BDY_pitch, BDY_roll;
  double CAM;
  double RFS, RFP, RFD, RFT;
  double LFS, LFP, LFD, LFT;
  double RRS, RRP, RRD, RRT;
  double LRS, LRP, LRD, LRT;
  KOS_Cricket_Struct()
  {
    BDY_pos_x = 0;
    BDY_pos_y = 0;
    BDY_pos_z = 0;
    BDY_yaw = 0;
    BDY_pitch = 0;
    BDY_roll = 0;
    CAM = 0;
    RFS = 0;
    RFP = 0;
    RFD = 0;
    RFT = 0;
    LFS = 0;
    LFP = 0;
    LFD = 0;
    LFT = 0;
    RRS = 0;
    RRP = 0;
    RRD = 0;
    RRT = 0;
    LRS = 0;
    LRP = 0;
    LRD = 0;
    LRT = 0;
  }
};

struct KOS_SR4K_Image
{
  kMath::hVector m_data[176 * 144];
};

struct KOS_Message_Struct
{
  Module_Identifier destination;
  Module_Identifier origin;
  std::string message_type;
  double time_of_origin;
  void* data1;
  void* data2;
  void* data3;
  KOS_Message_Struct()
  {
    message_type = "";
    time_of_origin = 0.0;
    data1 = NULL;
    data2 = NULL;
    data3 = NULL;
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// KOS_Message_Hub - KOS' Central Post Office for Messages
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Standardized Inbox Class
class KOS_Hub_Inbox
{
  struct message_linklist_node
  {
    message_linklist_node* m_next;
    KOS_Message_Struct* m_message;
    message_linklist_node(KOS_Message_Struct* in)
    {
      m_next = NULL;
      m_message = in;
    }
  };
  message_linklist_node* top_message;
  int message_count;

public:
  KOS_Hub_Inbox()
  {
    top_message = NULL;
    message_count = 0;
  }
  ~KOS_Hub_Inbox()
  {
    message_linklist_node* temp;
    while (top_message != NULL)
    {
      temp = top_message->m_next;
      delete top_message;
      top_message = temp;
    }
  }
  void add_message(KOS_Message_Struct* new_message)
  {
    if (top_message == NULL)
    {
      top_message = new message_linklist_node(new_message);
    }
    else
    {
      message_linklist_node* temp = top_message;
      while (temp->m_next != NULL)
        temp = temp->m_next;
      temp->m_next = new message_linklist_node(new_message);
    }
    message_count++;
  }
  KOS_Message_Struct* get_message()
  {
    if (top_message == NULL)
    {
      return NULL;
    }
    else
    {
      message_linklist_node* temp = top_message;
      top_message = top_message->m_next;
      message_count--;
      return temp->m_message;
    }
  }
  bool check_message()
  {
    if (top_message == NULL)
      return false;
    else
      return true;
  }
};

class KOS_Message_Hub
{
  // Private Member Variables
  KOS_Hardware_Inbox* m_hardware;
  KOS_Situational_Inbox* m_situational;
  KOS_Motion_Inbox* m_motion;

  // Private Member Functions

public:
  // Public Member Variables
  KOS_Hub_Inbox m_inbox;

  // Public Member Functions
  KOS_Message_Hub()
  {
    m_hardware = NULL;
    m_situational = NULL;
    m_motion = NULL;
  }
  void set_hardware_outbox(KOS_Hardware_Inbox* new_outbox)
  {
    m_hardware = new_outbox;
  }
  void set_situational_outbox(KOS_Situational_Inbox* new_outbox)
  {
    m_situational = new_outbox;
  }
  void set_motion_outbox(KOS_Motion_Inbox* new_outbox)
  {
    m_motion = new_outbox;
  }
  void process_message();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// KOS_Hardware - KOS' Hardware Interface Class
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Standardized Inbox Class
class KOS_Hardware_Inbox
{
  struct message_linklist_node
  {
    message_linklist_node* m_next;
    KOS_Message_Struct* m_message;
    message_linklist_node(KOS_Message_Struct* in)
    {
      m_next = NULL;
      m_message = in;
    }
  };
  message_linklist_node* top_message;
  int message_count;

public:
  KOS_Hardware_Inbox()
  {
    top_message = NULL;
    message_count = 0;
  }
  ~KOS_Hardware_Inbox()
  {
    message_linklist_node* temp;
    while (top_message != NULL)
    {
      temp = top_message->m_next;
      delete top_message;
      top_message = temp;
    }
  }
  void add_message(KOS_Message_Struct* new_message)
  {
    if (top_message == NULL)
    {
      top_message = new message_linklist_node(new_message);
    }
    else
    {
      message_linklist_node* temp = top_message;
      while (temp->m_next != NULL)
        temp = temp->m_next;
      temp->m_next = new message_linklist_node(new_message);
    }
    message_count++;
  }
  KOS_Message_Struct* get_message()
  {
    if (top_message == NULL)
    {
      return NULL;
    }
    else
    {
      message_linklist_node* temp = top_message;
      top_message = top_message->m_next;
      message_count--;
      return temp->m_message;
    }
  }
  bool check_message()
  {
    if (top_message == NULL)
      return false;
    else
      return true;
  }
};

class KOS_Hardware
{
  // Private Member Variables
  KOS_Hub_Inbox* m_outbox;

  // Private Member Functions

public:
  // Public Member Variables
  KOS_Hardware_Inbox m_inbox;

  // Public Member Functions
  KOS_Hardware()
  {
    m_outbox = NULL;
  }
  void set_outbox(KOS_Hub_Inbox* new_outbox)
  {
    m_outbox = new_outbox;
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// KOS_Situational - KOS' Situational Awareness Module Primary Class
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const static int SubGrid_Cell_Div = 8;             // Number of cell divisions per dimension.
const static KOS_DEC SubGrid_Measurements = 0.20;  // Measured length of a subgrid along each dimension.
const static KOS_DEC Default_Occupancy = 0.3;      // Default occupancy for any given location in the map where no
                                                   // previous occupancy data is available.
const static KOS_DEC Default_Confidence = 0.0;     // Default confidence for any given location in the map where no
                                                   // previous confidence data is available.
const static KOS_DEC Learning_Rate = 1.0;          // Neural Network Learning Rate.
const static int Num_Map_Layers = 1;  // Number of layers present within the CMAC style behaviour of the map.

// Standardized Inbox Class
class KOS_Situational_Inbox
{
  struct message_linklist_node
  {
    message_linklist_node* m_next;
    KOS_Message_Struct* m_message;
    message_linklist_node(KOS_Message_Struct* in)
    {
      m_next = NULL;
      m_message = in;
    }
  };
  message_linklist_node* top_message;
  int message_count;

public:
  KOS_Situational_Inbox()
  {
    top_message = NULL;
    message_count = 0;
  }
  ~KOS_Situational_Inbox()
  {
    message_linklist_node* temp;
    while (top_message != NULL)
    {
      temp = top_message->m_next;
      delete top_message;
      top_message = temp;
    }
  }
  void add_message(KOS_Message_Struct* new_message)
  {
    if (top_message == NULL)
    {
      top_message = new message_linklist_node(new_message);
    }
    else
    {
      message_linklist_node* temp = top_message;
      while (temp->m_next != NULL)
        temp = temp->m_next;
      temp->m_next = new message_linklist_node(new_message);
    }
    message_count++;
  }
  KOS_Message_Struct* get_message()
  {
    if (top_message == NULL)
    {
      return NULL;
    }
    else
    {
      message_linklist_node* temp = top_message;
      top_message = top_message->m_next;
      message_count--;
      return temp->m_message;
    }
  }
  bool check_message()
  {
    if (top_message == NULL)
      return false;
    else
      return true;
  }
};

class KOS_SubGrid
{
  KOS_DEC* m_occupancy;
  KOS_DEC* m_confidence;

public:
  KOS_SubGrid(KOS_DEC occupancy);
  ~KOS_SubGrid();
  KOS_DEC get_data(const int x, const int y, const int z) const
  {
    return m_occupancy[int(x * std::pow(SubGrid_Cell_Div, 2) + y * SubGrid_Cell_Div + z)];
  }  // Constant retrieval operator.
  void train(const int x,
             const int y,
             const int z,
             const KOS_DEC sensor_conf,
             const KOS_DEC sensed_occ);  // Training function given sensor inputs.
  KOS_DEC get_avg();                     // Function which returns the average of all elements of
                                         // the subgrid.
};

class KOS_ExoGrid_X
{
  int m_cell_count, m_zero_cell;
  KOS_SubGrid** m_data;

public:
  KOS_ExoGrid_X()
  {
    m_cell_count = 2;
    m_zero_cell = 1;
    m_data = new KOS_SubGrid*[m_cell_count];
    m_data[0] = new KOS_SubGrid(Default_Occupancy);
    m_data[1] = new KOS_SubGrid(Default_Occupancy);
  }
  ~KOS_ExoGrid_X()
  {
    for (int i = 0; i < m_cell_count; i++)
    {
      delete m_data[i];
    }
    delete[] m_data;
  }
  KOS_DEC get_data(const KOS_DEC x_pos, const int y, const int z);
  void train(const KOS_DEC x_pos, const int y, const int z, const KOS_DEC sensor_conf, const KOS_DEC sensed_occ);
};

class KOS_ExoGrid_Y
{
  int m_cell_count, m_zero_cell;
  KOS_ExoGrid_X** m_data;

public:
  KOS_ExoGrid_Y()
  {
    m_cell_count = 2;
    m_zero_cell = 1;
    m_data = new KOS_ExoGrid_X*[m_cell_count];
    m_data[0] = new KOS_ExoGrid_X;
    m_data[1] = new KOS_ExoGrid_X;
  }
  ~KOS_ExoGrid_Y()
  {
    for (int i = 0; i < m_cell_count; i++)
    {
      delete m_data[i];
    }
    delete[] m_data;
  }
  KOS_DEC get_data(const KOS_DEC x_pos, const KOS_DEC y_pos, const int z);
  void
  train(const KOS_DEC x_pos, const KOS_DEC y_pos, const int z, const KOS_DEC sensor_conf, const KOS_DEC sensed_occ);
};

class KOS_ExoGrid_Z
{
  int m_cell_count, m_zero_cell;
  KOS_ExoGrid_Y** m_data;

public:
  KOS_ExoGrid_Z()
  {
    m_cell_count = 2;
    m_zero_cell = 1;
    m_data = new KOS_ExoGrid_Y*[m_cell_count];
    m_data[0] = new KOS_ExoGrid_Y;
    m_data[1] = new KOS_ExoGrid_Y;
  }
  ~KOS_ExoGrid_Z()
  {
    for (int i = 0; i < m_cell_count; i++)
    {
      delete m_data[i];
    }
    delete[] m_data;
  }
  KOS_DEC get_data(const KOS_DEC x_pos, const KOS_DEC y_pos, const KOS_DEC z_pos);
  void train(const KOS_DEC x_pos,
             const KOS_DEC y_pos,
             const KOS_DEC z_pos,
             const KOS_DEC sensor_conf,
             const KOS_DEC sensed_occ);
};

class KOS_Map
{
  KOS_ExoGrid_Z* m_data;

public:
  KOS_Map()
  {
    m_data = new KOS_ExoGrid_Z[Num_Map_Layers];
  }
  ~KOS_Map()
  {
    delete[] m_data;
  }
  KOS_DEC get_data(const KOS_DEC x_pos, const KOS_DEC y_pos, const KOS_DEC z_pos);
  void train(const kMath::hVector pos, const KOS_DEC sensor_conf, const KOS_DEC sensed_occ);
};

class KOS_Situational
{
  // Private Member Variables
  KOS_Map m_map;
  KOS_Cricket_Struct m_cricket;
  KOS_Hub_Inbox* m_outbox;

  // Private Member Functions

public:
  // Public Member Variables
  const static KOS_DEC Dist_Per_Train_Poll = 0.01;
  KOS_Situational_Inbox m_inbox;

  // Public Access Functions
  KOS_Situational()
  {
    m_outbox = NULL;
  }
  KOS_DEC get_map_occupancy(const KOS_DEC x_pos, const KOS_DEC y_pos, const KOS_DEC z_pos)
  {
    return m_map.get_data(x_pos, y_pos, z_pos);
  }  // Depricated function, used to draw the map in the simulator.
  void set_outbox(KOS_Hub_Inbox* new_outbox)
  {
    m_outbox = new_outbox;
  }
  void process_message();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// KOS_Motion - KOS' Motion Planning Module Primary Class
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Standardized Inbox Class
class KOS_Motion_Inbox
{
  struct message_linklist_node
  {
    message_linklist_node* m_next;
    KOS_Message_Struct* m_message;
    message_linklist_node(KOS_Message_Struct* in)
    {
      m_next = NULL;
      m_message = in;
    }
  };
  message_linklist_node* top_message;
  int message_count;

public:
  KOS_Motion_Inbox()
  {
    top_message = NULL;
    message_count = 0;
  }
  ~KOS_Motion_Inbox()
  {
    message_linklist_node* temp;
    while (top_message != NULL)
    {
      temp = top_message->m_next;
      delete top_message;
      top_message = temp;
    }
  }
  void add_message(KOS_Message_Struct* new_message)
  {
    if (top_message == NULL)
    {
      top_message = new message_linklist_node(new_message);
    }
    else
    {
      message_linklist_node* temp = top_message;
      while (temp->m_next != NULL)
        temp = temp->m_next;
      temp->m_next = new message_linklist_node(new_message);
    }
    message_count++;
  }
  KOS_Message_Struct* get_message()
  {
    if (top_message == NULL)
    {
      return NULL;
    }
    else
    {
      message_linklist_node* temp = top_message;
      top_message = top_message->m_next;
      message_count--;
      return temp->m_message;
    }
  }
  bool check_message()
  {
    if (top_message == NULL)
      return false;
    else
      return true;
  }
};

class KOS_Motion
{
};
}  // namespace KOS

#endif /* KOS_CONTROLLER_H_ */
