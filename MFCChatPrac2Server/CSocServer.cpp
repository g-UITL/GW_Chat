// CSocServer.cpp: 구현 파일
//

#include "pch.h"
#include "MFCChatPrac2Server.h"
#include "CSocServer.h"


// CSocServer

CSocServer::CSocServer() : m_clientID(0)
{
}

CSocServer::~CSocServer()
{
	// 통신소켓 메모리 초기화
	for (auto socket : m_mSocCom) {
		delete socket.second;
	}
}


// CSocServer 멤버 함수

void CSocServer::Init(HWND hWnd) {
	m_hWnd = hWnd;
}

std::map<int, CSocCom*> CSocServer::GetSocMap() {
	return m_mSocCom;
}

CSocCom* CSocServer::GetSoc(size_t id) {
	return m_mSocCom[id];
}

void CSocServer::OnAccept(int nErrorCode)
{
	// 클라이언트 정원 찼을 경우
	if (m_mSocCom.size() == MAX_CLIENTS) {
		CSocCom socTmp(0, m_hWnd);
		Accept(socTmp);
		socTmp.Send("방이 꽉찼습니다.", 256);
		socTmp.Close();
		return;
	}
	
	++m_clientID;
	m_mSocCom[m_clientID] = new CSocCom(m_clientID, m_hWnd);
	Accept(*m_mSocCom[m_clientID]);

	//닉네임 수신
	char pTmp[256];
	memset(pTmp, 0, sizeof(pTmp));
	m_mSocCom[m_clientID]->Receive(pTmp, 256);
	CString strTmpNick(pTmp);
	int itmp = strTmpNick.Find(':');
	strTmpNick = strTmpNick.Mid(itmp + 1);
	m_mSocCom[m_clientID]->setNick(strTmpNick);

	//유저
	m_mSocCom[m_clientID]->Send("접속완료", 256);
	SendMessage(m_hWnd, UM_ACCEPT, reinterpret_cast<WPARAM>(m_mSocCom[m_clientID]), 0);
	CSocket::OnAccept(nErrorCode);
}


int CSocServer::disconnectClient(size_t id)
{
	if (m_mSocCom.count(id) == 0)
		return EXIT_FAILURE;

	delete m_mSocCom[id]; // 메모리 초기화
	m_mSocCom.erase(id); // 맵에서 제거

	return EXIT_SUCCESS;
}
