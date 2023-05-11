#include "stdafx.h"
#include <cstdlib>

#include <Windows.h>
#include <immdev.h>

using namespace std;

int getInputMethod() {
	HWND hwnd = GetForegroundWindow(); //dll
	if (hwnd) {
		DWORD threadID = GetWindowThreadProcessId(hwnd, NULL); //dll
		HKL currentLayout = GetKeyboardLayout(threadID); //dll
		unsigned int x = (unsigned int)currentLayout & 0x0000FFFF;
		return ((int)x);
	}
	return 0;
}
void switchInputMethod(int locale) {
	HWND hwnd = GetForegroundWindow(); //dll
	LPARAM currentLayout = ((LPARAM)locale);
	PostMessage(hwnd, WM_INPUTLANGCHANGEREQUEST, 0, currentLayout); //dll
}

// API: https://learn.microsoft.com/en-us/previous-versions/aa913780(v=msdn.10)
// For  Microsoft Old Chinese IME(Win10 and Previous) :
//       0: English
//       1: Chinese
// For  Microsoft New Chinese IME(Win11) :
//       0: English / Half Shape
//       1: Chinese / Half Shape
//       1024: English / Full Shape (Bit10 and Bit1 used)
//       1025: Chinese / Full Shape
LRESULT getInputMode(){
    HWND foregroundWindow  = GetForegroundWindow(); 
    HWND foregroundIME = ImmGetDefaultIMEWnd(foregroundWindow);
    if(foregroundIME){
        LRESULT result = SendMessage(foregroundIME, WM_IME_CONTROL, 0x001, 0);
        return result;
    } else {
        return 0;
    }
}

void switchInputMode(LRESULT locale_mode){
    HWND foregroundWindow  = GetForegroundWindow(); 
    HWND foregroundIME = ImmGetDefaultIMEWnd(foregroundWindow);
    LPARAM currentMode = (LPARAM)locale_mode;
    SendMessage(foregroundIME, WM_IME_CONTROL, IMC_SETCONVERSIONMODE, currentMode);
}


int main(int argc, char** argv)
{
	if (argc == 1) {
		int imID = getInputMethod();
        int imMode = getInputMode();
		printf("%d %d\n", imID,imMode);
	} else if( argc == 2 ) {
		int locale = atoi(argv[1]);
		switchInputMethod(locale);
	} else {
		int locale = atoi(argv[1]);
		LRESULT locale_mode = atoi(argv[2]);
		switchInputMethod(locale);
		switchInputMode(locale_mode);
    }
	return 0;
}

