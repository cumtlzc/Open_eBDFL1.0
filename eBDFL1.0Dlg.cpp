
// eBDFL1.0Dlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CeBDFL10Dlg �Ի���



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


// CeBDFL10Dlg ��Ϣ�������

BOOL CeBDFL10Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CeBDFL10Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		CHttpFile* hF= (CHttpFile*)mysession.OpenURL(url); //����ַ
		CString strData,strAllData;
		bool m_begin=false;
		while(hF->ReadString(strData)){ //��ȡ����
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
		AfxMessageBox("��ȡ����ʧ��");
	};
	return page=_ttoi(FinalNeed.TrimLeft("= "));
}
CString CeBDFL10Dlg::URLToImgPath(CString url){
	/******************************\
		ͨ��URL��ȡ��ҳ��Դ����Ϣ
	\******************************/
	CString FinalNeed;
	CString NeedText;
	bool flag=false;
	bool flag01=false;
	int count=0;

	try{
		CInternetSession mysession; 
		CHttpFile* hF= (CHttpFile*)mysession.OpenURL(url); //����ַ
		CString strData,strAllData;
		bool m_begin=false;
		while(hF->ReadString(strData)){ //��ȡ����
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
		AfxMessageBox("��ȡ����ʧ��");
	};
	return FinalNeed;
}
CString CeBDFL10Dlg::URLToGuide (CString url){
	/******************************\
		ͨ��URL��ȡ��ҳ��Դ����Ϣ
	\******************************/
	CString FinalNeed;
	CString NeedText;
	bool flag=false;
	bool flag01=false;
	int count=0;

	try{
		CInternetSession mysession; 
		CHttpFile* hF= (CHttpFile*)mysession.OpenURL(url); //����ַ
		CString strData,strAllData;
		bool m_begin=false;
		while(hF->ReadString(strData)){ //��ȡ����
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
		AfxMessageBox("��ȡ����ʧ��");
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
		���س�ȥ���ĵĲ��֣���Ϊ���ĵ�ҳ����ȷ���Խϴ�
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
		per_ImgPath+=temp01;//��ʱ�Ż��ͼƬ���������ӵ�ַ
		temp02.Format("%d.png",i);
		localPath+=temp02;//��������Ĵ洢·����Ϣ
		HRESULT hr = URLDownloadToFile(NULL,per_ImgPath,localPath, 0, NULL);
		if (hr == S_OK){
			//����Ƭ��ӡ��pdf��
			ImgToPDF(p,localPath);
			//��ͼƬɾ��
			DeleteFile(localPath);
			continue;
		}else{	
			AfxMessageBox("δ֪���󣡣���");
		}
	}
}

void CeBDFL10Dlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	p=NULL;
	//int Left = 85, Top = 740, Right = a4_width - 85;
	//pdf���󴴽�  
    if ((p = PDF_new()) == (PDF *)0){
		AfxMessageBox("Couldn't create PDFlib object (out of memory)!n");
    }
    PDF_TRY(p){
        //�ȴ���PDF�ĵ�
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
	//m_Progress.SetBkColor(RGB(255, 0, 0));//����ɫ
	m_Progress.SetBarColor(RGB(0, 255, 0));//ǰ��ɫ

	textPage=URLToPage(url);//����ҳ��
	per_ImgPath=URLToImgPath(url);//ͼƬ������ǰ��
	per_ImgPath_Copy=per_ImgPath;//ͼƬ������ǰ���ĸ���

	
	CString Guide=URLToGuide (url);
	for(int i=0;i< Guide.GetLength();i++){
		ProgressRange+=(Guide.GetAt(i)-'0');
	}
	ProgressRange+=textPage;
	m_Progress.SetRange(1,ProgressRange);

	if(Guide.GetAt(0)!='0'){//���ط���ҳ
		DownloadImg(Guide.GetAt(0)-'0',per_ImgPath,"cov",".\\cov");
	}
	if(Guide.GetAt(1)!='0'){//��������ҳ
		DownloadImg(Guide.GetAt(1)-'0',per_ImgPath,"bok",".\\bok");
	}
	if(Guide.GetAt(2)!='0'){//���ذ�Ȩҳ
		DownloadImg(Guide.GetAt(2)-'0',per_ImgPath,"leg",".\\leg");
	}
	if(Guide.GetAt(3)!='0'){//����ǰ��ҳ
		DownloadImg(Guide.GetAt(3)-'0',per_ImgPath,"fow",".\\fow");
	}
	if(Guide.GetAt(4)!='0'){//����Ŀ¼ҳ
		DownloadImg(Guide.GetAt(4)-'0',per_ImgPath,"!00",".\\con");
	}
	/******************************\
			�������Ĳ���
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
			AfxMessageBox("ҳ���д�");
		}
		CString localPath=".\\";//�ļ�·��
		CString imgName;//�ļ�����
		imgName.Format("page%d.png",i);
		localPath+=imgName;
		HRESULT hr = URLDownloadToFile(NULL,per_ImgPath,localPath, 0, NULL);
		if (hr == S_OK){
			//����Ƭ��ӡ��pdf��
			//��ͼƬɾ��
			ImgToPDF(p,localPath);
			DeleteFile(localPath);
			continue;
		}else{	
			AfxMessageBox("δ֪���󣡣���");
		}
	}




	//pdf�ĵ�����  
        PDF_end_document(p, "");
    }
    PDF_CATCH(p)//������Ϣ���  
    {
        CString temp;
		temp.Format("[%d] %s: %sn", PDF_get_errmsg(p), PDF_get_apiname(p), PDF_get_errmsg(p));
		AfxMessageBox(temp);
		PDF_delete(p);
    }
    PDF_delete(p);
}
void CeBDFL10Dlg::ImgToPDF(PDF*p,CString localPath){
	//�ڴ���PDF�ĵ������ҳ�棬������ҳ�������
	PDF_begin_page_ext(p, a4_width, a4_height, "");
	int img=PDF_load_image(p,"auto",localPath,0,"");
	PDF_fit_image(p,img, 0,0,"boxsize {595 842} fitmethod meet");
	PDF_close_image(p,img);
	//ҳ����  
	PDF_end_page_ext(p, "");
}

void CeBDFL10Dlg::OnEnChangeEdit1(){
	
}




