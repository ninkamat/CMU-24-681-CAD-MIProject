#ifndef VECTOR_NAK_IS_INCLUDED
#define VECTOR_NAK_IS_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

////////////////////////////////////////////////////////////////////////////////
//GENERIC VECTOR CLASS
////////////////////////////////////////////////////////////////////////////////

template <class T>
class Vec
{
protected:
	T *dat;
	long long int mysize;
	long long int available;
	void Cleanup();
	void Grow();
	void CopyFrom(const Vec &in);
	void Swap(Vec &in);
public:
	Vec();
	Vec(const Vec &in);
	Vec(Vec &&in);
	Vec &operator=(const Vec &in);
	Vec &operator=(Vec &&in);
	~Vec();
	long long int size() const;
	void clear();
	void resize(long long int newsize);
	T &operator[](const int n);
	const T &operator[](const int n) const;
	void push_back(const T &incoming);
	void pop_back();
	Vec *begin();
	Vec *end();
	const T *data() const;
	const Vec GetVecData() const;
	const T &front() const;
	T &front();
	const T &back() const;
	T &back();
};

////////////////////////////////////////////////////////////////////////////////
//LENGTH VECTOR CLASS
////////////////////////////////////////////////////////////////////////////////

template <class T, long long int nc>
class VecN : public Vec<T>
{
public:
	VecN();
	VecN &operator+=(const VecN rhs);
	VecN &operator-=(const VecN rhs);
	friend T dot(VecN a, VecN b);
	friend VecN operator*(const T lhs, VecN rhs);
	friend VecN operator*(VecN lhs, const T rhs);
	friend VecN operator+(VecN lhs, const VecN &rhs);
	friend VecN operator-(VecN lhs, const VecN &rhs);
	friend VecN operator/(const VecN &lhs, const T rhs);
	friend bool operator==(const VecN &lhs, const VecN &rhs);
	friend bool operator!=(const VecN &lhs, const VecN &rhs);
	friend double L2Norm(VecN a);
};

////////////////////////////////////////////////////////////////////////////////
//3-D DOUBLE VECTOR CLASS
////////////////////////////////////////////////////////////////////////////////

class Vec3 : public VecN<double,3>
{
public:
	Vec3();
	Vec3(double x, double y, double z);
	void Set(double x, double y, double z);
	void Normalize();
	friend Vec3 cross(Vec3 a, Vec3 b);
	const double xf() const;
	const double yf() const;
	const double zf() const;
    inline static Vec3 conv(VecN<double,3> a)
    {
        auto dat = a.data();
        return Vec3(dat[0],dat[1],dat[2]);
    }
    inline static Vec3 GetProjection(Vec3 N, Vec3 X, Vec3 Y);
};

double DistancePtToLine(Vec3 x1, Vec3 x2, Vec3 x0)
{
	double t = -1.0*dot((x1-x0),(x2-x1))/pow((L2Norm(x2-x1)),2.0);
	auto temp = ((x1-x0)+(x2-x0))*t;
	return L2Norm(temp);
}

inline Vec3 Vec3::GetProjection(Vec3 N, Vec3 X, Vec3 Y)
{
    N.Normalize();
    double d = dot(N, X-Y);
    return conv(Y - d*N);
}

#endif