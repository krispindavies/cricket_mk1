
#include "KOS_Controller.h"

void KOS::KOS_Message_Hub::process_message() {

	// Check and see if we have any new messages.
	if(m_inbox.check_message()) {

		// Grab the message out of our inbox.
		KOS::KOS_Message_Struct* temp = m_inbox.get_message();

		// Forward the message on to the appropriate inbox.
		switch(temp->destination) {
			case KOS::e_Situational:
				m_situational->add_message(temp);
				break;
			case KOS::e_Hardware:
				m_hardware->add_message(temp);
				break;
			case KOS::e_Motion:
				m_motion->add_message(temp);
				break;
			default:
				std::cout << "\n\n Got a message that I don't know what to do with. - Message_Hub\n";
				std::cout << " From: " << temp->origin << "\n";
				std::cout << " To: " << temp->destination << "\n";
				std::cout << " Type: " << temp->message_type << "\n\n";
				throw Misuse_Error();
		}
	}
}

///////////////////////////////////////

KOS::KOS_SubGrid::KOS_SubGrid(KOS::KOS_DEC occupancy) {
	m_occupancy = new KOS_DEC[int(std::pow(SubGrid_Cell_Div,3))];
	m_confidence = new KOS_DEC[int(std::pow(SubGrid_Cell_Div,3))];
	for(int i = 0; i < std::pow(SubGrid_Cell_Div,3); i++) {
		m_occupancy[i] = Default_Occupancy;
		m_confidence[i] = Default_Confidence;
	}
}


KOS::KOS_SubGrid::~KOS_SubGrid() {
	delete[] m_occupancy;
	delete[] m_confidence;
}

void KOS::KOS_SubGrid::train(const int x, const int y, const int z, const KOS::KOS_DEC sensor_conf, const KOS::KOS_DEC sensed_occ){
	if(x < 0 || y < 0 || z < 0 || x >= SubGrid_Cell_Div || y >= SubGrid_Cell_Div || z >= SubGrid_Cell_Div) {
		throw KOS::Range_Error();
	}
	int target_cell = x*std::pow(SubGrid_Cell_Div,2) + y*SubGrid_Cell_Div + z;
	KOS_DEC error = sensed_occ - m_occupancy[target_cell];
	m_occupancy[target_cell] += error*Learning_Rate*sensor_conf*std::exp(m_confidence[target_cell]);
	m_confidence[target_cell] -= 0.6*(0.5 - std::abs(error));
	if(m_confidence[target_cell] > 0)
		m_confidence[target_cell] = 0;
}

KOS::KOS_DEC KOS::KOS_SubGrid::get_avg() {
	KOS_DEC ret_val = 0;
	for(int i = 0; i < std::pow(SubGrid_Cell_Div,3); i++) {
		ret_val += m_occupancy[i];
	}
	ret_val /= std::pow(SubGrid_Cell_Div,3.0);
	return ret_val;
}

///////////////////////////////////////

KOS::KOS_DEC KOS::KOS_ExoGrid_X::get_data(const KOS::KOS_DEC x_pos, const int y, const int z) {
	int ExoGrid_Cell = std::floor(x_pos/SubGrid_Measurements);
	if(ExoGrid_Cell + m_zero_cell < 0 || ExoGrid_Cell + m_zero_cell >= m_cell_count)
		return Default_Occupancy;
	int SubGrid_Cell = std::floor(x_pos*SubGrid_Cell_Div/SubGrid_Measurements) - SubGrid_Cell_Div*ExoGrid_Cell;
	return m_data[ExoGrid_Cell + m_zero_cell]->get_data(SubGrid_Cell, y, z);
}

void KOS::KOS_ExoGrid_X::train(const KOS::KOS_DEC x_pos, const int y, const int z, const KOS::KOS_DEC sensor_conf, const KOS::KOS_DEC sensed_occ) {

	int ExoGrid_Cell = std::floor(x_pos/SubGrid_Measurements);

	// If array must be resized, resize array.
	if(ExoGrid_Cell + m_zero_cell < 0) {

		int new_cells = -ExoGrid_Cell - m_zero_cell;
		int new_cell_count = m_cell_count + new_cells;
		int new_zero_cell = -ExoGrid_Cell;

		KOS_SubGrid* temp[m_cell_count];
		for(int i = 0; i < m_cell_count; i++) {
			temp[i] = m_data[i];
		}

		delete[] m_data;

		m_data = new KOS_SubGrid*[new_cell_count];
		for(int i = 0; i < new_cell_count; i++){
			if(i < new_cells)
				m_data[i] = new KOS_SubGrid(Default_Occupancy);
			else
				m_data[i] = temp[i-new_cells];
		}

		m_zero_cell = new_zero_cell;
		m_cell_count = new_cell_count;

	} else if (ExoGrid_Cell + m_zero_cell >= m_cell_count) {

		int new_cells = ExoGrid_Cell - (m_cell_count - m_zero_cell) + 1;
		int new_cell_count = m_cell_count + new_cells;

		KOS_SubGrid* temp[m_cell_count];
		for(int i = 0; i < m_cell_count; i++) {
			temp[i] = m_data[i];
		}

		delete[] m_data;

		m_data = new KOS_SubGrid*[new_cell_count];
		for(int i = 0; i < new_cell_count; i++){
			if(i < m_cell_count)
				m_data[i] = temp[i];
			else
				m_data[i] = new KOS_SubGrid(Default_Occupancy);
		}

		m_cell_count = new_cell_count;

	}

	// Train appropriate cell.
	int SubGrid_Cell = std::floor(x_pos*SubGrid_Cell_Div/SubGrid_Measurements) - SubGrid_Cell_Div*ExoGrid_Cell;
	m_data[ExoGrid_Cell + m_zero_cell]->train(SubGrid_Cell, y, z, sensor_conf, sensed_occ);
}

///////////////////////////////////////

KOS::KOS_DEC KOS::KOS_ExoGrid_Y::get_data(const KOS::KOS_DEC x_pos, const KOS::KOS_DEC y_pos, const int z) {
	int ExoGrid_Cell = std::floor(y_pos/SubGrid_Measurements);
	if(ExoGrid_Cell + m_zero_cell < 0 || ExoGrid_Cell + m_zero_cell >= m_cell_count)
		return Default_Occupancy;
	int SubGrid_Cell = std::floor(y_pos*SubGrid_Cell_Div/SubGrid_Measurements) - SubGrid_Cell_Div*ExoGrid_Cell;
	return m_data[ExoGrid_Cell + m_zero_cell]->get_data(x_pos, SubGrid_Cell, z);
}

void KOS::KOS_ExoGrid_Y::train(const KOS::KOS_DEC x_pos, const KOS::KOS_DEC y_pos, const int z, const KOS::KOS_DEC sensor_conf, const KOS::KOS_DEC sensed_occ) {

	int ExoGrid_Cell = std::floor(y_pos/SubGrid_Measurements);

	// If array must be resized, resize array.
	if(ExoGrid_Cell + m_zero_cell < 0) {

		int new_cells = -ExoGrid_Cell - m_zero_cell;
		int new_cell_count = m_cell_count + new_cells;
		int new_zero_cell = -ExoGrid_Cell;

		KOS_ExoGrid_X* temp[m_cell_count];
		for(int i = 0; i < m_cell_count; i++) {
			temp[i] = m_data[i];
		}

		delete[] m_data;

		m_data = new KOS_ExoGrid_X*[new_cell_count];
		for(int i = 0; i < new_cell_count; i++){
			if(i < new_cells)
				m_data[i] = new KOS_ExoGrid_X;
			else
				m_data[i] = temp[i-new_cells];
		}

		m_zero_cell = new_zero_cell;
		m_cell_count = new_cell_count;

	} else if (ExoGrid_Cell + m_zero_cell >= m_cell_count) {

		int new_cells = ExoGrid_Cell - (m_cell_count - m_zero_cell) + 1;
		int new_cell_count = m_cell_count + new_cells;

		KOS_ExoGrid_X* temp[m_cell_count];
		for(int i = 0; i < m_cell_count; i++) {
			temp[i] = m_data[i];
		}

		delete[] m_data;

		m_data = new KOS_ExoGrid_X*[new_cell_count];
		for(int i = 0; i < new_cell_count; i++){
			if(i < m_cell_count)
				m_data[i] = temp[i];
			else
				m_data[i] = new KOS_ExoGrid_X;
		}

		m_cell_count = new_cell_count;

	}

	// Train appropriate cell.
	int SubGrid_Cell = std::floor(y_pos*SubGrid_Cell_Div/SubGrid_Measurements) - SubGrid_Cell_Div*ExoGrid_Cell;
	m_data[ExoGrid_Cell + m_zero_cell]->train(x_pos, SubGrid_Cell, z, sensor_conf, sensed_occ);
}

///////////////////////////////////////

KOS::KOS_DEC KOS::KOS_ExoGrid_Z::get_data(const KOS::KOS_DEC x_pos, const KOS::KOS_DEC y_pos, const KOS::KOS_DEC z_pos) {
	int ExoGrid_Cell = std::floor(z_pos/SubGrid_Measurements);
	if(ExoGrid_Cell + m_zero_cell < 0 || ExoGrid_Cell + m_zero_cell >= m_cell_count)
		return Default_Occupancy;
	int SubGrid_Cell = std::floor(z_pos*SubGrid_Cell_Div/SubGrid_Measurements) - SubGrid_Cell_Div*ExoGrid_Cell;
	return m_data[ExoGrid_Cell + m_zero_cell]->get_data(x_pos, y_pos, SubGrid_Cell);
}

void KOS::KOS_ExoGrid_Z::train(const KOS_DEC x_pos, const KOS_DEC y_pos, const KOS_DEC z_pos, const KOS::KOS_DEC sensor_conf, const KOS::KOS_DEC sensed_occ) {

	int ExoGrid_Cell = std::floor(z_pos/SubGrid_Measurements);

	// If array must be resized, resize array.
	if(ExoGrid_Cell + m_zero_cell < 0) {

		int new_cells = -ExoGrid_Cell - m_zero_cell;
		int new_cell_count = m_cell_count + new_cells;
		int new_zero_cell = -ExoGrid_Cell;

		KOS_ExoGrid_Y* temp[m_cell_count];
		for(int i = 0; i < m_cell_count; i++) {
			temp[i] = m_data[i];
		}

		delete[] m_data;

		m_data = new KOS_ExoGrid_Y*[new_cell_count];
		for(int i = 0; i < new_cell_count; i++){
			if(i < new_cells)
				m_data[i] = new KOS_ExoGrid_Y;
			else
				m_data[i] = temp[i-new_cells];
		}

		m_zero_cell = new_zero_cell;
		m_cell_count = new_cell_count;

	} else if (ExoGrid_Cell + m_zero_cell >= m_cell_count) {

		int new_cells = ExoGrid_Cell - (m_cell_count - m_zero_cell) + 1;
		int new_cell_count = m_cell_count + new_cells;

		KOS_ExoGrid_Y* temp[m_cell_count];
		for(int i = 0; i < m_cell_count; i++) {
			temp[i] = m_data[i];
		}

		delete[] m_data;

		m_data = new KOS_ExoGrid_Y*[new_cell_count];
		for(int i = 0; i < new_cell_count; i++){
			if(i < m_cell_count)
				m_data[i] = temp[i];
			else
				m_data[i] = new KOS_ExoGrid_Y;
		}

		m_cell_count = new_cell_count;

	}

	// Train appropriate cell.
	int SubGrid_Cell = std::floor(z_pos*SubGrid_Cell_Div/SubGrid_Measurements) - SubGrid_Cell_Div*ExoGrid_Cell;
	m_data[ExoGrid_Cell + m_zero_cell]->train(x_pos, y_pos, SubGrid_Cell, sensor_conf, sensed_occ);
}

///////////////////////////////////////

KOS::KOS_DEC KOS::KOS_Map::get_data(const KOS::KOS_DEC x_pos, const KOS::KOS_DEC y_pos, const KOS::KOS_DEC z_pos) {
	KOS_DEC ret_val = 0;
	for(int i = 0; i < Num_Map_Layers; i++) {
		KOS_DEC offset = i*(SubGrid_Measurements/Num_Map_Layers);
		ret_val += m_data[i].get_data(x_pos - offset, y_pos - offset, z_pos - offset);
	}

	return ret_val/Num_Map_Layers;
}
void KOS::KOS_Map::train(const kMath::hVector pos, const KOS::KOS_DEC sensor_conf, const KOS::KOS_DEC sensed_occ) {
	for(int i = 0; i < Num_Map_Layers; i++) {
		KOS_DEC offset = i*(SubGrid_Measurements/Num_Map_Layers);
		m_data[i].train(pos.get_val(0) - offset, pos.get_val(1) - offset, pos.get_val(2) - offset, sensor_conf, sensed_occ);
	}
}

///////////////////////////////////////

void KOS::KOS_Situational::process_message() {
	// Check and see if we have any new messages.
	if(m_inbox.check_message()) {

		// Grab the message out of our inbox.
		KOS::KOS_Message_Struct* temp = m_inbox.get_message();

		// Respond to the message appropriately.
		if(temp->message_type == "New State Frame") {

			// Update internal cricket representation.
			m_cricket = *((KOS_Cricket_Struct*)temp->data1);

			// Generate a homogeneous transformation matrix from camera local space to global space.
			kMath::hMatrix cam_to_global_trans;
			cam_to_global_trans = kMath::h_Trans(m_cricket.BDY_pos_x, m_cricket.BDY_pos_y, m_cricket.BDY_pos_z)*kMath::h_Rotz(m_cricket.BDY_yaw)*kMath::h_Roty(m_cricket.BDY_pitch)*kMath::h_Rotx(m_cricket.BDY_roll)*kMath::h_Trans(0.5*0.406,0,0)*kMath::h_Roty(m_cricket.CAM);

			std::cout << "\n Incorporating map data now...\n";

			// Incorporate the image data into the map.
			kMath::hVector* image = ((kMath::hVector*)temp->data2);
			/*for(int i = 0; i < 176*144; i++) {
				if(image[i].mag() < 2.5) {
					//m_map.train(cam_to_global_trans*image[i], 1.0, 1.0);
					for(double j = 0.5; j <= 1.05; j += Dist_Per_Train_Poll/image[i].mag()) {
						double sensor_conf = 2.0*std::exp(-0.5*std::pow(j-1.0,2)*std::pow(0.04246610,-2))-1.0;
						if(sensor_conf > 0)
							m_map.train(cam_to_global_trans*kMath::h_Scale(j)*image[i], sensor_conf, 1.0);
						else
							m_map.train(cam_to_global_trans*kMath::h_Scale(j)*image[i], -sensor_conf, 0.0);
					}
				}
			}*/

			std::cout << " Data incorporated.\n";

			delete ((KOS_Cricket_Struct*)temp->data1);
			delete[] ((kMath::hVector*)temp->data2);
			delete temp;

		} else {
				std::cout << "\n\n Got a message that I don't know what to do with. - Situational\n";
				std::cout << " From: " << temp->origin << "\n";
				std::cout << " To: " << temp->destination << "\n";
				std::cout << " Type: " << temp->message_type << "\n\n";
				throw Misuse_Error();
		}
	}
}
