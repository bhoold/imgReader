#pragma once
#include "stdafx.h"



class Os
{
public:
	Os();
	~Os();
	static BOOL ShowFileDialog(FileDlgSel &selFile);
	static BOOL ReadFile(CString &filePath, BitmapInfo &info);
};

