#pragma once

#include "Vector2.h"

namespace GlxNsMath
{
	template<typename T>
	class GlxVector3
	{
	public:
		static_assert(GlxIsFloatingPoint<T>::Value);
		using Type = T;

		static GLX_CONSTEXPR GlxInt32 Size = 3;

	public:
		GlxVector3() = default;

		GlxVector3(const GlxVector3&) = default;
		GlxVector3& operator=(const GlxVector3&) = default;
		GlxVector3(GlxVector3&&) noexcept = default;
		GlxVector3& operator=(GlxVector3&&) noexcept = default;

		GLX_FORCE_INLINE GlxVector3(Type InX, Type InY, Type InZ)
			: X(InX), Y(InY), Z(InZ)
		{}

		GLX_FORCE_INLINE GlxVector3(const GlxVector2<Type>& InXY, Type InZ)
			: X(InXY.X), Y(InXY.Y), Z(InZ)
		{}

		explicit GLX_FORCE_INLINE GlxVector3(Type InXYZ)
			: X(InXYZ), Y(InXYZ), Z(InXYZ)
		{}

		explicit GLX_FORCE_INLINE GlxVector3(const Type* InXYZ)
			: X(InXYZ[0]), Y(InXYZ[1]), Z(InXYZ[2])
		{}

		template<typename U, typename GlxEnableIf<!GlxIsSame<U, Type>::Value, GlxInt32>::Type = 0>
		explicit GLX_FORCE_INLINE GlxVector3(const GlxVector3<U>& InVec3)
			: X(static_cast<Type>(InVec3.X)), Y(static_cast<Type>(InVec3.Y)), Z(static_cast<Type>(InVec3.Z))
		{}

		~GlxVector3() = default;

		GLX_FORCE_INLINE Type& GetX()
		{
			return X;
		}

		GLX_FORCE_INLINE Type& GetY()
		{
			return Y;
		}

		GLX_FORCE_INLINE Type& GetZ()
		{
			return Z;
		}

		GLX_FORCE_INLINE Type GetX() const
		{
			return X;
		}

		GLX_FORCE_INLINE Type GetY() const
		{
			return Y;
		}

		GLX_FORCE_INLINE Type GetZ() const
		{
			return Z;
		}

		GLX_FORCE_INLINE Type& operator[](GlxInt32 InIndex)
		{
			return XYZ[InIndex];
		}

		GLX_FORCE_INLINE Type operator[](GlxInt32 InIndex) const
		{
			return XYZ[InIndex];
		}

		GLX_FORCE_INLINE GlxBool operator==(const GlxVector3& InVec3) const
		{
			return X == InVec3.X && Y == InVec3.Y && Z == InVec3.Z;
		}

		GLX_FORCE_INLINE GlxBool operator!=(const GlxVector3& InVec3) const
		{
			return X != InVec3.X || Y != InVec3.Y || Z != InVec3.Z;
		}

		GLX_FORCE_INLINE GlxBool operator>(const GlxVector3& InVec3) const
		{
			return X > InVec3.X && Y > InVec3.Y && Z > InVec3.Z;
		}

		GLX_FORCE_INLINE GlxBool operator>=(const GlxVector3& InVec3) const
		{
			return X >= InVec3.X && Y >= InVec3.Y && Z >= InVec3.Z;
		}

		GLX_FORCE_INLINE GlxBool operator<(const GlxVector3& InVec3) const
		{
			return X < InVec3.X && Y < InVec3.Y && Z < InVec3.Z;
		}

		GLX_FORCE_INLINE GlxBool operator<=(const GlxVector3& InVec3) const
		{
			return X <= InVec3.X && Y <= InVec3.Y && Z <= InVec3.Z;
		}

		GLX_FORCE_INLINE GlxVector3 operator-() const
		{
			return GlxVector3(-X, -Y, -Z);
		}

		GLX_FORCE_INLINE GlxVector3 operator+(const GlxVector3& InVec3) const
		{
			return GlxVector3(X + InVec3.X, Y + InVec3.Y, Z + InVec3.Z);
		}

		GLX_FORCE_INLINE GlxVector3 operator-(const GlxVector3& InVec3) const
		{
			return GlxVector3(X - InVec3.X, Y - InVec3.Y, Z - InVec3.Z);
		}

		GLX_FORCE_INLINE GlxVector3 operator*(const GlxVector3& InVec3) const
		{
			return GlxVector3(X * InVec3.X, Y * InVec3.Y, Z * InVec3.Z);
		}

		GLX_FORCE_INLINE GlxVector3 operator/(const GlxVector3& InVec3) const
		{
			return GlxVector3(X / InVec3.X, Y / InVec3.Y, Z / InVec3.Z);
		}

		GLX_FORCE_INLINE GlxVector3 operator+(Type InVal) const
		{
			return GlxVector3(X + InVal, Y + InVal, Z + InVal);
		}

		GLX_FORCE_INLINE GlxVector3 operator-(Type InVal) const
		{
			return GlxVector3(X - InVal, Y - InVal, Z - InVal);
		}

		GLX_FORCE_INLINE GlxVector3 operator*(Type InVal) const
		{
			return GlxVector3(X * InVal, Y * InVal, Z * InVal);
		}

		GLX_FORCE_INLINE GlxVector3 operator/(Type InVal) const
		{
			return GlxVector3(X / InVal, Y / InVal, Z / InVal);
		}

		friend GLX_FORCE_INLINE GlxVector3 operator*(Type InLhs, const GlxVector3& InRhs)
		{
			return GlxVector3(InLhs * InRhs.X, InLhs * InRhs.Y, InLhs * InRhs.Z);
		}

		GLX_FORCE_INLINE GlxVector3& operator+=(const GlxVector3& InVec3)
		{
			X += InVec3.X;
			Y += InVec3.Y;
			Z += InVec3.Z;
			return *this;
		}

		GLX_FORCE_INLINE GlxVector3& operator-=(const GlxVector3& InVec3)
		{
			X -= InVec3.X;
			Y -= InVec3.Y;
			Z -= InVec3.Z;
			return *this;
		}

		GLX_FORCE_INLINE GlxVector3& operator*=(const GlxVector3& InVec3)
		{
			X *= InVec3.X;
			Y *= InVec3.Y;
			Z *= InVec3.Z;
			return *this;
		}

		GLX_FORCE_INLINE GlxVector3& operator/=(const GlxVector3& InVec3)
		{
			X /= InVec3.X;
			Y /= InVec3.Y;
			Z /= InVec3.Z;
			return *this;
		}

		GLX_FORCE_INLINE GlxVector3& operator+=(Type InVal)
		{
			X += InVal;
			Y += InVal;
			Z += InVal;
			return *this;
		}

		GLX_FORCE_INLINE GlxVector3& operator-=(Type InVal)
		{
			X -= InVal;
			Y -= InVal;
			Z -= InVal;
			return *this;
		}

		GLX_FORCE_INLINE GlxVector3& operator*=(Type InVal)
		{
			X *= InVal;
			Y *= InVal;
			Z *= InVal;
			return *this;
		}

		GLX_FORCE_INLINE GlxVector3& operator/=(Type InVal)
		{
			X /= InVal;
			Y /= InVal;
			Z /= InVal;
			return *this;
		}

		union
		{
			struct
			{
				Type X;
				Type Y;
				Type Z;
			};

			Type XYZ[Size];
		};

		static const GlxVector3 Zero;
		static const GlxVector3 One;
		static const GlxVector3 UnitX;
		static const GlxVector3 UnitY;
		static const GlxVector3 UnitZ;

		static const GlxVector3 Up;
		static const GlxVector3 Down;
		static const GlxVector3 Right;
		static const GlxVector3 Left;
		static const GlxVector3 Forward;
		static const GlxVector3 Backward;
	};

	template<typename T>
	const GlxVector3<T> GlxVector3<T>::Zero = GlxVector3<T>{ static_cast<T>(0), static_cast<T>(0), static_cast<T>(0) };
	template<typename T>
	const GlxVector3<T> GlxVector3<T>::One = GlxVector3<T>{ static_cast<T>(1), static_cast<T>(1), static_cast<T>(1) };
	template<typename T>
	const GlxVector3<T> GlxVector3<T>::UnitX = GlxVector3<T>{ static_cast<T>(1), static_cast<T>(0), static_cast<T>(0) };
	template<typename T>
	const GlxVector3<T> GlxVector3<T>::UnitY = GlxVector3<T>{ static_cast<T>(0), static_cast<T>(1), static_cast<T>(0) };
	template<typename T>
	const GlxVector3<T> GlxVector3<T>::UnitZ = GlxVector3<T>{ static_cast<T>(0), static_cast<T>(0), static_cast<T>(1) };

	template<typename T>
	const GlxVector3<T> GlxVector3<T>::Up = GlxVector3<T>{ static_cast<T>(0), static_cast<T>(1), static_cast<T>(0) };
	template<typename T>
	const GlxVector3<T> GlxVector3<T>::Down = GlxVector3<T>{ static_cast<T>(0), static_cast<T>(-1), static_cast<T>(0) };
	template<typename T>
	const GlxVector3<T> GlxVector3<T>::Right = GlxVector3<T>{ static_cast<T>(1), static_cast<T>(0), static_cast<T>(0) };
	template<typename T>
	const GlxVector3<T> GlxVector3<T>::Left = GlxVector3<T>{ static_cast<T>(-1), static_cast<T>(0), static_cast<T>(0) };
	template<typename T>
	const GlxVector3<T> GlxVector3<T>::Forward = GlxVector3<T>{ static_cast<T>(0), static_cast<T>(0), static_cast<T>(1) };
	template<typename T>
	const GlxVector3<T> GlxVector3<T>::Backward = GlxVector3<T>{ static_cast<T>(0), static_cast<T>(0), static_cast<T>(-1) };

	using GlxVector3f = GlxVector3<GlxFloat>;
	using GlxVector3d = GlxVector3<GlxDouble>;
	using GlxVector3ld = GlxVector3<GlxLongDouble>;
}
