#pragma once

#include "GLX/Preprocessor.h"
#include "GLX/Types/DataTypes.h"
#include "GLX/Utils/Print.h"

using GlxAssertCallback = void (*)(const GlxChar* InExpr, const GlxInt32 InLine, const GlxChar* InFile, const GlxChar* InMessage, GlxSizeT InMessageLen);

void DefaultAssertionCallback(const GlxChar* InExpr, const GlxInt32 InLine, const GlxChar* InFile, const GlxChar* InMessage, GlxSizeT InMessageLen)
{
	if (InMessage)
	{
		Print("Assertion failed: {} [File: {}, Line: {}, Message: {}]\n", InExpr, InFile, InLine, InMessage);
	}
	else
	{
		Print("Assertion failed: {} [File: {}, Line: {}]\n", InExpr, InFile, InLine);
	}
}

class GLX_API GlxAssertion
{
public:
	template<typename... TArgs>
	static void Failed(const GlxChar* InExpr, const GlxInt32 InLine, const GlxChar* InFile, const GlxChar* InMessage, TArgs&&... InArgs)
	{
		if (InMessage)
		{
			auto Buffer = fmt::memory_buffer();
			auto FormatArgs = fmt::make_format_args(InArgs...);
			fmt::detail::vformat_to(Buffer, InMessage, FormatArgs);
			Buffer.push_back('\0');
			AssertCallback(InExpr, InLine, InFile, Buffer.data(), Buffer.size() - 1);
		}
		else
		{
			AssertCallback(InExpr, InLine, InFile, nullptr, 0);
		}
	}

	static void SetAssertCallback(GlxAssertCallback InCallback);

private:
	static GlxAssertCallback AssertCallback;
};

GlxAssertCallback GlxAssertion::AssertCallback = DefaultAssertionCallback;

void GlxAssertion::SetAssertCallback(GlxAssertCallback InCallback)
{
	AssertCallback = InCallback;
}

#if !defined(GLX_ALWAYS_ASSERT)
	#define GLX_ALWAYS_ASSERT(...)                                               \
		{                                                                        \
			if (!(__VA_ARGS__))                                                  \
			{                                                                    \
				GlxAssertion::Failed(#__VA_ARGS__, GLX_LINE, GLX_FILE, nullptr); \
				GLX_DEBUG_BREAK;                                                 \
			}                                                                    \
		}
#endif

#if !defined(GLX_ALWAYS_ASSERT_MSG)
	#define GLX_ALWAYS_ASSERT_MSG(InExpr, InMessage, ...)                                  \
		{                                                                                  \
			if (!(InExpr))                                                                 \
			{                                                                              \
				GlxAssertion::Failed(#InExpr, GLX_LINE, GLX_FILE, InMessage, __VA_ARGS__); \
				GLX_DEBUG_BREAK;                                                           \
			}                                                                              \
		}
#endif

#if (GLX_ENABLE_ASSERTION == 1)
	#define GLX_ASSERT(...) GLX_ALWAYS_ASSERT(__VA_ARGS__)
	#define GLX_ASSERT_MSG(InExpr, InMessage, ...) GLX_ALWAYS_ASSERT_MSG(InExpr, InMessage, __VA_ARGS__)
#else
	#define GLX_ASSERT(...)
	#define GLX_ASSERT_MSG(InExpr, InMessage, ...)
#endif
