// 2048Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "2048.h"
#include "2048Dlg.h"
#include <stdlib.h> 
#include <stdio.h> 
#include <time.h> 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy2048Dlg dialog

CMy2048Dlg::CMy2048Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy2048Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy2048Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy2048Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy2048Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy2048Dlg, CDialog)
	//{{AFX_MSG_MAP(CMy2048Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DOWN, OnDown)
	ON_BN_CLICKED(IDC_LEFT, OnLeft)
	ON_BN_CLICKED(IDC_RIGHT, OnRight)
	ON_BN_CLICKED(IDC_UP, OnUp)
	ON_BN_CLICKED(IDC_RESTART, OnRestart)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy2048Dlg message handlers

BOOL CMy2048Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	srand( (unsigned)time( NULL ) ); 
	ClearData();

	//set the font of the digit
	CFont font;
	font.CreatePointFont(200,_T("宋体"),NULL);
	unsigned int x,idc = IDC_STATIC0;
	for(x=0;x<16;x++)
	{
		GetDlgItem(idc)->SetFont(&font);
		idc++;
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy2048Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy2048Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy2048Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMy2048Dlg::OnDown() 
{
	// TODO: Add your control notification handler code here
	PullDown();
	
}

void CMy2048Dlg::OnLeft() 
{
	// TODO: Add your control notification handler code here
	PullLeft();
	
}

void CMy2048Dlg::OnRight() 
{
	// TODO: Add your control notification handler code here
	PullRight();
}

void CMy2048Dlg::OnUp() 
{
	// TODO: Add your control notification handler code here
	PullUp();
	
}

unsigned int CMy2048Dlg::Randomize(unsigned int max)
{
	return (rand()%(max+1));
}

void CMy2048Dlg::GetNewItem(void)
{
	unsigned int randomitem = Randomize(100);
	unsigned int newItem;
	unsigned int randomblocksC;
	unsigned int randomblocksR;
	if(randomitem < 80)
	{
		newItem = 2;
	}
	else
	{
		newItem = 4;
	}

	if(newItem > maxnumber)
	{
		maxnumber = newItem;
	}

	do
	{
		randomblocksC = Randomize(3);
		randomblocksR = Randomize(3);
	}
	while(_2048[randomblocksC][randomblocksR]);

	_2048[randomblocksC][randomblocksR] = newItem;
	_2048BackUp[randomblocksC][randomblocksR] = newItem;
}

void CMy2048Dlg::PullRight(void)
{
	unsigned int i;
	bool IsCombine = 0;

	if(!IsDie())
	{
		for(i = 0; i<4; i++)
		{
			//数组向右移
			if(!(_2048[i][0]==0 && _2048[i][1]==0 && _2048[i][2]==0))
			{
				if(_2048[i][1] == 0)
				{
					IsCombine = 1;

					_2048[i][1] = _2048[i][0];
					_2048[i][0] = 0;
				}
				if(_2048[i][2] == 0)
				{
					IsCombine = 1;

					_2048[i][2] = _2048[i][1];
					_2048[i][1] = _2048[i][0];
					_2048[i][0] = 0;
				}
				if(_2048[i][3] == 0)
				{
					IsCombine = 1;

					_2048[i][3] = _2048[i][2];
					_2048[i][2] = _2048[i][1];
					_2048[i][1] = _2048[i][0];
					_2048[i][0] = 0;
				}
			}

			//合并
			if(_2048[i][3] == _2048[i][2] && _2048[i][3] != 0)
			{
				IsCombine = 1;

				_2048[i][3] *= 2; 
				score += _2048[i][3];

				if(_2048[i][3] > maxnumber)
				{
					maxnumber = _2048[i][3];
				}

				_2048[i][2] = 0;
			}


			if(_2048[i][2] == _2048[i][1] && _2048[i][2] != 0)
			{
				IsCombine = 1;

				_2048[i][2] *= 2; 
				score += _2048[i][2];

				if(_2048[i][2] > maxnumber)
				{
					maxnumber = _2048[i][2];
				}

				_2048[i][1] = 0;
			}

			if(_2048[i][1] == _2048[i][0] && _2048[i][1] != 0)
			{
				IsCombine = 1;

				_2048[i][1] *= 2; 
				score += _2048[i][1];

				if(_2048[i][1] > maxnumber)
				{
					maxnumber = _2048[i][1];
				}

				_2048[i][0] = 0;
			}

			//再向右移一次
			if(!(_2048[i][0]==0 && _2048[i][1]==0 && _2048[i][2]==0))
			{
				if(_2048[i][1] == 0)
				{
					_2048[i][1] = _2048[i][0];
					_2048[i][0] = 0;
				}
				if(_2048[i][2] == 0)
				{
					_2048[i][2] = _2048[i][1];
					_2048[i][1] = _2048[i][0];
					_2048[i][0] = 0;
				}
				if(_2048[i][3] == 0)
				{
					_2048[i][3] = _2048[i][2];
					_2048[i][2] = _2048[i][1];
					_2048[i][1] = _2048[i][0];
					_2048[i][0] = 0;
				}
			}
		}

		if(IsDataChanged())
		GetNewItem();

		ShowNumber();

		if(IsDie())
		{
			MessageBox("Game Over! T_T");
		}
	}
}

void CMy2048Dlg::PullLeft(void)
{
	unsigned int i;
	bool IsCombine = 0;

	if(!IsDie())
	{
		for(i = 0; i<4; i++)
		{
			//数组向左移
			if(!(_2048[i][1]==0 && _2048[i][2]==0 && _2048[i][3]==0))
			{
				if(_2048[i][2] == 0)
				{
					IsCombine = 1;

					_2048[i][2] = _2048[i][3];
					_2048[i][3] = 0;
				}
				if(_2048[i][1] == 0)
				{
					IsCombine = 1;
					_2048[i][1] = _2048[i][2];
					_2048[i][2] = _2048[i][3];
					_2048[i][3] = 0;
				}
				if(_2048[i][0] == 0)
				{
					IsCombine = 1;
					_2048[i][0] = _2048[i][1];
					_2048[i][1] = _2048[i][2];
					_2048[i][2] = _2048[i][3];
					_2048[i][3] = 0;
				}
			}

			//合并
			if(_2048[i][0] == _2048[i][1] && _2048[i][0] != 0)
			{
				IsCombine = 1;

				_2048[i][0] *= 2; 
				score += _2048[i][0];

				if(_2048[i][0] > maxnumber)
				{
					maxnumber = _2048[i][0];
				}

				_2048[i][1] = 0;
			}


			if(_2048[i][1] == _2048[i][2] && _2048[i][1] != 0)
			{
				IsCombine = 1;

				_2048[i][1] *= 2; 
				score += _2048[i][1];

				if(_2048[i][1] > maxnumber)
				{
					maxnumber = _2048[i][1];
				}

				_2048[i][2] = 0;
			}

			if(_2048[i][2] == _2048[i][3] && _2048[i][2] != 0)
			{
				IsCombine = 1;

				_2048[i][2] *= 2; 
				score += _2048[i][2];

				if(_2048[i][2] > maxnumber)
				{
					maxnumber = _2048[i][2];
				}

				_2048[i][3] = 0;
			}

			//再向左移一次
			if(!(_2048[i][1]==0 && _2048[i][2]==0 && _2048[i][3]==0))
			{
				if(_2048[i][2] == 0)
				{
					_2048[i][2] = _2048[i][3];
					_2048[i][3] = 0;
				}
				if(_2048[i][1] == 0)
				{
					_2048[i][1] = _2048[i][2];
					_2048[i][2] = _2048[i][3];
					_2048[i][3] = 0;
				}
				if(_2048[i][0] == 0)
				{
					_2048[i][0] = _2048[i][1];
					_2048[i][1] = _2048[i][2];
					_2048[i][2] = _2048[i][3];
					_2048[i][3] = 0;
				}
			}
		}
		if(IsDataChanged())
		GetNewItem();

		ShowNumber();

		if(IsDie())
		{
			MessageBox("Game Over! T_T");
		}
	}
}

void CMy2048Dlg::PullUp(void)
{
	unsigned int i;
	bool IsCombine = 0;

	if(!IsDie())
	{
		for(i = 0; i<4; i++)
		{
			//数组向上移
			if(!(_2048[1][i]==0 && _2048[2][i]==0 && _2048[3][i]==0))
			{
				if(_2048[2][i] == 0)
				{
					IsCombine = 1;

					_2048[2][i] = _2048[3][i];
					_2048[3][i] = 0;
				}
				if(_2048[1][i] == 0)
				{
					IsCombine = 1;

					_2048[1][i] = _2048[2][i];
					_2048[2][i] = _2048[3][i];
					_2048[3][i] = 0;
				}
				if(_2048[0][i] == 0)
				{
					IsCombine = 1;
					_2048[0][i] = _2048[1][i];
					_2048[1][i] = _2048[2][i];
					_2048[2][i] = _2048[3][i];
					_2048[3][i] = 0;
				}
			}

			//合并
			if(_2048[0][i] == _2048[1][i] && _2048[0][i] != 0)
			{
				IsCombine = 1;

				_2048[0][i] *= 2; 
				score += _2048[0][i];

				if(_2048[0][i] > maxnumber)
				{
					maxnumber = _2048[0][i];
				}

				_2048[1][i] = 0;
			}


			if(_2048[1][i] == _2048[2][i] && _2048[1][i] != 0)
			{
				IsCombine = 1;

				_2048[1][i] *= 2; 
				score += _2048[1][i];

				if(_2048[1][i] > maxnumber)
				{
					maxnumber = _2048[1][i];
				}

				_2048[2][i] = 0;
			}

			if(_2048[2][i] == _2048[3][i] && _2048[2][i] != 0)
			{
				IsCombine = 1;

				_2048[2][i] *= 2; 
				score += _2048[2][i];

				if(_2048[2][i] > maxnumber)
				{
					maxnumber = _2048[2][i];
				}

				_2048[3][i] = 0;
			}

			//再上移一次
			if(!(_2048[1][i]==0 && _2048[2][i]==0 && _2048[3][i]==0))
			{
				if(_2048[2][i] == 0)
				{
					_2048[2][i] = _2048[3][i];
					_2048[3][i] = 0;
				}
				if(_2048[1][i] == 0)
				{
					_2048[1][i] = _2048[2][i];
					_2048[2][i] = _2048[3][i];
					_2048[3][i] = 0;
				}
				if(_2048[0][i] == 0)
				{
					_2048[0][i] = _2048[1][i];
					_2048[1][i] = _2048[2][i];
					_2048[2][i] = _2048[3][i];
					_2048[3][i] = 0;
				}
			}
		}

		if(IsDataChanged())
		GetNewItem();

		ShowNumber();

		if(IsDie())
		{
			MessageBox("Game Over! T_T");
		}
	}
}

void CMy2048Dlg::PullDown(void)
{
	unsigned int i;
	bool IsCombine = 0;

	if(!IsDie())
	{
		for(i = 0; i<4; i++)
		{
			//数组向下移
			if(!(_2048[0][i]==0 && _2048[1][i]==0 && _2048[2][i]==0))
			{
				if(_2048[1][i] == 0)
				{
					IsCombine = 1;

					_2048[1][i] = _2048[0][i];
					_2048[0][i] = 0;
				}
				if(_2048[2][i] == 0)
				{
					IsCombine = 1;
					_2048[2][i] = _2048[1][i];
					_2048[1][i] = _2048[0][i];
					_2048[0][i] = 0;
				}
				if(_2048[3][i] == 0)
				{
					IsCombine = 1;
					_2048[3][i] = _2048[2][i];
					_2048[2][i] = _2048[1][i];
					_2048[1][i] = _2048[0][i];
					_2048[0][i] = 0;
				}
			}

			//合并
			if(_2048[3][i] == _2048[2][i] && _2048[3][i] != 0)
			{
				IsCombine = 1;

				_2048[3][i] *= 2; 
				score += _2048[3][i];

				if(_2048[3][i] > maxnumber)
				{
					maxnumber = _2048[3][i];
				}

				_2048[2][i] = 0;
			}


			if(_2048[2][i] == _2048[1][i] && _2048[2][i] != 0)
			{
				IsCombine = 1;

				_2048[2][i] *= 2; 
				score += _2048[2][i];

				if(_2048[2][i] > maxnumber)
				{
					maxnumber = _2048[2][i];
				}

				_2048[1][i] = 0;
			}

			if(_2048[1][i] == _2048[0][i] && _2048[1][i] != 0)
			{
				IsCombine = 1;

				_2048[1][i] *= 2; 
				score += _2048[1][i];

				if(_2048[1][i] > maxnumber)
				{
					maxnumber = _2048[1][i];
				}

				_2048[0][i] = 0;
			}

			//再向下移一次
			if(!(_2048[0][i]==0 && _2048[1][i]==0 && _2048[2][i]==0))
			{
				if(_2048[1][i] == 0)
				{
					_2048[1][i] = _2048[0][i];
					_2048[0][i] = 0;
				}
				if(_2048[2][i] == 0)
				{
					_2048[2][i] = _2048[1][i];
					_2048[1][i] = _2048[0][i];
					_2048[0][i] = 0;
				}
				if(_2048[3][i] == 0)
				{
					_2048[3][i] = _2048[2][i];
					_2048[2][i] = _2048[1][i];
					_2048[1][i] = _2048[0][i];
					_2048[0][i] = 0;
				}
			}
		}
		if(IsDataChanged())
		GetNewItem();

		ShowNumber();

		if(IsDie())
		{
			MessageBox("Game Over! T_T");
		}
	}
}

void CMy2048Dlg::ShowNumber(void)
{
	unsigned short x,y;
	unsigned int idc = IDC_STATIC0;
	CString str;
	for(x=0;x<4;x++)
	{
		for(y=0;y<4;y++)
		{
			if(_2048[x][y] == 0)
			{
				str = "";
			}
			else
			{
				str.Format("%d",_2048[x][y]);
			}

			GetDlgItem(idc)->SetWindowText(str);
			idc++;
		}
	}
	str.Format("%d",score);
	GetDlgItem(IDC_SCORE)->SetWindowText(str);

	str.Format("%d",maxnumber);
	GetDlgItem(IDC_MAX)->SetWindowText(str);
}

bool CMy2048Dlg::IsDie(void)
{
	unsigned short x,y;
	for(x=0;x<4;x++)
	{
		for(y=0;y<4;y++)
		{
			if(_2048[x][y] == 0)
			{
				return 0;
			}
		}
	}

	for(x=0;x<4;x++)
	{
		if(CheckCols(x) == 0)
		{
			return 0;
		}
		if(CheckRows(x) == 0)
		{
			return 0;
		}
	}

	return 1;
}

bool CMy2048Dlg::CheckCols(unsigned int col)
{
	if(_2048[0][col] == _2048[1][col])
		return 0;

	if(_2048[1][col] == _2048[2][col])
		return 0;

	if(_2048[2][col] == _2048[3][col])
		return 0;

	return 1;
}

bool CMy2048Dlg::CheckRows(unsigned int row)
{
	if(_2048[row][0] == _2048[row][1])
		return 0;

	if(_2048[row][1] == _2048[row][2])
		return 0;

	if(_2048[row][2] == _2048[row][3])
		return 0;

	return 1;
}

void CMy2048Dlg::ClearData(void)
{
	unsigned short x,y;
	for(x=0;x<4;x++)
	{
		for(y=0;y<4;y++)
		{
			_2048[x][y] =0;
		}
	}
	maxnumber = 0;
	score = 0;

	GetNewItem();
	GetNewItem();

	for(x=0;x<4;x++)
	{
		for(y=0;y<4;y++)
		{
			_2048BackUp[x][y] = _2048[x][y];
		}
	}

	ShowNumber();
}

bool CMy2048Dlg::IsDataChanged(void)
{
	bool IsChanged = 0;
	unsigned short x,y;
	for(x=0;x<4;x++)
	{
		for(y=0;y<4;y++)
		{
			if(_2048BackUp[x][y] != _2048[x][y])
			{
				IsChanged = 1;
				_2048BackUp[x][y] = _2048[x][y];
			}
		}
	}

	return IsChanged;
}

void CMy2048Dlg::OnRestart() 
{
	// TODO: Add your control notification handler code here
	ClearData();
}

void CMy2048Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	PullDown();
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMy2048Dlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	PullUp();
	CDialog::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CMy2048Dlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
	case VK_DOWN:
		PullDown();
		break;

	case VK_UP:
		PullUp();
		break;

	case VK_LEFT:
		PullLeft();
		break;

	case VK_RIGHT:
		PullRight();
		break;
	}
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}

BOOL CMy2048Dlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg-> message   ==   WM_KEYDOWN)         //若 按键消息
    { 
        switch   (pMsg-> wParam)                 //获取按键虚键值
        { 
        case   VK_DOWN:                          //方向键下的虚拟键值
			PullDown();
			return 0;

		case	VK_UP:
			PullUp();
			return 0;

		case	VK_LEFT:
			PullLeft();
			return 0;

		case	VK_RIGHT:
			PullRight();
			return 0;
        } 
    } 
	return CDialog::PreTranslateMessage(pMsg);
}
