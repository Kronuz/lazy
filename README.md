# lazy

Part of [Kronuz C++ Libraries](https://github.com/Kronuz/cpp-libraries), a collection of small, reusable C++ libraries.

[![CI](https://github.com/Kronuz/lazy/actions/workflows/ci.yml/badge.svg)](https://github.com/Kronuz/lazy/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)
![Header-only](https://img.shields.io/badge/header--only-yes-green.svg)

Header-only deferred evaluation for C++20: LAZY(expr) computes a value only when it is formatted or read.
`LAZY` wraps the expression in a lambda inside a move-only `lazy_eval`, and `std::format`,
`operator<<` or a call runs it. Reach for it for log arguments that should cost nothing when
the line is filtered out.

## ✨ Highlights

- **`LAZY(expr)`.** Wraps any expression without evaluating it.
- **Formats like the value.** A `std::formatter` specialization formats the result with the
  result type's own formatter; `operator<<` and an explicit conversion work too.
- **`eval(x)`.** Passes a value through, or calls an invocable and returns its result.
- **One header, no dependencies.** The standard library, including `<format>`.

## 🚀 Quick start

```cpp
#include "lazy.hh"

#include <format>
#include <iostream>
#include <string>

int calls = 0;
std::string expensive() { ++calls; return "computed"; }

int main(int argc, char**) {
	auto value = LAZY(expensive());                    // nothing runs yet
	if (argc > 1) {                                    // a filtered-out log line
		std::cout << std::format("result = {}\n", value);
	}
	std::cout << calls << '\n';                        // 0
	std::cout << std::format("result = {}\n", value);  // result = computed
	std::cout << calls << '\n';                        // 1
}
```

## 📦 Installation

Requires a C++20 compiler; CMake 3.16 or newer for the CMake route. CI builds it on Linux
(x86_64, arm64), macOS (arm64, x86_64), and FreeBSD, plus ASan, UBSan, and TSan builds.

```cmake
include(FetchContent)
FetchContent_Declare(lazy
  GIT_REPOSITORY https://github.com/Kronuz/lazy.git
  GIT_TAG        78a82815418c8f66f199a18e79f205c21725459e)  # or main, to track the tip
FetchContent_MakeAvailable(lazy)

target_link_libraries(my_app PRIVATE lazy::lazy)
```

```cpp
#include "lazy.hh"
```

## 🎯 When to use it

Use it for arguments to log calls or debug output that may never be formatted.

Not for:

- **Caching.** A lazy value recomputes each time it is read.
- **Storing for later.** `LAZY` captures by reference, so use the value within the scope
  that made it.
- **Use as a plain value.** `lazy_eval` converts to its result type only explicitly; pass it
  to `std::format`, `operator<<`, or call it.

## 📚 Documentation

- [ARCHITECTURE.md](ARCHITECTURE.md): `eval`, `lazy_eval` and the formatter.
- [CHANGELOG.md](CHANGELOG.md): dated changes.
- [AGENTS.md](AGENTS.md): repository map and traps.
- [Kronuz C++ Libraries](https://github.com/Kronuz/cpp-libraries): the catalog.

## 🛠️ Building and testing

```sh
cmake -B build
cmake --build build
ctest --test-dir build
```

## 🤝 Contributing

Read [AGENTS.md](AGENTS.md) and the [catalog's rules](https://github.com/Kronuz/cpp-libraries/blob/main/AGENTS.md)
first.

## 📄 License

MIT, Copyright (c) 2026 Germán Méndez Bravo and (c) 2015-2020 Dubalu LLC. See
[LICENSE](LICENSE). Extracted from [Xapiand](https://github.com/Kronuz/Xapiand), where the
logger uses it.
