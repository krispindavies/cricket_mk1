
//----------------------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------------------
#include <iostream>
#include <cmath>
#include <cstdlib>

#include <freeglut.h>

#include "kMath.h"
#include "Sim_Resource.h"
#include "Simulation_Controls.h"
#include "KOS_Controller.h"

//----------------------------------------------------------------------------------
// Global Variables
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
// Function Declarations
//----------------------------------------------------------------------------------

void init();
void display();
void reshape(int w, int h);
void keybrdFunc(unsigned char key, int x, int y);
void simLoop();
kSim::Sim_Struct* Sim_Struct();
KOS::KOS_Message_Hub* Message_Hub();
KOS::KOS_Situational* Situ_Module();
KOS::KOS_Hardware* Hard_Module();
void KOS_Hardware_Handler(double Global_Time);

//----------------------------------------------------------------------------------
// Main
//----------------------------------------------------------------------------------
int main(int argc, char **argv) {
	/*std::cout << "\n Bypassing Normal Operation.\n\n";

	kSim::Sim_Crick_Struct test_crick;

	//test_crick.m_BDY.m_ExtM_Y = 1.0;
	test_crick.m_RFT.m_Joint_Torque = 1.0;
	test_crick.m_LFT.m_Joint_Torque = 1.0;
	test_crick.m_RRT.m_Joint_Torque = 1.0;
	test_crick.m_LRT.m_Joint_Torque = 1.0;

	test_crick.calcAccelQuat();

	return 0;*/


	std::cout << "\n Initialising.\n";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(1000,450);
	glutCreateWindow("Crick_Sim");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keybrdFunc);
	glutIdleFunc(simLoop);

	std::cout << " Initialisation complete.\n\n";

	glutMainLoop();
	return 0;
}

//----------------------------------------------------------------------------------
// Init
//----------------------------------------------------------------------------------

void init() {
	// Define basic OpenGL settings.
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Define basic lighting settings.
	GLfloat lmodel_ambient[] = {0.1, 0.1, 0.1, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	// Initialise simulation.
	Sim_Struct();

	// Initialise Message Hub.
	Message_Hub();

	// Initialise Hardware Module.
	Hard_Module();
	Message_Hub()->set_hardware_outbox(&(Hard_Module()->m_inbox));
	Hard_Module()->set_outbox(&(Message_Hub()->m_inbox));

	// Initialise Situational Awareness Module.
	Situ_Module();
	Message_Hub()->set_situational_outbox(&(Situ_Module()->m_inbox));
	Situ_Module()->set_outbox(&(Message_Hub()->m_inbox));

}

//----------------------------------------------------------------------------------
// Display
//----------------------------------------------------------------------------------

void display() {

	// Test whether we need to render an SR4000 Image.
	if((Sim_Struct()->m_SR_image)) {

		if(Sim_Struct()->m_image_width < SR_CAM_PIXEL_WIDTH || Sim_Struct()->m_image_height < SR_CAM_PIXEL_HEIGHT) {
			std::cout << "\n\n\n WARNING! Window insufficient size to render SR4000 camera images.\n\n\n";
			throw kSim::Misuse_Error();
		}

		// Define viewport position/size.
		glViewport(0, 0, GLsizei(SR_CAM_PIXEL_WIDTH), GLsizei(SR_CAM_PIXEL_HEIGHT));

		// Define Fustrum.
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(43.6, GLfloat(SR_CAM_PIXEL_WIDTH)/GLfloat(SR_CAM_PIXEL_HEIGHT), SR_CAM_NEAR_PLANE_COORD, SR_CAM_FAR_PLANE_COORD);

		// Switch mode back to modelview.
		glMatrixMode(GL_MODELVIEW);

		// Clear the window with background color.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Set up the camera view and lighting.
		// Remember to check whether we're displaying the SR4000 view or a user selected view.
		glLoadIdentity();
		double light_pos_x = 1;
		double light_pos_y = 1;
		double light_pos_z = 1;
		GLfloat light0_position[] = {light_pos_x, light_pos_y, light_pos_z, 1.0};
		glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
		GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
		glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
		glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

		// Determine gluLookAt values.
		kMath::hVector cam_pos, cam_focus, cam_up;
		cam_pos = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Point(MODEL_CAM_Origin_X, MODEL_CAM_Origin_Y, MODEL_CAM_Origin_Z);
		cam_focus = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_CAM_Origin_X, MODEL_CAM_Origin_Y, MODEL_CAM_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_CAM.m_Joint_Angle)*kMath::h_Point(1.0, 0.0, 0.0);
		cam_up = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Roty(Sim_Struct()->m_cricket.m_CAM.m_Joint_Angle)*kMath::h_Point(0.0, 0.0, 1.0);

		// Define camera position.
		gluLookAt(cam_pos(0), cam_pos(1), cam_pos(2), cam_focus(0), cam_focus(1), cam_focus(2), cam_up(0), cam_up(1), cam_up(2));

		// Specify material properties.
		GLfloat box_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
		glMaterialfv(GL_FRONT, GL_AMBIENT, box_ambient);
		GLfloat box_shininess[] = { 5.0 };
		glMaterialfv(GL_FRONT, GL_SHININESS, box_shininess);
		GLfloat box_specular[] = { 0.0, 0.0, 0.0, 1.0 };
		glMaterialfv(GL_FRONT, GL_SPECULAR, box_specular);
		GLfloat box_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, box_diffuse);

		// Remember to cull those objects which are in front of the Cricket so that we can actually see the robot and such.
		for(int i = 0; i < Sim_Struct()->m_environment.getCellCount(); i++) {

			// Floor
			double dot = 0;//(SIMSTRUCT.crick_pos_x() - SIMSTRUCT.cam_pos_x())*(ENVIRONMENT.get_floor(i).get_x() - SIMSTRUCT.crick_pos_x()) + (SIMSTRUCT.crick_pos_y() - SIMSTRUCT.cam_pos_y())*(ENVIRONMENT.get_floor(i).get_y() - SIMSTRUCT.crick_pos_y()) + (SIMSTRUCT.crick_pos_z() - SIMSTRUCT.cam_pos_z())*(ENVIRONMENT.get_floor(i).get_z() - SIMSTRUCT.crick_pos_z());
			if(dot >= 0) {
				glPushMatrix();
				glMultMatrixf(Sim_Struct()->m_environment.getFloor(i).m_GLtrans);
				glCallList(kSim::drawList_Box());
				glPopMatrix();
			}

			// Ceiling
			dot = 0;//(SIMSTRUCT.crick_pos_x() - SIMSTRUCT.cam_pos_x())*(ENVIRONMENT.get_ceiling(i).get_x() - SIMSTRUCT.crick_pos_x()) + (SIMSTRUCT.crick_pos_y() - SIMSTRUCT.cam_pos_y())*(ENVIRONMENT.get_ceiling(i).get_y() - SIMSTRUCT.crick_pos_y()) + (SIMSTRUCT.crick_pos_z() - SIMSTRUCT.cam_pos_z())*(ENVIRONMENT.get_ceiling(i).get_z() - SIMSTRUCT.crick_pos_z());
			if(dot >= 0) {
				glPushMatrix();
				glMultMatrixf(Sim_Struct()->m_environment.getCeiling(i).m_GLtrans);
				glCallList(kSim::drawList_Box());
				glPopMatrix();
			}
		}

		// Actually draw the screen.
		glFlush();

		// Allocate storage for reading buffers and such.
		double objx, objy, objz;
		double modelview[16], projection[16];
		int viewport[4];
		GLfloat z[176*144];

		// Read in the various transformation matricies.
		glGetDoublev( GL_PROJECTION_MATRIX, projection );
		glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
		glGetIntegerv( GL_VIEWPORT, viewport );

		// Read in the depth buffer.
		glReadPixels( 0, 0, 176, 144, GL_DEPTH_COMPONENT, GL_FLOAT, z );

		if(Sim_Struct()->m_image_data != NULL)
			delete[] Sim_Struct()->m_image_data;
		Sim_Struct()->m_image_data = new kMath::hVector[176*144];

		kMath::hMatrix global_to_cam_trans = kMath::h_Roty(-1.0*Sim_Struct()->m_cricket.m_CAM.m_Joint_Angle)*kMath::h_Trans(-MODEL_CAM_Origin_X, -MODEL_CAM_Origin_Y, -MODEL_CAM_Origin_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, -1.0*Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, -1.0*Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, -1.0*Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(-1.0*Sim_Struct()->m_cricket.m_BDY.m_Pos_X, -1.0*Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, -1.0*Sim_Struct()->m_cricket.m_BDY.m_Pos_Z);

		// Transform each pixel into world coordinates and measure distance to camera.
		for( int y = 0; y < 144; y++ ) {
			for( int x = 0; x < 176; x++ ) {

				// Transform pixel to world coordinates.
				gluUnProject( x, y, z[y*176+x], modelview, projection, viewport, &objx, &objy, &objz );

				// Measure position of pixel with respect to camera space.
				Sim_Struct()->m_image_data[y*176+x] = global_to_cam_trans*kMath::h_Point(objx, objy, objz);

				// Clip for maximum and minimum range. In either case, camera should output maximum recordable range.
				if(Sim_Struct()->m_image_data[y*176+x].mag() < SR_CAM_MIN_RANGE || Sim_Struct()->m_image_data[y*176+x].mag() > SR_CAM_MAX_RANGE)
					Sim_Struct()->m_image_data[y*176+x] = kMath::h_Scale(SR_CAM_MAX_RANGE/Sim_Struct()->m_image_data[y*176+x].mag())*Sim_Struct()->m_image_data[y*176+x];

				if((Sim_Struct()->m_image_data[y*176+x])(0) < 0) {
					kMath::h_Point(objx, objy, objz).display();
					(Sim_Struct()->m_image_data[y*176+x]).display();
					std::cout << "\n\nOpenGL is flaking out, resart the program...\n\n";
					//throw kSim::Misuse_Error();
				}

				// Add in random pixel error.
				Sim_Struct()->m_image_data[y*176+x] = kMath::h_Scale((1.0 + 0.1*(std::rand() % 100)/100.0 - 0.05))*Sim_Struct()->m_image_data[y*176+x];

			}
		}
	}

	// ======================================================================
	// Draw user image.
	// ======================================================================

	// Define viewport position/size.
	glViewport(0, 0, (GLsizei) Sim_Struct()->m_image_width, (GLsizei) Sim_Struct()->m_image_height);

	// Define Fustrum.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(Sim_Struct()->m_image_height != 0) {
		gluPerspective(43.6, GLfloat(Sim_Struct()->m_image_width)/GLfloat(Sim_Struct()->m_image_height), USER_NEAR_PLANE_COORD, USER_FAR_PLANE_COORD);
	} else {
		gluPerspective(43.6, GLfloat(Sim_Struct()->m_image_width)/GLfloat(1.0), USER_NEAR_PLANE_COORD, USER_FAR_PLANE_COORD);
	}

	// Switch mode back to modelview.
	glMatrixMode(GL_MODELVIEW);

	// Clear the window with background color.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set up the camera view and lighting.
	// Remember to check whether we're displaying the SR4000 view or a user selected view.
	glLoadIdentity();
	double light_pos_x = 1;
	double light_pos_y = 1;
	double light_pos_z = 1;
	GLfloat light0_position[] = {light_pos_x, light_pos_y, light_pos_z, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	gluLookAt(Sim_Struct()->m_cricket.m_BDY.m_Pos_X - Sim_Struct()->m_display_zoom*std::cos(Sim_Struct()->m_display_pitch)*std::cos(Sim_Struct()->m_display_yaw), Sim_Struct()->m_cricket.m_BDY.m_Pos_Y - Sim_Struct()->m_display_zoom*std::cos(Sim_Struct()->m_display_pitch)*std::sin(Sim_Struct()->m_display_yaw), Sim_Struct()->m_cricket.m_BDY.m_Pos_Z - Sim_Struct()->m_display_zoom*std::sin(Sim_Struct()->m_display_pitch), Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z, 0.0, 0.0, 1.0);

	// Draw Environment.
	switch(Sim_Struct()->m_env_disp_mode) {

		case kSim::Sim_Struct::Environment:
			{
				// Specify material properties.
				GLfloat box_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
				glMaterialfv(GL_FRONT, GL_AMBIENT, box_ambient);
				GLfloat box_shininess[] = { 5.0 };
				glMaterialfv(GL_FRONT, GL_SHININESS, box_shininess);
				GLfloat box_specular[] = { 0.0, 0.0, 0.0, 1.0 };
				glMaterialfv(GL_FRONT, GL_SPECULAR, box_specular);
				GLfloat box_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
				glMaterialfv(GL_FRONT, GL_DIFFUSE, box_diffuse);

				// Remember to cull those objects which are in front of the Cricket so that we can actually see the robot and such.
				for(int i = 0; i < Sim_Struct()->m_environment.getCellCount(); i++) {

					// Floor
					double dot = 0;//(SIMSTRUCT.crick_pos_x() - SIMSTRUCT.cam_pos_x())*(ENVIRONMENT.get_floor(i).get_x() - SIMSTRUCT.crick_pos_x()) + (SIMSTRUCT.crick_pos_y() - SIMSTRUCT.cam_pos_y())*(ENVIRONMENT.get_floor(i).get_y() - SIMSTRUCT.crick_pos_y()) + (SIMSTRUCT.crick_pos_z() - SIMSTRUCT.cam_pos_z())*(ENVIRONMENT.get_floor(i).get_z() - SIMSTRUCT.crick_pos_z());
					if(dot >= 0) {
						glPushMatrix();
						glMultMatrixf(Sim_Struct()->m_environment.getFloor(i).m_GLtrans);
						glCallList(kSim::drawList_Box());
						glPopMatrix();
					}

					// Ceiling
					dot = 0;//(SIMSTRUCT.crick_pos_x() - SIMSTRUCT.cam_pos_x())*(ENVIRONMENT.get_ceiling(i).get_x() - SIMSTRUCT.crick_pos_x()) + (SIMSTRUCT.crick_pos_y() - SIMSTRUCT.cam_pos_y())*(ENVIRONMENT.get_ceiling(i).get_y() - SIMSTRUCT.crick_pos_y()) + (SIMSTRUCT.crick_pos_z() - SIMSTRUCT.cam_pos_z())*(ENVIRONMENT.get_ceiling(i).get_z() - SIMSTRUCT.crick_pos_z());
					if(dot >= 0) {
						glPushMatrix();
						glMultMatrixf(Sim_Struct()->m_environment.getCeiling(i).m_GLtrans);
						glCallList(kSim::drawList_Box());
						glPopMatrix();
					}
				}
			}
			break;

		case kSim::Sim_Struct::Map:
			{

				GLfloat box_shininess[] = { 5.0 };
				glMaterialfv(GL_FRONT, GL_SHININESS, box_shininess);
				GLfloat box_specular[] = { 0.0, 0.0, 0.0, 1.0 };
				glMaterialfv(GL_FRONT, GL_SPECULAR, box_specular);

				float SIM_MAP_ELEM_LENGTH = 0.02;
				int SIM_MAP_ELEM_COUNT = std::ceil(2.0/SIM_MAP_ELEM_LENGTH);

				// Transform.
				GLfloat trans[16];
				trans[0] = SIM_MAP_ELEM_LENGTH;
				trans[1] = 0;
				trans[2] = 0;
				trans[3] = 0;
				trans[4] = 0;
				trans[5] = SIM_MAP_ELEM_LENGTH;
				trans[6] = 0;
				trans[7] = 0;
				trans[8] = 0;
				trans[9] = 0;
				trans[10] = SIM_MAP_ELEM_LENGTH;
				trans[11] = 0;
				trans[12] = 0;
				trans[13] = 0;
				trans[14] = 0;
				trans[15] = 1;

				for(int i = 0; i <= 2*SIM_MAP_ELEM_COUNT; i++) {
					for(int j = 0; j <= 2*SIM_MAP_ELEM_COUNT; j++) {
						for(int k = 0; k <= 2*SIM_MAP_ELEM_COUNT; k++) {
							trans[12] = (i-SIM_MAP_ELEM_COUNT)*SIM_MAP_ELEM_LENGTH + float(Sim_Struct()->m_cricket.m_BDY.m_Pos_X);
							trans[13] = (j-SIM_MAP_ELEM_COUNT)*SIM_MAP_ELEM_LENGTH + float(Sim_Struct()->m_cricket.m_BDY.m_Pos_Y);
							trans[14] = (k-SIM_MAP_ELEM_COUNT)*SIM_MAP_ELEM_LENGTH + float(Sim_Struct()->m_cricket.m_BDY.m_Pos_Z);
							double occ = Situ_Module()->get_map_occupancy(trans[12], trans[13], trans[14]);

							// Specify material properties.
							GLfloat box_ambient[] = { 1.0, 1.0, 1.0, occ };
							glMaterialfv(GL_FRONT, GL_AMBIENT, box_ambient);
							GLfloat box_diffuse[] = { 0.8, 0.8, 0.8, occ };
							glMaterialfv(GL_FRONT, GL_DIFFUSE, box_diffuse);

							if(occ > 0.70) {
								glPushMatrix();
								glMultMatrixf(trans);
								glCallList(kSim::drawList_Box());
								glPopMatrix();
							}
						}
					}
				}
			}
			break;
	}

	switch(Sim_Struct()->m_crick_disp_mode) {

		case kSim::Sim_Struct::Graphics:
			{
				// Draw Body.
				{
					// Specify material properties for BDY.
					GLfloat box_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
					glMaterialfv(GL_FRONT, GL_AMBIENT, box_ambient);
					GLfloat box_shininess[] = { 5.0 };
					glMaterialfv(GL_FRONT, GL_SHININESS, box_shininess);
					GLfloat box_specular[] = { 0.0, 0.0, 0.0, 1.0 };
					glMaterialfv(GL_FRONT, GL_SPECULAR, box_specular);
					GLfloat box_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
					glMaterialfv(GL_FRONT, GL_DIFFUSE, box_diffuse);

					// Draw BDY.
					glPushMatrix();
					kMath::hMatrix Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_BDY());
					glPopMatrix();
				}

				// Draw Shoulders.
				/*{
					// Specify material properties for RFS/LFS/RRS/LRS.
					GLfloat box_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
					glMaterialfv(GL_FRONT, GL_AMBIENT, box_ambient);
					GLfloat box_shininess[] = { 5.0 };
					glMaterialfv(GL_FRONT, GL_SHININESS, box_shininess);
					GLfloat box_specular[] = { 0.0, 0.0, 0.0, 1.0 };
					glMaterialfv(GL_FRONT, GL_SPECULAR, box_specular);
					GLfloat box_diffuse[] = { 1.0, 0.85, 0.0, 1.0 };
					glMaterialfv(GL_FRONT, GL_DIFFUSE, box_diffuse);

					// Draw RFS.
					glPushMatrix();
					kMath::hMatrix Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_RFS_Origin_X,MODEL_RFS_Origin_Y,MODEL_RFS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_RFS.m_Joint_Angle);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_RFS());
					glPopMatrix();

					// Draw LFS.
					glPushMatrix();
					Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_LFS_Origin_X,MODEL_LFS_Origin_Y,MODEL_LFS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_LFS.m_Joint_Angle);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_RFS());
					glPopMatrix();

					// Draw RRS.
					glPushMatrix();
					Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_RRS_Origin_X,MODEL_RRS_Origin_Y,MODEL_RRS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_RRS.m_Joint_Angle)*kMath::h_Scale(-1.0,1.0,1.0);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_RFS());
					glPopMatrix();

					// Draw LRS.
					glPushMatrix();
					Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_LRS_Origin_X,MODEL_LRS_Origin_Y,MODEL_LRS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_LRS.m_Joint_Angle)*kMath::h_Scale(-1.0,1.0,1.0);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_RFS());
					glPopMatrix();
				}

				// Draw Proximals.
				{
					// Specify material properties for RFP/LFP/RRP/LRP.
					GLfloat box_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
					glMaterialfv(GL_FRONT, GL_AMBIENT, box_ambient);
					GLfloat box_shininess[] = { 5.0 };
					glMaterialfv(GL_FRONT, GL_SHININESS, box_shininess);
					GLfloat box_specular[] = { 0.0, 0.0, 0.0, 1.0 };
					glMaterialfv(GL_FRONT, GL_SPECULAR, box_specular);
					GLfloat box_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
					glMaterialfv(GL_FRONT, GL_DIFFUSE, box_diffuse);

					// Draw RFP.
					glPushMatrix();
					kMath::hMatrix Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_RFS_Origin_X,MODEL_RFS_Origin_Y,MODEL_RFS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_RFS.m_Joint_Angle)*kMath::h_Trans(MODEL_RFP_Origin_X,MODEL_RFP_Origin_Y,MODEL_RFP_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RFP.m_Joint_Angle);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_RFP());
					glPopMatrix();

					// Draw LFP.
					glPushMatrix();
					Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_LFS_Origin_X,MODEL_LFS_Origin_Y,MODEL_LFS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_LFS.m_Joint_Angle)*kMath::h_Trans(MODEL_LFP_Origin_X,MODEL_LFP_Origin_Y,MODEL_LFP_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_LFP.m_Joint_Angle);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_RFP());
					glPopMatrix();

					// Draw RRP.
					glPushMatrix();
					Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_RRS_Origin_X,MODEL_RRS_Origin_Y,MODEL_RRS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_RRS.m_Joint_Angle)*kMath::h_Trans(MODEL_RRP_Origin_X,MODEL_RRP_Origin_Y,MODEL_RRP_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RRP.m_Joint_Angle);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_RFP());
					glPopMatrix();

					// Draw LRP.
					glPushMatrix();
					Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_LRS_Origin_X,MODEL_LRS_Origin_Y,MODEL_LRS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_LRS.m_Joint_Angle)*kMath::h_Trans(MODEL_LRP_Origin_X,MODEL_LRP_Origin_Y,MODEL_LRP_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_LRP.m_Joint_Angle);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_RFP());
					glPopMatrix();
				}

				// Draw Distals.
				{
					// Specify material properties for RFD/LFD/RRD/LRD.
					GLfloat box_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
					glMaterialfv(GL_FRONT, GL_AMBIENT, box_ambient);
					GLfloat box_shininess[] = { 5.0 };
					glMaterialfv(GL_FRONT, GL_SHININESS, box_shininess);
					GLfloat box_specular[] = { 0.0, 0.0, 0.0, 1.0 };
					glMaterialfv(GL_FRONT, GL_SPECULAR, box_specular);
					GLfloat box_diffuse[] = { 1.0, 0.85, 0.0, 1.0 };
					glMaterialfv(GL_FRONT, GL_DIFFUSE, box_diffuse);

					// Draw RFD.
					glPushMatrix();
					kMath::hMatrix Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_RFS_Origin_X,MODEL_RFS_Origin_Y,MODEL_RFS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_RFS.m_Joint_Angle)*kMath::h_Trans(MODEL_RFP_Origin_X,MODEL_RFP_Origin_Y,MODEL_RFP_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RFP.m_Joint_Angle)*kMath::h_Trans(MODEL_RFD_Origin_X,MODEL_RFD_Origin_Y,MODEL_RFD_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RFD.m_Joint_Angle);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_RFD());
					glPopMatrix();

					// Draw LFD.
					glPushMatrix();
					Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_LFS_Origin_X,MODEL_LFS_Origin_Y,MODEL_LFS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_LFS.m_Joint_Angle)*kMath::h_Trans(MODEL_LFP_Origin_X,MODEL_LFP_Origin_Y,MODEL_LFP_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_LFP.m_Joint_Angle)*kMath::h_Trans(MODEL_LFD_Origin_X,MODEL_LFD_Origin_Y,MODEL_LFD_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_LFD.m_Joint_Angle);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_RFD());
					glPopMatrix();

					// Draw RRD.
					glPushMatrix();
					Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_RRS_Origin_X,MODEL_RRS_Origin_Y,MODEL_RRS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_RRS.m_Joint_Angle)*kMath::h_Trans(MODEL_RRP_Origin_X,MODEL_RRP_Origin_Y,MODEL_RRP_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RRP.m_Joint_Angle)*kMath::h_Trans(MODEL_RRD_Origin_X,MODEL_RRD_Origin_Y,MODEL_RRD_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RRD.m_Joint_Angle);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_RFD());
					glPopMatrix();

					// Draw LRD.
					glPushMatrix();
					Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_LRS_Origin_X,MODEL_LRS_Origin_Y,MODEL_LRS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_LRS.m_Joint_Angle)*kMath::h_Trans(MODEL_LRP_Origin_X,MODEL_LRP_Origin_Y,MODEL_LRP_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_LRP.m_Joint_Angle)*kMath::h_Trans(MODEL_LRD_Origin_X,MODEL_LRD_Origin_Y,MODEL_LRD_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_LRD.m_Joint_Angle);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_RFD());
					glPopMatrix();
				}

				// Draw Tracks.
				{
					// Specify material properties for RFT/LFT/RRT/LRT.
					GLfloat box_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
					glMaterialfv(GL_FRONT, GL_AMBIENT, box_ambient);
					GLfloat box_shininess[] = { 5.0 };
					glMaterialfv(GL_FRONT, GL_SHININESS, box_shininess);
					GLfloat box_specular[] = { 0.0, 0.0, 0.0, 1.0 };
					glMaterialfv(GL_FRONT, GL_SPECULAR, box_specular);
					GLfloat box_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
					glMaterialfv(GL_FRONT, GL_DIFFUSE, box_diffuse);

					// Draw RFT.
					glPushMatrix();
					kMath::hMatrix Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_RFS_Origin_X,MODEL_RFS_Origin_Y,MODEL_RFS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_RFS.m_Joint_Angle)*kMath::h_Trans(MODEL_RFP_Origin_X,MODEL_RFP_Origin_Y,MODEL_RFP_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RFP.m_Joint_Angle)*kMath::h_Trans(MODEL_RFD_Origin_X,MODEL_RFD_Origin_Y,MODEL_RFD_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RFD.m_Joint_Angle)*kMath::h_Trans(MODEL_RFT_Origin_X,MODEL_RFT_Origin_Y,MODEL_RFT_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RFT.m_Joint_Angle);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_RFT());
					glPopMatrix();

					// Draw LFT.
					glPushMatrix();
					Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_LFS_Origin_X,MODEL_LFS_Origin_Y,MODEL_LFS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_LFS.m_Joint_Angle)*kMath::h_Trans(MODEL_LFP_Origin_X,MODEL_LFP_Origin_Y,MODEL_LFP_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_LFP.m_Joint_Angle)*kMath::h_Trans(MODEL_LFD_Origin_X,MODEL_LFD_Origin_Y,MODEL_LFD_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_LFD.m_Joint_Angle)*kMath::h_Trans(MODEL_LFT_Origin_X,MODEL_LFT_Origin_Y,MODEL_LFT_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_LFT.m_Joint_Angle);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_RFT());
					glPopMatrix();

					// Draw RRT
					glPushMatrix();
					Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_RRS_Origin_X,MODEL_RRS_Origin_Y,MODEL_RRS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_RRS.m_Joint_Angle)*kMath::h_Trans(MODEL_RRP_Origin_X,MODEL_RRP_Origin_Y,MODEL_RRP_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RRP.m_Joint_Angle)*kMath::h_Trans(MODEL_RRD_Origin_X,MODEL_RRD_Origin_Y,MODEL_RRD_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RRD.m_Joint_Angle)*kMath::h_Trans(MODEL_RRT_Origin_X,MODEL_RRT_Origin_Y,MODEL_RRT_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RRT.m_Joint_Angle);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_RFT());
					glPopMatrix();

					// Draw LRT
					glPushMatrix();
					Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_LRS_Origin_X,MODEL_LRS_Origin_Y,MODEL_LRS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_LRS.m_Joint_Angle)*kMath::h_Trans(MODEL_LRP_Origin_X,MODEL_LRP_Origin_Y,MODEL_LRP_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_LRP.m_Joint_Angle)*kMath::h_Trans(MODEL_LRD_Origin_X,MODEL_LRD_Origin_Y,MODEL_LRD_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_LRD.m_Joint_Angle)*kMath::h_Trans(MODEL_LRT_Origin_X,MODEL_LRT_Origin_Y,MODEL_LRT_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_LRT.m_Joint_Angle);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_RFT());
					glPopMatrix();
				}*/

				// Draw Simplified Tracks.
				{
					// Specify material properties for RFT/LFT.
					GLfloat box_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
					glMaterialfv(GL_FRONT, GL_AMBIENT, box_ambient);
					GLfloat box_shininess[] = { 5.0 };
					glMaterialfv(GL_FRONT, GL_SHININESS, box_shininess);
					GLfloat box_specular[] = { 0.0, 0.0, 0.0, 1.0 };
					glMaterialfv(GL_FRONT, GL_SPECULAR, box_specular);
					GLfloat box_diffuse[] = { 1.0, 0.85, 0.0, 1.0 };
					glMaterialfv(GL_FRONT, GL_DIFFUSE, box_diffuse);

					// Draw RFT.
					glPushMatrix();
					kMath::hMatrix Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(0.250,-0.150,0.0)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RFT.m_Joint_Angle)*kMath::h_Scale(1.0,-1.0,1.0);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_RFT());
					glPopMatrix();

					// Draw LFT.
					glPushMatrix();
					Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(0.250,0.150,0.0)*kMath::h_Roty(Sim_Struct()->m_cricket.m_LFT.m_Joint_Angle);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_RFT());
					glPopMatrix();
				}

				{
					// Specify material properties for RRT/LRT.
					GLfloat box_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
					glMaterialfv(GL_FRONT, GL_AMBIENT, box_ambient);
					GLfloat box_shininess[] = { 5.0 };
					glMaterialfv(GL_FRONT, GL_SHININESS, box_shininess);
					GLfloat box_specular[] = { 0.0, 0.0, 0.0, 1.0 };
					glMaterialfv(GL_FRONT, GL_SPECULAR, box_specular);
					GLfloat box_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
					glMaterialfv(GL_FRONT, GL_DIFFUSE, box_diffuse);

					// Draw RRT
					glPushMatrix();
					kMath::hMatrix Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(-0.250,-0.150,0.0)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RRT.m_Joint_Angle)*kMath::h_Scale(1.0,-1.0,1.0);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_RFT());
					glPopMatrix();

					// Draw LRT
					glPushMatrix();
					Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(-0.250,0.150,0.0)*kMath::h_Roty(Sim_Struct()->m_cricket.m_LRT.m_Joint_Angle);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_RFT());
					glPopMatrix();
				}

			}
			break;

		case kSim::Sim_Struct::Contacts:
			{

				// Specify material properties.
				GLfloat box_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
				glMaterialfv(GL_FRONT, GL_AMBIENT, box_ambient);
				GLfloat box_shininess[] = { 5.0 };
				glMaterialfv(GL_FRONT, GL_SHININESS, box_shininess);
				GLfloat box_specular[] = { 0.0, 0.0, 0.0, 1.0 };
				glMaterialfv(GL_FRONT, GL_SPECULAR, box_specular);
				GLfloat box_diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
				glMaterialfv(GL_FRONT, GL_DIFFUSE, box_diffuse);

				// Draw RFT contacts.
				for(int i = 0; i < Sim_Struct()->m_track_contacts.get_size(); i++) {
					glPushMatrix();
					kMath::hMatrix Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_RFS_Origin_X,MODEL_RFS_Origin_Y,MODEL_RFS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_RFS.m_Joint_Angle)*kMath::h_Trans(MODEL_RFP_Origin_X,MODEL_RFP_Origin_Y,MODEL_RFP_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RFP.m_Joint_Angle)*kMath::h_Trans(MODEL_RFD_Origin_X,MODEL_RFD_Origin_Y,MODEL_RFD_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RFD.m_Joint_Angle)*kMath::h_Trans(MODEL_RFT_Origin_X,MODEL_RFT_Origin_Y,MODEL_RFT_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RFT.m_Joint_Angle)*kMath::h_Trans(Sim_Struct()->m_track_contacts(i).m_pos_x,Sim_Struct()->m_track_contacts(i).m_pos_y,Sim_Struct()->m_track_contacts(i).m_pos_z)*kMath::h_Scale(MODEL_CONTACT_DIM);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_Box());
					glPopMatrix();
					glBegin(GL_LINES);
						kMath::hVector Line_Start = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_RFS_Origin_X,MODEL_RFS_Origin_Y,MODEL_RFS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_RFS.m_Joint_Angle)*kMath::h_Trans(MODEL_RFP_Origin_X,MODEL_RFP_Origin_Y,MODEL_RFP_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RFP.m_Joint_Angle)*kMath::h_Trans(MODEL_RFD_Origin_X,MODEL_RFD_Origin_Y,MODEL_RFD_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RFD.m_Joint_Angle)*kMath::h_Trans(MODEL_RFT_Origin_X,MODEL_RFT_Origin_Y,MODEL_RFT_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RFT.m_Joint_Angle)*kMath::h_Point(Sim_Struct()->m_track_contacts(i).m_pos_x,Sim_Struct()->m_track_contacts(i).m_pos_y,Sim_Struct()->m_track_contacts(i).m_pos_z);
						glVertex3f(Line_Start(0), Line_Start(1), Line_Start(2));
						kMath::hVector Line_End = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_RFS_Origin_X,MODEL_RFS_Origin_Y,MODEL_RFS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_RFS.m_Joint_Angle)*kMath::h_Trans(MODEL_RFP_Origin_X,MODEL_RFP_Origin_Y,MODEL_RFP_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RFP.m_Joint_Angle)*kMath::h_Trans(MODEL_RFD_Origin_X,MODEL_RFD_Origin_Y,MODEL_RFD_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RFD.m_Joint_Angle)*kMath::h_Trans(MODEL_RFT_Origin_X,MODEL_RFT_Origin_Y,MODEL_RFT_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RFT.m_Joint_Angle)*kMath::h_Trans(Sim_Struct()->m_track_contacts(i).m_pos_x,Sim_Struct()->m_track_contacts(i).m_pos_y,Sim_Struct()->m_track_contacts(i).m_pos_z)*kMath::h_Scale(MODEL_CONTACT_NORM_LENGTH)*kMath::h_Point(Sim_Struct()->m_track_contacts(i).m_norm_x,Sim_Struct()->m_track_contacts(i).m_norm_y,Sim_Struct()->m_track_contacts(i).m_norm_z);
						glVertex3f(Line_End(0), Line_End(1), Line_End(2));
					glEnd();
				}

				// Draw LFT contacts.
				for(int i = 0; i < Sim_Struct()->m_track_contacts.get_size(); i++) {
					glPushMatrix();
					kMath::hMatrix Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_LFS_Origin_X,MODEL_LFS_Origin_Y,MODEL_LFS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_LFS.m_Joint_Angle)*kMath::h_Trans(MODEL_LFP_Origin_X,MODEL_LFP_Origin_Y,MODEL_LFP_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_LFP.m_Joint_Angle)*kMath::h_Trans(MODEL_LFD_Origin_X,MODEL_LFD_Origin_Y,MODEL_LFD_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_LFD.m_Joint_Angle)*kMath::h_Trans(MODEL_LFT_Origin_X,MODEL_LFT_Origin_Y,MODEL_LFT_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_LFT.m_Joint_Angle)*kMath::h_Trans(Sim_Struct()->m_track_contacts(i).m_pos_x,Sim_Struct()->m_track_contacts(i).m_pos_y,Sim_Struct()->m_track_contacts(i).m_pos_z)*kMath::h_Scale(MODEL_CONTACT_DIM);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_Box());
					glPopMatrix();
				}

				// Draw RRT contacts.
				for(int i = 0; i < Sim_Struct()->m_track_contacts.get_size(); i++) {
					glPushMatrix();
					kMath::hMatrix Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_RRS_Origin_X,MODEL_RRS_Origin_Y,MODEL_RRS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_RRS.m_Joint_Angle)*kMath::h_Trans(MODEL_RRP_Origin_X,MODEL_RRP_Origin_Y,MODEL_RRP_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RRP.m_Joint_Angle)*kMath::h_Trans(MODEL_RRD_Origin_X,MODEL_RRD_Origin_Y,MODEL_RRD_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RRD.m_Joint_Angle)*kMath::h_Trans(MODEL_RRT_Origin_X,MODEL_RRT_Origin_Y,MODEL_RRT_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_RRT.m_Joint_Angle)*kMath::h_Trans(Sim_Struct()->m_track_contacts(i).m_pos_x,Sim_Struct()->m_track_contacts(i).m_pos_y,Sim_Struct()->m_track_contacts(i).m_pos_z)*kMath::h_Scale(MODEL_CONTACT_DIM);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_Box());
					glPopMatrix();
				}

				// Draw LRT contacts.
				for(int i = 0; i < Sim_Struct()->m_track_contacts.get_size(); i++) {
					glPushMatrix();
					kMath::hMatrix Global_Trans = kMath::h_Trans(Sim_Struct()->m_cricket.m_BDY.m_Pos_X, Sim_Struct()->m_cricket.m_BDY.m_Pos_Y, Sim_Struct()->m_cricket.m_BDY.m_Pos_Z)*kMath::h_RotQuat(Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat1, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat2, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat3, Sim_Struct()->m_cricket.m_BDY.m_Pos_Quat4)*kMath::h_Trans(MODEL_LRS_Origin_X,MODEL_LRS_Origin_Y,MODEL_LRS_Origin_Z)*kMath::h_Rotx(Sim_Struct()->m_cricket.m_LRS.m_Joint_Angle)*kMath::h_Trans(MODEL_LRP_Origin_X,MODEL_LRP_Origin_Y,MODEL_LRP_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_LRP.m_Joint_Angle)*kMath::h_Trans(MODEL_LRD_Origin_X,MODEL_LRD_Origin_Y,MODEL_LRD_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_LRD.m_Joint_Angle)*kMath::h_Trans(MODEL_LRT_Origin_X,MODEL_LRT_Origin_Y,MODEL_LRT_Origin_Z)*kMath::h_Roty(Sim_Struct()->m_cricket.m_LRT.m_Joint_Angle)*kMath::h_Trans(Sim_Struct()->m_track_contacts(i).m_pos_x,Sim_Struct()->m_track_contacts(i).m_pos_y,Sim_Struct()->m_track_contacts(i).m_pos_z)*kMath::h_Scale(MODEL_CONTACT_DIM);
					glMultMatrixf(Global_Trans.OGL());
					glCallList(kSim::drawList_Box());
					glPopMatrix();
				}


			}
			break;
	}

	// Actually Draw the screen.
	glFlush();
}

//----------------------------------------------------------------------------------
// Reshape
//----------------------------------------------------------------------------------

void reshape(int w, int h) {

	Sim_Struct()->m_image_width = w;
	Sim_Struct()->m_image_height = h;

	// Force OpenGL to redraw the scene.
	glutPostRedisplay();
}

//----------------------------------------------------------------------------------
// Keyboard Function
//----------------------------------------------------------------------------------

void keybrdFunc(unsigned char key, int x, int y) {
	if(!(Sim_Struct()->m_SR_image)) {
		switch(key) {
			case 't':
			case 'T':
				std::cout << "\n Current time: " << Sim_Struct()->m_sim_time << "\n";
				glutPostRedisplay();
				break;
			case 'w':
			case 'W':
				Sim_Struct()->m_display_pitch -= 0.05*kSim::PI;
				if(Sim_Struct()->m_display_pitch < -0.45*kSim::PI)
					Sim_Struct()->m_display_pitch = -0.45*kSim::PI;
				glutPostRedisplay();
				break;
			case 'a':
			case 'A':
				Sim_Struct()->m_display_yaw -= 0.05*kSim::PI;
				glutPostRedisplay();
				break;
			case 's':
			case 'S':
				Sim_Struct()->m_display_pitch += 0.05*kSim::PI;
				if(Sim_Struct()->m_display_pitch > 0.45*kSim::PI)
					Sim_Struct()->m_display_pitch = 0.45*kSim::PI;
				glutPostRedisplay();
				break;
			case 'd':
			case 'D':
				Sim_Struct()->m_display_yaw += 0.05*kSim::PI;
				glutPostRedisplay();
				break;
			case 'r':
			case 'R':
				Sim_Struct()->m_display_zoom -= 0.2;
				if(Sim_Struct()->m_display_zoom < 0.2)
					Sim_Struct()->m_display_zoom = 0.2;
				glutPostRedisplay();
				break;
			case 'f':
			case 'F':
				Sim_Struct()->m_display_zoom += 0.2;
				if(Sim_Struct()->m_display_zoom > 3.0)
					Sim_Struct()->m_display_zoom = 3.0;
				glutPostRedisplay();
				break;
			case 'y':
			case 'Y':
				switch(Sim_Struct()->m_env_disp_mode) {
				case kSim::Sim_Struct::Environment:
					Sim_Struct()->m_env_disp_mode = kSim::Sim_Struct::Map;
					break;
				case kSim::Sim_Struct::Map:
					Sim_Struct()->m_env_disp_mode = kSim::Sim_Struct::Environment;
					break;
				}
				glutPostRedisplay();
				break;
			case 'u':
			case 'U':
				switch(Sim_Struct()->m_crick_disp_mode) {
				case kSim::Sim_Struct::Graphics:
					Sim_Struct()->m_crick_disp_mode = kSim::Sim_Struct::Contacts;
					break;
				case kSim::Sim_Struct::Contacts:
					Sim_Struct()->m_crick_disp_mode = kSim::Sim_Struct::Graphics;
					break;
				}
				glutPostRedisplay();
				break;
		}
	}
}

//----------------------------------------------------------------------------------
// Simulation Main Loop
//----------------------------------------------------------------------------------

void simLoop() {

	static double Global_Time = 0.0;

	if (Global_Time <= 2.1) {
		// Process the hardware module (this may request an SR4000 image, which necessitates bypassing other modules).
		KOS_Hardware_Handler(Global_Time);

		// Check if an SR Image was just rendered, if so, bypass all other modules.
		if(!(Sim_Struct()->m_SR_image)) {

			// Operate message hub
			Message_Hub()->process_message();

			// Operate Situational Awareness Module
			Situ_Module()->process_message();

			// Increment the global time.
			Global_Time += 0.0001;

		}
	} else {
		Sim_Struct()->m_SR_image = false;
	}
}

//----------------------------------------------------------------------------------
// Access Function for Simulation Struct.
//----------------------------------------------------------------------------------

kSim::Sim_Struct* Sim_Struct() {
	static kSim::Sim_Struct Simulation(4,4,4,2,2,0.14);
	return &Simulation;
}

KOS::KOS_Message_Hub* Message_Hub() {
	static KOS::KOS_Message_Hub Message_Hub;
	return &Message_Hub;
}

KOS::KOS_Situational* Situ_Module() {
	static KOS::KOS_Situational Situational_Awareness_Module;
	return &Situational_Awareness_Module;
}

KOS::KOS_Hardware* Hard_Module() {
	static KOS::KOS_Hardware Hardware_Module;
	return &Hardware_Module;
}

void KOS_Hardware_Handler(double Global_Time) {

	// On first run, create KOS_Hardware module class and time tracker.
	//static kSim::Sim_Hardware Hardware_Module;
	static double Hardware_Time = 0.0;

	// Acquire Sensor Data if an SR Image was just rendered.
	if(Sim_Struct()->m_SR_image) {

		// Store the current Cricket state.
		KOS::KOS_Cricket_Struct* curr_crick = new KOS::KOS_Cricket_Struct;
		curr_crick->BDY_pos_x = Sim_Struct()->m_cricket.m_BDY.m_Pos_X;
		curr_crick->BDY_pos_y = Sim_Struct()->m_cricket.m_BDY.m_Pos_Y;
		curr_crick->BDY_pos_z = Sim_Struct()->m_cricket.m_BDY.m_Pos_Z;
		//curr_crick->BDY_yaw = Sim_Struct()->m_cricket.m_BDY.m_Pos_Ang3;
		//curr_crick->BDY_pitch = Sim_Struct()->m_cricket.m_BDY.m_Pos_Ang2;
		//curr_crick->BDY_roll = Sim_Struct()->m_cricket.m_BDY.m_Pos_Ang1;
		curr_crick->CAM = Sim_Struct()->m_cricket.m_CAM.m_Joint_Angle;
		curr_crick->RFS = Sim_Struct()->m_cricket.m_RFS.m_Joint_Angle;
		curr_crick->RFP = Sim_Struct()->m_cricket.m_RFP.m_Joint_Angle;
		curr_crick->RFD = Sim_Struct()->m_cricket.m_RFD.m_Joint_Angle;
		curr_crick->RFT = Sim_Struct()->m_cricket.m_RFT.m_Joint_Angle;
		curr_crick->LFS = Sim_Struct()->m_cricket.m_LFS.m_Joint_Angle;
		curr_crick->LFP = Sim_Struct()->m_cricket.m_LFP.m_Joint_Angle;
		curr_crick->LFD = Sim_Struct()->m_cricket.m_LFD.m_Joint_Angle;
		curr_crick->LFT = Sim_Struct()->m_cricket.m_LFT.m_Joint_Angle;
		curr_crick->RRS = Sim_Struct()->m_cricket.m_RRS.m_Joint_Angle;
		curr_crick->RRP = Sim_Struct()->m_cricket.m_RRP.m_Joint_Angle;
		curr_crick->RRD = Sim_Struct()->m_cricket.m_RRD.m_Joint_Angle;
		curr_crick->RRT = Sim_Struct()->m_cricket.m_RRT.m_Joint_Angle;
		curr_crick->LRS = Sim_Struct()->m_cricket.m_LRS.m_Joint_Angle;
		curr_crick->LRP = Sim_Struct()->m_cricket.m_LRP.m_Joint_Angle;
		curr_crick->LRD = Sim_Struct()->m_cricket.m_LRD.m_Joint_Angle;
		curr_crick->LRT = Sim_Struct()->m_cricket.m_LRT.m_Joint_Angle;

		// Create new data message to Situational Awareness Module containing state information.
		KOS::KOS_Message_Struct* new_message = new KOS::KOS_Message_Struct;
		new_message->destination = KOS::e_Situational;
		new_message->origin = KOS::e_Hardware;
		new_message->message_type = "New State Frame";
		new_message->time_of_origin = Hardware_Time;
		new_message->data1 = curr_crick;
		new_message->data2 = Sim_Struct()->m_image_data;
		new_message->data3 = NULL;

		// Add the new message to the message hub's inbox.
		Message_Hub()->m_inbox.add_message(new_message);

		// Remove the image from the simulator's awareness.
		Sim_Struct()->m_image_data = NULL;

		// Clear the SR Image flag.
		Sim_Struct()->m_SR_image = false;

		// Update time.
		Hardware_Time += 0.01;

	} else {

		// Take any messages and add them to the hardware cue.
		// <<<< To be added! >>>>

		// Update the simulation and take a new SR4000 image if needed.
		if(Hardware_Time <= Global_Time) {

			// Updated the simulation.
			while(Sim_Struct()->m_sim_time < Hardware_Time && Sim_Struct()->m_cutoff_count < 10)
				Sim_Struct()->Sim_Step();

			// Display the time of image for the user.
			std::cout << "\n Current Time: " << Hardware_Time << "\n";

			// Render the SR4000 Image.
			//Sim_Struct()->Display();
			Sim_Struct()->m_SR_image = true;
			glutPostRedisplay();
		}
	}
}
