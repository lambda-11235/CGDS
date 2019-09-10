
#include <stdbool.h>

#include "avl_common.h"


static inline int llong_compare(long long x, long long y) {
    if (x < y)
        return -1;
    else if (x > y)
        return 1;
    else
        return 0;
}

static inline int ullong_compare(unsigned long long x, unsigned long long y) {
    if (x < y)
        return -1;
    else if (x > y)
        return 1;
    else
        return 0;
}


#define TYPE bool
#define TYPE_ABBREV bool
#define COMPARE(a, b) ((a) - (b))
#include "avl_generic_impl.h"
#undef COMPARE
#undef TYPE_ABBREV
#undef TYPE

#define TYPE char
#define TYPE_ABBREV char
#define COMPARE(a, b) ((a) - (b))
#include "avl_generic_impl.h"
#undef COMPARE
#undef TYPE_ABBREV
#undef TYPE

#define TYPE short
#define TYPE_ABBREV short
#define COMPARE(a, b) ((a) - (b))
#include "avl_generic_impl.h"
#undef COMPARE
#undef TYPE_ABBREV
#undef TYPE

#define TYPE int
#define TYPE_ABBREV int
#define COMPARE(a, b) ((a) - (b))
#include "avl_generic_impl.h"
#undef COMPARE
#undef TYPE_ABBREV
#undef TYPE

#define TYPE long
#define TYPE_ABBREV long
#define COMPARE llong_compare
#include "avl_generic_impl.h"
#undef COMPARE
#undef TYPE_ABBREV
#undef TYPE

#define TYPE long long
#define TYPE_ABBREV llong
#define COMPARE llong_compare
#include "avl_generic_impl.h"
#undef COMPARE
#undef TYPE_ABBREV
#undef TYPE


#define TYPE unsigned char
#define TYPE_ABBREV uchar
#define COMPARE(a, b) ((a) - (b))
#include "avl_generic_impl.h"
#undef COMPARE
#undef TYPE_ABBREV
#undef TYPE

#define TYPE unsigned short
#define TYPE_ABBREV ushort
#define COMPARE(a, b) ((a) - (b))
#include "avl_generic_impl.h"
#undef COMPARE
#undef TYPE_ABBREV
#undef TYPE

#define TYPE unsigned int
#define TYPE_ABBREV uint
#define COMPARE(a, b) ((a) - (b))
#include "avl_generic_impl.h"
#undef COMPARE
#undef TYPE_ABBREV
#undef TYPE

#define TYPE unsigned long
#define TYPE_ABBREV ulong
#define COMPARE ullong_compare
#include "avl_generic_impl.h"
#undef COMPARE
#undef TYPE_ABBREV
#undef TYPE

#define TYPE unsigned long long
#define TYPE_ABBREV ullong
#define COMPARE ullong_compare
#include "avl_generic_impl.h"
#undef COMPARE
#undef TYPE_ABBREV
#undef TYPE

