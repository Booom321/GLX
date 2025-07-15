#pragma once

class GlxNonMovable
{
protected:
	GlxNonMovable() = default;
	~GlxNonMovable() = default;

	GlxNonMovable(GlxNonMovable&&) noexcept = delete;
	GlxNonMovable& operator=(GlxNonMovable&&) noexcept = delete;
};
