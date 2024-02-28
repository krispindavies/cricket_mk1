// Copyright (c) 2024 Krispin Davies
// SPDX-License-Identifier: BSD-3-Clause

#include "kMath.h"

///////////////////////////////////////////////////////////////////////
// KOS 2-Dimensional Array Class
///////////////////////////////////////////////////////////////////////

// This is the main constructor for kMatrix objects. It can be used with one or two inputs, if one input is used
// then an m x 1 vector is created.
kMath::kMatrix::kMatrix(const KOS_INT rows, const KOS_INT columns) {
	if(rows <= 0 || columns <= 0)
		throw Range_Error();
	size_r = rows;
	size_c = columns;
	data = new KOS_DEC*[size_r];
	for(int i = 0; i < size_r; i++) data[i] = new KOS_DEC[size_c];
}

// Copy constructor.
kMath::kMatrix::kMatrix(const kMatrix& arg1) {
	size_r = arg1.get_size_r();
	size_c = arg1.get_size_c();
	data = new KOS_DEC*[size_r];
	for(int i = 0; i < size_r; i++) {
		data[i] = new KOS_DEC[size_c];
		for(int j = 0; j < size_c; j++) data[i][j] = arg1.get_val(i, j);
	}
}

// Destructor, needed for memory deallocation to prevent memory leaks.
kMath::kMatrix::~kMatrix() {
	for(int i = 0; i < size_r; i++) delete[] data[i];
	delete[] data;
}

// A basic display function, will output the matrix in text format to the main cout stream.
void kMath::kMatrix::display() {
	for(int i = 0; i < size_r; i++) {
		std::cout << "[";
		for(int j = 0; j < size_c-1; j++)	std::cout << data[i][j] << ", ";
		std::cout << data[i][size_c-1] << "]\n";
	}
	std::cout << "\n";
}

// Round bracket access operator. Allows users to access matrix values via Mat(row,col). This is a non-const operation
// so use allows the value at (row,col) to be modified.
kMath::KOS_DEC& kMath::kMatrix::operator()(KOS_INT row, KOS_INT col) {
	if(row < 0 || row >= size_r || col < 0 || col >= size_c)
		throw Range_Error();
	return data[row][col];
}

// This is another round bracket access operator, but designed for use on vectors. If this is called on a non-vector (ie: column
// count greater than 1) this will throw a range error.
kMath::KOS_DEC& kMath::kMatrix::operator()(KOS_INT row) {
	if(row < 0 || row >= size_r || size_c != 1)
		throw Range_Error();
	return data[row][0];
}

void kMath::kMatrix::rref() {
	if(size_r >= size_c) {
		std::cout << "Attempt to rref a tall matrix!\n";
		return;
	}

	// The row_counter will track how far down the matrix we've progressed, the lead counter will track how far right
	// in the matrix we've progressed. If either of these reach their respective maximums, we've finished.
	for(int lead = 0, row_counter = 0; lead < size_c && row_counter < size_r; lead++, row_counter++) {

		// Find the row (from row_counter onwards) with the largest leading term.
		int i = row_counter;
		while(row_counter < size_r) {
			i = row_counter;
			for(int j = i; j < size_r; j++) {
				if(std::abs(data[j][lead]) > std::abs(data[i][lead]))
					i = j;
			}

			// If the largest leading term we found was zero, we know that we can't do anything to this column, so
			// increment the lead counter to the next column.
			if(data[i][lead] == 0) {
				lead++;

				// If we've hit the right side of the matrix, we're done.
				if(lead == size_c)
					return;
			} else {
				break;
			}
		}

		// If the row we found is not the same as the one we want, swap them.
		if(i != row_counter) {
			for(int j = 0; j < size_c; j++){
				KOS_DEC temp = data[row_counter][j];
				data[row_counter][j] = data[i][j];
				data[i][j] = temp;
			}
		}

		// Divide current row by leading value.
		KOS_DEC divisor = data[row_counter][lead];
		for(int j = 0; j < size_c; j++)
			data[row_counter][j] /= divisor;

		// Subtract all other rows by current row.
		for(int j = 0; j < size_r; j++) {
			if(j != row_counter) {
				KOS_DEC multiplier = data[j][lead];
				for(int k = 0; k < size_c; k++)
					data[j][k] -= multiplier*data[row_counter][k];
			}
		}
	}
}

void kMath::kMatrix::clean(int x) {
	for(int j = 0; j < size_r; j++)
		for(int k = 0; k < size_c; k++)
			if(std::abs(data[j][k]) < 1.0/pow(10,x))
				data[j][k] = 0;
}

// Assignment operator, checks for self assignment and performs proper memory deallocation/reallocation.
void kMath::kMatrix::operator=(const kMatrix& arg1) {
	if(this != &arg1) {
		for(int i = 0; i < size_r; i++) delete[] data[i];
		delete[] data;
		size_r = arg1.get_size_r();
		size_c = arg1.get_size_c();
		data = new KOS_DEC*[size_r];
		for(int i = 0; i < size_r; i++) {
			data[i] = new KOS_DEC[size_c];
			for(int j = 0; j < size_c; j++) data[i][j] = arg1.get_val(i, j);
		}
	}
}

// friend and helper functions for kMatrix.
namespace kMath {
	
	// Unary '-' operator.
	kMatrix operator-(const kMatrix& arg1) {
		kMatrix ret_val(arg1.get_size_r(), arg1.get_size_c());
		for(int i = 0; i < ret_val.get_size_r(); i++) {
			for(int j = 0; j < ret_val.get_size_c(); j++) ret_val(i,j) = -arg1.get_val(i,j);
		}
		return ret_val;
	}
	
	// Matrix subtraction. Checks for appropriate sizing.
	kMatrix operator-(const kMatrix& arg1, const kMatrix& arg2) {
		if(arg1.get_size_r() != arg2.get_size_r() || arg1.get_size_c() != arg2.get_size_c())
			throw Range_Error();
		kMatrix ret_val(arg1.get_size_r(), arg1.get_size_c());
		for(int i = 0; i < ret_val.get_size_r(); i++) {
			for(int j = 0; j < ret_val.get_size_c(); j++) ret_val(i,j) = arg1.get_val(i,j) - arg2.get_val(i,j);
		}
		return ret_val;
	}
	
	// Matrix addition. Checks for appropriate sizing.
	kMatrix operator+(const kMatrix& arg1, const kMatrix& arg2) {
		if(arg1.get_size_r() != arg2.get_size_r() || arg1.get_size_c() != arg2.get_size_c()) {
			std::cerr << "kMatrix::Operator+() Failed size test. (" << arg1.get_size_r() << "x" << arg1.get_size_c() << "), (" << arg2.get_size_r() << "x" << arg2.get_size_c() << ").\n";
			throw Range_Error();
		}
		kMatrix ret_val(arg1.get_size_r(), arg1.get_size_c());
		for(int i = 0; i < ret_val.get_size_r(); i++) {
			for(int j = 0; j < ret_val.get_size_c(); j++) ret_val(i,j) = arg1.get_val(i,j) + arg2.get_val(i,j);
		}
		return ret_val;
	}
	
	// Matrix multiplication. Checks for appropriate sizing.
	kMatrix operator*(const kMatrix& arg1, const kMatrix& arg2) {
		if(arg1.get_size_c() != arg2.get_size_r())
			throw Range_Error();
		kMatrix ret_val(arg1.get_size_r(), arg2.get_size_c());
		for(int i = 0; i < ret_val.get_size_r(); i++) {
			for(int j = 0; j < ret_val.get_size_c(); j++) {
				ret_val(i,j) = 0;
				for(int k = 0; k < arg1.get_size_c(); k++) ret_val(i,j) += arg1.get_val(i,k) * arg2.get_val(k,j);
			}
		}
		return ret_val;
	}
	
	// Scalar x matrix multiplication.
	kMatrix operator*(const KOS_DEC& arg1, const kMatrix& arg2) {
		kMatrix ret_val(arg2.get_size_r(), arg2.get_size_c());
		for(int i = 0; i < ret_val.get_size_r(); i++) {
			for(int j = 0; j < ret_val.get_size_c(); j++) ret_val(i,j) = arg1*arg2.get_val(i,j);
		}
		return ret_val;
	}
	
	// Matrix x scalar multiplication.
	kMatrix operator*(const kMatrix& arg1, const KOS_DEC& arg2) {
		kMatrix ret_val(arg1.get_size_r(), arg1.get_size_c());
		for(int i = 0; i < ret_val.get_size_r(); i++) {
			for(int j = 0; j < ret_val.get_size_c(); j++) ret_val(i,j) = arg2*arg1.get_val(i,j);
		}
		return ret_val;
	}	
	
	// Function for transposing a matrix.
	kMatrix transpose(const kMatrix& arg1) {
		kMatrix ret_val(arg1.get_size_c(), arg1.get_size_r());
		for(int i = 0; i < ret_val.get_size_r(); i++) {
			for(int j = 0; j < ret_val.get_size_c(); j++) ret_val(i,j) = arg1.get_val(j,i);
		}
		return ret_val;
	}
	
} // End of kMath namespace.

///////////////////////////////////////////////////////////////////////
// 2D Homogeneous Matrix (Statically Allocated)
///////////////////////////////////////////////////////////////////////

void kMath::hMatrix::display() {
	for(int i = 0; i < 4; i++) {
		std::cout << "[" << data[i][0] << " " << data[i][1] << " " << data[i][2] << " " << data[i][3] << "]\n";
	}
	std::cout << "\n";
}

GLfloat* kMath::hMatrix::OGL() {
	if(GL_Table != NULL)
		delete[] GL_Table;
	GL_Table = new GLfloat[16];
	GL_Table[0] = data[0][0];
	GL_Table[1] = data[1][0];
	GL_Table[2] = data[2][0];
	GL_Table[3] = data[3][0];
	GL_Table[4] = data[0][1];
	GL_Table[5] = data[1][1];
	GL_Table[6] = data[2][1];
	GL_Table[7] = data[3][1];
	GL_Table[8] = data[0][2];
	GL_Table[9] = data[1][2];
	GL_Table[10] = data[2][2];
	GL_Table[11] = data[3][2];
	GL_Table[12] = data[0][3];
	GL_Table[13] = data[1][3];
	GL_Table[14] = data[2][3];
	GL_Table[15] = data[3][3];
	return GL_Table;
}

void kMath::hMatrix::operator=(const hMatrix& arg1) {
	if(this != &arg1) {
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) data[i][j] = arg1.get_val(i, j);
		}
	}
}

void kMath::hMatrix::operator=(const kMatrix& arg1) {
	if(arg1.get_size_r() != 4 || arg1.get_size_c() != 4)
		throw Range_Error();
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) data[i][j] = arg1.get_val(i,j);
	}
}

kMath::hMatrix& kMath::hMatrix::operator*=(const hMatrix& arg1) {
	hMatrix temp = *this;
	if(this != &arg1) {
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				data[i][j] = 0;
				for(int k = 0; k < 4; k++) data[i][j] += arg1.get_val(i,k) * temp.get_val(k,j);
			}
		}
	} else {
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				data[i][j] = 0;
				for(int k = 0; k < 4; k++) data[i][j] += temp.get_val(i,k) * temp.get_val(k,j);
			}
		}
	}
	return *this;
}

namespace kMath {
	
	hMatrix operator-(const hMatrix& arg1) {
		hMatrix ret_val;
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) ret_val(i,j) = -arg1.get_val(i,j);
		}
		return ret_val;
	}
	
	hMatrix operator-(const hMatrix& arg1, const hMatrix& arg2) {
		hMatrix ret_val;
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) ret_val(i,j) = arg1.get_val(i,j) - arg2.get_val(i,j);
		}
		return ret_val;
	}
	
	hMatrix operator+(const hMatrix& arg1, const hMatrix& arg2) {
		hMatrix ret_val;
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) ret_val(i,j) = arg1.get_val(i,j) + arg2.get_val(i,j);
		}
		return ret_val;
	}
	
	hMatrix operator*(const hMatrix& arg1, const hMatrix& arg2) {
		hMatrix ret_val;
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				ret_val(i,j) = 0;
				for(int k = 0; k < 4; k++) ret_val(i,j) += arg1.get_val(i,k) * arg2.get_val(k,j);
			}
		}
		return ret_val;
	}
	
	hMatrix operator*(const KOS_DEC& arg1, const hMatrix& arg2) {
		hMatrix ret_val;
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) ret_val(i,j) = arg1*arg2.get_val(i,j);
		}
		return ret_val;
	}
	
	hMatrix operator*(const hMatrix& arg1, const KOS_DEC& arg2) {
		hMatrix ret_val;
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) ret_val(i,j) = arg2*arg1.get_val(i,j);
		}
		return ret_val;
	}
	
	hMatrix h_Ident() {
		hMatrix ret_val;
		ret_val(0,0) = 1;
		ret_val(1,1) = 1;
		ret_val(2,2) = 1;
		ret_val(3,3) = 1;
		return ret_val;
	}
	
	hMatrix h_Scale(const KOS_DEC& arg1, const KOS_DEC& arg2, const KOS_DEC& arg3) {
		hMatrix ret_val;
		ret_val(0,0) = arg1;
		ret_val(1,1) = arg2;
		ret_val(2,2) = arg3;
		ret_val(3,3) = 1;
		return ret_val;
	}

	hMatrix h_Scale(const KOS_DEC& arg1) {
		return h_Scale(arg1, arg1, arg1);
	}

	hMatrix h_Trans(const KOS_DEC& arg1, const KOS_DEC& arg2, const KOS_DEC& arg3) {
		hMatrix ret_val;
		ret_val(0,0) = 1;
		ret_val(0,3) = arg1;
		ret_val(1,1) = 1;
		ret_val(1,3) = arg2;
		ret_val(2,2) = 1;
		ret_val(2,3) = arg3;
		ret_val(3,3) = 1;
		return ret_val;
	}
	
	hMatrix h_Rotx(const KOS_DEC& arg1) {
		hMatrix ret_val;
		ret_val(0,0) = 1;
		ret_val(1,1) = cos(arg1);
		ret_val(1,2) = -sin(arg1);
		ret_val(2,1) = sin(arg1);
		ret_val(2,2) = cos(arg1);
		ret_val(3,3) = 1;
		return ret_val;
	}
	
	hMatrix h_Roty(const KOS_DEC& arg1) {
		hMatrix ret_val;
		ret_val(0,0) = cos(arg1);
		ret_val(0,2) = sin(arg1);
		ret_val(1,1) = 1;
		ret_val(2,0) = -sin(arg1);
		ret_val(2,2) = cos(arg1);
		ret_val(3,3) = 1;
		return ret_val;
	}
	
	hMatrix h_Rotz(const KOS_DEC& arg1) {
		hMatrix ret_val;
		ret_val(0,0) = cos(arg1);
		ret_val(0,1) = -sin(arg1);
		ret_val(1,0) = sin(arg1);
		ret_val(1,1) = cos(arg1);
		ret_val(2,2) = 1;
		ret_val(3,3) = 1;
		return ret_val;
	}
	
	hMatrix h_RotQuat(const KOS_DEC& quat_1, const KOS_DEC& quat_2, const KOS_DEC& quat_3, const KOS_DEC& quat_4) {
		hMatrix ret_val;
		ret_val(0,0) = 1 - 2*pow(quat_3,2) - 2*pow(quat_4,2);
		ret_val(0,1) = 2*quat_2*quat_3 - 2*quat_1*quat_4;
		ret_val(0,2) = 2*quat_2*quat_4 + 2*quat_1*quat_3;
		ret_val(1,0) = 2*quat_2*quat_3 + 2*quat_1*quat_4;
		ret_val(1,1) = 1 - 2*pow(quat_2,2) - 2*pow(quat_4,2);
		ret_val(1,2) = 2*quat_3*quat_4 - 2*quat_1*quat_2;
		ret_val(2,0) = 2*quat_2*quat_4 - 2*quat_1*quat_3;
		ret_val(2,1) = 2*quat_3*quat_4 + 2*quat_1*quat_2;
		ret_val(2,2) = 1 - 2*pow(quat_2,2) - 2*pow(quat_3,2);
		ret_val(3,3) = 1;
		return ret_val;
	}

} // End of kMath namespace.

///////////////////////////////////////////////////////////////////////
// Homogeneous Vector (Statically Allocated)
///////////////////////////////////////////////////////////////////////

void kMath::hVector::display() {
	for(int i = 0; i < 4; i++) {
		std::cout << "[" << data[i] << "]\n";
	}
	std::cout << "\n";
}

void kMath::hVector::operator=(const hVector& arg1) {
	if(this != &arg1) {
		for(int i = 0; i < 4; i++) {
			data[i] = arg1.get_val(i);
		}
	}
}

void kMath::hVector::operator=(const kMatrix& arg1) {
	if(arg1.get_size_r() != 4 || arg1.get_size_c() != 1)
		throw Range_Error();
	for(int i = 0; i < 4; i++) {
		data[i] = arg1.get_val(i,1);
	}
}

kMath::hVector& kMath::hVector::operator*=(const hMatrix& arg1) {
	hVector temp = *this;
	for(int i = 0; i < 4; i++) {
		data[i] = 0;
		for(int k = 0; k < 4; k++) data[i] += arg1.get_val(i,k) * temp.get_val(k);
	}
	return *this;
}

kMath::hVector& kMath::hVector::operator+=(const hVector& arg1) {
	for(int i = 0; i < 4; i++) {
		data[i] = arg1.get_val(i) + this->get_val(i);
	}
	return *this;
}

namespace kMath {
	
	hVector operator-(const hVector& arg1) {
		hVector ret_val;
		for(int i = 0; i < 4; i++) {
			ret_val(i) = -arg1.get_val(i);
		}
		return ret_val;
	}
	
	hVector operator-(const hVector& arg1, const hVector& arg2) {
		hVector ret_val;
		for(int i = 0; i < 4; i++) {
			ret_val(i) = arg1.get_val(i) - arg2.get_val(i);
		}
		return ret_val;
	}
	
	hVector operator+(const hVector& arg1, const hVector& arg2) {
		hVector ret_val;
		for(int i = 0; i < 4; i++) {
			ret_val(i) = arg1.get_val(i) + arg2.get_val(i);
		}
		return ret_val;
	}
	
	hVector operator*(const hMatrix& arg1, const hVector& arg2) {
		hVector ret_val;
		for(int i = 0; i < 4; i++) {
			ret_val(i) = 0;
			for(int k = 0; k < 4; k++) ret_val(i) += arg1.get_val(i,k) * arg2.get_val(k);
		}
		return ret_val;
	}
	
	hVector operator*(const KOS_DEC& arg1, const hVector& arg2) {
		hVector ret_val;
		for(int i = 0; i < 4; i++) {
			ret_val(i) = arg1*arg2.get_val(i);
		}
		return ret_val;
	}
	
	hVector operator*(const hVector& arg1, const KOS_DEC& arg2) {
		hVector ret_val;
		for(int i = 0; i < 4; i++) {
			ret_val(i) = arg2*arg1.get_val(i);
		}
		return ret_val;
	}
	
	hVector operator/(const hVector& arg1, const KOS_DEC& arg2) {
		hVector ret_val;
		for(int i = 0; i < 4; i++) {
			ret_val(i) = arg1.get_val(i)/arg2;
		}
		return ret_val;
	}

	hVector h_Point(const KOS_DEC& arg_x, const KOS_DEC& arg_y, const KOS_DEC& arg_z) {
		hVector ret_val;
		ret_val(0) = arg_x;
		ret_val(1) = arg_y;
		ret_val(2) = arg_z;
		ret_val(3) = 1;
		return ret_val;
	}

	hVector h_Vec(const KOS_DEC& arg_x, const KOS_DEC& arg_y, const KOS_DEC& arg_z) {
		hVector ret_val;
		ret_val(0) = arg_x;
		ret_val(1) = arg_y;
		ret_val(2) = arg_z;
		ret_val(3) = 0;
		return ret_val;
	}

	KOS_DEC dot(const hVector& arg_1, const hVector& arg_2) {
		return arg_1.get_val(0)*arg_2.get_val(0) + arg_1.get_val(1)*arg_2.get_val(1) + arg_1.get_val(2)*arg_2.get_val(2);
	}

	hVector h_VRotx(const KOS_DEC& Angle_Pos, const KOS_DEC& Angle_Vel, const hVector& Pos, const hVector& Vel) {
		hVector ret_val;
		ret_val(0) = Vel.get_val(0);
		ret_val(1) = cos(Angle_Pos)*Vel.get_val(1) - sin(Angle_Pos)*Angle_Vel*Pos.get_val(1) - sin(Angle_Pos)*Vel.get_val(2) - cos(Angle_Pos)*Angle_Vel*Pos.get_val(2);
		ret_val(2) = sin(Angle_Pos)*Vel.get_val(1) + cos(Angle_Pos)*Angle_Vel*Pos.get_val(1) + cos(Angle_Pos)*Vel.get_val(2) - sin(Angle_Pos)*Angle_Vel*Pos.get_val(2);
		ret_val(3) = 0;
		return ret_val;
	}

	hVector h_VRoty(const KOS_DEC& Angle_Pos, const KOS_DEC& Angle_Vel, const hVector& Pos, const hVector& Vel){
		hVector ret_val;
		ret_val(0) = cos(Angle_Pos)*Vel.get_val(0) - sin(Angle_Pos)*Angle_Vel*Pos.get_val(0) + sin(Angle_Pos)*Vel.get_val(2) + cos(Angle_Pos)*Angle_Vel*Pos.get_val(2);
		ret_val(1) = Vel.get_val(1);
		ret_val(2) = -sin(Angle_Pos)*Vel.get_val(0) - cos(Angle_Pos)*Angle_Vel*Pos.get_val(0) + cos(Angle_Pos)*Vel.get_val(2) - sin(Angle_Pos)*Angle_Vel*Pos.get_val(2);
		ret_val(3) = 0;
		return ret_val;
	}

	hVector h_VRotz(const KOS_DEC& Angle_Pos, const KOS_DEC& Angle_Vel, const hVector& Pos, const hVector& Vel){
		hVector ret_val;
		ret_val(0) = cos(Angle_Pos)*Vel.get_val(0) - sin(Angle_Pos)*Angle_Vel*Pos.get_val(0) - sin(Angle_Pos)*Vel.get_val(1) - cos(Angle_Pos)*Angle_Vel*Pos.get_val(1);
		ret_val(1) = sin(Angle_Pos)*Vel.get_val(0) + cos(Angle_Pos)*Angle_Vel*Pos.get_val(0) + cos(Angle_Pos)*Vel.get_val(1) - sin(Angle_Pos)*Angle_Vel*Pos.get_val(1);
		ret_val(2) = Vel.get_val(2);
		ret_val(3) = 0;
		return ret_val;
	}

	hVector h_VRotQuat(const KOS_DEC& QuatA_Pos, const KOS_DEC& QuatB_Pos, const KOS_DEC& QuatC_Pos, const KOS_DEC& QuatD_Pos, const KOS_DEC& QuatA_Vel, const KOS_DEC& QuatB_Vel, const KOS_DEC& QuatC_Vel, const KOS_DEC& QuatD_Vel, const hVector& Pos, const hVector& Vel) {
		hVector ret_val;
		ret_val(0) = (1 - 2*pow(QuatC_Pos,2) - 2*pow(QuatD_Pos,2))*Vel.get_val(0) + (2*QuatB_Pos*QuatC_Pos - 2*QuatA_Pos*QuatD_Pos)*Vel.get_val(1) + (2*QuatB_Pos*QuatD_Pos + 2*QuatA_Pos*QuatC_Pos)*Vel.get_val(2) + (-4*QuatC_Pos*QuatC_Vel - 4*QuatD_Pos*QuatD_Vel)*Pos.get_val(0) + (2*QuatB_Vel*QuatC_Pos + 2*QuatB_Pos*QuatC_Vel - 2*QuatA_Vel*QuatD_Pos - 2*QuatA_Pos*QuatD_Vel)*Pos.get_val(1) + (2*QuatB_Vel*QuatD_Pos + 2*QuatB_Pos*QuatD_Vel + 2*QuatA_Vel*QuatC_Pos + 2*QuatA_Pos*QuatC_Vel)*Pos.get_val(2);
		ret_val(1) = (2*QuatB_Pos*QuatC_Pos + 2*QuatA_Pos*QuatD_Pos)*Vel.get_val(0) + (1 - 2*pow(QuatB_Pos,2) - 2*pow(QuatD_Pos,2))*Vel.get_val(1) + (2*QuatC_Pos*QuatD_Pos - 2*QuatA_Pos*QuatB_Pos)*Vel.get_val(2) + (2*QuatB_Vel*QuatC_Pos + 2*QuatB_Pos*QuatC_Vel + 2*QuatA_Vel*QuatD_Pos + 2*QuatA_Pos*QuatD_Vel)*Pos.get_val(0) + (-4*QuatB_Pos*QuatB_Vel - 4*QuatD_Pos*QuatD_Vel)*Pos.get_val(1) + (2*QuatC_Vel*QuatD_Pos + 2*QuatC_Pos*QuatD_Vel - 2*QuatA_Vel*QuatB_Pos - 2*QuatA_Pos*QuatB_Vel)*Pos.get_val(2);
		ret_val(2) = (2*QuatB_Pos*QuatD_Pos - 2*QuatA_Pos*QuatC_Pos)*Vel.get_val(0) + (2*QuatC_Pos*QuatD_Pos + 2*QuatA_Pos*QuatB_Pos)*Vel.get_val(1) + (1 - 2*pow(QuatB_Pos,2) - 2*pow(QuatC_Pos,2))*Vel.get_val(2) + (2*QuatB_Vel*QuatD_Pos + 2*QuatB_Pos*QuatD_Vel - 2*QuatA_Vel*QuatC_Pos - 2*QuatA_Pos*QuatC_Vel)*Pos.get_val(0) + (2*QuatC_Vel*QuatD_Pos + 2*QuatC_Pos*QuatD_Vel + 2*QuatA_Vel*QuatB_Pos + 2*QuatA_Pos*QuatB_Vel)*Pos.get_val(1) + (-4*QuatB_Pos*QuatB_Vel - 4*QuatC_Pos*QuatC_Vel)*Pos.get_val(2);
		ret_val(3) = 0;
		return ret_val;
	}

} // End of kMath namespace.
