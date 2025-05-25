
// MFCChatPrac2ServerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCChatPrac2Server.h"
#include "MFCChatPrac2ServerDlg.h"
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


// CMFCChatPrac2ServerDlg 대화 상자



CMFCChatPrac2ServerDlg::CMFCChatPrac2ServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATPRAC2SERVER_DIALOG, pParent)
	, m_strInput(_T(""))
	, m_strStatus(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatPrac2ServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_strInput);
	DDX_Control(pDX, IDC_LIST1, m_listBox);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_strStatus);
	DDX_Control(pDX, IDC_LIST_USER_LIST, m_listBoxUser);
}

BEGIN_MESSAGE_MAP(CMFCChatPrac2ServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CMFCChatPrac2ServerDlg::OnClickedButtonSend)
	ON_MESSAGE(UM_ACCEPT, &CMFCChatPrac2ServerDlg::OnAccept)
	ON_MESSAGE(UM_RECEIVE, &CMFCChatPrac2ServerDlg::OnReceive)
END_MESSAGE_MAP()


// CMFCChatPrac2ServerDlg 메시지 처리기

BOOL CMFCChatPrac2ServerDlg::OnInitDialog()
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
	m_socServer.Create(5000);
	m_socServer.Listen();
	m_socServer.Init(m_hWnd);
	
	m_strStatus = _T("대기중");
	UpdateData(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCChatPrac2ServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCChatPrac2ServerDlg::OnPaint()
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
HCURSOR CMFCChatPrac2ServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCChatPrac2ServerDlg::OnClickedButtonSend()
{
	UpdateData(TRUE);
	postListBox(_T("나 : ") + m_strInput);
	sendToAll(_T("관리자 : ") + m_strInput, 0);
	m_strInput = "";
	UpdateData(FALSE);
}

int CMFCChatPrac2ServerDlg::sendUserList(CSocCom* soc_client = NULL)
{
	//유저리스트 형식 "USER_LIST:example1,example2,example3"
	CString strUserList = _T("USER_LIST:");
	for (int i = 0; i < m_listBoxUser.GetCount(); i++) {
		CString strTmp;
		m_listBoxUser.GetText(i, strTmp);
		if (i == 0) {
			strUserList += strTmp;
		}
		else {
			strUserList += _T(",") + strTmp;
		}
	}
	CStringA straUserList(strUserList);

	if (soc_client == NULL) // 모든 유저에게 새로운 유저 보내기
	{
		auto socClients = m_socServer.GetSocMap();
		for (auto socClient : socClients) {
			CSocCom* client = socClient.second;
			client->Send(straUserList, straUserList.GetLength()); //유저리스트 보내기
		}
	}
	else { // 해당유저에게만 보내기
		
		// .. 이럴경우 없을것으로 예상

	}
	return 0;
}

afx_msg LRESULT CMFCChatPrac2ServerDlg::OnAccept(WPARAM wParam, LPARAM lParam)
{
	CSocCom* soc_client = reinterpret_cast<CSocCom*>(wParam);

	// 리스트박스 추가
	postListBox(soc_client->getNick());

	// 사용자목록에 추가
	postUserListBox(soc_client->getNick());
	
	// Status 값 변경
	m_strStatus = soc_client->getNick() + _T("접속완료");

	// 유저리스트 업데이트 후 모든 유저에게 전송
	sendUserList();

	UpdateData(FALSE);
	return 0;
}


afx_msg LRESULT CMFCChatPrac2ServerDlg::OnReceive(WPARAM wParam, LPARAM lParam)
{
	CSocCom* soc_client = reinterpret_cast<CSocCom*>(wParam);

	char pTmp[256];
	memset(pTmp, 0, sizeof(pTmp));
	int rv = soc_client->Receive(pTmp, 256);
	
	if (rv == 0 || strcmp(pTmp, SOC_CLIENT_DISCONNECT) == 0) {
		postListBox(soc_client->getNick() + _T(" : 접속종료"));
		sendToAll(soc_client->getNick() + _T(" : 접속종료"), soc_client->getID());
		eraseUserListBox(soc_client->getNick());
		// 유저리스트 업데이트 후 모든 유저에게 전송
		sendUserList();
		m_socServer.disconnectClient(soc_client->getID());
	}
	else {
		CString strMsg(pTmp);
		postListBox(soc_client->getNick() + _T(" : ") + strMsg);
		sendToAll(soc_client->getNick() + _T(" : ") + strMsg, soc_client->getID());
	}

	UpdateData(FALSE);
	return 0;
}




int CMFCChatPrac2ServerDlg::postListBox(CString strMSG)
{
	int i = m_listBox.GetCount();
	m_listBox.InsertString(i, strMSG);
	return 0;
}

int CMFCChatPrac2ServerDlg::postUserListBox(CString strMSG)
{
	int i = m_listBoxUser.GetCount();
	m_listBoxUser.InsertString(i, strMSG);
	return 0;
}

int CMFCChatPrac2ServerDlg::eraseUserListBox(CString strNick)
{
	m_listBoxUser.DeleteString(m_listBoxUser.FindString(-1, strNick));
	return 0;
}


int CMFCChatPrac2ServerDlg::sendToAll(CString strMsg, size_t id)
{
	std::map<int, CSocCom*> mapSocCom = m_socServer.GetSocMap();
	for (auto socCom : mapSocCom) {
		if (socCom.first == id) continue; // 본인 제외 
		char pTmp[256];
		memset(pTmp, 0, sizeof(pTmp));
		strcpy_s(pTmp, CT2A(strMsg));
		socCom.second->Send(pTmp, 256);
	}
	return 0;
}


BOOL CMFCChatPrac2ServerDlg::PreTranslateMessage(MSG* pMsg)
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

	return CDialogEx::PreTranslateMessage(pMsg);
}
