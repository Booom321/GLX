#pragma once

#include "Vector4.h"

namespace GlxNsMath
{
	template<typename T>
	class GlxMat4x4
	{
	public:
		static_assert(GlxIsFloatingPoint<T>::Value);
		using Type = T;

		static GLX_CONSTEXPR GlxInt32 NumColumns = 4;
		static GLX_CONSTEXPR GlxInt32 NumRows = 4;
		static GLX_CONSTEXPR GlxInt32 ElementCount = NumColumns * NumRows;

		union
		{
			Type M[NumRows][NumColumns];
			Type A[ElementCount];

			struct
			{
				Type M00, M01, M02, M03;
				Type M10, M11, M12, M13;
				Type M20, M21, M22, M23;
				Type M30, M31, M32, M33;
			};
		};

		GlxMat4x4() = default;
		GlxMat4x4(const GlxMat4x4&) = default;
		GlxMat4x4& operator=(const GlxMat4x4&) = default;
		GlxMat4x4(GlxMat4x4&&) noexcept = default;
		GlxMat4x4& operator=(GlxMat4x4&&) noexcept = default;

		explicit GLX_FORCE_INLINE GlxMat4x4(const Type* InA)
		{
			GLX_MEMCPY(A, InA, ElementCount * sizeof(Type));
		}

		explicit GLX_FORCE_INLINE GlxMat4x4(Type InV)
			:	M00(InV), M01(InV), M02(InV), M03(InV),
				M10(InV), M11(InV), M12(InV), M13(InV),
				M20(InV), M21(InV), M22(InV), M23(InV),
				M30(InV), M31(InV), M32(InV), M33(InV)
		{}

		GLX_FORCE_INLINE GlxMat4x4(
			Type InM00, Type InM01, Type InM02, Type InM03,
			Type InM10, Type InM11, Type InM12, Type InM13,
			Type InM20, Type InM21, Type InM22, Type InM23,
			Type InM30, Type InM31, Type InM32, Type InM33)
			:	M00(InM00), M01(InM01), M02(InM02), M03(InM03),
				M10(InM10), M11(InM11), M12(InM12), M13(InM13),
				M20(InM20), M21(InM21), M22(InM22), M23(InM23),
				M30(InM30), M31(InM31), M32(InM32), M33(InM33)
		{}

		GLX_FORCE_INLINE GlxMat4x4(const GlxVector4<Type>& InV0, const GlxVector4<Type>& InV1, const GlxVector4<Type>& InV2, const GlxVector4<Type>& InV3)
			:	M00(InV0.X), M01(InV0.Y), M02(InV0.Z), M03(InV0.W),
				M10(InV1.X), M11(InV1.Y), M12(InV1.Z), M13(InV1.W),
				M20(InV2.X), M21(InV2.Y), M22(InV2.Z), M23(InV2.W),
				M30(InV3.X), M31(InV3.Y), M32(InV3.Z), M33(InV3.W)
		{}

		~GlxMat4x4() = default;

		GLX_FORCE_INLINE Type operator()(GlxInt32 InR, GlxInt32 InC) const
		{
			return M[InR][InC];
		}

		GLX_FORCE_INLINE Type& operator()(GlxInt32 InR, GlxInt32 InC)
		{
			return M[InR][InC];
		}

		GLX_FORCE_INLINE GlxVector4<Type> RowAt(GlxInt32 InIdx) const
		{
			return GlxVector4<Type>{ M[InIdx][0], M[InIdx][1], M[InIdx][2], M[InIdx][3] };
		}

		GLX_FORCE_INLINE GlxVector4<Type> ColumnAt(GlxInt32 InIdx) const
		{
			return GlxVector4<Type>{ M[0][InIdx], M[1][InIdx], M[2][InIdx], M[3][InIdx] };
		}

		GLX_FORCE_INLINE void SetRow(GlxInt32 InX, Type InX0, Type InX1, Type InX2, Type InX3) const
		{
			M[InX][0] = InX0;
			M[InX][1] = InX1;
			M[InX][2] = InX2;
			M[InX][3] = InX3;
		}

		GLX_FORCE_INLINE void SetColumn(GlxInt32 InX, Type In0X, Type In1X, Type In2X, Type In3X) const
		{
			M[0][InX] = In0X;
			M[1][InX] = In1X;
			M[2][InX] = In2X;
			M[3][InX] = In3X;
		}

		GLX_FORCE_INLINE GlxMat4x4<Type> operator-() const
		{
			return GlxMat4x4<Type>{
				-M00, -M01, -M02, -M03,
				-M10, -M11, -M12, -M13,
				-M20, -M21, -M22, -M23,
				-M30, -M31, -M32, -M33
			};
		}

		GlxMat4x4<Type>& operator+=(const GlxMat4x4<Type>& InM)
		{
			M00 += InM.M00, M01 += InM.M01, M02 += InM.M02, M03 += InM.M03;
			M10 += InM.M10, M11 += InM.M11, M12 += InM.M12, M13 += InM.M13;
			M20 += InM.M20, M21 += InM.M21, M22 += InM.M22, M23 += InM.M23;
			M30 += InM.M30, M31 += InM.M31, M32 += InM.M32, M33 += InM.M33;
			return *this;
		}

		GlxMat4x4<Type>& operator-=(const GlxMat4x4<Type>& InM)
		{
			M00 -= InM.M00, M01 -= InM.M01, M02 -= InM.M02, M03 -= InM.M03;
			M10 -= InM.M10, M11 -= InM.M11, M12 -= InM.M12, M13 -= InM.M13;
			M20 -= InM.M20, M21 -= InM.M21, M22 -= InM.M22, M23 -= InM.M23;
			M30 -= InM.M30, M31 -= InM.M31, M32 -= InM.M32, M33 -= InM.M33;
			return *this;
		}

		GlxMat4x4<Type>& operator*=(Type InV)
		{
			M00 *= InV, M01 *= InV, M02 *= InV, M03 *= InV;
			M10 *= InV, M11 *= InV, M12 *= InV, M13 *= InV;
			M20 *= InV, M21 *= InV, M22 *= InV, M23 *= InV;
			M30 *= InV, M31 *= InV, M32 *= InV, M33 *= InV;
			return *this;
		}

		GlxMat4x4<Type>& operator*=(const GlxMat4x4<T>& InM)
		{
			Type TmpM00 = M00 * InM.M00 + M01 * InM.M10 + M02 * InM.M20 + M03 * InM.M30;
			Type TmpM01 = M00 * InM.M01 + M01 * InM.M11 + M02 * InM.M21 + M03 * InM.M31;
			Type TmpM02 = M00 * InM.M02 + M01 * InM.M12 + M02 * InM.M22 + M03 * InM.M32;
			Type TmpM03 = M00 * InM.M03 + M01 * InM.M13 + M02 * InM.M23 + M03 * InM.M33;
			Type TmpM10 = M10 * InM.M00 + M11 * InM.M10 + M12 * InM.M20 + M13 * InM.M30;
			Type TmpM11 = M10 * InM.M01 + M11 * InM.M11 + M12 * InM.M21 + M13 * InM.M31;
			Type TmpM12 = M10 * InM.M02 + M11 * InM.M12 + M12 * InM.M22 + M13 * InM.M32;
			Type TmpM13 = M10 * InM.M03 + M11 * InM.M13 + M12 * InM.M23 + M13 * InM.M33;
			Type TmpM20 = M20 * InM.M00 + M21 * InM.M10 + M22 * InM.M20 + M23 * InM.M30;
			Type TmpM21 = M20 * InM.M01 + M21 * InM.M11 + M22 * InM.M21 + M23 * InM.M31;
			Type TmpM22 = M20 * InM.M02 + M21 * InM.M12 + M22 * InM.M22 + M23 * InM.M32;
			Type TmpM23 = M20 * InM.M03 + M21 * InM.M13 + M22 * InM.M23 + M23 * InM.M33;
			Type TmpM30 = M30 * InM.M00 + M31 * InM.M10 + M32 * InM.M20 + M33 * InM.M30;
			Type TmpM31 = M30 * InM.M01 + M31 * InM.M11 + M32 * InM.M21 + M33 * InM.M31;
			Type TmpM32 = M30 * InM.M02 + M31 * InM.M12 + M32 * InM.M22 + M33 * InM.M32;
			Type TmpM33 = M30 * InM.M03 + M31 * InM.M13 + M32 * InM.M23 + M33 * InM.M33;

			M00 = TmpM00, M01 = TmpM01, M02 = TmpM02, M03 = TmpM03;
			M10 = TmpM10, M11 = TmpM11, M12 = TmpM12, M13 = TmpM13;
			M20 = TmpM20, M21 = TmpM21, M22 = TmpM22, M23 = TmpM23;
			M30 = TmpM30, M31 = TmpM31, M32 = TmpM32, M33 = TmpM33;
			return *this;
		}

		GlxMat4x4<Type>& operator/=(Type InV)
		{
			M00 /= InV, M01 /= InV, M02 /= InV, M03 /= InV;
			M10 /= InV, M11 /= InV, M12 /= InV, M13 /= InV;
			M20 /= InV, M21 /= InV, M22 /= InV, M23 /= InV;
			M30 /= InV, M31 /= InV, M32 /= InV, M33 /= InV;
			return *this;
		}

		GlxBool operator==(const GlxMat4x4<Type>& InM) const
		{
			return	M00 == InM.M00 && M01 == InM.M01 && M02 == InM.M02 && M03 == InM.M03 &&
					M10 == InM.M10 && M11 == InM.M11 && M12 == InM.M12 && M13 == InM.M13 &&
					M20 == InM.M20 && M21 == InM.M21 && M22 == InM.M22 && M23 == InM.M23 &&
					M30 == InM.M30 && M31 == InM.M31 && M32 == InM.M32 && M33 == InM.M33;
		}

		GLX_FORCE_INLINE GlxBool operator!=(const GlxMat4x4<Type>& InM) const
		{
			return !operator==(InM);
		}

		static const GlxMat4x4 Identity;
	};

	template<typename T>
	const GlxMat4x4<T> GlxMat4x4<T>::Identity = GlxMat4x4<T>{
		static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
		static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
		static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
		static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
	};

	template<typename T>
	GlxMat4x4<T> operator+(const GlxMat4x4<T>& InX, const GlxMat4x4<T>& InY)
	{
		return GlxMat4x4<T>{
			InX.M00 + InY.M00, InX.M01 + InY.M01, InX.M02 + InY.M02, InX.M03 + InY.M03,
			InX.M10 + InY.M10, InX.M11 + InY.M11, InX.M12 + InY.M12, InX.M13 + InY.M13,
			InX.M20 + InY.M20, InX.M21 + InY.M21, InX.M22 + InY.M22, InX.M23 + InY.M23,
			InX.M30 + InY.M30, InX.M31 + InY.M31, InX.M32 + InY.M32, InX.M33 + InY.M33
		};
	}

	template<typename T>
	GlxMat4x4<T> operator-(const GlxMat4x4<T>& InX, const GlxMat4x4<T>& InY)
	{
		return GlxMat4x4<T>{
			InX.M00 - InY.M00, InX.M01 - InY.M01, InX.M02 - InY.M02, InX.M03 - InY.M03,
			InX.M10 - InY.M10, InX.M11 - InY.M11, InX.M12 - InY.M12, InX.M13 - InY.M13,
			InX.M20 - InY.M20, InX.M21 - InY.M21, InX.M22 - InY.M22, InX.M23 - InY.M23,
			InX.M30 - InY.M30, InX.M31 - InY.M31, InX.M32 - InY.M32, InX.M33 - InY.M33
		};
	}

	template<typename T>
	GlxMat4x4<T> operator*(const GlxMat4x4<T>& InX, T InV)
	{
		return GlxMat4x4<T>{
			InX.M00 * InV, InX.M01 * InV, InX.M02 * InV, InX.M03 * InV,
			InX.M10 * InV, InX.M11 * InV, InX.M12 * InV, InX.M13 * InV,
			InX.M20 * InV, InX.M21 * InV, InX.M22 * InV, InX.M23 * InV,
			InX.M30 * InV, InX.M31 * InV, InX.M32 * InV, InX.M33 * InV
		};
	}

	template<typename T>
	GlxMat4x4<T> operator*(T InV, const GlxMat4x4<T>& InX)
	{
		return GlxMat4x4<T>{
			InV * InX.M00, InV * InX.M01, InV * InX.M02, InV * InX.M03,
			InV * InX.M10, InV * InX.M11, InV * InX.M12, InV * InX.M13,
			InV * InX.M20, InV * InX.M21, InV * InX.M22, InV * InX.M23,
			InV * InX.M30, InV * InX.M31, InV * InX.M32, InV * InX.M33
		};
	}

	template<typename T>
	GlxMat4x4<T> operator*(const GlxMat4x4<T>& InX, const GlxMat4x4<T>& InY)
	{
		return GlxMat4x4<T>{
			InX.M00 * InY.M00 + InX.M01 * InY.M10 + InX.M02 * InY.M20 + InX.M03 * InY.M30,
			InX.M00 * InY.M01 + InX.M01 * InY.M11 + InX.M02 * InY.M21 + InX.M03 * InY.M31,
			InX.M00 * InY.M02 + InX.M01 * InY.M12 + InX.M02 * InY.M22 + InX.M03 * InY.M32,
			InX.M00 * InY.M03 + InX.M01 * InY.M13 + InX.M02 * InY.M23 + InX.M03 * InY.M33,
			InX.M10 * InY.M00 + InX.M11 * InY.M10 + InX.M12 * InY.M20 + InX.M13 * InY.M30,
			InX.M10 * InY.M01 + InX.M11 * InY.M11 + InX.M12 * InY.M21 + InX.M13 * InY.M31,
			InX.M10 * InY.M02 + InX.M11 * InY.M12 + InX.M12 * InY.M22 + InX.M13 * InY.M32,
			InX.M10 * InY.M03 + InX.M11 * InY.M13 + InX.M12 * InY.M23 + InX.M13 * InY.M33,
			InX.M20 * InY.M00 + InX.M21 * InY.M10 + InX.M22 * InY.M20 + InX.M23 * InY.M30,
			InX.M20 * InY.M01 + InX.M21 * InY.M11 + InX.M22 * InY.M21 + InX.M23 * InY.M31,
			InX.M20 * InY.M02 + InX.M21 * InY.M12 + InX.M22 * InY.M22 + InX.M23 * InY.M32,
			InX.M20 * InY.M03 + InX.M21 * InY.M13 + InX.M22 * InY.M23 + InX.M23 * InY.M33,
			InX.M30 * InY.M00 + InX.M31 * InY.M10 + InX.M32 * InY.M20 + InX.M33 * InY.M30,
			InX.M30 * InY.M01 + InX.M31 * InY.M11 + InX.M32 * InY.M21 + InX.M33 * InY.M31,
			InX.M30 * InY.M02 + InX.M31 * InY.M12 + InX.M32 * InY.M22 + InX.M33 * InY.M32,
			InX.M30 * InY.M03 + InX.M31 * InY.M13 + InX.M32 * InY.M23 + InX.M33 * InY.M33
		};
	}

	template<typename T>
	GlxMat4x4<T> operator/(const GlxMat4x4<T>& InX, T InV)
	{
		return GlxMat4x4<T>{
			InX.M00 / InV, InX.M01 / InV, InX.M02 / InV, InX.M03 / InV,
			InX.M10 / InV, InX.M11 / InV, InX.M12 / InV, InX.M13 / InV,
			InX.M20 / InV, InX.M21 / InV, InX.M22 / InV, InX.M23 / InV,
			InX.M30 / InV, InX.M31 / InV, InX.M32 / InV, InX.M33 / InV
		};
	}

	using GlxMat4x4f = GlxMat4x4<GlxFloat>;
	using GlxMat4x4d = GlxMat4x4<GlxDouble>;
	using GlxMat4x4ld = GlxMat4x4<GlxLongDouble>;

	using GlxMat4x4i = GlxMat4x4<GlxInt32>;
	using GlxMat4x4u = GlxMat4x4<GlxUInt32>;
}
