#pragma once
#ifndef MODULE1_H
#define MODULE1_H

#define BUFSIZE 512

// 채팅 메시지 구조체
typedef struct {
    int type;            // 0: 일반 채팅 메시지
    char id[20];         // 사용자 ID
    char data[BUFSIZE];  // 채팅 내용
} CHAT_MSG;

#endif // MODULE1_H
