// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/C_RevenantBossCharacter.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"
#include "C_SMSGameInstance.h"
#include "Quest/C_SMSQuest.h"
#include "HUD/C_WorldHUD.h"
#include "GameMode/C_WorldGameMode.h"


AC_RevenantBossCharacter::AC_RevenantBossCharacter()
{
	EnemyInfo.Name = TEXT("레버넌트");
	EnemyInfo.Maxhp = 100000;
	EnemyInfo.Curhp = 100000;

	EnemyInfo.Damage = 1200;
    EnemyInfo.Defense = 100;

	EnemyInfo.DropExp = 10;	
	
	EnemyInfo.CurGroggy = 100;
	EnemyInfo.MaxGroggy = 100;

	EnemyInfo.Job = EPlayerJob::BOSS;
}

void AC_RevenantBossCharacter::Death(AC_SMSCharacter* Killer)
{
	Super::Death(Killer);



	MultiDeath(Killer);
}

void AC_RevenantBossCharacter::OpenResult(AC_SMSCharacter* Killer)
{
	AC_PlayerCharacter* Character = Cast<AC_PlayerCharacter>(Killer);
	AC_WorldHUD* WorldHUD = CastWHUD(GetMyHUD());
	if (WorldHUD)
	{
		WorldHUD->SetResultWidgetVisible(true, EnemyInfo.Name); // 결과창 켜주기
		if (Character->PartyInfo.InParty) // 파티일 때,
		{
			FString Who;
			unsigned int WhoLevel;
			EPlayerJob Job;
			

			for (int i=0;i<Character->PartyInfo.PartyPlayers.Num();++i)
			{
				Who = Character->PartyInfo.PartyPlayers[i]->CharacterInfo.CharacterName;

				CharacterDamage.FindOrAdd(Who); // 만약 Map 안에 파티원이 없다면 추가
			}
			TArray<TPair<FString, float>>SortedArray = CharacterDamage.Array(); // Map의 배열화
			SortedArray.Sort([](const TPair<FString, float>& A, const TPair<FString, float>& B)
				{
					return A.Value > B.Value; // 데미지량에 따른 내림차순 정렬
				});

			for (const TPair<FString, float>& Pair : SortedArray)
			{
				for (int i = 0; i < Character->PartyInfo.PartyPlayers.Num(); ++i)
				{
					if (*Pair.Key == Character->PartyInfo.PartyPlayers[i]->CharacterInfo.CharacterName)
					{
						WhoLevel = Character->PartyInfo.PartyPlayers[i]->CharacterInfo.Level;
						Job = Character->PartyInfo.PartyPlayers[i]->CharacterInfo.Job;
					}
				}
				WorldHUD->AddResultText(*Pair.Key, Pair.Value, WhoLevel, Job); // 결과창에 추가
			}
		}
		else // 솔로일때,
		{
			FString Who = Character->CharacterInfo.CharacterName;
			CharacterDamage.FindOrAdd(Who);
			float WhoDamage = CharacterDamage.FindRef(Who);
			unsigned int WhoLevel = Character->CharacterInfo.Level;
			EPlayerJob Job = Character->CharacterInfo.Job;
			WorldHUD->AddResultText(Who, WhoDamage, WhoLevel,Job);
		}
	
	}
}

float AC_RevenantBossCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	if (Blocking)
	{

		
	   return 0.0f;

		
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);


}


void AC_RevenantBossCharacter::MultiDeath_Implementation(AC_SMSCharacter* Killer)
{
	AC_PlayerCharacter* Character = Cast<AC_PlayerCharacter>(Killer);
	if (Character)
	{
		if (!Character->PartyInfo.InParty) // 솔로일 때, 퀘스트 갱신
		{
			QuestUpdate(Killer);
		}
		else // 파티일 때, 퀘스트 갱신
		{
			for (AC_PlayerCharacter* PartyCharacter : Character->PartyInfo.PartyPlayers)
			{
				QuestUpdate(PartyCharacter);
			}
		}
	}

	OpenResult(Killer);
}


void AC_RevenantBossCharacter::QuestUpdate(AC_SMSCharacter* Killer)
{
	AC_PlayerCharacter* Character = Cast<AC_PlayerCharacter>(Killer);

	for (int i = 0; i < Character->QuestArr.Num(); ++i)
	{
		if (Character->QuestArr[i]->GetClass() == CastWGI(GetMyGI())->QuestManager->DefeatBoss)
		{
			Character->QuestArr[i]->QuestData.CurNum++;
			Character->QuestArr[i]->QuestData.QuestState = EQuestState::Completed;
			if (Character->QuestArr[i]->QuestData.CurNum >= Character->QuestArr[i]->ObjectNum)
			{
				Character->QuestArr[i]->QuestData.CurNum = Character->QuestArr[i]->ObjectNum;
			}
			if (CastWHUD(GetMyHUD()))
			{
				CastWHUD(GetMyHUD())->UpdateQuestingText(Character->QuestArr[i], i);
			}
			Character->QuestArr[i]->QuestData.QuestState = EQuestState::Completed;
			
			CastWPC(GetMyPC())->ServerDeleteQuestCSV(Character->QuestArr[i]->QuestData);			
			CastWPC(GetMyPC())->ServerAddQuestToCSV(Character->QuestArr[i]->QuestData);
		}
	}
}