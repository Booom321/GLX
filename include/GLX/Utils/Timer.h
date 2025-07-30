#pragma once

#include "GLX/Preprocessor.h"

#include <chrono>

class GlxTimer
{
public:
	using ClockType = std::chrono::high_resolution_clock;
	using TimePoint = std::chrono::time_point<ClockType>;

	template<typename T>
	using NsDuration = std::chrono::duration<T, std::nano>;
	template<typename T>
	using UsDuration = std::chrono::duration<T, std::micro>;
	template<typename T>
	using MsDuration = std::chrono::duration<T, std::milli>;
	template<typename T>
	using SDuration = std::chrono::duration<T, std::ratio<1, 1>>;

	GlxTimer() = default;
	~GlxTimer() = default;

	GLX_NODISCARD static GLX_INLINE TimePoint Now()
	{
		return ClockType::now();
	}

	void Reset()
	{
		Start = ClockType::now();
	}

	template<typename T = GlxDouble>
	GLX_INLINE T GetElapsedNs() const
	{
		return NsDuration<T>{ ClockType::now() - Start }.count();
	}

	template<typename T = GlxDouble>
	GLX_INLINE T GetElapsedUs() const
	{
		return UsDuration<T>{ ClockType::now() - Start }.count();
	}

	template<typename T = GlxDouble>
	GLX_INLINE T GetElapsedMs() const
	{
		return MsDuration<T>{ ClockType::now() - Start }.count();
	}

	template<typename T = GlxDouble>
	GLX_INLINE T GetElapsedS() const
	{
		return SDuration<T>{ ClockType::now() - Start }.count();
	}

private:
	TimePoint Start{ Now() };
};
