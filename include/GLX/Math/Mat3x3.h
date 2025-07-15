#pragma once

#include "Vector3.h"

namespace GlxNsMath
{
	template<typename T>
	class GlxMat3x3
	{
	public:
		static_assert(GlxIsFloatingPoint<T>::Value);
		using Type = T;

		static GLX_CONSTEXPR GlxInt32 NumColumns = 3;
		static GLX_CONSTEXPR GlxInt32 NumRows = 3;
		static GLX_CONSTEXPR GlxInt32 ElementCount = NumColumns * NumRows;

		union
		{
			Type M[NumRows][NumColumns];
			Type A[ElementCount];

			struct
			{
				Type M00, M01, M02;
				Type M10, M11, M12;
				Type M20, M21, M22;
			};
		};

		GlxMat3x3() = default;
		GlxMat3x3(const GlxMat3x3&) = default;
		GlxMat3x3& operator=(const GlxMat3x3&) = default;
		GlxMat3x3(GlxMat3x3&&) noexcept = default;
		GlxMat3x3& operator=(GlxMat3x3&&) noexcept = default;

		explicit GLX_FORCE_INLINE GlxMat3x3(const Type* InA)
		{
			GLX_MEMCPY(A, InA, ElementCount * sizeof(Type));
		}

		explicit GLX_FORCE_INLINE GlxMat3x3(Type InV)
			:	M00(InV), M01(InV), M02(InV),
				M10(InV), M11(InV), M12(InV),
				M20(InV), M21(InV), M22(InV)
		{}

		GLX_FORCE_INLINE GlxMat3x3(Type InM00, Type InM01, Type InM02, Type InM10, Type InM11, Type InM12, Type InM20, Type InM21, Type InM22)
			:	M00(InM00), M01(InM01), M02(InM02),
				M10(InM10), M11(InM11), M12(InM12),
				M20(InM20), M21(InM21), M22(InM22)
		{}

		GLX_FORCE_INLINE GlxMat3x3(const GlxVector3<Type>& InV0, const GlxVector3<Type>& InV1, const GlxVector3<Type>& InV2)
			:	M00(InV0.X), M01(InV0.Y), M02(InV0.Z),
				M10(InV1.X), M11(InV1.Y), M12(InV1.Z),
				M20(InV2.X), M21(InV2.Y), M22(InV2.Z)
		{}

		~GlxMat3x3() = default;

		GLX_FORCE_INLINE Type operator()(GlxInt32 InR, GlxInt32 InC) const
		{
			return M[InR][InC];
		}

		GLX_FORCE_INLINE Type& operator()(GlxInt32 InR, GlxInt32 InC)
		{
			return M[InR][InC];
		}

		GLX_FORCE_INLINE GlxVector3<Type> RowAt(GlxInt32 InIdx) const
		{
			return GlxVector3<Type>{ M[InIdx][0], M[InIdx][1], M[InIdx][2] };
		}

		GLX_FORCE_INLINE GlxVector3<Type> ColumnAt(GlxInt32 InIdx) const
		{
			return GlxVector3<Type>{ M[0][InIdx], M[1][InIdx], M[2][InIdx] };
		}

		GLX_FORCE_INLINE void SetRow(GlxInt32 InX, Type InX0, Type InX1, Type InX2) const
		{
			M[InX][0] = InX0;
			M[InX][1] = InX1;
			M[InX][2] = InX2;
		}

		GLX_FORCE_INLINE void SetColumn(GlxInt32 InX, Type In0X, Type In1X, Type In2X) const
		{
			M[0][InX] = In0X;
			M[1][InX] = In1X;
			M[2][InX] = In2X;
		}

		GLX_FORCE_INLINE GlxMat3x3<Type> operator-() const
		{
			return GlxMat3x3<Type>{
				-M00, -M01, -M02,
				-M10, -M11, -M12,
				-M20, -M21, -M22
			};
		}

		GlxMat3x3<Type>& operator+=(const GlxMat3x3<Type>& InM)
		{
			M00 += InM.M00, M01 += InM.M01, M02 += InM.M02;
			M10 += InM.M10, M11 += InM.M11, M12 += InM.M12;
			M20 += InM.M20, M21 += InM.M21, M22 += InM.M22;
			return *this;
		}

		GlxMat3x3<Type>& operator-=(const GlxMat3x3<Type>& InM)
		{
			M00 -= InM.M00, M01 -= InM.M01, M02 -= InM.M02;
			M10 -= InM.M10, M11 -= InM.M11, M12 -= InM.M12;
			M20 -= InM.M20, M21 -= InM.M21, M22 -= InM.M22;
			return *this;
		}

		GlxMat3x3<Type>& operator*=(Type InV)
		{
			M00 *= InV, M01 *= InV, M02 *= InV;
			M10 *= InV, M11 *= InV, M12 *= InV;
			M20 *= InV, M21 *= InV, M22 *= InV;
			return *this;
		}

		GlxMat3x3<Type>& operator*=(const GlxMat3x3<T>& InM)
		{
			Type TmpM00 = M00 * InM.M00 + M01 * InM.M10 + M02 * InM.M20;
			Type TmpM01 = M00 * InM.M01 + M01 * InM.M11 + M02 * InM.M21;
			Type TmpM02 = M00 * InM.M02 + M01 * InM.M12 + M02 * InM.M22;
			Type TmpM10 = M10 * InM.M00 + M11 * InM.M10 + M12 * InM.M20;
			Type TmpM11 = M10 * InM.M01 + M11 * InM.M11 + M12 * InM.M21;
			Type TmpM12 = M10 * InM.M02 + M11 * InM.M12 + M12 * InM.M22;
			Type TmpM20 = M20 * InM.M00 + M21 * InM.M10 + M22 * InM.M20;
			Type TmpM21 = M20 * InM.M01 + M21 * InM.M11 + M22 * InM.M21;
			Type TmpM22 = M20 * InM.M02 + M21 * InM.M12 + M22 * InM.M22;
			M00 = TmpM00, M01 = TmpM01, M02 = TmpM02;
			M10 = TmpM10, M11 = TmpM11, M12 = TmpM12;
			M20 = TmpM20, M21 = TmpM21, M22 = TmpM22;
			return *this;
		}

		GlxMat3x3<Type>& operator/=(Type InV)
		{
			M00 /= InV, M01 /= InV, M02 /= InV;
			M10 /= InV, M11 /= InV, M12 /= InV;
			M20 /= InV, M21 /= InV, M22 /= InV;
			return *this;
		}

		GlxBool operator==(const GlxMat3x3<Type>& InM) const
		{
			return	M00 == InM.M00 && M01 == InM.M01 && M02 == InM.M02 &&
					M10 == InM.M10 && M11 == InM.M11 && M12 == InM.M12 &&
					M20 == InM.M20 && M21 == InM.M21 && M22 == InM.M22;
		}

		GLX_FORCE_INLINE GlxBool operator!=(const GlxMat3x3<Type>& InM) const
		{
			return !operator==(InM);
		}

		static const GlxMat3x3 Identity;
	};

	template<typename T>
	const GlxMat3x3<T> GlxMat3x3<T>::Identity = GlxMat3x3<T>{
		static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
		static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
		static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
		static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
	};

	template<typename T>
	GlxMat3x3<T> operator+(const GlxMat3x3<T>& InX, const GlxMat3x3<T>& InY)
	{
		return GlxMat3x3<T>{
			InX.M00 + InY.M00, InX.M01 + InY.M01, InX.M02 + InY.M02,
			InX.M10 + InY.M10, InX.M11 + InY.M11, InX.M12 + InY.M12,
			InX.M20 + InY.M20, InX.M21 + InY.M21, InX.M22 + InY.M22
		};
	}

	template<typename T>
	GlxMat3x3<T> operator-(const GlxMat3x3<T>& InX, const GlxMat3x3<T>& InY)
	{
		return GlxMat3x3<T>{
			InX.M00 - InY.M00, InX.M01 - InY.M01, InX.M02 - InY.M02,
			InX.M10 - InY.M10, InX.M11 - InY.M11, InX.M12 - InY.M12,
			InX.M20 - InY.M20, InX.M21 - InY.M21, InX.M22 - InY.M22
		};
	}

	template<typename T>
	GlxMat3x3<T> operator*(const GlxMat3x3<T>& InX, T InV)
	{
		return GlxMat3x3<T>{
			InX.M00 * InV, InX.M01 * InV, InX.M02 * InV,
			InX.M10 * InV, InX.M11 * InV, InX.M12 * InV,
			InX.M20 * InV, InX.M21 * InV, InX.M22 * InV
		};
	}

	template<typename T>
	GlxMat3x3<T> operator*(T InV, const GlxMat3x3<T>& InX)
	{
		return GlxMat3x3<T>{
			InV * InX.M00, InV * InX.M01, InV * InX.M02,
			InV * InX.M10, InV * InX.M11, InV * InX.M12,
			InV * InX.M20, InV * InX.M21, InV * InX.M22
		};
	}

	template<typename T>
	GlxMat3x3<T> operator*(const GlxMat3x3<T>& InX, const GlxMat3x3<T>& InY)
	{
		return GlxMat3x3<T>{
			InX.M00 * InY.M00 + InX.M01 * InY.M10 + InX.M02 * InY.M20,
			InX.M00 * InY.M01 + InX.M01 * InY.M11 + InX.M02 * InY.M21,
			InX.M00 * InY.M02 + InX.M01 * InY.M12 + InX.M02 * InY.M22,
			InX.M10 * InY.M00 + InX.M11 * InY.M10 + InX.M12 * InY.M20,
			InX.M10 * InY.M01 + InX.M11 * InY.M11 + InX.M12 * InY.M21,
			InX.M10 * InY.M02 + InX.M11 * InY.M12 + InX.M12 * InY.M22,
			InX.M20 * InY.M00 + InX.M21 * InY.M10 + InX.M22 * InY.M20,
			InX.M20 * InY.M01 + InX.M21 * InY.M11 + InX.M22 * InY.M21,
			InX.M20 * InY.M02 + InX.M21 * InY.M12 + InX.M22 * InY.M22
		};
	}

	template<typename T>
	GlxMat3x3<T> operator/(const GlxMat3x3<T>& InX, T InV)
	{
		return GlxMat3x3<T>{
			InX.M00 / InV, InX.M01 / InV, InX.M02 / InV,
			InX.M10 / InV, InX.M11 / InV, InX.M12 / InV,
			InX.M20 / InV, InX.M21 / InV, InX.M22 / InV
		};
	}

	using GlxMat3x3f = GlxMat3x3<GlxFloat>;
	using GlxMat3x3d = GlxMat3x3<GlxDouble>;
	using GlxMat3x3ld = GlxMat3x3<GlxLongDouble>;

	using GlxMat3x3i = GlxMat3x3<GlxInt32>;
	using GlxMat3x3u = GlxMat3x3<GlxUInt32>;
}
