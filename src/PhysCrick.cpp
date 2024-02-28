// Copyright (c) 2024 Krispin Davies
// SPDX-License-Identifier: BSD-3-Clause

#include "PhysCrick.h"

// This function simply goes through all of the BODY variables and sets them to zero.
void kSim::Sim_Crick_Struct::Sim_Body_Struct::reset() {
	m_Pos_X = 0; m_Pos_Y = 0; m_Pos_Z= 0;
	m_Vel_X = 0; m_Vel_Y = 0; m_Vel_Z= 0;
	m_Accel_X = 0; m_Accel_Y = 0; m_Accel_Z = 0;
	m_Pos_Quat1 = 1; m_Pos_Quat2 = 0; m_Pos_Quat3 = 0; m_Pos_Quat4 = 0;
	m_Vel_Quat1 = 0; m_Vel_Quat2 = 0; m_Vel_Quat3 = 0; m_Vel_Quat4 = 0;
	m_Accel_Quat1 = 0; m_Accel_Quat2 = 0; m_Accel_Quat3 = 0; m_Accel_Quat4 = 0;
	m_ExtF_X = 0; m_ExtF_Y = 0; m_ExtF_Z = 0;
	m_ExtM_X = 0; m_ExtM_Y = 0; m_ExtM_Z = 0;
}

void kSim::Sim_Crick_Struct::Sim_Body_Struct::operator=(const Sim_Body_Struct& In) {
	m_Pos_X = In.m_Pos_X; m_Pos_Y = In.m_Pos_Y; m_Pos_Z = In.m_Pos_Z;
	m_Vel_X = In.m_Vel_X; m_Vel_Y = In.m_Vel_Y; m_Vel_Z = In.m_Vel_Z;
	m_Accel_X = In.m_Accel_X; m_Accel_Y = In.m_Accel_Y; m_Accel_Z = In.m_Accel_Z;
	m_Pos_Quat1 = In.m_Pos_Quat1; m_Pos_Quat2 = In.m_Pos_Quat2; m_Pos_Quat3 = In.m_Pos_Quat3; m_Pos_Quat4 = In.m_Pos_Quat4;
	m_Vel_Quat1 = In.m_Vel_Quat1; m_Vel_Quat2 = In.m_Vel_Quat2; m_Vel_Quat3 = In.m_Vel_Quat3; m_Vel_Quat4 = In.m_Vel_Quat4;
	m_Accel_Quat1 = In.m_Accel_Quat1; m_Accel_Quat2 = In.m_Accel_Quat2; m_Accel_Quat3 = In.m_Accel_Quat3; m_Accel_Quat4 = In.m_Accel_Quat4;
	m_ExtF_X = In.m_ExtF_X; m_ExtF_Y = In.m_ExtF_Y; m_ExtF_Z = In.m_ExtF_Z;
	m_ExtM_X = In.m_ExtM_X; m_ExtM_Y = In.m_ExtM_Y; m_ExtM_Z = In.m_ExtM_Z;
}

// This function simply goes through all of the non-BODY segment's variables and sets them to zero.
void kSim::Sim_Crick_Struct::Sim_Seg_Struct::reset() {
	m_Joint_Angle = 0; m_Joint_Vel = 0; m_Joint_Accel = 0; m_Joint_Torque = 0;
	m_ExtF_X = 0; m_ExtF_Y = 0; m_ExtF_Z = 0;
	m_ExtM_X = 0; m_ExtM_Y = 0; m_ExtM_Z = 0;
}

void kSim::Sim_Crick_Struct::Sim_Seg_Struct::operator=(const Sim_Seg_Struct& In) {
	m_Joint_Angle = In.m_Joint_Angle; m_Joint_Vel = In.m_Joint_Vel; m_Joint_Accel = In.m_Joint_Accel; m_Joint_Torque = In.m_Joint_Torque;
	m_ExtF_X = In.m_ExtF_X; m_ExtF_Y = In.m_ExtF_Y; m_ExtF_Z = In.m_ExtF_Z;
	m_ExtM_X = In.m_ExtM_X; m_ExtM_Y = In.m_ExtM_Y; m_ExtM_Z = In.m_ExtM_Z;
}

// This function goes through each of the segments and calls their respective reset() functions, then sets the mode to YPR.
void kSim::Sim_Crick_Struct::reset() {
	m_BDY.reset();
	m_CAM.reset();
	m_RFS.reset(); m_RFP.reset(); m_RFD.reset(); m_RFT.reset();
	m_LFS.reset(); m_LFP.reset(); m_LFD.reset(); m_LFT.reset();
	m_RRS.reset(); m_RRP.reset(); m_RRD.reset(); m_RRT.reset();
	m_LRS.reset(); m_LRP.reset(); m_LRD.reset(); m_LRT.reset();
	m_RFS.m_Joint_Angle = PI;
	m_RRS.m_Joint_Angle = PI;
	m_RFP.m_Joint_Angle = PI;
	m_LFP.m_Joint_Angle = PI;
	m_RRP.m_Joint_Angle = PI;
	m_LRP.m_Joint_Angle = PI;
	m_RFD.m_Joint_Angle = PI;
	m_LFD.m_Joint_Angle = PI;
	m_RRD.m_Joint_Angle = PI;
	m_LRD.m_Joint_Angle = PI;
	m_RRT.m_Joint_Angle = PI;
	m_LRT.m_Joint_Angle = PI;

}

void kSim::Sim_Crick_Struct::operator=(const Sim_Crick_Struct& In) {
	m_BDY = In.m_BDY;
	m_CAM = In.m_CAM;
	m_RFS = In.m_RFS; m_RFP = In.m_RFP; m_RFD = In.m_RFD; m_RFT = In.m_RFT;
	m_LFS = In.m_LFS; m_LFP = In.m_LFP; m_LFD = In.m_LFD; m_LFT = In.m_LFT;
	m_RRS = In.m_RRS; m_RRP = In.m_RRP; m_RRD = In.m_RRD; m_RRT = In.m_RRT;
	m_LRS = In.m_LRS; m_LRP = In.m_LRP; m_LRD = In.m_LRD; m_LRT = In.m_LRT;
}


