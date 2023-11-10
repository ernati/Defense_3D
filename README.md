# Defense_3D


## 클래스 구조
### Defence_3DGameMode 클래스
- StartMap_GameMode와 InGameMode 블루프린트들이 상속하는 클래스다.
  
============================================================================================

### StartMap_PlayerController 클래스
- Start 레벨을 담당하는 클래스
- 게임이 시작되면, 게임이 시작되면, 플레이어의 키보드 입력을 제한하고, 메인메뉴 UI를 띄워
준다.

### InGamePlayerController 클래스

- 인게임 레벨을 담당하는 클래스
- 인게임 레벨에 진입하면, 유저에게 지금까지 소환된 몬스터 수, 유저 및 AttackTower가 잡은
몬스터 수, 현재 Point 를 알려주는 UI를 띄운다.
- 총 소환된 몬스터 수가 2000마리가 넘으면, 승리했으므로, 재시작 메뉴 UI을 띄운다.
  
=============================================================================================

### FPSCharacter 클래스 - 사용
- 플레이어 캐릭터 클래스
- 포탑을 생성할 수 있다.
- 비용은 포탑 1개당 20 point
- 1인칭 시점이며, 조준점을 통해 투사체를 발사한다.
- 히트 스캔 방식이다. 초당 8발을 발사한다.
### Defence_3DCharacter 클래스 - 미사용
- 플레이어 캐릭터 클래스
- 포탑을 생성할 수 있다.
- 비용은 포탑 1개당 20 point
- 3인칭 시점이며, 조준점을 통해 투사체를 발사한다.
- 히트 스캔 방식이다. 초당 8발을 발사한다.
  
============================================================================================

### Tower 클래스
- 포탑 클래스들이 상속받을 부모 클래스
### AttackTower 클래스
- 발사체를 발사하는 포탑 클래스
  
============================================================================================

### AttackTowerProjectile 클래스
- 발사체 클래스
- 포탑과 플레이어 캐릭터의 발사체 모두 이 클래스의 인스턴스를 사용한다.
- 데미지는 10이다.
  
============================================================================================

### BagComponent 클래스
- 플레이어 캐릭터의 Point 를 담는 컴포넌트
  - Point 획득
  - Point 값 리턴
### HealthComponent 클래스
- 이 컴포넌트를 보유하는 액터의 체력을 관리하는 컴포넌트
- 체력 관리 주요 함수
  - LoseHealth
    - 체력이 0 이하가 되면
      - 이 액터가 몬스터였다면 등급에 맞게 point를 캐릭터에게 부여한다.
      - 이 액터가 베이스 캠프였다면, 패배한다.
  - ReturnHealthRatio
    
============================================================================================

### BaseCamp 클래스
- 베이스 캠프 액터
- 이 액터가 적에 의해 파괴되면, 게임에서 패배한다.
- 체력 5000의 체력을 가진다.
  - HealthComponent
    
============================================================================================

### Enemy 클래스
- 적( 몬스터 )들이 상속받는 부모 클래스
- 공통 요소
  - HealthComponent
  - ProjectileMovement
  - Damage
### WeakestMob 클래스
- 기본 몬스터 클래스
- 80의 체력을 가진다.
  - HealthComponent
- 베이스 캠프 액터와 충돌하면, 사라지면서 베이스 캠프 액터에게 20의 데미지를 준다.
### EliteMob 클래스
- 엘리트 몬스터 클래스
- 400의 체력을 가진다.
  - HealthComponent
- 베이스 캠프 액터와 충돌하면, 사라지면서 베이스 캠프 액터에게 100의 데미지를 준다.
### BossMob 클래스
- 보스 몬스터 클래스
- 2000의 체력을 가진다
  - HealthComponent
- 베이스 캠프 액터와 충돌하면, 사라지면서 베이스 캠프 액터에게 100의 데미지를 준다.
  
============================================================================================

### Portal 클래스
- 포탈들이 상속받는 부모 클래스
### WeakestMobPortal 클래스
- 기본 몬스터 액터를 스폰하는 포탈 액터
- 1.85초마다 한번씩 , 각 기본 몬스터 포탈은 기본 몬스터를 스폰한다.
### EliteMobPortal 클래스
- 엘리트 몬스터 액터를 스폰하는 포탈 액터
- 14.27초마다 한번씩 , 각 엘리트 몬스터 포탈은 엘리트 몬스터를 스폰한다.
### BossMobPortal 클래스
- 보스 몬스터 액터를 스폰하는 포탈 액터
- 총 스폰된 몬스터의 수가 100의 배수일 때마다, 각 보스몬스터 포탈은 보스몬스터를 스폰한다.

============================================================================================

### IngameWidget 클래스
### MainMenuWidget 클래스
### RestartWidget 클래스
- 유저에게 보여줄 UI 메뉴들
