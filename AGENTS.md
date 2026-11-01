# AGENTS

Deferred-evaluation helpers extracted verbatim from Xapiand: `eval` (value-or-
invocable), `lazy_eval<L>` / `make_lazy_eval`, the `LAZY(expr)` macro, and a
`std::formatter` + `ostream<<` that evaluate on demand.

- Header-only; needs `<format>` (C++20) and `<type_traits>`/`<utility>`/`<ostream>`.
- `eval()` overloads on `std::is_invocable`: an invocable is called, anything else is
  forwarded. Keep that dispatch intact -- `LAZY` and `lazy_eval` depend on it.
- `LAZY(expr)` captures by reference (`[&]`); it is for use-now-or-very-soon deferral
  (logging), not for storing past the referents` lifetime.
- `test/test.cc` covers eager-vs-deferred timing, run-once, `std::format`, and side effects.

## Verification and benchmarks

CI (`.github/workflows/ci.yml`) calls the catalog's shared
[`cmake.yml`](https://github.com/Kronuz/cpp-libraries/blob/main/.github/workflows/cmake.yml) on every push and nightly:
CTest on Linux (x86-64 GCC and Clang, arm64), macOS (arm64, x86-64) and FreeBSD, then again under
ASan+UBSan and TSan. The shared method is the catalog's
[PERFORMANCE.md](https://github.com/Kronuz/cpp-libraries/blob/main/docs/PERFORMANCE.md).

```sh
cmake -S . -B build && cmake --build build && ctest --test-dir build --output-on-failure
# ASan+UBSan as CI's linux-asan-ubsan job runs it (Linux, Clang)
CC=clang CXX=clang++ cmake -S . -B build-asan -DCMAKE_BUILD_TYPE=Debug \
  "-DCMAKE_CXX_FLAGS=-fsanitize=address,undefined -fno-sanitize-recover=undefined -fno-omit-frame-pointer -D_GLIBCXX_ASSERTIONS" \
  "-DCMAKE_EXE_LINKER_FLAGS=-fsanitize=address,undefined"
cmake --build build-asan && ASAN_OPTIONS=detect_leaks=1 ctest --test-dir build-asan --output-on-failure
```

`lazy_test` counts the calls of the deferred expression: none before the value is read, one per
read, `std::format` reading through `lazy_eval`, and `LAZY(expr)` running its side effect only on
the call. Two `static_assert`s pin that `lazy_eval` converts to its result type only
explicitly. Its checks print `FAIL` and set the exit status, so they hold in Release, the
default build type. There is no bench, fuzz target or mutation script: the library makes no
performance claim.
