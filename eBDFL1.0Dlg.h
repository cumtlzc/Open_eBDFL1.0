
// eBDFL1.0Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "PDFLib.h"

// CeBDFL10Dlg �Ի���
class CeBDFL10Dlg : public CDialogEx
{
// ����
public:
	CeBDFL10Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EBDFL10_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
	CString URLToImgPath(CString url);
	int URLToPage(CString url);
	CProgressCtrl m_Progress;
	CString URLToGuide (CString url);
	void DownloadImg(int page,CString per_ImgPath,CString mark,CString localPath);
	void ImgToPDF(PDF*p,CString localPath);
public:
	PDF *p;
};
