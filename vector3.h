#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include <math.h>

class Vector3 {
public:
	float f[3];

	Vector3(float x, float y, float z) {
		f[0] =x;
		f[1] =y;
		f[2] =z;
	}
	 
	Vector3() {}
	
	float length() const {
		return sqrt(f[0]*f[0]+f[1]*f[1]+f[2]*f[2]);
	}

	Vector3 normalized() const {
		float l = length();
		return Vector3(f[0]/l,f[1]/l,f[2]/l);
	}

	void operator+= (const Vector3& v) {
		f[0]+=v.f[0];
		f[1]+=v.f[1];
		f[2]+=v.f[2];
	}

	Vector3 operator/ (float a) const {
		return Vector3(f[0]/a,f[1]/a,f[2]/a);
	}

	Vector3 operator- (const Vector3& v) const {
		return Vector3(f[0]-v.f[0],f[1]-v.f[1],f[2]-v.f[2]);
	}

	Vector3 operator+ (const Vector3& v) const {
		return Vector3(f[0]+v.f[0],f[1]+v.f[1],f[2]+v.f[2]);
	}

	Vector3 operator* (const float &a) const {
		return Vector3(f[0]*a,f[1]*a,f[2]*a);
	}
	
	Vector3 operator *= (const float &a) {
		f[0] *= a;
		f[1] *= a;
		f[2] *= a;
		return *this;
	}

	Vector3 operator-() const {
		return Vector3(-f[0],-f[1],-f[2]);
	}

	Vector3 cross(const Vector3& v) const {
		return Vector3(f[1]*v.f[2] - f[2]*v.f[1], f[2]*v.f[0] - f[0]*v.f[2], f[0]*v.f[1] - f[1]*v.f[0]);
	}

	float dot(const Vector3& v) const {
		return f[0]*v.f[0] + f[1]*v.f[1] + f[2]*v.f[2];
	}
};

#endif // __VECTOR3_H__