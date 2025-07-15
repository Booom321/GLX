#pragma once

#include "GLX/TypeTraits/TypeTraits.h"

namespace GlxNsMath
{
	template<typename T>
	class GlxVector2
	{
	public:
		static_assert(GlxIsFloatingPoint<T>::Value);
		using Type = T;

		static GLX_CONSTEXPR GlxInt32 Size = 2;

	public:
		GlxVector2() = default;

		GlxVector2(const GlxVector2&) = default;
		GlxVector2& operator=(const GlxVector2&) = default;
		GlxVector2(GlxVector2&&) noexcept = default;
		GlxVector2& operator=(GlxVector2&&) noexcept = default;

		GLX_FORCE_INLINE GlxVector2(Type InX, Type InY)
			: X(InX), Y(InY)
		{}

		explicit GLX_FORCE_INLINE GlxVector2(Type InXY)
			: X(InXY), Y(InXY)
		{}

		explicit GLX_FORCE_INLINE GlxVector2(const Type* InXY)
			: X(InXY[0]), Y(InXY[1])
		{}

		template<typename U, typename GlxEnableIf<!GlxIsSame<U, Type>::Value, GlxInt32>::Type = 0>
		explicit GLX_FORCE_INLINE GlxVector2(const GlxVector2<U>& InVec2)
			: X(static_cast<Type>(InVec2.X)), Y(static_cast<Type>(InVec2.Y))
		{}

		~GlxVector2() = default;

		GLX_FORCE_INLINE Type& GetX()
		{
			return X;
		}

		GLX_FORCE_INLINE Type& GetY()
		{
			return Y;
		}

		GLX_FORCE_INLINE Type GetX() const
		{
			return X;
		}

		GLX_FORCE_INLINE Type GetY() const
		{
			return Y;
		}

		GLX_FORCE_INLINE Type& operator[](GlxInt32 InIndex)
		{
			return XY[InIndex];
		}

		GLX_FORCE_INLINE Type operator[](GlxInt32 InIndex) const
		{
			return XY[InIndex];
		}

		GLX_FORCE_INLINE GlxBool operator==(const GlxVector2& InVec2) const
		{
			return X == InVec2.X && Y == InVec2.Y;
		}

		GLX_FORCE_INLINE GlxBool operator!=(const GlxVector2& InVec2) const
		{
			return X != InVec2.X || Y != InVec2.Y;
		}

		GLX_FORCE_INLINE GlxBool operator>(const GlxVector2& InVec2) const
		{
			return X > InVec2.X && Y > InVec2.Y;
		}

		GLX_FORCE_INLINE GlxBool operator>=(const GlxVector2& InVec2) const
		{
			return X >= InVec2.X && Y >= InVec2.Y;
		}

		GLX_FORCE_INLINE GlxBool operator<(const GlxVector2& InVec2) const
		{
			return X < InVec2.X && Y < InVec2.Y;
		}

		GLX_FORCE_INLINE GlxBool operator<=(const GlxVector2& InVec2) const
		{
			return X <= InVec2.X && Y <= InVec2.Y;
		}

		GLX_FORCE_INLINE GlxVector2 operator-() const
		{
			return GlxVector2(-X, -Y);
		}

		GLX_FORCE_INLINE GlxVector2 operator+(const GlxVector2& InVec2) const
		{
			return GlxVector2(X + InVec2.X, Y + InVec2.Y);
		}

		GLX_FORCE_INLINE GlxVector2 operator-(const GlxVector2& InVec2) const
		{
			return GlxVector2(X - InVec2.X, Y - InVec2.Y);
		}

		GLX_FORCE_INLINE GlxVector2 operator*(const GlxVector2& InVec2) const
		{
			return GlxVector2(X * InVec2.X, Y * InVec2.Y);
		}

		GLX_FORCE_INLINE GlxVector2 operator/(const GlxVector2& InVec2) const
		{
			return GlxVector2(X / InVec2.X, Y / InVec2.Y);
		}

		GLX_FORCE_INLINE GlxVector2 operator+(Type InVal) const
		{
			return GlxVector2(X + InVal, Y + InVal);
		}

		GLX_FORCE_INLINE GlxVector2 operator-(Type InVal) const
		{
			return GlxVector2(X - InVal, Y - InVal);
		}

		GLX_FORCE_INLINE GlxVector2 operator*(Type InVal) const
		{
			return GlxVector2(X * InVal, Y * InVal);
		}

		GLX_FORCE_INLINE GlxVector2 operator/(Type InVal) const
		{
			return GlxVector2(X / InVal, Y / InVal);
		}

		friend GLX_FORCE_INLINE GlxVector2 operator*(Type InLhs, const GlxVector2& InRhs)
		{
			return GlxVector2(InLhs * InRhs.X, InLhs * InRhs.Y);
		}

		GLX_FORCE_INLINE GlxVector2& operator+=(const GlxVector2& InVec2)
		{
			X += InVec2.X;
			Y += InVec2.Y;
			return *this;
		}

		GLX_FORCE_INLINE GlxVector2& operator-=(const GlxVector2& InVec2)
		{
			X -= InVec2.X;
			Y -= InVec2.Y;
			return *this;
		}

		GLX_FORCE_INLINE GlxVector2& operator*=(const GlxVector2& InVec2)
		{
			X *= InVec2.X;
			Y *= InVec2.Y;
			return *this;
		}

		GLX_FORCE_INLINE GlxVector2& operator/=(const GlxVector2& InVec2)
		{
			X /= InVec2.X;
			Y /= InVec2.Y;
			return *this;
		}

		GLX_FORCE_INLINE GlxVector2& operator+=(Type InVal)
		{
			X += InVal;
			Y += InVal;
			return *this;
		}

		GLX_FORCE_INLINE GlxVector2& operator-=(Type InVal)
		{
			X -= InVal;
			Y -= InVal;
			return *this;
		}

		GLX_FORCE_INLINE GlxVector2& operator*=(Type InVal)
		{
			X *= InVal;
			Y *= InVal;
			return *this;
		}

		GLX_FORCE_INLINE GlxVector2& operator/=(Type InVal)
		{
			X /= InVal;
			Y /= InVal;
			return *this;
		}

		union
		{
			struct
			{
				Type X;
				Type Y;
			};

			Type XY[Size];
		};

		static const GlxVector2 Zero;
		static const GlxVector2 One;
		static const GlxVector2 UnitX;
		static const GlxVector2 UnitY;
	};

	template<typename T>
	const GlxVector2<T> GlxVector2<T>::Zero = GlxVector2<T>{ static_cast<T>(0), static_cast<T>(0) };
	template<typename T>
	const GlxVector2<T> GlxVector2<T>::One = GlxVector2<T>{ static_cast<T>(1), static_cast<T>(1) };
	template<typename T>
	const GlxVector2<T> GlxVector2<T>::UnitX = GlxVector2<T>{ static_cast<T>(1), static_cast<T>(0) };
	template<typename T>
	const GlxVector2<T> GlxVector2<T>::UnitY = GlxVector2<T>{ static_cast<T>(0), static_cast<T>(1) };

	using GlxVector2f = GlxVector2<GlxFloat>;
	using GlxVector2d = GlxVector2<GlxDouble>;
	using GlxVector2ld = GlxVector2<GlxLongDouble>;
}
