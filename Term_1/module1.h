#pragma once
#ifndef MODULE1_H
#define MODULE1_H

#define BUFSIZE 512

// ä�� �޽��� ����ü
typedef struct {
    int type;            // 0: �Ϲ� ä�� �޽���
    char id[20];         // ����� ID
    char data[BUFSIZE];  // ä�� ����
} CHAT_MSG;

#endif // MODULE1_H
