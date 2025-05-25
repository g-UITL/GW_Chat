
// MFCChatPrac2ClientDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCChatPrac2Client.h"
#include "MFCChatPrac2ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCChatPrac2ClientDlg 대화 상자



CMFCChatPrac2ClientDlg::CMFCChatPrac2ClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATPRAC2CLIENT_DIALOG, pParent)
	, m_strInput(_T(""))
	, m_strIP(_T(""))
	, m_strStatus(_T(""))
	, m_strNick(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatPrac2ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_strInput);
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	DDX_Control(pDX, IDC_LIST1, m_listBox);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_strStatus);
	DDX_Control(pDX, IDC_LIST_USER_LIST, m_listBoxUser);
	DDX_Text(pDX, IDC_EDIT_NICK, m_strNick);
	DDX_Control(pDX, IDC_STATIC_USER_LIST, m_listBoxUser);
}

BEGIN_MESSAGE_MAP(CMFCChatPrac2ClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_RECEIVE, &CMFCChatPrac2ClientDlg::OnReceive)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CMFCChatPrac2ClientDlg::OnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CMFCChatPrac2ClientDlg::OnClickedButtonSend)
	ON_BN_CLICKED(IDCANCEL, &CMFCChatPrac2ClientDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMFCChatPrac2ClientDlg 메시지 처리기

BOOL CMFCChatPrac2ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_socClient.Create();
	m_socClient.Init(m_hWnd);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCChatPrac2ClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	// x 키로 종료했을 경우
	else if (nID == SC_CLOSE)
	{
		m_socClient.Send(SOC_CLIENT_DISCONNECT, 256);
		this->EndDialog(IDCANCEL);
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCChatPrac2ClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCChatPrac2ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CMFCChatPrac2ClientDlg::updateUserList(CString strList)
{
	m_listBoxUser.ResetContent(); //초기화

	//ex1,ex2,ex3 부분만 updateUserList에 삽입
	while (strList.GetLength()) {
		int i = strList.Find(_T(','));
		if (i < 0) // 마지막 일때 
		{
			m_listBoxUser.AddString(strList);
			break;
		}
		CString strTmp = strList.Left(i);
		m_listBoxUser.AddString(strTmp);

		strList = strList.Mid(i + 1);
	}
	return 0;
}

afx_msg LRESULT CMFCChatPrac2ClientDlg::OnReceive(WPARAM wParam, LPARAM lParam)
{
	/*AfxMessageBox(_T("CMFCChatPrac2ClientDlg::OnReceive"));*/
	char pTmp[256];
	memset(pTmp, 0, sizeof(pTmp));

	m_socClient.Receive(pTmp, 256);
	CString strMsg(pTmp);
	if (strMsg.Find(_T("USER_LIST:")) == 0) //"USER_LIST:"가 0번째 즉 맨 앞에 있다면, USER_LIST 업데이트를 해주면 된다.
	{
		//"USER_LIST:ex1,ex2,ex3"에서 앞부분 때고
		//ex1,ex2,ex3 부분만 updateUserList에 삽입
		int itmp = strMsg.Find(_T(':'));
		updateUserList(strMsg.Mid(itmp + 1));
	}
	else { // 일반적으로 메시지를 받는 경우
		postListBox(strMsg);
	}
	UpdateData(FALSE);
	return 0;
}


void CMFCChatPrac2ClientDlg::OnClickedButtonConnect()
{
	UpdateData(TRUE);

	if (m_socClient.Connect(m_strIP, 5000) == FALSE)
	{
		AfxMessageBox(_T("접속 불가"));
		UpdateData(FALSE);
		return;
	}
	else { // 정상 접속시 입력된 닉네임 전송
		CString strTmp = _T("NICK:") + m_strNick;
		CStringA straTmp(strTmp);
		m_socClient.Send(straTmp, straTmp.GetLength());
	}
}


int CMFCChatPrac2ClientDlg::postListBox(CString strMsg)
{
	int i = m_listBox.GetCount();
	m_listBox.InsertString(i, strMsg);
	return 0;
}


void CMFCChatPrac2ClientDlg::OnClickedButtonSend()
{
	UpdateData(TRUE);
	postListBox(_T("나 : ") + m_strInput);

	m_socClient.Send(CT2A(m_strInput), 256);

	m_strInput = "";
	UpdateData(FALSE);
}


BOOL CMFCChatPrac2ClientDlg::PreTranslateMessage(MSG* pMsg)
{
	// Enter키 눌렸을 경우
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		CWnd* pButtonEnter = GetDlgItem(IDC_BUTTON_SEND);
		CWnd* pEditInput = GetDlgItem(IDC_EDIT_INPUT);
		if (pButtonEnter != NULL && pEditInput != NULL) {
			pButtonEnter->SendMessage(BM_CLICK);
			pEditInput->SetFocus();
		}

		return TRUE;
	}

	// ESC키 눌렸을 경우
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		this->EndDialog(IDCANCEL);
	}


	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMFCChatPrac2ClientDlg::OnBnClickedCancel()
{
	m_socClient.Send(SOC_CLIENT_DISCONNECT, 256);
	CDialogEx::OnCancel();
}


int CMFCChatPrac2ClientDlg::addUserList(CString strUser)
{
	
	return 0;
}
