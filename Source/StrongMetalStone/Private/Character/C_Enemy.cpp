#include "Character/C_Enemy.h"
#include "HUD/C_WorldHUD.h"
#include "Character/C_PlayerCharacter.h"
#include "Component/C_SkillSystemComponent.h"
#include "Actor/Item/C_Gold.h"
#include "Actor/Item/C_Item.h"

AC_Enemy::AC_Enemy()
{
}

void AC_Enemy::BaseAttack(float Value)
{
}

void AC_Enemy::Death(AC_SMSCharacter* Killer)
{
	Super::Death(Killer);
	if (Killer)
	{
		if (CastWCharacter(Killer)->PartyInfo.InParty)
		{
			for (AC_PlayerCharacter* PartyCharacter : CastWCharacter(Killer)->PartyInfo.PartyPlayers)
			{
				CastWCharacter(PartyCharacter)->CharacterInfo.CurExp += EnemyInfo.DropExp;
				CastWCharacter(PartyCharacter)->IncreaseExp(CastWCharacter(PartyCharacter)->CharacterInfo.CurExp);

			}
		}
		else
		{
			CastWCharacter(Killer)->CharacterInfo.CurExp += EnemyInfo.DropExp;
			CastWCharacter(Killer)->IncreaseExp(CastWCharacter(Killer)->CharacterInfo.CurExp);
		}
	}
	
	if (DropItem.Num() > 0)
	{
		int32 Index = FMath::RandRange(0, DropItem.Num() - 1);
		TSubclassOf<AC_Item> ItemClass = DropItem[Index];

		if (ItemClass)
		{
			GetWorld()->SpawnActor<AC_Item>(ItemClass, GetActorLocation(), FRotator::ZeroRotator);
		}
	}
	AC_Gold* DropGold =  GetWorld()->SpawnActor<AC_Gold>(DropGoldClass, GetActorLocation(), FRotator::ZeroRotator);
	DropGold->MulitySetAmount(DropGoldValue);	
}

void AC_Enemy::ServerUpdate_Implementation(FEnemyInfo _EnemyInfo)
{
	EnemyInfo = _EnemyInfo;
	MultiUpdate(_EnemyInfo);
}

void AC_Enemy::MultiUpdate_Implementation(FEnemyInfo _EnemyInfo)
{
	EnemyInfo = _EnemyInfo;
}

void AC_Enemy::Update_Implementation()
{	
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		if (APlayerController* PC = Cast<APlayerController>(*It))
		{
			if (PC->IsLocalController())
			{
				// UI Update
				if (AC_WorldHUD* WorldHUD = Cast<AC_WorldHUD>(PC->GetHUD()))
				{
					WorldHUD->UpdateProgressBar(EProgressBarType::BOSS, EnemyInfo.Curhp);
				}
			}
		}
	}
}