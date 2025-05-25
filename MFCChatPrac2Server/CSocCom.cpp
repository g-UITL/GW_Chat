// CSocCom.cpp: 구현 파일
//

#include "pch.h"
#include "MFCChatPrac2Server.h"
#include "CSocCom.h"


// CSocCom

CSocCom::CSocCom(int index, HWND hWnd) : m_index(index), m_hWnd(hWnd), m_strNick("사용자")
{
}

CSocCom::CSocCom(int index, HWND hWnd, CString nick) : m_index(index), m_hWnd(hWnd), m_strNick(nick)
{
}

CSocCom::CSocCom()
{
}

CSocCom::~CSocCom()
{
}


// CSocCom 멤버 함수

const int CSocCom::getID() const { return m_index; }

const CString& CSocCom::getNick() const { return m_strNick; }

void CSocCom::setNick(CString nick) { m_strNick = nick; }

void CSocCom::Init(HWND hWnd) {
	m_hWnd = hWnd;
}

void CSocCom::OnReceive(int nErrorCode)
{
	SendMessage(m_hWnd, UM_RECEIVE, reinterpret_cast<WPARAM>(this), 0);
	CSocket::OnReceive(nErrorCode);
}


void CSocCom::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CString strTmp;
	strTmp.Format(_T("%d"), m_index);
	AfxMessageBox(strTmp + _T(" 접속종료"));
	CSocket::OnClose(nErrorCode);
}
