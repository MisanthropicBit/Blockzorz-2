#ifndef BLOCKZORZ2_VECTOR_HPP
#define BLOCKZORZ2_VECTOR_HPP

#include <math.h>

const float PI           = 3.14159265f;
const float DEGS_TO_RADS = PI/180.f;

// TODO: vector -> vector2?
class vector {
	public:
		vector();
		vector(float x, float y);

		void set_angle(float angle);
		float angle() const;
		float length() const;
		bool is_zero();
		void zero();

		// Operators
		vector operator+ (const vector& v);
		vector operator- (const vector& v);
		vector operator* (const vector& v);
		vector operator/ (const vector& v);

		void operator+= (const vector& v);
		void operator-= (const vector& v);
		void operator*= (const vector& v);
		void operator/= (const vector& v);

		vector operator+ (float f);
		vector operator- (float f);
		vector operator* (float f);
		vector operator/ (float f);

		void operator+= (float f);
		void operator-= (float f);
		void operator*= (float f);
		void operator/= (float f);

		bool operator== (const vector& v);
		bool operator!= (const vector& v);

		float x; // public access
		float y;
};

#endif
