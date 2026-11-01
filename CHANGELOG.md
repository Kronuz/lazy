# Changelog

Notable changes to `lazy`, newest first. The format follows
[Keep a Changelog](https://keepachangelog.com/en/1.1.0/); the library has no releases, so
entries are dated.

## 2026-11-01

### Fixed

- `ARCHITECTURE.md` described `operator T` as an implicit conversion. It is `explicit`
  (`lazy.hh`), so a `lazy_eval` is read with `static_cast<T>(lz)`, `lz()`, `operator<<` or
  `std::format`, and never converts by itself. The document now says so, and `test/test.cc`
  asserts that `lazy_eval` is not implicitly convertible to its result type and that the
  explicit conversion evaluates once.

### Changed

- The README follows the family README standard: the description as its first sentence,
  Quick start before Installation (a complete program that counts the calls), a pinned
  FetchContent tag, and "Not for" limits. It names CMake 3.16, the version
  `CMakeLists.txt` requires, where it said 3.14, and states that the conversion to the
  result type is explicit.
