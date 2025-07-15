#pragma once

#if defined(GLX_PLATFORM_WINDOWS)

#include <functional>

static DWORD WINAPI RunThread(LPVOID InData)
{
	GlxThread::ProcType* ProcPtr = static_cast<GlxThread::ProcType*>(InData);
	ProcPtr->operator()();
	delete ProcPtr;
	ProcPtr = nullptr;
	return 0;
}

template<typename TFunc, typename... TArgs>
GlxThread::GlxThread(TFunc&& InF, TArgs&&... InArgs)
{
	GlxThread::ProcType* ProcPtr = new GlxThread::ProcType(std::bind(Forward<TFunc>(InF), Forward<TArgs>(InArgs)...));

	Data.ThreadHandle = CreateThread(nullptr, 0, RunThread, ProcPtr, 0, &Data.ThreadID);
	GLX_ASSERT(Data.ThreadHandle);
}

GlxThread::GlxThread(GlxThread&& InOther) noexcept
	: Data(Move(InOther.Data))
{
	InOther.Data.ThreadHandle = nullptr;
	InOther.Data.ThreadID = 0;
}

GlxThread& GlxThread::operator=(GlxThread&& InOther) noexcept
{
	GLX_ASSERT(InOther.Data.ThreadID == 0);

	Data = Move(InOther.Data);
	InOther.Data.ThreadID = 0;
	InOther.Data.ThreadHandle = nullptr;

	return *this;
}

GlxThread::~GlxThread()
{
	GLX_ASSERT(Data.ThreadID == 0 && Data.ThreadHandle == nullptr);
}

GlxBool GlxThread::Joinable() const
{
	return Data.ThreadID != 0;
}

GlxBool GlxThread::Join()
{
	GLX_ASSERT(Data.ThreadID != GetCurrentThreadId(), "Resource deadlock would occur!");

	if (WaitForSingleObjectEx(Data.ThreadHandle, INFINITE, FALSE) == WAIT_FAILED)
	{
		return false;
	}

	GlxBool Ok = CloseHandle(Data.ThreadHandle) != 0;
	Data.ThreadID = 0;
	Data.ThreadHandle = nullptr;

	return Ok;
}

GlxBool GlxThread::Detach()
{
	GlxBool Ok = CloseHandle(Data.ThreadHandle) != 0;
	Data.ThreadID = 0;
	Data.ThreadHandle = nullptr;

	return Ok;
}

void GlxThreadUtils::YieldThisThread()
{
	SwitchToThread();
}

GlxInt32 GlxThreadUtils::GetNumberOfThreads()
{
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	return SystemInfo.dwNumberOfProcessors;
}

GlxThreadID GlxThreadUtils::GetCurrentThreadID()
{
	return GetCurrentThreadId();
}

void GlxThreadUtils::SleepFor(GlxInt64 InMilliseconds)
{
	Sleep(static_cast<DWORD>(InMilliseconds));
}

#endif
