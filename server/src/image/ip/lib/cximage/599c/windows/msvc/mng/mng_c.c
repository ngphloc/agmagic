#include <windows.h>
#include <stdio.h>
#include "mng_c.h"

/////////////////////////////////////////////////////////////////////////////
// callbacks for the mng decoder:
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// memory allocation; data must be zeroed
mng_ptr mymngalloc( mng_uint32 size )
{
	return (mng_ptr)calloc(1, size);
}

/////////////////////////////////////////////////////////////////////////////
// memory deallocation
void mymngfree(mng_ptr p, mng_uint32 size)
{
	free(p);
}

/////////////////////////////////////////////////////////////////////////////
// Stream open/close:
// since the user is responsible for opening and closing the file,
// we leave the default implementation open
mng_bool mymngopenstream(mng_handle mng)      { return MNG_TRUE; }
mng_bool mymngopenstreamwrite(mng_handle mng) { return MNG_TRUE; }
mng_bool mymngclosestream(mng_handle mng)     { return MNG_TRUE; }

/////////////////////////////////////////////////////////////////////////////
// feed data to the decoder
mng_bool mymngreadstream(mng_handle mng, mng_ptr buffer, mng_uint32 size, mng_uint32 *bytesread)
{
	mngstuff *mymng = (mngstuff *)mng_get_userdata(mng);
	// read the requested amount of data from the file
	*bytesread = fread( buffer, sizeof(BYTE), size, mymng->file );
	return MNG_TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// the header's been read. set up the display stuff
mng_bool mymngprocessheader( mng_handle mng, mng_uint32 width, mng_uint32 height )
{
	// normally the image buffer is allocated here,
	// but in this module we don't know nothing about
	// the final environment.

	mngstuff *mymng = (mngstuff *)mng_get_userdata(mng);
	mymng->width  = width;
	mymng->height = height;
	mymng->effwdt = ((((width * 24) + 31) >> 5) << 2);

	// tell the mng decoder about our bit-depth choice
	mng_set_canvasstyle( mng, MNG_CANVAS_BGR8 );
	return MNG_TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// return a row pointer for the decoder to fill
mng_ptr mymnggetcanvasline( mng_handle mng, mng_uint32 line )
{
	mngstuff *mymng = (mngstuff *)mng_get_userdata(mng);
	return (mng_ptr)(mymng->image + (mymng->effwdt * (mymng->height - 1 - line)));
}

/////////////////////////////////////////////////////////////////////////////
// timer
mng_uint32 mymnggetticks(mng_handle mng)
{
	return (mng_uint32)GetTickCount();
}

/////////////////////////////////////////////////////////////////////////////
// Refresh:
mng_bool mymngrefresh(mng_handle mng, mng_uint32 x, mng_uint32 y, mng_uint32 w, mng_uint32 h)
{
	mngstuff *mymng = (mngstuff *)mng_get_userdata(mng);
	mymng->refresh = MNG_TRUE; //set the refresh flag
	return MNG_TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// interframe delay callback
mng_bool mymngsettimer(mng_handle mng, mng_uint32 msecs)
{
	mngstuff *mymng = (mngstuff *)mng_get_userdata(mng);
	mymng->delay = msecs; 	// set the timer for when the decoder wants to be woken
	return MNG_TRUE;
}

/////////////////////////////////////////////////////////////////////////////
mng_bool mymngerror(mng_handle mng, mng_int32 code, mng_int8 severity, mng_chunkid chunktype, mng_uint32 chunkseq, mng_int32 extra1, mng_int32 extra2, mng_pchar text)
{
	throw (const char *)text;
}

/////////////////////////////////////////////////////////////////////////////
