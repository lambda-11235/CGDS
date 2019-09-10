
#ifndef CGDS_GENERIC_H
#define CGDS_GENERIC_H


#define GENERIC_ERROR_MSG(MACRO) "Expected macro " #MACRO " to be defined"

#define GEN1(BASE, TYPE) XGEN1(BASE, TYPE)
#define XGEN1(BASE, TYPE) BASE ## _ ## TYPE

#define GEN2(BASE, TYPE1, TYPE2) XGEN2(BASE, TYPE1, TYPE2)
#define XGEN2(BASE, TYPE1, TYPE2) BASE ## _ ## TYPE1 ## _ ## TYPE2

#define GEN3(BASE, TYPE1, TYPE2, TYPE3) XGEN2(BASE, TYPE1, TYPE2, TYPE3)
#define XGEN3(BASE, TYPE1, TYPE2, TYPE3) BASE ## _ ## TYPE1 ## _ ## TYPE2 ## _ ## TYPE3

// Declares FUNC as a method of TYPE.
#define METH(TYPE, FUNC) XMETH(TYPE, FUNC)
#define XMETH(TYPE, FUNC) TYPE ## _ ## FUNC


#endif /* end of include guard: CGDS_GENERIC_H */
