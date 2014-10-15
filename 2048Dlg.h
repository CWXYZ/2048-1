// 2048Dlg.h : header file
//

#if !defined(AFX_2048DLG_H__1035D912_1FBB_41C7_A212_291B27242006__INCLUDED_)
#define AFX_2048DLG_H__1035D912_1FBB_41C7_A212_291B27242006__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VK_LEFT           0x25
#define VK_UP             0x26
#define VK_RIGHT          0x27
#define VK_DOWN           0x28

/////////////////////////////////////////////////////////////////////////////
// CMy2048Dlg dialog

class CMy2048Dlg : public CDialog
{
// Construction
public:
	CMy2048Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMy2048Dlg)
	enum { IDD = IDD_MY2048_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy2048Dlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	unsigned int _2048[4][4];
	unsigned int _2048BackUp[4][4];
	unsigned int Randomize(unsigned int max);
	void GetNewItem(void);
	void PullRight(void);
	void PullLeft(void);
	void PullUp(void);
	void PullDown(void);
	void ShowNumber(void);
	bool IsDie(void);
	bool IsDataChanged(void);
	bool CheckCols(unsigned int col);
	bool CheckRows(unsigned int row);
	void ClearData(void);
	unsigned int maxnumber;
	unsigned int score;
	// Generated message map functions
	//{{AFX_MSG(CMy2048Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDown();
	afx_msg void OnLeft();
	afx_msg void OnRight();
	afx_msg void OnUp();
	afx_msg void OnRestart();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_2048DLG_H__1035D912_1FBB_41C7_A212_291B27242006__INCLUDED_)
