
// eBDFL1.0Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "eBDFL1.0.h"
#include "eBDFL1.0Dlg.h"
#include "afxdialogex.h"

#include <string>
#include <urlmon.h>
#pragma comment(lib,"urlmon.lib")


#pragma comment(lib, "PDFLib.lib")

using namespace std;
#include <afxinet.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CeBDFL10Dlg 对话框



CeBDFL10Dlg::CeBDFL10Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CeBDFL10Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CeBDFL10Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
}

BEGIN_MESSAGE_MAP(CeBDFL10Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CeBDFL10Dlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CeBDFL10Dlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CeBDFL10Dlg 消息处理程序

BOOL CeBDFL10Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CeBDFL10Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CeBDFL10Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CeBDFL10Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CeBDFL10Dlg::URLToPage(CString url){
	int page=0;
	int count=0;
	bool flag=false;
	CString NeedText;
	int count01=0;
	bool flag01=false;
	CString FinalNeed;
	try{
		CInternetSession mysession; 
		CHttpFile* hF= (CHttpFile*)mysession.OpenURL(url); //打开网址
		CString strData,strAllData;
		bool m_begin=false;
		while(hF->ReadString(strData)){ //读取数据
			if(strData=="		<script>"){
				m_begin=true;
			}
			if(strData=="	             var checkCode = function(code){"){
				m_begin=false;
			}
			if(m_begin){
				strAllData+="@";
				strAllData+=strData;
			}	
		}
		for(int i=0;i<strAllData.GetLength();i++){
			if(strAllData.GetAt(i)=='@'){
				count++;
			}
			if(count==9){
				flag=true;
			}else{
				flag=false;
			}
			if(flag){
				NeedText+=strAllData.GetAt(i);
			}
		}
		for(int i=0;i<NeedText.GetLength();i++){
			if(NeedText.GetAt(i)=='='){
				count01++;
			}
			if(count01==2){
				flag01=true;
			}
			if(NeedText.GetAt(i)==';'){
				flag01=false;
			}
			if(flag01){
				FinalNeed+=NeedText.GetAt(i);
			}
		}
		hF->Close();
		mysession.Close();
	}catch(CException *e){
		AfxMessageBox("获取数据失败");
	};
	return page=_ttoi(FinalNeed.TrimLeft("= "));
}
CString CeBDFL10Dlg::URLToImgPath(CString url){
	/******************************\
		通过URL读取网页的源码信息
	\******************************/
	CString FinalNeed;
	CString NeedText;
	bool flag=false;
	bool flag01=false;
	int count=0;

	try{
		CInternetSession mysession; 
		CHttpFile* hF= (CHttpFile*)mysession.OpenURL(url); //打开网址
		CString strData,strAllData;
		bool m_begin=false;
		while(hF->ReadString(strData)){ //读取数据
			if(strData=="		<script>"){
				m_begin=true;
			}
			if(strData=="	             var checkCode = function(code){"){
				m_begin=false;
			}
			if(m_begin){
				strAllData+="@";
				strAllData+=strData;
			}	
		}	
		for(int i=0;i<strAllData.GetLength();i++){
			if(strAllData.GetAt(i)=='@'){
				count++;
			}
			if(count==8){
				flag=true;
			}else{
				flag=false;
			}
			if(flag){
				NeedText+=strAllData.GetAt(i);
			}
		}
		for(int i=0;i<NeedText.GetLength();i++){
			if(NeedText.GetAt(i)=='h'){
				flag01=true;
			}
			if(NeedText.GetAt(i)=='\''){
				flag01=false;
			}
			if(flag01){
				FinalNeed+=NeedText.GetAt(i);
			}
		}
		hF->Close();
		mysession.Close();
	}catch(CException *e){
		AfxMessageBox("获取数据失败");
	};
	return FinalNeed;
}
CString CeBDFL10Dlg::URLToGuide (CString url){
	/******************************\
		通过URL读取网页的源码信息
	\******************************/
	CString FinalNeed;
	CString NeedText;
	bool flag=false;
	bool flag01=false;
	int count=0;

	try{
		CInternetSession mysession; 
		CHttpFile* hF= (CHttpFile*)mysession.OpenURL(url); //打开网址
		CString strData,strAllData;
		bool m_begin=false;
		while(hF->ReadString(strData)){ //读取数据
			if(strData=="                        jpgPath:str,"){
				m_begin=true;
			}
			if(strData=="                        page: null || filpspage || spage,"){
				m_begin=false;
			}
			if(m_begin){
				strAllData+="@";
				strAllData+=strData;
			}	
		}
		for(int i=0;i<strAllData.GetLength();i++){
			if(strAllData.GetAt(i)==','){
				count++;
				flag01=true;
			}
			if(strAllData.GetAt(i)==']'||count%2!=0){
				flag01=false;
			}
			if(flag01){
				switch(count){
					case 2:
						FinalNeed.AppendChar(strAllData.GetAt(i+1));
						break;
					case 4:
						FinalNeed.AppendChar(strAllData.GetAt(i+1));
						break;
					case 6:
						FinalNeed.AppendChar(strAllData.GetAt(i+1));
						break;
					case 8:
						FinalNeed.AppendChar(strAllData.GetAt(i+1));
						break;
					case 10:
						FinalNeed.AppendChar(strAllData.GetAt(i+1));
						break;
					default:
						break;
				}
			}			
		}

		hF->Close();
		mysession.Close();
	}catch(CException *e){
		AfxMessageBox("获取数据失败");
	};
	for(int i=0;i<FinalNeed.GetLength();i++){
		if(FinalNeed.GetAt(i)==']'){
			FinalNeed.Remove(FinalNeed.GetAt(i));
		}
	}
	return FinalNeed;
}
void CeBDFL10Dlg::DownloadImg(int page,CString per_ImgPath,CString mark,CString localPath){
	/********************************************\
		下载除去正文的部分，因为正文的页数不确定性较大
	\********************************************/
	CString per_ImgPath_Copy=per_ImgPath;
	CString localPath_Copy=localPath;

	for (int i=1;i<=page; i++){
		m_Progress.OffsetPos(1);
		per_ImgPath=per_ImgPath_Copy;
		localPath=localPath_Copy;
		CString temp01,temp02;
		temp01.Format("%d.jpg&uf=ssr&zoom=0",i);
		//per_ImgPath+=mark;
		if(i<10){
			per_ImgPath+=mark+"00";
		}else if(i<100){
			per_ImgPath+=mark+"0";
		}
		per_ImgPath+=temp01;//此时才获得图片完整的链接地址
		temp02.Format("%d.png",i);
		localPath+=temp02;//获得完整的存储路径信息
		HRESULT hr = URLDownloadToFile(NULL,per_ImgPath,localPath, 0, NULL);
		if (hr == S_OK){
			//将照片打印到pdf中
			ImgToPDF(p,localPath);
			//将图片删除
			DeleteFile(localPath);
			continue;
		}else{	
			AfxMessageBox("未知错误！！！");
		}
	}
}

void CeBDFL10Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	p=NULL;
	//int Left = 85, Top = 740, Right = a4_width - 85;
	//pdf对象创建  
    if ((p = PDF_new()) == (PDF *)0){
		AfxMessageBox("Couldn't create PDFlib object (out of memory)!n");
    }
    PDF_TRY(p){
        //先创建PDF文档
		CTime time=CTime::GetCurrentTime();
		CString pName=time.Format("%Y%m%d%H%M%S.pdf");
        if (PDF_begin_document(p,pName,0,"")==-1){
			CString temp;
			temp.Format("Error: %sn", PDF_get_errmsg(p));
			AfxMessageBox(temp);
        }


        






	CString url;
	CEdit* pEdit=(CEdit*)GetDlgItem(IDC_EDIT1);
	pEdit->GetWindowText(url);
	CString per_ImgPath;
	int textPage=0;
	int ProgressRange=0;
	CString per_ImgPath_Copy;

	m_Progress.ShowWindow(SW_SHOW);
	//m_Progress.SetBkColor(RGB(255, 0, 0));//背景色
	m_Progress.SetBarColor(RGB(0, 255, 0));//前景色

	textPage=URLToPage(url);//正文页数
	per_ImgPath=URLToImgPath(url);//图片的链接前部
	per_ImgPath_Copy=per_ImgPath;//图片的链接前部的副本

	
	CString Guide=URLToGuide (url);
	for(int i=0;i< Guide.GetLength();i++){
		ProgressRange+=(Guide.GetAt(i)-'0');
	}
	ProgressRange+=textPage;
	m_Progress.SetRange(1,ProgressRange);

	if(Guide.GetAt(0)!='0'){//下载封面页
		DownloadImg(Guide.GetAt(0)-'0',per_ImgPath,"cov",".\\cov");
	}
	if(Guide.GetAt(1)!='0'){//下载书名页
		DownloadImg(Guide.GetAt(1)-'0',per_ImgPath,"bok",".\\bok");
	}
	if(Guide.GetAt(2)!='0'){//下载版权页
		DownloadImg(Guide.GetAt(2)-'0',per_ImgPath,"leg",".\\leg");
	}
	if(Guide.GetAt(3)!='0'){//下载前言页
		DownloadImg(Guide.GetAt(3)-'0',per_ImgPath,"fow",".\\fow");
	}
	if(Guide.GetAt(4)!='0'){//下载目录页
		DownloadImg(Guide.GetAt(4)-'0',per_ImgPath,"!00",".\\con");
	}
	/******************************\
			下载正文部分
	\******************************/
	for (int i=1;i<=textPage; i++){
		m_Progress.OffsetPos(1);
		CString temp;
		per_ImgPath=per_ImgPath_Copy;
		if(i<10){
			temp.Format("00000%d.jpg&uf=ssr&zoom=0",i);
			per_ImgPath+=temp;
		}else if(i<100){
			temp.Format("0000%d.jpg&uf=ssr&zoom=0",i);
			per_ImgPath+=temp;
		}else if(i<1000){
			temp.Format("000%d.jpg&uf=ssr&zoom=0",i);
			per_ImgPath+=temp;
		}else if(i<10000){
			temp.Format("00%d.jpg&uf=ssr&zoom=0",i);
			per_ImgPath+=temp;
		}else if(i<100000){
			temp.Format("0%d.jpg&uf=ssr&zoom=0",i);
			per_ImgPath+=temp;
		}else if(i<1000000){
			temp.Format("%d.jpg&uf=ssr&zoom=0",i);
			per_ImgPath+=temp;
		}else{
			AfxMessageBox("页数有错");
		}
		CString localPath=".\\";//文件路径
		CString imgName;//文件名称
		imgName.Format("page%d.png",i);
		localPath+=imgName;
		HRESULT hr = URLDownloadToFile(NULL,per_ImgPath,localPath, 0, NULL);
		if (hr == S_OK){
			//将照片打印到pdf中
			//将图片删除
			ImgToPDF(p,localPath);
			DeleteFile(localPath);
			continue;
		}else{	
			AfxMessageBox("未知错误！！！");
		}
	}




	//pdf文档结束  
        PDF_end_document(p, "");
    }
    PDF_CATCH(p)//错误信息输出  
    {
        CString temp;
		temp.Format("[%d] %s: %sn", PDF_get_errmsg(p), PDF_get_apiname(p), PDF_get_errmsg(p));
		AfxMessageBox(temp);
		PDF_delete(p);
    }
    PDF_delete(p);
}
void CeBDFL10Dlg::ImgToPDF(PDF*p,CString localPath){
	//在创建PDF文档里面的页面，并填入页面的内容
	PDF_begin_page_ext(p, a4_width, a4_height, "");
	int img=PDF_load_image(p,"auto",localPath,0,"");
	PDF_fit_image(p,img, 0,0,"boxsize {595 842} fitmethod meet");
	PDF_close_image(p,img);
	//页结束  
	PDF_end_page_ext(p, "");
}

void CeBDFL10Dlg::OnEnChangeEdit1(){
	
}




