
// eBDFL1.0Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "PDFLib.h"

// CeBDFL10Dlg 对话框
class CeBDFL10Dlg : public CDialogEx
{
// 构造
public:
	CeBDFL10Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EBDFL10_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
