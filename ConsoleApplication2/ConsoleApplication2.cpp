//没有运行提示，win10的气泡提示好复杂，msgbox又太烦
#include <iostream>
#include <Windows.h>
using namespace std;
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
int main()
{

    // 注册两个热键 Ctrl+F1 , Ctrl+F2
    if (0 == RegisterHotKey(NULL, 1, MOD_CONTROL, VK_F1)) {
        cout << "RegisterHotKey error : " << GetLastError() << endl;

    }
    if (0 == RegisterHotKey(NULL, 2, MOD_CONTROL, VK_F2)) {
        cout << "RegisterHotKey error : " << GetLastError() << endl;

    }
    // 消息循环
    bool f = false;
    HWND hwnd = GetForegroundWindow();//获取最前端的窗口的句柄 
    ShowWindow(hwnd, f);
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {

        switch (msg.message) {
        case WM_HOTKEY:
        {
            if (1 == msg.wParam) {
                DEVMODE dm;
                // initialize the DEVMODE structure
                ZeroMemory(&dm, sizeof(dm));
                dm.dmSize = sizeof(dm);
                if (0 != EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm))
                {
                    // swap height and width
                    DWORD dwTemp = dm.dmPelsHeight;
                    dm.dmPelsHeight = dm.dmPelsWidth;
                    dm.dmPelsWidth = dwTemp;
                    // determine new orientaion
                    switch (dm.dmDisplayOrientation)
                    {
                    case DMDO_DEFAULT:
                        dm.dmDisplayOrientation = DMDO_270;
                        break;
                    case DMDO_270:
                        dm.dmDisplayOrientation = DMDO_DEFAULT;
                        break;//旋转角度
                    default:
                        // unknown orientation value
                        // add exception handling here
                        break;
                    }
                    long lRet = ChangeDisplaySettings(&dm, 0);
                    if (DISP_CHANGE_SUCCESSFUL != lRet)
                    {
                        // add exception handling here
                    }

                }
            }

            else if (2 == msg.wParam) {
                cout << "2" << endl;
                UnregisterHotKey(NULL, 1);
                UnregisterHotKey(NULL, 2);//取消注册的热键
                return 0;
            }

            break;
        }

        default:
            break;
        }

    }

    cout << "finished." << endl;
    return 0;
}
