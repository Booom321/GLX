#pragma once

#include "Constants.h"

#include "Mat3x3.h"
#include "Mat4x4.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include <cmath>

namespace GlxNsMath
{
	template<typename T>
	class GlxIsMathMatrix : public GlxFalseType
	{};

	template<typename T>
	class GlxIsMathMatrix<GlxMat3x3<T>> : public GlxTrueType
	{};

	template<typename T>
	class GlxIsMathMatrix<GlxMat4x4<T>> : public GlxTrueType
	{};

	template<typename T>
	class GlxIsMathMatrix<const GlxMat3x3<T>> : public GlxTrueType
	{};

	template<typename T>
	class GlxIsMathMatrix<const GlxMat4x4<T>> : public GlxTrueType
	{};

	template<typename T>
	class GlxIsMathMatrix<volatile GlxMat3x3<T>> : public GlxTrueType
	{};

	template<typename T>
	class GlxIsMathMatrix<volatile GlxMat4x4<T>> : public GlxTrueType
	{};

	template<typename T>
	class GlxIsMathMatrix<const volatile GlxMat3x3<T>> : public GlxTrueType
	{};

	template<typename T>
	class GlxIsMathMatrix<const volatile GlxMat4x4<T>> : public GlxTrueType
	{};
	//////////////////////////////////////////////////////////////////////////
	template<typename T>
	class GlxIsMathVector : public GlxFalseType
	{};

	template<typename T>
	class GlxIsMathVector<GlxVector2<T>> : public GlxTrueType
	{};

	template<typename T>
	class GlxIsMathVector<GlxVector3<T>> : public GlxTrueType
	{};

	template<typename T>
	class GlxIsMathVector<GlxVector4<T>> : public GlxTrueType
	{};

	template<typename T>
	class GlxIsMathVector<const GlxVector2<T>> : public GlxTrueType
	{};

	template<typename T>
	class GlxIsMathVector<const GlxVector3<T>> : public GlxTrueType
	{};

	template<typename T>
	class GlxIsMathVector<const GlxVector4<T>> : public GlxTrueType
	{};

	template<typename T>
	class GlxIsMathVector<volatile GlxVector2<T>> : public GlxTrueType
	{};

	template<typename T>
	class GlxIsMathVector<volatile GlxVector3<T>> : public GlxTrueType
	{};

	template<typename T>
	class GlxIsMathVector<volatile GlxVector4<T>> : public GlxTrueType
	{};

	template<typename T>
	class GlxIsMathVector<const volatile GlxVector2<T>> : public GlxTrueType
	{};

	template<typename T>
	class GlxIsMathVector<const volatile GlxVector3<T>> : public GlxTrueType
	{};

	template<typename T>
	class GlxIsMathVector<const volatile GlxVector4<T>> : public GlxTrueType
	{};
	//////////////////////////////////////////////////////////////////////////
	template<typename T>
	class GlxIsMathNumber : public GlxBoolConstant<GlxIsArithmetic<typename GlxRemoveCVRef<T>::Type>::Value>
	{};

	/** Trigonometric functions **/
	GLX_FORCE_INLINE GlxFloat Sin(GlxFloat InX)
	{
		return sinf(InX);
	}

	GLX_FORCE_INLINE GlxDouble Sin(GlxDouble InX)
	{
		return sin(InX);
	}

	GLX_FORCE_INLINE GlxLongDouble Sin(GlxLongDouble InX)
	{
		return sinl(InX);
	}

	GLX_FORCE_INLINE GlxFloat Cos(GlxFloat InX)
	{
		return cosf(InX);
	}

	GLX_FORCE_INLINE GlxDouble Cos(GlxDouble InX)
	{
		return cos(InX);
	}

	GLX_FORCE_INLINE GlxLongDouble Cos(GlxLongDouble InX)
	{
		return cosl(InX);
	}

	GLX_FORCE_INLINE GlxFloat Tan(GlxFloat InX)
	{
		return tanf(InX);
	}

	GLX_FORCE_INLINE GlxDouble Tan(GlxDouble InX)
	{
		return tan(InX);
	}

	GLX_FORCE_INLINE GlxLongDouble Tan(GlxLongDouble InX)
	{
		return tanl(InX);
	}

	GLX_FORCE_INLINE GlxFloat Asin(GlxFloat InX)
	{
		return asinf(InX);
	}

	GLX_FORCE_INLINE GlxDouble Asin(GlxDouble InX)
	{
		return asin(InX);
	}

	GLX_FORCE_INLINE GlxLongDouble Asin(GlxLongDouble InX)
	{
		return asinl(InX);
	}

	GLX_FORCE_INLINE GlxFloat Acos(GlxFloat InX)
	{
		return acosf(InX);
	}

	GLX_FORCE_INLINE GlxDouble Acos(GlxDouble InX)
	{
		return acos(InX);
	}

	GLX_FORCE_INLINE GlxLongDouble Acos(GlxLongDouble InX)
	{
		return acosl(InX);
	}

	GLX_FORCE_INLINE GlxFloat Atan(GlxFloat InX)
	{
		return atanf(InX);
	}

	GLX_FORCE_INLINE GlxDouble Atan(GlxDouble InX)
	{
		return atan(InX);
	}

	GLX_FORCE_INLINE GlxLongDouble Atan(GlxLongDouble InX)
	{
		return atanl(InX);
	}

	GLX_FORCE_INLINE GlxFloat Atan2(GlxFloat InY, GlxFloat InX)
	{
		return atan2f(InY, InX);
	}

	GLX_FORCE_INLINE GlxDouble Atan2(GlxDouble InY, GlxDouble InX)
	{
		return atan2(InY, InX);
	}

	GLX_FORCE_INLINE GlxLongDouble Atan2(GlxLongDouble InY, GlxLongDouble InX)
	{
		return atan2l(InY, InX);
	}

	/** Exponential functions **/
	GLX_FORCE_INLINE GlxFloat Exp(GlxFloat InX)
	{
		return expf(InX);
	}

	GLX_FORCE_INLINE GlxDouble Exp(GlxDouble InX)
	{
		return exp(InX);
	}

	GLX_FORCE_INLINE GlxLongDouble Exp(GlxLongDouble InX)
	{
		return expl(InX);
	}

	GLX_FORCE_INLINE GlxFloat Ln(GlxFloat InX)
	{
		return logf(InX);
	}

	GLX_FORCE_INLINE GlxDouble Ln(GlxDouble InX)
	{
		return log(InX);
	}

	GLX_FORCE_INLINE GlxLongDouble Ln(GlxLongDouble InX)
	{
		return logl(InX);
	}

	GLX_FORCE_INLINE GlxFloat Log2(GlxFloat InX)
	{
		return log2f(InX);
	}

	GLX_FORCE_INLINE GlxDouble Log2(GlxDouble InX)
	{
		return log2(InX);
	}

	GLX_FORCE_INLINE GlxLongDouble Log2(GlxLongDouble InX)
	{
		return log2l(InX);
	}

	GLX_FORCE_INLINE GlxFloat Log10(GlxFloat InX)
	{
		return log10f(InX);
	}

	GLX_FORCE_INLINE GlxDouble Log10(GlxDouble InX)
	{
		return log10(InX);
	}

	GLX_FORCE_INLINE GlxLongDouble Log10(GlxLongDouble InX)
	{
		return log10l(InX);
	}

	GLX_FORCE_INLINE GlxFloat Log(GlxFloat InBase, GlxFloat InX)
	{
		return log10f(InX) / log10f(InBase);
	}

	GLX_FORCE_INLINE GlxDouble Log(GlxDouble InBase, GlxDouble InX)
	{
		return log10(InX) / log10(InBase);
	}

	GLX_FORCE_INLINE GlxLongDouble Log(GlxLongDouble InBase, GlxLongDouble InX)
	{
		return log10l(InX) / log10l(InBase);
	}

	/** Power functions **/
	GLX_FORCE_INLINE GlxFloat Pow(GlxFloat InX, GlxFloat InY)
	{
		return powf(InX, InY);
	}

	GLX_FORCE_INLINE GlxDouble Pow(GlxDouble InX, GlxDouble InY)
	{
		return pow(InX, InY);
	}

	GLX_FORCE_INLINE GlxLongDouble Pow(GlxLongDouble InX, GlxLongDouble InY)
	{
		return powl(InX, InY);
	}

	GLX_FORCE_INLINE GlxFloat Sqrt(GlxFloat InX)
	{
		return sqrtf(InX);
	}

	GLX_FORCE_INLINE GlxDouble Sqrt(GlxDouble InX)
	{
		return sqrt(InX);
	}

	GLX_FORCE_INLINE GlxLongDouble Sqrt(GlxLongDouble InX)
	{
		return sqrtl(InX);
	}

	/** Nearest integer floating-point operations **/
	GLX_FORCE_INLINE GlxFloat Ceil(GlxFloat InX)
	{
		return ceilf(InX);
	}

	GLX_FORCE_INLINE GlxDouble Ceil(GlxDouble InX)
	{
		return ceil(InX);
	}

	GLX_FORCE_INLINE GlxLongDouble Ceil(GlxLongDouble InX)
	{
		return ceill(InX);
	}

	GLX_FORCE_INLINE GlxFloat Floor(GlxFloat InX)
	{
		return floorf(InX);
	}

	GLX_FORCE_INLINE GlxDouble Floor(GlxDouble InX)
	{
		return floor(InX);
	}

	GLX_FORCE_INLINE GlxLongDouble Floor(GlxLongDouble InX)
	{
		return floorl(InX);
	}

	GLX_FORCE_INLINE GlxFloat Round(GlxFloat InX)
	{
		return roundf(InX);
	}

	GLX_FORCE_INLINE GlxDouble Round(GlxDouble InX)
	{
		return round(InX);
	}

	GLX_FORCE_INLINE GlxLongDouble Round(GlxLongDouble InX)
	{
		return roundl(InX);
	}

	GLX_FORCE_INLINE GlxFloat Trunc(GlxFloat InX)
	{
		return truncf(InX);
	}

	GLX_FORCE_INLINE GlxDouble Trunc(GlxDouble InX)
	{
		return trunc(InX);
	}

	GLX_FORCE_INLINE GlxLongDouble Trunc(GlxLongDouble InX)
	{
		return truncl(InX);
	}

	GLX_FORCE_INLINE GlxFloat Fractional(GlxFloat InX)
	{
		return InX - static_cast<long>(truncf(InX));
	}

	GLX_FORCE_INLINE GlxDouble Fractional(GlxDouble InX)
	{
		return InX - static_cast<long>(trunc(InX));
	}

	GLX_FORCE_INLINE GlxLongDouble Fractional(GlxLongDouble InX)
	{
		return InX - static_cast<long>(truncl(InX));
	}

	GLX_FORCE_INLINE GlxInt32 Rand()
	{
		return rand();
	}

	GLX_FORCE_INLINE void SRand(GlxUInt32 InSeeds)
	{
		srand(InSeeds);
	}

	template<typename T>
	typename GlxEnableIf<GlxIsMathNumber<T>::Value, T>::Type Sign(T InX)
	{
		static GLX_CONSTEXPR T Zero = static_cast<T>(0);

		if (InX > Zero)
		{
			return static_cast<T>(1);
		}

		if (InX < Zero)
		{
			return static_cast<T>(-1);
		}

		return static_cast<T>(0);
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathNumber<T>::Value, T>::Type Square(T InX)
	{
		return InX * InX;
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathNumber<T>::Value, T>::Type Cube(T InX)
	{
		return InX * InX * InX;
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathNumber<T>::Value, T>::Type RadiansToDegrees(T InRad)
	{
		static GLX_CONSTEXPR T Mult = static_cast<T>(180) / GlxNsMath::Pi<T>;
		return InRad * Mult;
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathNumber<T>::Value, T>::Type DegreesToRadians(T InDeg)
	{
		static GLX_CONSTEXPR T Mult = GlxNsMath::Pi<T> / static_cast<T>(180);
		return InDeg * Mult;
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathNumber<T>::Value, T>::Type Saturate(T InX)
	{
		return InX < 0 ? 0 : (InX < 1 ? InX : 1);
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathNumber<T>::Value, GlxBool>::Type IsPowerOfTwo(T InX)
	{
		return !(InX == 0) && !(InX & (InX - 1));
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathNumber<T>::Value, GlxBool>::Type IsInRange(T InX, T InMin, T InMax)
	{
		return InX >= InMin && InX <= InMax;
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathNumber<T>::Value, GlxBool>::Type IsNotInRange(T InX, T InMin, T InMax)
	{
		return InX < InMin || InX > InMax;
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathNumber<T>::Value, T>::Type RandRange(T InMin, T InMax)
	{
		return static_cast<T>(InMin + (((T)rand()) % (InMax - InMin + (T)1)));
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathNumber<T>::Value, T>::Type Abs(T InX)
	{
		return InX >= static_cast<T>(0) ? InX : -InX;
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathVector<T>::Value, T>::Type Abs(const T& InVec)
	{
		using ComponentType = typename T::Type;

		if constexpr (T::Size == 2)
		{
			return T(
				InVec.X >= static_cast<ComponentType>(0) ? InVec.X : -InVec.X,
				InVec.Y >= static_cast<ComponentType>(0) ? InVec.Y : -InVec.Y);
		}
		else if constexpr (T::Size == 3)
		{
			return T(
				InVec.X >= static_cast<ComponentType>(0) ? InVec.X : -InVec.X,
				InVec.Y >= static_cast<ComponentType>(0) ? InVec.Y : -InVec.Y,
				InVec.Z >= static_cast<ComponentType>(0) ? InVec.Z : -InVec.Z);
		}
		else if constexpr (T::Size == 4)
		{
			return T(
				InVec.X >= static_cast<ComponentType>(0) ? InVec.X : -InVec.X,
				InVec.Y >= static_cast<ComponentType>(0) ? InVec.Y : -InVec.Y,
				InVec.Z >= static_cast<ComponentType>(0) ? InVec.Z : -InVec.Z,
				InVec.W >= static_cast<ComponentType>(0) ? InVec.W : -InVec.W);
		}
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathNumber<T>::Value, GlxBool>::Type IsNearlyEqual(T InX, T InY, T InTolerance = SmallTolerance<T>)
	{
		return (InY >= InX - InTolerance) && (InY <= InX + InTolerance);
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathVector<T>::Value, GlxBool>::Type IsNearlyEqual(const T& InLhs, const T& InRhs, typename T::Type InTolerance = SmallTolerance<typename T::Type>)
	{
		using ComponentType = typename T::Type;

		if constexpr (T::Size == 2)
		{
			return ((InRhs.X >= InLhs.X - InTolerance) && (InRhs.X <= InLhs.X + InTolerance)) &&
				((InRhs.Y >= InLhs.Y - InTolerance) && (InRhs.Y <= InLhs.Y + InTolerance));
		}
		else if constexpr (T::Size == 3)
		{
			return ((InRhs.X >= InLhs.X - InTolerance) && (InRhs.X <= InLhs.X + InTolerance)) &&
				((InRhs.Y >= InLhs.Y - InTolerance) && (InRhs.Y <= InLhs.Y + InTolerance)) &&
				((InRhs.Z >= InLhs.Z - InTolerance) && (InRhs.Z <= InLhs.Z + InTolerance));
		}
		else if constexpr (T::Size == 4)
		{
			return ((InRhs.X >= InLhs.X - InTolerance) && (InRhs.X <= InLhs.X + InTolerance)) &&
				((InRhs.Y >= InLhs.Y - InTolerance) && (InRhs.Y <= InLhs.Y + InTolerance)) &&
				((InRhs.Z >= InLhs.Z - InTolerance) && (InRhs.Z <= InLhs.Z + InTolerance)) &&
				((InRhs.W >= InLhs.W - InTolerance) && (InRhs.W <= InLhs.W + InTolerance));
		}
	}

	template<typename M>
	typename GlxEnableIf<GlxIsMathMatrix<M>::Value, GlxBool>::Type IsNearlyEqual(const M& InLhs, const M& InRhs, typename M::Type InTolerance = SmallTolerance<typename M::Type>)
	{
		for (GlxInt32 Index = 0; Index < M::ElementCount; ++Index)
		{
			if (!((InLhs.A[Index] >= InRhs.A[Index] - InTolerance) && (InLhs.A[Index] <= InRhs.A[Index] + InTolerance)))
			{
				return false;
			}
		}

		return true;
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathNumber<T>::Value, GlxBool>::Type IsNearlyZero(T InX, T InTolerance = SmallTolerance<T>)
	{
		return (InX >= -InTolerance) && (InX <= InTolerance);
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathVector<T>::Value, GlxBool>::Type IsNearlyZero(const T& InVec, typename T::Type InTolerance = SmallTolerance<typename T::Type>)
	{
		using ComponentType = typename T::Type;
		ComponentType NegativeTolerance = -InTolerance;

		if constexpr (T::Size == 2)
		{
			return (InVec.X >= NegativeTolerance && InVec.X <= InTolerance) && (InVec.Y >= NegativeTolerance && InVec.Y <= InTolerance);
		}
		else if constexpr (T::Size == 3)
		{
			return (InVec.X >= NegativeTolerance && InVec.X <= InTolerance) && (InVec.Y >= NegativeTolerance && InVec.Y <= InTolerance) && (InVec.Z >= NegativeTolerance && InVec.Z <= InTolerance);
		}
		else if constexpr (T::Size == 4)
		{
			return (InVec.X >= NegativeTolerance && InVec.X <= InTolerance) && (InVec.Y >= NegativeTolerance && InVec.Y <= InTolerance) && (InVec.Z >= NegativeTolerance && InVec.Z <= InTolerance) && (InVec.W >= NegativeTolerance && InVec.W <= InTolerance);
		}
	}

	template<typename M>
	typename GlxEnableIf<GlxIsMathMatrix<M>::Value, GlxBool>::Type IsNearlyZero(const M& InM, typename M::Type InTolerance = SmallTolerance<typename M::Type>)
	{
		typename M::Type NegativeTolerance = -InTolerance;
		for (GlxInt32 Index = 0; Index < M::ElementCount; ++Index)
		{
			if (!(InM.A[Index] >= NegativeTolerance && InM.A[Index] <= InTolerance))
			{
				return false;
			}
		}

		return true;
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathNumber<T>::Value, GlxBool>::Type IsZero(T InX)
	{
		return InX == 0;
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathVector<T>::Value, GlxBool>::Type IsZero(const T& InVec)
	{
		using ComponentType = typename T::Type;

		if constexpr (T::Size == 2)
		{
			return InVec.X == 0 && InVec.Y == 0;
		}
		else if constexpr (T::Size == 3)
		{
			return InVec.X == 0 && InVec.Y == 0 && InVec.Z == 0;
		}
		else if constexpr (T::Size == 4)
		{
			return InVec.X == 0 && InVec.Y == 0 && InVec.Z == 0 && InVec.W == 0;
		}
	}

	template<typename M>
	typename GlxEnableIf<GlxIsMathMatrix<M>::Value, GlxBool>::Type IsZero(const M& InM)
	{
		using Type = typename M::Type;
		for (GlxInt32 Index = 0; Index < M::ElementCount; ++Index)
		{
			if (InM.A[Index] != static_cast<Type>(0))
			{
				return false;
			}
		}

		return true;
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathNumber<T>::Value, GlxBool>::Type IsNaN(T InX)
	{
		if constexpr (GlxIsFloatingPoint<T>::Value)
		{
			return InX != InX;
		}
		else
		{
			return std::isnan(InX);
		}
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathVector<T>::Value, GlxBool>::Type IsNaN(const T& InVec)
	{
		using ComponentType = typename T::Type;

		if constexpr (T::Size == 2)
		{
			return IsNaN<ComponentType>(InVec.X) || IsNaN<ComponentType>(InVec.Y);
		}
		else if constexpr (T::Size == 3)
		{
			return IsNaN<ComponentType>(InVec.X) || IsNaN<ComponentType>(InVec.Y) || IsNaN<ComponentType>(InVec.Z);
		}
		else if constexpr (T::Size == 4)
		{
			return IsNaN<ComponentType>(InVec.X) || IsNaN<ComponentType>(InVec.Y) || IsNaN<ComponentType>(InVec.Z) || IsNaN<ComponentType>(InVec.W);
		}
	}

	template<typename M>
	typename GlxEnableIf<GlxIsMathMatrix<M>::Value, GlxBool>::Type IsNaN(const M& InM)
	{
		using Type = typename M::Type;
		for (GlxInt32 Index = 0; Index < M::ElementCount; ++Index)
		{
			if (IsNaN<Type>(InM.A[Index]))
			{
				return true;
			}
		}

		return false;
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathNumber<T>::Value, GlxBool>::Type IsInfinite(T InX)
	{
		return std::isinf(InX);
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathVector<T>::Value, GlxBool>::Type IsInfinite(const T& InVec)
	{
		using ComponentType = typename T::Type;

		if constexpr (T::Size == 2)
		{
			return std::isinf(InVec.X) || std::isinf(InVec.Y);
		}
		else if constexpr (T::Size == 3)
		{
			return std::isinf(InVec.X) || std::isinf(InVec.Y) || std::isinf(InVec.Z);
		}
		else if constexpr (T::Size == 4)
		{
			return std::isinf(InVec.X) || std::isinf(InVec.Y) || std::isinf(InVec.Z) || std::isinf(InVec.W);
		}
	}

	template<typename M>
	typename GlxEnableIf<GlxIsMathMatrix<M>::Value, GlxBool>::Type IsInfinite(const M& InM)
	{
		for (GlxInt32 Index = 0; Index < M::ElementCount; ++Index)
		{
			if (std::isinf(InM.A[Index]))
			{
				return true;
			}
		}

		return false;
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathNumber<T>::Value, GlxBool>::Type IsFinite(T InX)
	{
		return std::isfinite(InX);
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathVector<T>::Value, GlxBool>::Type IsFinite(const T& InVec)
	{
		using ComponentType = typename T::Type;

		if constexpr (T::Size == 2)
		{
			return std::isfinite(InVec.X) || std::isfinite(InVec.Y);
		}
		else if constexpr (T::Size == 3)
		{
			return std::isfinite(InVec.X) || std::isfinite(InVec.Y) || std::isfinite(InVec.Z);
		}
		else if constexpr (T::Size == 4)
		{
			return std::isfinite(InVec.X) || std::isfinite(InVec.Y) || std::isfinite(InVec.Z) || std::isfinite(InVec.W);
		}
	}

	template<typename M>
	typename GlxEnableIf<GlxIsMathMatrix<M>::Value, GlxBool>::Type IsFinite(const M& InM)
	{
		for (GlxInt32 Index = 0; Index < M::ElementCount; ++Index)
		{
			if (std::isfinite(InM.A[Index]))
			{
				return true;
			}
		}

		return false;
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathNumber<T>::Value, T>::Type Clamp(T InX, T InMin, T InMax)
	{
		return GLX_CLAMP(InX, InMin, InMax);
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathVector<T>::Value, T>::Type Clamp(const T& InVec, const T& InMin, const T& InMax)
	{
		using ComponentType = typename T::Type;

		if constexpr (T::Size == 2)
		{
			return T(GLX_CLAMP(InVec.X, InMin.X, InMax.X), GLX_CLAMP(InVec.Y, InMin.Y, InMax.Y));
		}
		else if constexpr (T::Size == 3)
		{
			return T(GLX_CLAMP(InVec.X, InMin.X, InMax.X), GLX_CLAMP(InVec.Y, InMin.Y, InMax.Y), GLX_CLAMP(InVec.Z, InMin.Z, InMax.Z));
		}
		else if constexpr (T::Size == 4)
		{
			return T(GLX_CLAMP(InVec.X, InMin.X, InMax.X), GLX_CLAMP(InVec.Y, InMin.Y, InMax.Y), GLX_CLAMP(InVec.Z, InMin.Z, InMax.Z), GLX_CLAMP(InVec.W, InMin.W, InMax.W));
		}
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathNumber<T>::Value, T>::Type Max(T InX, T InY)
	{
		return GLX_MAX(InX, InY);
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathVector<T>::Value, T>::Type Max(const T& InX, const T& InY)
	{
		using ComponentType = typename T::Type;

		if constexpr (T::Size == 2)
		{
			return T(GLX_MAX(InX.X, InY.X), GLX_MAX(InX.Y, InY.Y));
		}
		else if constexpr (T::Size == 3)
		{
			return T(GLX_MAX(InX.X, InY.X), GLX_MAX(InX.Y, InY.Y), GLX_MAX(InX.Z, InY.Z));
		}
		else if constexpr (T::Size == 4)
		{
			return T(GLX_MAX(InX.X, InY.X), GLX_MAX(InX.Y, InY.Y), GLX_MAX(InX.Z, InY.Z), GLX_MAX(InX.W, InY.W));
		}
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathNumber<T>::Value, T>::Type Min(T InX, T InY)
	{
		return GLX_MIN(InX, InY);
	}

	template<typename T>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathVector<T>::Value, T>::Type Min(const T& InX, const T& InY)
	{
		using ComponentType = typename T::Type;

		if constexpr (T::Size == 2)
		{
			return T(GLX_MIN(InX.X, InY.X), GLX_MIN(InX.Y, InY.Y));
		}
		else if constexpr (T::Size == 3)
		{
			return T(GLX_MIN(InX.X, InY.X), GLX_MIN(InX.Y, InY.Y), GLX_MIN(InX.Z, InY.Z));
		}
		else if constexpr (T::Size == 4)
		{
			return T(GLX_MIN(InX.X, InY.X), GLX_MIN(InX.Y, InY.Y), GLX_MIN(InX.Z, InY.Z), GLX_MIN(InX.W, InY.W));
		}
	}

	template<typename T, typename U>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathNumber<T>::Value, T>::Type Lerp(T InFrom, T InTo, U InAmount)
	{
		return (static_cast<T>(1) - InAmount) * InFrom + InAmount * InTo;
	}

	template<typename T, typename U>
	GLX_FORCE_INLINE typename GlxEnableIf<GlxIsMathVector<T>::Value, T>::Type Lerp(const T& InFrom, const T& InTo, U InAmount)
	{
		using ComponentType = typename T::Type;

		if constexpr (T::Size == 2)
		{
			return T(Lerp<ComponentType>(InFrom.X, InTo.X, InAmount), Lerp<ComponentType>(InFrom.Y, InTo.Y, InAmount));
		}
		else if constexpr (T::Size == 3)
		{
			return T(Lerp<ComponentType>(InFrom.X, InTo.X, InAmount), Lerp<ComponentType>(InFrom.Y, InTo.Y, InAmount), Lerp<ComponentType>(InFrom.Z, InTo.Z, InAmount));
		}
		else if constexpr (T::Size == 4)
		{
			return T(Lerp<ComponentType>(InFrom.X, InTo.X, InAmount), Lerp<ComponentType>(InFrom.Y, InTo.Y, InAmount), Lerp<ComponentType>(InFrom.Z, InTo.Z, InAmount), Lerp<ComponentType>(InFrom.W, InTo.W, InAmount));
		}
	}

	template<typename T>
	GLX_FORCE_INLINE T Dot(const GlxVector2<T>& InA, const GlxVector2<T>& InB)
	{
		return InA.X * InB.X + InA.Y * InB.Y;
	}

	template<typename T>
	GLX_FORCE_INLINE T Dot(const GlxVector3<T>& InA, const GlxVector3<T>& InB)
	{
		return InA.X * InB.X + InA.Y * InB.Y + InA.Z * InB.Z;
	}

	template<typename T>
	GLX_FORCE_INLINE T Dot(const GlxVector4<T>& InA, const GlxVector4<T>& InB)
	{
		return InA.X * InB.X + InA.Y * InB.Y + InA.Z * InB.Z + InA.W * InB.W;
	}

	template<typename T>
	GLX_FORCE_INLINE GlxVector3<T> Cross(const GlxVector3<T>& InA, const GlxVector3<T>& InB)
	{
		return GlxVector3<T>(
			InA.Y * InB.Z - InA.Z * InB.Y,
			InA.Z * InB.X - InA.X * InB.Z,
			InA.X * InB.Y - InA.Y * InB.X);
	}

	template<typename T>
	T GetDistanceSquared(const GlxVector2<T>& InA, const GlxVector2<T>& InB)
	{
		const T OffsetX = InB.X - InA.X;
		const T OffsetY = InB.Y - InA.Y;
		return OffsetX * OffsetX + OffsetY * OffsetY;
	}

	template<typename T>
	T GetDistanceSquared(const GlxVector3<T>& InA, const GlxVector3<T>& InB)
	{
		const T OffsetX = InB.X - InA.X;
		const T OffsetY = InB.Y - InA.Y;
		const T OffsetZ = InB.Z - InA.Z;
		return OffsetX * OffsetX + OffsetY * OffsetY + OffsetZ * OffsetZ;
	}

	template<typename T>
	T GetDistanceSquared(const GlxVector4<T>& InA, const GlxVector4<T>& InB)
	{
		const T OffsetX = InB.X - InA.X;
		const T OffsetY = InB.Y - InA.Y;
		const T OffsetZ = InB.Z - InA.Z;
		const T OffsetW = InB.W - InA.W;
		return OffsetX * OffsetX + OffsetY * OffsetY + OffsetZ * OffsetZ + OffsetW * OffsetW;
	}

	template<typename T, typename TResult = T>
	TResult GetDistance(const GlxVector2<T>& InA, const GlxVector2<T>& InB)
	{
		return Sqrt(static_cast<TResult>(GetDistanceSquared<T>(InA, InB)));
	}

	template<typename T, typename TResult = T>
	TResult GetDistance(const GlxVector3<T>& InA, const GlxVector3<T>& InB)
	{
		return Sqrt(static_cast<TResult>(GetDistanceSquared<T>(InA, InB)));
	}

	template<typename T, typename TResult = T>
	TResult GetDistance(const GlxVector4<T>& InA, const GlxVector4<T>& InB)
	{
		return Sqrt(static_cast<TResult>(GetDistanceSquared<T>(InA, InB)));
	}

	template<typename T>
	GlxBool IsNormalized(const GlxVector2<T>& InV, T InTolerance = SmallTolerance<T>)
	{
		const T Test = static_cast<T>(InV.X * InV.X + InV.Y * InV.Y) - static_cast<T>(1.0);
		return Test >= -InTolerance && Test <= InTolerance;
	}

	template<typename T>
	GlxBool IsNormalized(const GlxVector3<T>& InV, T InTolerance = SmallTolerance<T>)
	{
		const T Test = static_cast<T>(InV.X * InV.X + InV.Y * InV.Y + InV.Z * InV.Z) - static_cast<T>(1.0);
		return Test >= -InTolerance && Test <= InTolerance;
	}

	template<typename T>
	GlxBool IsNormalized(const GlxVector4<T>& InV, T InTolerance = SmallTolerance<T>)
	{
		const T Test = static_cast<T>(InV.X * InV.X + InV.Y * InV.Y + InV.Z * InV.Z + InV.W * InV.W) - static_cast<T>(1.0);
		return Test >= -InTolerance && Test <= InTolerance;
	}

	template<typename T>
	GLX_FORCE_INLINE T GetLengthSquared(const GlxVector2<T>& InV)
	{
		return InV.X * InV.X + InV.Y * InV.Y;
	}

	template<typename T>
	GLX_FORCE_INLINE T GetLengthSquared(const GlxVector3<T>& InV)
	{
		return InV.X * InV.X + InV.Y * InV.Y + InV.Z * InV.Z;
	}

	template<typename T>
	GLX_FORCE_INLINE T GetLengthSquared(const GlxVector4<T>& InV)
	{
		return InV.X * InV.X + InV.Y * InV.Y + InV.Z * InV.Z + InV.W * InV.W;
	}

	template<typename T, typename TResult = T>
	GLX_FORCE_INLINE TResult GetLength(const GlxVector2<T>& InV)
	{
		return Sqrt(static_cast<TResult>(InV.X * InV.X + InV.Y * InV.Y));
	}

	template<typename T, typename TResult = T>
	GLX_FORCE_INLINE TResult GetLength(const GlxVector3<T>& InV)
	{
		return Sqrt(static_cast<TResult>(InV.X * InV.X + InV.Y * InV.Y + InV.Z * InV.Z));
	}

	template<typename T, typename TResult = T>
	GLX_FORCE_INLINE TResult GetLength(const GlxVector4<T>& InV)
	{
		return Sqrt(static_cast<TResult>(InV.X * InV.X + InV.Y * InV.Y + InV.Z * InV.Z + InV.W * InV.W));
	}

	template<typename T>
	void Normalize(GlxVector2<T>& InV)
	{
		const T LengthSquared = InV.X * InV.X + InV.Y * InV.Y;

		if (LengthSquared != (T)0)
		{
			const T Scale = static_cast<T>(1.0) / Sqrt(static_cast<T>(LengthSquared));

			InV.X *= Scale;
			InV.Y *= Scale;
		}
	}

	template<typename T>
	void Normalize(GlxVector3<T>& InV)
	{
		const T LengthSquared = InV.X * InV.X + InV.Y * InV.Y + InV.Z * InV.Z;

		if (LengthSquared != (T)0)
		{
			const T Scale = static_cast<T>(1.0) / Sqrt(static_cast<T>(LengthSquared));

			InV.X *= Scale;
			InV.Y *= Scale;
			InV.Z *= Scale;
		}
	}

	template<typename T>
	void Normalize(GlxVector4<T>& InV)
	{
		const T LengthSquared = InV.X * InV.X + InV.Y * InV.Y + InV.Z * InV.Z + InV.W * InV.W;

		if (LengthSquared != (T)0)
		{
			const T Scale = static_cast<T>(1.0) / Sqrt(static_cast<T>(LengthSquared));

			InV.X *= Scale;
			InV.Y *= Scale;
			InV.Z *= Scale;
			InV.W *= Scale;
		}
	}

	template<typename T>
	GlxMat4x4<T> RotateX(const GlxMat4x4<T>& InM, T InAngle /* radians */)
	{
		const T C = Cos(InAngle);
		const T S = Sin(InAngle);

		return GlxMat4x4<T>(
			(T)1, (T)0, (T)0, (T)0,
			(T)0,    C,   -S, (T)0,
			(T)0,    S,    C, (T)0,
			(T)0, (T)0, (T)0, (T) 1
		);
	}

	template<typename T>
	GlxMat4x4<T> RotateY(const GlxMat4x4<T>& InM, T InAngle /* radians */)
	{
		const T C = Cos(InAngle);
		const T S = Sin(InAngle);

		return GlxMat4x4<T>(
			   C, (T)0,    S, (T)0,
			(T)0, (T)1, (T)0, (T)0,
			  -S, (T)0,    C, (T)0,
			(T)0, (T)0, (T)0, (T)1
		);
	}

	template<typename T>
	GlxMat4x4<T> RotateZ(const GlxMat4x4<T>& InM, T InAngle /* radians */)
	{
		const T C = Cos(InAngle);
		const T S = Sin(InAngle);

		return GlxMat4x4<T>(
			   C,   -S, (T)0, (T)0,
			   S,    C, (T)0, (T)0,
			(T)0, (T)0, (T)1, (T)0,
			(T)0, (T)0, (T)0, (T)1
		);
	}

	template<typename T>
	GlxMat4x4<T> RotateXYZ(const GlxMat4x4<T>& InM, const GlxVector3<T>& InAxis, T InAngle /* radians */)
	{
		const T Scale = static_cast<T>(1.0) / Sqrt(static_cast<T>(InAxis.X * InAxis.X + InAxis.Y * InAxis.Y + InAxis.Z * InAxis.Z));
		const T X = InAxis.X * Scale;
		const T	Y = InAxis.Y * Scale;
		const T	Z = InAxis.Z * Scale;

		const T C = Cos(InAngle);
		const T S = Sin(InAngle);
		const T Omc = static_cast<T>(1) - C;

		const T XZ = X * Z;
		const T XY = X * Y;
		const T YZ = Y * Z;

		const T XS = X * S;
		const T YS = Y * S;
		const T ZS = Z * S;

		return GlxMat4x4<T>(
			X * X * Omc + C,   XY * Omc + ZS,   XZ * Omc - YS, (T)0,
			  XY * Omc - ZS, Y * Y * Omc + C,   YZ * Omc + XS, (T)0,
			  XZ * Omc + YS,   YZ * Omc - XS, Z * Z * Omc + C, (T)0,
			           (T)0,            (T)0,            (T)0, (T)1
		);
	}

	template<typename T>
	GlxMat4x4<T> LookAtLH(const GlxVector3<T>& InEye, const GlxVector3<T>& InCenter, const GlxVector3<T>& InUp)
	{
		GlxVector3<T> ZAxis(InCenter - InEye);
		Normalize(ZAxis);
		GlxVector3<T> XAxis(Cross(InUp, ZAxis));
		Normalize(XAxis);
		GlxVector3<T> YAxis(Cross(ZAxis, XAxis));

		return GlxMat4x4<T>(
			XAxis.X, YAxis.X, ZAxis.X, (T)0,
			XAxis.Y, YAxis.Y, ZAxis.Y, (T)0,
			XAxis.Z, YAxis.Z, ZAxis.Z, (T)0,
			-static_cast<T>(XAxis.X * InEye.X + XAxis.Y * InEye.Y + XAxis.Z * InEye.Z),
			-static_cast<T>(YAxis.X * InEye.X + YAxis.Y * InEye.Y + YAxis.Z * InEye.Z),
			-static_cast<T>(ZAxis.X * InEye.X + ZAxis.Y * InEye.Y + ZAxis.Z * InEye.Z), (T)1
		);
	}

	template<typename T>
	GlxMat4x4<T> LookAtRH(const GlxVector3<T>& InEye, const GlxVector3<T>& InCenter, const GlxVector3<T>& InUp)
	{
		GlxVector3<T> ZAxis(InEye - InCenter);
		Normalize(ZAxis);
		GlxVector3<T> XAxis(Cross(InUp, ZAxis));
		Normalize(XAxis);
		GlxVector3<T> YAxis(Cross(ZAxis, XAxis));

		return  GlxMat4x4<T>(
			XAxis.X, YAxis.X, ZAxis.X, (T)0,
			XAxis.Y, YAxis.Y, ZAxis.Y, (T)0,
			XAxis.Z, YAxis.Z, ZAxis.Z, (T)0,
			-static_cast<T>(XAxis.X * InEye.X + XAxis.Y * InEye.Y + XAxis.Z * InEye.Z),
			-static_cast<T>(YAxis.X * InEye.X + YAxis.Y * InEye.Y + YAxis.Z * InEye.Z),
			-static_cast<T>(ZAxis.X * InEye.X + ZAxis.Y * InEye.Y + ZAxis.Z * InEye.Z), (T)1
		);;
	}

	template<typename T>
	GlxMat4x4<T> PerspectiveRH(T InFovy, T InAspect, T InZNear, T InZFar)
	{
		const T F = static_cast<T>(static_cast<T>(1) / Tan(InFovy * static_cast<T>(0.5f)));

		return GlxMat4x4<T>(
			F / InAspect, (T)0, (T)0, (T)0,
			(T)0, F, (T)0, (T)0,
			(T)0, (T)0, (InZFar + InZNear) / (InZNear - InZFar), -1,
			(T)0, (T)0, (((T)2) * InZFar * InZNear) / (InZNear - InZFar), (T)0
		);
	}

	template<typename T>
	GlxMat4x4<T> PerspectiveLH(T InFovy, T InAspect, T InZNear, T InZFar)
	{
		const T F = static_cast<T>(static_cast<T>(1) / Tan(InFovy * static_cast<T>(0.5f)));

		return GlxMat4x4<T>(
			F / InAspect, (T)0, (T)0, (T)0,
			(T)0, F, (T)0, (T)0,
			(T)0, (T)0, InZFar / (InZFar - InZNear), (T)1,
			(T)0, (T)0, (-InZFar * InZNear) / (InZFar - InZNear), (T)0
		);
	}
}
