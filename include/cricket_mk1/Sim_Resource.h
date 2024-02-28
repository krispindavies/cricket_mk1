// Copyright (c) 2024 Krispin Davies
// SPDX-License-Identifier: BSD-3-Clause

#ifndef SIM_RESOURCE_H_
#define SIM_RESOURCE_H_

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <freeglut.h>

#include "kMath.h"
#include "PhysCrick.h"

namespace kSim {

	// Declarations of classes created herein.
	struct Sim_Env_Struct;
	struct Contact_List;
	struct Sim_Struct;
	class Sim_Hardware;

///////////////////////////////////////////////////////////////////////
// Drawing List Functions.
///////////////////////////////////////////////////////////////////////
	GLuint drawList_Box();
	GLuint drawList_BDY();
	GLuint drawList_RFS();
	GLuint drawList_RFP();
	GLuint drawList_RFD();
	GLuint drawList_RFT();

///////////////////////////////////////////////////////////////////////
// Environment Storage Structure
///////////////////////////////////////////////////////////////////////

	struct Sim_Env_Struct {

		// Internally used structure for representing a single box within the environment.
		struct Sim_Env_Box {
			double m_low_x, m_low_y, m_low_z;
			double m_high_x, m_high_y, m_high_z;
			GLfloat* m_GLtrans;
			Sim_Env_Box() { m_low_x = 0; m_low_y = 0; m_low_z = 0; m_high_x = 0; m_high_y = 0; m_high_z = 0; m_GLtrans = NULL;}
		};

		double m_length_x;
		double m_width_y;
		double m_height_z;

	private:

		int m_cells_x;
		int m_cells_y;
		Sim_Env_Box* floor_Array;
		Sim_Env_Box* ceiling_Array;

	public:

		// Constructor/Destructor
		Sim_Env_Struct(double length_x, double width_y, double height_z, double max_dimension, double floor_thickness);
		~Sim_Env_Struct();

		// Access operators based on an x and y position.
		Sim_Env_Box& getFloor(double x, double y);
		Sim_Env_Box& getCeiling(double x, double y);

		// Access operators based on array indicies.
		int getCellCount() { return m_cells_x*m_cells_y; }
		Sim_Env_Box& getFloor(int target) { return floor_Array[target]; }
		Sim_Env_Box& getCeiling(int target) { return ceiling_Array[target]; }

		// Definition operators allowing you to set the z dimension based on x and y position.
		void setFloor(double x, double y, double z);
		void setCeiling(double x, double y, double z);
	};

///////////////////////////////////////////////////////////////////////
// Cricket Contact Point List Container
///////////////////////////////////////////////////////////////////////

	struct Contact_List {

		// Internally used container for a single contact node.
		struct Contact_Node {
			double m_pos_x, m_pos_y, m_pos_z;
			double m_norm_x, m_norm_y, m_norm_z;
			double m_surf_area;
			Contact_Node() {m_pos_x = 0; m_pos_y = 0; m_pos_z = 0; m_norm_x = 0; m_norm_y = 0; m_norm_z = 0; m_surf_area = 0;}
		};

	private:

		Contact_Node* m_node_list;
		int m_size;
		int m_counter;

	public:

		// Constructors/Destructor
		Contact_List() { m_node_list = NULL; this->reset();}
		Contact_List(const Contact_List&);
		~Contact_List() { delete[] m_node_list; }

		// Access operator.
		const Contact_Node& operator()(int i) const {if(i >= 0 && i < m_counter) return m_node_list[i]; else throw Range_Error();}

		// Assignment operator.
		void operator=(const Contact_List&);

		// Returns the number of contact nodes in the list.
		int get_size() const {return m_counter;}

		// Clears the node list.
		void reset() {if(m_node_list != NULL) delete[] m_node_list; m_node_list = NULL; m_size = 0; m_counter = 0;}

		// Resizes the list if needed and adds a new entry.
		void add(const kMath::hVector& vertex, const kMath::hVector& normal, const double& surf_area);

		void addTriangle(const kMath::hVector& vertex_1, const kMath::hVector& vertex_2, const kMath::hVector& vertex_3, const kMath::hVector& normal);

	};

///////////////////////////////////////////////////////////////////////
// Simulation Containiner.
///////////////////////////////////////////////////////////////////////
	struct Sim_Struct {

		// Enumerators for holding the environmental display parameters.
		enum Env_Disp_Mode_Enum { Environment, Map };
		enum Crick_Disp_Mode_Enum { Graphics, Contacts };

		// Public Variables
		Sim_Env_Struct m_environment;
		Sim_Crick_Struct m_cricket;
		Contact_List m_track_contacts;
		double m_sim_time, m_last_vid_frame_time;
		Env_Disp_Mode_Enum m_env_disp_mode;
		Crick_Disp_Mode_Enum m_crick_disp_mode;
		double m_display_pitch, m_display_yaw, m_display_zoom;
		bool m_SR_image;
		int m_image_width, m_image_height;
		kMath::hVector* m_image_data;
		int m_cutoff_count;

	public:

		// Constructor/Destructor.
		Sim_Struct(double floor_x_dim, double floor_y_dim, double floor_z_dim, double crick_pos_x, double crick_pos_y, double crick_pos_z);
		~Sim_Struct() { if(m_image_data != NULL) delete[] m_image_data; }

		// Function for updating the simulation until a specific time based on the currently supplied configurations list.
		//void Sim_Update(double until_time);

	// Private functions for conducting force calculations.
	private:

		// Builds the contact lists during the initialisation process.
		void Build_Contacts();

		// Called in order to determine the motor torques for the Cricket. (This determines the current target configuration, and target joint velocities.)
		void Calc_Torques(kSim::Sim_Crick_Struct& In_Crick);

		// A sub-function which determines the force imposed on a single contact node by a single environmental object (box).
		kMath::hVector Calc_Force(kSim::Sim_Env_Struct::Sim_Env_Box curr_floor_node, kMath::hVector contact_node_pos, kMath::hVector contact_node_vel, kMath::hVector contact_node_normal, double contact_area);

		// Called in order to determine the external forces imposed on one body segment of the Cricket by the environment.
		void Calc_ExtFM_RFT(kSim::Sim_Crick_Struct& In_Crick, double& max_vel);
		void Calc_ExtFM_LFT(kSim::Sim_Crick_Struct& In_Crick, double& max_vel);
		void Calc_ExtFM_RRT(kSim::Sim_Crick_Struct& In_Crick, double& max_vel);
		void Calc_ExtFM_LRT(kSim::Sim_Crick_Struct& In_Crick, double& max_vel);

	public:
		// Function for incrementing Simulation time by one calculation.
		void Sim_Step();

		void Display();
	};

///////////////////////////////////////////////////////////////////////
// Simulated Hardware Module.
///////////////////////////////////////////////////////////////////////
	class Sim_Hardware {

	};

}

#endif /* SIM_RESOURCE_H_ */
