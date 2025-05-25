#include "..\\..\\Common.h"
#include "resource.h"
#include "module1.h"  // CHAT_MSG 구조체 정의

#define BUFSIZE 512

// 전역 변수
SOCKET sock;
char buf[BUFSIZE + 1];
HANDLE hReadEvent, hWriteEvent;
HWND hEditRecv, hEditSend, hButtonSend;
char serverIP[16] = "127.0.0.1";
int serverPort = 9000;
char userID[20] = "";  // ID 저장

DWORD WINAPI ClientThread(LPVOID);
void DisplayText(HWND hEdit, const char* fmt, ...);
void DisplayError(HWND hEdit, const char* msg);

// 대화상자 프로시저
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_INITDIALOG:
        hEditRecv = GetDlgItem(hDlg, IDC_EDIT_RECV);
        hEditSend = GetDlgItem(hDlg, IDC_EDIT_SEND);
        hButtonSend = GetDlgItem(hDlg, IDC_BUTTON_SEND);
        hReadEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
        hWriteEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_BUTTON_SET:
            GetDlgItemTextA(hDlg, IDC_EDIT_IP, serverIP, sizeof(serverIP));
            char portStr[6];
            GetDlgItemTextA(hDlg, IDC_EDIT_PORT, portStr, sizeof(portStr));
            GetDlgItemTextA(hDlg, IDC_EDIT_ID, userID, sizeof(userID));
            serverPort = atoi(portStr);
            CreateThread(NULL, 0, ClientThread, hDlg, 0, NULL);
            break;

        case IDC_BUTTON_RESET:
            SetDlgItemTextA(hDlg, IDC_EDIT_IP, "");
            SetDlgItemTextA(hDlg, IDC_EDIT_PORT, "");
            SetDlgItemTextA(hDlg, IDC_EDIT_ID, "");
            SetDlgItemTextA(hDlg, IDC_EDIT_SEND, "");
            SetDlgItemTextA(hDlg, IDC_EDIT_RECV, "");
            break;

        case IDC_BUTTON_SEND:
            EnableWindow(hButtonSend, FALSE);
            WaitForSingleObject(hReadEvent, INFINITE);
            GetDlgItemTextA(hDlg, IDC_EDIT_SEND, buf, BUFSIZE);
            SetEvent(hWriteEvent);
            break;

        case IDC_BUTTON_EXIT:
            EndDialog(hDlg, 0);
            break;
        }
        break;

    case WM_CLOSE:
        EndDialog(hDlg, 0);
        break;
    }
    return FALSE;
}

// 클라이언트 스레드
DWORD WINAPI ClientThread(LPVOID param) {
    HWND hDlg = (HWND)param;
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        DisplayError(hEditRecv, "socket()");
        return 1;
    }

    SOCKADDR_IN serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(serverIP);
    serveraddr.sin_port = htons(serverPort);
    if (connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR) {
        DisplayError(hEditRecv, "connect()");
        return 1;
    }

    int retval;
    while (1) {
        WaitForSingleObject(hWriteEvent, INFINITE);

        if (strlen(buf) == 0) {
            EnableWindow(hButtonSend, TRUE);
            SetEvent(hReadEvent);
            continue;
        }

        // 메시지 구조체 구성
        CHAT_MSG msg;
        msg.type = 0;
        strncpy(msg.id, userID, sizeof(msg.id));
        strncpy(msg.data, buf, sizeof(msg.data));

        // 전송
        retval = send(sock, (char*)&msg, sizeof(msg), 0);
        if (retval == SOCKET_ERROR) {
            DisplayError(hEditRecv, "send()");
            break;
        }

        DisplayText(hEditRecv, "[%s] %s\r\n", msg.id, msg.data);

        // 수신
        retval = recv(sock, (char*)&msg, sizeof(msg), 0);
        if (retval <= 0) break;

        msg.id[19] = '\0';
        msg.data[BUFSIZE - 1] = '\0';
        DisplayText(hEditRecv, "[%s] %s\r\n", msg.id, msg.data);

        EnableWindow(hButtonSend, TRUE);
        SetEvent(hReadEvent);
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}

// 출력 함수
void DisplayText(HWND hEdit, const char* fmt, ...) {
    char msg[BUFSIZE * 2];
    va_list args;
    va_start(args, fmt);
    vsprintf(msg, fmt, args);
    va_end(args);
    int len = GetWindowTextLength(hEdit);
    SendMessage(hEdit, EM_SETSEL, len, len);
    SendMessageA(hEdit, EM_REPLACESEL, FALSE, (LPARAM)msg);
}

// 에러 출력 함수
void DisplayError(HWND hEdit, const char* msg) {
    LPVOID lpMsgBuf;
    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&lpMsgBuf, 0, NULL);
    DisplayText(hEdit, "[%s] %s\r\n", msg, (char*)lpMsgBuf);
    LocalFree(lpMsgBuf);
}

// 진입점
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    return (int)DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}