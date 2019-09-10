
#include <stdbool.h>


#ifndef CGDS_AVL_COMMON
#define CGDS_AVL_COMMON


#define TYPE bool
#define TYPE_ABBREV bool
#include "avl_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE char
#define TYPE_ABBREV char
#include "avl_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE short
#define TYPE_ABBREV short
#include "avl_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE int
#define TYPE_ABBREV int
#include "avl_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE long
#define TYPE_ABBREV long
#include "avl_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE long long
#define TYPE_ABBREV llong
#include "avl_generic.h"
#undef TYPE_ABBREV
#undef TYPE


#define TYPE unsigned char
#define TYPE_ABBREV uchar
#include "avl_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE unsigned short
#define TYPE_ABBREV ushort
#include "avl_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE unsigned int
#define TYPE_ABBREV uint
#include "avl_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE unsigned long
#define TYPE_ABBREV ulong
#include "avl_generic.h"
#undef TYPE_ABBREV
#undef TYPE

#define TYPE unsigned long long
#define TYPE_ABBREV ullong
#include "avl_generic.h"
#undef TYPE_ABBREV
#undef TYPE


#endif /* end of include guard: CGDS_AVL_COMMON */

