#ifndef _MNG_C_
#define	_MNG_C_

#include "libmng.h"

/////////////////////////////////////////////////////////////////////////////
typedef struct 
{
	FILE		*file;
	BYTE		*image;
	mng_uint32	delay;
	mng_uint32  width;
	mng_uint32  height;
	mng_uint32  effwdt;
	mng_bool	refresh;
} mngstuff;

/////////////////////////////////////////////////////////////////////////////
// callbacks for the mng decoder:
/////////////////////////////////////////////////////////////////////////////
mng_ptr		mymngalloc( mng_uint32 size );
void		mymngfree(mng_ptr p, mng_uint32 size);

mng_bool	mymngopenstream(mng_handle mng);
mng_bool	mymngopenstreamwrite(mng_handle mng);
mng_bool	mymngclosestream(mng_handle mng);
mng_bool	mymngreadstream(mng_handle mng, mng_ptr buffer, mng_uint32 size, mng_uint32 *bytesread);

mng_bool	mymngprocessheader( mng_handle mng, mng_uint32 width, mng_uint32 height );
mng_ptr		mymnggetcanvasline( mng_handle mng, mng_uint32 line );

mng_uint32	mymnggetticks(mng_handle mng);
mng_bool	mymngrefresh(mng_handle mng, mng_uint32 x, mng_uint32 y, mng_uint32 w, mng_uint32 h);
mng_bool	mymngsettimer(mng_handle mng, mng_uint32 msecs);

mng_bool	mymngerror(mng_handle mng, mng_int32 code, mng_int8 severity, mng_chunkid chunktype, mng_uint32 chunkseq, mng_int32 extra1, mng_int32 extra2, mng_pchar text);

/////////////////////////////////////////////////////////////////////////////
#endif //_MNG_C_