#pragma once

// Reference: https://rodusek.com/posts/2021/02/24/creating-a-fast-and-efficient-delegate-type-part-1/
// Reference: https://rodusek.com/posts/2021/02/26/creating-a-fast-and-efficient-delegate-type-part-2/
// Reference: https://rodusek.com/posts/2021/02/26/creating-a-fast-and-efficient-delegate-type-part-3/

#include "GLX/Assert.h"
#include "GLX/TypeTraits/Decay.h"
#include "GLX/TypeTraits/Trivial.h"
#include "GLX/TypeTraits/EnableIf.h"
#include "GLX/TypeTraits/IsReference.h"
#include "GLX/TypeTraits/IsInvocableR.h"
#include "GLX/TypeTraits/RemoveReference.h"
#include "GLX/TypeTraits/IsDefaultConstructible.h"

class GlxBadDelegateCallException : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Bad delegate call";
	}
};

template<typename T>
class GlxDelegate;

template<typename TReturnType, typename... TArgs>
class GlxDelegate<TReturnType(TArgs...)>
{
private:
	using StubFunction = TReturnType (*)(const GlxDelegate*, TArgs...);

public:
	GLX_FORCE_INLINE GlxDelegate()
		: ObjectPtr(nullptr), Stub(&NullStub)
	{}

	GlxDelegate(const GlxDelegate&) = default;
	GlxDelegate& operator=(const GlxDelegate&) = default;
	GlxDelegate(GlxDelegate&&) noexcept = default;
	GlxDelegate& operator=(GlxDelegate&&) noexcept = default;

	template<
		typename TLambda,
		typename = typename GlxEnableIf<
			!GlxIsSame<typename GlxDecay<TLambda>::Type, GlxDelegate>::Value &&
			GlxIsInvocableR<TReturnType, const TLambda&, TArgs...>::Value>
		::Type>
	GLX_FORCE_INLINE GlxDelegate(TLambda&& InLambda)
		: Stub(&LambdaStub<typename GlxDecay<TLambda>::Type>)
	{
		new (static_cast<void*>(Storage)) typename GlxDecay<TLambda>::Type(Forward<TLambda>(InLambda));
	}

	TReturnType operator()(TArgs... InArgs)
	{
		return (*Stub)(this, Forward<TArgs>(InArgs)...);
	}

	GLX_FORCE_INLINE void Reset()
	{
		ObjectPtr = nullptr;
		Stub = &NullStub;
	}

	GLX_FORCE_INLINE explicit operator bool() const noexcept
	{
		return Stub != &NullStub;
	}

	template<
		TReturnType (*InFunc)(TArgs...),
		typename = typename GlxEnableIf<GlxIsInvocableR<TReturnType, decltype(InFunc), TArgs...>::Value>::Type>
	GLX_FORCE_INLINE void Bind()
	{
		ObjectPtr = nullptr;
		Stub = &FunctionStub<InFunc>;
	}

	template<
		auto InMemberFunc,
		typename TClass,
		typename = typename GlxEnableIf<GlxIsInvocableR<TReturnType, decltype(InMemberFunc), TClass*, TArgs...>::Value>::Type>
	GLX_FORCE_INLINE void Bind(TClass* InObjectPtr)
	{
		ObjectPtr = InObjectPtr;
		Stub = &MemberFunctionStub<InMemberFunc, TClass>;
	}

	template<
		auto InMemberFunc,
		typename TClass,
		typename = typename GlxEnableIf<GlxIsInvocableR<TReturnType, decltype(InMemberFunc), const TClass*, TArgs...>::Value>::Type>
	GLX_FORCE_INLINE void Bind(const TClass* InObjectPtr)
	{
		ConstObjectPtr = InObjectPtr;
		Stub = &ConstMemberFunctionStub<InMemberFunc, TClass>;
	}

	template<
		typename TCallable,
		typename = typename GlxEnableIf<GlxIsInvocableR<TReturnType, TCallable, TArgs...>::Value && !GlxIsFunction<TCallable>::Value>::Type>
	GLX_FORCE_INLINE void Bind(TCallable* InCallablePtr)
	{
		ObjectPtr = InCallablePtr;
		Stub = &CallableStub<TCallable>;
	}

	template<
		typename TCallable,
		typename = typename GlxEnableIf<GlxIsInvocableR<TReturnType, const TCallable, TArgs...>::Value && !GlxIsFunction<TCallable>::Value>::Type>
	GLX_FORCE_INLINE void Bind(const TCallable* InCallablePtr)
	{
		ConstObjectPtr = InCallablePtr;
		Stub = &ConstCallableStub<TCallable>;
	}

	template<
		typename TCallable,
		typename = typename GlxEnableIf<
			GlxIsEmpty<TCallable>::Value &&
			GlxIsDefaultConstructible<TCallable>::Value &&
			GlxIsInvocableR<TReturnType, TCallable, TArgs...>::Value
		>::Type>
	GLX_FORCE_INLINE void Bind()
	{
		ObjectPtr = nullptr;
		Stub = &EmptyCallableStub<TCallable>;
	}

	template<
		typename TLambda,
		typename = typename GlxEnableIf<
			!GlxIsSame<typename GlxDecay<TLambda>::Type, GlxDelegate>::Value &&
			GlxIsInvocableR<TReturnType, const TLambda&, TArgs...>::Value
		>::Type>
	GLX_FORCE_INLINE void Bind(TLambda&& InLambda)
	{
		new (static_cast<void*>(Storage)) typename GlxDecay<TLambda>::Type(Forward<TLambda>(InLambda));
		Stub = &LambdaStub<typename GlxDecay<TLambda>::Type>;
	}

private:
	GLX_NORETURN GLX_FORCE_INLINE static TReturnType NullStub(const GlxDelegate*, TArgs... InArgs)
	{
		throw GlxBadDelegateCallException{};
	}

	template<TReturnType (*InFunc)(TArgs...)>
	GLX_FORCE_INLINE static TReturnType FunctionStub(const GlxDelegate*, TArgs... InArgs)
	{
		return (*InFunc)(Forward<TArgs>(InArgs)...);
	}

	template<auto InMemberFunc, typename TClass>
	GLX_FORCE_INLINE static TReturnType MemberFunctionStub(const GlxDelegate* InDelegate, TArgs... InArgs)
	{
		return (static_cast<TClass*>(InDelegate->ObjectPtr)->*InMemberFunc)(Forward<TArgs>(InArgs)...);
	}

	template<auto InMemberFunc, typename TClass>
	GLX_FORCE_INLINE static TReturnType ConstMemberFunctionStub(const GlxDelegate* InDelegate, TArgs... InArgs)
	{
		return (static_cast<const TClass*>(InDelegate->ConstObjectPtr)->*InMemberFunc)(Forward<TArgs>(InArgs)...);
	}

	template<typename TCallable>
	GLX_FORCE_INLINE static TReturnType CallableStub(const GlxDelegate* InDelegate, TArgs... InArgs)
	{
		return (*static_cast<TCallable*>(InDelegate->ObjectPtr))(Forward<TArgs>(InArgs)...);
	}

	template<typename TCallable>
	GLX_FORCE_INLINE static TReturnType ConstCallableStub(const GlxDelegate* InDelegate, TArgs... InArgs)
	{
		return (*static_cast<const TCallable*>(InDelegate->ConstObjectPtr))(Forward<TArgs>(InArgs)...);
	}

	template<typename TCallable>
	GLX_FORCE_INLINE static TReturnType EmptyCallableStub(const GlxDelegate*, TArgs... InArgs)
	{
		return TCallable{}(Forward<TArgs>(InArgs)...);
	}

	template<typename TLambda>
	GLX_FORCE_INLINE static TReturnType LambdaStub(const GlxDelegate* InDelegate, TArgs... InArgs)
	{
		return (*reinterpret_cast<const TLambda*>(InDelegate->Storage))(Forward<TArgs>(InArgs)...);
	}

	static GLX_CONSTEXPR GlxInt32 MaxStorageSize = GLX_MAX(sizeof(void*), sizeof(void(*)()));

	StubFunction Stub;
	union
	{
		void* ObjectPtr;
		const void* ConstObjectPtr;
		GlxChar Storage[MaxStorageSize];
	};
};
