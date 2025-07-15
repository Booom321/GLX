#pragma once

#include "GLX/Preprocessor.h"
#include "GLX/Types/Delegate.h"
#include "GLX/String/String.h"
#include "GLX/Containers/List.h"
#include "GLX/Threading/Mutex.h"
#include "GLX/Threading/ScopedLock.h"

#include "LogRecord.h"
#include "LogProperties.h"

#include "GLX/ThirdParty/fmt/core.h"
#include "GLX/ThirdParty/fmt/xchar.h"

#include <chrono>

using GlxLogCallback = void (*)(const GlxLogRecord&);

class GLX_API GlxLog
{
public:
	static GLX_CONSTEXPR const GlxChar* LogLevelToCString[6] = {
		"Debug",
		"Info",
		"Success",
		"Warning",
		"Error",
		"Fatal",
	};

	static GLX_CONSTEXPR const GlxWChar* LogLevelToWString[6] = {
		L"Debug",
		L"Info",
		L"Success",
		L"Warning",
		L"Error",
		L"Fatal",
	};

	template<typename TLogProperties, typename TChar, typename... TArgs>
	static GLX_FORCE_INLINE void Debug(const TLogProperties& InProperties, const TChar* InString, TArgs&&... InArgs)
	{
		LogImpl<TLogProperties, TChar, GlxELogLevel::Debug, TArgs...>(InProperties, InString, Forward<TArgs>(InArgs)...);
	}

	template<typename TLogProperties, typename TChar, typename... TArgs>
	static GLX_FORCE_INLINE void Info(const TLogProperties& InProperties, const TChar* InString, TArgs&&... InArgs)
	{
		LogImpl<TLogProperties, TChar, GlxELogLevel::Info, TArgs...>(InProperties, InString, Forward<TArgs>(InArgs)...);
	}

	template<typename TLogProperties, typename TChar, typename... TArgs>
	static GLX_FORCE_INLINE void Success(const TLogProperties& InProperties, const TChar* InString, TArgs&&... InArgs)
	{
		LogImpl<TLogProperties, TChar, GlxELogLevel::Success, TArgs...>(InProperties, InString, Forward<TArgs>(InArgs)...);
	}

	template<typename TLogProperties, typename TChar, typename... TArgs>
	static GLX_FORCE_INLINE void Warning(const TLogProperties& InProperties, const TChar* InString, TArgs&&... InArgs)
	{
		LogImpl<TLogProperties, TChar, GlxELogLevel::Warning, TArgs...>(InProperties, InString, Forward<TArgs>(InArgs)...);
	}

	template<typename TLogProperties, typename TChar, typename... TArgs>
	static GLX_FORCE_INLINE void Error(const TLogProperties& InProperties, const TChar* InString, TArgs&&... InArgs)
	{
		LogImpl<TLogProperties, TChar, GlxELogLevel::Error, TArgs...>(InProperties, InString, Forward<TArgs>(InArgs)...);
	}

	template<typename TLogProperties, typename TChar, typename... TArgs>
	static GLX_FORCE_INLINE void Fatal(const TLogProperties& InProperties, const TChar* InString, TArgs&&... InArgs)
	{
		LogImpl<TLogProperties, TChar, GlxELogLevel::Fatal, TArgs...>(InProperties, InString, Forward<TArgs>(InArgs)...);
	}

private:
	using LogCallbackList = GlxList<GlxLogCallback>;

	static GlxMutex LogMutex;
	static LogCallbackList LogCallbacks;

	template<typename TLogProperties, typename TChar, GlxELogLevel InLevel, typename... TArgs>
	static void LogImpl(const TLogProperties& InProperties, const TChar* InString, TArgs&&... InArgs)
	{
		// [    0,    1,       2,       3,     4,     5]
		// [Debug, Info, Success, Warning, Error, Fatal]
		static_assert(InLevel >= GlxELogLevel::Debug && InLevel <= GlxELogLevel::Fatal);
		static_assert(GlxOr<GlxIsSame<TChar, GlxChar>, GlxIsSame<TChar, GlxWChar>>::Value);
		static_assert(GlxIsBaseOf<GlxNsPrivate::GlxLogPropertiesBase, TLogProperties>::Value);

		if (InProperties.Level == GlxELogLevel::Off)
		{
			return;
		}

		if (InProperties.Level == GlxELogLevel::All || InProperties.Level <= InLevel)
		{
			fmt::basic_memory_buffer<TChar> Buffer = fmt::basic_memory_buffer<TChar>();
			std::chrono::time_point Now = std::chrono::system_clock::now();

			if constexpr (GlxIsSame<TChar, GlxChar>::Value)
			{
				GlxString FmtString("[{:%Y-%m-%d %H:%M:%S}] [{}] {}: ");
				FmtString += InString;
				FmtString += '\n';
				fmt::detail::vformat_to(
					Buffer,
					fmt::string_view{ FmtString.GetData(), static_cast<GlxSizeT>(FmtString.GetElementCount()) },
					fmt::make_format_args(Now, TLogProperties::Name, LogLevelToCString[static_cast<GlxInt32>(InLevel)], InArgs...));
			}
			else if constexpr (GlxIsSame<TChar, GlxWChar>::Value)
			{
				GlxWString FmtString(L"[{:%Y-%m-%d %H:%M:%S}] [{}] {}: ");
				FmtString += InString;
				FmtString += L'\n';
				fmt::detail::vformat_to(
					Buffer,
					fmt::wstring_view{ FmtString.GetData(), static_cast<GlxSizeT>(FmtString.GetElementCount()) },
					fmt::make_format_args<fmt::wformat_context>(Now, TLogProperties::NameW, LogLevelToWString[static_cast<GlxInt32>(InLevel)], InArgs...));
			}

			Buffer.push_back(static_cast<TChar>(0));

			LogMutex.Lock();

			GlxLogRecord CurrentRecord{};

			for (LogCallbackList::IteratorType Begin = LogCallbacks.begin(), End = LogCallbacks.end(); Begin != End; ++Begin)
			{
				CurrentRecord.Data = Buffer.data();
				CurrentRecord.DataLength = Buffer.size() - 1;
				CurrentRecord.Level = InLevel;

				if constexpr (GlxIsSame<TChar, GlxChar>::Value)
				{
					CurrentRecord.CharType = GlxECharType::Char;
				}
				else if constexpr (GlxIsSame<TChar, GlxWChar>::Value)
				{
					CurrentRecord.CharType = GlxECharType::WChar;
				}

				(*Begin)(CurrentRecord);
			}
			LogMutex.Unlock();
		}

		if constexpr (InLevel == GlxELogLevel::Fatal)
		{
			LogCallbacks.Release();
			std::abort();
		}
	}

	static GLX_FORCE_INLINE LogCallbackList::IteratorType FindLogCallback(GlxLogCallback InCallback)
	{
		LogCallbackList::IteratorType Begin = LogCallbacks.begin();
		LogCallbackList::IteratorType End = LogCallbacks.end();
		for (; Begin != End; ++Begin)
		{
			if (*Begin == InCallback)
			{
				return Begin;
			}
		}

		return End;
	}

public:
	static GlxBool AddLogCallback(GlxLogCallback InCallback);
	static GlxBool RemoveLogCallback(GlxLogCallback InCallback);
	static void ClearAllLogCallbacks();
};

void DefaultConsoleLogCallback(const GlxLogRecord& InRecord);


GlxMutex GlxLog::LogMutex;
GlxLog::LogCallbackList GlxLog::LogCallbacks;

GlxBool GlxLog::AddLogCallback(GlxLogCallback InCallback)
{
	GlxScopedLock<GlxMutex> Lock{ LogMutex };

	if (FindLogCallback(InCallback) != LogCallbacks.end())
	{
		return false;
	}

	LogCallbacks.EmplaceBack(InCallback);
	return true;
}

GlxBool GlxLog::RemoveLogCallback(GlxLogCallback InCallback)
{
	GlxScopedLock<GlxMutex> Lock{ LogMutex };

	LogCallbackList::IteratorType It = FindLogCallback(InCallback);
	if (It == LogCallbacks.end())
	{
		return false;
	}

	LogCallbacks.RemoveAt(It.GetNode());
	return true;
}

void GlxLog::ClearAllLogCallbacks()
{
	LogMutex.Lock();
	LogCallbacks.Clear();
	LogMutex.Unlock();
}

void DefaultConsoleLogCallback(const GlxLogRecord& InRecord)
{
	std::FILE* OutputType = nullptr;

	switch (InRecord.Level)
	{
		case GlxELogLevel::Debug:
		case GlxELogLevel::Info:
		case GlxELogLevel::Success:
			OutputType = stdout;
			break;
		case GlxELogLevel::Warning:
		case GlxELogLevel::Error:
		case GlxELogLevel::Fatal:
			OutputType = stderr;
			break;
	}

	switch (InRecord.CharType)
	{
		case GlxECharType::Char:
			fprintf(OutputType, static_cast<const GlxChar*>(InRecord.Data));
			break;
		case GlxECharType::WChar:
			fwprintf(OutputType, static_cast<const GlxWChar*>(InRecord.Data));
	}
}

#if !defined(GLX_LOG_DEBUG)
	#define GLX_LOG_DEBUG(InProperties, ...) GlxLog::Debug<GLX_MAKE_LOG_PROPERTIES_CLASS_NAME(InProperties)>(GLX_MAKE_LOG_PROPERTIES_OBJECT_NAME(InProperties), __VA_ARGS__)
#endif

#if !defined(GLX_LOG_INFO)
	#define GLX_LOG_INFO(InProperties, ...) GlxLog::Info<GLX_MAKE_LOG_PROPERTIES_CLASS_NAME(InProperties)>(GLX_MAKE_LOG_PROPERTIES_OBJECT_NAME(InProperties), __VA_ARGS__)
#endif

#if !defined(GLX_LOG_SUCCESS)
	#define GLX_LOG_SUCCESS(InProperties, ...) GlxLog::Success<GLX_MAKE_LOG_PROPERTIES_CLASS_NAME(InProperties)>(GLX_MAKE_LOG_PROPERTIES_OBJECT_NAME(InProperties), __VA_ARGS__)
#endif

#if !defined(GLX_LOG_WARNING)
	#define GLX_LOG_WARNING(InProperties, ...) GlxLog::Warning<GLX_MAKE_LOG_PROPERTIES_CLASS_NAME(InProperties)>(GLX_MAKE_LOG_PROPERTIES_OBJECT_NAME(InProperties), __VA_ARGS__)
#endif

#if !defined(GLX_LOG_ERROR)
	#define GLX_LOG_ERROR(InProperties, ...) GlxLog::Error<GLX_MAKE_LOG_PROPERTIES_CLASS_NAME(InProperties)>(GLX_MAKE_LOG_PROPERTIES_OBJECT_NAME(InProperties), __VA_ARGS__)
#endif

#if !defined(GLX_LOG_FATAL)
	#define GLX_LOG_FATAL(InProperties, ...) GlxLog::Fatal<GLX_MAKE_LOG_PROPERTIES_CLASS_NAME(InProperties)>(GLX_MAKE_LOG_PROPERTIES_OBJECT_NAME(InProperties), __VA_ARGS__)
#endif
