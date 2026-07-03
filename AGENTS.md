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
