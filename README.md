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
- 방향키 또는 WASD로 플레이어를 움직이는 초기 게임 프로토타입 구현
- 목표 도달 판정과 점수 증가 기능 구현
- .gitignore를 적용하여 빌드 결과물과 사용자별 설정 파일 제외
- Debug와 Release, x86과 x64 빌드 확인

## 프로젝트 구성

- 26311038_Leeminsung_GameProject.sln: Visual Studio 솔루션
- 26311038_Leeminsung_GameProject/26311038_Leeminsung_GameProject.vcxproj: C++ 프로젝트
- 26311038_Leeminsung_GameProject/main.cpp: 게임 소스 코드
- 26311038_Leeminsung_GameProject/packages.config: NuGet 패키지 정보
- .gitignore: Git 제외 파일 규칙
- docs/WEEK1_SUBMISSION_GUIDE.md: 1주차 제출 방법

## 실행 방법

1. 26311038_Leeminsung_GameProject.sln을 Visual Studio 2022로 엽니다.
2. 솔루션을 우클릭하고 NuGet 패키지 복원을 선택합니다.
3. 구성을 Debug, 플랫폼을 x64로 선택합니다.
4. Ctrl+Shift+B를 눌러 빌드합니다.
5. Ctrl+F5를 눌러 실행합니다.

## 조작 방법

- 이동: 방향키 또는 W, A, S, D
- 점수 초기화: R
- 종료: Esc

## 1주차 제출 정보

- 저장소 이름: 26311038_Leeminsung_GameProject
- 프로젝트 이름: 26311038_Leeminsung_GameProject
- Git Tag: 26311038_Leeminsung_GameProject_w01

Tag 생성, Push, 날짜 캡처, ZIP 생성 방법은 docs/WEEK1_SUBMISSION_GUIDE.md에서 확인할 수 있습니다.
