#pragma once

#include "GLX/Preprocessor.h"
#include "GLX/Types/DataTypes.h"

class GlxVersion
{
public:
	GlxUInt32 Major; // Breaking API change
	GlxUInt32 Minor; // New feature
	GlxUInt32 Patch; // Bug fix

	GLX_CONSTEXPR GlxVersion() = default;
	GLX_CONSTEXPR GlxVersion(const GlxVersion&) = default;
	GLX_CONSTEXPR GlxVersion(GlxVersion&&) noexcept = default;
	GlxVersion& operator=(const GlxVersion&) = default;
	GlxVersion& operator=(GlxVersion&&) noexcept = default;

	GLX_CONSTEXPR GLX_FORCE_INLINE GlxVersion(GlxUInt32 InMajor, GlxUInt32 InMinor, GlxUInt32 InPatch)
		: Major(InMajor), Minor(InMinor), Patch(InPatch)
	{}

	~GlxVersion() = default;
};
