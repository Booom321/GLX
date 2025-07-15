#pragma once

#include "Path.h"
#include "GLX/String/String.h"
#include "GLX/Containers/DynamicArray.h"

#if defined(GLX_PLATFORM_WINDOWS)
	#undef CreateFile
	#undef DeleteFile
	#undef CreateDirectory
	#undef SetCurrentDirectory
	#undef GetCurrentDirectory
#endif

class GLX_API GlxFileSystem
{
public:
	enum class GlxECopyOptions
	{
		None = static_cast<GlxInt32>(std::filesystem::copy_options::none),
		SkipExisting = static_cast<GlxInt32>(std::filesystem::copy_options::skip_existing),
		OverwriteExisting = static_cast<GlxInt32>(std::filesystem::copy_options::overwrite_existing),
		UpdateExisting= static_cast<GlxInt32>(std::filesystem::copy_options::update_existing),
		Recursive = static_cast<GlxInt32>(std::filesystem::copy_options::recursive),
		CopySymlinks = static_cast<GlxInt32>(std::filesystem::copy_options::copy_symlinks),
		SkipSymlinks = static_cast<GlxInt32>(std::filesystem::copy_options::skip_symlinks),
		DirectoriesOnly = static_cast<GlxInt32>(std::filesystem::copy_options::directories_only),
		CreateSymlinks = static_cast<GlxInt32>(std::filesystem::copy_options::create_symlinks),
		CreateHardLinks = static_cast<GlxInt32>(std::filesystem::copy_options::create_hard_links),
	};

	static GlxBool Exists(const GlxPath& InPath);
	static GlxBool Delete(const GlxPath& InPath);
	static GlxBool CreateDirectory(const GlxPath& InPath);
	static GlxBool Rename(const GlxPath& InOld, const GlxPath& InNew);
	static GlxPath GetAbsolutePath(const GlxPath& InPath);
	static GlxPath GetRelativePath(const GlxPath& InPath, const GlxPath& InBase);
	static void Copy(const GlxPath& InFrom, const GlxPath& InTo, GlxECopyOptions InOptions);

	static void SetCurrentDirectory(const GlxPath& InCurrentDir);
	static GlxPath GetCurrentDirectory();

	static GlxUInt64 GetFileSize(const GlxPath& InFile);

	static GlxBool IsDirectory(const GlxPath& InPath);
	static GlxBool Equivalent(const GlxPath& InLhs, const GlxPath& InRhs);

	template<typename TFunc>
	static void IterateFilesInDirectory(const GlxPath& InDir, TFunc InFunc)
	{
		for (const auto& Entry : std::filesystem::directory_iterator{ InDir })
		{
			GlxPath Path = Entry.path();
			InFunc(Path);
		}
	}

	static GlxString GetExtension(const GlxString& InPath);
	static GlxString GetFileName(const GlxString& InPath);
	static GlxString GetFileNameWithoutExtension(const GlxString& InPath);
	static GlxBool IsPathSeparator(GlxChar InChar);
};

GLX_DEFINE_ENUM_CLASS_BITWISE_OPERATORS(GlxFileSystem::GlxECopyOptions);

GlxBool GlxFileSystem::Exists(const GlxPath& InPath)
{
	return std::filesystem::exists(InPath);
}

GlxBool GlxFileSystem::Rename(const GlxPath& InOld, const GlxPath& InNew)
{
	if (!std::filesystem::exists(InOld) && std::filesystem::exists(InNew))
	{
		return false;
	}
	std::filesystem::rename(InOld, InNew);
	return true;
}

GlxBool GlxFileSystem::Delete(const GlxPath& InPath)
{
	if (std::filesystem::is_directory(InPath))
	{
		return std::filesystem::remove_all(InPath) != static_cast<std::uintmax_t>(-1);
	}
	else
	{
		return std::filesystem::remove(InPath);
	}
}

GlxBool GlxFileSystem::CreateDirectory(const GlxPath& InPath)
{
	return std::filesystem::create_directory(InPath);
}

void GlxFileSystem::Copy(const GlxPath& InFrom, const GlxPath& InTo, GlxECopyOptions InOptions)
{
	std::filesystem::copy(InFrom, InTo, static_cast<std::filesystem::copy_options>(InOptions));
}

void GlxFileSystem::SetCurrentDirectory(const GlxPath& InCurrentDir)
{
	std::filesystem::current_path(InCurrentDir);
}

GlxPath GlxFileSystem::GetCurrentDirectory()
{
	return std::filesystem::current_path();
}

GlxBool GlxFileSystem::IsDirectory(const GlxPath& InPath)
{
	return std::filesystem::is_directory(InPath);
}

GlxUInt64 GlxFileSystem::GetFileSize(const GlxPath& InFile)
{
	return std::filesystem::file_size(InFile);
}

GlxBool GlxFileSystem::Equivalent(const GlxPath& InLhs, const GlxPath& InRhs)
{
	return std::filesystem::equivalent(InLhs, InRhs);
}

GlxPath GlxFileSystem::GetAbsolutePath(const GlxPath& InPath)
{
	return std::filesystem::absolute(InPath);
}

GlxPath GlxFileSystem::GetRelativePath(const GlxPath& InPath, const GlxPath& InBase)
{
	return std::filesystem::relative(InPath, InBase);
}

GlxString GlxFileSystem::GetExtension(const GlxString& InPath)
{
	if (InPath.IsEmpty())
	{
		return "";
	}

	const GlxChar* Start = InPath.GetData();
	const GlxChar* End = Start + InPath.GetElementCount();
	const GlxChar* TmpEnd = End;

	while (End >= Start)
	{
		if (*End == '/' || *End == '\\')
		{
			return "";
		}

		if (*End == '.')
		{
			return GlxString(End, static_cast<typename GlxString::SizeType>(TmpEnd - End) + 1);
		}

		--End;
	}

	return "";
}

GlxString GlxFileSystem::GetFileName(const GlxString& InPath)
{
	if (InPath.IsEmpty())
	{
		return "";
	}

	typename GlxString::SizeType Count = InPath.GetElementCount();
	const GlxChar* Start = InPath.GetData();
	const GlxChar* End = Start + Count;
	const GlxChar* TmpEnd = End;

	while (End >= Start)
	{
		if (*End == '/' || *End == '\\')
		{
			++End;
			return GlxString(End, static_cast<typename GlxString::SizeType>(TmpEnd - End) + 1);
		}
		--End;
	}

	return Count > 0 ? InPath : "";
}

GlxString GlxFileSystem::GetFileNameWithoutExtension(const GlxString& InPath)
{
	if (InPath.IsEmpty())
	{
		return "";
	}

	const GlxChar* Start = InPath.GetData();
	const GlxChar* End = Start + InPath.GetElementCount();
	const GlxChar* TmpEnd = End;
	const GlxChar* DotPos = nullptr;

	while (End >= Start)
	{
		if (!DotPos && *End == '.')
		{
			DotPos = End;
		}

		if (*End == '/' || *End == '\\')
		{
			++End;
			break;
		}
		--End;
	}

	if ((End + 1) == Start)
	{
		if (DotPos)
		{
			return GlxString(DotPos + 1, static_cast<typename GlxString::SizeType>(TmpEnd - DotPos));
		}
		else
		{
			return InPath;
		}
	}

	return GlxString(End, static_cast<typename GlxString::SizeType>((DotPos ? DotPos : TmpEnd) - End));
}

GlxBool GlxFileSystem::IsPathSeparator(GlxChar InChar)
{
	return InChar == '/' || InChar == '\\';
}
