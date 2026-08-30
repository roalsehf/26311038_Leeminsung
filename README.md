# 26311038_Leeminsung_GameProject

## 과제 정보

- 학번: 26311038
- 이름: 이민성
- 영문 이름: Leeminsung
- 과목명: 게임프로그래밍
- 과제명: C++과 glc2d를 활용한 2D 게임 제작 프로젝트
- 개발 기간: 4주
- 개발 환경: Visual Studio 2022 Community, C++17, glc2d
- 버전 관리: Git, GitHub
- GitHub 저장소: https://github.com/roalsehf/26311038_Leeminsung_GameProject

## 게임 개요

- 게임 제목: DUNGEON DECK
- 장르: 턴제 덱빌딩 카드 RPG
- 핵심 목표: 카드를 사용해 3개 Stage를 진행하고 Dungeon Warden을 처치
- 시작 능력치: HP 50, Energy 3, 기본 손패 5장
- 시작 덱: Strike 5장, Guard 4장, Focus 1장

## 준비 자료

- Visual Studio 2022 Community: https://aka.ms/vs/17/release/vs_community.exe
- Microsoft.DXSDK.D3DX 9.29.952.8: https://www.nuget.org/packages/Microsoft.DXSDK.D3DX/9.29.952.8
- glc2d NuGet 패키지: https://www.nuget.org/packages/glc2d
- glc2d 라이브러리 소스: https://github.com/3dapi/glc2d_lib

## 1주차 개발 내용

- 과제 규칙에 맞는 Visual Studio C++ 솔루션과 프로젝트 구성
- NuGet을 이용한 glc2d 0.1.0.7 설치 및 복원 구성
- Microsoft.DXSDK.D3DX 9.29.952.8 설치 및 복원 구성
- glc2d 창 생성, 게임 루프, 키보드 입력, 글꼴 출력 구현
- DUNGEON DECK 메인 메뉴 구현
- W, S, 방향키를 사용한 메뉴 이동 구현
- Enter 선택과 Esc 이전 화면 또는 종료 기능 구현
- HOW TO PLAY 화면 구현
- 플레이어와 Training Goblin 정보가 표시되는 전투 미리보기 구현
- 4주 개발 계획과 전체 게임 규칙을 정리한 기획서 작성
- .gitignore를 적용하여 빌드 결과물과 사용자별 설정 파일 제외
- Debug와 Release, x86과 x64 빌드 확인

## 프로젝트 구성

- 26311038_Leeminsung_GameProject.sln: Visual Studio 솔루션
- 26311038_Leeminsung_GameProject/26311038_Leeminsung_GameProject.vcxproj: C++ 프로젝트
- 26311038_Leeminsung_GameProject/main.cpp: 게임 소스 코드
- 26311038_Leeminsung_GameProject/packages.config: NuGet 패키지 정보
- .gitignore: Git 제외 파일 규칙
- docs/GAME_DESIGN.md: DUNGEON DECK 게임 기획서
- docs/WEEK1_SUBMISSION_GUIDE.md: 1주차 제출 방법

## 실행 방법

1. 26311038_Leeminsung_GameProject.sln을 Visual Studio 2022로 엽니다.
2. 솔루션을 우클릭하고 NuGet 패키지 복원을 선택합니다.
3. 구성을 Debug, 플랫폼을 x64로 선택합니다.
4. Ctrl+Shift+B를 눌러 빌드합니다.
5. Ctrl+F5를 눌러 실행합니다.

## 조작 방법

- 메뉴 이동: W, S 또는 위, 아래 방향키
- 선택: Enter
- 이전 화면 또는 종료: Esc

1주차 프로토타입에서는 GAME START를 선택하면 전투 미리보기 화면이 열린다. 실제 카드 드로우와 전투 로직은 기획서의 주차별 개발 계획에 따라 이후 Commit에서 구현한다.

## 1주차 제출 정보

- 저장소 이름: 26311038_Leeminsung_GameProject
- 프로젝트 이름: 26311038_Leeminsung_GameProject
- Git Tag: 26311038_Leeminsung_GameProject_w01

Tag 생성, Push, 날짜 캡처, ZIP 생성 방법은 docs/WEEK1_SUBMISSION_GUIDE.md에서 확인할 수 있습니다.
