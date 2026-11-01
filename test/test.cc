// ctest for lazy: eval() of values vs invocables, lazy_eval deferral, the LAZY
// macro, and the std::format integration.

#include "lazy.hh"

#include <cstdio>
#include <format>
#include <string>
#include <type_traits>

int main() {
	int failures = 0;
	auto check = [&](bool ok, const char* what) {
		if (!ok) { std::fprintf(stderr, "FAIL: %s\n", what); ++failures; }
	};

	// eval() passes a plain value through, and invokes an invocable.
	check(eval(41) == 41, "eval(value)");
	check(eval([] { return 42; }) == 42, "eval(invocable)");

	// lazy_eval defers: the lambda runs only when the value is requested.
	int calls = 0;
	auto lz = make_lazy_eval([&] { ++calls; return 7; });
	check(calls == 0, "lazy_eval does not run eagerly");
	check(lz() == 7, "lazy_eval() runs the lambda");
	check(calls == 1, "lazy_eval ran exactly once when called");

	// The conversion to the result type is explicit: it evaluates under static_cast and never implicitly.
	static_assert(!std::is_convertible_v<decltype(lz), int>, "lazy_eval converts to its result type only explicitly");
	static_assert(std::is_constructible_v<int, decltype(lz)>, "static_cast<result type>(lazy_eval) is available");
	auto converted = make_lazy_eval([&] { ++calls; return 9; });
	int before = calls;
	check(static_cast<int>(converted) == 9, "static_cast<result type>(lazy_eval) evaluates");
	check(calls == before + 1, "the explicit conversion ran the lambda once");

	// std::format sees through lazy_eval to the underlying value's formatter.
	auto s = std::format("{}", make_lazy_eval([] { return 123; }));
	check(s == "123", "format(lazy_eval) formats the evaluated value");

	// The LAZY macro wraps an arbitrary expression; eval() inside handles value-or-callable.
	int side = 0;
	auto deferred = LAZY((side = 5, std::string("hi")));
	check(side == 0, "LAZY(expr) does not evaluate eagerly");
	check(deferred() == "hi", "LAZY(expr)() evaluates the expression");
	check(side == 5, "LAZY(expr) side effect happened on call");

	if (failures == 0) { std::puts("all lazy tests passed"); }
	return failures == 0 ? 0 : 1;
}
