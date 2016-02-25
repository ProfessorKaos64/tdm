/*****************************************************************************
                    The Dark Mod GPL Source Code
 
 This file is part of the The Dark Mod Source Code, originally based 
 on the Doom 3 GPL Source Code as published in 2011.
 
 The Dark Mod Source Code is free software: you can redistribute it 
 and/or modify it under the terms of the GNU General Public License as 
 published by the Free Software Foundation, either version 3 of the License, 
 or (at your option) any later version. For details, see LICENSE.TXT.
 
 Project: The Dark Mod (http://www.thedarkmod.com/)
 
 $Revision: 5171 $ (Revision of last commit) 
 $Date: 2012-01-07 10:08:06 +0200 (Sat, 07 Jan 2012) $ (Date of last commit)
 $Author: greebo $ (Author of last commit)
 
******************************************************************************/

#include "precompiled_engine.h"
#pragma hdrstop

static bool versioned = RegisterVersionedFile("$Id: RotateDlg.cpp 5171 2012-01-07 08:08:06Z greebo $");

#include "qe3.h"
#include "Radiant.h"
#include "RotateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRotateDlg dialog


CRotateDlg::CRotateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRotateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRotateDlg)
	m_strX = _T("");
	m_strY = _T("");
	m_strZ = _T("");
	//}}AFX_DATA_INIT
}


void CRotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRotateDlg)
	DDX_Control(pDX, IDC_SPIN3, m_wndSpin3);
	DDX_Control(pDX, IDC_SPIN2, m_wndSpin2);
	DDX_Control(pDX, IDC_SPIN1, m_wndSpin1);
	DDX_Text(pDX, IDC_ROTX, m_strX);
	DDX_Text(pDX, IDC_ROTY, m_strY);
	DDX_Text(pDX, IDC_ROTZ, m_strZ);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRotateDlg, CDialog)
	//{{AFX_MSG_MAP(CRotateDlg)
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, OnDeltaposSpin3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRotateDlg message handlers

void CRotateDlg::OnOK() 
{
  OnApply();
  CDialog::OnOK();
}

void CRotateDlg::OnApply() 
{
  UpdateData(TRUE);
	float f = atof(m_strX);
  if (f != 0.0)
    Select_RotateAxis(0,f);
	f = atof(m_strY);
  if (f != 0.0)
    Select_RotateAxis(1,f);
	f = atof(m_strZ);
  if (f != 0.0)
    Select_RotateAxis(2,f);
}

BOOL CRotateDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_wndSpin1.SetRange(0, 359);
	m_wndSpin2.SetRange(0, 359);
	m_wndSpin3.SetRange(0, 359);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRotateDlg::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	Select_RotateAxis(0, pNMUpDown->iDelta);
	*pResult = 0;
}

void CRotateDlg::OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	Select_RotateAxis(1, pNMUpDown->iDelta);
	*pResult = 0;
}

void CRotateDlg::OnDeltaposSpin3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	Select_RotateAxis(2, pNMUpDown->iDelta);
	*pResult = 0;
}

void CRotateDlg::ApplyNoPaint()
{

}
