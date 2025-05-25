
// MFCChatPrac2ClientDlg.h: 헤더 파일
//

#pragma once
#include "CSocClient.h"

// CMFCChatPrac2ClientDlg 대화 상자
class CMFCChatPrac2ClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCChatPrac2ClientDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCHATPRAC2CLIENT_DIALOG };
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
	CString m_strIP;
	CListBox m_listBox;
	CString m_strStatus;
private:
	CSocClient m_socClient;
protected:
	afx_msg LRESULT OnReceive(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnClickedButtonConnect();
	int postListBox(CString strMsg);
	afx_msg void OnClickedButtonSend();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCancel();
	int addUserList(CString strUser);
private:
	CString m_strNick;
	CListBox m_listBoxUser;
	int updateUserList(CString strList);
public:
	afx_msg void OnDestroy();
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
