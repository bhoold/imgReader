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
	BOOL open_state = TRUE;		    //记录对话框打开状态，True为打开，False为保存
	CString default_dir = _T("");	//默认目录名
	CString defalut_path = _T("");	//默认路径名
	CString filter = _T("图片文件 (*.bmp)|*.bmp||");

	// 单选
	CFileDialog dlg(open_state, default_dir, defalut_path, OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, filter, NULL);
	dlg.m_ofn.lpstrTitle = _T("选择图片文件");

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
	if (fileheader.bfType != 0x4D42)  // 判断是否为BMP图片
	{
		fclose(fp);
		return FALSE;
	}
	info.type = Bmp;
	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);
	info.width = head.biWidth;     //获取图片的宽
	info.height = head.biHeight;   //获取图片的宽
	info.bitCount = head.biBitCount;

	fclose(fp);
	return TRUE;
}
