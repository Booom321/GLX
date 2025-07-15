#pragma once

class GlxNonCopyable
{
protected:
	GlxNonCopyable() = default;
	~GlxNonCopyable() = default;

	GlxNonCopyable(const GlxNonCopyable&) = delete;
	GlxNonCopyable& operator=(const GlxNonCopyable&) = delete;
};
