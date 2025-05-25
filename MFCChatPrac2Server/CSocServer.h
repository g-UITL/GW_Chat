#pragma once
#include "CSocCom.h"
#include <map>
#define UM_ACCEPT WM_USER + 1
#define MAX_CLIENTS 3
// CSocServer 명령 대상

class CSocServer : public CSocket
{
public:
	CSocServer();
	virtual ~CSocServer();

	void CSocServer::Init(HWND hWnd);		// 메인윈도우 연결

	std::map<int, CSocCom*> GetSocMap();
	CSocCom* GetSoc(size_t id);

	virtual void OnAccept(int nErrorCode);

private:
	HWND m_hWnd;					// 메인윈도우
	std::map<int, CSocCom*> m_mSocCom;// 통신용소켓
	size_t	m_clientID;				// 클라이언트 아이디
public:
	int disconnectClient(size_t id);
};
