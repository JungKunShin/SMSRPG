// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/NotifyState/Warrior/C_WrExplosionWaveANS.h"
#include "Character/C_Warrior.h"
#include "PlayerController/C_WorldPlayerController.h"

void UC_WrExplosionWaveANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (!MeshComp)return;
	AC_Warrior* Warrior = CastWWarrior(MeshComp->GetOwner());
	if (!Warrior)return;
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Warrior->GetController());
	if (!WPC)return;

	if (Warrior->HasAuthority()) // 서버에서만 소환
	{
		FVector SpawnLocation = MeshComp->GetSocketLocation("FX_Sword_Top"); // 전사 검 끝 소켓저장
		FRotator SpawnRotation = MeshComp->GetSocketRotation("FX_Sword_Top");

		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = Warrior;
		SpawnedAttackParticle = MeshComp->GetWorld()->SpawnActor<AC_WrExplosionWaveAP>(AttackParticleClass, SpawnLocation, SpawnRotation, SpawnParam); // 액터 소환

		FTimerDelegate TimerDel;
		TimerDel.BindUFunction(this, FName("SpawnDelayedActor"), MeshComp); // SpawnDelayedActor 함수 바인딩

		MeshComp->GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, TimerDel, 0.2f, false); // 각 타이머별로 각 시간에 맞춰 소환
		MeshComp->GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle1, TimerDel, 0.4f, false);
		MeshComp->GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle2, TimerDel, 0.6f, false);
		MeshComp->GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle3, TimerDel, 0.8f, false);
	}
}

void UC_WrExplosionWaveANS::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp)return;
	AC_Warrior* Warrior = CastWWarrior(MeshComp->GetOwner());
	if (!Warrior)return;
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Warrior->GetController());
	if (!WPC)return;

	if (MeshComp->GetWorld())
	{
		MeshComp->GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle); // 타이머핸들 clear
		MeshComp->GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle1);
		MeshComp->GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle2);
		MeshComp->GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle3);
		Distance = 500.0f; //거리값 초기화
		TotalScale = FVector(FIRST_SCALE, FIRST_SCALE, FIRST_SCALE); // 스케일값 초기화
	}
}

void UC_WrExplosionWaveANS::SpawnDelayedActor(USkeletalMeshComponent* MeshComp)
{
	if (!MeshComp || !MeshComp->GetOwner() || !AttackParticleClass)
	{
		return;
	}
	UWorld* World = MeshComp->GetWorld();

	if (!World)
	{
		return;
	}

	if (!MeshComp)return;
	AC_Warrior* Warrior = CastWWarrior(MeshComp->GetOwner());
	if (!Warrior)return;
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Warrior->GetController());
	if (!WPC)return;

	FVector ForwardVector = Warrior->GetActorForwardVector();
	FVector SpawnLocation = MeshComp->GetSocketLocation("FX_Sword_Top") + ForwardVector * Distance; // 전사 검 끝 소켓 위치로부터 앞방향으로 Distanc미터에서
	FRotator SpawnRotation = MeshComp->GetSocketRotation("FX_Sword_Top");
	Distance += 500.0f; // 거리값 5미터 추가

	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = Warrior;

	SpawnedAttackParticle = MeshComp->GetWorld()->SpawnActor<AC_WrExplosionWaveAP>(AttackParticleClass, SpawnLocation, SpawnRotation, SpawnParam); // 액터 소환
	SpawnedAttackParticle->SetActorScale3D(TotalScale); // 스케일 값 설정
	TotalScale.X += ADD_SCALE; // 스케일 값 추가
	TotalScale.Y += ADD_SCALE;
	TotalScale.Z += ADD_SCALE;
}
