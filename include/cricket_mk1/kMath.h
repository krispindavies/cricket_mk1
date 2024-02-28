// Copyright (c) 2024 Krispin Davies
// SPDX-License-Identifier: BSD-3-Clause

#ifndef KMATH_H_
#define KMATH_H_

#include <iostream>
#include <cmath>
#include <freeglut.h>

//----------------------------------------------------------------------------------

namespace kMath {
	
	// Typedefs for easily changing the representation of interger and decimal values used by kMath.
	typedef int KOS_INT; // Interger
	typedef double KOS_DEC; // Decimal
	
	// Thrown error class declarations.
	class Range_Error { }; //kMath
	
	// Declarations of classes created herein.
	class kMatrix;
	class hMatrix;
	class hVector;
	
///////////////////////////////////////////////////////////////////////
// General 2D Matrix Class (Dynamically Allocated)
///////////////////////////////////////////////////////////////////////
	
	class kMatrix {
		KOS_INT size_r; // Row count.
		KOS_INT size_c; // Column count.
		KOS_DEC** data; // Data storage pointer.
		
	public:
		// Constructors
		kMatrix(const KOS_INT rows, const KOS_INT columns = 1); // Standard Constructor for (n x m) matricies.
		kMatrix(const kMatrix&); // Copy Constructor.
		
		// Bracket style NON-const data access operators for assignment and reading.
		KOS_DEC& operator()(KOS_INT row, KOS_INT col);
		KOS_DEC& operator()(KOS_INT row);
		
		// Operator for turning a 1x1 kMatrix into a decimal value.
		KOS_DEC dec() {if(size_r == 1 && size_c == 1) return data[0][0]; else throw Range_Error();}
		
		// Function for performing a reduced row echelon formatting.
		void rref();

		// Function for cleaning out any insanely small values.
		// Anything less than, 1e-x where x is the input variable.
		void clean(int x);

		// Function for displaying the entire matrix to the cout stream.
		void display();
		
		// Assignment operator.
		void operator=(const kMatrix&);
		
		// Basic matrix with ret_val.get_size_c()matrix math functions.
		friend kMatrix operator-(const kMatrix&);
		friend kMatrix operator-(const kMatrix&, const kMatrix&);
		friend kMatrix operator+(const kMatrix&, const kMatrix&);
		friend kMatrix operator*(const kMatrix&, const kMatrix&);
		friend kMatrix operator*(const KOS_DEC&, const kMatrix&);
		friend kMatrix operator*(const kMatrix&, const KOS_DEC&);
		
		// Access operators for determining matrix dimensions.
		KOS_INT get_size_r() const {return size_r;} // Rows
		KOS_INT get_size_c() const {return size_c;} // Columns
		
		// Const data access operator.
		KOS_DEC get_val(KOS_INT row, KOS_INT col) const {if(row >= 0 && row < size_r && col >= 0 && col < size_c) return data[row][col]; else throw Range_Error();}
		
		// Destructor (needed for memory deallocation).
		~kMatrix();
	};
	
	// Helper function for transposing matricies.
	kMatrix transpose(const kMatrix&);
	
	// Helper function for performing reduced row echelon form.
	// kMatrix rref(const kMatrix&);
	
	// Typedef to create a vector type (which is really just a 1d version of the matrix class). 
	typedef kMatrix kVector;
	
	
	
///////////////////////////////////////////////////////////////////////
// 2D Homogeneous Matrix (Statically Allocated)
///////////////////////////////////////////////////////////////////////
		
	class hMatrix {
		KOS_DEC data[4][4]; // Data storage array.
		GLfloat* GL_Table;
		
	public:
		// Constructors.
		hMatrix() {for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) data[i][j] = 0; GL_Table = NULL;}
		hMatrix(const hMatrix& source) {for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) data[i][j] = source.get_val(i,j); GL_Table = NULL;}
		~hMatrix() {if(GL_Table != NULL) delete[] GL_Table;}
		
		// Bracket style NON-const data access operator for assignment and reading.
		KOS_DEC& operator()(KOS_INT row, KOS_INT col) {if(row >= 0 && row < 4 && col >= 0 && col < 4) return data[row][col]; else throw Range_Error();}
		
		// Function for displaying the entire matrix to the cout stream.
		void display();
		
		// Function for returning an OpenGL transformation matrix.
		GLfloat* OGL();

		// Assignment operators. (second operator allows conversion from kMatrix form)
		void operator=(const hMatrix&);
		void operator=(const kMatrix&);
		
		// The *= operator.
		// This operator does a RIGHT SIDE MULTIPLICATION, ie: [result] = [arg1]*[*this]
		// The purpose of this is to tack on homogeneous transforms in logical order.
		hMatrix& operator*=(const hMatrix& arg1);
		
		// Fucntions for matrix math.
		friend hMatrix operator-(const hMatrix&);
		friend hMatrix operator-(const hMatrix&, const hMatrix&);
		friend hMatrix operator+(const hMatrix&, const hMatrix&);
		friend hMatrix operator*(const hMatrix&, const hMatrix&);
		friend hMatrix operator*(const KOS_DEC&, const hMatrix&);
		friend hMatrix operator*(const hMatrix&, const KOS_DEC&);
		
		// Function for transforming an hMatrix into a kMatrix. (this is a ONE WAY operation!)
		operator kMatrix() const {
			kMatrix ret_val(4,4);
			for(int i = 0; i < 4; i++)
				for(int j = 0; j < 4; j++)
					ret_val(i,j) = data[i][j];
			return ret_val;
		}
		
		// Const data access operator.
		KOS_DEC get_val(KOS_INT row, KOS_INT col) const {if(row >= 0 && row < 4 && col >= 0 && col < 4) return data[row][col]; else throw Range_Error();}
	};
	
	// Helper functions for quickly generating transformation matricies.
	hMatrix h_Ident();
	hMatrix h_Scale(const KOS_DEC& scale_x, const KOS_DEC& scale_y, const KOS_DEC& scale_z);
	hMatrix h_Scale(const KOS_DEC& scale);
	hMatrix h_Trans(const KOS_DEC& d_x, const KOS_DEC& d_y, const KOS_DEC& d_z);
	hMatrix h_Rotx(const KOS_DEC& theta_x);
	hMatrix h_Roty(const KOS_DEC& theta_y);
	hMatrix h_Rotz(const KOS_DEC& theta_z);
	hMatrix h_RotQuat(const KOS_DEC& quat_1, const KOS_DEC& quat_2, const KOS_DEC& quat_3, const KOS_DEC& quat_4);
	
///////////////////////////////////////////////////////////////////////
// Homogeneous Vector (Statically Allocated)
///////////////////////////////////////////////////////////////////////
		
	class hVector {
		KOS_DEC data[4]; // Data storage array.
		
	public:
		// Constructors.
		hVector() {for(int i = 0; i < 3; i++) data[i] = 0; data[3] = 1;}
		hVector(const hVector& source) {for(int i = 0; i < 4; i++) data[i] = source.get_val(i);}
		
		// Bracket style NON-const data access operator for assignment and reading.
		KOS_DEC& operator()(KOS_INT row) {if(row >= 0 && row < 4) return data[row]; else throw Range_Error();}
		
		// Function for displaying the entire matrix to the cout stream.
		void display();
		
		// Function to normalize a vector.
		void normalize() {
			KOS_DEC temp = sqrt(data[0]*data[0] + data[1]*data[1] + data[2]*data[2]);
			if(temp != 0) {
				data[0] /= temp;
				data[1] /= temp;
				data[2] /= temp;
			}
		}

		// Magnitude.
		KOS_DEC mag() {
			return sqrt(data[0]*data[0] + data[1]*data[1] + data[2]*data[2]);
		}

		// Assignment operators. (second operator allows conversion from kMatrix form)
		void operator=(const hVector&);
		void operator=(const kMatrix&);
		
		// The *= operator.
		// This operator does a RIGHT SIDE MULTIPLICATION, ie: [result] = [arg1]*[*this]
		// The purpose of this is to tack on homogeneous transforms in logical order.
		hVector& operator*=(const hMatrix& arg1);
		
		// The += operator, works as one would expect.
		hVector& operator+=(const hVector& arg1);

		// Fucntions for matrix math.
		friend hVector operator-(const hVector&);
		friend hVector operator-(const hVector&, const hVector&);
		friend hVector operator+(const hVector&, const hVector&);
		friend hVector operator*(const hMatrix&, const hVector&);
		friend hVector operator*(const KOS_DEC&, const hVector&);
		friend hVector operator*(const hVector&, const KOS_DEC&);
		friend hVector operator/(const hVector&, const KOS_DEC&);
		
		// Function for transforming an hVector into a kMatrix. (this is a ONE WAY operation!)
		operator kMatrix() const {
			kMatrix ret_val(4,1);
			for(int i = 0; i < 4; i++)
				ret_val(i,0) = data[i];
			return ret_val;
		}
		
		// Const data access operator.
		KOS_DEC get_val(KOS_INT row) const {if(row >= 0 && row < 4) return data[row]; else throw Range_Error();}
	};
	
	// Helper functions.
	hVector h_Point(const KOS_DEC& arg_x, const KOS_DEC& arg_y, const KOS_DEC& arg_z); // Creates an hVector representation of a point.
	hVector h_Vec(const KOS_DEC& arg_x, const KOS_DEC& arg_y, const KOS_DEC& arg_z); // Creates an hVector representation of a vector quantity.
	
	// Dot product function.
	KOS_DEC dot(const hVector& arg_1, const hVector& arg_2);

	// Velocity rotation functions.
	hVector h_VRotx(const KOS_DEC& Angle_Pos, const KOS_DEC& Angle_Vel, const hVector& Pos, const hVector& Vel);
	hVector h_VRoty(const KOS_DEC& Angle_Pos, const KOS_DEC& Angle_Vel, const hVector& Pos, const hVector& Vel);
	hVector h_VRotz(const KOS_DEC& Angle_Pos, const KOS_DEC& Angle_Vel, const hVector& Pos, const hVector& Vel);
	hVector h_VRotQuat(const KOS_DEC& Quat1_Pos, const KOS_DEC& Quat2_Pos, const KOS_DEC& Quat3_Pos, const KOS_DEC& Quat4_Pos, const KOS_DEC& Quat1_Vel, const KOS_DEC& Quat2_Vel, const KOS_DEC& Quat3_Vel, const KOS_DEC& Quat4_Vel, const hVector& Pos, const hVector& Vel);

	
} // End of kMath namespace.

#endif /*KMATH_H_*/
