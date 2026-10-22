# lazy

Part of [Kronuz C++ Libraries](https://github.com/Kronuz/cpp-libraries), a collection of small, reusable C++ libraries.

[![CI](https://github.com/Kronuz/lazy/actions/workflows/ci.yml/badge.svg)](https://github.com/Kronuz/lazy/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)
![Header-only](https://img.shields.io/badge/header--only-yes-green.svg)

Deferred evaluation for C++20: `LAZY(expensive())` makes a value that is computed
only if and when it is used, and that formats through `std::format`. For log
arguments that should cost nothing when the line is filtered out.

## ✨ Highlights

- **`LAZY(expr)`** wraps any expression without evaluating it.
- **Formats like the value**: a `std::formatter`, `operator<<`, and a conversion
  to the result type.
- **`eval(x)`** passes a value through, or calls an invocable.
- **One header, no dependencies.**

## 📦 Installation

Requires a C++20 compiler; CMake 3.14 or newer for the CMake route. CI builds it
on Linux (x86_64, arm64), macOS (arm64, x86_64), and FreeBSD, plus ASan, UBSan,
and TSan builds.

```cmake
include(FetchContent)
FetchContent_Declare(lazy
  GIT_REPOSITORY https://github.com/Kronuz/lazy.git
  GIT_TAG        main)
FetchContent_MakeAvailable(lazy)

target_link_libraries(my_app PRIVATE lazy::lazy)
```

## 🚀 Quick start

```cpp
#include "lazy.hh"

#include <format>
#include <string>

std::string expensive() { return "computed"; }

int main(int argc, char**) {
	bool verbose = argc > 1;
	auto value = LAZY(expensive());              // nothing runs yet
	if (verbose) {
		std::string line = std::format("result = {}", value);   // runs here
	}
}
```

`LAZY` captures by reference, so use the value within the scope that made it.

## 🎯 When to use it

- ✅ Arguments to log calls or debug output that may never be formatted.
- ❌ Caching: a lazy value recomputes each time it is read.

## 📚 Documentation

- [ARCHITECTURE.md](ARCHITECTURE.md): `eval`, `lazy_eval`, and the formatter.
- [AGENTS.md](AGENTS.md): repository map and traps.

## 🛠️ Building and testing

```sh
cmake -B build && cmake --build build && ctest --test-dir build
```

## 🤝 Contributing

Issues and pull requests are welcome. Read [AGENTS.md](AGENTS.md) first. CI must
pass on every platform.

## 📄 License

MIT, Copyright (c) 2015-2019 Dubalu LLC. See [LICENSE](LICENSE). Extracted from
[Xapiand](https://github.com/Kronuz/Xapiand), where the logger uses it.
