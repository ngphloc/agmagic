#include "AG_PRIVATE_DECREASE_DEFINED.h"

#if AGMAGIC_DEFINED_COUNTER==0
#ifdef	AGMAGIC_DECL
#undef	AGMAGIC_DECL
#endif
#define AGMAGIC_DECL				__declspec(dllexport)

#undef	AGMAGIC_DEFINED_COUNTER	
#undef	THIS_PART_USE_AGMAGIC_LIBRARY

#endif	//#if AGMAGIC_LIBRARY_USED_COUNTER==1