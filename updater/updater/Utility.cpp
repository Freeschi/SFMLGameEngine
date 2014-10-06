// ====================================================================================================
// Includes
// ====================================================================================================
#include "Updater.h"

// ====================================================================================================
// Readable File Size
// ====================================================================================================
std::string readable_fs(unsigned long bytes)
{
	char ext[64];
	if (bytes < 1024)
		sprintf(ext, "%i bytes", bytes);
	else if (bytes < 1048576)
		sprintf(ext, "%lu kb", bytes / 1024);
	else
		sprintf(ext, "%.2f mb", (float) ((double)bytes / (double)1048576));

	return std::string(ext);
}

// ====================================================================================================
// File Exists check
// ====================================================================================================
bool file_exists(const std::string& name) 
{
	if (FILE *file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}

// ====================================================================================================
// Clear Console
// ====================================================================================================
void ClearConsole()
{
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
	SetConsoleCursorPosition(console, topLeft);
}