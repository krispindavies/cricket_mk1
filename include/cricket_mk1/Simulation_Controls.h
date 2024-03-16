// Copyright (c) 2024 Krispin Davies
// SPDX-License-Identifier: BSD-3-Clause

#ifndef SIMULATION_CONTROLS_H_
#define SIMULATION_CONTROLS_H_

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// Simulated Camera Properties
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#define SR_CAM_NEAR_PLANE_COORD 0.02
#define SR_CAM_FAR_PLANE_COORD 3.4
#define SR_CAM_PIXEL_WIDTH 176
#define SR_CAM_PIXEL_HEIGHT 144
#define SR_CAM_MIN_RANGE 0.0
#define SR_CAM_MAX_RANGE 3.0
#define SR_CAM_ERROR_FACTOR 0.00

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// User View Properties
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#define USER_NEAR_PLANE_COORD 0.1
#define USER_FAR_PLANE_COORD 10.0
#define MODEL_SIM_FPS 30.0
#define MODEL_CONTACT_DIM 0.005
#define MODEL_CONTACT_NORM_LENGTH 0.01
#define MODEL_GRAPHICS_ROUNDNESS 5  // Number of straight segments used to approximate a half circle.

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// Simulated Environment Properties
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#define MODEL_Gravity -9.81
#define MODEL_MAX_CONTACT_AREA 0.04
#define MODEL_MAX_CONTACT_SIDE_LENGTH 0.03
#define MODEL_ENV_SPRING_COEFF (6.6 * std::pow(10, 9))
#define MODEL_ENV_DAMPING_COEFF (1.0 * std::pow(10, 10))
#define MODEL_ENV_FRICT_COEFF_STATIC 1.4
#define MODEL_ENV_FRICT_COEFF_DYNAMIC 0.8

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// Simulation Calculation Properties
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#define MODEL_BASE_TIME_STEP (1.0 / 1000.0)
#define MODEL_MAX_DISTANCE_STEP 0.01
#define MODEL_MAX_VELOCITY_STEP 0.1
#define MODEL_EQN_DISPLAY_FLAG false

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// Cricket Model Properties
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// Body
#define MODEL_BDY_Origin_X 0.0  // This is included only for standardization.
#define MODEL_BDY_Origin_Y 0.0
#define MODEL_BDY_Origin_Z 0.0
#define MODEL_BDY_COG_X 0.0  // COG Location in Body Space
#define MODEL_BDY_COG_Y 0.0
#define MODEL_BDY_COG_Z 0.0
#define MODEL_BDY_MASS 4.12         // Mass
#define MODEL_BDY_I_XX 0.035598039  // I in Body Space
#define MODEL_BDY_I_YY 0.053971915
#define MODEL_BDY_I_ZZ 0.884455685

#define MODEL_BDY_HEIGHT 0.078         // From top to bottom
#define MODEL_BDY_CAGE_WIDTH 0.174     // From left of sensor cage to right.
#define MODEL_BDY_CAGE_LENGTH 0.406    // From front of sensor cage to back.
#define MODEL_BDY_BRIDGE_WIDTH 0.252   // From left half cylinder centreline to right half cylinder centreline.
#define MODEL_BDY_BRIDGE_LENGTH 0.096  // From front of body bridge to back.

// Camera
#define MODEL_CAM_Origin_X 0.169  // Joint Location in Body Space
#define MODEL_CAM_Origin_Y 0.0
#define MODEL_CAM_Origin_Z 0.0
#define MODEL_CAM_COG_X 0.0  // COG Location in Camera Space
#define MODEL_CAM_COG_Y 0.0
#define MODEL_CAM_COG_Z 0.0
#define MODEL_CAM_MASS 0.470   // Mass
#define MODEL_CAM_I_XX 0.0002  // I in Camera Space
#define MODEL_CAM_I_YY 0.0002
#define MODEL_CAM_I_ZZ 0.0002

#define MODEL_CAM_HEIGHT 0.065  // From top to bottom
#define MODEL_CAM_WIDTH 0.065   // From left to right
#define MODEL_CAM_LENGTH 0.068  // From front to back

// Shoulders
#define MODEL_RFS_Origin_X 0.048  // Joint Location in Body Space
#define MODEL_RFS_Origin_Y -0.126
#define MODEL_RFS_Origin_Z 0.0
#define MODEL_RFS_COG_X 0.07346  // COG Location in RFS Space
#define MODEL_RFS_COG_Y 0.01204
#define MODEL_RFS_COG_Z 0.00569
#define MODEL_RFS_MASS 0.468        // Mass
#define MODEL_RFS_I_XX 0.000182876  // I in RFS Space
#define MODEL_RFS_I_YY 0.000521037
#define MODEL_RFS_I_ZZ 0.000512402

#define MODEL_LFS_Origin_X 0.048  // Joint Location in Body Space
#define MODEL_LFS_Origin_Y 0.126
#define MODEL_LFS_Origin_Z 0.0
#define MODEL_LFS_COG_X 0.07346  // COG Location in LFS Space
#define MODEL_LFS_COG_Y 0.01204
#define MODEL_LFS_COG_Z 0.00569
#define MODEL_LFS_MASS 0.468        // Mass
#define MODEL_LFS_I_XX 0.000182876  // I in LFS Space
#define MODEL_LFS_I_YY 0.000521037
#define MODEL_LFS_I_ZZ 0.000512402

#define MODEL_RRS_Origin_X -0.048  // Joint Location in Body Space
#define MODEL_RRS_Origin_Y -0.126
#define MODEL_RRS_Origin_Z 0.0
#define MODEL_RRS_COG_X -0.07346  // COG Location in RRS Space
#define MODEL_RRS_COG_Y 0.01204
#define MODEL_RRS_COG_Z 0.00569
#define MODEL_RRS_MASS 0.468        // Mass
#define MODEL_RRS_I_XX 0.000182876  // I in RRS Space
#define MODEL_RRS_I_YY 0.000521037
#define MODEL_RRS_I_ZZ 0.000512402

#define MODEL_LRS_Origin_X -0.048  // Joint Location in Body Space
#define MODEL_LRS_Origin_Y 0.126
#define MODEL_LRS_Origin_Z 0.0
#define MODEL_LRS_COG_X -0.07346  // COG Location in LRS Space
#define MODEL_LRS_COG_Y 0.01204
#define MODEL_LRS_COG_Z 0.00569
#define MODEL_LRS_MASS 0.468        // Mass
#define MODEL_LRS_I_XX 0.000182876  // I in LRS Space
#define MODEL_LRS_I_YY 0.000521037
#define MODEL_LRS_I_ZZ 0.000512402

#define MODEL_SHLD_CYL_DIA 0.07      // Diameter of the shoulder cylinder.
#define MODEL_SHLD_CYL_LENGTH 0.125  // Length of the shoulder cylinder.
#define MODEL_SHLD_BOX_LENGTH 0.06   // From front of shoulder cylinder to back of box.
#define MODEL_SHLD_BOX_WIDTH 0.04    // From centre to box furthest Y position.
#define MODEL_SHLD_BOX_HEIGHT 0.05   // From box bottom to top.

// Proximal
#define MODEL_RFP_Origin_X 0.106  // Joint Location in RFS Space
#define MODEL_RFP_Origin_Y 0.039
#define MODEL_RFP_Origin_Z 0.0
#define MODEL_RFP_COG_X 0.09271  // COG Location in RFP Space
#define MODEL_RFP_COG_Y 0.03409
#define MODEL_RFP_COG_Z 0.00625
#define MODEL_RFP_MASS 0.558        // Mass
#define MODEL_RFP_I_XX 0.000241567  // I in RFP Space
#define MODEL_RFP_I_YY 0.000890644
#define MODEL_RFP_I_ZZ 0.000948128

#define MODEL_LFP_Origin_X 0.106  // Joint Location in LFS Space
#define MODEL_LFP_Origin_Y 0.039
#define MODEL_LFP_Origin_Z 0.0
#define MODEL_LFP_COG_X 0.09271  // COG Location in LFP Space
#define MODEL_LFP_COG_Y 0.03409
#define MODEL_LFP_COG_Z 0.00625
#define MODEL_LFP_MASS 0.558        // Mass
#define MODEL_LFP_I_XX 0.000241567  // I in LFP Space
#define MODEL_LFP_I_YY 0.000890644
#define MODEL_LFP_I_ZZ 0.000948128

#define MODEL_RRP_Origin_X -0.106  // Joint Location in RRS Space
#define MODEL_RRP_Origin_Y 0.039
#define MODEL_RRP_Origin_Z 0.0
#define MODEL_RRP_COG_X 0.09271  // COG Location in RRP Space
#define MODEL_RRP_COG_Y 0.03409
#define MODEL_RRP_COG_Z 0.00625
#define MODEL_RRP_MASS 0.558        // Mass
#define MODEL_RRP_I_XX 0.000241567  // I in RRP Space
#define MODEL_RRP_I_YY 0.000890644
#define MODEL_RRP_I_ZZ 0.000948128

#define MODEL_LRP_Origin_X -0.106  // Joint Location in LRS Space
#define MODEL_LRP_Origin_Y 0.039
#define MODEL_LRP_Origin_Z 0.0
#define MODEL_LRP_COG_X 0.09271  // COG Location in LRP Space
#define MODEL_LRP_COG_Y 0.03409
#define MODEL_LRP_COG_Z 0.00625
#define MODEL_LRP_MASS 0.558        // Mass
#define MODEL_LRP_I_XX 0.000241567  // I in LRP Space
#define MODEL_LRP_I_YY 0.000890644
#define MODEL_LRP_I_ZZ 0.000948128

#define MODEL_PRX_ARM_LENGTH 0.15   // From origin axis centreline to front end of box.
#define MODEL_PRX_ARM_HEIGHT 0.03   // From top to bottom of the thin section.
#define MODEL_PRX_ARM_WIDTH 0.016   // From left to right to thin section.
#define MODEL_PRX_BOX_LENGTH 0.10   // From front of box to back of box.
#define MODEL_PRX_BOX_HEIGHT 0.065  // From top to bottom of the box.
#define MODEL_PRX_BOX_WIDTH 0.063   // From left to right of the box.

// Distal
#define MODEL_RFD_Origin_X 0.133  // Joint Location in RFP Space
#define MODEL_RFD_Origin_Y 0.0635
#define MODEL_RFD_Origin_Z 0.0
#define MODEL_RFD_COG_X 0.1364  // COG Location in RFD Space
#define MODEL_RFD_COG_Y -0.0029
#define MODEL_RFD_COG_Z 0.0037
#define MODEL_RFD_MASS 0.552        // Mass
#define MODEL_RFD_I_XX 0.000184014  // I in RFD Space
#define MODEL_RFD_I_YY 0.001586338
#define MODEL_RFD_I_ZZ 0.001594024

#define MODEL_LFD_Origin_X 0.133  // Joint Location in LFP Space
#define MODEL_LFD_Origin_Y 0.0635
#define MODEL_LFD_Origin_Z 0.0
#define MODEL_LFD_COG_X 0.1364  // COG Location in LFD Space
#define MODEL_LFD_COG_Y -0.0029
#define MODEL_LFD_COG_Z 0.0037
#define MODEL_LFD_MASS 0.552        // Mass
#define MODEL_LFD_I_XX 0.000184014  // I in LFD Space
#define MODEL_LFD_I_YY 0.001586338
#define MODEL_LFD_I_ZZ 0.001594024

#define MODEL_RRD_Origin_X 0.133  // Joint Location in RRP Space
#define MODEL_RRD_Origin_Y 0.0635
#define MODEL_RRD_Origin_Z 0.0
#define MODEL_RRD_COG_X 0.1364  // COG Location in RRD Space
#define MODEL_RRD_COG_Y -0.0029
#define MODEL_RRD_COG_Z 0.0037
#define MODEL_RRD_MASS 0.552        // Mass
#define MODEL_RRD_I_XX 0.000184014  // I in RRD Space
#define MODEL_RRD_I_YY 0.001586338
#define MODEL_RRD_I_ZZ 0.001594024

#define MODEL_LRD_Origin_X 0.133  // Joint Location in LRP Space
#define MODEL_LRD_Origin_Y 0.0635
#define MODEL_LRD_Origin_Z 0.0
#define MODEL_LRD_COG_X 0.1364  // COG Location in LRD Space
#define MODEL_LRD_COG_Y -0.0029
#define MODEL_LRD_COG_Z 0.0037
#define MODEL_LRD_MASS 0.552        // Mass
#define MODEL_LRD_I_XX 0.000184014  // I in LRD Space
#define MODEL_LRD_I_YY 0.001586338
#define MODEL_LRD_I_ZZ 0.001594024

#define MODEL_DST_ARM_LENGTH 0.202  // From origin axis centreline to front end of box.
#define MODEL_DST_ARM_HEIGHT 0.031  // From top to bottom of the thin section.
#define MODEL_DST_ARM_WIDTH 0.018   // From left to right to thin section.
#define MODEL_DST_BOX_LENGTH 0.103  // From front of box to back of box.
#define MODEL_DST_BOX_HEIGHT 0.065  // From top to bottom of the box.
#define MODEL_DST_BOX_WIDTH 0.056   // From left to right of the box.

// Track
#define MODEL_RFT_Origin_X 0.185  // Joint Location in RFD Space
#define MODEL_RFT_Origin_Y 0.0185
#define MODEL_RFT_Origin_Z 0.0
#define MODEL_RFT_COG_X 0.1046  // COG Location in RFT Space
#define MODEL_RFT_COG_Y 0.0275
#define MODEL_RFT_COG_Z 0.0004
#define MODEL_RFT_MASS 1.254        // Mass
#define MODEL_RFT_I_XX 0.000561906  // I in RFT Space
#define MODEL_RFT_I_YY 0.006213578
#define MODEL_RFT_I_ZZ 0.006224147

#define MODEL_LFT_Origin_X 0.185  // Joint Location in LFD Space
#define MODEL_LFT_Origin_Y 0.0185
#define MODEL_LFT_Origin_Z 0.0
#define MODEL_LFT_COG_X 0.1046  // COG Location in LFT Space
#define MODEL_LFT_COG_Y 0.0275
#define MODEL_LFT_COG_Z 0.0004
#define MODEL_LFT_MASS 1.254        // Mass
#define MODEL_LFT_I_XX 0.000561906  // I in LFT Space
#define MODEL_LFT_I_YY 0.006213578
#define MODEL_LFT_I_ZZ 0.006224147

#define MODEL_RRT_Origin_X 0.185  // Joint Location in RRD Space
#define MODEL_RRT_Origin_Y 0.0185
#define MODEL_RRT_Origin_Z 0.0
#define MODEL_RRT_COG_X 0.1046  // COG Location in RRT Space
#define MODEL_RRT_COG_Y 0.0275
#define MODEL_RRT_COG_Z 0.0004
#define MODEL_RRT_MASS 1.254        // Mass
#define MODEL_RRT_I_XX 0.000561906  // I in RRT Space
#define MODEL_RRT_I_YY 0.006213578
#define MODEL_RRT_I_ZZ 0.006224147

#define MODEL_LRT_Origin_X 0.185  // Joint Location in LRD Space
#define MODEL_LRT_Origin_Y 0.0185
#define MODEL_LRT_Origin_Z 0.0
#define MODEL_LRT_COG_X 0.1046  // COG Location in LRT Space
#define MODEL_LRT_COG_Y 0.0275
#define MODEL_LRT_COG_Z 0.0004
#define MODEL_LRT_MASS 1.254        // Mass
#define MODEL_LRT_I_XX 0.000561906  // I in LRT Space
#define MODEL_LRT_I_YY 0.006213578
#define MODEL_LRT_I_ZZ 0.006224147

#define MODEL_TRK_LENGTH 0.19   // From front axle to back axle.
#define MODEL_TRK_WIDTH 0.055   // From left side to right side.
#define MODEL_TRK_HEIGHT 0.078  // From top to bottom.

#define MODEL_TOTAL_MASS 15.918

#endif /* CRICKET_MODEL_H_ */
