#pragma once
#ifndef UTIL_LINALG_H_
#define UTIL_LINALG_H_

typedef float float_t;

namespace mth
{
	const float_t pi = 3.1415926536f;

	class float2;
	class float3;
	class float4;

	class float2x2;
	class float3x3;
	class float4x4;
	typedef float4x4 matrix;

	class float2
	{
	public:
		float_t x;
		float_t y;

	public:
		float2();
		float2(const float_t f);
		float2(const float_t * const v);
		float2(const float_t x, const float_t y);
		float2(const float2& v);
		float2(const float2* v);
		bool isZeroVector() const;
		float_t Dot(const float2 v) const;
		float_t LengthSquare() const;
		float_t Length() const;
		void Abs();
		void Normalize();
		float2 Normalized() const;
		float2 operator+(const float2 v) const;
		float2 operator-(const float2 v) const;
		float2 operator*(const float2 v) const;
		float2 operator/(const float2 v) const;
		float2 operator+(const float_t f) const;
		float2 operator-(const float_t f) const;
		float2 operator*(const float_t f) const;
		float2 operator/(const float_t f) const;
		float2 operator-() const;
		float2& operator+=(const float2 v);
		float2& operator-=(const float2 v);
		float2& operator*=(const float2 v);
		float2& operator/=(const float2 v);
		float2& operator=(const float2 v);
		float2& operator+=(const float_t f);
		float2& operator-=(const float_t f);
		float2& operator*=(const float_t f);
		float2& operator/=(const float_t f);
		float2& operator=(const float_t f);
		float2 operator*(const float2x2& m) const;
		float_t operator()(const int i) const;
		float_t& operator()(const int i);
		operator float3() const;
		operator float4() const;
		operator float_t*() const;
	};

	class float3
	{
	public:
		float_t x;
		float_t y;
		float_t z;

	public:
		float3();
		float3(const float_t f);
		float3(const float_t * const v);
		float3(const float_t x, const float_t y, const float_t z);
		float3(const float3& v);
		float3(const float3* v);
		bool isZeroVector() const;
		float_t Dot(const float3 v) const;
		float3 Cross(const float3 v) const;
		float_t LengthSquare() const;
		float_t Length() const;
		void Abs();
		void Normalize();
		float3 Normalized() const;
		float3 operator+(const float3 v) const;
		float3 operator-(const float3 v) const;
		float3 operator*(const float3 v) const;
		float3 operator/(const float3 v) const;
		float3 operator+(const float_t f) const;
		float3 operator-(const float_t f) const;
		float3 operator*(const float_t f) const;
		float3 operator/(const float_t f) const;
		float3 operator-() const;
		float3& operator+=(const float3 v);
		float3& operator-=(const float3 v);
		float3& operator*=(const float3 v);
		float3& operator/=(const float3 v);
		float3& operator=(const float3 v);
		float3& operator+=(const float_t f);
		float3& operator-=(const float_t f);
		float3& operator*=(const float_t f);
		float3& operator/=(const float_t f);
		float3& operator=(const float_t f);
		float3 operator*(const float3x3& m) const;
		float_t operator()(const int i) const;
		float_t& operator()(const int i);
		operator float2() const;
		operator float4() const;
		operator float_t*() const;
	};

	class float4
	{
	public:
		float_t x;
		float_t y;
		float_t z;
		float_t w;

	public:
		float4();
		float4(const float_t f);
		float4(const float_t * const v);
		float4(const float_t x, const float_t y, const float_t z, const float_t w);
		float4(const float4& v);
		float4(const float4* v);
		bool isZeroVector() const;
		float_t Dot(const float4 v) const;
		float_t LengthSquare() const;
		float_t Length() const;
		void Abs();
		void Normalize();
		float4 Normalized() const;
		float4 operator+(const float4 v) const;
		float4 operator-(const float4 v) const;
		float4 operator*(const float4 v) const;
		float4 operator/(const float4 v) const;
		float4 operator+(const float_t f) const;
		float4 operator-(const float_t f) const;
		float4 operator*(const float_t f) const;
		float4 operator/(const float_t f) const;
		float4 operator-() const;
		float4& operator+=(const float4 v);
		float4& operator-=(const float4 v);
		float4& operator*=(const float4 v);
		float4& operator/=(const float4 v);
		float4& operator=(const float4 v);
		float4& operator+=(const float_t f);
		float4& operator-=(const float_t f);
		float4& operator*=(const float_t f);
		float4& operator/=(const float_t f);
		float4& operator=(const float_t f);
		float4 operator*(const float4x4& m) const;
		float_t operator()(const int i) const;
		float_t& operator()(const int i);
		operator float2() const;
		operator float3() const;
		operator float_t*() const;
	};

	class float2x2
	{
		float_t mat[2][2];

	public:
		float2x2();
		float2x2(const float_t f);
		float2x2(const float_t * const m);
		float2x2(const float_t _00, const float_t _01, const float_t _10, const float_t _11);
		float2x2(const float2x2& m);
		float2x2(const float2x2* m);
		static float2x2 Identity();
		static float2x2 Rotation(const float_t a);
		static float2x2 Scaling(const float_t x, const float_t y);
		static float2x2 Scaling(const float2 s);
		static float2x2 RotationScaling(const float_t a, const float_t x, const float_t y);
		static float2x2 RotationScaling(const float_t a, const float2 s);

		float_t operator()(const int row, const int column) const;
		float_t& operator()(const int row, const int column);
		float2 operator*(const float2 v) const;
		operator float3x3() const;
		operator float4x4() const;
		float_t Determinant() const;
		void Invert();
		float2x2 Inverse() const;
		void Transpose();
		float2x2 Trasposed() const;
		float2x2 operator*(const float2x2& m) const;
		float2x2& operator*=(const float2x2& m);
		float2x2 operator+(const float2x2& m) const;
		float2x2& operator+=(const float2x2& m);
		float2x2 operator-(const float2x2& m) const;
		float2x2& operator-=(const float2x2& m);
		float2x2& operator=(const float2x2& m);
		float2x2 operator+(const float_t f) const;
		float2x2& operator+=(const float_t f);
		float2x2 operator-(const float_t f) const;
		float2x2& operator-=(const float_t f);
		float2x2 operator*(const float_t f) const;
		float2x2& operator*=(const float_t f);
		float2x2 operator/(const float_t f) const;
		float2x2& operator/=(const float_t f);
		float2x2& operator=(const float_t f);
		float2x2 operator-() const;
	};

	class float3x3
	{
		float_t mat[3][3];

	public:
		float3x3();
		float3x3(const float_t f);
		float3x3(const float_t * const m);
		float3x3(const float_t _00, const float_t _01, const float_t _02,
			const float_t _10, const float_t _11, const float_t _12,
			const float_t _20, const float_t _21, const float_t _22);
		float3x3(const float3x3& m);
		float3x3(const float3x3* m);
		static float3x3 Identity();
		static float3x3 Scaling2D(const float_t x, const float_t y);
		static float3x3 Scaling2D(const float2 s);
		static float3x3 Translation2D(const float_t x, const float_t y);
		static float3x3 Translation2D(const float2 t);
		static float3x3 Rotation2D(const float_t a);
		static float3x3 Scaling(const float_t x, const float_t y, const float_t z);
		static float3x3 Scaling(const float3 s);
		static float3x3 RotationX(const float_t a);
		static float3x3 RotationY(const float_t a);
		static float3x3 RotationZ(const float_t a);
		static float3x3 Rotation(const float_t pitch, const float_t yaw, const float_t roll);
		static float3x3 Rotation(const float3 r);
		static float3x3 RotationAxis(const float3 axis, const float_t a);
		static float3x3 RotationNormal(const float3 n, const float_t a);

		float_t operator()(const int row, const int column) const;
		float_t& operator()(const int row, const int column);
		float3 operator*(const float3 v) const;
		operator float2x2() const;
		operator float4x4() const;
		float_t Determinant() const;
		void Invert();
		float3x3 Inverse() const;
		void Transpose();
		float3x3 Trasposed() const;
		float3x3 operator*(const float3x3& m) const;
		float3x3& operator*=(const float3x3& m);
		float3x3 operator+(const float3x3& m) const;
		float3x3& operator+=(const float3x3& m);
		float3x3 operator-(const float3x3& m) const;
		float3x3& operator-=(const float3x3& m);
		float3x3& operator=(const float3x3& m);
		float3x3 operator+(const float_t f) const;
		float3x3& operator+=(const float_t f);
		float3x3 operator-(const float_t f) const;
		float3x3& operator-=(const float_t f);
		float3x3 operator*(const float_t f) const;
		float3x3& operator*=(const float_t f);
		float3x3 operator/(const float_t f) const;
		float3x3& operator/=(const float_t f);
		float3x3& operator=(const float_t f);
		float3x3 operator-() const;
	};

	class float4x4
	{
		float_t mat[4][4];

	public:
		float4x4();
		float4x4(const float_t f);
		float4x4(const float_t * const m);
		float4x4(const float_t _00, const float_t _01, const float_t _02, const float_t _03,
			const float_t _10, const float_t _11, const float_t _12, const float_t _13,
			const float_t _20, const float_t _21, const float_t _22, const float_t _23,
			const float_t _30, const float_t _31, const float_t _32, const float_t _33);
		float4x4(const float4x4& m);
		float4x4(const float4x4* m);
		static float4x4 Identity();
		static float4x4 Scaling(const float_t x, const float_t y, const float_t z);
		static float4x4 Scaling(const float3 s);
		static float4x4 Translation(const float_t x, const float_t y, const float_t z);
		static float4x4 Translation(const float3 t);
		static float4x4 RotationX(const float_t a);
		static float4x4 RotationY(const float_t a);
		static float4x4 RotationZ(const float_t a);
		static float4x4 Rotation(const float_t pitch, const float_t yaw, const float_t roll);
		static float4x4 Rotation(const float3 r);
		static float4x4 RotationAxis(const float3 axis, const float_t a);
		static float4x4 RotationNormal(const float3 n, const float_t a);
		static float4x4 ScalingRotationTranslation(const float_t sx, const float_t sy, const float_t sz,
			const float_t pitch, const float_t yaw, const float_t roll,
			const float_t tx, const float_t ty, const float_t tz);
		static float4x4 ScalingRotationTranslation(const float3 s, const float3 r, const float3 t);
		static float4x4 PerspectiveFOV(const float_t fov, const float_t screenAspect, const float_t screenNear, const float_t screenDepth);
		static float4x4 Orthographic(const float_t viewWidth, const float_t viewHeight, const float_t screenNear, const float_t screenDepth);
		static float4x4 LookTo(const float3 eye, const float3 direction, const float3 up);
		static float4x4 LookAt(const float3 eye, const float3 focus, const float3 up);

		float_t operator()(const int row, const int column) const;
		float_t& operator()(const int row, const int column);
		float4 operator*(const float4 v) const;
		operator float2x2() const;
		operator float3x3() const;
		float_t Determinant() const;
		void Invert();
		float4x4 Inverse() const;
		void Transpose();
		float4x4 Transposed() const;
		float4x4 operator*(const float4x4& m)const;
		float4x4& operator*=(const float4x4& m);
		float4x4 operator+(const float4x4& m) const;
		float4x4& operator+=(const float4x4& m);
		float4x4 operator-(const float4x4& m) const;
		float4x4& operator-=(const float4x4& m);
		float4x4& operator=(const float4x4& m);
		float4x4 operator+(const float_t f) const;
		float4x4& operator+=(const float_t f);
		float4x4 operator-(const float_t f) const;
		float4x4& operator-=(const float_t f);
		float4x4 operator*(const float_t f) const;
		float4x4& operator*=(const float_t f);
		float4x4 operator/(const float_t f) const;
		float4x4& operator/=(const float_t f);
		float4x4& operator=(const float_t f);
		float4x4 operator-() const;
	};


	float2 operator+(const float_t f, const float2 v);
	float3 operator+(const float_t f, const float3 v);
	float4 operator+(const float_t f, const float4 v);
	float2x2 operator+(const float_t f, const float2x2 m);
	float3x3 operator+(const float_t f, const float3x3 m);
	float4x4 operator+(const float_t f, const float4x4 m);

	float2 operator-(const float_t f, const float2 v);
	float3 operator-(const float_t f, const float3 v);
	float4 operator-(const float_t f, const float4 v);
	float2x2 operator-(const float_t f, const float2x2 m);
	float3x3 operator-(const float_t f, const float3x3 m);
	float4x4 operator-(const float_t f, const float4x4 m);

	float2 operator*(const float_t f, const float2 v);
	float3 operator*(const float_t f, const float3 v);
	float4 operator*(const float_t f, const float4 v);
	float2x2 operator*(const float_t f, const float2x2 m);
	float3x3 operator*(const float_t f, const float3x3 m);
	float4x4 operator*(const float_t f, const float4x4 m);
}
#endif /* UTIL_LINALG_H_ */
