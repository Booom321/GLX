#pragma once

#include "LogLevel.h"

#include "GLX/Preprocessor.h"
#include "GLX/Types/DataTypes.h"

class GlxLog;

namespace GlxNsPrivate
{
	class GlxLogPropertiesBase
	{
	public:
		GLX_FORCE_INLINE GlxLogPropertiesBase(GlxELogLevel InLevel)
			: Level(InLevel)
		{}

		GlxLogPropertiesBase() = default;
		GlxLogPropertiesBase(const GlxLogPropertiesBase&) = default;
		GlxLogPropertiesBase& operator=(const GlxLogPropertiesBase&) = default;
		GlxLogPropertiesBase(GlxLogPropertiesBase&&) noexcept = default;
		GlxLogPropertiesBase& operator=(GlxLogPropertiesBase&&) noexcept = default;
		~GlxLogPropertiesBase() = default;

		GLX_FORCE_INLINE GlxELogLevel GetLogLevel() const
		{
			return Level;
		}

		GLX_FORCE_INLINE void SetLogLevel(GlxELogLevel InLevel)
		{
			Level = InLevel;
		}

		GlxELogLevel Level;
	};
}

#if !defined(GLX_MAKE_LOG_CHANNEL_CLASS_NAME)
	#define GLX_MAKE_LOG_PROPERTIES_CLASS_NAME(InName) GlxLogProperties##InName
#endif

//// LP = LogProperties
#if !defined(GLX_MAKE_LOG_PROPERTIES_OBJECT_NAME)
	#define GLX_MAKE_LOG_PROPERTIES_OBJECT_NAME(InName) LP##InName
#endif

#if !defined(GLX_DEFINE_LOG_PROPERTIES)
	#define GLX_DEFINE_LOG_PROPERTIES(InName, InLevel)                                                  \
		class GLX_MAKE_LOG_PROPERTIES_CLASS_NAME(InName) : public GlxNsPrivate::GlxLogPropertiesBase    \
		{                                                                                               \
		public:                                                                                         \
			static GLX_CONSTEXPR const GlxChar* Name = GLX_STRINGIFY(InName);                           \
			static GLX_CONSTEXPR const GlxWChar* NameW = GLX_STRINGIFY_W(InName);                       \
			GLX_MAKE_LOG_PROPERTIES_CLASS_NAME(InName)() : GlxNsPrivate::GlxLogPropertiesBase(InLevel)  \
			{}                                                                                          \
		};                                                                                              \
		static GLX_MAKE_LOG_PROPERTIES_CLASS_NAME(InName) GLX_MAKE_LOG_PROPERTIES_OBJECT_NAME(InName) {}
#endif

#if !defined(GLX_GET_LOG_LEVEL)
	#define GLX_GET_LOG_LEVEL(InName) GLX_MAKE_LOG_PROPERTIES_OBJECT_NAME(InName).GetLogLevel();
#endif

#if !defined(GLX_SET_LOG_LEVEL)
	#define GLX_SET_LOG_LEVEL(InName, InLevel) GLX_MAKE_LOG_PROPERTIES_OBJECT_NAME(InName).SetLogLevel(InLevel);
#endif

GLX_DEFINE_LOG_PROPERTIES(Default, GlxELogLevel::All);
