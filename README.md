# 네프실 Term Project - Network Programming

## 📌 프로젝트 개요
이 프로젝트는 **윈도우 기반 네트워크 프로그래밍** 수업의 기말 프로젝트로, 다양한 네트워크 기능을 구현한 **TCP/UDP 기반 서버-클라이언트 시스템**입니다.

- **과목**: 네트워크 프로그래밍
- **목표**: 채팅, 파일 전송, UDP 1:1 대화, 계산기 등 다양한 기능을 구현
- **UI**: GUI 기반 (윈도우 대화상자 기반)

## 📁 디렉토리 구조
├── Client/

│ ├── Client_main.cpp # 클라이언트 진입점

│ ├── TCPClient_FixedVariable.cpp

│ ├── TCPClient_Variable.cpp

│ ├── UDPClient.cpp

│ └── resource.h

├── Server/

│ ├── GUITCPServer.cpp # GUI 기반 TCP 서버

│ ├── TCPServer_FixedVariable.cpp

│ ├── TCPServer_Variable.cpp

│ ├── NonblockTCPServer.cpp

│ ├── SelectTCPServer.cpp

│ ├── UDPServer.cpp

│ └── DlgApp.cpp

├── Common/

│ └── Common.h # 공통 유틸 및 윈속 초기화


## ✅ 구현 기능 목록

| 항목 | 기능 | 상태 |
|------|------|------|
| 1 | 채팅 메시지에 사용자 ID 포함 | ✅ |
| 2 | 고정+가변 길이 메시지 전송 방식 적용 | ✅ |
| 3 | 다자간(3명 이상) 채팅 지원 | ✅ |
| 4 | 신규 접속자에게 이전 채팅 이력 복원 | ✅ |
| 5 | 텍스트/바이너리 파일 전송 기능 | ✅ |
| 6 | 서버 넌블로킹 소켓 처리 | ✅ |
| 7 | UDP 기반 1:1 비밀 대화 | ✅ |
| 8 | 계산기 서버 기능 (수식 계산) | ✅ |
| 9 | 디버깅 모드 지원 (/d 옵션) | ✅ |
| 10 | 기타 기능: GUI 기반 설정/전송, 포트/IP 설정 | ✅ |

## 🛠️ 사용 기술
- **언어**: C / C++ (Windows API 사용)
- **통신 방식**: TCP / UDP
- **GUI**: Win32 API (DialogBox, Edit Control 등)
- **비동기 처리**: `CreateThread`, `CriticalSection`, `Event`, `Select()`, 넌블로킹 소켓 등

## 🚀 실행 방법

### 서버
```bash
# 기본 실행
Server.exe

# 디버깅 모드
Server.exe /d

클라이언트
Client.exe
# 실행 후 IP, Port, ID 입력 → 접속

💡 주요 설계 포인트
모든 메시지는 CHAT_MSG 또는 전용 구조체를 기반으로 처리

공통 코드(Common.h)를 통해 오류 처리 및 초기화 일관성 유지

기능별 파일로 철저하게 모듈화 (main.cpp에서 호출만 담당)

채팅 외에도 파일 전송/계산기/UDP 통신을 통합 처리

🧪 테스트 기준
다자간 채팅 정상 작동 여부

ID 포함 메시지 전송 확인

파일(.txt, .jpg 등) 정상 수신

UDP 비밀 대화 동작 확인

서버 디버깅 로그 확인

