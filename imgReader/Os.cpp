#include "stdafx.h"
#include "Os.h"


Os::Os()
{
}


Os::~Os()
{
}

BOOL Os::ShowFileDialog(FileDlgSel &selFile)
{
	BOOL open_state = TRUE;		    //��¼�Ի����״̬��TrueΪ�򿪣�FalseΪ����
	CString default_dir = _T("");	//Ĭ��Ŀ¼��
	CString defalut_path = _T("");	//Ĭ��·����
	CString filter = _T("ͼƬ�ļ� (*.bmp)|*.bmp||");

	// ��ѡ
	CFileDialog dlg(open_state, default_dir, defalut_path, OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, filter, NULL);
	dlg.m_ofn.lpstrTitle = _T("ѡ��ͼƬ�ļ�");

	if (dlg.DoModal() != IDOK)
	{
		return FALSE;
	}

	selFile.fileFullpath = dlg.GetPathName();
	selFile.fileName = dlg.GetFileName();
	selFile.fileExt = dlg.GetFileExt();

	return TRUE;
}

BOOL Os::ReadFile(CString &filePath, BitmapInfo &info)
{
	FILE *fp = NULL;
	int ret = fopen_s(&fp, filePath.GetBuffer(), "rb");
	if (fp == 0) {
		return FALSE;
	}
	BITMAPFILEHEADER fileheader = { 0 };
	fread(&fileheader, sizeof(fileheader), 1, fp);
	if (fileheader.bfType != 0x4D42)  // �ж��Ƿ�ΪBMPͼƬ
	{
		fclose(fp);
		return FALSE;
	}
	info.type = Bmp;
	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);
	info.width = head.biWidth;     //��ȡͼƬ�Ŀ�
	info.height = head.biHeight;   //��ȡͼƬ�Ŀ�
	info.bitCount = head.biBitCount;

	fclose(fp);
	return TRUE;
}
