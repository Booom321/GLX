#pragma once

#include "GLX/Utils/Locale.h"
#include "GLX/Utils/NonCopyable.h"
#include "GLX/Containers/DynamicArray.h"
#include "GLX/TypeTraits/TypeRelationships.h"

#include "Path.h"

#include <fstream>

enum class GlxESeekDir : GlxInt8
{
	Begin = 0,
	Current = 1,
	End = 2,
};

enum class GlxEOpenMode
{
	Append = static_cast<GlxInt32>(std::ios_base::app),
	Binary = static_cast<GlxInt32>(std::ios_base::binary),
	Read = static_cast<GlxInt32>(std::ios_base::in),
	Write = static_cast<GlxInt32>(std::ios_base::out),
	Truncate = static_cast<GlxInt32>(std::ios_base::trunc),
	Ate = static_cast<GlxInt32>(std::ios_base::ate),
};

GLX_DEFINE_ENUM_CLASS_BITWISE_OPERATORS(GlxEOpenMode);

template<typename TStream>
class GLX_API GlxBasicFileIO : public GlxNonCopyable
{
public:
	using StreamType = TStream;
	using PosType = typename TStream::pos_type;
	using OffType = typename TStream::off_type;
	using OpenModeType = GlxEOpenMode;

	GlxBasicFileIO() = default;
	GlxBasicFileIO(GlxBasicFileIO&&) noexcept = default;
	GlxBasicFileIO& operator=(GlxBasicFileIO&&) noexcept = default;

	GLX_FORCE_INLINE GlxBasicFileIO(const GlxChar* InFileName, GlxEOpenMode InMode)
		: Stream(InFileName, static_cast<std::ios_base::openmode>(InMode))
	{}

	GLX_FORCE_INLINE GlxBasicFileIO(const GlxPath& InPath, GlxEOpenMode InMode)
		: Stream(InPath, static_cast<std::ios_base::openmode>(InMode))
	{}

	~GlxBasicFileIO() = default;

	GLX_FORCE_INLINE void Open(const GlxChar* InFileName, GlxEOpenMode InMode)
	{
		Stream.open(InFileName, static_cast<std::ios_base::openmode>(InMode));
	}

	GLX_FORCE_INLINE void Open(const GlxPath& InPath, GlxEOpenMode InMode)
	{
		Stream.open(InPath, static_cast<std::ios_base::openmode>(InMode));
	}

	GLX_FORCE_INLINE void Close() { Stream.close(); }
	GLX_FORCE_INLINE GlxBool IsOpen() const { return Stream.is_open(); }
	GLX_FORCE_INLINE explicit operator bool() const { return Stream.operator bool(); }
	GLX_FORCE_INLINE bool operator!() const { return !Stream.operator bool(); }
	GLX_FORCE_INLINE GlxLocale Imbue(const GlxLocale& InLocale) { return Stream.imbue(InLocale); }

protected:
	StreamType Stream;
};

class GLX_API GlxFileReader : public GlxBasicFileIO<std::ifstream>
{
public:
	using Super = GlxBasicFileIO<std::ifstream>;

	GlxFileReader() = default;

	GLX_FORCE_INLINE GlxFileReader(GlxFileReader&& InOther) noexcept
	{
		this->Stream = Move(InOther.Stream);
	}

	GLX_FORCE_INLINE GlxFileReader& operator=(GlxFileReader&& InOther) noexcept
	{
		if (this != &InOther)
		{
			this->Stream = Move(InOther.Stream);
		}
		return *this;
	}

	GLX_FORCE_INLINE GlxFileReader(const GlxChar* InFileName, GlxEOpenMode InMode) : Super(InFileName, InMode) {}
	GLX_FORCE_INLINE GlxFileReader(const GlxPath& InPath, GlxEOpenMode InMode) : Super(InPath, InMode) {}

	~GlxFileReader() = default;

	GLX_FORCE_INLINE PosType Tell() { return this->Stream.tellg(); }
	GLX_FORCE_INLINE void Seek(PosType InPos) { this->Stream.seekg(InPos); }
	GLX_FORCE_INLINE void Seek(OffType InOffset, GlxESeekDir InDir) { this->Stream.seekg(InOffset, static_cast<std::ios_base::seekdir>(InDir)); }

	PosType GetFileSize();
	GlxBool Read(void* InBuffer, GlxInt64 InSize);
};

class GLX_API GlxFileWriter : public GlxBasicFileIO<std::ofstream>
{
public:
	using Super = GlxBasicFileIO<std::ofstream>;

	GlxFileWriter() = default;

	GLX_FORCE_INLINE GlxFileWriter(GlxFileWriter&& InOther) noexcept
	{
		this->Stream = Move(InOther.Stream);
	}

	GLX_FORCE_INLINE GlxFileWriter& operator=(GlxFileWriter&& InOther) noexcept
	{
		if (this != &InOther)
		{
			this->Stream = Move(InOther.Stream);
		}
		return *this;
	}

	GLX_FORCE_INLINE GlxFileWriter(const GlxChar* InFileName, GlxEOpenMode InMode) : Super(InFileName, InMode) {}
	GLX_FORCE_INLINE GlxFileWriter(const GlxPath& InPath, GlxEOpenMode InMode) : Super(InPath, InMode) {}

	~GlxFileWriter() = default;

	GLX_FORCE_INLINE PosType Tell() { return this->Stream.tellp(); }
	GLX_FORCE_INLINE void Seek(PosType InPos) { this->Stream.seekp(InPos); }
	GLX_FORCE_INLINE void Seek(OffType InOffset, GlxESeekDir InDir) { this->Stream.seekp(InOffset, static_cast<std::ios_base::seekdir>(InDir)); }

	PosType GetFileSize();
	GlxBool Write(const void* InBuffer, GlxInt64 InSize);
};

GlxFileReader::PosType GlxFileReader::GetFileSize()
{
	PosType CurrentPos = this->Stream.tellg();

	this->Stream.seekg(0, std::ios_base::end);
	PosType FileSize = this->Stream.tellg();
	this->Stream.seekg(CurrentPos, std::ios_base::beg);
	return FileSize;
}

GlxBool GlxFileReader::Read(void* InBuffer, GlxInt64 InSize)
{
	if (!InBuffer)
	{
		return false;
	}

	if (InSize < 0)
	{
		InSize = GetFileSize().operator std::streamoff();
	}

	if (this->Stream.is_open())
	{
		this->Stream.read((char*)InBuffer, InSize);
		return true;
	}
	return false;
}

GlxFileWriter::PosType GlxFileWriter::GetFileSize()
{
	PosType CurrentPos = this->Stream.tellp();

	this->Stream.seekp(0, std::ios_base::end);
	PosType FileSize = this->Stream.tellp();
	this->Stream.seekp(CurrentPos, std::ios_base::beg);
	return FileSize;
}

GlxBool GlxFileWriter::Write(const void* InBuffer, GlxInt64 InSize)
{
	if (!InBuffer || InSize < 0)
	{
		return false;
	}

	if (this->Stream.is_open())
	{
		this->Stream.write((const char*)InBuffer, InSize);
		return true;
	}
	return false;
}
