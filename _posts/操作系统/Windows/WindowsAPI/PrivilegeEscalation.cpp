/*
 * @Brief        : 
 * @Author       : dmjcb
 * @Date         : 2024-10-12 21:33:39
 * @LastEditors  : dmjcb@outlook.com
 * @LastEditTime : 2024-10-12 21:34:19
 */

#include <windows.h>
#include <iostream>

bool EnablePrivilege(LPCSTR privilege) {
    // 获取当前进程的访问令牌
    HANDLE hToken;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        return false;
    }

    // 获取特权的LUID
    LUID luid;
    if (!LookupPrivilegeValue(nullptr, privilege, &luid)) {
        CloseHandle(hToken);
        return false;
    }

    // 设置特权
    TOKEN_PRIVILEGES tp;
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), nullptr, nullptr)) {
        CloseHandle(hToken);
        return false;
    }

    CloseHandle(hToken);
    return true;
}

int main() {
    if (EnablePrivilege(SE_DEBUG_NAME)) {
        std::cout << "Privilege enabled." << std::endl;
    } else {
        std::cout << "Failed to enable privilege." << std::endl;
    }
    system("pause");
    return 0;
}