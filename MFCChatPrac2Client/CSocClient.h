#pragma once

#define UM_RECEIVE WM_USER + 1
#define SOC_CLIENT_CONNECT "접속성공"
#define SOC_CLIENT_DISCONNECT "클라이언트 종료"
// CSocClient 명령 대상

class CSocClient : public CSocket
{
public:
	CSocClient();
	virtual ~CSocClient();
	virtual void OnReceive(int nErrorCode);
	void CSocClient::Init(HWND hWnd);

private:
	HWND m_hWnd;

};


