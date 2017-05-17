#include "StartupDialog.h"
#include "GameConfig.h"
#include "../../resource.h"
#include <windowsx.h>

GameConfig* StartupDialog::config = nullptr;

StartupDialog::StartupDialog(GameConfig& config)
{
	StartupDialog::config = &config;
}

bool StartupDialog::Show()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	if (DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_DISPLAY_MODE), NULL, StartupDialogFunc) == IDCANCEL)
	{
		return false;
	}
	return true;
}

INT_PTR CALLBACK StartupDialog::StartupDialogFunc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		//center the dialog
		RECT rc;
		GetWindowRect(hDlg, &rc);
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;
		int screen_width = GetSystemMetrics(SM_CXSCREEN);
		int screen_height = GetSystemMetrics(SM_CYSCREEN);
		MoveWindow(hDlg, (screen_width - width) / 2, (screen_height - height) / 2, width, height, TRUE);

		//set initial states of the controls according to GameConfig
		switch (config->startupType)
		{
		case GameConfig::StartupType::FULL_SCREEN_640_480:
			CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
			break;
		case GameConfig::StartupType::WINDOW_640_480:
			CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
			break;
		default:
			throw std::logic_error("not implemented");
		}
		Button_SetCheck(GetDlgItem(hDlg, IDC_CHECK1), BST_CHECKED);

		return (INT_PTR)TRUE;
	}

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		switch (LOWORD(wParam))
		{
		case IDC_RADIO1:
			config->startupType = GameConfig::StartupType::FULL_SCREEN_640_480;
			break;
		case IDC_RADIO2:
			config->startupType = GameConfig::StartupType::WINDOW_640_480;
			break;
		case IDC_CHECK1:
			config->askEveryTime = !config->askEveryTime;
			break;
		default:
			throw std::logic_error("not implemented");
		}

		return (INT_PTR)TRUE;
		break;
	}
	return (INT_PTR)FALSE;
}