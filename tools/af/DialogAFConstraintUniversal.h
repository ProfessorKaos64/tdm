/*****************************************************************************
                    The Dark Mod GPL Source Code
 
 This file is part of the The Dark Mod Source Code, originally based 
 on the Doom 3 GPL Source Code as published in 2011.
 
 The Dark Mod Source Code is free software: you can redistribute it 
 and/or modify it under the terms of the GNU General Public License as 
 published by the Free Software Foundation, either version 3 of the License, 
 or (at your option) any later version. For details, see LICENSE.TXT.
 
 Project: The Dark Mod (http://www.thedarkmod.com/)
 
 $Revision: 5122 $ (Revision of last commit) 
 $Date: 2011-12-11 21:47:31 +0200 (Sun, 11 Dec 2011) $ (Date of last commit)
 $Author: greebo $ (Author of last commit)
 
******************************************************************************/
#pragma once

// DialogAFConstraintUniversal dialog

class DialogAFConstraintUniversal : public CDialog {

	DECLARE_DYNAMIC(DialogAFConstraintUniversal)

public:
						DialogAFConstraintUniversal(CWnd* pParent = NULL);   // standard constructor
	virtual				~DialogAFConstraintUniversal();
	void				LoadFile( idDeclAF *af );
	void				SaveFile( void );
	void				LoadConstraint( idDeclAF_Constraint *c );
	void				SaveConstraint( void );
	void				UpdateFile( void );

						enum { IDD = IDD_DIALOG_AF_CONSTRAINT_UNIVERSAL };

protected:
	virtual void		DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual int			OnToolHitTest( CPoint point, TOOLINFO* pTI ) const;
	afx_msg BOOL		OnToolTipNotify( UINT id, NMHDR *pNMHDR, LRESULT *pResult );
	afx_msg void		OnBnClickedRadioAnchorJoint();
	afx_msg void		OnBnClickedRadioAnchorCoordinates();
	afx_msg void		OnCbnSelchangeComboAnchorJoint();
	afx_msg void		OnEnChangeEditAnchorX();
	afx_msg void		OnEnChangeEditAnchorY();
	afx_msg void		OnEnChangeEditAnchorZ();
	afx_msg void		OnDeltaposSpinAnchorX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void		OnDeltaposSpinAnchorY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void		OnDeltaposSpinAnchorZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void		OnBnClickedRadioUniversalBoneShaft1();
	afx_msg void		OnBnClickedRadioUniversalAnglesShaft1();
	afx_msg void		OnCbnSelchangeComboUniversalJoint1Shaft1();
	afx_msg void		OnCbnSelchangeComboUniversalJoint2Shaft1();
	afx_msg void		OnEnChangeEditUniversalPitchShaft1();
	afx_msg void		OnDeltaposSpinUniversalPitchShaft1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void		OnEnChangeEditUniversalYawShaft1();
	afx_msg void		OnDeltaposSpinUniversalYawShaft1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void		OnBnClickedRadioUniversalBoneShaft2();
	afx_msg void		OnBnClickedRadioUniversalAnglesShaft2();
	afx_msg void		OnCbnSelchangeComboUniversalJoint1Shaft2();
	afx_msg void		OnCbnSelchangeComboUniversalJoint2Shaft2();
	afx_msg void		OnEnChangeEditUniversalPitchShaft2();
	afx_msg void		OnDeltaposSpinUniversalPitchShaft2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void		OnEnChangeEditUniversalYawShaft2();
	afx_msg void		OnDeltaposSpinUniversalYawShaft2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void		OnBnClickedRadioUniversalLimitNone();
	afx_msg void		OnBnClickedRadioUniversalLimitCone();
	afx_msg void		OnBnClickedRadioUniversalLimitPyramid();
	afx_msg void		OnEnChangeEditUniversalLimitConeAngle();
	afx_msg void		OnDeltaposSpinUniversalLimitConeAngle(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void		OnEnChangeEditUniversalLimitPyramidAngle1();
	afx_msg void		OnDeltaposSpinUniversalLimitPyramidAngle1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void		OnEnChangeEditUniversalLimitPyramidAngle2();
	afx_msg void		OnDeltaposSpinUniversalLimitPyramidAngle2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void		OnEnChangeEditUniversalLimitRoll();
	afx_msg void		OnDeltaposSpinUniversalLimitRoll(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void		OnBnClickedRadioUniversalLimitBone();
	afx_msg void		OnBnClickedRadioUniversalLimitAngles();
	afx_msg void		OnCbnSelchangeComboUniversalLimitJoint1();
	afx_msg void		OnCbnSelchangeComboUniversalLimitJoint2();
	afx_msg void		OnEnChangeEditUniversalLimitPitch();
	afx_msg void		OnDeltaposSpinUniversalLimitPitch(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void		OnEnChangeEditUniversalLimitYaw();
	afx_msg void		OnDeltaposSpinUniversalLimitYaw(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()

private:
	idDeclAF *			file;
	idDeclAF_Constraint*constraint;

	//{{AFX_DATA(DialogAFConstraintUniversal)
	CComboBox			m_comboAnchorJoint;
	float				m_anchor_x;
	float				m_anchor_y;
	float				m_anchor_z;
	CComboBox			m_comboJoint1Shaft1;
	CComboBox			m_comboJoint2Shaft1;
	float				m_pitchShaft1;
	float				m_yawShaft1;
	CComboBox			m_comboJoint1Shaft2;
	CComboBox			m_comboJoint2Shaft2;
	float				m_pitchShaft2;
	float				m_yawShaft2;
	float				m_coneAngle;
	float				m_pyramidAngle1;
	float				m_pyramidAngle2;
	CComboBox			m_comboLimitJoint1;
	CComboBox			m_comboLimitJoint2;
	float				m_limitPitch;
	float				m_limitYaw;
	float				m_limitRoll;
	//}}AFX_DATA

	static toolTip_t	toolTips[];

private:
	void				InitJointLists( void );
};
