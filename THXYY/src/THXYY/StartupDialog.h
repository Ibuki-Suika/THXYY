#ifndef STARTUP_DIALOG_H
#define STARTUP_DIALOG_H

#include <Windows.h>

class GameConfig;

class StartupDialog
{
private:
	static GameConfig* config;

private:
	static INT_PTR CALLBACK StartupDialogFunc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

public:
	StartupDialog(GameConfig& config);
	bool Show();
};

#endif
