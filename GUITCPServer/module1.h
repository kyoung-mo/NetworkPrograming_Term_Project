#pragma once
#ifndef MODULE1_H
#define MODULE1_H

#define BUFSIZE 512

// �޽��� ����ü ����
typedef struct {
    int type;              // �޽��� Ÿ�� (0: ä��)
    char id[20];           // ����� ID
    char data[BUFSIZE];    // �޽��� ����
} CHAT_MSG;

// �Լ� ����
void HandleChatMessage(SOCKET client_sock, struct sockaddr_in* clientaddr);

#endif // MODULE1_H