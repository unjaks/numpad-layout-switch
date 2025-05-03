#include <windows.h>
#include <winuser.h>
#include <map>

std::map<char, int> numpadMap = {
    {'0', VK_NUMPAD0},
    {'1', VK_NUMPAD1},
    {'2', VK_NUMPAD2},
    {'3', VK_NUMPAD3},
    {'4', VK_NUMPAD4},
    {'5', VK_NUMPAD5},
    {'6', VK_NUMPAD6},
    {'7', VK_NUMPAD7},
    {'8', VK_NUMPAD8},
    {'9', VK_NUMPAD9},
    {'.', VK_DECIMAL},
    {'+', VK_ADD},
    {'-', VK_SUBTRACT},
    {'*', VK_MULTIPLY},
    {'/', VK_DIVIDE},
    {'\r', VK_RETURN}
};

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKey = (KBDLLHOOKSTRUCT*)lParam;
        bool capsLockOn = (GetKeyState(VK_CAPITAL) & 0x0001) != 0;
        if (capsLockOn) {
            BYTE keyboardState[256];
            GetKeyboardState(keyboardState);
            char keyChar = MapVirtualKey(pKey->vkCode, MAPVK_VK_TO_CHAR);
            if (numpadMap.find(keyChar) != numpadMap.end()) {
                if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                    keybd_event(numpadMap[keyChar], 0, 0, 0);
                    return 1;
                }
                else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
                    keybd_event(numpadMap[keyChar], 0, KEYEVENTF_KEYUP, 0);
                    return 1;
                }
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (keyboardHook == NULL) {
        MessageBox(NULL, L"hook installation failed!", L"Error", MB_ICONERROR);
        return 1;
    }
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(keyboardHook);
    return 0;
}