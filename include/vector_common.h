
#include <stdbool.h>


#ifndef CGDS_VECTOR_COMMON
#define CGDS_VECTOR_COMMON


#define TYPE bool
#define TYPE_ABBREV bool
#include "vector_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE char
#define TYPE_ABBREV char
#include "vector_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE short
#define TYPE_ABBREV short
#include "vector_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE int
#define TYPE_ABBREV int
#include "vector_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE long
#define TYPE_ABBREV long
#include "vector_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE long long
#define TYPE_ABBREV llong
#include "vector_generic.h"
#undef TYPE_ABBREV
#undef TYPE


#define TYPE unsigned char
#define TYPE_ABBREV uchar
#include "vector_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE unsigned short
#define TYPE_ABBREV ushort
#include "vector_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE unsigned int
#define TYPE_ABBREV uint
#include "vector_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE unsigned long
#define TYPE_ABBREV ulong
#include "vector_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE unsigned long long
#define TYPE_ABBREV ullong
#include "vector_generic.h"
#undef TYPE_ABBREV
#undef TYPE


#endif /* end of include guard: CGDS_VECTOR_COMMON */
