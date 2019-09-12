
#include <stdbool.h>


#ifndef CGDS_HASHTABLE_COMMON
#define CGDS_HASHTABLE_COMMON


#define TYPE bool
#define TYPE_ABBREV bool
#include "hashtable_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE char
#define TYPE_ABBREV char
#include "hashtable_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE short
#define TYPE_ABBREV short
#include "hashtable_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE int
#define TYPE_ABBREV int
#include "hashtable_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE long
#define TYPE_ABBREV long
#include "hashtable_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE long long
#define TYPE_ABBREV llong
#include "hashtable_generic.h"
#undef TYPE_ABBREV
#undef TYPE


#define TYPE unsigned char
#define TYPE_ABBREV uchar
#include "hashtable_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE unsigned short
#define TYPE_ABBREV ushort
#include "hashtable_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE unsigned int
#define TYPE_ABBREV uint
#include "hashtable_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE unsigned long
#define TYPE_ABBREV ulong
#include "hashtable_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE unsigned long long
#define TYPE_ABBREV ullong
#include "hashtable_generic.h"
#undef TYPE_ABBREV
#undef TYPE


#endif /* end of include guard: CGDS_HASHTABLE_COMMON */
