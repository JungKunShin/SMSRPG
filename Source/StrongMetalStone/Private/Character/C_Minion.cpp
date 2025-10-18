// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/C_Minion.h"
#include "Character/C_PlayerCharacter.h"
#include "Actor/Enemy/C_MonsterSpawner.h"

void AC_Minion::Death(AC_SMSCharacter* Killer)
{
	Super::Death(Killer);

	if(OwnerSpawner)
	OwnerSpawner->SpawnEnemy = nullptr;
}


// 카메라 쉐이크
void AC_Minion::PlayCameraShake_Implementation(AActor* DamageTarget)
{

	AC_PlayerCharacter* Player = Cast<AC_PlayerCharacter>(DamageTarget);
	if (!Player) return;

	APlayerController* PC = Cast<APlayerController>(Player->GetController());
	if (PC && PC->PlayerCameraManager && CamShakeClass)
	{
		PC->PlayerCameraManager->StartCameraShake(CamShakeClass);
	}



}
