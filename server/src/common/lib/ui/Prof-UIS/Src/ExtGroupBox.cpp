// This is part of the Professional User Interface Suite library.
// Copyright (C) 2001-2004 FOSS Software, Inc.
// All rights reserved.
//
// http://www.prof-uis.com
// http://www.fossware.com
// mailto:support@fossware.com
//
// This source code can be used, modified and redistributed
// under the terms of the license agreement that is included
// in the Professional User Interface Suite package.
//
// Warranties and Disclaimers:
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND
// INCLUDING, BUT NOT LIMITED TO, WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
// IN NO EVENT WILL FOSS SOFTWARE INC. BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES,
// INCLUDING DAMAGES FOR LOSS OF PROFITS, LOSS OR INACCURACY OF DATA,
// INCURRED BY ANY PERSON FROM SUCH PERSON'S USAGE OF THIS SOFTWARE
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

#include "stdafx.h"

#if (!defined __EXT_GROUPBOX_H)
	#include <ExtGroupBox.h>
#endif

#if (!defined __EXT_MEMORY_DC_H)
	#include <../Src/ExtMemoryDC.h>
#endif

#if (!defined __EXT_PAINT_MANAGER_H)
	#include <ExtPaintManager.h>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtGroupBox

IMPLEMENT_DYNAMIC( CExtGroupBox, CButton );

CExtGroupBox::CExtGroupBox()
	: m_eStyle( STYLE_ETCHED )
{
}

CExtGroupBox::~CExtGroupBox()
{
}

BEGIN_MESSAGE_MAP(CExtGroupBox, CButton)
	//{{AFX_MSG_MAP(CExtGroupBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtGroupBox message handlers

void CExtGroupBox::PreSubclassWindow() 
{
	ModifyStyle( 0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS );
	CButton::PreSubclassWindow();
}

LRESULT CExtGroupBox::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if( message == WM_ERASEBKGND )
		return TRUE;
    if( message == WM_PAINT )
    {
		CRect rcClient;
		GetClientRect( &rcClient );
		CPaintDC dcPaint( this );
		CExtMemoryDC dc( &dcPaint, &rcClient );
		if( g_PaintManager->GetCb2DbTransparentMode(this) )
		{
			CExtPaintManager::stat_ExcludeChildAreas(
				dc,
				GetSafeHwnd(),
				CExtPaintManager::stat_DefExcludeChildAreaCallback
				);
			g_PaintManager->PaintDockerBkgnd( dc, this );
		} // if( g_PaintManager->GetCb2DbTransparentMode(this) )
		else
			dc.FillSolidRect( &rcClient, g_PaintManager->GetColor(CExtPaintManager::CLR_3DFACE_OUT) );
		int nOldBkMode = dc.SetBkMode(TRANSPARENT);
		// caption 
		CString strText;
		GetWindowText( strText );
		CRect rcText(
			9,
			0,
			rcClient.right - 4,
			rcClient.bottom
			);
		CRect rcBorder( rcClient );
		if( strText.GetLength() > 0 )
		{
			DWORD dwDrawTextFlags = DT_LEFT;
			if( strText.Find( _T('\t') ) != -1 ) // do tabs expanding
				dwDrawTextFlags |= DT_EXPANDTABS;
			dwDrawTextFlags |= (DT_VCENTER|DT_END_ELLIPSIS); 
			bool bEnabled = IsWindowEnabled() ? true : false;
			CRect rcTextDimension = OnDrawLabelText(
				dc,
				rcText,
				strText,
				dwDrawTextFlags,
				bEnabled
				);
			rcText.right = rcText.left + rcTextDimension.Width();
			rcText.bottom = rcText.top + rcTextDimension.Height();
			rcText.InflateRect(2,0,2,0);
			if( rcText.right > rcClient.right-4 ){
				rcText.right = rcClient.right-4;
			}
			dc.ExcludeClipRect( &rcText );
			rcBorder.top += rcText.Height()/2;
		} // if( strText.GetLength() > 0 )
		else 
		{
			rcBorder.top += 6;
		}
	
		// frame rect
		OnDrawFrameRect(
			dc,
			rcBorder
			);
		dc.SetBkMode(nOldBkMode);
		//DefWindowProc( WM_PAINT, WPARAM(dc.GetSafeHdc()), 0L );
		g_PaintManager->OnPaintSessionComplete( this );

		// redraw siblings
		CWnd *pParent = GetParent();
		for(	CWnd* pWnd = pParent->GetWindow(GW_CHILD);
				pWnd != NULL && pWnd != this;
				pWnd = pWnd->GetWindow(GW_HWNDNEXT)
			)
		{
			CRect rcChildRect, rcIntersection;
			pWnd->GetWindowRect( &rcChildRect );
			ScreenToClient( &rcChildRect );
			rcIntersection.IntersectRect(
				&rcClient,
				&rcChildRect
				);
			
			if( !rcIntersection.IsRectEmpty() )
			{
				VERIFY(
					pWnd->RedrawWindow(
					NULL,
					NULL,
					RDW_INVALIDATE //|RDW_UPDATENOW
					|RDW_ERASE //|RDW_ERASENOW
					|RDW_FRAME|RDW_ALLCHILDREN
					)
					);
			}// if( !rcIntersection.IsRectEmpty() )
		}

		return 0;
    } // if( message == WM_PAINT )	

	if(		message == WM_SETTEXT 
		||	message == WM_ENABLE
		||	message == 0x0128 // WM_UPDATEUISTATE
		)
	{
		SetRedraw( FALSE );
		LRESULT lResult = CButton::WindowProc(message, wParam, lParam);
		SetRedraw( TRUE );
		if( (GetStyle()&WS_CHILD) != 0 )
		{
			CWnd * pWndParent = GetParent();
			ASSERT_VALID( pWndParent );
			CRect rc;
			GetWindowRect( &rc );
			pWndParent->ScreenToClient( &rc );
			pWndParent->InvalidateRect( &rc );
		} // if( (GetStyle()&WS_CHILD) != 0 )
		Invalidate();
		return lResult;
	}
	return CButton::WindowProc(message, wParam, lParam);
}

void CExtGroupBox::OnDrawFrameRect(
	CDC & dc,
	const RECT & rcClient
	)
{
CRect rcBorder( rcClient );
	switch( m_eStyle )
	{
	case STYLE_ETCHED:
		{
			dc.Draw3dRect(
				&rcBorder,
				g_PaintManager->GetColor( COLOR_3DSHADOW ),
				g_PaintManager->GetColor( COLOR_WINDOW )
				);
			rcBorder.DeflateRect(1,1);
			dc.Draw3dRect(
				&rcBorder,
				g_PaintManager->GetColor( COLOR_WINDOW ),
				g_PaintManager->GetColor( COLOR_3DSHADOW )
				);
		}
		break;
	case STYLE_ROUNDED:
		{
			CBrush * pBrush =
				CBrush::FromHandle( (HBRUSH)::GetStockObject(NULL_BRUSH) );
			CBrush * pOldBrush = dc.SelectObject( pBrush );
			CPen pen;
			pen.CreatePen(
				PS_SOLID,
				1,
				g_PaintManager->GetColor( COLOR_3DSHADOW )
				);
			CPen * pOldPen = dc.SelectObject( &pen );
			dc.RoundRect(
				&rcClient,
				CPoint( 10, 10 )
				);
			dc.SelectObject( pOldPen );
			dc.SelectObject( pOldBrush );
		}
		break;
	case STYLE_FLAT:
		{
			dc.Draw3dRect(
				&rcBorder,
				g_PaintManager->GetColor( COLOR_3DSHADOW ),
				g_PaintManager->GetColor( COLOR_3DSHADOW )
				);
		}
		break;
	} // switch( m_eStyle )
}
	
CRect CExtGroupBox::OnDrawLabelText(
	CDC & dc,
	const RECT & rcText,
	__EXT_MFC_SAFE_LPCTSTR strText,
	DWORD dwDrawTextFlags,
	bool bEnabled
	)
{
	HFONT hFont = (HFONT)
		::SendMessage( m_hWnd, WM_GETFONT, 0L, 0L );
	if( hFont == NULL )
	{
		HWND hWndParent = ::GetParent( m_hWnd );
		if( hWndParent != NULL )
			hFont = (HFONT)
			::SendMessage( hWndParent, WM_GETFONT, 0L, 0L );
	} // if( hFont == NULL )
	if( hFont == NULL )
	{
		hFont = (HFONT)::GetStockObject( DEFAULT_GUI_FONT );
		if( hFont == NULL )
			hFont = (HFONT)::GetStockObject( SYSTEM_FONT );
	} // if( hFont == NULL )
HGDIOBJ hOldFont = NULL;
	if( hFont != NULL )
		hOldFont = ::SelectObject( dc, (HGDIOBJ)hFont );
INT nOldBkMode = dc.SetBkMode( TRANSPARENT );
	COLORREF clrOldText =
		dc.SetTextColor(
			g_PaintManager->GetColor(
				bEnabled
					? COLOR_BTNTEXT
					: COLOR_3DSHADOW
			)
		);
CRect rc( rcText );
	dc.DrawText(
		LPCTSTR(strText),
		_tcslen(strText),
		rc,
		dwDrawTextFlags
		);
CRect rcTextDimension =
		CExtPaintManager::stat_CalcTextDimension(
			dc,
			*(CFont::FromHandle(hFont)),
			strText
			);
	dc.SetTextColor( clrOldText );
	dc.SetBkMode( nOldBkMode );
	if( hFont != NULL )
		::SelectObject( dc, hOldFont );
	return rcTextDimension;
}

