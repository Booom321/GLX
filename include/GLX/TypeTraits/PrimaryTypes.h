#pragma once

#include "BoolConstant.h"
#include "Logical.h"
#include "TypeRelationships.h"

#include <type_traits>

template<typename T>
class GlxIsFloatingPoint : public GlxFalseType
{};

template<>
class GlxIsFloatingPoint<GlxFloat> : public GlxTrueType
{};

template<>
class GlxIsFloatingPoint<GlxDouble> : public GlxTrueType
{};

template<>
class GlxIsFloatingPoint<GlxLongDouble> : public GlxTrueType
{};

template<typename T>
class GlxIsFloatingPoint<const T> : public GlxBoolConstant<GlxIsFloatingPoint<T>::Value>
{};

template<typename T>
class GlxIsFloatingPoint<volatile T> : public GlxBoolConstant<GlxIsFloatingPoint<T>::Value>
{};

template<typename T>
class GlxIsFloatingPoint<const volatile T> : public GlxBoolConstant<GlxIsFloatingPoint<T>::Value>
{};

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
class GlxIsIntegral : public GlxFalseType
{};

template<>
class GlxIsIntegral<GlxBool> : public GlxTrueType
{};

template<>
class GlxIsIntegral<GlxChar> : public GlxTrueType
{};

template<>
class GlxIsIntegral<signed char> : public GlxTrueType
{};

template<>
class GlxIsIntegral<unsigned char> : public GlxTrueType
{};

#ifdef __cpp_char8_t
template<>
class GlxIsIntegral<GlxChar8> : public GlxTrueType
{};
#endif // __cpp_char8_t

template<>
class GlxIsIntegral<GlxChar16> : public GlxTrueType
{};

template<>
class GlxIsIntegral<GlxChar32> : public GlxTrueType
{};

template<>
class GlxIsIntegral<GlxWChar> : public GlxTrueType
{};

template<>
class GlxIsIntegral<short> : public GlxTrueType
{};

template<>
class GlxIsIntegral<unsigned short> : public GlxTrueType
{};

template<>
class GlxIsIntegral<GlxInt32> : public GlxTrueType
{};

template<>
class GlxIsIntegral<GlxUInt32> : public GlxTrueType
{};

template<>
class GlxIsIntegral<long> : public GlxTrueType
{};

template<>
class GlxIsIntegral<unsigned long> : public GlxTrueType
{};

template<>
class GlxIsIntegral<long long> : public GlxTrueType
{};

template<>
class GlxIsIntegral<unsigned long long> : public GlxTrueType
{};

template<typename T>
class GlxIsIntegral<const T> : public GlxBoolConstant<GlxIsIntegral<T>::Value>
{};

template<typename T>
class GlxIsIntegral<volatile T> : public GlxBoolConstant<GlxIsIntegral<T>::Value>
{};

template<typename T>
class GlxIsIntegral<const volatile T> : public GlxBoolConstant<GlxIsIntegral<T>::Value>
{};

///////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
class GlxIsArithmetic : public GlxBoolConstant<GlxIsFloatingPoint<T>::Value || GlxIsIntegral<T>::Value>
{};

////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
class GlxIsArray : public GlxFalseType
{};

template<typename T>
class GlxIsArray<T[]> : public GlxTrueType
{};

template<typename T, GlxSizeT InN>
class GlxIsArray<T[InN]> : public GlxTrueType
{};

////////////////////////////////////////////////////////////////////////////////////////////////

template<typename>
class GlxIsFunction : public GlxFalseType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...)> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......)> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) const> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) volatile> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) const volatile> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) const> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) volatile> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) const volatile> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...)&> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) const&> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) volatile&> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) const volatile&> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......)&> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) const&> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) volatile&> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) const volatile&> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) &&> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) const&&> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) volatile&&> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) const volatile&&> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) &&> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) const&&> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) volatile&&> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) const volatile&&> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) const noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) volatile noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) const volatile noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) const noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) volatile noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) const volatile noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) & noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) const & noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) volatile & noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) const volatile & noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) & noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) const & noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) volatile & noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) const volatile & noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) && noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) const && noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) volatile && noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs...) const volatile && noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) && noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) const && noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) volatile && noexcept> : public GlxTrueType
{};

template<typename TReturnType, typename... TArgs>
class GlxIsFunction<TReturnType(TArgs......) const volatile && noexcept> : public GlxTrueType
{};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
class GlxIsEnum : public GlxBoolConstant<std::is_enum_v<T>>
{};

template<typename T>
class GlxIsPointer : public GlxFalseType
{};

template<typename T>
class GlxIsPointer<T*> : public GlxTrueType
{};

template<typename T>
class GlxIsPointer<const T*> : public GlxTrueType
{};

template<typename T>
class GlxIsPointer<volatile T*> : public GlxTrueType
{};

template<typename T>
class GlxIsPointer<const volatile T*> : public GlxTrueType
{};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
class GlxIsClass : public GlxBoolConstant<std::is_class_v<T>>
{};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename>
class GlxIsUnboundedArray : public GlxFalseType
{};

template<typename T>
class GlxIsUnboundedArray<T[]> : public GlxTrueType
{};

template<typename>
class GlxIsBoundedArray : public GlxFalseType
{};

template<typename T, GlxSizeT InN>
class GlxIsBoundedArray<T[InN]> : public GlxTrueType
{};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
class GlxIsCharType
{
public:
	static GLX_CONSTEXPR GlxBool Value = GlxOr<
		GlxIsSame<T, GlxChar>,
		GlxIsSame<T, GlxWChar>,
#ifdef __cpp_char8_t
		GlxIsSame<T, GlxChar8>,
#endif
		GlxIsSame<T, GlxChar16>,
		GlxIsSame<T, GlxChar32>>::Value;
};

template<typename T>
class GlxIsCharType<const T> : public GlxIsCharType<T>
{};

template<typename T>
class GlxIsCharType<volatile T> : public GlxIsCharType<T>
{};

template<typename T>
class GlxIsCharType<const volatile T> : public GlxIsCharType<T>
{};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
class GlxIsEmpty : public GlxBoolConstant<std::is_empty_v<T>>
{};

template<typename T>
class GlxIsFinal : public GlxBoolConstant<std::is_final_v<T>>
{};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
class GlxIsPODType : public GlxBoolConstant<std::is_pod_v<T>>
{};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
class GlxIsMemberObjectPointer : public GlxBoolConstant<std::is_member_object_pointer_v<T>>
{};

template<typename T>
class GlxIsMemberFunctionPointer : public GlxBoolConstant<std::is_member_function_pointer_v<T>>
{};
