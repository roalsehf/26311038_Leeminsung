# 1주차 제출 방법

이 문서는 26311038_Leeminsung_GameProject의 1주차 제출 절차를 정리한 안내서입니다.

## 현재 준비된 항목

- 저장소와 프로젝트에 사용할 이름을 26311038_Leeminsung_GameProject로 통일했습니다.
- Visual Studio 2022 C++ 솔루션과 프로젝트 파일을 준비했습니다.
- glc2d와 Microsoft.DXSDK.D3DX NuGet 복원 설정을 준비했습니다.
- glc2d를 사용하는 초기 게임 화면과 게임 코드를 작성했습니다.
- .gitignore와 .gitattributes를 준비했습니다.
- README에 학번, 이름, 과목명, 과제명, 저장소 주소를 작성했습니다.
- Debug와 Release, x86과 x64 구성을 빌드했습니다.
- 제출용 로컬 Commit을 준비했습니다.

## GitHub 저장소 이름 변경

현재 GitHub 저장소 이름은 26311038_Leeminsung입니다. 과제 규칙에 맞게 다음 작업을 한 번 수행해야 합니다.

1. https://github.com/roalsehf/26311038_Leeminsung 을 엽니다.
2. Settings를 선택합니다.
3. General의 Repository name을 26311038_Leeminsung_GameProject로 변경합니다.
4. Rename을 선택합니다.

로컬 origin 주소는 변경될 저장소 이름에 맞춰 설정되어 있습니다.

## Visual Studio 최종 확인

1. 26311038_Leeminsung_GameProject.sln을 엽니다.
2. 솔루션을 우클릭하고 NuGet 패키지 복원을 선택합니다.
3. Debug와 x64를 선택합니다.
4. 솔루션 다시 빌드를 실행합니다.
5. 오류가 0개인지 확인합니다.
6. Ctrl+F5로 게임을 실행합니다.
7. 방향키 또는 WASD 이동, 목표 도달 시 점수 증가, R 초기화, Esc 종료를 확인합니다.

사용 패키지는 다음과 같습니다.

- glc2d 0.1.0.7
- Microsoft.DXSDK.D3DX 9.29.952.8

packages 폴더는 Git에 저장하지 않습니다. Clone한 PC에서는 packages.config를 기준으로 NuGet이 패키지를 복원합니다.

## Tag 생성과 Push

GitHub 저장소 이름을 변경한 후 PowerShell에서 다음 명령을 실행합니다.

```powershell
cd "C:\Users\처음사용자\26311038_Leeminsung"
git tag -a 26311038_Leeminsung_GameProject_w01 -m "Week 01 submission"
git push origin main 26311038_Leeminsung_GameProject_w01
```

기존 projet1 Tag는 요구 형식이 아니지만 이미 원격 저장소에 올라가 있습니다. 기록을 임의로 변경하지 않기 위해 삭제하지 않고 올바른 w01 Tag를 새로 추가합니다.

## Tag와 Commit 확인

다음 명령으로 Tag가 현재 제출용 Commit을 가리키는지 확인합니다.

```powershell
git status
git show --no-patch --format=fuller 26311038_Leeminsung_GameProject_w01
git ls-remote --tags origin
```

git status 결과가 working tree clean이면 정상입니다.

## Tag 생성 날짜 캡처

다음 내용이 보이도록 화면을 캡처합니다.

1. PowerShell에서 git show 결과와 Tag 이름
2. GitHub Tags 화면의 Tag 이름과 연결된 Commit
3. PC 화면의 날짜와 시간

## Tag 기준 ZIP 생성

다음 명령을 실행하면 1주차 Tag가 가리키는 파일만 ZIP에 포함됩니다.

```powershell
git archive --format=zip --output="..\26311038_Leeminsung_GameProject_w01.zip" 26311038_Leeminsung_GameProject_w01
```

생성 파일은 다음 위치에 있습니다.

```text
C:\Users\처음사용자\26311038_Leeminsung_GameProject_w01.zip
```

ZIP 내부에 다음 파일이 있는지 확인합니다.

- 26311038_Leeminsung_GameProject.sln
- 26311038_Leeminsung_GameProject/26311038_Leeminsung_GameProject.vcxproj
- 26311038_Leeminsung_GameProject/main.cpp
- 26311038_Leeminsung_GameProject/packages.config
- .gitignore
- .gitattributes
- README.md
- docs/WEEK1_SUBMISSION_GUIDE.md

packages, .vs, bin, obj, x64, Debug, Release, 사용자별 .user 파일은 ZIP에 없어야 합니다.

## 최종 체크리스트

- [ ] GitHub 저장소 이름이 26311038_Leeminsung_GameProject이다.
- [ ] 프로젝트 이름이 26311038_Leeminsung_GameProject이다.
- [ ] README에 학번, 이름, 과목명, 과제명이 있다.
- [ ] 솔루션과 프로젝트 파일이 있다.
- [ ] glc2d와 DXSDK 패키지가 복원된다.
- [ ] 프로젝트가 빌드되고 실행된다.
- [ ] 초기 게임 화면과 게임 소스 코드가 있다.
- [ ] Tag 이름이 26311038_Leeminsung_GameProject_w01이다.
- [ ] main과 Tag를 원격 저장소에 Push했다.
- [ ] Tag 날짜를 캡처했다.
- [ ] Tag 기준 ZIP을 생성했다.

## 이후 주차 작업 원칙

- 2주차 기획서를 작성하면서 게임 코드에도 기획 내용을 반영합니다.
- 3주차 이미지와 사운드를 준비하면서 클래스 구성과 게임 구현을 계속합니다.
- 4주차에는 기존 게임을 완성하고 새 프로젝트를 만들지 않습니다.
- 기능 단위로 Commit을 계속 작성합니다.
- 매주 제출할 Commit에만 해당 주차 Tag를 생성합니다.
- 제출한 Tag를 이후 Commit으로 옮기지 않습니다.
