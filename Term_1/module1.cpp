#include "..\\..\\Common.h"
#include "module1.h"
#include "resource.h"

// ���� ����
extern SOCKET sock;
extern HWND hEditRecv, hEditSend, hButtonSend;
extern HANDLE hReadEvent, hWriteEvent;
extern char buf[BUFSIZE + 1];

static bool isFirstMessage = true;
static char userID[20] = "";

// ä�� �޽��� �۽� ó��
void HandleChatSend(HWND hDlg)
{
    GetDlgItemTextA(hDlg, IDC_EDIT_SEND, buf, BUFSIZE);
    if (strlen(buf) == 0) {
        SetEvent(hReadEvent);
        return;
    }

    // ù �޽����� ID�� ���
    if (isFirstMessage) {
        strncpy(userID, buf, sizeof(userID));
        DisplayText(hEditRecv, "[SYSTEM] ID�� ��ϵ�: %s\r\n", userID);
        SetDlgItemTextA(hDlg, IDC_EDIT_SEND, "");
        isFirstMessage = false;
        EnableWindow(hButtonSend, TRUE);
        SetEvent(hReadEvent);
        return;
    }

    CHAT_MSG msg;
    msg.type = 0;
    strncpy(msg.id, userID, sizeof(msg.id));
    strncpy(msg.data, buf, sizeof(msg.data));

    int retval = send(sock, (char*)&msg, sizeof(msg), 0);
    if (retval == SOCKET_ERROR) {
        DisplayError(hEditRecv, "send()");
        return;
    }

    DisplayText(hEditRecv, "[%s] %s\r\n", msg.id, msg.data);
    SetDlgItemTextA(hDlg, IDC_EDIT_SEND, "");
    EnableWindow(hButtonSend, TRUE);
    SetEvent(hReadEvent);
}

// ä�� �޽��� ���� ó��
void HandleChatRecv()
{
    CHAT_MSG msg;
    int retval = recv(sock, (char*)&msg, sizeof(msg), 0);
    if (retval <= 0) return;

    msg.data[BUFSIZE - 1] = '\0';
    msg.id[19] = '\0';

    DisplayText(hEditRecv, "[%s] %s\r\n", msg.id, msg.data);
}
