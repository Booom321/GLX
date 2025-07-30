#pragma once

#include "GLX/Containers/DynamicArray.h"
#include "GLX/String/String.h"
#include "GLX/Types/Pair.h"
#include "GLX/TypeTraits/RemoveCVRef.h"
#include "GLX/Utils/FromString.h"

class GLX_API GlxCommandLine
{
public:
	static void SetCommandLine(GlxInt32 InArgCount, GlxChar** InArgv);
	static void Reset();
	static void Release();
	static void Parse();
	static void AddCommandLineArg(const GlxChar* InArg);

	static GlxBool HasCommandLineOption(const GlxChar* InOptionName, GlxBool InIgnoreCase = false);
	static GlxInt64 GetCommandLineOptionIndex(const GlxChar* InOptionName, GlxBool InIgnoreCase = false);

	GLX_NODISCARD static GLX_FORCE_INLINE GlxBool IsParsed()
	{
		return Parsed;
	}

	GLX_NODISCARD static GLX_FORCE_INLINE GlxInt32 GetCommandLineArgCount()
	{
		return (GlxInt32)CmdLineArgs.GetElementCount();
	}

	GLX_NODISCARD static GLX_FORCE_INLINE const GlxString& GetCommandLineAsString()
	{
		return CmdLine;
	}

	GLX_NODISCARD static GLX_FORCE_INLINE const GlxString& GetExeFilePath()
	{
		return CmdLineArgs[0];
	}

	GLX_NODISCARD static GLX_FORCE_INLINE const GlxString& GetCommandLineArgAt(GlxInt64 InIndex)
	{
		return CmdLineArgs[InIndex];
	}

	GLX_NODISCARD static GLX_FORCE_INLINE const GlxDynamicArray<GlxString>& GetCommandLineArgs()
	{
		return CmdLineArgs;
	}

	template<
		typename T,
		typename U = typename GlxRemoveCVRef<T>::Type>
	static GlxBool GetValueOf(const GlxChar* InOptionName, U* InValue, GlxBool InIgnoreCase = false)
	{
		if (!InOptionName || !InValue)
		{
			return false;
		}

		GlxInt64 Index = GetCommandLineOptionIndex(InOptionName);

		if (Index == GlxDynamicArray<GlxPair<GlxString, GlxString>>::InvalidIndex)
		{
			return false;
		}

		FromString(OptionValuePairs[Index].Second.GetData(), InValue);

		return true;
	}

private:
	static GlxBool Parsed;
	static GlxString CmdLine;
	static GlxDynamicArray<GlxString> CmdLineArgs;
	static GlxDynamicArray<GlxPair<GlxString, GlxString>> OptionValuePairs;
};

GlxBool GlxCommandLine::Parsed = false;
GlxString GlxCommandLine::CmdLine{};
GlxDynamicArray<GlxString> GlxCommandLine::CmdLineArgs{};
GlxDynamicArray<GlxPair<GlxString, GlxString>> GlxCommandLine::OptionValuePairs{};

void GlxCommandLine::SetCommandLine(GlxInt32 InArgCount, GlxChar** InArgv)
{
	CmdLine.Clear();
	CmdLineArgs.Clear();

	CmdLineArgs.Reserve(InArgCount);

	for (GlxInt32 Index = 0; Index < InArgCount; ++Index)
	{
		CmdLineArgs.EmplaceBack(InArgv[Index]);
		CmdLine.Append(InArgv[Index]);
		CmdLine.Append(' ', 1);
	}

	CmdLine.TrimEnd();
}

void GlxCommandLine::Reset()
{
	CmdLine.Clear();
	CmdLineArgs.Clear();
	OptionValuePairs.Clear();
	Parsed = false;
}

void GlxCommandLine::Release()
{
	CmdLine.Release();
	CmdLineArgs.Release();
	OptionValuePairs.Release();
	Parsed = false;
}

void ParseImpl(const GlxString& InArg, GlxString& InOption, GlxString& InValue)
{
	const GlxInt64 Pos = InArg.FindChar('=');

	if (Pos != GlxString::InvalidIndex)
	{
		GLX_ASSERT_MSG(Pos + 1 != InArg.GetElementCount(), "Missing value for this command line option.");
		GLX_ASSERT_MSG(Pos != 0, "Missing name for this command line option.");

		InOption = InArg.Substring(0, Pos);
		InValue = InArg.Substring(Pos + 1);
	}
	else
	{
		GLX_ASSERT_MSG(InArg.GetElementCount() != 0, "Missing name for this command line option.");

		// Let it be a boolean flag (example: -use-this-feature, -disable-this-feature, ...)
		InOption = InArg;
		InValue = "1";
	}
}

void GlxCommandLine::Parse()
{
	OptionValuePairs.Clear();

	GlxPair<GlxString, GlxString> CurrentPair{};

	for (GlxInt32 Index = 1 /* Ignore exe file path */, ArgCount = (GlxInt32)CmdLineArgs.GetElementCount(); Index < ArgCount; ++Index)
	{
		const GlxString& Arg = CmdLineArgs[Index];
		ParseImpl(Arg, CurrentPair.First, CurrentPair.Second);
		OptionValuePairs.EmplaceBack(CurrentPair);
	}

	Parsed = true;
}

GlxBool GlxCommandLine::HasCommandLineOption(const GlxChar* InOptionName, GlxBool InIgnoreCase)
{
	// exe file path not counted
	GlxInt64 Index = OptionValuePairs.FindIf([&](const GlxPair<GlxString, GlxString>& InElement) -> GlxBool
	{
		return InElement.First.Equals(InOptionName, InIgnoreCase);
	});

	return Index != GlxDynamicArray<GlxPair<GlxString, GlxString>>::InvalidIndex;
}

GlxInt64 GlxCommandLine::GetCommandLineOptionIndex(const GlxChar* InOptionName, GlxBool InIgnoreCase)
{
	// exe file path not counted
	GlxInt64 Index = OptionValuePairs.FindIf([&](const GlxPair<GlxString, GlxString>& InElement) -> GlxBool
	{
		return InElement.First.Equals(InOptionName, InIgnoreCase);
	});

	return Index;
}

void GlxCommandLine::AddCommandLineArg(const GlxChar* InArg)
{
	GlxString Arg{ InArg };

	CmdLineArgs.EmplaceBack(Arg);
	CmdLine.Append(' ', 1);
	CmdLine.Append(Arg);

	if (Parsed)
	{
		GlxString Option;
		GlxString Value;
		ParseImpl(Arg, Option, Value);

		OptionValuePairs.EmplaceBack(Option, Value);
	}
}
