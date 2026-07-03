# lazy

Deferred (lazy) evaluation helpers extracted from
[Xapiand](https://github.com/Kronuz/Xapiand). The point is to build a value that is
only computed **if and when** it is actually used -- e.g. an expensive log-message
argument that should cost nothing when the log level is disabled.

```cpp
#include "lazy.hh"

// eval() forwards a plain value, or invokes an invocable:
eval(42);              // 42
eval([]{ return 42; }); // 42

// LAZY(expr) wraps an arbitrary expression; it runs only when queried, and
// formats through the underlying type`s std::formatter:
log(level, "result = {}", LAZY(expensive_compute()));  // expensive_compute() runs
                                                        // only if this log emits
```

`make_lazy_eval(fn)` / `lazy_eval<L>` give a reusable deferred value with an
`operator()`, an `operator T`, an `ostream <<`, and a `std::formatter`. Header-only.

## Build / test
```sh
cmake -B build && cmake --build build && ctest --test-dir build
```

## Use (FetchContent)
```cmake
FetchContent_Declare(lazy GIT_REPOSITORY https://github.com/Kronuz/lazy.git GIT_TAG main)
FetchContent_MakeAvailable(lazy)
target_link_libraries(your_app PRIVATE lazy::lazy)
```
