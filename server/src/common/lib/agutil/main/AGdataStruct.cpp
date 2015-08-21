#include "AGdataStruct.h"

#if AGMAGIC_SUPPORT_MFC
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
CAGmagicElementPtrArray::CAGmagicElementPtrArray() : CAGobjPtrArray<CAGmagicElement>()
{
}
CAGmagicElementPtrArray::~CAGmagicElementPtrArray()
{
}

agbool CAGmagicElementPtrArray::GetValueAt(agint32 idx, agfreal& value)
{
	CAGmagicElement* e=(CAGmagicElement*)GetAt(idx);
	if(e==NULL)	return agfalse;
	value=e->GetValue();
	return agtrue;
}
agbool CAGmagicElementPtrArray::GetIDAt(agint32 idx, aguint_id& ID)
{
	CAGmagicElement* e=(CAGmagicElement*)GetAt(idx);
	if(e==NULL)	return agfalse;
	ID=e->GetID();
	return agtrue;
}

agint32	CAGmagicElementPtrArray::LSearchID(aguint_id ID)
{
	if(IsEmpty())	return -1;
	agint32 n=GetSize();
	agint32 i=0;
	for(i=0; i<n; i++)
	{
		aguint_id	TempID;
		if(!GetIDAt(i,TempID))	continue;
		if(TempID==ID)			break;
	}
	if(i==n)	return -1;
	return i;
}
agbool CAGmagicElementPtrArray::GetValueAtID(aguint_id ID, agfreal& value)
{
	agint32 idx=LSearchID(ID);
	if(idx==-1)	return agfalse;
	return GetValueAt(idx,value);
}
/*******************************class CAGbuRectVec*******************************/
CAGbuRectVec::CAGbuRectVec() : CAGbaseArray<AGBU_RECT>()
{
}
CAGbuRectVec::~CAGbuRectVec()
{
}
agint32 CAGbuRectVec::TotalWidth(agint32 wHinge)
{
	agint32 total_width=0;
	agint32 n=GetSize();
	for(agint32 i=0; i<n; i++)
	{
		AGBU_RECT	rc=GetAt(i);
		agint32		w=(rc.right-rc.left);
		total_width +=w;
		if(i!=n-1)	total_width +=(w>0?wHinge:0);
	}
	return total_width;
}
agint32 CAGbuRectVec::TotalHeight()
{
	agint32 max_height=0;
	agint32 n=GetSize();
	for(agint32 i=0; i<n; i++)
	{
		AGBU_RECT	rc=GetAt(i);
		max_height= AGMAX(max_height,(agint32)(rc.top-rc.bottom));
	}
	return max_height;
}
void CAGbuRectVec::Import(CAGtdRectVec* pRectVec)
{
	RemoveAll();
	if(pRectVec==NULL) return;

	agint32		n=pRectVec->GetSize();
	if(n==0)	return;
	agint32		max_height=pRectVec->TotalHeight();
	SetSize(n);
	for(agint32 i=0; i<n; i++)
	{
		AGBU_RECT&	bu_rc=ElementAt(i);
		AGTD_RECT	td_rc=pRectVec->GetAt(i);
		CAGmagicMicUtil::ChangeTDtoBU(max_height,&bu_rc,&td_rc);
	}
}
void CAGbuRectVec::Import(CAGbuRectMatrix* pRectMatrix)
{
	RemoveAll();
	if(pRectMatrix==NULL) return;
	agint32 rows=pRectMatrix->GetSize();
	for(agint32 i=0; i<rows; i++)
	{
		CAGbuRectVec*			pRectVector=pRectMatrix->GetAt(i);
		if(pRectVector==NULL)	continue;
		agint32					cols=pRectVector->GetSize();

		for(agint32 j=0; j<cols; j++)
			Add(pRectVector->GetAt(j));
	}
}
agbool	CAGbuRectVec::CreateByCut(AGBU_RECT TotalRect, SIZE block_size)
{
	CAGbuRectMatrix RectMatrix;
	agbool bResult=RectMatrix.CreateByCut(TotalRect, block_size);
	Import(&RectMatrix);
	return bResult;
}
agbool	CAGbuRectVec::CreateByCut(AGBU_RECT TotalRect, agint32 nRows, agint32 nCols)
{
	CAGbuRectMatrix RectMatrix;
	agbool bResult=RectMatrix.CreateByCut(TotalRect, nRows, nCols);
	Import(&RectMatrix);
	return bResult;
}
agbool	CAGbuRectVec::CreateByCut(AGBU_RECT TotalRect, agint32 CXsizes[], agint32 nCXsizes, agint32 CYsizes[], agint32 nCYsizes)
{
	CAGbuRectMatrix RectMatrix;
	agbool bResult=RectMatrix.CreateByCut(TotalRect, CXsizes, nCXsizes, CYsizes, nCYsizes);
	Import(&RectMatrix);
	return bResult;
}

/*******************************class CAGbuRectMatrix*******************************/
CAGbuRectMatrix::CAGbuRectMatrix() : CAGobjPtrArray<CAGbuRectVec>()
{
}
CAGbuRectMatrix::~CAGbuRectMatrix()
{
}
agint32 CAGbuRectMatrix::TotalWidth(agint32 wHinge)
{
	agint32 max_width=0;
	agint32 n=GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGbuRectVec*	pRectVec=GetAt(i);
		if(pRectVec)
			max_width = AGMAX(max_width,pRectVec->TotalWidth(wHinge));
	}
	return max_width;
}
agint32 CAGbuRectMatrix::TotalHeight(agint32 hHinge)
{
	agint32 total_height=0;
	agint32 n=GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGbuRectVec*	pRectVec=GetAt(i);
		if(pRectVec)
		{

			agint32			h=pRectVec->TotalHeight();
			total_height	+= h;
			if(i!=n-1)		total_height +=(h>0?hHinge:0);
		}
	}
	return total_height;
}
void CAGbuRectMatrix::Import(CAGtdRectMatrix* pRectMatrix)
{
	RemoveAll();
	if(pRectMatrix==NULL) return;

	agint32		m=pRectMatrix->GetSize();
	if(m==0)	return;
	agint32		max_height=pRectMatrix->TotalHeight();
	SetSize(m,agfalse);

	for(agint32 i=0; i<m; i++)
	{
		CAGbuRectVec*&	pbuRectVec=ElementAt(i);
		CAGtdRectVec*	ptdRectVec=pRectMatrix->GetAt(m-1-i);
		if(ptdRectVec==NULL) continue;
		agint32		n=ptdRectVec->GetSize();
		if(n==0)	continue;
		
		if(pbuRectVec) delete pbuRectVec;
		pbuRectVec=new CAGbuRectVec();
		pbuRectVec->SetSize(n);
		for(agint32 j=0; j<n; j++)
		{
			AGBU_RECT&	bu_rc=pbuRectVec->ElementAt(i);
			AGTD_RECT	td_rc=ptdRectVec->GetAt(i);
			CAGmagicMicUtil::ChangeTDtoBU(max_height,&bu_rc,&td_rc);
		}
	}
}
agbool CAGbuRectMatrix::CreateByCut(AGBU_RECT TotalRect, SIZE block_size)
{
	RemoveAll();

	SIZE TotalSize;
	TotalSize.cx=TotalRect.right-TotalRect.left;
	TotalSize.cy=TotalRect.top-TotalRect.bottom;
	if(TotalSize.cx<=0 || TotalSize.cy<=0 || block_size.cx<=0 || block_size.cy<=0)
		return agfalse;

	if(block_size.cx > TotalSize.cx)	block_size.cx = TotalSize.cx;
	if(block_size.cy > TotalSize.cy)	block_size.cy = TotalSize.cy;
	agint32 rows=TotalSize.cy/block_size.cy;
	agint32 cols=TotalSize.cx/block_size.cx;

	for(agint32 i=0; i<rows; i++)
	{
		CAGbuRectVec* pRectVector=(CAGbuRectVec*)newAGOBJ_ARRAY_TYPE();
		for(agint32 j=0; j<cols; j++)
		{
			AGBU_RECT rc;
			memset(&rc,0,sizeof(AGBU_RECT));

			//goc trai,duoi
			rc.left  =TotalRect.left    + j*block_size.cx;
			rc.bottom=TotalRect.bottom  + i*block_size.cy;

			//goc phai, tren
			if(j==cols-1)	rc.right=TotalRect.right;
			else			rc.right=rc.left + block_size.cx;
			if(i==rows-1)	rc.top=TotalRect.top;
			else			rc.top=rc.bottom + block_size.cy;

			pRectVector->Add(rc);
		}
		Add(pRectVector,agfalse);
	}
	return agtrue;
}
agbool CAGbuRectMatrix::CreateByCut(AGBU_RECT TotalRect, agint32 nRows, agint32 nCols)
{
	RemoveAll();
	if(nRows==0 || nCols==0) return false;

	SIZE	TotalSize;
	TotalSize.cx=TotalRect.right-TotalRect.left;
	TotalSize.cy=TotalRect.top-TotalRect.bottom;
	SIZE	block_size;
	block_size.cx=TotalSize.cx/nCols;
	block_size.cy=TotalSize.cy/nRows;
	
	return CreateByCut(TotalRect,block_size);
}
agbool CAGbuRectMatrix::CreateByCut(AGBU_RECT TotalRect, agint32 CXsizes[], agint32 nCXsizes, agint32 CYsizes[], agint32 nCYsizes)
{
	RemoveAll();
	if(CXsizes==NULL || nCXsizes==0 || CYsizes==NULL || nCYsizes==0)
		throw _T("Invalid parameter");

	SIZE TotalSize;
	TotalSize.cx=TotalRect.right-TotalRect.left;
	TotalSize.cy=TotalRect.top-TotalRect.bottom;
	if(TotalSize.cx<=0 || TotalSize.cy<=0)
		return agfalse;

	agint32 accum_cy=0;
	for(agint32 i=0; i<nCYsizes; i++)
	{
		agint32			cy=CYsizes[i];
		if(cy<=0)		throw _T("Invalid parameter");

		CAGbuRectVec*	pRectVector=(CAGbuRectVec*)newAGOBJ_ARRAY_TYPE();
		agint32			accum_cx=0;
		AGBU_RECT		rc;
		for(agint32 j=0; j<nCXsizes; j++)
		{
			agint32		cx=CXsizes[j];
			if(cx<=0)	throw _T("Invalid parameter");

			memset(&rc,0,sizeof(AGBU_RECT));
			//goc trai,duoi
			rc.left   = TotalRect.left   + accum_cx;
			rc.bottom = TotalRect.bottom + accum_cy;

			//goc phai, tren
			rc.right=rc.left + cx;
			if(rc.right > TotalRect.right)	rc.right = TotalRect.right;
			rc.top=rc.bottom + cy;
			if(rc.top   > TotalRect.top)	rc.top   = TotalRect.top;

			pRectVector->Add(rc);
			if(rc.right == TotalRect.right) break;
			accum_cx +=cx;
		}
		Add(pRectVector,agfalse);
		if(rc.top == TotalRect.top)	break;
		accum_cy +=cy;
	}
	return agtrue;
}

/*******************************class CAGtdRectVec*******************************/

CAGtdRectVec::CAGtdRectVec() : CAGbaseArray<AGTD_RECT>()
{
}
CAGtdRectVec::~CAGtdRectVec()
{
}
agint32 CAGtdRectVec::TotalWidth(agint32 wHinge)
{
	agint32 total_width=0;
	agint32 n=GetSize();
	for(agint32 i=0; i<n; i++)
	{
		AGTD_RECT	rc=GetAt(i);
		agint32		w=(rc.right-rc.left);
		total_width +=w;
		if(i!=n-1)	total_width +=(w>0?wHinge:0);
	}
	return total_width;
}
agint32 CAGtdRectVec::TotalHeight()
{
	agint32 max_height=0;
	agint32 n=GetSize();
	for(agint32 i=0; i<n; i++)
	{
		AGTD_RECT	rc=GetAt(i);
		max_height= AGMAX(max_height,(agint32)(rc.bottom-rc.top));
	}
	return max_height;
}
void CAGtdRectVec::Import(CAGbuRectVec* pRectVec)
{
	RemoveAll();
	if(pRectVec==NULL) return;

	agint32		n=pRectVec->GetSize();
	if(n==0)	return;
	agint32		max_height=pRectVec->TotalHeight();
	SetSize(n);
	for(agint32 i=0; i<n; i++)
	{
		AGTD_RECT&	td_rc=ElementAt(i);
		AGBU_RECT	bu_rc=pRectVec->GetAt(i);
		CAGmagicMicUtil::ChangeBUtoTD(max_height,&td_rc,&bu_rc);
	}
}
void CAGtdRectVec::Import(CAGtdRectMatrix* pRectMatrix)
{
	RemoveAll();
	if(pRectMatrix==NULL) return;
	agint32 rows=pRectMatrix->GetSize();
	for(agint32 i=0; i<rows; i++)
	{
		CAGtdRectVec* pRectVector=pRectMatrix->GetAt(i);
		agint32 cols=pRectVector->GetSize();

		for(agint32 j=0; j<cols; j++)
			Add(pRectVector->GetAt(j));
	}
}
agbool	CAGtdRectVec::CreateByCut(AGTD_RECT TotalRect, SIZE block_size)
{
	CAGtdRectMatrix RectMatrix;
	agbool bResult=RectMatrix.CreateByCut(TotalRect, block_size);
	Import(&RectMatrix);
	return bResult;
}
agbool	CAGtdRectVec::CreateByCut(AGTD_RECT TotalRect, agint32 nRows, agint32 nCols)
{
	CAGtdRectMatrix RectMatrix;
	agbool bResult=RectMatrix.CreateByCut(TotalRect, nRows, nCols);
	Import(&RectMatrix);
	return bResult;
}
agbool	CAGtdRectVec::CreateByCut(AGTD_RECT TotalRect, agint32 CXsizes[], agint32 nCXsizes, agint32 CYsizes[], agint32 nCYsizes)
{
	CAGtdRectMatrix RectMatrix;
	agbool bResult=RectMatrix.CreateByCut(TotalRect, CXsizes, nCXsizes, CYsizes, nCYsizes);
	Import(&RectMatrix);
	return bResult;
}
/*******************************class CAGtdRectMatrix*******************************/
CAGtdRectMatrix::CAGtdRectMatrix() : CAGobjPtrArray<CAGtdRectVec>()
{
}
CAGtdRectMatrix::~CAGtdRectMatrix()
{
}
agint32 CAGtdRectMatrix::TotalWidth(agint32 wHinge)
{
	agint32 max_width=0;
	agint32 n=GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGtdRectVec*	pRectVec=GetAt(i);
		if(pRectVec)
			max_width = AGMAX(max_width,pRectVec->TotalWidth(wHinge));
	}
	return max_width;
}
agint32 CAGtdRectMatrix::TotalHeight(agint32 hHinge)
{
	agint32 total_height=0;
	agint32 n=GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGtdRectVec*	pRectVec=GetAt(i);
		if(pRectVec)
		{

			agint32			h=pRectVec->TotalHeight();
			total_height	+= h;
			if(i!=n-1)		total_height +=(h>0?hHinge:0);
		}
	}
	return total_height;
}
void CAGtdRectMatrix::Import(CAGbuRectMatrix* pRectMatrix)
{
	RemoveAll();
	if(pRectMatrix==NULL) return;

	agint32		m=pRectMatrix->GetSize();
	if(m==0)	return;
	agint32		max_height=pRectMatrix->TotalHeight();
	SetSize(m,agfalse);

	for(agint32 i=0; i<m; i++)
	{
		CAGtdRectVec*&	ptdRectVec=ElementAt(i);
		CAGbuRectVec*	pbuRectVec=pRectMatrix->GetAt(m-1-i);
		if(pbuRectVec==NULL) continue;
		agint32		n=pbuRectVec->GetSize();
		if(n==0)	continue;
		
		if(ptdRectVec) delete ptdRectVec;
		ptdRectVec=new CAGtdRectVec();
		ptdRectVec->SetSize(n);
		for(agint32 j=0; j<n; j++)
		{
			AGTD_RECT&	td_rc=ptdRectVec->ElementAt(i);
			AGBU_RECT	bu_rc=pbuRectVec->GetAt(i);
			CAGmagicMicUtil::ChangeBUtoTD(max_height,&td_rc,&bu_rc);
		}
	}
}
agbool	CAGtdRectMatrix::CreateByCut(AGTD_RECT TotalRect, SIZE block_size)
{
	RemoveAll();

	SIZE TotalSize;
	TotalSize.cx=TotalRect.right-TotalRect.left;
	TotalSize.cy=TotalRect.bottom-TotalRect.top;
	if(TotalSize.cx<=0 || TotalSize.cy<=0 || block_size.cx<=0 || block_size.cy<=0)
		return agfalse;

	if(block_size.cx > TotalSize.cx)	block_size.cx = TotalSize.cx;
	if(block_size.cy > TotalSize.cy)	block_size.cy = TotalSize.cy;
	agint32 rows=TotalSize.cy/block_size.cy;
	agint32 cols=TotalSize.cx/block_size.cx;

	for(agint32 i=0; i<rows; i++)
	{
		CAGtdRectVec* pRectVector=(CAGtdRectVec*)newAGOBJ_ARRAY_TYPE();
		for(agint32 j=0; j<cols; j++)
		{
			AGTD_RECT rc;
			memset(&rc,0,sizeof(AGTD_RECT));

			//goc trai,duoi
			rc.left  =TotalRect.left    + j*block_size.cx;
			rc.top=TotalRect.top  + i*block_size.cy;

			//goc phai, tren
			if(j==cols-1)	rc.right=TotalRect.right;
			else			rc.right=rc.left + block_size.cx;
			if(i==rows-1)	rc.bottom=TotalRect.bottom;
			else			rc.bottom=rc.top + block_size.cy;

			pRectVector->Add(rc);
		}
		Add(pRectVector,agfalse);
	}
	return agtrue;
}
agbool	CAGtdRectMatrix::CreateByCut(AGTD_RECT TotalRect, agint32 nRows, agint32 nCols)
{
	RemoveAll();
	if(nRows==0 || nCols==0) return false;

	SIZE	TotalSize;
	TotalSize.cx=TotalRect.right-TotalRect.left;
	TotalSize.cy=TotalRect.bottom-TotalRect.top;
	SIZE	block_size;
	block_size.cx=TotalSize.cx/nCols;
	block_size.cy=TotalSize.cy/nRows;
	
	return CreateByCut(TotalRect,block_size);
}
agbool	CAGtdRectMatrix::CreateByCut(AGTD_RECT TotalRect, agint32 CXsizes[], agint32 nCXsizes, agint32 CYsizes[], agint32 nCYsizes)
{
	RemoveAll();
	if(CXsizes==NULL || nCXsizes==0 || CYsizes==NULL || nCYsizes==0)
		throw _T("Invalid parameter");

	SIZE TotalSize;
	TotalSize.cx=TotalRect.right-TotalRect.left;
	TotalSize.cy=TotalRect.bottom-TotalRect.top;
	if(TotalSize.cx<=0 || TotalSize.cy<=0)
		return agfalse;

	agint32 accum_cy=0;
	for(agint32 i=0; i<nCYsizes; i++)
	{
		agint32			cy=CYsizes[i];
		if(cy<=0)		throw _T("Invalid parameter");

		CAGtdRectVec*	pRectVector=(CAGtdRectVec*)newAGOBJ_ARRAY_TYPE();
		agint32			accum_cx=0;
		AGTD_RECT		rc;
		for(agint32 j=0; j<nCXsizes; j++)
		{
			agint32		cx=CXsizes[j];
			if(cx<=0)	throw _T("Invalid parameter");

			memset(&rc,0,sizeof(AGTD_RECT));
			//goc trai,duoi
			rc.left   = TotalRect.left   + accum_cx;
			rc.top = TotalRect.top + accum_cy;

			//goc phai, tren
			rc.right=rc.left + cx;
			if(rc.right > TotalRect.right)	rc.right = TotalRect.right;
			rc.bottom=rc.top + cy;
			if(rc.bottom   > TotalRect.bottom)	rc.bottom   = TotalRect.bottom;

			pRectVector->Add(rc);
			if(rc.right == TotalRect.right) break;
			accum_cx +=cx;
		}
		Add(pRectVector,agfalse);
		if(rc.bottom == TotalRect.bottom)	break;
		accum_cy +=cy;
	}
	return agtrue;
}
