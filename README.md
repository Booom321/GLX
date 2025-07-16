# GLX

GLX is a C++ utility library inspired by [Galaxy](https://github.com/Booom321/Galaxy) Core. It provides several containers, math utilities, threading, string, and more. GLX is designed to be modular, header-only, and easy to integrate into your C++ projects for tool or software development. =)))

---

| Platform | Supported |
| -------- | --------- |
| Windows  | Yes       |
| macOS    | No        |
| Linux    | No        |

## Installation

GLX is a header-only library. To use it in your project:

1. **Clone or Download** this repository.
2. **Include** the relevant headers from the `include/GLX/` directory in your project.
3. Add `include/` to your compiler's include path.

## Usage Examples

```cpp
#include <GLX/GLX.h>

int main() {
    Print("Hello world");
    return 0;
}
```

```cpp
#include <GLX/GLX.h>

GLX_DEFINE_LOG_PROPERTIES(Foo, GlxELogLevel::All);

int main(int argc, char** argv)
{
	GlxLog::AddLogCallback(DefaultConsoleLogCallback);

	GLX_LOG_DEBUG(Foo, "Debug");
	GLX_LOG_INFO(Foo, "Info");
	GLX_LOG_SUCCESS(Foo, "Success");
	GLX_LOG_WARNING(Foo, "Warning");
	GLX_LOG_ERROR(Foo, "Error");

	GLX_LOG_INFO(Foo, "{} {}", "hello", "world");

	GlxLog::ClearAllLogCallbacks();

	return 0;
}
```

```cpp
#include <GLX/GLX.h>

int main() {
    GlxDynamicArray<int> Arr;
    Arr.EmplaceBack(42);

    GlxString Str{ "This is a string" };
    Str = "This is another string";

    GlxNsMath::GlxVector3f V{ 1.0f, 2.0f, 3.0f };
    return 0;
}
```

## Contributing 🤝

Contributions are welcome! To contribute:

1. Fork this repository.
2. Create a new branch for your feature or bugfix.
3. Submit a pull request with a description of your changes.

> Do not intentionally damage, obfuscate, or remove meaningful parts of the original code.

## License

Feel free to use it for any purpose 👍.

Please do not:

- Misrepresent the source
- Use the code in harmful, malicious, or unethical ways
- Remove or obscure any original attribution or documentation (if included)

## Credits

- [fmt](https://github.com/fmtlib/fmt) for formatting utilities
- [xxHash](https://github.com/Cyan4973/xxHash) for fast hashing

---
