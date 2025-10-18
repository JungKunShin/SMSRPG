
#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "C_SMSStruct.h"
#include "C_SMSUtility.h"

//���� ���� include �̸� ���
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

//�޴���
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



//���� ��ũ��

// WorldLevel���� ȣ�⸹���ϴ� �Լ����̶� ���� ��ũ�η� �������
// Ex) GetHUD()�� �ᵵ GetWorld()->GetFirstPlayerController()->GetHUD()�� ���� ģ�Ŷ� ����ȿ��
#define GetMyGM() GetWorld()->GetAuthGameMode()
#define GetMyPC() GetWorld()->GetFirstPlayerController()
#define GetMyCharacter() GetWorld()->GetFirstPlayerController()->GetCharacter()
#define GetMyGS() GetWorld()->GetGameState()
#define GetMyHUD() GetWorld()->GetFirstPlayerController()->GetHUD()
#define GetMyPS() GetWorld()->GetFirstPlayerController()->PlayerState
#define GetMyGI() GetWorld()->GetGameInstance()
#define GetMyEffectManager() Cast<UC_SMSGameInstance>(GetWorld()->GetGameInstance())->EffectManager

//���� ������ �ֿ� WorldŬ������ ĳ�������ִ� �Լ� 
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