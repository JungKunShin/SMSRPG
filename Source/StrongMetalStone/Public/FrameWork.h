
#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "C_SMSStruct.h"
#include "C_SMSUtility.h"

//자주 쓰는 include 미리 등록
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

//메니저
#include "Manager/C_DamageManager.h"
#include "Manager/C_CustomizingManager.h"
#include "Manager/C_EffectManager.h"
#include "Manager/C_SoundManager.h"

class AGameModeBase;
class AC_WorldGameMode;
class APlayerController;
class AC_WorldPlayerController;
class AC_PlayerCharacter;
class AC_Enemy;
class AC_WorldGameState;
class AC_WorldHUD;
class AC_WorldPlayerState;
class UC_SMSGameInstance;
class AC_Warrior;



//월드 매크로

// WorldLevel에서 호출많이하는 함수들이라 전부 매크로로 등록했음
// Ex) GetHUD()만 써도 GetWorld()->GetFirstPlayerController()->GetHUD()를 전부 친거랑 같은효과
#define GetMyGM() GetWorld()->GetAuthGameMode()
#define GetMyPC() GetWorld()->GetFirstPlayerController()
#define GetMyCharacter() GetWorld()->GetFirstPlayerController()->GetCharacter()
#define GetMyGS() GetWorld()->GetGameState()
#define GetMyHUD() GetWorld()->GetFirstPlayerController()->GetHUD()
#define GetMyPS() GetWorld()->GetFirstPlayerController()->PlayerState
#define GetMyGI() GetWorld()->GetGameInstance()
#define GetMyEffectManager() Cast<UC_SMSGameInstance>(GetWorld()->GetGameInstance())->EffectManager

//같은 이유로 주요 World클래스를 캐스팅해주는 함수 
AC_WorldGameMode* CastWGM(AGameModeBase* GM);
AC_WorldPlayerController* CastWPC(APlayerController* PC);
AC_PlayerCharacter* CastWCharacter(AActor* Character);
AC_Enemy* CastWEnemy(AActor* Enemy);
AC_WorldGameState* CastWGS(AGameStateBase* GS);
AC_WorldHUD* CastWHUD(AHUD* WHUD);
AC_WorldPlayerState* CastWPS(APlayerState* PS);
UC_SMSGameInstance* CastWGI(UGameInstance* GI);
AC_Warrior* CastWWarrior(AActor* Character);

FString GetLevelIP(int PortNum);