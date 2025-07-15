#pragma once

#include "Vector3.h"

namespace GlxNsMath
{
	template<typename T>
	class GlxVector4
	{
	public:
		static_assert(GlxIsFloatingPoint<T>::Value);
		using Type = T;

		static GLX_CONSTEXPR GlxInt32 Size = 4;

	public:
		GlxVector4() = default;

		GlxVector4(const GlxVector4&) = default;
		GlxVector4& operator=(const GlxVector4&) = default;
		GlxVector4(GlxVector4&&) noexcept = default;
		GlxVector4& operator=(GlxVector4&&) noexcept = default;

		GLX_FORCE_INLINE GlxVector4(Type InX, Type InY, Type InZ, Type InW)
			: X(InX), Y(InY), Z(InZ), W(InW)
		{}

		GLX_FORCE_INLINE GlxVector4(const GlxVector3<Type>& InXYZ, Type InW)
			: X(InXYZ.X), Y(InXYZ.Y), Z(InXYZ.Z), W(InW)
		{}

		GLX_FORCE_INLINE GlxVector4(const GlxVector2<Type>& InXY, const GlxVector2<Type>& InZW)
			: X(InXY.X), Y(InXY.Y), Z(InZW.X), W(InZW.Y)
		{}

		explicit GLX_FORCE_INLINE GlxVector4(Type InXYZW)
			: X(InXYZW), Y(InXYZW), Z(InXYZW), W(InXYZW)
		{}

		explicit GLX_FORCE_INLINE GlxVector4(const Type* InXYZW)
			: X(InXYZW[0]), Y(InXYZW[1]), Z(InXYZW[2]), W(InXYZW[3])
		{}

		template<typename U, typename GlxEnableIf<!GlxIsSame<U, Type>::Value, GlxInt32>::Type = 0>
		explicit GLX_FORCE_INLINE GlxVector4(const GlxVector4<U>& InVec4)
			: X(static_cast<Type>(InVec4.X)), Y(static_cast<Type>(InVec4.Y)), Z(static_cast<Type>(InVec4.Z)), W(static_cast<Type>(InVec4.W))
		{}

		~GlxVector4() = default;

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

		GLX_FORCE_INLINE Type& GetW()
		{
			return W;
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

		GLX_FORCE_INLINE Type GetW() const
		{
			return W;
		}

		GLX_FORCE_INLINE Type& operator[](GlxInt32 InIndex)
		{
			return XYZW[InIndex];
		}

		GLX_FORCE_INLINE Type operator[](GlxInt32 InIndex) const
		{
			return XYZW[InIndex];
		}

		GLX_FORCE_INLINE GlxBool operator==(const GlxVector4& InVec4) const
		{
			return X == InVec4.X && Y == InVec4.Y && Z == InVec4.Z && W == InVec4.W;
		}

		GLX_FORCE_INLINE GlxBool operator!=(const GlxVector4& InVec4) const
		{
			return X != InVec4.X || Y != InVec4.Y || Z != InVec4.Z || W != InVec4.W;
		}

		GLX_FORCE_INLINE GlxBool operator>(const GlxVector4& InVec4) const
		{
			return X > InVec4.X && Y > InVec4.Y && Z > InVec4.Z && W > InVec4.W;
		}

		GLX_FORCE_INLINE GlxBool operator>=(const GlxVector4& InVec4) const
		{
			return X >= InVec4.X && Y >= InVec4.Y && Z >= InVec4.Z && W >= InVec4.W;
		}

		GLX_FORCE_INLINE GlxBool operator<(const GlxVector4& InVec4) const
		{
			return X < InVec4.X && Y < InVec4.Y && Z < InVec4.Z && W < InVec4.W;
		}

		GLX_FORCE_INLINE GlxBool operator<=(const GlxVector4& InVec4) const
		{
			return X <= InVec4.X && Y <= InVec4.Y && Z <= InVec4.Z && W <= InVec4.W;
		}

		GLX_FORCE_INLINE GlxVector4 operator-() const
		{
			return GlxVector4(-X, -Y, -Z, -W);
		}

		GLX_FORCE_INLINE GlxVector4 operator+(const GlxVector4& InVec4) const
		{
			return GlxVector4(X + InVec4.X, Y + InVec4.Y, Z + InVec4.Z, W + InVec4.W);
		}

		GLX_FORCE_INLINE GlxVector4 operator-(const GlxVector4& InVec4) const
		{
			return GlxVector4(X - InVec4.X, Y - InVec4.Y, Z - InVec4.Z, W - InVec4.W);
		}

		GLX_FORCE_INLINE GlxVector4 operator*(const GlxVector4& InVec4) const
		{
			return GlxVector4(X * InVec4.X, Y * InVec4.Y, Z * InVec4.Z, W * InVec4.W);
		}

		GLX_FORCE_INLINE GlxVector4 operator/(const GlxVector4& InVec4) const
		{
			return GlxVector4(X / InVec4.X, Y / InVec4.Y, Z / InVec4.Z, W / InVec4.W);
		}

		GLX_FORCE_INLINE GlxVector4 operator+(Type InVal) const
		{
			return GlxVector4(X + InVal, Y + InVal, Z + InVal, W + InVal);
		}

		GLX_FORCE_INLINE GlxVector4 operator-(Type InVal) const
		{
			return GlxVector4(X - InVal, Y - InVal, Z - InVal, W - InVal);
		}

		GLX_FORCE_INLINE GlxVector4 operator*(Type InVal) const
		{
			return GlxVector4(X * InVal, Y * InVal, Z * InVal, W * InVal);
		}

		GLX_FORCE_INLINE GlxVector4 operator/(Type InVal) const
		{
			return GlxVector4(X / InVal, Y / InVal, Z / InVal, W / InVal);
		}

		friend GLX_FORCE_INLINE GlxVector4 operator*(Type InLhs, const GlxVector4& InRhs)
		{
			return GlxVector4(InLhs * InRhs.X, InLhs * InRhs.Y, InLhs * InRhs.Z, InLhs * InRhs.W);
		}

		GLX_FORCE_INLINE GlxVector4& operator+=(const GlxVector4& InVec4)
		{
			X += InVec4.X;
			Y += InVec4.Y;
			Z += InVec4.Z;
			W += InVec4.W;
			return *this;
		}

		GLX_FORCE_INLINE GlxVector4& operator-=(const GlxVector4& InVec4)
		{
			X -= InVec4.X;
			Y -= InVec4.Y;
			Z -= InVec4.Z;
			W -= InVec4.W;
			return *this;
		}

		GLX_FORCE_INLINE GlxVector4& operator*=(const GlxVector4& InVec4)
		{
			X *= InVec4.X;
			Y *= InVec4.Y;
			Z *= InVec4.Z;
			W *= InVec4.W;
			return *this;
		}

		GLX_FORCE_INLINE GlxVector4& operator/=(const GlxVector4& InVec4)
		{
			X /= InVec4.X;
			Y /= InVec4.Y;
			Z /= InVec4.Z;
			W /= InVec4.W;
			return *this;
		}

		GLX_FORCE_INLINE GlxVector4& operator+=(Type InVal)
		{
			X += InVal;
			Y += InVal;
			Z += InVal;
			W += InVal;
			return *this;
		}

		GLX_FORCE_INLINE GlxVector4& operator-=(Type InVal)
		{
			X -= InVal;
			Y -= InVal;
			Z -= InVal;
			W -= InVal;
			return *this;
		}

		GLX_FORCE_INLINE GlxVector4& operator*=(Type InVal)
		{
			X *= InVal;
			Y *= InVal;
			Z *= InVal;
			W *= InVal;
			return *this;
		}

		GLX_FORCE_INLINE GlxVector4& operator/=(Type InVal)
		{
			X /= InVal;
			Y /= InVal;
			Z /= InVal;
			W /= InVal;
			return *this;
		}

		union
		{
			struct
			{
				Type X;
				Type Y;
				Type Z;
				Type W;
			};

			Type XYZW[Size];
		};

		static const GlxVector4 Zero;
		static const GlxVector4 One;
		static const GlxVector4 UnitX;
		static const GlxVector4 UnitY;
		static const GlxVector4 UnitZ;
		static const GlxVector4 UnitW;
	};

	template<typename T>
	const GlxVector4<T> GlxVector4<T>::Zero = GlxVector4<T>{
		static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)
	};
	template<typename T>
	const GlxVector4<T> GlxVector4<T>::One = GlxVector4<T>{
		static_cast<T>(1), static_cast<T>(1), static_cast<T>(1), static_cast<T>(1)
	};
	template<typename T>
	const GlxVector4<T> GlxVector4<T>::UnitX = GlxVector4<T>{
		static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)
	};
	template<typename T>
	const GlxVector4<T> GlxVector4<T>::UnitY = GlxVector4<T>{
		static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0)
	};
	template<typename T>
	const GlxVector4<T> GlxVector4<T>::UnitZ = GlxVector4<T>{
		static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0)
	};
	template<typename T>
	const GlxVector4<T> GlxVector4<T>::UnitW = GlxVector4<T>{
		static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
	};

	using GlxVector4f = GlxVector4<GlxFloat>;
	using GlxVector4d = GlxVector4<GlxDouble>;
	using GlxVector4ld = GlxVector4<GlxLongDouble>;
}
