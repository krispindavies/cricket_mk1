// Copyright (c) 2024 Krispin Davies
// SPDX-License-Identifier: BSD-3-Clause

#ifndef PHYSCRICK_H_
#define PHYSCRICK_H_

#include <iostream>
#include <cmath>

#include "kMath.h"

namespace kSim {

	// Thrown error class declarations.
	class Misuse_Error { }; // kSim
	class Range_Error { }; // kSim

	static const double PI = 3.1415926535898;

	struct Sim_Crick_Struct {

		// This is an internally used struct for storing the body variables.
		struct Sim_Body_Struct {
			double m_Pos_X, m_Pos_Y, m_Pos_Z;
			double m_Vel_X, m_Vel_Y, m_Vel_Z;
			double m_Accel_X, m_Accel_Y, m_Accel_Z;
			double m_Pos_Quat1, m_Pos_Quat2, m_Pos_Quat3, m_Pos_Quat4;
			double m_Vel_Quat1, m_Vel_Quat2, m_Vel_Quat3, m_Vel_Quat4;
			double m_Accel_Quat1, m_Accel_Quat2, m_Accel_Quat3, m_Accel_Quat4;
			double m_ExtF_X, m_ExtF_Y, m_ExtF_Z;
			double m_ExtM_X, m_ExtM_Y, m_ExtM_Z;
			Sim_Body_Struct() { this->reset(); } // Constructor.
			void reset(); // Sets all values back to zero.
			void operator=(const Sim_Body_Struct& In); // Copy constructor.
		};

		// This is an internally used struct for storing the each non-body segment's variables.
		struct Sim_Seg_Struct {
			double m_Joint_Angle, m_Joint_Vel, m_Joint_Accel, m_Joint_Torque;
			double m_ExtF_X, m_ExtF_Y, m_ExtF_Z;
			double m_ExtM_X, m_ExtM_Y, m_ExtM_Z;
			Sim_Seg_Struct() { this->reset(); } // Constructor.
			void reset(); // Sets all member variables to zero.
			void operator=(const Sim_Seg_Struct& In); // Copy constructor
		};

	public:

		// Member variables
		Sim_Body_Struct m_BDY;
		Sim_Seg_Struct m_CAM;
		Sim_Seg_Struct m_RFS, m_RFP, m_RFD, m_RFT;
		Sim_Seg_Struct m_LFS, m_LFP, m_LFD, m_LFT;
		Sim_Seg_Struct m_RRS, m_RRP, m_RRD, m_RRT;
		Sim_Seg_Struct m_LRS, m_LRP, m_LRD, m_LRT;

		// Constructor
		Sim_Crick_Struct() { this->reset(); }

		// Sets all member variables to zero, and m_Mode to YPR.
		void reset();

		// Assignment Operator
		void operator=(const Sim_Crick_Struct& In);

		// Acceleration Calculation Functions.
		void calcAccelQuat();
	private:
		void calcAccelQuatStg1(kMath::kMatrix& equations, double* VL);
		void calcAccelQuatStg2(kMath::kMatrix& equations, double* VL);
	};



}

#endif /* PHYSCRICK_H_ */


