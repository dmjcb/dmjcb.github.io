#include <stdio.h>
#include <windows.h>

int main() {
    // 打开串口
    // --------------------------------------------------------------------------------------------------------
    HANDLE handle;
    handle = CreateFileA("COM1", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (handle == INVALID_HANDLE_VALUE) {
        printf("无法打开串口\n");
        return 1;
    }
    // --------------------------------------------------------------------------------------------------------

    // 设置串口参数
    // --------------------------------------------------------------------------------------------------------
    DCB comParam = {0};
    comParam.DCBlength = sizeof(comParam);
    if (!GetCommState(handle, &comParam)) {
        printf("获取串口状态失败\n");

        CloseHandle(handle);
        return 1;
    }
    // 波特率
    comParam.BaudRate = CBR_9600;
    // 数据位
    comParam.ByteSize = 8;
    // 停止位
    comParam.StopBits = ONESTOPBIT;
    // 校验位
    comParam.Parity = NOPARITY;
    if (!SetCommState(handle, &comParam)) {
        printf("设置串口状态失败\n");

        CloseHandle(handle);
        return 1;
    }
    // --------------------------------------------------------------------------------------------------------

    // 设置超时
    // --------------------------------------------------------------------------------------------------------
    COMMTIMEOUTS comTime = {0};
    comTime.ReadIntervalTimeout = 50;
    comTime.ReadTotalTimeoutConstant = 50;
    comTime.ReadTotalTimeoutMultiplier = 10;
    comTime.WriteTotalTimeoutConstant = 50;
    comTime.WriteTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(handle, &comTime)) {
        printf("设置超时失败\n");
        CloseHandle(handle);
        return 1;
    }
    // --------------------------------------------------------------------------------------------------------

    // 向串口发送数据
    // --------------------------------------------------------------------------------------------------------
    DWORD bytesWritten;
    char data[] = "Hello, Serial!";
    if (!WriteFile(handle, data, sizeof(data), &bytesWritten, NULL)) {
        printf("写入数据失败\n");
        CloseHandle(handle);
        return 1;
    }
    // --------------------------------------------------------------------------------------------------------

    // 从串口读取数据
    // --------------------------------------------------------------------------------------------------------
    DWORD bytesRead;
    char buffer[100];
    if (!ReadFile(handle, buffer, sizeof(buffer), &bytesRead, NULL)) {
        printf("读取数据失败\n");
        CloseHandle(handle);
        return 1;
    }

    printf("接收到的数据: %s\n", buffer);
    // --------------------------------------------------------------------------------------------------------

    // 关闭串口
    // --------------------------------------------------------------------------------------------------------
    CloseHandle(handle);
    // --------------------------------------------------------------------------------------------------------
    return 0;
}
