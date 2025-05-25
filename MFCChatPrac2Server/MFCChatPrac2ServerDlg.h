
// MFCChatPrac2ServerDlg.h: 헤더 파일
//
#include "CSocServer.h"
#pragma once


// CMFCChatPrac2ServerDlg 대화 상자
class CMFCChatPrac2ServerDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCChatPrac2ServerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCHATPRAC2SERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strInput;
	CListBox m_listBox;
	CString m_strStatus;
	CSocServer m_socServer;
	afx_msg void OnClickedButtonSend();

protected:
	afx_msg LRESULT OnAccept(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReceive(WPARAM wParam, LPARAM lParam);
public:
	int postUserListBox(CString strMSG);
	int postListBox(CString strMSG);

	int sendToAll(CString strMsg, size_t id);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
private:
	CListBox m_listBoxUser;
	int sendUserList(CSocCom* soc_client);
	int eraseUserListBox(CString strNick);
};
