#ifndef BLOCKZORZ2_VECTOR2_HPP
#define BLOCKZORZ2_VECTOR2_HPP

const float PI           = 3.14159265f;
const float DEGS_TO_RADS = PI / 180.f;

class vector2 {
	public:
		vector2();
		vector2(float x, float y);

		void set_angle(float angle);
		float angle() const;
		float length() const;
		bool is_zero() const;
		void zero();

		// Operators
		vector2 operator+(const vector2& v);
		vector2 operator-(const vector2& v);
		vector2 operator*(const vector2& v);
		vector2 operator/(const vector2& v);

		vector2& operator+=(const vector2& v);
		vector2& operator-=(const vector2& v);
		vector2& operator*=(const vector2& v);
		vector2& operator/=(const vector2& v);

		vector2 operator+(float f);
		vector2 operator-(float f);
		vector2 operator*(float f);
		vector2 operator/(float f);

		vector2& operator+=(float f);
		vector2& operator-=(float f);
		vector2& operator*=(float f);
		vector2& operator/=(float f);

		bool operator==(const vector2& v);
		bool operator!=(const vector2& v);

		float x; // public access
		float y;
};

#endif
