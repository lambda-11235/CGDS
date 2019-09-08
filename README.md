
# C Generic Data Structures (CGDS)

This is yet another attempt at implementing generics in C. The main focus of
this library is on building reusable core data structures, such as AVL trees,
hash tables, etc, and not on ADTs, such as maps, sets, etc. The hope is that the
data structures will have a generic enough implementation that using them as the
building blocks of higher level ADTs will be relatively trivial.

## Usage

Let's say we want to use a generic data structure `foo` for several types `boo`,
`baz*`, etc. The first step is to define a header `foo_my_types.h` which
contains something like
```c
#ifndef FOO_MY_TYPES
#define FOO_MY_TYPES

#define TYPE boo
#define TYPE_ABBREV boo
#include "CGDS/foo_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE baz*
#define TYPE_ABBREV bazp
#include "CGDS/foo_generic.h"
#undef TYPE_ABBREV
#undef TYPE

// ...

#endif  // FOO_MY_TYPES
```

Then in `foo_my_types.c` we do
```c
#include "foo_my_types.h"

#define TYPE boo
#define TYPE_ABBREV boo
#include "CGDS/foo_generic_impl.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE baz*
#define TYPE_ABBREV bazp
#include "CGDS/foo_generic_impl.h"
#undef TYPE_ABBREV
#undef TYPE

// ...
```

Finally in our source file we can use the generics like so
```c
#include "foo_my_types.h"
// ...
struct foo_boo foo1;
struct foo_bazp foo1;
// ...
foo_boo_func1(&foo1, ...);
foo_bazp_func1(&foo2, ...);
// ...
```

See `include/vector_common.h`, `src/vector_common.c`, and `test/vector_test.c`
for example usage.


## Reasoning for Library Design

One may wonder why I designed the library so that the user has to do the
slightly inconvenient macro handling across a header and implementation file.
First I wanted to implement the data structures with an unobtrusive design, so
common intrusive designs were disqualified (if you want intrusive see
[https://github.com/graphitemaster/libintrusive](https://github.com/graphitemaster/libintrusive)).
Consider the two other main alternative ways of doing unobtrusive generics in C.
The first is to use `void*` for data types. The other is to define it like
```c
#define IMPLEMENT(TYPE) \
struct foo_##TYPE { \
    // ... \
}; \
 \
static ret_type foo_##TYPE##_method(...) { \
    // ... \
}
```

I feel my way of doing beats the others out in three main areas.

Maintainability: This is probably the most important to me. Obviously the macro
alternative macro way is nigh unreadable. However, the `void*` way is also hard
to maintain because it requires a lot of workarounds to get flat data structures
(i.e. we want to store `int`s instead of `int*`s to save memory. Using my
methodology we get to write the implementations almost as if we were writing
non-generic data structures, which makes them easier to read and understand.

Efficiency: When using `void*`s we either need to use indirection through
pointers, which is not good for types like `int` and `char`, or we need to use
`memcpy` to move data (something like `memcpy(void_ptr, &element, elem_size)`).
Using `memcpy` and trying to maintain flat data structures adds additional
overhead for the `void*` method, which the compiler can better handle if we
insert the types directly with macros. The other macro method also leads to
executable bloat due to the use of static functions.

Compile Times: Because we have a separate implementation file, we can use
incremental builds to significantly speed up compile times. Since the other
macro method uses static definitions in the header file, it can cause
significant slowdowns in compilation.

If anyone has a better solution for implementing generics in C, or I missed
something, let me know.


## Contributing

There are several conventions that must be obeyed when designing new data
structures for CGDS. First let's see an example header file called
`foo_generic.h`.

```c
// This include defines common macros that are used for defining generic data
// structures.
#include "generic.h"

// For each type paramter we require two macros to be defined.  One gives the
// exact type, and the other (with suffic _ABBREV) is what is included in
// struct and function names.
#ifndef TYPE1
#error "Expected macro TYPE1 to be defined"
#endif

#ifndef TYPE1_ABBREV
#error "Expected macro TYPE1_ABBREV to be defined"
#endif

// We can also define TYPE2, TYPE3, etc.

// When defining a data structure we first define a macro that gives its full
// title with type parameters. GEN1, GEN2, etc. allow us to combine a base name
// with the type parameters.
#define FOO GEN1(foo, TYPE1_ABBREV)
// or #define FOO GEN2(foo, TYPE1_ABBREV, TYPE2_ABBREV)
// etc.

// We then define the main struct like so
struct FOO {
    // ...
};

// Functions that operate over the data structure are declared with the METH
// macro (think like methods in OO languages, but not that :P). The first
// parameter should be a pointer to the data structure.
int METH(FOO, method)(struct FOO *vec, ...);

// Each data structure must also define methods to initialize and free resources
// used by the data structure. Free is not required to handle element resources.
int METH(FOO, init)(struct FOO *vec, ...);
int METH(FOO, free)(struct FOO *vec);

// Undefine the full macro type to prevent collisions.
#undef FOO
```

Now we define our main implementation as `foo_generic_impl.h`.
```c
// We must list out all types again since we cannot gaurantee they're defined.
#ifndef TYPE1
#error "Expected macro TYPE1 to be defined"
#endif

#ifndef TYPE1_ABBREV
#error "Expected macro TYPE1_ABBREV to be defined"
#endif

// We must also define TYPE2, TYPE3, etc.

// These must also be redefined, since they are undefined in the header.
#define FOO GEN1(foo, TYPE1_ABBREV)
// or #define FOO GEN2(foo, TYPE1_ABBREV, TYPE2_ABBREV)
// etc.

// Implement methods like so
int METH(FOO, method)(struct FOO *vec, ...) {
    // ...
}

// Helper functions should be declared static if used.
static ret_type helper(...) {
}
```

Additional things to consider are the following.

1. For functions that delete elements there should be a parameter along the
   lines of `TYPE *elem` that, if non-null, the element to be deleted in is
   placed before deletion. This allows the use to avoid having to make an extra,
   and possibly expensive, call to a lookup function before deletion. It's also
   just plain convenient.

See `include/vector_generic.h` and `include/vector_generic_impl.h` for example
implementations.
