// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyCharacter/NotifyState/C_Revenant_BaseAttack_ANS.h"
#include "Character/C_RevenantBossCharacter.h"
#include "Character/Skill/BossRevenant/BluePrint/C_Revenant_SceneComponent.h"


void UC_Revenant_BaseAttack_ANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{

    Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (!MeshComp)return;

	AC_RevenantBossCharacter* Boss = Cast<AC_RevenantBossCharacter>(MeshComp->GetOwner());

	if (!Boss)return;

	

    // 서버인지 체크 
	if (!Boss->HasAuthority())
	{
		return;
	}
    // 해당 노티파이의 오너가 피가 1이상인지 체크
	if (Boss->EnemyInfo.Curhp <= 0.0f) return;
	

	// 스폰하기 

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Boss;
	SpawnParams.Instigator = Boss->GetInstigator();

	FVector SpawnLocation = Boss->GetActorLocation();
	FRotator SpawnRotation = Boss->GetActorRotation();

	MeshComp->GetWorld()->SpawnActor<AActor>(Revenant_Bullet, SpawnLocation, SpawnRotation, SpawnParams);



}


void UC_Revenant_BaseAttack_ANS::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
}


void UC_Revenant_BaseAttack_ANS::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}
