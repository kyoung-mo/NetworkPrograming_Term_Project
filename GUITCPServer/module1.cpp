#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "module1.h"

// 외부 함수 정의 (GUITCPServer.cpp에서 실제 구현됨)
extern void DisplayText(const char* fmt, ...);
extern void DisplayError(const char* msg);

// 채팅 메시지 수신, 출력, 에코 처리
void HandleChatMessage(SOCKET client_sock, struct sockaddr_in* clientaddr)
{
    int retval;
    CHAT_MSG msg;
    char addr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientaddr->sin_addr, addr, sizeof(addr));

    // 수신
    retval = recv(client_sock, (char*)&msg, sizeof(msg), 0);
    if (retval <= 0) return;

    msg.id[19] = '\0';
    msg.data[BUFSIZE - 1] = '\0';

    // 메시지 출력
    DisplayText("[TCP/%s:%d] %s: %s\r\n",
        addr, ntohs(clientaddr->sin_port), msg.id, msg.data);

    // 클라이언트에게 에코
    retval = send(client_sock, (char*)&msg, sizeof(msg), 0);
    if (retval == SOCKET_ERROR) {
        DisplayError("send()");
    }
}