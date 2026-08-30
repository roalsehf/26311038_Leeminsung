# DUNGEON DECK 게임 기획서

## 1. 프로젝트 기본 정보

- 프로젝트 이름: 26311038_Leeminsung_GameProject
- 게임 제목: DUNGEON DECK
- 장르: 턴제 덱빌딩 카드 RPG
- 개발 언어: C++17
- 그래픽 라이브러리: glc2d
- 개발 도구: Visual Studio 2022 Community
- 버전 관리: Git, GitHub
- 개발 기간: 4주

## 2. 기획 의도

DUNGEON DECK은 제한된 Energy 안에서 공격, 방어, 드로우 카드를 선택해 적을 쓰러뜨리는 턴제 카드 RPG이다. 초반에는 카드 3종과 적 3단계만 사용하여 전투 규칙을 명확하게 구현하고, 개발이 진행되면 카드와 시각 리소스를 추가한다.

이 게임을 통해 다음 내용을 구현하고 학습한다.

- glc2d를 사용한 게임 화면 출력
- 키보드 입력과 화면 상태 전환
- C++ 클래스와 enum class를 사용한 게임 구조
- 덱, 손패, 버림 더미 자료구조
- 턴, Energy, Block, Damage 처리
- 적 행동 예고와 반복 패턴
- Git Commit과 주차별 Tag를 이용한 개발 과정 관리

## 3. 전체 게임 흐름

1. 메인 메뉴를 표시한다.
2. GAME START를 선택한다.
3. Stage 1 전투를 시작한다.
4. 플레이어가 카드 5장을 드로우한다.
5. 플레이어가 Energy를 사용하여 카드를 낸다.
6. 플레이어가 턴을 종료한다.
7. 적이 예고한 행동을 실행한다.
8. 한쪽 HP가 0이 될 때까지 플레이어 턴과 적 턴을 반복한다.
9. 승리하면 보상 카드를 선택한다.
10. 다음 Stage를 시작한다.
11. Stage 3의 Dungeon Warden을 처치하면 GAME CLEAR를 표시한다.
12. 플레이어 HP가 0이 되면 GAME OVER를 표시한다.
13. Enter를 누르면 플레이 데이터를 초기화하고 메인 메뉴로 돌아간다.

## 4. 게임 상태

게임 상태는 여러 bool 변수가 아니라 enum class로 구분한다.

```cpp
enum class GameState
{
    MainMenu,
    HowToPlay,
    Battle,
    Reward,
    GameOver,
    GameClear,
    Exit
};
```

1주차 프로토타입에는 MainMenu, HowToPlay, BattlePreview 상태를 먼저 구현한다. 이후 주차에 Battle, Reward, GameOver, GameClear 상태를 연결한다.

## 5. 메인 메뉴

메뉴 항목은 다음과 같다.

1. GAME START
2. HOW TO PLAY
3. EXIT

조작 방법은 다음과 같다.

- W 또는 위 방향키: 위 항목 이동
- S 또는 아래 방향키: 아래 항목 이동
- Enter: 선택
- Esc: 이전 화면 또는 종료

선택된 메뉴는 glc2d 글꼴의 색상을 변경하여 구분한다. Windows Console API와 system 함수를 사용하지 않는다.

## 6. 플레이어 규칙

- 최대 HP: 50
- 시작 HP: 50
- 최대 Energy: 3
- 턴 시작 Energy: 3
- 시작 Block: 0
- 기본 손패: 5장

플레이어 턴 시작 시 처리 순서는 다음과 같다.

1. Energy를 최대값까지 회복한다.
2. Block을 0으로 초기화한다.
3. 카드 5장을 손패로 가져온다.

피해를 받으면 Block이 먼저 피해를 흡수한다. 남은 피해만 HP에서 감소한다. HP와 Energy는 0보다 작아지지 않도록 처리한다.

## 7. 시작 덱

시작 덱은 총 10장이다.

- Strike 5장
- Guard 4장
- Focus 1장

### Strike

- 종류: Attack
- 비용: 1
- 효과: 적에게 6 Damage
- 설명: Deal 6 damage.

### Guard

- 종류: Skill
- 비용: 1
- 효과: 플레이어 Block 5 증가
- 설명: Gain 5 Block.

### Focus

- 종류: Skill
- 비용: 0
- 효과: 카드 1장 추가 드로우
- 설명: Draw 1 card.

카드 효과는 카드 이름 문자열을 비교하는 방식으로 처리하지 않는다. CardType과 카드 데이터에 저장된 Damage, Block, DrawCount를 사용한다.

## 8. 덱 규칙

Deck 클래스는 다음 영역을 관리한다.

- DrawPile
- Hand
- DiscardPile

전투 시작 시 시작 덱을 생성하고 std::shuffle로 섞는다. 난수 엔진은 Deck이 보관하며 매 함수 호출마다 새로운 시드를 만들지 않는다.

카드를 사용하면 Hand에서 제거하여 DiscardPile로 이동한다. 턴 종료 시 남은 Hand 카드도 DiscardPile로 이동한다. DrawPile이 부족하면 DiscardPile을 DrawPile로 이동하고 다시 섞은 다음 필요한 수만큼 드로우한다.

## 9. 적 규칙

### Stage 1 Training Goblin

- 최대 HP: 32
- 행동 1: Attack 7
- 행동 2: Defend 5
- 행동 3: Heavy Attack 11
- 행동 4: 행동 1부터 반복

### Stage 2 Armored Goblin

- 최대 HP: 45
- 행동 1: Attack 8
- 행동 2: Defend 6
- 행동 3: Heavy Attack 12
- 행동 4: 행동 1부터 반복

### Stage 3 Dungeon Warden

- 최대 HP: 65
- 행동 1: Attack 8
- 행동 2: Defend 7
- 행동 3: Heavy Attack 14
- 행동 4: Attack 8
- 행동 5: 행동 1부터 반복

적은 다음 행동을 Intent로 미리 표시한다. 행동은 EnemyActionType enum class와 turnCount로 결정한다. 행동 이름 문자열을 비교하여 로직을 실행하지 않는다.

## 10. 전투 조작

- 숫자 1부터 5: 해당 위치의 손패 카드 사용
- E: 플레이어 턴 종료
- Esc: 필요한 경우 이전 화면으로 이동

손패보다 큰 번호를 선택하면 게임을 종료하지 않고 안내 메시지를 표시한다. Energy가 부족한 카드를 선택하면 카드를 제거하지 않고 Not enough Energy 메시지를 표시한다.

## 11. 카드 사용 처리

### Strike 처리

1. Energy가 1 이상인지 확인한다.
2. Energy를 1 감소시킨다.
3. 적 Block과 HP에 6 Damage를 적용한다.
4. Strike를 Hand에서 제거한다.
5. Strike를 DiscardPile로 이동한다.

### Guard 처리

1. Energy가 1 이상인지 확인한다.
2. Energy를 1 감소시킨다.
3. 플레이어 Block을 5 증가시킨다.
4. Guard를 Hand에서 제거한다.
5. Guard를 DiscardPile로 이동한다.

### Focus 처리

1. Energy 감소 없이 카드 1장을 추가 드로우한다.
2. Focus를 Hand에서 제거한다.
3. Focus를 DiscardPile로 이동한다.

## 12. 턴 처리

플레이어가 E를 누르면 다음 순서로 처리한다.

1. 손에 남은 카드를 모두 DiscardPile로 이동한다.
2. 적이 현재 Intent에 해당하는 행동을 실행한다.
3. 다음 적 Intent를 계산한다.
4. 플레이어와 적의 HP를 확인한다.
5. 전투가 계속되면 새로운 플레이어 턴을 시작한다.

## 13. 보상과 Stage

적을 처치하면 Strike, Guard, Focus 중 카드 1장을 선택한다. 선택한 카드는 플레이어의 영구 덱에 추가된다.

- Stage 1 승리 후 카드 보상 선택
- Stage 2 승리 후 카드 보상 선택
- Stage 3 승리 후 GAME CLEAR

플레이어 HP는 첫 프로토타입에서 Stage 사이에 유지한다. 밸런스 테스트 결과에 따라 회복 보상을 추가할 수 있다.

## 14. 화면 구성

### 메인 메뉴 화면

- 게임 제목
- 장르 설명
- GAME START
- HOW TO PLAY
- EXIT
- 조작 안내

### 전투 화면

- Stage 번호
- 적 이름, HP, Block
- 적의 다음 Intent
- 플레이어 HP, Block, Energy
- 현재 손패 카드
- 카드 비용과 효과
- 입력 안내
- 최근 행동 결과 메시지

### 보상 화면

- BATTLE WIN
- 처치한 적 이름
- 선택 가능한 카드 3종
- 선택 입력 안내

## 15. 클래스 구성 계획

불필요한 파일을 한 번에 만들지 않고 해당 기능을 구현하는 주차에 추가한다.

### 1주차

- main.cpp
- GameState를 사용한 메뉴와 화면 상태 전환

### 2주차

- GameManager.h, GameManager.cpp
- Player.h, Player.cpp
- Enemy.h, Enemy.cpp
- Card.h, Card.cpp

### 3주차

- Deck.h, Deck.cpp
- BattleManager.h, BattleManager.cpp
- RewardManager.h, RewardManager.cpp
- StageManager.h, StageManager.cpp

입력과 glc2d 출력 코드가 커지면 InputManager와 RenderManager를 추가한다. 역할이 적은 클래스를 형식적으로 만들지 않는다.

## 16. 리소스 계획

모든 이미지와 사운드는 저장소의 Assets 폴더에 포함한다.

예정 이미지 리소스는 다음과 같다.

- 메인 메뉴 배경
- 플레이어 초상화
- Training Goblin 이미지
- Armored Goblin 이미지
- Dungeon Warden 이미지
- Strike 카드 이미지
- Guard 카드 이미지
- Focus 카드 이미지
- 카드 테두리와 버튼 이미지

예정 사운드 리소스는 다음과 같다.

- 메인 메뉴 배경 음악
- 전투 배경 음악
- 카드 선택 효과음
- 공격 효과음
- 방어 효과음
- 승리 효과음
- 패배 효과음

리소스의 출처와 라이선스를 Assets/README.md에 기록한다.

## 17. 예외 처리 기준

다음 상황에서도 프로그램이 비정상 종료되지 않아야 한다.

- Energy가 부족한 카드 선택
- 존재하지 않는 손패 번호 입력
- DrawPile이 비어 있는 상태
- DrawPile과 DiscardPile이 모두 비어 있는 상태
- HP가 0 아래로 내려가는 상황
- Block보다 큰 Damage를 받는 상황
- Block보다 작은 Damage를 받는 상황
- 손패가 5장보다 적은 상황
- Focus 사용 시 DrawPile이 부족한 상황
- 전투 종료 직전 추가 입력

## 18. 사용하지 않는 구현 방식

- system("cls")
- system("pause")
- goto
- scanf
- 카드 이름 문자열만 비교하는 거대한 조건문
- 적 행동 문자열 비교 방식
- 매번 srand를 호출하는 방식
- 불필요한 new와 delete
- 선언만 있고 구현이 없는 함수
- 컴파일되지 않는 임시 코드
- TODO만 남긴 미완성 기능

## 19. 주차별 개발 계획

### 1주차 환경 구성과 초기 개발

- Git 저장소와 Visual Studio 프로젝트 구성
- glc2d와 DXSDK NuGet 복원 구성
- 메인 메뉴 구현
- W, S, 방향키, Enter, Esc 입력 구현
- HOW TO PLAY 화면 구현
- 전투 화면 미리보기 구현
- 1주차 빌드와 실행 검증

### 2주차 기획서와 핵심 데이터 구현

- 본 기획서 보완 및 제출
- GameManager 상태 구조 구현
- Player와 Enemy 클래스 구현
- Card 클래스와 카드 3종 구현
- 실제 전투 화면 데이터 연결

### 3주차 리소스와 전투 시스템 구현

- 이미지와 사운드 리소스 준비
- Deck, Hand, DiscardPile 구현
- 카드 사용과 Energy 처리
- Enemy Intent와 적 턴 구현
- 승패 판정과 보상 구현
- Stage 1부터 Stage 3 구현

### 4주차 완성과 검증

- 모든 리소스를 glc2d 화면에 적용
- Dungeon Warden 보스전 완성
- GAME OVER와 GAME CLEAR 완성
- 밸런스 조정
- 입력 예외 처리
- 전체 빌드와 실행 검증
- README와 제출 문서 최종 수정

## 20. 개발 로그 계획

- LOG 00: 프로젝트와 glc2d 환경 구성
- LOG 01: 메인 메뉴와 화면 상태 전환
- LOG 02: Player와 Enemy 데이터
- LOG 03: Card 클래스와 기본 카드
- LOG 04: Deck, Hand, DiscardPile
- LOG 05: 카드 사용과 Energy
- LOG 06: Enemy Intent와 적 턴
- LOG 07: 전투 승패
- LOG 08: 카드 보상
- LOG 09: Stage 시스템
- LOG 10: Dungeon Warden
- LOG 11: glc2d 이미지와 사운드 적용
- LOG 12: 밸런스와 UI 개선
- LOG 13: 예외 처리와 최종 리팩터링

각 로그는 실제 기능 구현과 빌드 확인이 끝난 뒤 별도 Commit으로 기록한다.

## 21. 최종 완료 기준

- 메인 메뉴에서 모든 항목을 선택할 수 있다.
- GAME START를 선택하면 Stage 1 전투가 시작된다.
- 턴 시작 시 카드 5장을 드로우한다.
- 숫자키로 카드를 사용할 수 있다.
- 카드 비용만큼 Energy가 감소한다.
- 공격, Block, 추가 드로우가 정상 처리된다.
- E로 턴을 종료하면 적 행동이 실행된다.
- 적 처치 후 보상 카드를 선택할 수 있다.
- Stage 2와 Stage 3으로 진행할 수 있다.
- Dungeon Warden 처치 후 GAME CLEAR가 표시된다.
- 플레이어 사망 후 GAME OVER가 표시된다.
- Enter를 누르면 메인 메뉴로 돌아간다.
- NuGet 복원 후 프로젝트가 오류 없이 빌드된다.
- 주차별 Commit과 Tag가 올바른 Commit을 가리킨다.
