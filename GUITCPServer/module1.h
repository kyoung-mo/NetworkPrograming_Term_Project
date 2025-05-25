#pragma once
#ifndef MODULE1_H
#define MODULE1_H

#define BUFSIZE 512

// 메시지 구조체 정의
typedef struct {
    int type;              // 메시지 타입 (0: 채팅)
    char id[20];           // 사용자 ID
    char data[BUFSIZE];    // 메시지 내용
} CHAT_MSG;

// 함수 선언
void HandleChatMessage(SOCKET client_sock, struct sockaddr_in* clientaddr);

#endif // MODULE1_H