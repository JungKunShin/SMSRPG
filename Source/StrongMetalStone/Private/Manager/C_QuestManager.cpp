#include "Manager/C_QuestManager.h"
#include "Character/C_PlayerCharacter.h"
#include "Quest/C_SMSQuest.h"
#include "HUD/C_WorldHUD.h"
#include "PlayerController/C_WorldPlayerController.h"

// Sets default values
AC_QuestManager::AC_QuestManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AC_QuestManager::BeginPlay()
{
	Super::BeginPlay();
}

void AC_QuestManager::PickUpInit(AC_PlayerCharacter* Character)
{
	if (!OnPickUp)return;
	//위젯을 열어주고
	//캐릭터에 퀘스트어레이에서 해당퀘스트가 이미 존재하는지 확인
	//없으면 새로 생성해서 넣어주기

	AC_WorldPlayerController* Controller = Cast<AC_WorldPlayerController>(Character->GetController());
	AC_WorldHUD* HUD = Cast<AC_WorldHUD>(Controller->GetHUD());

	if (HUD)
	{
		HUD->SetQuestWidgetVisible(true);
	}

	for (int i = 0; i < Character->QuestArr.Num(); ++i)
	{
		if (Character->QuestArr[i]->GetClass() == PickUp)
		{
			HUD->SetQuestText(Character->QuestArr[i]);
			return;
		}
	}

	PickUpINS = NewObject<AC_SMSQuest>(this, PickUp);
	PickUpINS->QuestData.OwnerName = Character->CharacterInfo.CharacterName;
	CurQuest = PickUpINS;
	HUD->SetQuestText(PickUpINS);
}

void AC_QuestManager::KillMonsterInit(AC_PlayerCharacter* Character)
{
	if (!OnKillMonster)return;
	AC_WorldPlayerController* Controller = Cast<AC_WorldPlayerController>(Character->GetController());
	AC_WorldHUD* HUD = Cast<AC_WorldHUD>(Controller->GetHUD());

	if (HUD)
	{
		HUD->SetQuestWidgetVisible(true);
	}

	for (int i = 0; i < Character->QuestArr.Num(); ++i)
	{
		if (Character->QuestArr[i]->GetClass() == KillMonster)
		{
			HUD->SetQuestText(Character->QuestArr[i]);
			return;
		}
	}

	KillMonsterINS = NewObject<AC_SMSQuest>(this, KillMonster);
	KillMonsterINS->QuestData.OwnerName = Character->CharacterInfo.CharacterName;
	CurQuest = KillMonsterINS;
	HUD->SetQuestText(KillMonsterINS);
}

void AC_QuestManager::DefeatBossInit(AC_PlayerCharacter* Character)
{
	if (!OnDefeatBoss)return;
	AC_WorldPlayerController* Controller = Cast<AC_WorldPlayerController>(Character->GetController());
	AC_WorldHUD* HUD = Cast<AC_WorldHUD>(Controller->GetHUD());

	if (HUD)
	{
		HUD->SetQuestWidgetVisible(true);
	}

	for (int i = 0; i < Character->QuestArr.Num(); ++i)
	{
		if (Character->QuestArr[i]->GetClass() == DefeatBoss)
		{
			HUD->SetQuestText(Character->QuestArr[i]);
			return;
		}
	}
	DefeatBossINS = NewObject<AC_SMSQuest>(this,DefeatBoss);
	DefeatBossINS->QuestData.OwnerName = Character->CharacterInfo.CharacterName;
	CurQuest = DefeatBossINS;
	HUD->SetQuestText(DefeatBossINS);
}


	
