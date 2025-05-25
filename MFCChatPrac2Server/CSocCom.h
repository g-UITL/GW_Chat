#pragma once

#define UM_RECEIVE WM_USER+2
#define SOC_CLIENT_CONNECT "접속성공"
#define SOC_CLIENT_DISCONNECT "클라이언트 종료"
// CSocCom 명령 대상

class CSocCom : public CSocket
{
public:
	CSocCom(int index, HWND hWnd);
	CSocCom(int index, HWND hWnd, CString nick);
	virtual ~CSocCom();
	

private:
	CSocCom();
	HWND m_hWnd; // 메인윈도우
	int	m_index; // 사용자 인덱스 이자 ID
	CString m_strNick; // 사용자 닉네임

public:
	const int getID() const;
	const CString& getNick() const;
	void setNick(CString nick);

	void CSocCom::Init(HWND hWnd); // 메인윈도우 연결
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


