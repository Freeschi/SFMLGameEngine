// ====================================================================================================
// Includes
// ====================================================================================================
#include <iostream>
#include <stdint.h>
#include <Windows.h>
#include <cstdio>
#include "IniFile.h"

#pragma warning(disable: 4996) // blabla sprintf
using namespace std;

// ====================================================================================================
// Download File
// ====================================================================================================
struct DownloadThreadInfo
{
	std::string path;
	std::string saveas;
	bool bSuccess;
	bool bFinished;

	float progress;
	unsigned long size_downloaded;
	unsigned long size_total;
};
DownloadThreadInfo* DownloadFile(std::string filepath, std::string saveas);

// ====================================================================================================
// Utility
// ====================================================================================================
int GetFileRevision(std::string val);
#include "Utility.h"