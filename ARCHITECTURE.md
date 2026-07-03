# Architecture

Deferred evaluation in one header. The goal: build a value that is computed only *if and
when* it is used — the classic case being an expensive log-message argument that should
cost nothing when the log level is off.

## The pieces

- **`eval(x)`** — two overloads selected by `std::is_invocable`: an invocable is called,
  anything else is forwarded. This is the primitive the rest build on.
- **`lazy_eval<L>` / `make_lazy_eval(fn)`** — a move-only wrapper around a callable that
  runs it on demand, with `operator()`, an `operator T` (implicit evaluation), an
  `ostream <<`, and a `std::formatter` specialization that formats the *evaluated* value
  through the underlying type's formatter.
- **`LAZY(expr)`** — a macro that wraps an arbitrary expression as
  `make_lazy_eval([&]{ return eval(expr); })`, so `expr` runs only when the lazy value
  is queried.

## Lifetime note

`LAZY(expr)` captures by reference (`[&]`). It is meant for use-now-or-very-soon
deferral (a logging call on the same statement), not for storing a lazy value past the
lifetime of what `expr` refers to.

## Dependencies

**None.** Standard library only, including `<format>` (C++20) for the formatter.

## Invariants

- `eval`'s invocable-vs-value dispatch (via `std::is_invocable`) is load-bearing; `LAZY`
  and `lazy_eval` build on it. Keep it.
- `lazy_eval` is move-only. Verbatim from Xapiand.
