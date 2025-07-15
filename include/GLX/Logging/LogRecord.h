#pragma once

#include "LogLevel.h"

#include "GLX/Preprocessor.h"
#include "GLX/Types/DataTypes.h"

enum class GlxECharType : GlxInt8
{
	Char,
	WChar,
};

class GlxLogRecord
{
public:
	GlxLogRecord() = default;
	GlxLogRecord(const GlxLogRecord&) = default;
	GlxLogRecord& operator=(const GlxLogRecord&) = default;
	GlxLogRecord(GlxLogRecord&&) noexcept = default;
	GlxLogRecord& operator=(GlxLogRecord&&) noexcept = default;
	~GlxLogRecord() = default;

	void* Data;
	GlxSizeT DataLength;
	GlxELogLevel Level;
	GlxECharType CharType;
};
