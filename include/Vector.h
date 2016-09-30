#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
const float PI = 3.14159265f;
const float DEGS_TO_RADS = PI/180.f;

// Simple 2D vector class
class Vector
{
	public:
		Vector();
		Vector(float x, float y);

		void SetAngle(float angle);
		float Angle() const;
		float Length() const;
		bool IsZero();
		void Zero();

		// Operators
		Vector operator+ (const Vector& v);
		Vector operator- (const Vector& v);
		Vector operator* (const Vector& v);
		Vector operator/ (const Vector& v);

		void operator+= (const Vector& v);
		void operator-= (const Vector& v);
		void operator*= (const Vector& v);
		void operator/= (const Vector& v);

		Vector operator+ (float f);
		Vector operator- (float f);
		Vector operator* (float f);
		Vector operator/ (float f);

		void operator+= (float f);
		void operator-= (float f);
		void operator*= (float f);
		void operator/= (float f);

		bool operator== (const Vector& v);
		bool operator!= (const Vector& v);

		float x; // public access
		float y;
};

#endif