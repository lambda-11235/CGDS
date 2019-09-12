
#include <stdbool.h>

#include "hashtable_common.h"


#define TYPE bool
#define TYPE_ABBREV bool
#define EQUAL(a, b) ((a) == (b))
#define HASH(a) (a)
#include "hashtable_generic_impl.h"
#undef HASH
#undef EQUAL
#undef TYPE_ABBREV
#undef TYPE

#define TYPE char
#define TYPE_ABBREV char
#define EQUAL(a, b) ((a) == (b))
#define HASH(a) (a)
#include "hashtable_generic_impl.h"
#undef HASH
#undef EQUAL
#undef TYPE_ABBREV
#undef TYPE

#define TYPE short
#define TYPE_ABBREV short
#define EQUAL(a, b) ((a) == (b))
#define HASH(a) (a)
#include "hashtable_generic_impl.h"
#undef HASH
#undef EQUAL
#undef TYPE_ABBREV
#undef TYPE

#define TYPE int
#define TYPE_ABBREV int
#define EQUAL(a, b) ((a) == (b))
#define HASH(a) (a)
#include "hashtable_generic_impl.h"
#undef HASH
#undef EQUAL
#undef TYPE_ABBREV
#undef TYPE

#define TYPE long
#define TYPE_ABBREV long
#define EQUAL(a, b) ((a) == (b))
#define HASH(a) (a)
#include "hashtable_generic_impl.h"
#undef HASH
#undef EQUAL
#undef TYPE_ABBREV
#undef TYPE

#define TYPE long long
#define TYPE_ABBREV llong
#define EQUAL(a, b) ((a) == (b))
#define HASH(a) (a)
#include "hashtable_generic_impl.h"
#undef HASH
#undef EQUAL
#undef TYPE_ABBREV
#undef TYPE


#define TYPE unsigned char
#define TYPE_ABBREV uchar
#define EQUAL(a, b) ((a) == (b))
#define HASH(a) (a)
#include "hashtable_generic_impl.h"
#undef HASH
#undef EQUAL
#undef TYPE_ABBREV
#undef TYPE

#define TYPE unsigned short
#define TYPE_ABBREV ushort
#define EQUAL(a, b) ((a) == (b))
#define HASH(a) (a)
#include "hashtable_generic_impl.h"
#undef HASH
#undef EQUAL
#undef TYPE_ABBREV
#undef TYPE

#define TYPE unsigned int
#define TYPE_ABBREV uint
#define EQUAL(a, b) ((a) == (b))
#define HASH(a) (a)
#include "hashtable_generic_impl.h"
#undef HASH
#undef EQUAL
#undef TYPE_ABBREV
#undef TYPE

#define TYPE unsigned long
#define TYPE_ABBREV ulong
#define EQUAL(a, b) ((a) == (b))
#define HASH(a) (a)
#include "hashtable_generic_impl.h"
#undef HASH
#undef EQUAL
#undef TYPE_ABBREV
#undef TYPE

#define TYPE unsigned long long
#define TYPE_ABBREV ullong
#define EQUAL(a, b) ((a) == (b))
#define HASH(a) (a)
#include "hashtable_generic_impl.h"
#undef HASH
#undef EQUAL
#undef TYPE_ABBREV
#undef TYPE


